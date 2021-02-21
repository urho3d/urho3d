// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

#ifdef URHO3D_URHO2D
// explicit CollisionBox2D::CollisionBox2D(Context* context) | File: ../Urho2D/CollisionBox2D.h
static CollisionBox2D* CollisionBox2D_CollisionBox2D_Context()
{
    return new CollisionBox2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionBox2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionBox2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit CollisionChain2D::CollisionChain2D(Context* context) | File: ../Urho2D/CollisionChain2D.h
static CollisionChain2D* CollisionChain2D_CollisionChain2D_Context()
{
    return new CollisionChain2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Vector2>& CollisionChain2D::GetVertices() const | File: ../Urho2D/CollisionChain2D.h
static CScriptArray* CollisionChain2D_GetVertices_void(CollisionChain2D* ptr)
{
    const PODVector<Vector2>& result = ptr->GetVertices();
    return VectorToArray(result, "Array<Vector2>");
}
#endif

#ifdef URHO3D_URHO2D
// void CollisionChain2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionChain2D.h
static void CollisionChain2D_SetVertices_PODVectorVector2(CollisionChain2D* ptr, CScriptArray* vertices_conv)
{
    PODVector<Vector2> vertices = ArrayToPODVector<Vector2>(vertices_conv);
    ptr->SetVertices(vertices);
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionChain2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionChain2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit CollisionCircle2D::CollisionCircle2D(Context* context) | File: ../Urho2D/CollisionCircle2D.h
static CollisionCircle2D* CollisionCircle2D_CollisionCircle2D_Context()
{
    return new CollisionCircle2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionCircle2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionCircle2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit CollisionEdge2D::CollisionEdge2D(Context* context) | File: ../Urho2D/CollisionEdge2D.h
static CollisionEdge2D* CollisionEdge2D_CollisionEdge2D_Context()
{
    return new CollisionEdge2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionEdge2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionEdge2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit CollisionPolygon2D::CollisionPolygon2D(Context* context) | File: ../Urho2D/CollisionPolygon2D.h
static CollisionPolygon2D* CollisionPolygon2D_CollisionPolygon2D_Context()
{
    return new CollisionPolygon2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Vector2>& CollisionPolygon2D::GetVertices() const | File: ../Urho2D/CollisionPolygon2D.h
static CScriptArray* CollisionPolygon2D_GetVertices_void(CollisionPolygon2D* ptr)
{
    const PODVector<Vector2>& result = ptr->GetVertices();
    return VectorToArray(result, "Array<Vector2>");
}
#endif

#ifdef URHO3D_URHO2D
// void CollisionPolygon2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionPolygon2D.h
static void CollisionPolygon2D_SetVertices_PODVectorVector2(CollisionPolygon2D* ptr, CScriptArray* vertices_conv)
{
    PODVector<Vector2> vertices = ArrayToPODVector<Vector2>(vertices_conv);
    ptr->SetVertices(vertices);
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionPolygon2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionPolygon2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_PHYSICS
// explicit CollisionShape::CollisionShape(Context* context) | File: ../Physics/CollisionShape.h
static CollisionShape* CollisionShape_CollisionShape_Context()
{
    return new CollisionShape(GetScriptContext());
}
#endif

#ifdef URHO3D_PHYSICS
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionShape_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionShape* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CollisionShape2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CollisionShape2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// Color::Color(const Color& color) noexcept=default | File: ../Math/Color.h
static void Color_Color_Color(Color* ptr, const Color &color)
{
    new(ptr) Color(color);
}

// Color::Color(const Color& color, float a) noexcept | File: ../Math/Color.h
static void Color_Color_Color_float(Color* ptr, const Color &color, float a)
{
    new(ptr) Color(color, a);
}

// Color::Color(float r, float g, float b) noexcept | File: ../Math/Color.h
static void Color_Color_float_float_float(Color* ptr, float r, float g, float b)
{
    new(ptr) Color(r, g, b);
}

// Color::Color(float r, float g, float b, float a) noexcept | File: ../Math/Color.h
static void Color_Color_float_float_float_float(Color* ptr, float r, float g, float b, float a)
{
    new(ptr) Color(r, g, b, a);
}

// explicit Color::Color(const Vector3& color) | File: ../Math/Color.h
static void Color_Color_Vector3(Color* ptr, const Vector3 &color)
{
    new(ptr) Color(color);
}

// explicit Color::Color(const Vector4& color) | File: ../Math/Color.h
static void Color_Color_Vector4(Color* ptr, const Vector4 &color)
{
    new(ptr) Color(color);
}

// explicit Component::Component(Context* context) | File: ../Scene/Component.h
static Component* Component_Component_Context()
{
    return new Component(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Component* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_NETWORK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Connection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Connection* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit Console::Console(Context* context) | File: ../Engine/Console.h
static Console* Console_Console_Context()
{
    return new Console(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Console_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Console* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit ConstantBuffer::ConstantBuffer(Context* context) | File: ../Graphics/ConstantBuffer.h
static ConstantBuffer* ConstantBuffer_ConstantBuffer_Context()
{
    return new ConstantBuffer(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ConstantBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ConstantBuffer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// Context::Context() | File: ../Core/Context.h
static Context* Context_Context_void()
{
    return new Context();
}

// SharedPtr<Object> Context::CreateObject(StringHash objectType) | File: ../Core/Context.h
static Object* Context_CreateObject_StringHash(Context* ptr, StringHash objectType)
{
    SharedPtr<Object> result = ptr->CreateObject(objectType);
    return result.Detach();
}

#ifdef URHO3D_NAVIGATION
// explicit CrowdAgent::CrowdAgent(Context* context) | File: ../Navigation/CrowdAgent.h
static CrowdAgent* CrowdAgent_CrowdAgent_Context()
{
    return new CrowdAgent(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CrowdAgent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CrowdAgent* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_NAVIGATION
// explicit CrowdManager::CrowdManager(Context* context) | File: ../Navigation/CrowdManager.h
static CrowdManager* CrowdManager_CrowdManager_Context()
{
    return new CrowdManager(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// PODVector<CrowdAgent*> CrowdManager::GetAgents(Node* node=nullptr, bool inCrowdFilter=true) const | File: ../Navigation/CrowdManager.h
static CScriptArray* CrowdManager_GetAgents_Node_bool(CrowdManager* ptr, Node* node, bool inCrowdFilter)
{
    PODVector<CrowdAgent*> result = ptr->GetAgents(node, inCrowdFilter);
    return VectorToHandleArray(result, "Array<CrowdAgent@>");
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CrowdManager_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CrowdManager* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Cursor_AddTags_StringVector(Cursor* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// explicit Cursor::Cursor(Context* context) | File: ../UI/Cursor.h
static Cursor* Cursor_Cursor_Context()
{
    return new Cursor(GetScriptContext());
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Cursor_GetChildren_void(Cursor* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Cursor_GetChildren_bool(Cursor* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Cursor_GetChildrenWithTag_String_bool(Cursor* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Cursor_GetTags_void(Cursor* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Cursor_SetTags_StringVector(Cursor* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Cursor_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Cursor* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit CustomGeometry::CustomGeometry(Context* context) | File: ../Graphics/CustomGeometry.h
static CustomGeometry* CustomGeometry_CustomGeometry_Context()
{
    return new CustomGeometry(GetScriptContext());
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* CustomGeometry_GetLights_void(CustomGeometry* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* CustomGeometry_GetVertexLights_void(CustomGeometry* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CustomGeometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CustomGeometry* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// ColorFrame::ColorFrame() | File: ../Graphics/ParticleEffect.h
static ColorFrame* ColorFrame_ColorFrame_void()
{
    return new ColorFrame();
}

// explicit ColorFrame::ColorFrame(const Color& color) | File: ../Graphics/ParticleEffect.h
static ColorFrame* ColorFrame_ColorFrame_Color(const Color &color)
{
    return new ColorFrame(color);
}

// ColorFrame::ColorFrame(const Color& color, float time) | File: ../Graphics/ParticleEffect.h
static ColorFrame* ColorFrame_ColorFrame_Color_float(const Color &color, float time)
{
    return new ColorFrame(color, time);
}

#ifdef URHO3D_PHYSICS
// void ConvexData::BuildHull(const PODVector<Vector3>& vertices) | File: ../Physics/CollisionShape.h
static void ConvexData_BuildHull_PODVectorVector3(ConvexData* ptr, CScriptArray* vertices_conv)
{
    PODVector<Vector3> vertices = ArrayToPODVector<Vector3>(vertices_conv);
    ptr->BuildHull(vertices);
}
#endif

#ifdef URHO3D_PHYSICS
// ConvexData::ConvexData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
static ConvexData* ConvexData_ConvexData_Model_unsigned(Model *model, unsigned lodLevel)
{
    return new ConvexData(model, lodLevel);
}
#endif

#ifdef URHO3D_PHYSICS
// explicit ConvexData::ConvexData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
static ConvexData* ConvexData_ConvexData_CustomGeometry(CustomGeometry *custom)
{
    return new ConvexData(custom);
}
#endif

// explicit CursorShapeInfo::CursorShapeInfo(int systemCursor) | File: ../UI/Cursor.h
static void CursorShapeInfo_CursorShapeInfo_int(CursorShapeInfo* ptr, int systemCursor)
{
    new(ptr) CursorShapeInfo(systemCursor);
}

void ASRegisterGenerated_Members_Cn_Cz(asIScriptEngine* engine)
{
#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionBox2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void AllocateNetworkState()", AS_METHODPR(CollisionBox2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ApplyAttributes()", AS_METHODPR(CollisionBox2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionBox2D::CollisionBox2D(Context* context) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_FACTORY, "CollisionBox2D@+ f()", AS_FUNCTION(CollisionBox2D_CollisionBox2D_Context), AS_CALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void CreateFixture()", AS_METHODPR(CollisionBox2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionBox2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // float CollisionBox2D::GetAngle() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAngle() const", AS_METHODPR(CollisionBox2D, GetAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_angle() const", AS_METHODPR(CollisionBox2D, GetAngle, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionBox2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionBox2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionBox2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionBox2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionBox2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionBox2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionBox2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionBox2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const String& GetCategory() const", AS_METHODPR(CollisionBox2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const String& get_category() const", AS_METHODPR(CollisionBox2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetCategoryBits() const", AS_METHODPR(CollisionBox2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_categoryBits() const", AS_METHODPR(CollisionBox2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // const Vector2& CollisionBox2D::GetCenter() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& GetCenter() const", AS_METHODPR(CollisionBox2D, GetCenter, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_center() const", AS_METHODPR(CollisionBox2D, GetCenter, () const, const Vector2&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionBox2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetDensity() const", AS_METHODPR(CollisionBox2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_density() const", AS_METHODPR(CollisionBox2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionBox2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionBox2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetFriction() const", AS_METHODPR(CollisionBox2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_friction() const", AS_METHODPR(CollisionBox2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionBox2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionBox2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionBox2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionBox2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetGroupIndex() const", AS_METHODPR(CollisionBox2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_groupIndex() const", AS_METHODPR(CollisionBox2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetID() const", AS_METHODPR(CollisionBox2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "uint get_id() const", AS_METHODPR(CollisionBox2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetInertia() const", AS_METHODPR(CollisionBox2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_inertia() const", AS_METHODPR(CollisionBox2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionBox2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetMaskBits() const", AS_METHODPR(CollisionBox2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_maskBits() const", AS_METHODPR(CollisionBox2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetMass() const", AS_METHODPR(CollisionBox2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_mass() const", AS_METHODPR(CollisionBox2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionBox2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionBox2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Node@+ GetNode() const", AS_METHODPR(CollisionBox2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Node@+ get_node() const", AS_METHODPR(CollisionBox2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionBox2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "uint get_numAttributes() const", AS_METHODPR(CollisionBox2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionBox2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionBox2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionBox2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionBox2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetRestitution() const", AS_METHODPR(CollisionBox2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_restitution() const", AS_METHODPR(CollisionBox2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionBox2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // const Vector2& CollisionBox2D::GetSize() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& GetSize() const", AS_METHODPR(CollisionBox2D, GetSize, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_size() const", AS_METHODPR(CollisionBox2D, GetSize, () const, const Vector2&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionBox2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "StringHash GetType() const", AS_METHODPR(CollisionBox2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "StringHash get_type() const", AS_METHODPR(CollisionBox2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const String& GetTypeName() const", AS_METHODPR(CollisionBox2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const String& get_typeName() const", AS_METHODPR(CollisionBox2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionBox2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionBox2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionBox2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsEnabled() const", AS_METHODPR(CollisionBox2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_enabled() const", AS_METHODPR(CollisionBox2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionBox2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionBox2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionBox2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsReplicated() const", AS_METHODPR(CollisionBox2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_replicated() const", AS_METHODPR(CollisionBox2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsTemporary() const", AS_METHODPR(CollisionBox2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_temporary() const", AS_METHODPR(CollisionBox2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsTrigger() const", AS_METHODPR(CollisionBox2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_trigger() const", AS_METHODPR(CollisionBox2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionBox2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionBox2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionBox2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionBox2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionBox2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionBox2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionBox2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnSetEnabled()", AS_METHODPR(CollisionBox2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionBox2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionBox2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionBox2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionBox2D", "int Refs() const", AS_METHODPR(CollisionBox2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_refs() const", AS_METHODPR(CollisionBox2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionBox2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionBox2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ReleaseFixture()", AS_METHODPR(CollisionBox2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionBox2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void Remove()", AS_METHODPR(CollisionBox2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionBox2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionBox2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionBox2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ResetToDefault()", AS_METHODPR(CollisionBox2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionBox2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionBox2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionBox2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionBox2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionBox2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionBox2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void CollisionBox2D::SetAngle(float angle) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAngle(float)", AS_METHODPR(CollisionBox2D, SetAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_angle(float)", AS_METHODPR(CollisionBox2D, SetAngle, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionBox2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionBox2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionBox2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionBox2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionBox2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionBox2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionBox2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionBox2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionBox2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionBox2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionBox2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionBox2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_categoryBits(int)", AS_METHODPR(CollisionBox2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionBox2D::SetCenter(const Vector2& center) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(const Vector2&in)", AS_METHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_center(const Vector2&in)", AS_METHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionBox2D::SetCenter(float x, float y) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(float, float)", AS_METHODPR(CollisionBox2D, SetCenter, (float, float), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetDensity(float)", AS_METHODPR(CollisionBox2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_density(float)", AS_METHODPR(CollisionBox2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetEnabled(bool)", AS_METHODPR(CollisionBox2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_enabled(bool)", AS_METHODPR(CollisionBox2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetFriction(float)", AS_METHODPR(CollisionBox2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_friction(float)", AS_METHODPR(CollisionBox2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionBox2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionBox2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionBox2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_groupIndex(int)", AS_METHODPR(CollisionBox2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionBox2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionBox2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetMaskBits(int)", AS_METHODPR(CollisionBox2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_maskBits(int)", AS_METHODPR(CollisionBox2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionBox2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionBox2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionBox2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetRestitution(float)", AS_METHODPR(CollisionBox2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_restitution(float)", AS_METHODPR(CollisionBox2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void CollisionBox2D::SetSize(const Vector2& size) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(const Vector2&in)", AS_METHODPR(CollisionBox2D, SetSize, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_size(const Vector2&in)", AS_METHODPR(CollisionBox2D, SetSize, (const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionBox2D::SetSize(float width, float height) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(float, float)", AS_METHODPR(CollisionBox2D, SetSize, (float, float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetTemporary(bool)", AS_METHODPR(CollisionBox2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_temporary(bool)", AS_METHODPR(CollisionBox2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetTrigger(bool)", AS_METHODPR(CollisionBox2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_trigger(bool)", AS_METHODPR(CollisionBox2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionBox2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionBox2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionBox2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionBox2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionBox2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionBox2D", "int WeakRefs() const", AS_METHODPR(CollisionBox2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_weakRefs() const", AS_METHODPR(CollisionBox2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionBox2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionBox2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionBox2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionBox2D, "CollisionBox2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionBox2D
    REGISTER_MANUAL_PART_CollisionBox2D(CollisionBox2D, "CollisionBox2D")
#endif
    RegisterSubclass<CollisionShape2D, CollisionBox2D>(engine, "CollisionShape2D", "CollisionBox2D");
    RegisterSubclass<Component, CollisionBox2D>(engine, "Component", "CollisionBox2D");
    RegisterSubclass<Animatable, CollisionBox2D>(engine, "Animatable", "CollisionBox2D");
    RegisterSubclass<Serializable, CollisionBox2D>(engine, "Serializable", "CollisionBox2D");
    RegisterSubclass<Object, CollisionBox2D>(engine, "Object", "CollisionBox2D");
    RegisterSubclass<RefCounted, CollisionBox2D>(engine, "RefCounted", "CollisionBox2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionChain2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void AllocateNetworkState()", AS_METHODPR(CollisionChain2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ApplyAttributes()", AS_METHODPR(CollisionChain2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionChain2D::CollisionChain2D(Context* context) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_FACTORY, "CollisionChain2D@+ f()", AS_FUNCTION(CollisionChain2D_CollisionChain2D_Context), AS_CALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void CreateFixture()", AS_METHODPR(CollisionChain2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionChain2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionChain2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionChain2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionChain2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionChain2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionChain2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionChain2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionChain2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionChain2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const String& GetCategory() const", AS_METHODPR(CollisionChain2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const String& get_category() const", AS_METHODPR(CollisionChain2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetCategoryBits() const", AS_METHODPR(CollisionChain2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_categoryBits() const", AS_METHODPR(CollisionChain2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionChain2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetDensity() const", AS_METHODPR(CollisionChain2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_density() const", AS_METHODPR(CollisionChain2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionChain2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionChain2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetFriction() const", AS_METHODPR(CollisionChain2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_friction() const", AS_METHODPR(CollisionChain2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionChain2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionChain2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionChain2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionChain2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetGroupIndex() const", AS_METHODPR(CollisionChain2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_groupIndex() const", AS_METHODPR(CollisionChain2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetID() const", AS_METHODPR(CollisionChain2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_id() const", AS_METHODPR(CollisionChain2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetInertia() const", AS_METHODPR(CollisionChain2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_inertia() const", AS_METHODPR(CollisionChain2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionChain2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // bool CollisionChain2D::GetLoop() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetLoop() const", AS_METHODPR(CollisionChain2D, GetLoop, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_loop() const", AS_METHODPR(CollisionChain2D, GetLoop, () const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetMaskBits() const", AS_METHODPR(CollisionChain2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_maskBits() const", AS_METHODPR(CollisionChain2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetMass() const", AS_METHODPR(CollisionChain2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_mass() const", AS_METHODPR(CollisionChain2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionChain2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionChain2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Node@+ GetNode() const", AS_METHODPR(CollisionChain2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Node@+ get_node() const", AS_METHODPR(CollisionChain2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionChain2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_numAttributes() const", AS_METHODPR(CollisionChain2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionChain2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionChain2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionChain2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionChain2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetRestitution() const", AS_METHODPR(CollisionChain2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_restitution() const", AS_METHODPR(CollisionChain2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionChain2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionChain2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "StringHash GetType() const", AS_METHODPR(CollisionChain2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "StringHash get_type() const", AS_METHODPR(CollisionChain2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const String& GetTypeName() const", AS_METHODPR(CollisionChain2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const String& get_typeName() const", AS_METHODPR(CollisionChain2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const Vector2& CollisionChain2D::GetVertex(unsigned index) const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "const Vector2& GetVertex(uint) const", AS_METHODPR(CollisionChain2D, GetVertex, (unsigned) const, const Vector2&), AS_CALL_THISCALL);
    // unsigned CollisionChain2D::GetVertexCount() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetVertexCount() const", AS_METHODPR(CollisionChain2D, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_vertexCount() const", AS_METHODPR(CollisionChain2D, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Vector2>& CollisionChain2D::GetVertices() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "Array<Vector2>@ GetVertices() const", AS_FUNCTION_OBJFIRST(CollisionChain2D_GetVertices_void), AS_CALL_CDECL_OBJFIRST);
    // PODVector<unsigned char> CollisionChain2D::GetVerticesAttr() const | File: ../Urho2D/CollisionChain2D.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionChain2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionChain2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionChain2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsEnabled() const", AS_METHODPR(CollisionChain2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_enabled() const", AS_METHODPR(CollisionChain2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionChain2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionChain2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionChain2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsReplicated() const", AS_METHODPR(CollisionChain2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_replicated() const", AS_METHODPR(CollisionChain2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsTemporary() const", AS_METHODPR(CollisionChain2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_temporary() const", AS_METHODPR(CollisionChain2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsTrigger() const", AS_METHODPR(CollisionChain2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_trigger() const", AS_METHODPR(CollisionChain2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionChain2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionChain2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionChain2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionChain2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionChain2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionChain2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionChain2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnSetEnabled()", AS_METHODPR(CollisionChain2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionChain2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionChain2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionChain2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionChain2D", "int Refs() const", AS_METHODPR(CollisionChain2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_refs() const", AS_METHODPR(CollisionChain2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionChain2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionChain2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ReleaseFixture()", AS_METHODPR(CollisionChain2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionChain2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void Remove()", AS_METHODPR(CollisionChain2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionChain2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionChain2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionChain2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ResetToDefault()", AS_METHODPR(CollisionChain2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionChain2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionChain2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionChain2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionChain2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionChain2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionChain2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionChain2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionChain2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionChain2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionChain2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionChain2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionChain2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionChain2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionChain2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionChain2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionChain2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionChain2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionChain2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_categoryBits(int)", AS_METHODPR(CollisionChain2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetDensity(float)", AS_METHODPR(CollisionChain2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_density(float)", AS_METHODPR(CollisionChain2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetEnabled(bool)", AS_METHODPR(CollisionChain2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_enabled(bool)", AS_METHODPR(CollisionChain2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetFriction(float)", AS_METHODPR(CollisionChain2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_friction(float)", AS_METHODPR(CollisionChain2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionChain2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionChain2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionChain2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_groupIndex(int)", AS_METHODPR(CollisionChain2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionChain2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionChain2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionChain2D::SetLoop(bool loop) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetLoop(bool)", AS_METHODPR(CollisionChain2D, SetLoop, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_loop(bool)", AS_METHODPR(CollisionChain2D, SetLoop, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetMaskBits(int)", AS_METHODPR(CollisionChain2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_maskBits(int)", AS_METHODPR(CollisionChain2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionChain2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionChain2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionChain2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetRestitution(float)", AS_METHODPR(CollisionChain2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_restitution(float)", AS_METHODPR(CollisionChain2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetTemporary(bool)", AS_METHODPR(CollisionChain2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_temporary(bool)", AS_METHODPR(CollisionChain2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetTrigger(bool)", AS_METHODPR(CollisionChain2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_trigger(bool)", AS_METHODPR(CollisionChain2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void CollisionChain2D::SetVertex(unsigned index, const Vector2& vertex) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertex(uint, const Vector2&in)", AS_METHODPR(CollisionChain2D, SetVertex, (unsigned, const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionChain2D::SetVertexCount(unsigned count) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertexCount(uint)", AS_METHODPR(CollisionChain2D, SetVertexCount, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_vertexCount(uint)", AS_METHODPR(CollisionChain2D, SetVertexCount, (unsigned), void), AS_CALL_THISCALL);
    // void CollisionChain2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertices(Array<Vector2>@+)", AS_FUNCTION_OBJFIRST(CollisionChain2D_SetVertices_PODVectorVector2), AS_CALL_CDECL_OBJFIRST);
    // void CollisionChain2D::SetVerticesAttr(const PODVector<unsigned char>& value) | File: ../Urho2D/CollisionChain2D.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionChain2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionChain2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionChain2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionChain2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionChain2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionChain2D", "int WeakRefs() const", AS_METHODPR(CollisionChain2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_weakRefs() const", AS_METHODPR(CollisionChain2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionChain2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionChain2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionChain2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionChain2D, "CollisionChain2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionChain2D
    REGISTER_MANUAL_PART_CollisionChain2D(CollisionChain2D, "CollisionChain2D")
#endif
    RegisterSubclass<CollisionShape2D, CollisionChain2D>(engine, "CollisionShape2D", "CollisionChain2D");
    RegisterSubclass<Component, CollisionChain2D>(engine, "Component", "CollisionChain2D");
    RegisterSubclass<Animatable, CollisionChain2D>(engine, "Animatable", "CollisionChain2D");
    RegisterSubclass<Serializable, CollisionChain2D>(engine, "Serializable", "CollisionChain2D");
    RegisterSubclass<Object, CollisionChain2D>(engine, "Object", "CollisionChain2D");
    RegisterSubclass<RefCounted, CollisionChain2D>(engine, "RefCounted", "CollisionChain2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionCircle2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void AllocateNetworkState()", AS_METHODPR(CollisionCircle2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ApplyAttributes()", AS_METHODPR(CollisionCircle2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionCircle2D::CollisionCircle2D(Context* context) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_FACTORY, "CollisionCircle2D@+ f()", AS_FUNCTION(CollisionCircle2D_CollisionCircle2D_Context), AS_CALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void CreateFixture()", AS_METHODPR(CollisionCircle2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionCircle2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionCircle2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionCircle2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionCircle2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionCircle2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionCircle2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionCircle2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionCircle2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionCircle2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& GetCategory() const", AS_METHODPR(CollisionCircle2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& get_category() const", AS_METHODPR(CollisionCircle2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetCategoryBits() const", AS_METHODPR(CollisionCircle2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_categoryBits() const", AS_METHODPR(CollisionCircle2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // const Vector2& CollisionCircle2D::GetCenter() const | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& GetCenter() const", AS_METHODPR(CollisionCircle2D, GetCenter, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& get_center() const", AS_METHODPR(CollisionCircle2D, GetCenter, () const, const Vector2&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionCircle2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetDensity() const", AS_METHODPR(CollisionCircle2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_density() const", AS_METHODPR(CollisionCircle2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionCircle2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionCircle2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetFriction() const", AS_METHODPR(CollisionCircle2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_friction() const", AS_METHODPR(CollisionCircle2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionCircle2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionCircle2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionCircle2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionCircle2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetGroupIndex() const", AS_METHODPR(CollisionCircle2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_groupIndex() const", AS_METHODPR(CollisionCircle2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetID() const", AS_METHODPR(CollisionCircle2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "uint get_id() const", AS_METHODPR(CollisionCircle2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetInertia() const", AS_METHODPR(CollisionCircle2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_inertia() const", AS_METHODPR(CollisionCircle2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionCircle2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetMaskBits() const", AS_METHODPR(CollisionCircle2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_maskBits() const", AS_METHODPR(CollisionCircle2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetMass() const", AS_METHODPR(CollisionCircle2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_mass() const", AS_METHODPR(CollisionCircle2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionCircle2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionCircle2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Node@+ GetNode() const", AS_METHODPR(CollisionCircle2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Node@+ get_node() const", AS_METHODPR(CollisionCircle2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionCircle2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "uint get_numAttributes() const", AS_METHODPR(CollisionCircle2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionCircle2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionCircle2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionCircle2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionCircle2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionCircle2D::GetRadius() const | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetRadius() const", AS_METHODPR(CollisionCircle2D, GetRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_radius() const", AS_METHODPR(CollisionCircle2D, GetRadius, () const, float), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetRestitution() const", AS_METHODPR(CollisionCircle2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_restitution() const", AS_METHODPR(CollisionCircle2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionCircle2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionCircle2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "StringHash GetType() const", AS_METHODPR(CollisionCircle2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "StringHash get_type() const", AS_METHODPR(CollisionCircle2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& GetTypeName() const", AS_METHODPR(CollisionCircle2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& get_typeName() const", AS_METHODPR(CollisionCircle2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionCircle2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionCircle2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionCircle2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsEnabled() const", AS_METHODPR(CollisionCircle2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_enabled() const", AS_METHODPR(CollisionCircle2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionCircle2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionCircle2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionCircle2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsReplicated() const", AS_METHODPR(CollisionCircle2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_replicated() const", AS_METHODPR(CollisionCircle2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsTemporary() const", AS_METHODPR(CollisionCircle2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_temporary() const", AS_METHODPR(CollisionCircle2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsTrigger() const", AS_METHODPR(CollisionCircle2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_trigger() const", AS_METHODPR(CollisionCircle2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionCircle2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionCircle2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionCircle2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionCircle2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionCircle2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionCircle2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionCircle2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnSetEnabled()", AS_METHODPR(CollisionCircle2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionCircle2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionCircle2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionCircle2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int Refs() const", AS_METHODPR(CollisionCircle2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_refs() const", AS_METHODPR(CollisionCircle2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionCircle2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionCircle2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ReleaseFixture()", AS_METHODPR(CollisionCircle2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionCircle2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void Remove()", AS_METHODPR(CollisionCircle2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionCircle2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionCircle2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionCircle2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ResetToDefault()", AS_METHODPR(CollisionCircle2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionCircle2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionCircle2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionCircle2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionCircle2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionCircle2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionCircle2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionCircle2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionCircle2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionCircle2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionCircle2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionCircle2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionCircle2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionCircle2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionCircle2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionCircle2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionCircle2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionCircle2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionCircle2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_categoryBits(int)", AS_METHODPR(CollisionCircle2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionCircle2D::SetCenter(const Vector2& center) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(const Vector2&in)", AS_METHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_center(const Vector2&in)", AS_METHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionCircle2D::SetCenter(float x, float y) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(float, float)", AS_METHODPR(CollisionCircle2D, SetCenter, (float, float), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetDensity(float)", AS_METHODPR(CollisionCircle2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_density(float)", AS_METHODPR(CollisionCircle2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetEnabled(bool)", AS_METHODPR(CollisionCircle2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_enabled(bool)", AS_METHODPR(CollisionCircle2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetFriction(float)", AS_METHODPR(CollisionCircle2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_friction(float)", AS_METHODPR(CollisionCircle2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionCircle2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionCircle2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionCircle2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_groupIndex(int)", AS_METHODPR(CollisionCircle2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionCircle2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionCircle2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetMaskBits(int)", AS_METHODPR(CollisionCircle2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_maskBits(int)", AS_METHODPR(CollisionCircle2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionCircle2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionCircle2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionCircle2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionCircle2D::SetRadius(float radius) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetRadius(float)", AS_METHODPR(CollisionCircle2D, SetRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_radius(float)", AS_METHODPR(CollisionCircle2D, SetRadius, (float), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetRestitution(float)", AS_METHODPR(CollisionCircle2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_restitution(float)", AS_METHODPR(CollisionCircle2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetTemporary(bool)", AS_METHODPR(CollisionCircle2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_temporary(bool)", AS_METHODPR(CollisionCircle2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetTrigger(bool)", AS_METHODPR(CollisionCircle2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_trigger(bool)", AS_METHODPR(CollisionCircle2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionCircle2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionCircle2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionCircle2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionCircle2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionCircle2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int WeakRefs() const", AS_METHODPR(CollisionCircle2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_weakRefs() const", AS_METHODPR(CollisionCircle2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionCircle2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionCircle2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionCircle2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionCircle2D, "CollisionCircle2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionCircle2D
    REGISTER_MANUAL_PART_CollisionCircle2D(CollisionCircle2D, "CollisionCircle2D")
#endif
    RegisterSubclass<CollisionShape2D, CollisionCircle2D>(engine, "CollisionShape2D", "CollisionCircle2D");
    RegisterSubclass<Component, CollisionCircle2D>(engine, "Component", "CollisionCircle2D");
    RegisterSubclass<Animatable, CollisionCircle2D>(engine, "Animatable", "CollisionCircle2D");
    RegisterSubclass<Serializable, CollisionCircle2D>(engine, "Serializable", "CollisionCircle2D");
    RegisterSubclass<Object, CollisionCircle2D>(engine, "Object", "CollisionCircle2D");
    RegisterSubclass<RefCounted, CollisionCircle2D>(engine, "RefCounted", "CollisionCircle2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionEdge2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void AllocateNetworkState()", AS_METHODPR(CollisionEdge2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ApplyAttributes()", AS_METHODPR(CollisionEdge2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionEdge2D::CollisionEdge2D(Context* context) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_FACTORY, "CollisionEdge2D@+ f()", AS_FUNCTION(CollisionEdge2D_CollisionEdge2D_Context), AS_CALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void CreateFixture()", AS_METHODPR(CollisionEdge2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionEdge2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionEdge2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionEdge2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionEdge2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionEdge2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionEdge2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionEdge2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionEdge2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionEdge2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& GetCategory() const", AS_METHODPR(CollisionEdge2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& get_category() const", AS_METHODPR(CollisionEdge2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetCategoryBits() const", AS_METHODPR(CollisionEdge2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_categoryBits() const", AS_METHODPR(CollisionEdge2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionEdge2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetDensity() const", AS_METHODPR(CollisionEdge2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_density() const", AS_METHODPR(CollisionEdge2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionEdge2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionEdge2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetFriction() const", AS_METHODPR(CollisionEdge2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_friction() const", AS_METHODPR(CollisionEdge2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionEdge2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionEdge2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionEdge2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionEdge2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetGroupIndex() const", AS_METHODPR(CollisionEdge2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_groupIndex() const", AS_METHODPR(CollisionEdge2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetID() const", AS_METHODPR(CollisionEdge2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "uint get_id() const", AS_METHODPR(CollisionEdge2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetInertia() const", AS_METHODPR(CollisionEdge2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_inertia() const", AS_METHODPR(CollisionEdge2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionEdge2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetMaskBits() const", AS_METHODPR(CollisionEdge2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_maskBits() const", AS_METHODPR(CollisionEdge2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetMass() const", AS_METHODPR(CollisionEdge2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_mass() const", AS_METHODPR(CollisionEdge2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionEdge2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionEdge2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Node@+ GetNode() const", AS_METHODPR(CollisionEdge2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Node@+ get_node() const", AS_METHODPR(CollisionEdge2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionEdge2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "uint get_numAttributes() const", AS_METHODPR(CollisionEdge2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionEdge2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionEdge2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionEdge2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionEdge2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetRestitution() const", AS_METHODPR(CollisionEdge2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_restitution() const", AS_METHODPR(CollisionEdge2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionEdge2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionEdge2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "StringHash GetType() const", AS_METHODPR(CollisionEdge2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "StringHash get_type() const", AS_METHODPR(CollisionEdge2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& GetTypeName() const", AS_METHODPR(CollisionEdge2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& get_typeName() const", AS_METHODPR(CollisionEdge2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const Vector2& CollisionEdge2D::GetVertex1() const | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& GetVertex1() const", AS_METHODPR(CollisionEdge2D, GetVertex1, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex1() const", AS_METHODPR(CollisionEdge2D, GetVertex1, () const, const Vector2&), AS_CALL_THISCALL);
    // const Vector2& CollisionEdge2D::GetVertex2() const | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& GetVertex2() const", AS_METHODPR(CollisionEdge2D, GetVertex2, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex2() const", AS_METHODPR(CollisionEdge2D, GetVertex2, () const, const Vector2&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionEdge2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionEdge2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionEdge2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsEnabled() const", AS_METHODPR(CollisionEdge2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_enabled() const", AS_METHODPR(CollisionEdge2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionEdge2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionEdge2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionEdge2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsReplicated() const", AS_METHODPR(CollisionEdge2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_replicated() const", AS_METHODPR(CollisionEdge2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsTemporary() const", AS_METHODPR(CollisionEdge2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_temporary() const", AS_METHODPR(CollisionEdge2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsTrigger() const", AS_METHODPR(CollisionEdge2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_trigger() const", AS_METHODPR(CollisionEdge2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionEdge2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionEdge2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionEdge2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionEdge2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionEdge2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionEdge2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionEdge2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnSetEnabled()", AS_METHODPR(CollisionEdge2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionEdge2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionEdge2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionEdge2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int Refs() const", AS_METHODPR(CollisionEdge2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_refs() const", AS_METHODPR(CollisionEdge2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionEdge2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionEdge2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ReleaseFixture()", AS_METHODPR(CollisionEdge2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionEdge2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void Remove()", AS_METHODPR(CollisionEdge2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionEdge2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionEdge2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionEdge2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ResetToDefault()", AS_METHODPR(CollisionEdge2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionEdge2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionEdge2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionEdge2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionEdge2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionEdge2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionEdge2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionEdge2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionEdge2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionEdge2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionEdge2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionEdge2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionEdge2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionEdge2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionEdge2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionEdge2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionEdge2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionEdge2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionEdge2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_categoryBits(int)", AS_METHODPR(CollisionEdge2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetDensity(float)", AS_METHODPR(CollisionEdge2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_density(float)", AS_METHODPR(CollisionEdge2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetEnabled(bool)", AS_METHODPR(CollisionEdge2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_enabled(bool)", AS_METHODPR(CollisionEdge2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetFriction(float)", AS_METHODPR(CollisionEdge2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_friction(float)", AS_METHODPR(CollisionEdge2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionEdge2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionEdge2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionEdge2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_groupIndex(int)", AS_METHODPR(CollisionEdge2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionEdge2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionEdge2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetMaskBits(int)", AS_METHODPR(CollisionEdge2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_maskBits(int)", AS_METHODPR(CollisionEdge2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionEdge2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionEdge2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionEdge2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetRestitution(float)", AS_METHODPR(CollisionEdge2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_restitution(float)", AS_METHODPR(CollisionEdge2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetTemporary(bool)", AS_METHODPR(CollisionEdge2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_temporary(bool)", AS_METHODPR(CollisionEdge2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetTrigger(bool)", AS_METHODPR(CollisionEdge2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_trigger(bool)", AS_METHODPR(CollisionEdge2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void CollisionEdge2D::SetVertex1(const Vector2& vertex) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertex1(const Vector2&in)", AS_METHODPR(CollisionEdge2D, SetVertex1, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex1(const Vector2&in)", AS_METHODPR(CollisionEdge2D, SetVertex1, (const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionEdge2D::SetVertex2(const Vector2& vertex) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertex2(const Vector2&in)", AS_METHODPR(CollisionEdge2D, SetVertex2, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex2(const Vector2&in)", AS_METHODPR(CollisionEdge2D, SetVertex2, (const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionEdge2D::SetVertices(const Vector2& vertex1, const Vector2& vertex2) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertices(const Vector2&in, const Vector2&in)", AS_METHODPR(CollisionEdge2D, SetVertices, (const Vector2&, const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionEdge2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionEdge2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionEdge2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionEdge2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionEdge2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int WeakRefs() const", AS_METHODPR(CollisionEdge2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_weakRefs() const", AS_METHODPR(CollisionEdge2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionEdge2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionEdge2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionEdge2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionEdge2D, "CollisionEdge2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionEdge2D
    REGISTER_MANUAL_PART_CollisionEdge2D(CollisionEdge2D, "CollisionEdge2D")
#endif
    RegisterSubclass<CollisionShape2D, CollisionEdge2D>(engine, "CollisionShape2D", "CollisionEdge2D");
    RegisterSubclass<Component, CollisionEdge2D>(engine, "Component", "CollisionEdge2D");
    RegisterSubclass<Animatable, CollisionEdge2D>(engine, "Animatable", "CollisionEdge2D");
    RegisterSubclass<Serializable, CollisionEdge2D>(engine, "Serializable", "CollisionEdge2D");
    RegisterSubclass<Object, CollisionEdge2D>(engine, "Object", "CollisionEdge2D");
    RegisterSubclass<RefCounted, CollisionEdge2D>(engine, "RefCounted", "CollisionEdge2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionPolygon2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void AllocateNetworkState()", AS_METHODPR(CollisionPolygon2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ApplyAttributes()", AS_METHODPR(CollisionPolygon2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionPolygon2D::CollisionPolygon2D(Context* context) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_FACTORY, "CollisionPolygon2D@+ f()", AS_FUNCTION(CollisionPolygon2D_CollisionPolygon2D_Context), AS_CALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void CreateFixture()", AS_METHODPR(CollisionPolygon2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionPolygon2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionPolygon2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionPolygon2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionPolygon2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionPolygon2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionPolygon2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionPolygon2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionPolygon2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& GetCategory() const", AS_METHODPR(CollisionPolygon2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& get_category() const", AS_METHODPR(CollisionPolygon2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetCategoryBits() const", AS_METHODPR(CollisionPolygon2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_categoryBits() const", AS_METHODPR(CollisionPolygon2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionPolygon2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetDensity() const", AS_METHODPR(CollisionPolygon2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_density() const", AS_METHODPR(CollisionPolygon2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionPolygon2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionPolygon2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetFriction() const", AS_METHODPR(CollisionPolygon2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_friction() const", AS_METHODPR(CollisionPolygon2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionPolygon2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionPolygon2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionPolygon2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionPolygon2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetGroupIndex() const", AS_METHODPR(CollisionPolygon2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_groupIndex() const", AS_METHODPR(CollisionPolygon2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetID() const", AS_METHODPR(CollisionPolygon2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_id() const", AS_METHODPR(CollisionPolygon2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetInertia() const", AS_METHODPR(CollisionPolygon2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_inertia() const", AS_METHODPR(CollisionPolygon2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionPolygon2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetMaskBits() const", AS_METHODPR(CollisionPolygon2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_maskBits() const", AS_METHODPR(CollisionPolygon2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetMass() const", AS_METHODPR(CollisionPolygon2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_mass() const", AS_METHODPR(CollisionPolygon2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionPolygon2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionPolygon2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Node@+ GetNode() const", AS_METHODPR(CollisionPolygon2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Node@+ get_node() const", AS_METHODPR(CollisionPolygon2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionPolygon2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_numAttributes() const", AS_METHODPR(CollisionPolygon2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionPolygon2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionPolygon2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionPolygon2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionPolygon2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetRestitution() const", AS_METHODPR(CollisionPolygon2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_restitution() const", AS_METHODPR(CollisionPolygon2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionPolygon2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionPolygon2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "StringHash GetType() const", AS_METHODPR(CollisionPolygon2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "StringHash get_type() const", AS_METHODPR(CollisionPolygon2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& GetTypeName() const", AS_METHODPR(CollisionPolygon2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& get_typeName() const", AS_METHODPR(CollisionPolygon2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const Vector2& CollisionPolygon2D::GetVertex(unsigned index) const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Vector2& GetVertex(uint) const", AS_METHODPR(CollisionPolygon2D, GetVertex, (unsigned) const, const Vector2&), AS_CALL_THISCALL);
    // unsigned CollisionPolygon2D::GetVertexCount() const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetVertexCount() const", AS_METHODPR(CollisionPolygon2D, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_vertexCount() const", AS_METHODPR(CollisionPolygon2D, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Vector2>& CollisionPolygon2D::GetVertices() const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Array<Vector2>@ GetVertices() const", AS_FUNCTION_OBJFIRST(CollisionPolygon2D_GetVertices_void), AS_CALL_CDECL_OBJFIRST);
    // PODVector<unsigned char> CollisionPolygon2D::GetVerticesAttr() const | File: ../Urho2D/CollisionPolygon2D.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionPolygon2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionPolygon2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionPolygon2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsEnabled() const", AS_METHODPR(CollisionPolygon2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_enabled() const", AS_METHODPR(CollisionPolygon2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionPolygon2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionPolygon2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionPolygon2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsReplicated() const", AS_METHODPR(CollisionPolygon2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_replicated() const", AS_METHODPR(CollisionPolygon2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsTemporary() const", AS_METHODPR(CollisionPolygon2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_temporary() const", AS_METHODPR(CollisionPolygon2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsTrigger() const", AS_METHODPR(CollisionPolygon2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_trigger() const", AS_METHODPR(CollisionPolygon2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionPolygon2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionPolygon2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionPolygon2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionPolygon2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionPolygon2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionPolygon2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionPolygon2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnSetEnabled()", AS_METHODPR(CollisionPolygon2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionPolygon2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionPolygon2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionPolygon2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int Refs() const", AS_METHODPR(CollisionPolygon2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_refs() const", AS_METHODPR(CollisionPolygon2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionPolygon2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionPolygon2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ReleaseFixture()", AS_METHODPR(CollisionPolygon2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionPolygon2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void Remove()", AS_METHODPR(CollisionPolygon2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionPolygon2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionPolygon2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionPolygon2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ResetToDefault()", AS_METHODPR(CollisionPolygon2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionPolygon2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionPolygon2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionPolygon2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionPolygon2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionPolygon2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionPolygon2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionPolygon2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionPolygon2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionPolygon2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionPolygon2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionPolygon2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionPolygon2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionPolygon2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionPolygon2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionPolygon2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionPolygon2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionPolygon2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionPolygon2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_categoryBits(int)", AS_METHODPR(CollisionPolygon2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetDensity(float)", AS_METHODPR(CollisionPolygon2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_density(float)", AS_METHODPR(CollisionPolygon2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetEnabled(bool)", AS_METHODPR(CollisionPolygon2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_enabled(bool)", AS_METHODPR(CollisionPolygon2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetFriction(float)", AS_METHODPR(CollisionPolygon2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_friction(float)", AS_METHODPR(CollisionPolygon2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionPolygon2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionPolygon2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionPolygon2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_groupIndex(int)", AS_METHODPR(CollisionPolygon2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionPolygon2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionPolygon2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetMaskBits(int)", AS_METHODPR(CollisionPolygon2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_maskBits(int)", AS_METHODPR(CollisionPolygon2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionPolygon2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionPolygon2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionPolygon2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetRestitution(float)", AS_METHODPR(CollisionPolygon2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_restitution(float)", AS_METHODPR(CollisionPolygon2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetTemporary(bool)", AS_METHODPR(CollisionPolygon2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_temporary(bool)", AS_METHODPR(CollisionPolygon2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetTrigger(bool)", AS_METHODPR(CollisionPolygon2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_trigger(bool)", AS_METHODPR(CollisionPolygon2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void CollisionPolygon2D::SetVertex(unsigned index, const Vector2& vertex) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertex(uint, const Vector2&in)", AS_METHODPR(CollisionPolygon2D, SetVertex, (unsigned, const Vector2&), void), AS_CALL_THISCALL);
    // void CollisionPolygon2D::SetVertexCount(unsigned count) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertexCount(uint)", AS_METHODPR(CollisionPolygon2D, SetVertexCount, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_vertexCount(uint)", AS_METHODPR(CollisionPolygon2D, SetVertexCount, (unsigned), void), AS_CALL_THISCALL);
    // void CollisionPolygon2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertices(Array<Vector2>@+)", AS_FUNCTION_OBJFIRST(CollisionPolygon2D_SetVertices_PODVectorVector2), AS_CALL_CDECL_OBJFIRST);
    // void CollisionPolygon2D::SetVerticesAttr(const PODVector<unsigned char>& value) | File: ../Urho2D/CollisionPolygon2D.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionPolygon2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionPolygon2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionPolygon2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionPolygon2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionPolygon2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int WeakRefs() const", AS_METHODPR(CollisionPolygon2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_weakRefs() const", AS_METHODPR(CollisionPolygon2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionPolygon2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionPolygon2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionPolygon2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionPolygon2D, "CollisionPolygon2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionPolygon2D
    REGISTER_MANUAL_PART_CollisionPolygon2D(CollisionPolygon2D, "CollisionPolygon2D")
#endif
    RegisterSubclass<CollisionShape2D, CollisionPolygon2D>(engine, "CollisionShape2D", "CollisionPolygon2D");
    RegisterSubclass<Component, CollisionPolygon2D>(engine, "Component", "CollisionPolygon2D");
    RegisterSubclass<Animatable, CollisionPolygon2D>(engine, "Animatable", "CollisionPolygon2D");
    RegisterSubclass<Serializable, CollisionPolygon2D>(engine, "Serializable", "CollisionPolygon2D");
    RegisterSubclass<Object, CollisionPolygon2D>(engine, "Object", "CollisionPolygon2D");
    RegisterSubclass<RefCounted, CollisionPolygon2D>(engine, "RefCounted", "CollisionPolygon2D");
#endif

#ifdef URHO3D_PHYSICS
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionShape, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void AllocateNetworkState()", AS_METHODPR(CollisionShape, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void CollisionShape::ApplyAttributes() override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void ApplyAttributes()", AS_METHODPR(CollisionShape, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionShape::CollisionShape(Context* context) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_FACTORY, "CollisionShape@+ f()", AS_FUNCTION(CollisionShape_CollisionShape_Context), AS_CALL_CDECL);
    // void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionShape, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionShape, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_animationEnabled() const", AS_METHODPR(CollisionShape, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionShape, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Variant get_attributes(uint) const", AS_METHODPR(CollisionShape, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionShape, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionShape, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionShape, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionShape, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionShape, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionShape, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionShape, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionShape, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetBlockEvents() const", AS_METHODPR(CollisionShape, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const String& GetCategory() const", AS_METHODPR(CollisionShape, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const String& get_category() const", AS_METHODPR(CollisionShape, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // btCollisionShape* CollisionShape::GetCollisionShape() const | File: ../Physics/CollisionShape.h
    // Error: type "btCollisionShape*" can not automatically bind
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionShape, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("CollisionShape", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionShape, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "Object@+ GetEventSender() const", AS_METHODPR(CollisionShape, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // CollisionGeometryData* CollisionShape::GetGeometryData() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "CollisionGeometryData@+ GetGeometryData() const", AS_METHODPR(CollisionShape, GetGeometryData, () const, CollisionGeometryData*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionShape, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionShape, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionShape, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionShape, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetID() const", AS_METHODPR(CollisionShape, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_id() const", AS_METHODPR(CollisionShape, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionShape, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned CollisionShape::GetLodLevel() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetLodLevel() const", AS_METHODPR(CollisionShape, GetLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_lodLevel() const", AS_METHODPR(CollisionShape, GetLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape::GetMargin() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "float GetMargin() const", AS_METHODPR(CollisionShape, GetMargin, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "float get_margin() const", AS_METHODPR(CollisionShape, GetMargin, () const, float), AS_CALL_THISCALL);
    // Model* CollisionShape::GetModel() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "Model@+ GetModel() const", AS_METHODPR(CollisionShape, GetModel, () const, Model*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Model@+ get_model() const", AS_METHODPR(CollisionShape, GetModel, () const, Model*), AS_CALL_THISCALL);
    // ResourceRef CollisionShape::GetModelAttr() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "ResourceRef GetModelAttr() const", AS_METHODPR(CollisionShape, GetModelAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Node@+ GetNode() const", AS_METHODPR(CollisionShape, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Node@+ get_node() const", AS_METHODPR(CollisionShape, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetNumAttributes() const", AS_METHODPR(CollisionShape, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_numAttributes() const", AS_METHODPR(CollisionShape, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionShape, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionShape, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionShape, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionShape, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // PhysicsWorld* CollisionShape::GetPhysicsWorld() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "PhysicsWorld@+ GetPhysicsWorld() const", AS_METHODPR(CollisionShape, GetPhysicsWorld, () const, PhysicsWorld*), AS_CALL_THISCALL);
    // const Vector3& CollisionShape::GetPosition() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& GetPosition() const", AS_METHODPR(CollisionShape, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_position() const", AS_METHODPR(CollisionShape, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& CollisionShape::GetRotation() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& GetRotation() const", AS_METHODPR(CollisionShape, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& get_rotation() const", AS_METHODPR(CollisionShape, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Scene@+ GetScene() const", AS_METHODPR(CollisionShape, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // ShapeType CollisionShape::GetShapeType() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "ShapeType GetShapeType() const", AS_METHODPR(CollisionShape, GetShapeType, () const, ShapeType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ShapeType get_shapeType() const", AS_METHODPR(CollisionShape, GetShapeType, () const, ShapeType), AS_CALL_THISCALL);
    // const Vector3& CollisionShape::GetSize() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& GetSize() const", AS_METHODPR(CollisionShape, GetSize, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_size() const", AS_METHODPR(CollisionShape, GetSize, () const, const Vector3&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionShape, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "StringHash GetType() const", AS_METHODPR(CollisionShape, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "StringHash get_type() const", AS_METHODPR(CollisionShape, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const String& GetTypeName() const", AS_METHODPR(CollisionShape, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const String& get_typeName() const", AS_METHODPR(CollisionShape, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // BoundingBox CollisionShape::GetWorldBoundingBox() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox GetWorldBoundingBox() const", AS_METHODPR(CollisionShape, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox get_worldBoundingBox() const", AS_METHODPR(CollisionShape, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasEventHandlers() const", AS_METHODPR(CollisionShape, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionShape, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionShape, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsEnabled() const", AS_METHODPR(CollisionShape, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_enabled() const", AS_METHODPR(CollisionShape, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsEnabledEffective() const", AS_METHODPR(CollisionShape, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_enabledEffective() const", AS_METHODPR(CollisionShape, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionShape, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsReplicated() const", AS_METHODPR(CollisionShape, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_replicated() const", AS_METHODPR(CollisionShape, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsTemporary() const", AS_METHODPR(CollisionShape, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_temporary() const", AS_METHODPR(CollisionShape, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool Load(Deserializer&)", AS_METHODPR(CollisionShape, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionShape, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionShape, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void MarkNetworkUpdate()", AS_METHODPR(CollisionShape, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void CollisionShape::NotifyRigidBody(bool updateMass=true) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void NotifyRigidBody(bool = true)", AS_METHODPR(CollisionShape, NotifyRigidBody, (bool), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionShape, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionShape, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionShape, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape::OnSetEnabled() override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void OnSetEnabled()", AS_METHODPR(CollisionShape, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionShape, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionShape, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionShape, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape", "int Refs() const", AS_METHODPR(CollisionShape, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "int get_refs() const", AS_METHODPR(CollisionShape, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionShape::RegisterObject(Context* context) | File: ../Physics/CollisionShape.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionShape, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void CollisionShape::ReleaseShape() | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void ReleaseShape()", AS_METHODPR(CollisionShape, ReleaseShape, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void Remove()", AS_METHODPR(CollisionShape, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionShape, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveInstanceDefault()", AS_METHODPR(CollisionShape, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveObjectAnimation()", AS_METHODPR(CollisionShape, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void ResetToDefault()", AS_METHODPR(CollisionShape, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool Save(Serializer&) const", AS_METHODPR(CollisionShape, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionShape, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionShape, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionShape, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SendEvent(StringHash)", AS_METHODPR(CollisionShape, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionShape, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionShape, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_animationEnabled(bool)", AS_METHODPR(CollisionShape, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAnimationTime(float)", AS_METHODPR(CollisionShape, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionShape, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionShape, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionShape, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionShape, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionShape, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionShape, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionShape, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SetBlockEvents(bool)", AS_METHODPR(CollisionShape, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape::SetBox(const Vector3& size, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetBox(const Vector3&in, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetBox, (const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCapsule(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCapsule(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCapsule, (float, float, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCone(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCone(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCone, (float, float, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetConvexHull(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetConvexHull(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetConvexHull, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCustomConvexHull(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomConvexHull(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCustomConvexHull, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCustomGImpactMesh(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomGImpactMesh(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCustomGImpactMesh, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCustomTriangleMesh(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomTriangleMesh(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCustomTriangleMesh, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetCylinder(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCylinder(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetCylinder, (float, float, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void SetEnabled(bool)", AS_METHODPR(CollisionShape, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_enabled(bool)", AS_METHODPR(CollisionShape, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape::SetGImpactMesh(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetGImpactMesh(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetGImpactMesh, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionShape, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionShape, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionShape, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionShape, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape::SetLodLevel(unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetLodLevel(uint)", AS_METHODPR(CollisionShape, SetLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_lodLevel(uint)", AS_METHODPR(CollisionShape, SetLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void CollisionShape::SetMargin(float margin) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetMargin(float)", AS_METHODPR(CollisionShape, SetMargin, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_margin(float)", AS_METHODPR(CollisionShape, SetMargin, (float), void), AS_CALL_THISCALL);
    // void CollisionShape::SetModel(Model* model) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetModel(Model@+)", AS_METHODPR(CollisionShape, SetModel, (Model*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_model(Model@+)", AS_METHODPR(CollisionShape, SetModel, (Model*), void), AS_CALL_THISCALL);
    // void CollisionShape::SetModelAttr(const ResourceRef& value) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetModelAttr(const ResourceRef&in)", AS_METHODPR(CollisionShape, SetModelAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionShape, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionShape, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionShape, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetPosition(const Vector3& position) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetPosition(const Vector3&in)", AS_METHODPR(CollisionShape, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_position(const Vector3&in)", AS_METHODPR(CollisionShape, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetRotation(const Quaternion& rotation) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetRotation(const Quaternion&in)", AS_METHODPR(CollisionShape, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_rotation(const Quaternion&in)", AS_METHODPR(CollisionShape, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetShapeType(ShapeType type) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetShapeType(ShapeType)", AS_METHODPR(CollisionShape, SetShapeType, (ShapeType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_shapeType(ShapeType)", AS_METHODPR(CollisionShape, SetShapeType, (ShapeType), void), AS_CALL_THISCALL);
    // void CollisionShape::SetSize(const Vector3& size) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetSize(const Vector3&in)", AS_METHODPR(CollisionShape, SetSize, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_size(const Vector3&in)", AS_METHODPR(CollisionShape, SetSize, (const Vector3&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetSphere(float diameter, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetSphere(float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetSphere, (float, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetStaticPlane(const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetStaticPlane(const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetStaticPlane, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTemporary(bool)", AS_METHODPR(CollisionShape, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_temporary(bool)", AS_METHODPR(CollisionShape, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape::SetTerrain(unsigned lodLevel=0) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTerrain(uint = 0)", AS_METHODPR(CollisionShape, SetTerrain, (unsigned), void), AS_CALL_THISCALL);
    // void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(CollisionShape, SetTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void CollisionShape::SetTriangleMesh(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTriangleMesh(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", AS_METHODPR(CollisionShape, SetTriangleMesh, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionShape, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionShape_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionShape, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionShape, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionShape, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape", "int WeakRefs() const", AS_METHODPR(CollisionShape, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "int get_weakRefs() const", AS_METHODPR(CollisionShape, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionShape, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionShape, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionShape, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionShape, "CollisionShape")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionShape, "CollisionShape")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionShape, "CollisionShape")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionShape, "CollisionShape")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionShape, "CollisionShape")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionShape
    REGISTER_MANUAL_PART_CollisionShape(CollisionShape, "CollisionShape")
#endif
    RegisterSubclass<Component, CollisionShape>(engine, "Component", "CollisionShape");
    RegisterSubclass<Animatable, CollisionShape>(engine, "Animatable", "CollisionShape");
    RegisterSubclass<Serializable, CollisionShape>(engine, "Serializable", "CollisionShape");
    RegisterSubclass<Object, CollisionShape>(engine, "Object", "CollisionShape");
    RegisterSubclass<RefCounted, CollisionShape>(engine, "RefCounted", "CollisionShape");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionShape2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void AllocateNetworkState()", AS_METHODPR(CollisionShape2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ApplyAttributes()", AS_METHODPR(CollisionShape2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void CreateFixture()", AS_METHODPR(CollisionShape2D, CreateFixture, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CollisionShape2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetAnimationEnabled() const", AS_METHODPR(CollisionShape2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_animationEnabled() const", AS_METHODPR(CollisionShape2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttribute(uint) const", AS_METHODPR(CollisionShape2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Variant get_attributes(uint) const", AS_METHODPR(CollisionShape2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CollisionShape2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CollisionShape2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CollisionShape2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetBlockEvents() const", AS_METHODPR(CollisionShape2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const String& GetCategory() const", AS_METHODPR(CollisionShape2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const String& get_category() const", AS_METHODPR(CollisionShape2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetCategoryBits() const", AS_METHODPR(CollisionShape2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_categoryBits() const", AS_METHODPR(CollisionShape2D, GetCategoryBits, () const, int), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CollisionShape2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetDensity() const", AS_METHODPR(CollisionShape2D, GetDensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_density() const", AS_METHODPR(CollisionShape2D, GetDensity, () const, float), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(CollisionShape2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "Object@+ GetEventSender() const", AS_METHODPR(CollisionShape2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetFriction() const", AS_METHODPR(CollisionShape2D, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_friction() const", AS_METHODPR(CollisionShape2D, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CollisionShape2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CollisionShape2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CollisionShape2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const VariantMap& get_globalVars() const", AS_METHODPR(CollisionShape2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetGroupIndex() const", AS_METHODPR(CollisionShape2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_groupIndex() const", AS_METHODPR(CollisionShape2D, GetGroupIndex, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetID() const", AS_METHODPR(CollisionShape2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "uint get_id() const", AS_METHODPR(CollisionShape2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetInertia() const", AS_METHODPR(CollisionShape2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_inertia() const", AS_METHODPR(CollisionShape2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CollisionShape2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetMaskBits() const", AS_METHODPR(CollisionShape2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_maskBits() const", AS_METHODPR(CollisionShape2D, GetMaskBits, () const, int), AS_CALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetMass() const", AS_METHODPR(CollisionShape2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_mass() const", AS_METHODPR(CollisionShape2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "Vector2 GetMassCenter() const", AS_METHODPR(CollisionShape2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Vector2 get_massCenter() const", AS_METHODPR(CollisionShape2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Node@+ GetNode() const", AS_METHODPR(CollisionShape2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Node@+ get_node() const", AS_METHODPR(CollisionShape2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetNumAttributes() const", AS_METHODPR(CollisionShape2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "uint get_numAttributes() const", AS_METHODPR(CollisionShape2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(CollisionShape2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CollisionShape2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CollisionShape2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CollisionShape2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetRestitution() const", AS_METHODPR(CollisionShape2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_restitution() const", AS_METHODPR(CollisionShape2D, GetRestitution, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Scene@+ GetScene() const", AS_METHODPR(CollisionShape2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CollisionShape2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "StringHash GetType() const", AS_METHODPR(CollisionShape2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "StringHash get_type() const", AS_METHODPR(CollisionShape2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const String& GetTypeName() const", AS_METHODPR(CollisionShape2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const String& get_typeName() const", AS_METHODPR(CollisionShape2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasEventHandlers() const", AS_METHODPR(CollisionShape2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CollisionShape2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CollisionShape2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsEnabled() const", AS_METHODPR(CollisionShape2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_enabled() const", AS_METHODPR(CollisionShape2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsEnabledEffective() const", AS_METHODPR(CollisionShape2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_enabledEffective() const", AS_METHODPR(CollisionShape2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CollisionShape2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsReplicated() const", AS_METHODPR(CollisionShape2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_replicated() const", AS_METHODPR(CollisionShape2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsTemporary() const", AS_METHODPR(CollisionShape2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_temporary() const", AS_METHODPR(CollisionShape2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsTrigger() const", AS_METHODPR(CollisionShape2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_trigger() const", AS_METHODPR(CollisionShape2D, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool Load(Deserializer&)", AS_METHODPR(CollisionShape2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CollisionShape2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CollisionShape2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void MarkNetworkUpdate()", AS_METHODPR(CollisionShape2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CollisionShape2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CollisionShape2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CollisionShape2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnSetEnabled()", AS_METHODPR(CollisionShape2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void PrepareNetworkUpdate()", AS_METHODPR(CollisionShape2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CollisionShape2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CollisionShape2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape2D", "int Refs() const", AS_METHODPR(CollisionShape2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_refs() const", AS_METHODPR(CollisionShape2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void CollisionShape2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionShape2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ReleaseFixture()", AS_METHODPR(CollisionShape2D, ReleaseFixture, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionShape2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void Remove()", AS_METHODPR(CollisionShape2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CollisionShape2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveInstanceDefault()", AS_METHODPR(CollisionShape2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveObjectAnimation()", AS_METHODPR(CollisionShape2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ResetToDefault()", AS_METHODPR(CollisionShape2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool Save(Serializer&) const", AS_METHODPR(CollisionShape2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveDefaultAttributes() const", AS_METHODPR(CollisionShape2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CollisionShape2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(CollisionShape2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SendEvent(StringHash)", AS_METHODPR(CollisionShape2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CollisionShape2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAnimationEnabled(bool)", AS_METHODPR(CollisionShape2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_animationEnabled(bool)", AS_METHODPR(CollisionShape2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAnimationTime(float)", AS_METHODPR(CollisionShape2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CollisionShape2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CollisionShape2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CollisionShape2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CollisionShape2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CollisionShape2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CollisionShape2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CollisionShape2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetBlockEvents(bool)", AS_METHODPR(CollisionShape2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetCategoryBits(int)", AS_METHODPR(CollisionShape2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_categoryBits(int)", AS_METHODPR(CollisionShape2D, SetCategoryBits, (int), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetDensity(float)", AS_METHODPR(CollisionShape2D, SetDensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_density(float)", AS_METHODPR(CollisionShape2D, SetDensity, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetEnabled(bool)", AS_METHODPR(CollisionShape2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_enabled(bool)", AS_METHODPR(CollisionShape2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetFriction(float)", AS_METHODPR(CollisionShape2D, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_friction(float)", AS_METHODPR(CollisionShape2D, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionShape2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CollisionShape2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetGroupIndex(int)", AS_METHODPR(CollisionShape2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_groupIndex(int)", AS_METHODPR(CollisionShape2D, SetGroupIndex, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetInstanceDefault(bool)", AS_METHODPR(CollisionShape2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CollisionShape2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetMaskBits(int)", AS_METHODPR(CollisionShape2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_maskBits(int)", AS_METHODPR(CollisionShape2D, SetMaskBits, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionShape2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CollisionShape2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CollisionShape2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetRestitution(float)", AS_METHODPR(CollisionShape2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_restitution(float)", AS_METHODPR(CollisionShape2D, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetTemporary(bool)", AS_METHODPR(CollisionShape2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_temporary(bool)", AS_METHODPR(CollisionShape2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetTrigger(bool)", AS_METHODPR(CollisionShape2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_trigger(bool)", AS_METHODPR(CollisionShape2D, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(CollisionShape2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CollisionShape2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CollisionShape2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CollisionShape2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CollisionShape2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape2D", "int WeakRefs() const", AS_METHODPR(CollisionShape2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_weakRefs() const", AS_METHODPR(CollisionShape2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CollisionShape2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CollisionShape2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CollisionShape2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CollisionShape2D, "CollisionShape2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CollisionShape2D, "CollisionShape2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CollisionShape2D, "CollisionShape2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CollisionShape2D, "CollisionShape2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionShape2D, "CollisionShape2D")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionShape2D
    REGISTER_MANUAL_PART_CollisionShape2D(CollisionShape2D, "CollisionShape2D")
#endif
    RegisterSubclass<Component, CollisionShape2D>(engine, "Component", "CollisionShape2D");
    RegisterSubclass<Animatable, CollisionShape2D>(engine, "Animatable", "CollisionShape2D");
    RegisterSubclass<Serializable, CollisionShape2D>(engine, "Serializable", "CollisionShape2D");
    RegisterSubclass<Object, CollisionShape2D>(engine, "Object", "CollisionShape2D");
    RegisterSubclass<RefCounted, CollisionShape2D>(engine, "RefCounted", "CollisionShape2D");
#endif

    // float Color::a_ | File: ../Math/Color.h
    engine->RegisterObjectProperty("Color", "float a", offsetof(Color, a_));
    // const ChannelMask Color::ABGR | File: ../Math/Color.h
    // Error: type "const ChannelMask" can not automatically bind
    // const ChannelMask Color::ARGB | File: ../Math/Color.h
    // Error: type "const ChannelMask" can not automatically bind
    // float Color::b_ | File: ../Math/Color.h
    engine->RegisterObjectProperty("Color", "float b", offsetof(Color, b_));
    // const Color Color::BLACK | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color BLACK", (void*)&Color::BLACK);
    engine->SetDefaultNamespace("");
    // const Color Color::BLUE | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color BLUE", (void*)&Color::BLUE);
    engine->SetDefaultNamespace("");
    // const Color Color::CYAN | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color CYAN", (void*)&Color::CYAN);
    engine->SetDefaultNamespace("");
    // float Color::g_ | File: ../Math/Color.h
    engine->RegisterObjectProperty("Color", "float g", offsetof(Color, g_));
    // const Color Color::GRAY | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color GRAY", (void*)&Color::GRAY);
    engine->SetDefaultNamespace("");
    // const Color Color::GREEN | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color GREEN", (void*)&Color::GREEN);
    engine->SetDefaultNamespace("");
    // const Color Color::MAGENTA | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color MAGENTA", (void*)&Color::MAGENTA);
    engine->SetDefaultNamespace("");
    // float Color::r_ | File: ../Math/Color.h
    engine->RegisterObjectProperty("Color", "float r", offsetof(Color, r_));
    // const Color Color::RED | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color RED", (void*)&Color::RED);
    engine->SetDefaultNamespace("");
    // const Color Color::TRANSPARENT_BLACK | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color TRANSPARENT_BLACK", (void*)&Color::TRANSPARENT_BLACK);
    engine->SetDefaultNamespace("");
    // const Color Color::WHITE | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color WHITE", (void*)&Color::WHITE);
    engine->SetDefaultNamespace("");
    // const Color Color::YELLOW | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalProperty("const Color YELLOW", (void*)&Color::YELLOW);
    engine->SetDefaultNamespace("");
    // Color Color::Abs() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color Abs() const", AS_METHODPR(Color, Abs, () const, Color), AS_CALL_THISCALL);
    // float Color::Average() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Average() const", AS_METHODPR(Color, Average, () const, float), AS_CALL_THISCALL);
    // void Color::Bounds(float* min, float* max, bool clipped=false) const | File: ../Math/Color.h
    // Error: type "float*" can not automatically bind
    // float Color::Chroma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Chroma() const", AS_METHODPR(Color, Chroma, () const, float), AS_CALL_THISCALL);
    // void Color::Clip(bool clipAlpha=false) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void Clip(bool = false)", AS_METHODPR(Color, Clip, (bool), void), AS_CALL_THISCALL);
    // Color::Color(const Color& color) noexcept=default | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", AS_FUNCTION_OBJFIRST(Color_Color_Color), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(const Color& color, float a) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in, float)", AS_FUNCTION_OBJFIRST(Color_Color_Color_float), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Color_Color_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b, float a) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Color_Color_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Color::Color(const float* data) noexcept | File: ../Math/Color.h
    // Error: type "const float*" can not automatically bind
    // explicit Color::Color(unsigned color, const ChannelMask& mask=ABGR) | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // explicit Color::Color(const Vector3& color) | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Color_Color_Vector3), AS_CALL_CDECL_OBJFIRST);
    // explicit Color::Color(const Vector4& color) | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Color_Color_Vector4), AS_CALL_CDECL_OBJFIRST);
    // static float Color::ConvertGammaToLinear(float value) | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalFunction("float ConvertGammaToLinear(float)", AS_FUNCTIONPR(Color::ConvertGammaToLinear, (float), float), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static float Color::ConvertLinearToGamma(float value) | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalFunction("float ConvertLinearToGamma(float)", AS_FUNCTIONPR(Color::ConvertLinearToGamma, (float), float), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const float* Color::Data() const | File: ../Math/Color.h
    // Error: type "const float*" can not automatically bind
    // bool Color::Equals(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "bool Equals(const Color&in) const", AS_METHODPR(Color, Equals, (const Color&) const, bool), AS_CALL_THISCALL);
    // void Color::FromHSL(float h, float s, float l, float a=1.0f) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromHSL(float, float, float, float = 1.0f)", AS_METHODPR(Color, FromHSL, (float, float, float, float), void), AS_CALL_THISCALL);
    // void Color::FromHSV(float h, float s, float v, float a=1.0f) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromHSV(float, float, float, float = 1.0f)", AS_METHODPR(Color, FromHSV, (float, float, float, float), void), AS_CALL_THISCALL);
    // void Color::FromUInt(unsigned color) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromUInt(uint)", AS_METHODPR(Color, FromUInt, (unsigned), void), AS_CALL_THISCALL);
    // void Color::FromUIntMask(unsigned color, const ChannelMask& mask) | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // Color Color::GammaToLinear() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color GammaToLinear() const", AS_METHODPR(Color, GammaToLinear, () const, Color), AS_CALL_THISCALL);
    // float Color::Hue() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Hue() const", AS_METHODPR(Color, Hue, () const, float), AS_CALL_THISCALL);
    // void Color::Invert(bool invertAlpha=false) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void Invert(bool = false)", AS_METHODPR(Color, Invert, (bool), void), AS_CALL_THISCALL);
    // Color Color::Lerp(const Color& rhs, float t) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color Lerp(const Color&in, float) const", AS_METHODPR(Color, Lerp, (const Color&, float) const, Color), AS_CALL_THISCALL);
    // float Color::Lightness() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Lightness() const", AS_METHODPR(Color, Lightness, () const, float), AS_CALL_THISCALL);
    // Color Color::LinearToGamma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color LinearToGamma() const", AS_METHODPR(Color, LinearToGamma, () const, Color), AS_CALL_THISCALL);
    // float Color::Luma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Luma() const", AS_METHODPR(Color, Luma, () const, float), AS_CALL_THISCALL);
    // float Color::MaxRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float MaxRGB() const", AS_METHODPR(Color, MaxRGB, () const, float), AS_CALL_THISCALL);
    // float Color::MinRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float MinRGB() const", AS_METHODPR(Color, MinRGB, () const, float), AS_CALL_THISCALL);
    // Color Color::operator*(float rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", AS_METHODPR(Color, operator*, (float) const, Color), AS_CALL_THISCALL);
    // Color Color::operator+(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color&in) const", AS_METHODPR(Color, operator+, (const Color&) const, Color), AS_CALL_THISCALL);
    // Color& Color::operator+=(const Color& rhs) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color& opAddAssign(const Color&in)", AS_METHODPR(Color, operator+=, (const Color&), Color&), AS_CALL_THISCALL);
    // Color Color::operator-() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opNeg() const", AS_METHODPR(Color, operator-, () const, Color), AS_CALL_THISCALL);
    // Color Color::operator-(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opSub(const Color&in) const", AS_METHODPR(Color, operator-, (const Color&) const, Color), AS_CALL_THISCALL);
    // Color& Color::operator=(const Color& rhs) noexcept=default | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color& opAssign(const Color&in)", AS_METHODPR(Color, operator=, (const Color&), Color&), AS_CALL_THISCALL);
    // bool Color::operator==(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color&in) const", AS_METHODPR(Color, operator==, (const Color&) const, bool), AS_CALL_THISCALL);
    // float Color::Range() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Range() const", AS_METHODPR(Color, Range, () const, float), AS_CALL_THISCALL);
    // float Color::SaturationHSL() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SaturationHSL() const", AS_METHODPR(Color, SaturationHSL, () const, float), AS_CALL_THISCALL);
    // float Color::SaturationHSV() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SaturationHSV() const", AS_METHODPR(Color, SaturationHSV, () const, float), AS_CALL_THISCALL);
    // float Color::SumRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SumRGB() const", AS_METHODPR(Color, SumRGB, () const, float), AS_CALL_THISCALL);
    // unsigned Color::ToHash() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToHash() const", AS_METHODPR(Color, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // Vector3 Color::ToHSL() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToHSL() const", AS_METHODPR(Color, ToHSL, () const, Vector3), AS_CALL_THISCALL);
    // Vector3 Color::ToHSV() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToHSV() const", AS_METHODPR(Color, ToHSV, () const, Vector3), AS_CALL_THISCALL);
    // String Color::ToString() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "String ToString() const", AS_METHODPR(Color, ToString, () const, String), AS_CALL_THISCALL);
    // unsigned Color::ToUInt() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToUInt() const", AS_METHODPR(Color, ToUInt, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Color::ToUIntArgb() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToUIntArgb() const", AS_METHODPR(Color, ToUIntArgb, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Color::ToUIntMask(const ChannelMask& mask) const | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // Vector3 Color::ToVector3() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToVector3() const", AS_METHODPR(Color, ToVector3, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 get_rgb() const", AS_METHODPR(Color, ToVector3, () const, Vector3), AS_CALL_THISCALL);
    // Vector4 Color::ToVector4() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector4 ToVector4() const", AS_METHODPR(Color, ToVector4, () const, Vector4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector4 get_rgba() const", AS_METHODPR(Color, ToVector4, () const, Vector4), AS_CALL_THISCALL);
    // float Color::Value() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Value() const", AS_METHODPR(Color, Value, () const, float), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Color
    REGISTER_MANUAL_PART_Color(Color, "Color")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Component, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void AllocateNetworkState()", AS_METHODPR(Component, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void ApplyAttributes()", AS_METHODPR(Component, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Component::Component(Context* context) | File: ../Scene/Component.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_FACTORY, "Component@+ f()", AS_FUNCTION(Component_Component_Context), AS_CALL_CDECL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Component, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool GetAnimationEnabled() const", AS_METHODPR(Component, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_animationEnabled() const", AS_METHODPR(Component, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttribute(uint) const", AS_METHODPR(Component, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Variant get_attributes(uint) const", AS_METHODPR(Component, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttribute(const String&in) const", AS_METHODPR(Component, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Component, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Component, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Component, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Component, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Component, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Component, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Component, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool GetBlockEvents() const", AS_METHODPR(Component, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const String& GetCategory() const", AS_METHODPR(Component, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const String& get_category() const", AS_METHODPR(Component, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Component, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Component", "VariantMap& GetEventDataMap() const", AS_METHODPR(Component, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "Object@+ GetEventSender() const", AS_METHODPR(Component, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Component, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Component, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Component, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const VariantMap& get_globalVars() const", AS_METHODPR(Component, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "uint GetID() const", AS_METHODPR(Component, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "uint get_id() const", AS_METHODPR(Component, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Component, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Node@+ GetNode() const", AS_METHODPR(Component, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Node@+ get_node() const", AS_METHODPR(Component, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "uint GetNumAttributes() const", AS_METHODPR(Component, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "uint get_numAttributes() const", AS_METHODPR(Component, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "uint GetNumNetworkAttributes() const", AS_METHODPR(Component, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Component, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Component, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Component, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Scene@+ GetScene() const", AS_METHODPR(Component, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Component, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "StringHash GetType() const", AS_METHODPR(Component, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "StringHash get_type() const", AS_METHODPR(Component, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const String& GetTypeName() const", AS_METHODPR(Component, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const String& get_typeName() const", AS_METHODPR(Component, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasEventHandlers() const", AS_METHODPR(Component, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Component, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Component, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsEnabled() const", AS_METHODPR(Component, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_enabled() const", AS_METHODPR(Component, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsEnabledEffective() const", AS_METHODPR(Component, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_enabledEffective() const", AS_METHODPR(Component, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Component, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsReplicated() const", AS_METHODPR(Component, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_replicated() const", AS_METHODPR(Component, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool IsTemporary() const", AS_METHODPR(Component, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_temporary() const", AS_METHODPR(Component, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool Load(Deserializer&)", AS_METHODPR(Component, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Component, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Component, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void MarkNetworkUpdate()", AS_METHODPR(Component, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Component, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Component, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Component, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void OnSetEnabled()", AS_METHODPR(Component, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void PrepareNetworkUpdate()", AS_METHODPR(Component, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Component, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Component, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Component", "int Refs() const", AS_METHODPR(Component, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "int get_refs() const", AS_METHODPR(Component, Refs, () const, int), AS_CALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Component, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void Remove()", AS_METHODPR(Component, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Component, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void RemoveInstanceDefault()", AS_METHODPR(Component, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void RemoveObjectAnimation()", AS_METHODPR(Component, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void ResetToDefault()", AS_METHODPR(Component, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool Save(Serializer&) const", AS_METHODPR(Component, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SaveDefaultAttributes() const", AS_METHODPR(Component, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Component, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool SaveXML(XMLElement&) const", AS_METHODPR(Component, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SendEvent(StringHash)", AS_METHODPR(Component, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Component, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAnimationEnabled(bool)", AS_METHODPR(Component, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_animationEnabled(bool)", AS_METHODPR(Component, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAnimationTime(float)", AS_METHODPR(Component, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Component, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Component, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Component, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Component, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Component, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Component, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Component, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SetBlockEvents(bool)", AS_METHODPR(Component, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void SetEnabled(bool)", AS_METHODPR(Component, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_enabled(bool)", AS_METHODPR(Component, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Component, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Component, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetInstanceDefault(bool)", AS_METHODPR(Component, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Component, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Component, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Component, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Component, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetTemporary(bool)", AS_METHODPR(Component, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_temporary(bool)", AS_METHODPR(Component, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromAllEvents()", AS_METHODPR(Component, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Component, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Component, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Component, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Component", "int WeakRefs() const", AS_METHODPR(Component, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Component", "int get_weakRefs() const", AS_METHODPR(Component, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Component, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Component, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Component, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Component, "Component")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Component, "Component")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Component, "Component")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Component, "Component")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Component, "Component")
#endif
    RegisterSubclass<Animatable, Component>(engine, "Animatable", "Component");
    RegisterSubclass<Serializable, Component>(engine, "Serializable", "Component");
    RegisterSubclass<Object, Component>(engine, "Object", "Component");
    RegisterSubclass<RefCounted, Component>(engine, "RefCounted", "Component");

    // void Condition::Set() | File: ../Core/Condition.h
    engine->RegisterObjectMethod("Condition", "void Set()", AS_METHODPR(Condition, Set, (), void), AS_CALL_THISCALL);
    // void Condition::Wait() | File: ../Core/Condition.h
    engine->RegisterObjectMethod("Condition", "void Wait()", AS_METHODPR(Condition, Wait, (), void), AS_CALL_THISCALL);
    // Condition& Condition::operator=(const Condition&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Condition>(engine, "Condition");
#ifdef REGISTER_MANUAL_PART_Condition
    REGISTER_MANUAL_PART_Condition(Condition, "Condition")
#endif

#ifdef URHO3D_NETWORK
    // Controls Connection::controls_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("Connection", "Controls controls", offsetof(Connection, controls_));
    // VariantMap Connection::identity_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("Connection", "VariantMap identity", offsetof(Connection, identity_));
    // unsigned char Connection::timeStamp_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("Connection", "uint8 timeStamp", offsetof(Connection, timeStamp_));
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Connection, AddRef, (), void), AS_CALL_THISCALL);
    // void Connection::Ban() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void Ban()", AS_METHODPR(Connection, Ban, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Connection::ConfigureNetworkSimulator(int latencyMs, float packetLoss) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void ConfigureNetworkSimulator(int, float)", AS_METHODPR(Connection, ConfigureNetworkSimulator, (int, float), void), AS_CALL_THISCALL);
    // Connection::Connection(Context* context, bool isClient, const SLNet::AddressOrGUID& address, SLNet::RakPeerInterface* peer) | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Connection::Disconnect(int waitMSec=0) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void Disconnect(int = 0)", AS_METHODPR(Connection, Disconnect, (int), void), AS_CALL_THISCALL);
    // String Connection::GetAddress() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "String GetAddress() const", AS_METHODPR(Connection, GetAddress, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String get_address() const", AS_METHODPR(Connection, GetAddress, () const, String), AS_CALL_THISCALL);
    // const SLNet::AddressOrGUID& Connection::GetAddressOrGUID() const | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool GetBlockEvents() const", AS_METHODPR(Connection, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // float Connection::GetBytesInPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetBytesInPerSec() const", AS_METHODPR(Connection, GetBytesInPerSec, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_bytesInPerSec() const", AS_METHODPR(Connection, GetBytesInPerSec, () const, float), AS_CALL_THISCALL);
    // float Connection::GetBytesOutPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetBytesOutPerSec() const", AS_METHODPR(Connection, GetBytesOutPerSec, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_bytesOutPerSec() const", AS_METHODPR(Connection, GetBytesOutPerSec, () const, float), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const String& GetCategory() const", AS_METHODPR(Connection, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_category() const", AS_METHODPR(Connection, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const Controls& Connection::GetControls() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Controls& GetControls() const", AS_METHODPR(Connection, GetControls, () const, const Controls&), AS_CALL_THISCALL);
    // const String& Connection::GetDownloadName() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const String& GetDownloadName() const", AS_METHODPR(Connection, GetDownloadName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_downloadName() const", AS_METHODPR(Connection, GetDownloadName, () const, const String&), AS_CALL_THISCALL);
    // float Connection::GetDownloadProgress() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetDownloadProgress() const", AS_METHODPR(Connection, GetDownloadProgress, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_downloadProgress() const", AS_METHODPR(Connection, GetDownloadProgress, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "VariantMap& GetEventDataMap() const", AS_METHODPR(Connection, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "Object@+ GetEventSender() const", AS_METHODPR(Connection, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Connection, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Connection, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Connection, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const VariantMap& get_globalVars() const", AS_METHODPR(Connection, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VariantMap& Connection::GetIdentity() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "VariantMap& GetIdentity()", AS_METHODPR(Connection, GetIdentity, (), VariantMap&), AS_CALL_THISCALL);
    // unsigned Connection::GetLastHeardTime() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint GetLastHeardTime() const", AS_METHODPR(Connection, GetLastHeardTime, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_lastHeardTime() const", AS_METHODPR(Connection, GetLastHeardTime, () const, unsigned), AS_CALL_THISCALL);
    // bool Connection::GetLogStatistics() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool GetLogStatistics() const", AS_METHODPR(Connection, GetLogStatistics, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_logStatistics() const", AS_METHODPR(Connection, GetLogStatistics, () const, bool), AS_CALL_THISCALL);
    // unsigned Connection::GetNumDownloads() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint GetNumDownloads() const", AS_METHODPR(Connection, GetNumDownloads, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_numDownloads() const", AS_METHODPR(Connection, GetNumDownloads, () const, unsigned), AS_CALL_THISCALL);
    // int Connection::GetPacketsInPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "int GetPacketsInPerSec() const", AS_METHODPR(Connection, GetPacketsInPerSec, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_packetsInPerSec() const", AS_METHODPR(Connection, GetPacketsInPerSec, () const, int), AS_CALL_THISCALL);
    // int Connection::GetPacketsOutPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "int GetPacketsOutPerSec() const", AS_METHODPR(Connection, GetPacketsOutPerSec, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_packetsOutPerSec() const", AS_METHODPR(Connection, GetPacketsOutPerSec, () const, int), AS_CALL_THISCALL);
    // PacketType Connection::GetPacketType(bool reliable, bool inOrder) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "PacketType GetPacketType(bool, bool)", AS_METHODPR(Connection, GetPacketType, (bool, bool), PacketType), AS_CALL_THISCALL);
    // unsigned short Connection::GetPort() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint16 GetPort() const", AS_METHODPR(Connection, GetPort, () const, unsigned short), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 get_port() const", AS_METHODPR(Connection, GetPort, () const, unsigned short), AS_CALL_THISCALL);
    // const Vector3& Connection::GetPosition() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Vector3& GetPosition() const", AS_METHODPR(Connection, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Vector3& get_position() const", AS_METHODPR(Connection, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& Connection::GetRotation() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Quaternion& GetRotation() const", AS_METHODPR(Connection, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Quaternion& get_rotation() const", AS_METHODPR(Connection, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // float Connection::GetRoundTripTime() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetRoundTripTime() const", AS_METHODPR(Connection, GetRoundTripTime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_roundTripTime() const", AS_METHODPR(Connection, GetRoundTripTime, () const, float), AS_CALL_THISCALL);
    // Scene* Connection::GetScene() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "Scene@+ GetScene() const", AS_METHODPR(Connection, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "Scene@+ get_scene() const", AS_METHODPR(Connection, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Connection, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned char Connection::GetTimeStamp() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint8 GetTimeStamp() const", AS_METHODPR(Connection, GetTimeStamp, () const, unsigned char), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "StringHash GetType() const", AS_METHODPR(Connection, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "StringHash get_type() const", AS_METHODPR(Connection, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const String& GetTypeName() const", AS_METHODPR(Connection, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_typeName() const", AS_METHODPR(Connection, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasEventHandlers() const", AS_METHODPR(Connection, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Connection, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Connection, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Connection::IsClient() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsClient() const", AS_METHODPR(Connection, IsClient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_client() const", AS_METHODPR(Connection, IsClient, () const, bool), AS_CALL_THISCALL);
    // bool Connection::IsConnected() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsConnected() const", AS_METHODPR(Connection, IsConnected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connected() const", AS_METHODPR(Connection, IsConnected, () const, bool), AS_CALL_THISCALL);
    // bool Connection::IsConnectPending() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsConnectPending() const", AS_METHODPR(Connection, IsConnectPending, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connectPending() const", AS_METHODPR(Connection, IsConnectPending, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Connection, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Connection::IsSceneLoaded() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsSceneLoaded() const", AS_METHODPR(Connection, IsSceneLoaded, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_sceneLoaded() const", AS_METHODPR(Connection, IsSceneLoaded, () const, bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Connection, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // bool Connection::ProcessMessage(int msgID, MemoryBuffer& buffer) | File: ../Network/Connection.h
    // Error: type "MemoryBuffer" can not automatically bind bacause have @nobind mark
    // void Connection::ProcessPendingLatestData() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void ProcessPendingLatestData()", AS_METHODPR(Connection, ProcessPendingLatestData, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Connection", "int Refs() const", AS_METHODPR(Connection, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_refs() const", AS_METHODPR(Connection, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Connection, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Connection::SendAllBuffers() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendAllBuffers()", AS_METHODPR(Connection, SendAllBuffers, (), void), AS_CALL_THISCALL);
    // void Connection::SendBuffer(PacketType type) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendBuffer(PacketType)", AS_METHODPR(Connection, SendBuffer, (PacketType), void), AS_CALL_THISCALL);
    // void Connection::SendClientUpdate() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendClientUpdate()", AS_METHODPR(Connection, SendClientUpdate, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SendEvent(StringHash)", AS_METHODPR(Connection, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Connection, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID=0) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendMessage(int, bool, bool, const VectorBuffer&in, uint = 0)", AS_METHODPR(Connection, SendMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), AS_CALL_THISCALL);
    // void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID=0) | File: ../Network/Connection.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Connection::SendPackages() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendPackages()", AS_METHODPR(Connection, SendPackages, (), void), AS_CALL_THISCALL);
    // void Connection::SendPackageToClient(PackageFile* package) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendPackageToClient(PackageFile@+)", AS_METHODPR(Connection, SendPackageToClient, (PackageFile*), void), AS_CALL_THISCALL);
    // void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(StringHash, bool, const VariantMap&in = VariantMap())", AS_METHODPR(Connection, SendRemoteEvent, (StringHash, bool, const VariantMap&), void), AS_CALL_THISCALL);
    // void Connection::SendRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(Node@+, StringHash, bool, const VariantMap&in = VariantMap())", AS_METHODPR(Connection, SendRemoteEvent, (Node*, StringHash, bool, const VariantMap&), void), AS_CALL_THISCALL);
    // void Connection::SendRemoteEvents() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvents()", AS_METHODPR(Connection, SendRemoteEvents, (), void), AS_CALL_THISCALL);
    // void Connection::SendServerUpdate() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendServerUpdate()", AS_METHODPR(Connection, SendServerUpdate, (), void), AS_CALL_THISCALL);
    // void Connection::SetAddressOrGUID(const SLNet::AddressOrGUID& addr) | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SetBlockEvents(bool)", AS_METHODPR(Connection, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Connection::SetConnectPending(bool connectPending) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetConnectPending(bool)", AS_METHODPR(Connection, SetConnectPending, (bool), void), AS_CALL_THISCALL);
    // void Connection::SetControls(const Controls& newControls) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetControls(const Controls&in)", AS_METHODPR(Connection, SetControls, (const Controls&), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Connection, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Connection, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Connection::SetIdentity(const VariantMap& identity) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetIdentity(const VariantMap&in)", AS_METHODPR(Connection, SetIdentity, (const VariantMap&), void), AS_CALL_THISCALL);
    // void Connection::SetLogStatistics(bool enable) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetLogStatistics(bool)", AS_METHODPR(Connection, SetLogStatistics, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_logStatistics(bool)", AS_METHODPR(Connection, SetLogStatistics, (bool), void), AS_CALL_THISCALL);
    // void Connection::SetPacketSizeLimit(int limit) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetPacketSizeLimit(int)", AS_METHODPR(Connection, SetPacketSizeLimit, (int), void), AS_CALL_THISCALL);
    // void Connection::SetPosition(const Vector3& position) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetPosition(const Vector3&in)", AS_METHODPR(Connection, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_position(const Vector3&in)", AS_METHODPR(Connection, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Connection::SetRotation(const Quaternion& rotation) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetRotation(const Quaternion&in)", AS_METHODPR(Connection, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_rotation(const Quaternion&in)", AS_METHODPR(Connection, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Connection::SetScene(Scene* newScene) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetScene(Scene@+)", AS_METHODPR(Connection, SetScene, (Scene*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_scene(Scene@+)", AS_METHODPR(Connection, SetScene, (Scene*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String Connection::ToString() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "String ToString() const", AS_METHODPR(Connection, ToString, () const, String), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromAllEvents()", AS_METHODPR(Connection, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Connection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Connection, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Connection, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Connection, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Connection", "int WeakRefs() const", AS_METHODPR(Connection, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_weakRefs() const", AS_METHODPR(Connection, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Connection, "Connection")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Connection, "Connection")
#endif
#ifdef REGISTER_MANUAL_PART_Connection
    REGISTER_MANUAL_PART_Connection(Connection, "Connection")
#endif
    RegisterSubclass<Object, Connection>(engine, "Object", "Connection");
    RegisterSubclass<RefCounted, Connection>(engine, "RefCounted", "Connection");
#endif

    // void Console::AddAutoComplete(const String& option) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void AddAutoComplete(const String&in)", AS_METHODPR(Console, AddAutoComplete, (const String&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Console, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit Console::Console(Context* context) | File: ../Engine/Console.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_FACTORY, "Console@+ f()", AS_FUNCTION(Console_Console_Context), AS_CALL_CDECL);
    // void Console::CopySelectedRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void CopySelectedRows() const", AS_METHODPR(Console, CopySelectedRows, () const, void), AS_CALL_THISCALL);
    // BorderImage* Console::GetBackground() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "BorderImage@+ GetBackground() const", AS_METHODPR(Console, GetBackground, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "BorderImage@+ get_background() const", AS_METHODPR(Console, GetBackground, () const, BorderImage*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool GetBlockEvents() const", AS_METHODPR(Console, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const String& GetCategory() const", AS_METHODPR(Console, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_category() const", AS_METHODPR(Console, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Button* Console::GetCloseButton() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "Button@+ GetCloseButton() const", AS_METHODPR(Console, GetCloseButton, () const, Button*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "Button@+ get_closeButton() const", AS_METHODPR(Console, GetCloseButton, () const, Button*), AS_CALL_THISCALL);
    // const String& Console::GetCommandInterpreter() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "const String& GetCommandInterpreter() const", AS_METHODPR(Console, GetCommandInterpreter, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_commandInterpreter() const", AS_METHODPR(Console, GetCommandInterpreter, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* Console::GetDefaultStyle() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "XMLFile@+ GetDefaultStyle() const", AS_METHODPR(Console, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "XMLFile@+ get_defaultStyle() const", AS_METHODPR(Console, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "VariantMap& GetEventDataMap() const", AS_METHODPR(Console, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "Object@+ GetEventSender() const", AS_METHODPR(Console, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool Console::GetFocusOnShow() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool GetFocusOnShow() const", AS_METHODPR(Console, GetFocusOnShow, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_focusOnShow() const", AS_METHODPR(Console, GetFocusOnShow, () const, bool), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Console, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Console, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Console, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const VariantMap& get_globalVars() const", AS_METHODPR(Console, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Console::GetHistoryPosition() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetHistoryPosition() const", AS_METHODPR(Console, GetHistoryPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_historyPosition() const", AS_METHODPR(Console, GetHistoryPosition, () const, unsigned), AS_CALL_THISCALL);
    // const String& Console::GetHistoryRow(unsigned index) const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "const String& GetHistoryRow(uint) const", AS_METHODPR(Console, GetHistoryRow, (unsigned) const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_historyRow(uint) const", AS_METHODPR(Console, GetHistoryRow, (unsigned) const, const String&), AS_CALL_THISCALL);
    // LineEdit* Console::GetLineEdit() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "LineEdit@+ GetLineEdit() const", AS_METHODPR(Console, GetLineEdit, () const, LineEdit*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "LineEdit@+ get_lineEdit() const", AS_METHODPR(Console, GetLineEdit, () const, LineEdit*), AS_CALL_THISCALL);
    // unsigned Console::GetNumBufferedRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumBufferedRows() const", AS_METHODPR(Console, GetNumBufferedRows, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numBufferedRows() const", AS_METHODPR(Console, GetNumBufferedRows, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Console::GetNumHistoryRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumHistoryRows() const", AS_METHODPR(Console, GetNumHistoryRows, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numHistoryRows() const", AS_METHODPR(Console, GetNumHistoryRows, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Console::GetNumRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumRows() const", AS_METHODPR(Console, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numRows() const", AS_METHODPR(Console, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Console, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "StringHash GetType() const", AS_METHODPR(Console, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "StringHash get_type() const", AS_METHODPR(Console, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const String& GetTypeName() const", AS_METHODPR(Console, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_typeName() const", AS_METHODPR(Console, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasEventHandlers() const", AS_METHODPR(Console, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Console, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Console, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Console::IsAutoVisibleOnError() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool IsAutoVisibleOnError() const", AS_METHODPR(Console, IsAutoVisibleOnError, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_autoVisibleOnError() const", AS_METHODPR(Console, IsAutoVisibleOnError, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Console, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Console::IsVisible() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool IsVisible() const", AS_METHODPR(Console, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_visible() const", AS_METHODPR(Console, IsVisible, () const, bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Console, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Console", "int Refs() const", AS_METHODPR(Console, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "int get_refs() const", AS_METHODPR(Console, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Console, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Console::RemoveAutoComplete(const String& option) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void RemoveAutoComplete(const String&in)", AS_METHODPR(Console, RemoveAutoComplete, (const String&), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SendEvent(StringHash)", AS_METHODPR(Console, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Console, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Console::SetAutoVisibleOnError(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetAutoVisibleOnError(bool)", AS_METHODPR(Console, SetAutoVisibleOnError, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_autoVisibleOnError(bool)", AS_METHODPR(Console, SetAutoVisibleOnError, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SetBlockEvents(bool)", AS_METHODPR(Console, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Console::SetCommandInterpreter(const String& interpreter) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetCommandInterpreter(const String&in)", AS_METHODPR(Console, SetCommandInterpreter, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_commandInterpreter(const String&in)", AS_METHODPR(Console, SetCommandInterpreter, (const String&), void), AS_CALL_THISCALL);
    // void Console::SetDefaultStyle(XMLFile* style) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Console, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Console, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void Console::SetFocusOnShow(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetFocusOnShow(bool)", AS_METHODPR(Console, SetFocusOnShow, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_focusOnShow(bool)", AS_METHODPR(Console, SetFocusOnShow, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Console, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Console, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Console::SetNumBufferedRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumBufferedRows(uint)", AS_METHODPR(Console, SetNumBufferedRows, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numBufferedRows(uint)", AS_METHODPR(Console, SetNumBufferedRows, (unsigned), void), AS_CALL_THISCALL);
    // void Console::SetNumHistoryRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumHistoryRows(uint)", AS_METHODPR(Console, SetNumHistoryRows, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numHistoryRows(uint)", AS_METHODPR(Console, SetNumHistoryRows, (unsigned), void), AS_CALL_THISCALL);
    // void Console::SetNumRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumRows(uint)", AS_METHODPR(Console, SetNumRows, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numRows(uint)", AS_METHODPR(Console, SetNumRows, (unsigned), void), AS_CALL_THISCALL);
    // void Console::SetVisible(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetVisible(bool)", AS_METHODPR(Console, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_visible(bool)", AS_METHODPR(Console, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Console::Toggle() | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void Toggle()", AS_METHODPR(Console, Toggle, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromAllEvents()", AS_METHODPR(Console, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Console_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Console, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Console, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Console, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Console::UpdateElements() | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void UpdateElements()", AS_METHODPR(Console, UpdateElements, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Console", "int WeakRefs() const", AS_METHODPR(Console, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Console", "int get_weakRefs() const", AS_METHODPR(Console, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Console, "Console")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Console, "Console")
#endif
#ifdef REGISTER_MANUAL_PART_Console
    REGISTER_MANUAL_PART_Console(Console, "Console")
#endif
    RegisterSubclass<Object, Console>(engine, "Object", "Console");
    RegisterSubclass<RefCounted, Console>(engine, "RefCounted", "Console");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConstantBuffer, AddRef, (), void), AS_CALL_THISCALL);
    // void ConstantBuffer::Apply() | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void Apply()", AS_METHODPR(ConstantBuffer, Apply, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "void ClearDataLost()", AS_METHODPR(ConstantBuffer, ClearDataLost, (), void), AS_CALL_THISCALL);
    // explicit ConstantBuffer::ConstantBuffer(Context* context) | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_FACTORY, "ConstantBuffer@+ f()", AS_FUNCTION(ConstantBuffer_ConstantBuffer_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool GetBlockEvents() const", AS_METHODPR(ConstantBuffer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const String& GetCategory() const", AS_METHODPR(ConstantBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const String& get_category() const", AS_METHODPR(ConstantBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "VariantMap& GetEventDataMap() const", AS_METHODPR(ConstantBuffer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "Object@+ GetEventSender() const", AS_METHODPR(ConstantBuffer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ConstantBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ConstantBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ConstantBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const VariantMap& get_globalVars() const", AS_METHODPR(ConstantBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "uint GetGPUObjectName() const", AS_METHODPR(ConstantBuffer, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "Graphics@+ GetGraphics() const", AS_METHODPR(ConstantBuffer, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // unsigned ConstantBuffer::GetSize() const | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "uint GetSize() const", AS_METHODPR(ConstantBuffer, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ConstantBuffer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "StringHash GetType() const", AS_METHODPR(ConstantBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "StringHash get_type() const", AS_METHODPR(ConstantBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const String& GetTypeName() const", AS_METHODPR(ConstantBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const String& get_typeName() const", AS_METHODPR(ConstantBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasEventHandlers() const", AS_METHODPR(ConstantBuffer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasPendingData() const", AS_METHODPR(ConstantBuffer, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ConstantBuffer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ConstantBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsDataLost() const", AS_METHODPR(ConstantBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "bool get_dataLost() const", AS_METHODPR(ConstantBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool ConstantBuffer::IsDirty() const | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsDirty() const", AS_METHODPR(ConstantBuffer, IsDirty, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ConstantBuffer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnDeviceLost()", AS_METHODPR(ConstantBuffer, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void ConstantBuffer::OnDeviceReset() override | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnDeviceReset()", AS_METHODPR(ConstantBuffer, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ConstantBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstantBuffer", "int Refs() const", AS_METHODPR(ConstantBuffer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "int get_refs() const", AS_METHODPR(ConstantBuffer, Refs, () const, int), AS_CALL_THISCALL);
    // void ConstantBuffer::Release() override | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void Release()", AS_METHODPR(ConstantBuffer, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConstantBuffer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SendEvent(StringHash)", AS_METHODPR(ConstantBuffer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ConstantBuffer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SetBlockEvents(bool)", AS_METHODPR(ConstantBuffer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ConstantBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ConstantBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void ConstantBuffer::SetParameter(unsigned offset, unsigned size, const void* data) | File: ../Graphics/ConstantBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool ConstantBuffer::SetSize(unsigned size) | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool SetSize(uint)", AS_METHODPR(ConstantBuffer, SetSize, (unsigned), bool), AS_CALL_THISCALL);
    // void ConstantBuffer::SetVector3ArrayParameter(unsigned offset, unsigned rows, const void* data) | File: ../Graphics/ConstantBuffer.h
    // Error: type "const void*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromAllEvents()", AS_METHODPR(ConstantBuffer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ConstantBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ConstantBuffer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ConstantBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ConstantBuffer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstantBuffer", "int WeakRefs() const", AS_METHODPR(ConstantBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "int get_weakRefs() const", AS_METHODPR(ConstantBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ConstantBuffer, "ConstantBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConstantBuffer, "ConstantBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(ConstantBuffer, "ConstantBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_ConstantBuffer
    REGISTER_MANUAL_PART_ConstantBuffer(ConstantBuffer, "ConstantBuffer")
#endif
    RegisterSubclass<Object, ConstantBuffer>(engine, "Object", "ConstantBuffer");
    RegisterSubclass<RefCounted, ConstantBuffer>(engine, "RefCounted", "ConstantBuffer");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Context, AddRef, (), void), AS_CALL_THISCALL);
    // Context::Context() | File: ../Core/Context.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_FACTORY, "Context@+ f()", AS_FUNCTION(Context_Context_void), AS_CALL_CDECL);
    // void Context::CopyBaseAttributes(StringHash baseType, StringHash derivedType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void CopyBaseAttributes(StringHash, StringHash)", AS_METHODPR(Context, CopyBaseAttributes, (StringHash, StringHash), void), AS_CALL_THISCALL);
    // template<class T, class U> void Context::CopyBaseAttributes() | File: ../Core/Context.h
    // Not registered because template
    // template<class T> SharedPtr<T> Context::CreateObject() | File: ../Core/Context.h
    // Not registered because template
    // SharedPtr<Object> Context::CreateObject(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ CreateObject(StringHash)", AS_FUNCTION_OBJFIRST(Context_CreateObject_StringHash), AS_CALL_CDECL_OBJFIRST);
    // const HashMap<StringHash, Vector<AttributeInfo>>& Context::GetAllAttributes() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, Vector<AttributeInfo>>&" can not automatically bind
    // AttributeInfo* Context::GetAttribute(StringHash objectType, const char* name) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> AttributeInfo* Context::GetAttribute(const char* name) | File: ../Core/Context.h
    // Not registered because template
    // const Vector<AttributeInfo>* Context::GetAttributes(StringHash type) const | File: ../Core/Context.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // VariantMap& Context::GetEventDataMap() | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "VariantMap& GetEventDataMap()", AS_METHODPR(Context, GetEventDataMap, (), VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Context::GetEventHandler() const | File: ../Core/Context.h
    // Error: type "EventHandler*" can not automatically bind
    // EventReceiverGroup* Context::GetEventReceivers(Object* sender, StringHash eventType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "EventReceiverGroup@+ GetEventReceivers(Object@+, StringHash)", AS_METHODPR(Context, GetEventReceivers, (Object*, StringHash), EventReceiverGroup*), AS_CALL_THISCALL);
    // EventReceiverGroup* Context::GetEventReceivers(StringHash eventType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "EventReceiverGroup@+ GetEventReceivers(StringHash)", AS_METHODPR(Context, GetEventReceivers, (StringHash), EventReceiverGroup*), AS_CALL_THISCALL);
    // Object* Context::GetEventSender() const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ GetEventSender() const", AS_METHODPR(Context, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Context::GetGlobalVar(StringHash key) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Context, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Context::GetGlobalVars() const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Context, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector<AttributeInfo>* Context::GetNetworkAttributes(StringHash type) const | File: ../Core/Context.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const HashMap<String, Vector<StringHash>>& Context::GetObjectCategories() const | File: ../Core/Context.h
    // Error: type "const HashMap<String, Vector<StringHash>>&" can not automatically bind
    // const HashMap<StringHash, SharedPtr<ObjectFactory>>& Context::GetObjectFactories() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, SharedPtr<ObjectFactory>>&" can not automatically bind
    // Object* Context::GetSubsystem(StringHash type) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Context, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    // Not registered because template
    // const HashMap<StringHash, SharedPtr<Object>>& Context::GetSubsystems() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, SharedPtr<Object>>&" can not automatically bind
    // const String& Context::GetTypeName(StringHash objectType) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const String& GetTypeName(StringHash) const", AS_METHODPR(Context, GetTypeName, (StringHash) const, const String&), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Context", "int Refs() const", AS_METHODPR(Context, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Context", "int get_refs() const", AS_METHODPR(Context, Refs, () const, int), AS_CALL_THISCALL);
    // AttributeHandle Context::RegisterAttribute(StringHash objectType, const AttributeInfo& attr) | File: ../Core/Context.h
    // Error: type "AttributeHandle" can not automatically bind bacause have @nobind mark
    // template<class T> AttributeHandle Context::RegisterAttribute(const AttributeInfo& attr) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RegisterFactory(ObjectFactory* factory) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RegisterFactory(ObjectFactory@+)", AS_METHODPR(Context, RegisterFactory, (ObjectFactory*), void), AS_CALL_THISCALL);
    // void Context::RegisterFactory(ObjectFactory* factory, const char* category) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::RegisterFactory() | File: ../Core/Context.h
    // Not registered because template
    // template<class T> void Context::RegisterFactory(const char* category) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RegisterSubsystem(Object* object) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RegisterSubsystem(Object@+)", AS_METHODPR(Context, RegisterSubsystem, (Object*), void), AS_CALL_THISCALL);
    // template<class T> T* Context::RegisterSubsystem() | File: ../Core/Context.h
    // Not registered because template
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Context, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Context::ReleaseSDL() | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void ReleaseSDL()", AS_METHODPR(Context, ReleaseSDL, (), void), AS_CALL_THISCALL);
    // void Context::RemoveAllAttributes(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RemoveAllAttributes(StringHash)", AS_METHODPR(Context, RemoveAllAttributes, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Context::RemoveAllAttributes() | File: ../Core/Context.h
    // Not registered because template
    // void Context::RemoveAttribute(StringHash objectType, const char* name) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::RemoveAttribute(const char* name) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RemoveSubsystem(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RemoveSubsystem(StringHash)", AS_METHODPR(Context, RemoveSubsystem, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Context::RemoveSubsystem() | File: ../Core/Context.h
    // Not registered because template
    // bool Context::RequireSDL(unsigned int sdlFlags) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "bool RequireSDL(uint)", AS_METHODPR(Context, RequireSDL, (unsigned int), bool), AS_CALL_THISCALL);
    // void Context::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Context, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Context::UpdateAttributeDefaultValue(StringHash objectType, const char* name, const Variant& defaultValue) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::UpdateAttributeDefaultValue(const char* name, const Variant& defaultValue) | File: ../Core/Context.h
    // Not registered because template
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Context", "int WeakRefs() const", AS_METHODPR(Context, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Context", "int get_weakRefs() const", AS_METHODPR(Context, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Context, "Context")
#endif
#ifdef REGISTER_MANUAL_PART_Context
    REGISTER_MANUAL_PART_Context(Context, "Context")
#endif
    RegisterSubclass<RefCounted, Context>(engine, "RefCounted", "Context");

    // unsigned Controls::buttons_ | File: ../Input/Controls.h
    engine->RegisterObjectProperty("Controls", "uint buttons", offsetof(Controls, buttons_));
    // VariantMap Controls::extraData_ | File: ../Input/Controls.h
    engine->RegisterObjectProperty("Controls", "VariantMap extraData", offsetof(Controls, extraData_));
    // float Controls::pitch_ | File: ../Input/Controls.h
    engine->RegisterObjectProperty("Controls", "float pitch", offsetof(Controls, pitch_));
    // float Controls::yaw_ | File: ../Input/Controls.h
    engine->RegisterObjectProperty("Controls", "float yaw", offsetof(Controls, yaw_));
    // bool Controls::IsDown(unsigned button) const | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "bool IsDown(uint) const", AS_METHODPR(Controls, IsDown, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Controls::IsPressed(unsigned button, const Controls& previousControls) const | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "bool IsPressed(uint, const Controls&in) const", AS_METHODPR(Controls, IsPressed, (unsigned, const Controls&) const, bool), AS_CALL_THISCALL);
    // void Controls::Reset() | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "void Reset()", AS_METHODPR(Controls, Reset, (), void), AS_CALL_THISCALL);
    // void Controls::Set(unsigned buttons, bool down=true) | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "void Set(uint, bool = true)", AS_METHODPR(Controls, Set, (unsigned, bool), void), AS_CALL_THISCALL);
    // Controls& Controls::operator=(const Controls&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Controls>(engine, "Controls");
#ifdef REGISTER_MANUAL_PART_Controls
    REGISTER_MANUAL_PART_Controls(Controls, "Controls")
#endif

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CrowdAgent, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void AllocateNetworkState()", AS_METHODPR(CrowdAgent, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void CrowdAgent::ApplyAttributes() override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void ApplyAttributes()", AS_METHODPR(CrowdAgent, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CrowdAgent::CrowdAgent(Context* context) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_FACTORY, "CrowdAgent@+ f()", AS_FUNCTION(CrowdAgent_CrowdAgent_Context), AS_CALL_CDECL);
    // void CrowdAgent::DrawDebugGeometry(bool depthTest) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void DrawDebugGeometry(bool)", AS_METHODPR(CrowdAgent, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // void CrowdAgent::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CrowdAgent, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // Vector3 CrowdAgent::GetActualVelocity() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetActualVelocity() const", AS_METHODPR(CrowdAgent, GetActualVelocity, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_actualVelocity() const", AS_METHODPR(CrowdAgent, GetActualVelocity, () const, Vector3), AS_CALL_THISCALL);
    // int CrowdAgent::GetAgentCrowdId() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "int GetAgentCrowdId() const", AS_METHODPR(CrowdAgent, GetAgentCrowdId, () const, int), AS_CALL_THISCALL);
    // CrowdAgentState CrowdAgent::GetAgentState() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentState GetAgentState() const", AS_METHODPR(CrowdAgent, GetAgentState, () const, CrowdAgentState), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentState get_agentState() const", AS_METHODPR(CrowdAgent, GetAgentState, () const, CrowdAgentState), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetAnimationEnabled() const", AS_METHODPR(CrowdAgent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_animationEnabled() const", AS_METHODPR(CrowdAgent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttribute(uint) const", AS_METHODPR(CrowdAgent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Variant get_attributes(uint) const", AS_METHODPR(CrowdAgent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttribute(const String&in) const", AS_METHODPR(CrowdAgent, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CrowdAgent, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CrowdAgent, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CrowdAgent, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CrowdAgent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CrowdAgent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CrowdAgent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CrowdAgent, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetBlockEvents() const", AS_METHODPR(CrowdAgent, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const String& GetCategory() const", AS_METHODPR(CrowdAgent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const String& get_category() const", AS_METHODPR(CrowdAgent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CrowdAgent, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // Vector3 CrowdAgent::GetDesiredVelocity() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetDesiredVelocity() const", AS_METHODPR(CrowdAgent, GetDesiredVelocity, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_desiredVelocity() const", AS_METHODPR(CrowdAgent, GetDesiredVelocity, () const, Vector3), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "VariantMap& GetEventDataMap() const", AS_METHODPR(CrowdAgent, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "Object@+ GetEventSender() const", AS_METHODPR(CrowdAgent, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CrowdAgent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CrowdAgent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CrowdAgent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const VariantMap& get_globalVars() const", AS_METHODPR(CrowdAgent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float CrowdAgent::GetHeight() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetHeight() const", AS_METHODPR(CrowdAgent, GetHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_height() const", AS_METHODPR(CrowdAgent, GetHeight, () const, float), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetID() const", AS_METHODPR(CrowdAgent, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_id() const", AS_METHODPR(CrowdAgent, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CrowdAgent, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float CrowdAgent::GetMaxAccel() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetMaxAccel() const", AS_METHODPR(CrowdAgent, GetMaxAccel, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_maxAccel() const", AS_METHODPR(CrowdAgent, GetMaxAccel, () const, float), AS_CALL_THISCALL);
    // float CrowdAgent::GetMaxSpeed() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetMaxSpeed() const", AS_METHODPR(CrowdAgent, GetMaxSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_maxSpeed() const", AS_METHODPR(CrowdAgent, GetMaxSpeed, () const, float), AS_CALL_THISCALL);
    // NavigationPushiness CrowdAgent::GetNavigationPushiness() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "NavigationPushiness GetNavigationPushiness() const", AS_METHODPR(CrowdAgent, GetNavigationPushiness, () const, NavigationPushiness), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "NavigationPushiness get_navigationPushiness() const", AS_METHODPR(CrowdAgent, GetNavigationPushiness, () const, NavigationPushiness), AS_CALL_THISCALL);
    // NavigationQuality CrowdAgent::GetNavigationQuality() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "NavigationQuality GetNavigationQuality() const", AS_METHODPR(CrowdAgent, GetNavigationQuality, () const, NavigationQuality), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "NavigationQuality get_navigationQuality() const", AS_METHODPR(CrowdAgent, GetNavigationQuality, () const, NavigationQuality), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Node@+ GetNode() const", AS_METHODPR(CrowdAgent, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Node@+ get_node() const", AS_METHODPR(CrowdAgent, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetNumAttributes() const", AS_METHODPR(CrowdAgent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_numAttributes() const", AS_METHODPR(CrowdAgent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetNumNetworkAttributes() const", AS_METHODPR(CrowdAgent, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CrowdAgent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CrowdAgent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CrowdAgent, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned CrowdAgent::GetObstacleAvoidanceType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetObstacleAvoidanceType() const", AS_METHODPR(CrowdAgent, GetObstacleAvoidanceType, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_obstacleAvoidanceType() const", AS_METHODPR(CrowdAgent, GetObstacleAvoidanceType, () const, unsigned), AS_CALL_THISCALL);
    // Vector3 CrowdAgent::GetPosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetPosition() const", AS_METHODPR(CrowdAgent, GetPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_position() const", AS_METHODPR(CrowdAgent, GetPosition, () const, Vector3), AS_CALL_THISCALL);
    // unsigned CrowdAgent::GetQueryFilterType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetQueryFilterType() const", AS_METHODPR(CrowdAgent, GetQueryFilterType, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_queryFilterType() const", AS_METHODPR(CrowdAgent, GetQueryFilterType, () const, unsigned), AS_CALL_THISCALL);
    // float CrowdAgent::GetRadius() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetRadius() const", AS_METHODPR(CrowdAgent, GetRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_radius() const", AS_METHODPR(CrowdAgent, GetRadius, () const, float), AS_CALL_THISCALL);
    // CrowdAgentRequestedTarget CrowdAgent::GetRequestedTargetType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentRequestedTarget GetRequestedTargetType() const", AS_METHODPR(CrowdAgent, GetRequestedTargetType, () const, CrowdAgentRequestedTarget), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentRequestedTarget get_requestedTargetType() const", AS_METHODPR(CrowdAgent, GetRequestedTargetType, () const, CrowdAgentRequestedTarget), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Scene@+ GetScene() const", AS_METHODPR(CrowdAgent, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CrowdAgent, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector3& CrowdAgent::GetTargetPosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& GetTargetPosition() const", AS_METHODPR(CrowdAgent, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& get_targetPosition() const", AS_METHODPR(CrowdAgent, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // CrowdAgentTargetState CrowdAgent::GetTargetState() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentTargetState GetTargetState() const", AS_METHODPR(CrowdAgent, GetTargetState, () const, CrowdAgentTargetState), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentTargetState get_targetState() const", AS_METHODPR(CrowdAgent, GetTargetState, () const, CrowdAgentTargetState), AS_CALL_THISCALL);
    // const Vector3& CrowdAgent::GetTargetVelocity() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& GetTargetVelocity() const", AS_METHODPR(CrowdAgent, GetTargetVelocity, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& get_targetVelocity() const", AS_METHODPR(CrowdAgent, GetTargetVelocity, () const, const Vector3&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "StringHash GetType() const", AS_METHODPR(CrowdAgent, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "StringHash get_type() const", AS_METHODPR(CrowdAgent, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const String& GetTypeName() const", AS_METHODPR(CrowdAgent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const String& get_typeName() const", AS_METHODPR(CrowdAgent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool CrowdAgent::GetUpdateNodePosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetUpdateNodePosition() const", AS_METHODPR(CrowdAgent, GetUpdateNodePosition, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_updateNodePosition() const", AS_METHODPR(CrowdAgent, GetUpdateNodePosition, () const, bool), AS_CALL_THISCALL);
    // bool CrowdAgent::HasArrived() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasArrived() const", AS_METHODPR(CrowdAgent, HasArrived, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_arrived() const", AS_METHODPR(CrowdAgent, HasArrived, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasEventHandlers() const", AS_METHODPR(CrowdAgent, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool CrowdAgent::HasRequestedTarget() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasRequestedTarget() const", AS_METHODPR(CrowdAgent, HasRequestedTarget, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_requestedTarget() const", AS_METHODPR(CrowdAgent, HasRequestedTarget, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CrowdAgent, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CrowdAgent, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsEnabled() const", AS_METHODPR(CrowdAgent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_enabled() const", AS_METHODPR(CrowdAgent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsEnabledEffective() const", AS_METHODPR(CrowdAgent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_enabledEffective() const", AS_METHODPR(CrowdAgent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool CrowdAgent::IsInCrowd() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsInCrowd() const", AS_METHODPR(CrowdAgent, IsInCrowd, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_inCrowd() const", AS_METHODPR(CrowdAgent, IsInCrowd, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CrowdAgent, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsReplicated() const", AS_METHODPR(CrowdAgent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_replicated() const", AS_METHODPR(CrowdAgent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsTemporary() const", AS_METHODPR(CrowdAgent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_temporary() const", AS_METHODPR(CrowdAgent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool Load(Deserializer&)", AS_METHODPR(CrowdAgent, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CrowdAgent, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CrowdAgent, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void MarkNetworkUpdate()", AS_METHODPR(CrowdAgent, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CrowdAgent, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CrowdAgent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CrowdAgent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void CrowdAgent::OnSetEnabled() override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnSetEnabled()", AS_METHODPR(CrowdAgent, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void PrepareNetworkUpdate()", AS_METHODPR(CrowdAgent, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CrowdAgent, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CrowdAgent, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdAgent", "int Refs() const", AS_METHODPR(CrowdAgent, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "int get_refs() const", AS_METHODPR(CrowdAgent, Refs, () const, int), AS_CALL_THISCALL);
    // static void CrowdAgent::RegisterObject(Context* context) | File: ../Navigation/CrowdAgent.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CrowdAgent, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void Remove()", AS_METHODPR(CrowdAgent, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CrowdAgent, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveInstanceDefault()", AS_METHODPR(CrowdAgent, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveObjectAnimation()", AS_METHODPR(CrowdAgent, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void CrowdAgent::ResetTarget() | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void ResetTarget()", AS_METHODPR(CrowdAgent, ResetTarget, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void ResetToDefault()", AS_METHODPR(CrowdAgent, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool Save(Serializer&) const", AS_METHODPR(CrowdAgent, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveDefaultAttributes() const", AS_METHODPR(CrowdAgent, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CrowdAgent, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveXML(XMLElement&) const", AS_METHODPR(CrowdAgent, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SendEvent(StringHash)", AS_METHODPR(CrowdAgent, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CrowdAgent, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAnimationEnabled(bool)", AS_METHODPR(CrowdAgent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_animationEnabled(bool)", AS_METHODPR(CrowdAgent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAnimationTime(float)", AS_METHODPR(CrowdAgent, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CrowdAgent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CrowdAgent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CrowdAgent, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CrowdAgent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CrowdAgent, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CrowdAgent, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CrowdAgent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetBlockEvents(bool)", AS_METHODPR(CrowdAgent, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetEnabled(bool)", AS_METHODPR(CrowdAgent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_enabled(bool)", AS_METHODPR(CrowdAgent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CrowdAgent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CrowdAgent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetHeight(float height) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetHeight(float)", AS_METHODPR(CrowdAgent, SetHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_height(float)", AS_METHODPR(CrowdAgent, SetHeight, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetInstanceDefault(bool)", AS_METHODPR(CrowdAgent, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CrowdAgent, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetMaxAccel(float maxAccel) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetMaxAccel(float)", AS_METHODPR(CrowdAgent, SetMaxAccel, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_maxAccel(float)", AS_METHODPR(CrowdAgent, SetMaxAccel, (float), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetMaxSpeed(float maxSpeed) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetMaxSpeed(float)", AS_METHODPR(CrowdAgent, SetMaxSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_maxSpeed(float)", AS_METHODPR(CrowdAgent, SetMaxSpeed, (float), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetNavigationPushiness(NavigationPushiness val) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetNavigationPushiness(NavigationPushiness)", AS_METHODPR(CrowdAgent, SetNavigationPushiness, (NavigationPushiness), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_navigationPushiness(NavigationPushiness)", AS_METHODPR(CrowdAgent, SetNavigationPushiness, (NavigationPushiness), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetNavigationQuality(NavigationQuality val) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetNavigationQuality(NavigationQuality)", AS_METHODPR(CrowdAgent, SetNavigationQuality, (NavigationQuality), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_navigationQuality(NavigationQuality)", AS_METHODPR(CrowdAgent, SetNavigationQuality, (NavigationQuality), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CrowdAgent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CrowdAgent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CrowdAgent, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetObstacleAvoidanceType(unsigned obstacleAvoidanceType) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObstacleAvoidanceType(uint)", AS_METHODPR(CrowdAgent, SetObstacleAvoidanceType, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_obstacleAvoidanceType(uint)", AS_METHODPR(CrowdAgent, SetObstacleAvoidanceType, (unsigned), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetQueryFilterType(unsigned queryFilterType) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetQueryFilterType(uint)", AS_METHODPR(CrowdAgent, SetQueryFilterType, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_queryFilterType(uint)", AS_METHODPR(CrowdAgent, SetQueryFilterType, (unsigned), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetRadius(float radius) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetRadius(float)", AS_METHODPR(CrowdAgent, SetRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_radius(float)", AS_METHODPR(CrowdAgent, SetRadius, (float), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetTargetPosition(const Vector3& position) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTargetPosition(const Vector3&in)", AS_METHODPR(CrowdAgent, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_targetPosition(const Vector3&in)", AS_METHODPR(CrowdAgent, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetTargetVelocity(const Vector3& velocity) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTargetVelocity(const Vector3&in)", AS_METHODPR(CrowdAgent, SetTargetVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_targetVelocity(const Vector3&in)", AS_METHODPR(CrowdAgent, SetTargetVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTemporary(bool)", AS_METHODPR(CrowdAgent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_temporary(bool)", AS_METHODPR(CrowdAgent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void CrowdAgent::SetUpdateNodePosition(bool unodepos) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetUpdateNodePosition(bool)", AS_METHODPR(CrowdAgent, SetUpdateNodePosition, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_updateNodePosition(bool)", AS_METHODPR(CrowdAgent, SetUpdateNodePosition, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromAllEvents()", AS_METHODPR(CrowdAgent, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CrowdAgent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CrowdAgent, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CrowdAgent, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CrowdAgent, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdAgent", "int WeakRefs() const", AS_METHODPR(CrowdAgent, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "int get_weakRefs() const", AS_METHODPR(CrowdAgent, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CrowdAgent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CrowdAgent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CrowdAgent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CrowdAgent, "CrowdAgent")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CrowdAgent, "CrowdAgent")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CrowdAgent, "CrowdAgent")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CrowdAgent, "CrowdAgent")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CrowdAgent, "CrowdAgent")
#endif
#ifdef REGISTER_MANUAL_PART_CrowdAgent
    REGISTER_MANUAL_PART_CrowdAgent(CrowdAgent, "CrowdAgent")
#endif
    RegisterSubclass<Component, CrowdAgent>(engine, "Component", "CrowdAgent");
    RegisterSubclass<Animatable, CrowdAgent>(engine, "Animatable", "CrowdAgent");
    RegisterSubclass<Serializable, CrowdAgent>(engine, "Serializable", "CrowdAgent");
    RegisterSubclass<Object, CrowdAgent>(engine, "Object", "CrowdAgent");
    RegisterSubclass<RefCounted, CrowdAgent>(engine, "RefCounted", "CrowdAgent");
#endif

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CrowdManager, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void AllocateNetworkState()", AS_METHODPR(CrowdManager, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void CrowdManager::ApplyAttributes() override | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void ApplyAttributes()", AS_METHODPR(CrowdManager, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CrowdManager::CrowdManager(Context* context) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_FACTORY, "CrowdManager@+ f()", AS_FUNCTION(CrowdManager_CrowdManager_Context), AS_CALL_CDECL);
    // void CrowdManager::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CrowdManager, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void CrowdManager::DrawDebugGeometry(bool depthTest) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void DrawDebugGeometry(bool)", AS_METHODPR(CrowdManager, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // void CrowdManager::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, int queryFilterType) | File: ../Navigation/CrowdManager.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // PODVector<CrowdAgent*> CrowdManager::GetAgents(Node* node=nullptr, bool inCrowdFilter=true) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "Array<CrowdAgent@>@ GetAgents(Node@+ = null, bool = true) const", AS_FUNCTION_OBJFIRST(CrowdManager_GetAgents_Node_bool), AS_CALL_CDECL_OBJFIRST);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetAnimationEnabled() const", AS_METHODPR(CrowdManager, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_animationEnabled() const", AS_METHODPR(CrowdManager, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float CrowdManager::GetAreaCost(unsigned queryFilterType, unsigned areaID) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAreaCost(uint, uint) const", AS_METHODPR(CrowdManager, GetAreaCost, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttribute(uint) const", AS_METHODPR(CrowdManager, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Variant get_attributes(uint) const", AS_METHODPR(CrowdManager, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttribute(const String&in) const", AS_METHODPR(CrowdManager, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CrowdManager, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CrowdManager, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CrowdManager, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CrowdManager, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CrowdManager, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CrowdManager, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CrowdManager, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetBlockEvents() const", AS_METHODPR(CrowdManager, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const String& GetCategory() const", AS_METHODPR(CrowdManager, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const String& get_category() const", AS_METHODPR(CrowdManager, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CrowdManager, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float CrowdManager::GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, Vector3* hitPos=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "Vector3*" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "VariantMap& GetEventDataMap() const", AS_METHODPR(CrowdManager, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "Object@+ GetEventSender() const", AS_METHODPR(CrowdManager, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // unsigned short CrowdManager::GetExcludeFlags(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint16 GetExcludeFlags(uint) const", AS_METHODPR(CrowdManager, GetExcludeFlags, (unsigned) const, unsigned short), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CrowdManager, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CrowdManager, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CrowdManager, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const VariantMap& get_globalVars() const", AS_METHODPR(CrowdManager, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetID() const", AS_METHODPR(CrowdManager, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_id() const", AS_METHODPR(CrowdManager, GetID, () const, unsigned), AS_CALL_THISCALL);
    // unsigned short CrowdManager::GetIncludeFlags(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint16 GetIncludeFlags(uint) const", AS_METHODPR(CrowdManager, GetIncludeFlags, (unsigned) const, unsigned short), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CrowdManager, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float CrowdManager::GetMaxAgentRadius() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "float GetMaxAgentRadius() const", AS_METHODPR(CrowdManager, GetMaxAgentRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "float get_maxAgentRadius() const", AS_METHODPR(CrowdManager, GetMaxAgentRadius, () const, float), AS_CALL_THISCALL);
    // unsigned CrowdManager::GetMaxAgents() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetMaxAgents() const", AS_METHODPR(CrowdManager, GetMaxAgents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_maxAgents() const", AS_METHODPR(CrowdManager, GetMaxAgents, () const, unsigned), AS_CALL_THISCALL);
    // NavigationMesh* CrowdManager::GetNavigationMesh() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "NavigationMesh@+ GetNavigationMesh() const", AS_METHODPR(CrowdManager, GetNavigationMesh, () const, NavigationMesh*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "NavigationMesh@+ get_navMesh() const", AS_METHODPR(CrowdManager, GetNavigationMesh, () const, NavigationMesh*), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Node@+ GetNode() const", AS_METHODPR(CrowdManager, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Node@+ get_node() const", AS_METHODPR(CrowdManager, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned CrowdManager::GetNumAreas(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumAreas(uint) const", AS_METHODPR(CrowdManager, GetNumAreas, (unsigned) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numAreas(uint) const", AS_METHODPR(CrowdManager, GetNumAreas, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumAttributes() const", AS_METHODPR(CrowdManager, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numAttributes() const", AS_METHODPR(CrowdManager, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumNetworkAttributes() const", AS_METHODPR(CrowdManager, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned CrowdManager::GetNumObstacleAvoidanceTypes() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumObstacleAvoidanceTypes() const", AS_METHODPR(CrowdManager, GetNumObstacleAvoidanceTypes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numObstacleAvoidanceTypes() const", AS_METHODPR(CrowdManager, GetNumObstacleAvoidanceTypes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned CrowdManager::GetNumQueryFilterTypes() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumQueryFilterTypes() const", AS_METHODPR(CrowdManager, GetNumQueryFilterTypes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numQueryFilterTypes() const", AS_METHODPR(CrowdManager, GetNumQueryFilterTypes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CrowdManager, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CrowdManager, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CrowdManager, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const CrowdObstacleAvoidanceParams& CrowdManager::GetObstacleAvoidanceParams(unsigned obstacleAvoidanceType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "const CrowdObstacleAvoidanceParams& GetObstacleAvoidanceParams(uint) const", AS_METHODPR(CrowdManager, GetObstacleAvoidanceParams, (unsigned) const, const CrowdObstacleAvoidanceParams&), AS_CALL_THISCALL);
    // VariantVector CrowdManager::GetObstacleAvoidanceTypesAttr() const | File: ../Navigation/CrowdManager.h
    // Error: type "VariantVector" can not automatically bind
    // VariantVector CrowdManager::GetQueryFilterTypesAttr() const | File: ../Navigation/CrowdManager.h
    // Error: type "VariantVector" can not automatically bind
    // Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef* randomRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Scene@+ GetScene() const", AS_METHODPR(CrowdManager, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CrowdManager, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "StringHash GetType() const", AS_METHODPR(CrowdManager, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "StringHash get_type() const", AS_METHODPR(CrowdManager, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const String& GetTypeName() const", AS_METHODPR(CrowdManager, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const String& get_typeName() const", AS_METHODPR(CrowdManager, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasEventHandlers() const", AS_METHODPR(CrowdManager, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CrowdManager, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CrowdManager, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsEnabled() const", AS_METHODPR(CrowdManager, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_enabled() const", AS_METHODPR(CrowdManager, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsEnabledEffective() const", AS_METHODPR(CrowdManager, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_enabledEffective() const", AS_METHODPR(CrowdManager, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CrowdManager, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsReplicated() const", AS_METHODPR(CrowdManager, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_replicated() const", AS_METHODPR(CrowdManager, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsTemporary() const", AS_METHODPR(CrowdManager, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_temporary() const", AS_METHODPR(CrowdManager, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool Load(Deserializer&)", AS_METHODPR(CrowdManager, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CrowdManager, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CrowdManager, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void MarkNetworkUpdate()", AS_METHODPR(CrowdManager, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 CrowdManager::MoveAlongSurface(const Vector3& start, const Vector3& end, int queryFilterType, int maxVisited=3) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "Vector3 MoveAlongSurface(const Vector3&in, const Vector3&in, int, int = 3)", AS_METHODPR(CrowdManager, MoveAlongSurface, (const Vector3&, const Vector3&, int, int), Vector3), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CrowdManager, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CrowdManager, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CrowdManager, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void OnSetEnabled()", AS_METHODPR(CrowdManager, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void PrepareNetworkUpdate()", AS_METHODPR(CrowdManager, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "Vector3*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CrowdManager, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CrowdManager, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdManager", "int Refs() const", AS_METHODPR(CrowdManager, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "int get_refs() const", AS_METHODPR(CrowdManager, Refs, () const, int), AS_CALL_THISCALL);
    // static void CrowdManager::RegisterObject(Context* context) | File: ../Navigation/CrowdManager.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CrowdManager, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void Remove()", AS_METHODPR(CrowdManager, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CrowdManager, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveInstanceDefault()", AS_METHODPR(CrowdManager, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveObjectAnimation()", AS_METHODPR(CrowdManager, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void CrowdManager::ResetCrowdTarget(Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void ResetCrowdTarget(Node@+ = null)", AS_METHODPR(CrowdManager, ResetCrowdTarget, (Node*), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void ResetToDefault()", AS_METHODPR(CrowdManager, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool Save(Serializer&) const", AS_METHODPR(CrowdManager, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveDefaultAttributes() const", AS_METHODPR(CrowdManager, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CrowdManager, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveXML(XMLElement&) const", AS_METHODPR(CrowdManager, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SendEvent(StringHash)", AS_METHODPR(CrowdManager, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CrowdManager, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAnimationEnabled(bool)", AS_METHODPR(CrowdManager, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_animationEnabled(bool)", AS_METHODPR(CrowdManager, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAnimationTime(float)", AS_METHODPR(CrowdManager, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void CrowdManager::SetAreaCost(unsigned queryFilterType, unsigned areaID, float cost) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAreaCost(uint, uint, float)", AS_METHODPR(CrowdManager, SetAreaCost, (unsigned, unsigned, float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CrowdManager, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CrowdManager, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CrowdManager, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CrowdManager, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CrowdManager, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CrowdManager, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CrowdManager, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SetBlockEvents(bool)", AS_METHODPR(CrowdManager, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void CrowdManager::SetCrowdTarget(const Vector3& position, Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetCrowdTarget(const Vector3&in, Node@+ = null)", AS_METHODPR(CrowdManager, SetCrowdTarget, (const Vector3&, Node*), void), AS_CALL_THISCALL);
    // void CrowdManager::SetCrowdVelocity(const Vector3& velocity, Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetCrowdVelocity(const Vector3&in, Node@+ = null)", AS_METHODPR(CrowdManager, SetCrowdVelocity, (const Vector3&, Node*), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void SetEnabled(bool)", AS_METHODPR(CrowdManager, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_enabled(bool)", AS_METHODPR(CrowdManager, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CrowdManager::SetExcludeFlags(unsigned queryFilterType, unsigned short flags) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetExcludeFlags(uint, uint16)", AS_METHODPR(CrowdManager, SetExcludeFlags, (unsigned, unsigned short), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CrowdManager, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CrowdManager, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void CrowdManager::SetIncludeFlags(unsigned queryFilterType, unsigned short flags) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetIncludeFlags(uint, uint16)", AS_METHODPR(CrowdManager, SetIncludeFlags, (unsigned, unsigned short), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetInstanceDefault(bool)", AS_METHODPR(CrowdManager, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CrowdManager, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void CrowdManager::SetMaxAgentRadius(float maxAgentRadius) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetMaxAgentRadius(float)", AS_METHODPR(CrowdManager, SetMaxAgentRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_maxAgentRadius(float)", AS_METHODPR(CrowdManager, SetMaxAgentRadius, (float), void), AS_CALL_THISCALL);
    // void CrowdManager::SetMaxAgents(unsigned maxAgents) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetMaxAgents(uint)", AS_METHODPR(CrowdManager, SetMaxAgents, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_maxAgents(uint)", AS_METHODPR(CrowdManager, SetMaxAgents, (unsigned), void), AS_CALL_THISCALL);
    // void CrowdManager::SetNavigationMesh(NavigationMesh* navMesh) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetNavigationMesh(NavigationMesh@+)", AS_METHODPR(CrowdManager, SetNavigationMesh, (NavigationMesh*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_navMesh(NavigationMesh@+)", AS_METHODPR(CrowdManager, SetNavigationMesh, (NavigationMesh*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CrowdManager, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CrowdManager, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CrowdManager, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void CrowdManager::SetObstacleAvoidanceParams(unsigned obstacleAvoidanceType, const CrowdObstacleAvoidanceParams& params) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObstacleAvoidanceParams(uint, const CrowdObstacleAvoidanceParams&in)", AS_METHODPR(CrowdManager, SetObstacleAvoidanceParams, (unsigned, const CrowdObstacleAvoidanceParams&), void), AS_CALL_THISCALL);
    // void CrowdManager::SetObstacleAvoidanceTypesAttr(const VariantVector& value) | File: ../Navigation/CrowdManager.h
    // Error: type "const VariantVector&" can not automatically bind
    // void CrowdManager::SetQueryFilterTypesAttr(const VariantVector& value) | File: ../Navigation/CrowdManager.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetTemporary(bool)", AS_METHODPR(CrowdManager, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_temporary(bool)", AS_METHODPR(CrowdManager, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromAllEvents()", AS_METHODPR(CrowdManager, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CrowdManager_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CrowdManager, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CrowdManager, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CrowdManager, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdManager", "int WeakRefs() const", AS_METHODPR(CrowdManager, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "int get_weakRefs() const", AS_METHODPR(CrowdManager, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CrowdManager, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CrowdManager, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CrowdManager, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CrowdManager, "CrowdManager")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CrowdManager, "CrowdManager")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CrowdManager, "CrowdManager")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CrowdManager, "CrowdManager")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CrowdManager, "CrowdManager")
#endif
#ifdef REGISTER_MANUAL_PART_CrowdManager
    REGISTER_MANUAL_PART_CrowdManager(CrowdManager, "CrowdManager")
#endif
    RegisterSubclass<Component, CrowdManager>(engine, "Component", "CrowdManager");
    RegisterSubclass<Animatable, CrowdManager>(engine, "Animatable", "CrowdManager");
    RegisterSubclass<Serializable, CrowdManager>(engine, "Serializable", "CrowdManager");
    RegisterSubclass<Object, CrowdManager>(engine, "Object", "CrowdManager");
    RegisterSubclass<RefCounted, CrowdManager>(engine, "RefCounted", "CrowdManager");
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddChild(UIElement@+)", AS_METHODPR(Cursor, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Cursor, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTag(const String&in)", AS_METHODPR(Cursor, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Cursor, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Cursor_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AdjustScissor(IntRect&)", AS_METHODPR(Cursor, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void AllocateNetworkState()", AS_METHODPR(Cursor, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void ApplyAttributes()", AS_METHODPR(Cursor, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void Cursor::ApplyOSCursorShape() | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void ApplyOSCursorShape()", AS_METHODPR(Cursor, ApplyOSCursorShape, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void BringToFront()", AS_METHODPR(Cursor, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Cursor, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // explicit Cursor::Cursor(Context* context) | File: ../UI/Cursor.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_FACTORY, "Cursor@+ f()", AS_FUNCTION(Cursor_Cursor_Context), AS_CALL_CDECL);
    // void Cursor::DefineShape(const String& shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void DefineShape(const String&in, Image@+, const IntRect&in, const IntVector2&in)", AS_METHODPR(Cursor, DefineShape, (const String&, Image*, const IntRect&, const IntVector2&), void), AS_CALL_THISCALL);
    // void Cursor::DefineShape(CursorShape shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void DefineShape(CursorShape, Image@+, const IntRect&in, const IntVector2&in)", AS_METHODPR(Cursor, DefineShape, (CursorShape, Image*, const IntRect&, const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void DisableLayoutUpdate()", AS_METHODPR(Cursor, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Cursor, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void EnableLayoutUpdate()", AS_METHODPR(Cursor, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Cursor, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint FindChild(UIElement@+) const", AS_METHODPR(Cursor, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool GetAnimationEnabled() const", AS_METHODPR(Cursor, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_animationEnabled() const", AS_METHODPR(Cursor, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const String& GetAppliedStyle() const", AS_METHODPR(Cursor, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_style() const", AS_METHODPR(Cursor, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttribute(uint) const", AS_METHODPR(Cursor, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Variant get_attributes(uint) const", AS_METHODPR(Cursor, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttribute(const String&in) const", AS_METHODPR(Cursor, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Cursor, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Cursor, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Cursor, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Cursor, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Cursor, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Cursor, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Cursor, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Cursor::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Cursor.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "BlendMode GetBlendMode() const", AS_METHODPR(Cursor, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "BlendMode get_blendMode() const", AS_METHODPR(Cursor, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool GetBlockEvents() const", AS_METHODPR(Cursor, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetBorder() const", AS_METHODPR(Cursor, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_border() const", AS_METHODPR(Cursor, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetBringToBack() const", AS_METHODPR(Cursor, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_bringToBack() const", AS_METHODPR(Cursor, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetBringToFront() const", AS_METHODPR(Cursor, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_bringToFront() const", AS_METHODPR(Cursor, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const String& GetCategory() const", AS_METHODPR(Cursor, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_category() const", AS_METHODPR(Cursor, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(uint) const", AS_METHODPR(Cursor, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_children(uint) const", AS_METHODPR(Cursor, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Cursor, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Cursor, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetChildOffset() const", AS_METHODPR(Cursor, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_childOffset() const", AS_METHODPR(Cursor, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Cursor_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Cursor_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Cursor_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetClipBorder() const", AS_METHODPR(Cursor, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_clipBorder() const", AS_METHODPR(Cursor, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetClipChildren() const", AS_METHODPR(Cursor, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_clipChildren() const", AS_METHODPR(Cursor, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetColor(Corner) const", AS_METHODPR(Cursor, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Color& get_colors(Corner) const", AS_METHODPR(Cursor, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetColorAttr() const", AS_METHODPR(Cursor, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntRect GetCombinedScreenRect()", AS_METHODPR(Cursor, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "IntRect get_combinedScreenRect()", AS_METHODPR(Cursor, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Cursor, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetDerivedColor() const", AS_METHODPR(Cursor, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "float GetDerivedOpacity() const", AS_METHODPR(Cursor, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "float get_derivedOpacity() const", AS_METHODPR(Cursor, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(Cursor, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_disabledOffset() const", AS_METHODPR(Cursor, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Cursor, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Cursor, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint GetDragButtonCount() const", AS_METHODPR(Cursor, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_dragButtonCount() const", AS_METHODPR(Cursor, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Cursor, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Cursor, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Cursor, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Cursor, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetEnableAnchor() const", AS_METHODPR(Cursor, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enableAnchor() const", AS_METHODPR(Cursor, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "VariantMap& GetEventDataMap() const", AS_METHODPR(Cursor, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "Object@+ GetEventSender() const", AS_METHODPR(Cursor, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "FocusMode GetFocusMode() const", AS_METHODPR(Cursor, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "FocusMode get_focusMode() const", AS_METHODPR(Cursor, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Cursor, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Cursor, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Cursor, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const VariantMap& get_globalVars() const", AS_METHODPR(Cursor, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetHeight() const", AS_METHODPR(Cursor, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_height() const", AS_METHODPR(Cursor, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Cursor, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Cursor, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetHoverOffset() const", AS_METHODPR(Cursor, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_hoverOffset() const", AS_METHODPR(Cursor, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetImageBorder() const", AS_METHODPR(Cursor, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_imageBorder() const", AS_METHODPR(Cursor, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetImageRect() const", AS_METHODPR(Cursor, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_imageRect() const", AS_METHODPR(Cursor, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndent() const", AS_METHODPR(Cursor, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indent() const", AS_METHODPR(Cursor, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndentSpacing() const", AS_METHODPR(Cursor, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indentSpacing() const", AS_METHODPR(Cursor, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndentWidth() const", AS_METHODPR(Cursor, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indentWidth() const", AS_METHODPR(Cursor, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Cursor, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Cursor, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_layoutBorder() const", AS_METHODPR(Cursor, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetLayoutElementMaxSize() const", AS_METHODPR(Cursor, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Cursor, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Cursor, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "LayoutMode GetLayoutMode() const", AS_METHODPR(Cursor, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "LayoutMode get_layoutMode() const", AS_METHODPR(Cursor, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetLayoutSpacing() const", AS_METHODPR(Cursor, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_layoutSpacing() const", AS_METHODPR(Cursor, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "Material@+ GetMaterial() const", AS_METHODPR(Cursor, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Material@+ get_material() const", AS_METHODPR(Cursor, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Cursor, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Cursor, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_maxAnchor() const", AS_METHODPR(Cursor, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMaxHeight() const", AS_METHODPR(Cursor, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_maxHeight() const", AS_METHODPR(Cursor, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Cursor, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_maxOffset() const", AS_METHODPR(Cursor, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMaxSize() const", AS_METHODPR(Cursor, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_maxSize() const", AS_METHODPR(Cursor, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMaxWidth() const", AS_METHODPR(Cursor, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_maxWidth() const", AS_METHODPR(Cursor, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetMinAnchor() const", AS_METHODPR(Cursor, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_minAnchor() const", AS_METHODPR(Cursor, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMinHeight() const", AS_METHODPR(Cursor, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_minHeight() const", AS_METHODPR(Cursor, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMinOffset() const", AS_METHODPR(Cursor, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_minOffset() const", AS_METHODPR(Cursor, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMinSize() const", AS_METHODPR(Cursor, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_minSize() const", AS_METHODPR(Cursor, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMinWidth() const", AS_METHODPR(Cursor, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_minWidth() const", AS_METHODPR(Cursor, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const String& GetName() const", AS_METHODPR(Cursor, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_name() const", AS_METHODPR(Cursor, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumAttributes() const", AS_METHODPR(Cursor, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_numAttributes() const", AS_METHODPR(Cursor, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumChildren(bool = false) const", AS_METHODPR(Cursor, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_numChildren(bool = false) const", AS_METHODPR(Cursor, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumNetworkAttributes() const", AS_METHODPR(Cursor, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Cursor, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Cursor, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Cursor, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "float GetOpacity() const", AS_METHODPR(Cursor, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "float get_opacity() const", AS_METHODPR(Cursor, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetParent() const", AS_METHODPR(Cursor, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_parent() const", AS_METHODPR(Cursor, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetPivot() const", AS_METHODPR(Cursor, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_pivot() const", AS_METHODPR(Cursor, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetPosition() const", AS_METHODPR(Cursor, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_position() const", AS_METHODPR(Cursor, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetPriority() const", AS_METHODPR(Cursor, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_priority() const", AS_METHODPR(Cursor, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetRoot() const", AS_METHODPR(Cursor, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_root() const", AS_METHODPR(Cursor, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Cursor, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_screenPosition() const", AS_METHODPR(Cursor, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const String& Cursor::GetShape() const | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "const String& GetShape() const", AS_METHODPR(Cursor, GetShape, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_shape() const", AS_METHODPR(Cursor, GetShape, () const, const String&), AS_CALL_THISCALL);
    // VariantVector Cursor::GetShapesAttr() const | File: ../UI/Cursor.h
    // Error: type "VariantVector" can not automatically bind
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetSize() const", AS_METHODPR(Cursor, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_size() const", AS_METHODPR(Cursor, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetSortChildren() const", AS_METHODPR(Cursor, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_sortChildren() const", AS_METHODPR(Cursor, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Cursor, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Cursor_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Cursor", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Cursor_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "Texture@+ GetTexture() const", AS_METHODPR(Cursor, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Texture@+ get_texture() const", AS_METHODPR(Cursor, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetTextureAttr() const", AS_METHODPR(Cursor, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "TraversalMode GetTraversalMode() const", AS_METHODPR(Cursor, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "TraversalMode get_traversalMode() const", AS_METHODPR(Cursor, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "StringHash GetType() const", AS_METHODPR(Cursor, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "StringHash get_type() const", AS_METHODPR(Cursor, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const String& GetTypeName() const", AS_METHODPR(Cursor, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_typeName() const", AS_METHODPR(Cursor, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetUseDerivedOpacity() const", AS_METHODPR(Cursor, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_useDerivedOpacity() const", AS_METHODPR(Cursor, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // bool Cursor::GetUseSystemShapes() const | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "bool GetUseSystemShapes() const", AS_METHODPR(Cursor, GetUseSystemShapes, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_useSystemShapes() const", AS_METHODPR(Cursor, GetUseSystemShapes, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Cursor, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const VariantMap& GetVars() const", AS_METHODPR(Cursor, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Cursor, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Cursor, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetWidth() const", AS_METHODPR(Cursor, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_width() const", AS_METHODPR(Cursor, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasColorGradient() const", AS_METHODPR(Cursor, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_colorGradient() const", AS_METHODPR(Cursor, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasEventHandlers() const", AS_METHODPR(Cursor, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasFocus() const", AS_METHODPR(Cursor, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_focus() const", AS_METHODPR(Cursor, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Cursor, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Cursor, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasTag(const String&in) const", AS_METHODPR(Cursor, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Cursor, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Cursor, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEditable() const", AS_METHODPR(Cursor, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_editable() const", AS_METHODPR(Cursor, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsElementEventSender() const", AS_METHODPR(Cursor, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_elementEventSender() const", AS_METHODPR(Cursor, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEnabled() const", AS_METHODPR(Cursor, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enabled() const", AS_METHODPR(Cursor, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEnabledSelf() const", AS_METHODPR(Cursor, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enabledSelf() const", AS_METHODPR(Cursor, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedHeight() const", AS_METHODPR(Cursor, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedHeight() const", AS_METHODPR(Cursor, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedSize() const", AS_METHODPR(Cursor, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedSize() const", AS_METHODPR(Cursor, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedWidth() const", AS_METHODPR(Cursor, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedWidth() const", AS_METHODPR(Cursor, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsHovering() const", AS_METHODPR(Cursor, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_hovering() const", AS_METHODPR(Cursor, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInside(IntVector2, bool)", AS_METHODPR(Cursor, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Cursor, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Cursor, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInternal() const", AS_METHODPR(Cursor, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_internal() const", AS_METHODPR(Cursor, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsSelected() const", AS_METHODPR(Cursor, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_selected() const", AS_METHODPR(Cursor, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool IsTemporary() const", AS_METHODPR(Cursor, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_temporary() const", AS_METHODPR(Cursor, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "bool IsTiled() const", AS_METHODPR(Cursor, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_tiled() const", AS_METHODPR(Cursor, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsVisible() const", AS_METHODPR(Cursor, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_visible() const", AS_METHODPR(Cursor, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsVisibleEffective() const", AS_METHODPR(Cursor, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_visibleEffective() const", AS_METHODPR(Cursor, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsWheelHandler() const", AS_METHODPR(Cursor, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Cursor, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool Load(Deserializer&)", AS_METHODPR(Cursor, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Cursor, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Cursor, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Cursor, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Cursor, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(Deserializer&)", AS_METHODPR(Cursor, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void MarkNetworkUpdate()", AS_METHODPR(Cursor, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Cursor, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Cursor, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Cursor, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Cursor, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Cursor, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Cursor, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Cursor, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Cursor, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Cursor, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Cursor, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Cursor, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Cursor, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnIndentSet()", AS_METHODPR(Cursor, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Cursor, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Cursor, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Cursor, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Cursor, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnSetEditable()", AS_METHODPR(Cursor, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnTextInput(const String&in)", AS_METHODPR(Cursor, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Cursor, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Cursor, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Cursor, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Cursor", "int Refs() const", AS_METHODPR(Cursor, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_refs() const", AS_METHODPR(Cursor, Refs, () const, int), AS_CALL_THISCALL);
    // static void Cursor::RegisterObject(Context* context) | File: ../UI/Cursor.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Cursor, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void Remove()", AS_METHODPR(Cursor, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAllChildren()", AS_METHODPR(Cursor, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAllTags()", AS_METHODPR(Cursor, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Cursor, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Cursor, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveChildAtIndex(uint)", AS_METHODPR(Cursor, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveInstanceDefault()", AS_METHODPR(Cursor, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveObjectAnimation()", AS_METHODPR(Cursor, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool RemoveTag(const String&in)", AS_METHODPR(Cursor, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void ResetDeepEnabled()", AS_METHODPR(Cursor, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void ResetToDefault()", AS_METHODPR(Cursor, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool Save(Serializer&) const", AS_METHODPR(Cursor, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SaveDefaultAttributes() const", AS_METHODPR(Cursor, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Cursor, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SaveXML(XMLElement&) const", AS_METHODPR(Cursor, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Cursor, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Cursor, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SendEvent(StringHash)", AS_METHODPR(Cursor, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Cursor, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Cursor, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAnimationEnabled(bool)", AS_METHODPR(Cursor, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_animationEnabled(bool)", AS_METHODPR(Cursor, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAnimationTime(float)", AS_METHODPR(Cursor, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Cursor, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Cursor, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Cursor, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Cursor, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Cursor, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Cursor, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Cursor, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetBlendMode(BlendMode)", AS_METHODPR(Cursor, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_blendMode(BlendMode)", AS_METHODPR(Cursor, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SetBlockEvents(bool)", AS_METHODPR(Cursor, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetBorder(const IntRect&in)", AS_METHODPR(Cursor, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_border(const IntRect&in)", AS_METHODPR(Cursor, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetBringToBack(bool)", AS_METHODPR(Cursor, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_bringToBack(bool)", AS_METHODPR(Cursor, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetBringToFront(bool)", AS_METHODPR(Cursor, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_bringToFront(bool)", AS_METHODPR(Cursor, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Cursor, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Cursor, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetClipChildren(bool)", AS_METHODPR(Cursor, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_clipChildren(bool)", AS_METHODPR(Cursor, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetColor(const Color&in)", AS_METHODPR(Cursor, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_color(const Color&in)", AS_METHODPR(Cursor, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetColor(Corner, const Color&in)", AS_METHODPR(Cursor, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_colors(Corner, const Color&in)", AS_METHODPR(Cursor, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDeepEnabled(bool)", AS_METHODPR(Cursor, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Cursor, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Cursor, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetDisabledOffset(int, int)", AS_METHODPR(Cursor, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Cursor, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Cursor, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEditable(bool)", AS_METHODPR(Cursor, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_editable(bool)", AS_METHODPR(Cursor, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetElementEventSender(bool)", AS_METHODPR(Cursor, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_elementEventSender(bool)", AS_METHODPR(Cursor, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnableAnchor(bool)", AS_METHODPR(Cursor, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_enableAnchor(bool)", AS_METHODPR(Cursor, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnabled(bool)", AS_METHODPR(Cursor, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_enabled(bool)", AS_METHODPR(Cursor, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnabledRecursive(bool)", AS_METHODPR(Cursor, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedHeight(int)", AS_METHODPR(Cursor, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Cursor, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedSize(int, int)", AS_METHODPR(Cursor, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedWidth(int)", AS_METHODPR(Cursor, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFocus(bool)", AS_METHODPR(Cursor, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_focus(bool)", AS_METHODPR(Cursor, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFocusMode(FocusMode)", AS_METHODPR(Cursor, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_focusMode(FocusMode)", AS_METHODPR(Cursor, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetFullImageRect()", AS_METHODPR(Cursor, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Cursor, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Cursor, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHeight(int)", AS_METHODPR(Cursor, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_height(int)", AS_METHODPR(Cursor, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Cursor, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Cursor, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHovering(bool)", AS_METHODPR(Cursor, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetHoverOffset(int, int)", AS_METHODPR(Cursor, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetImageBorder(const IntRect&in)", AS_METHODPR(Cursor, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_imageBorder(const IntRect&in)", AS_METHODPR(Cursor, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetImageRect(const IntRect&in)", AS_METHODPR(Cursor, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_imageRect(const IntRect&in)", AS_METHODPR(Cursor, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetIndent(int)", AS_METHODPR(Cursor, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_indent(int)", AS_METHODPR(Cursor, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetIndentSpacing(int)", AS_METHODPR(Cursor, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_indentSpacing(int)", AS_METHODPR(Cursor, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetInstanceDefault(bool)", AS_METHODPR(Cursor, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Cursor, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetInternal(bool)", AS_METHODPR(Cursor, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_internal(bool)", AS_METHODPR(Cursor, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Cursor, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Cursor, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Cursor, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Cursor, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Cursor, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Cursor, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutMode(LayoutMode)", AS_METHODPR(Cursor, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutSpacing(int)", AS_METHODPR(Cursor, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutSpacing(int)", AS_METHODPR(Cursor, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetMaterial(Material@+)", AS_METHODPR(Cursor, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_material(Material@+)", AS_METHODPR(Cursor, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Cursor, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Cursor, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Cursor, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxAnchor(float, float)", AS_METHODPR(Cursor, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxHeight(int)", AS_METHODPR(Cursor, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxHeight(int)", AS_METHODPR(Cursor, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Cursor, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Cursor, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxSize(int, int)", AS_METHODPR(Cursor, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxWidth(int)", AS_METHODPR(Cursor, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxWidth(int)", AS_METHODPR(Cursor, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Cursor, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Cursor, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinAnchor(float, float)", AS_METHODPR(Cursor, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinHeight(int)", AS_METHODPR(Cursor, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minHeight(int)", AS_METHODPR(Cursor, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Cursor, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Cursor, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minSize(const IntVector2&in)", AS_METHODPR(Cursor, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinSize(int, int)", AS_METHODPR(Cursor, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinWidth(int)", AS_METHODPR(Cursor, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minWidth(int)", AS_METHODPR(Cursor, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetName(const String&in)", AS_METHODPR(Cursor, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_name(const String&in)", AS_METHODPR(Cursor, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Cursor, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Cursor, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Cursor, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetOpacity(float)", AS_METHODPR(Cursor, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_opacity(float)", AS_METHODPR(Cursor, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Cursor, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPivot(const Vector2&in)", AS_METHODPR(Cursor, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_pivot(const Vector2&in)", AS_METHODPR(Cursor, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPivot(float, float)", AS_METHODPR(Cursor, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPosition(const IntVector2&in)", AS_METHODPR(Cursor, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_position(const IntVector2&in)", AS_METHODPR(Cursor, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPosition(int, int)", AS_METHODPR(Cursor, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPriority(int)", AS_METHODPR(Cursor, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_priority(int)", AS_METHODPR(Cursor, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Cursor, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSelected(bool)", AS_METHODPR(Cursor, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_selected(bool)", AS_METHODPR(Cursor, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void Cursor::SetShape(const String& shape) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetShape(const String&in)", AS_METHODPR(Cursor, SetShape, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_shape(const String&in)", AS_METHODPR(Cursor, SetShape, (const String&), void), AS_CALL_THISCALL);
    // void Cursor::SetShape(CursorShape shape) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetShape(CursorShape)", AS_METHODPR(Cursor, SetShape, (CursorShape), void), AS_CALL_THISCALL);
    // void Cursor::SetShapesAttr(const VariantVector& value) | File: ../UI/Cursor.h
    // Error: type "const VariantVector&" can not automatically bind
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSize(const IntVector2&in)", AS_METHODPR(Cursor, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_size(const IntVector2&in)", AS_METHODPR(Cursor, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSize(int, int)", AS_METHODPR(Cursor, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSortChildren(bool)", AS_METHODPR(Cursor, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_sortChildren(bool)", AS_METHODPR(Cursor, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Cursor, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Cursor, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Cursor, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Cursor_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetTemporary(bool)", AS_METHODPR(Cursor, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_temporary(bool)", AS_METHODPR(Cursor, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTexture(Texture@+)", AS_METHODPR(Cursor, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_texture(Texture@+)", AS_METHODPR(Cursor, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Cursor, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTiled(bool)", AS_METHODPR(Cursor, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_tiled(bool)", AS_METHODPR(Cursor, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Cursor, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_traversalMode(TraversalMode)", AS_METHODPR(Cursor, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Cursor, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_useDerivedOpacity(bool)", AS_METHODPR(Cursor, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void Cursor::SetUseSystemShapes(bool enable) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetUseSystemShapes(bool)", AS_METHODPR(Cursor, SetUseSystemShapes, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_useSystemShapes(bool)", AS_METHODPR(Cursor, SetUseSystemShapes, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Cursor, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Cursor, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Cursor, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVisible(bool)", AS_METHODPR(Cursor, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_visible(bool)", AS_METHODPR(Cursor, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetWidth(int)", AS_METHODPR(Cursor, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_width(int)", AS_METHODPR(Cursor, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SortChildren()", AS_METHODPR(Cursor, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromAllEvents()", AS_METHODPR(Cursor, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Cursor_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Cursor, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Cursor, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Cursor, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void Update(float)", AS_METHODPR(Cursor, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void UpdateLayout()", AS_METHODPR(Cursor, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Cursor", "int WeakRefs() const", AS_METHODPR(Cursor, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_weakRefs() const", AS_METHODPR(Cursor, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Cursor, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Cursor, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Cursor, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Cursor, "Cursor")
#endif
#ifdef REGISTER_MANUAL_PART_Cursor
    REGISTER_MANUAL_PART_Cursor(Cursor, "Cursor")
#endif
    RegisterSubclass<BorderImage, Cursor>(engine, "BorderImage", "Cursor");
    RegisterSubclass<UIElement, Cursor>(engine, "UIElement", "Cursor");
    RegisterSubclass<Animatable, Cursor>(engine, "Animatable", "Cursor");
    RegisterSubclass<Serializable, Cursor>(engine, "Serializable", "Cursor");
    RegisterSubclass<Object, Cursor>(engine, "Object", "Cursor");
    RegisterSubclass<RefCounted, Cursor>(engine, "RefCounted", "Cursor");

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void AddLight(Light@+)", AS_METHODPR(CustomGeometry, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CustomGeometry, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void AddVertexLight(Light@+)", AS_METHODPR(CustomGeometry, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void AllocateNetworkState()", AS_METHODPR(CustomGeometry, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void ApplyAttributes()", AS_METHODPR(CustomGeometry, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void CustomGeometry::BeginGeometry(unsigned index, PrimitiveType type) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void BeginGeometry(uint, PrimitiveType)", AS_METHODPR(CustomGeometry, BeginGeometry, (unsigned, PrimitiveType), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void CustomGeometry::Clear() | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void Clear()", AS_METHODPR(CustomGeometry, Clear, (), void), AS_CALL_THISCALL);
    // void CustomGeometry::Commit() | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void Commit()", AS_METHODPR(CustomGeometry, Commit, (), void), AS_CALL_THISCALL);
    // explicit CustomGeometry::CustomGeometry(Context* context) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_FACTORY, "CustomGeometry@+ f()", AS_FUNCTION(CustomGeometry_CustomGeometry_Context), AS_CALL_CDECL);
    // void CustomGeometry::DefineColor(const Color& color) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineColor(const Color&in)", AS_METHODPR(CustomGeometry, DefineColor, (const Color&), void), AS_CALL_THISCALL);
    // void CustomGeometry::DefineGeometry(unsigned index, PrimitiveType type, unsigned numVertices, bool hasNormals, bool hasColors, bool hasTexCoords, bool hasTangents) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineGeometry(uint, PrimitiveType, uint, bool, bool, bool, bool)", AS_METHODPR(CustomGeometry, DefineGeometry, (unsigned, PrimitiveType, unsigned, bool, bool, bool, bool), void), AS_CALL_THISCALL);
    // void CustomGeometry::DefineNormal(const Vector3& normal) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineNormal(const Vector3&in)", AS_METHODPR(CustomGeometry, DefineNormal, (const Vector3&), void), AS_CALL_THISCALL);
    // void CustomGeometry::DefineTangent(const Vector4& tangent) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineTangent(const Vector4&in)", AS_METHODPR(CustomGeometry, DefineTangent, (const Vector4&), void), AS_CALL_THISCALL);
    // void CustomGeometry::DefineTexCoord(const Vector2& texCoord) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineTexCoord(const Vector2&in)", AS_METHODPR(CustomGeometry, DefineTexCoord, (const Vector2&), void), AS_CALL_THISCALL);
    // void CustomGeometry::DefineVertex(const Vector3& position) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineVertex(const Vector3&in)", AS_METHODPR(CustomGeometry, DefineVertex, (const Vector3&), void), AS_CALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(CustomGeometry, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool CustomGeometry::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(CustomGeometry, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetAnimationEnabled() const", AS_METHODPR(CustomGeometry, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_animationEnabled() const", AS_METHODPR(CustomGeometry, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttribute(uint) const", AS_METHODPR(CustomGeometry, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Variant get_attributes(uint) const", AS_METHODPR(CustomGeometry, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttribute(const String&in) const", AS_METHODPR(CustomGeometry, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CustomGeometry, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CustomGeometry, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CustomGeometry, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CustomGeometry, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CustomGeometry, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CustomGeometry, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CustomGeometry, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetBlockEvents() const", AS_METHODPR(CustomGeometry, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(CustomGeometry, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& get_boundingBox() const", AS_METHODPR(CustomGeometry, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetCastShadows() const", AS_METHODPR(CustomGeometry, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_castShadows() const", AS_METHODPR(CustomGeometry, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const String& GetCategory() const", AS_METHODPR(CustomGeometry, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const String& get_category() const", AS_METHODPR(CustomGeometry, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Component@+ GetComponent(StringHash) const", AS_METHODPR(CustomGeometry, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetDistance() const", AS_METHODPR(CustomGeometry, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint8 GetDrawableFlags() const", AS_METHODPR(CustomGeometry, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetDrawDistance() const", AS_METHODPR(CustomGeometry, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_drawDistance() const", AS_METHODPR(CustomGeometry, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "VariantMap& GetEventDataMap() const", AS_METHODPR(CustomGeometry, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "Object@+ GetEventSender() const", AS_METHODPR(CustomGeometry, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Light@+ GetFirstLight() const", AS_METHODPR(CustomGeometry, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // PODVector<unsigned char> CustomGeometry::GetGeometryDataAttr() const | File: ../Graphics/CustomGeometry.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CustomGeometry, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CustomGeometry, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CustomGeometry, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const VariantMap& get_globalVars() const", AS_METHODPR(CustomGeometry, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetID() const", AS_METHODPR(CustomGeometry, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_id() const", AS_METHODPR(CustomGeometry, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CustomGeometry, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetLightMask() const", AS_METHODPR(CustomGeometry, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_lightMask() const", AS_METHODPR(CustomGeometry, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(CustomGeometry_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetLodBias() const", AS_METHODPR(CustomGeometry, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_lodBias() const", AS_METHODPR(CustomGeometry, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetLodDistance() const", AS_METHODPR(CustomGeometry, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // Geometry* CustomGeometry::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(CustomGeometry, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* CustomGeometry::GetMaterial(unsigned index=0) const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "Material@+ GetMaterial(uint = 0) const", AS_METHODPR(CustomGeometry, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Material@+ get_materials(uint = 0) const", AS_METHODPR(CustomGeometry, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    // const ResourceRefList& CustomGeometry::GetMaterialsAttr() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "const ResourceRefList& GetMaterialsAttr() const", AS_METHODPR(CustomGeometry, GetMaterialsAttr, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetMaxLights() const", AS_METHODPR(CustomGeometry, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_maxLights() const", AS_METHODPR(CustomGeometry, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetMaxZ() const", AS_METHODPR(CustomGeometry, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetMinZ() const", AS_METHODPR(CustomGeometry, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Node@+ GetNode() const", AS_METHODPR(CustomGeometry, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Node@+ get_node() const", AS_METHODPR(CustomGeometry, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumAttributes() const", AS_METHODPR(CustomGeometry, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numAttributes() const", AS_METHODPR(CustomGeometry, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned CustomGeometry::GetNumGeometries() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumGeometries() const", AS_METHODPR(CustomGeometry, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numGeometries() const", AS_METHODPR(CustomGeometry, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumNetworkAttributes() const", AS_METHODPR(CustomGeometry, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned CustomGeometry::GetNumOccluderTriangles() override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumOccluderTriangles()", AS_METHODPR(CustomGeometry, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // unsigned CustomGeometry::GetNumVertices(unsigned index) const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumVertices(uint) const", AS_METHODPR(CustomGeometry, GetNumVertices, (unsigned) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numVertices(uint) const", AS_METHODPR(CustomGeometry, GetNumVertices, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CustomGeometry, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CustomGeometry, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CustomGeometry, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Scene@+ GetScene() const", AS_METHODPR(CustomGeometry, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetShadowDistance() const", AS_METHODPR(CustomGeometry, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_shadowDistance() const", AS_METHODPR(CustomGeometry, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetShadowMask() const", AS_METHODPR(CustomGeometry, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_shadowMask() const", AS_METHODPR(CustomGeometry, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetSortValue() const", AS_METHODPR(CustomGeometry, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CustomGeometry, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "StringHash GetType() const", AS_METHODPR(CustomGeometry, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "StringHash get_type() const", AS_METHODPR(CustomGeometry, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const String& GetTypeName() const", AS_METHODPR(CustomGeometry, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const String& get_typeName() const", AS_METHODPR(CustomGeometry, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(CustomGeometry, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // CustomGeometryVertex* CustomGeometry::GetVertex(unsigned geometryIndex, unsigned vertexNum) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "CustomGeometryVertex@+ GetVertex(uint, uint)", AS_METHODPR(CustomGeometry, GetVertex, (unsigned, unsigned), CustomGeometryVertex*), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(CustomGeometry_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // Vector<PODVector<CustomGeometryVertex>>& CustomGeometry::GetVertices() | File: ../Graphics/CustomGeometry.h
    // Error: type "Vector<PODVector<CustomGeometryVertex>>&" can not automatically bind
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetViewMask() const", AS_METHODPR(CustomGeometry, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_viewMask() const", AS_METHODPR(CustomGeometry, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(CustomGeometry, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(CustomGeometry, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Zone@+ GetZone() const", AS_METHODPR(CustomGeometry, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Zone@+ get_zone() const", AS_METHODPR(CustomGeometry, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetZoneMask() const", AS_METHODPR(CustomGeometry, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_zoneMask() const", AS_METHODPR(CustomGeometry, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasBasePass(uint) const", AS_METHODPR(CustomGeometry, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasEventHandlers() const", AS_METHODPR(CustomGeometry, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CustomGeometry, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CustomGeometry, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool CustomGeometry::IsDynamic() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsDynamic() const", AS_METHODPR(CustomGeometry, IsDynamic, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_dynamic() const", AS_METHODPR(CustomGeometry, IsDynamic, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsEnabled() const", AS_METHODPR(CustomGeometry, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_enabled() const", AS_METHODPR(CustomGeometry, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsEnabledEffective() const", AS_METHODPR(CustomGeometry, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_enabledEffective() const", AS_METHODPR(CustomGeometry, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CustomGeometry, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView() const", AS_METHODPR(CustomGeometry, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_inView() const", AS_METHODPR(CustomGeometry, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView(Camera@+) const", AS_METHODPR(CustomGeometry, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(CustomGeometry, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsOccludee() const", AS_METHODPR(CustomGeometry, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_occludee() const", AS_METHODPR(CustomGeometry, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsOccluder() const", AS_METHODPR(CustomGeometry, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_occluder() const", AS_METHODPR(CustomGeometry, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsReplicated() const", AS_METHODPR(CustomGeometry, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_replicated() const", AS_METHODPR(CustomGeometry, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsTemporary() const", AS_METHODPR(CustomGeometry, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_temporary() const", AS_METHODPR(CustomGeometry, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsZoneDirty() const", AS_METHODPR(CustomGeometry, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void LimitLights()", AS_METHODPR(CustomGeometry, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void LimitVertexLights(bool)", AS_METHODPR(CustomGeometry, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool Load(Deserializer&)", AS_METHODPR(CustomGeometry, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CustomGeometry, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CustomGeometry, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkForUpdate()", AS_METHODPR(CustomGeometry, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkInView(const FrameInfo&in)", AS_METHODPR(CustomGeometry, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkInView(uint)", AS_METHODPR(CustomGeometry, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkNetworkUpdate()", AS_METHODPR(CustomGeometry, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CustomGeometry, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CustomGeometry, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CustomGeometry, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnSetEnabled()", AS_METHODPR(CustomGeometry, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void PrepareNetworkUpdate()", AS_METHODPR(CustomGeometry, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void CustomGeometry::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/CustomGeometry.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CustomGeometry, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CustomGeometry, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CustomGeometry", "int Refs() const", AS_METHODPR(CustomGeometry, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "int get_refs() const", AS_METHODPR(CustomGeometry, Refs, () const, int), AS_CALL_THISCALL);
    // static void CustomGeometry::RegisterObject(Context* context) | File: ../Graphics/CustomGeometry.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CustomGeometry, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void Remove()", AS_METHODPR(CustomGeometry, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CustomGeometry, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveInstanceDefault()", AS_METHODPR(CustomGeometry, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveObjectAnimation()", AS_METHODPR(CustomGeometry, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void ResetToDefault()", AS_METHODPR(CustomGeometry, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool Save(Serializer&) const", AS_METHODPR(CustomGeometry, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveDefaultAttributes() const", AS_METHODPR(CustomGeometry, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CustomGeometry, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveXML(XMLElement&) const", AS_METHODPR(CustomGeometry, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SendEvent(StringHash)", AS_METHODPR(CustomGeometry, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CustomGeometry, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAnimationEnabled(bool)", AS_METHODPR(CustomGeometry, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_animationEnabled(bool)", AS_METHODPR(CustomGeometry, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAnimationTime(float)", AS_METHODPR(CustomGeometry, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CustomGeometry, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CustomGeometry, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CustomGeometry, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CustomGeometry, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CustomGeometry, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CustomGeometry, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CustomGeometry, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetBasePass(uint)", AS_METHODPR(CustomGeometry, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetBlockEvents(bool)", AS_METHODPR(CustomGeometry, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetCastShadows(bool)", AS_METHODPR(CustomGeometry, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_castShadows(bool)", AS_METHODPR(CustomGeometry, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetDrawDistance(float)", AS_METHODPR(CustomGeometry, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_drawDistance(float)", AS_METHODPR(CustomGeometry, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void CustomGeometry::SetDynamic(bool enable) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetDynamic(bool)", AS_METHODPR(CustomGeometry, SetDynamic, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_dynamic(bool)", AS_METHODPR(CustomGeometry, SetDynamic, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetEnabled(bool)", AS_METHODPR(CustomGeometry, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_enabled(bool)", AS_METHODPR(CustomGeometry, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void CustomGeometry::SetGeometryDataAttr(const PODVector<unsigned char>& value) | File: ../Graphics/CustomGeometry.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CustomGeometry, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CustomGeometry, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetInstanceDefault(bool)", AS_METHODPR(CustomGeometry, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CustomGeometry, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetLightMask(uint)", AS_METHODPR(CustomGeometry, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_lightMask(uint)", AS_METHODPR(CustomGeometry, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetLodBias(float)", AS_METHODPR(CustomGeometry, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_lodBias(float)", AS_METHODPR(CustomGeometry, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void CustomGeometry::SetMaterial(Material* material) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaterial(Material@+)", AS_METHODPR(CustomGeometry, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_material(Material@+)", AS_METHODPR(CustomGeometry, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // bool CustomGeometry::SetMaterial(unsigned index, Material* material) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetMaterial(uint, Material@+)", AS_METHODPR(CustomGeometry, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool set_materials(uint, Material@+)", AS_METHODPR(CustomGeometry, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    // void CustomGeometry::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaterialsAttr(const ResourceRefList&in)", AS_METHODPR(CustomGeometry, SetMaterialsAttr, (const ResourceRefList&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaxLights(uint)", AS_METHODPR(CustomGeometry, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_maxLights(uint)", AS_METHODPR(CustomGeometry, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMinMaxZ(float, float)", AS_METHODPR(CustomGeometry, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void CustomGeometry::SetNumGeometries(unsigned num) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetNumGeometries(uint)", AS_METHODPR(CustomGeometry, SetNumGeometries, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_numGeometries(uint)", AS_METHODPR(CustomGeometry, SetNumGeometries, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CustomGeometry, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CustomGeometry, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CustomGeometry, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetOccludee(bool)", AS_METHODPR(CustomGeometry, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_occludee(bool)", AS_METHODPR(CustomGeometry, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetOccluder(bool)", AS_METHODPR(CustomGeometry, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_occluder(bool)", AS_METHODPR(CustomGeometry, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetShadowDistance(float)", AS_METHODPR(CustomGeometry, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_shadowDistance(float)", AS_METHODPR(CustomGeometry, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetShadowMask(uint)", AS_METHODPR(CustomGeometry, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_shadowMask(uint)", AS_METHODPR(CustomGeometry, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetSortValue(float)", AS_METHODPR(CustomGeometry, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetTemporary(bool)", AS_METHODPR(CustomGeometry, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_temporary(bool)", AS_METHODPR(CustomGeometry, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetViewMask(uint)", AS_METHODPR(CustomGeometry, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_viewMask(uint)", AS_METHODPR(CustomGeometry, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetZone(Zone@+, bool = false)", AS_METHODPR(CustomGeometry, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetZoneMask(uint)", AS_METHODPR(CustomGeometry, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_zoneMask(uint)", AS_METHODPR(CustomGeometry, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromAllEvents()", AS_METHODPR(CustomGeometry, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CustomGeometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CustomGeometry, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CustomGeometry, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CustomGeometry, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void Update(const FrameInfo&in)", AS_METHODPR(CustomGeometry, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(CustomGeometry, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(CustomGeometry, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CustomGeometry", "int WeakRefs() const", AS_METHODPR(CustomGeometry, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "int get_weakRefs() const", AS_METHODPR(CustomGeometry, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CustomGeometry, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CustomGeometry, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CustomGeometry, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CustomGeometry, "CustomGeometry")
#endif
#ifdef REGISTER_MANUAL_PART_CustomGeometry
    REGISTER_MANUAL_PART_CustomGeometry(CustomGeometry, "CustomGeometry")
#endif
    RegisterSubclass<Drawable, CustomGeometry>(engine, "Drawable", "CustomGeometry");
    RegisterSubclass<Component, CustomGeometry>(engine, "Component", "CustomGeometry");
    RegisterSubclass<Animatable, CustomGeometry>(engine, "Animatable", "CustomGeometry");
    RegisterSubclass<Serializable, CustomGeometry>(engine, "Serializable", "CustomGeometry");
    RegisterSubclass<Object, CustomGeometry>(engine, "Object", "CustomGeometry");
    RegisterSubclass<RefCounted, CustomGeometry>(engine, "RefCounted", "CustomGeometry");

#ifdef URHO3D_PHYSICS
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionGeometryData", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CollisionGeometryData, AddRef, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionGeometryData", "int Refs() const", AS_METHODPR(CollisionGeometryData, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionGeometryData", "int get_refs() const", AS_METHODPR(CollisionGeometryData, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionGeometryData", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CollisionGeometryData, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionGeometryData", "int WeakRefs() const", AS_METHODPR(CollisionGeometryData, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CollisionGeometryData", "int get_weakRefs() const", AS_METHODPR(CollisionGeometryData, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CollisionGeometryData, "CollisionGeometryData")
#endif
#ifdef REGISTER_MANUAL_PART_CollisionGeometryData
    REGISTER_MANUAL_PART_CollisionGeometryData(CollisionGeometryData, "CollisionGeometryData")
#endif
    RegisterSubclass<RefCounted, CollisionGeometryData>(engine, "RefCounted", "CollisionGeometryData");
#endif

    // Color ColorFrame::color_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("ColorFrame", "Color color", offsetof(ColorFrame, color_));
    // float ColorFrame::time_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("ColorFrame", "float time", offsetof(ColorFrame, time_));
    // ColorFrame::ColorFrame() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f()", AS_FUNCTION(ColorFrame_ColorFrame_void), AS_CALL_CDECL);
    // explicit ColorFrame::ColorFrame(const Color& color) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in)", AS_FUNCTION(ColorFrame_ColorFrame_Color), AS_CALL_CDECL);
    // ColorFrame::ColorFrame(const Color& color, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in, float)", AS_FUNCTION(ColorFrame_ColorFrame_Color_float), AS_CALL_CDECL);
    // Color ColorFrame::Interpolate(const ColorFrame& next, float time) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ColorFrame", "Color Interpolate(const ColorFrame&in, float) const", AS_METHODPR(ColorFrame, Interpolate, (const ColorFrame&, float) const, Color), AS_CALL_THISCALL);
    // ColorFrame& ColorFrame::operator=(const ColorFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ColorFrame>(engine, "ColorFrame");
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_ColorFrame
    REGISTER_MANUAL_PART_ColorFrame(ColorFrame, "ColorFrame")
#endif

    // WeakPtr<Component> ComponentReplicationState::component_ | File: ../Scene/ReplicationState.h
    // Error: type "WeakPtr<Component>" can not automatically bind
    // Connection* ReplicationState::connection_ | File: ../Scene/ReplicationState.h
    // Connection* can not be registered
    // DirtyBits ComponentReplicationState::dirtyAttributes_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("ComponentReplicationState", "DirtyBits dirtyAttributes", offsetof(ComponentReplicationState, dirtyAttributes_));
    // NodeReplicationState* ComponentReplicationState::nodeState_ | File: ../Scene/ReplicationState.h
    // NodeReplicationState* can not be registered
    // ComponentReplicationState& ComponentReplicationState::operator=(const ComponentReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ComponentReplicationState>(engine, "ComponentReplicationState");
#ifdef REGISTER_MANUAL_PART_ReplicationState
    REGISTER_MANUAL_PART_ReplicationState(ComponentReplicationState, "ComponentReplicationState")
#endif
#ifdef REGISTER_MANUAL_PART_ComponentReplicationState
    REGISTER_MANUAL_PART_ComponentReplicationState(ComponentReplicationState, "ComponentReplicationState")
#endif

    // unsigned CompressedLevel::blockSize_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "uint blockSize", offsetof(CompressedLevel, blockSize_));
    // unsigned char* CompressedLevel::data_ | File: ../Resource/Image.h
    // unsigned char* can not be registered
    // unsigned CompressedLevel::dataSize_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "uint dataSize", offsetof(CompressedLevel, dataSize_));
    // int CompressedLevel::depth_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "int depth", offsetof(CompressedLevel, depth_));
    // CompressedFormat CompressedLevel::format_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "CompressedFormat format", offsetof(CompressedLevel, format_));
    // int CompressedLevel::height_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "int height", offsetof(CompressedLevel, height_));
    // unsigned CompressedLevel::rows_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "uint rows", offsetof(CompressedLevel, rows_));
    // unsigned CompressedLevel::rowSize_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "uint rowSize", offsetof(CompressedLevel, rowSize_));
    // int CompressedLevel::width_ | File: ../Resource/Image.h
    engine->RegisterObjectProperty("CompressedLevel", "int width", offsetof(CompressedLevel, width_));
    // bool CompressedLevel::Decompress(unsigned char* dest) const | File: ../Resource/Image.h
    // Error: type "unsigned char*" can not automatically bind
    // CompressedLevel& CompressedLevel::operator=(const CompressedLevel&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CompressedLevel>(engine, "CompressedLevel");
#ifdef REGISTER_MANUAL_PART_CompressedLevel
    REGISTER_MANUAL_PART_CompressedLevel(CompressedLevel, "CompressedLevel")
#endif

#ifdef URHO3D_PHYSICS
    // unsigned ConvexData::indexCount_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("ConvexData", "uint indexCount", offsetof(ConvexData, indexCount_));
    // SharedArrayPtr<unsigned> ConvexData::indexData_ | File: ../Physics/CollisionShape.h
    // Error: type "SharedArrayPtr<unsigned>" can not automatically bind
    // unsigned ConvexData::vertexCount_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("ConvexData", "uint vertexCount", offsetof(ConvexData, vertexCount_));
    // SharedArrayPtr<Vector3> ConvexData::vertexData_ | File: ../Physics/CollisionShape.h
    // Error: type "SharedArrayPtr<Vector3>" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ConvexData, AddRef, (), void), AS_CALL_THISCALL);
    // void ConvexData::BuildHull(const PODVector<Vector3>& vertices) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("ConvexData", "void BuildHull(Array<Vector3>@+)", AS_FUNCTION_OBJFIRST(ConvexData_BuildHull_PODVectorVector3), AS_CALL_CDECL_OBJFIRST);
    // ConvexData::ConvexData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(Model@+, uint)", AS_FUNCTION(ConvexData_ConvexData_Model_unsigned), AS_CALL_CDECL);
    // explicit ConvexData::ConvexData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(CustomGeometry@+)", AS_FUNCTION(ConvexData_ConvexData_CustomGeometry), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConvexData", "int Refs() const", AS_METHODPR(ConvexData, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConvexData", "int get_refs() const", AS_METHODPR(ConvexData, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ConvexData, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConvexData", "int WeakRefs() const", AS_METHODPR(ConvexData, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ConvexData", "int get_weakRefs() const", AS_METHODPR(ConvexData, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionGeometryData
    REGISTER_MANUAL_PART_CollisionGeometryData(ConvexData, "ConvexData")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ConvexData, "ConvexData")
#endif
#ifdef REGISTER_MANUAL_PART_ConvexData
    REGISTER_MANUAL_PART_ConvexData(ConvexData, "ConvexData")
#endif
    RegisterSubclass<CollisionGeometryData, ConvexData>(engine, "CollisionGeometryData", "ConvexData");
    RegisterSubclass<RefCounted, ConvexData>(engine, "RefCounted", "ConvexData");
#endif

#ifdef URHO3D_NAVIGATION
    // unsigned char CrowdObstacleAvoidanceParams::adaptiveDepth | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "uint8 adaptiveDepth", offsetof(CrowdObstacleAvoidanceParams, adaptiveDepth));
    // unsigned char CrowdObstacleAvoidanceParams::adaptiveDivs | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "uint8 adaptiveDivs", offsetof(CrowdObstacleAvoidanceParams, adaptiveDivs));
    // unsigned char CrowdObstacleAvoidanceParams::adaptiveRings | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "uint8 adaptiveRings", offsetof(CrowdObstacleAvoidanceParams, adaptiveRings));
    // unsigned char CrowdObstacleAvoidanceParams::gridSize | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "uint8 gridSize", offsetof(CrowdObstacleAvoidanceParams, gridSize));
    // float CrowdObstacleAvoidanceParams::horizTime | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float horizTime", offsetof(CrowdObstacleAvoidanceParams, horizTime));
    // float CrowdObstacleAvoidanceParams::velBias | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float velBias", offsetof(CrowdObstacleAvoidanceParams, velBias));
    // float CrowdObstacleAvoidanceParams::weightCurVel | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float weightCurVel", offsetof(CrowdObstacleAvoidanceParams, weightCurVel));
    // float CrowdObstacleAvoidanceParams::weightDesVel | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float weightDesVel", offsetof(CrowdObstacleAvoidanceParams, weightDesVel));
    // float CrowdObstacleAvoidanceParams::weightSide | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float weightSide", offsetof(CrowdObstacleAvoidanceParams, weightSide));
    // float CrowdObstacleAvoidanceParams::weightToi | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectProperty("CrowdObstacleAvoidanceParams", "float weightToi", offsetof(CrowdObstacleAvoidanceParams, weightToi));
    // CrowdObstacleAvoidanceParams& CrowdObstacleAvoidanceParams::operator=(const CrowdObstacleAvoidanceParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CrowdObstacleAvoidanceParams>(engine, "CrowdObstacleAvoidanceParams");
#ifdef REGISTER_MANUAL_PART_CrowdObstacleAvoidanceParams
    REGISTER_MANUAL_PART_CrowdObstacleAvoidanceParams(CrowdObstacleAvoidanceParams, "CrowdObstacleAvoidanceParams")
#endif
#endif

    // IntVector2 CursorShapeInfo::hotSpot_ | File: ../UI/Cursor.h
    engine->RegisterObjectProperty("CursorShapeInfo", "IntVector2 hotSpot", offsetof(CursorShapeInfo, hotSpot_));
    // SharedPtr<Image> CursorShapeInfo::image_ | File: ../UI/Cursor.h
    // Error: type "SharedPtr<Image>" can not automatically bind
    // IntRect CursorShapeInfo::imageRect_ | File: ../UI/Cursor.h
    engine->RegisterObjectProperty("CursorShapeInfo", "IntRect imageRect", offsetof(CursorShapeInfo, imageRect_));
    // SDL_Cursor* CursorShapeInfo::osCursor_ | File: ../UI/Cursor.h
    // SDL_Cursor* can not be registered
    // int CursorShapeInfo::systemCursor_ | File: ../UI/Cursor.h
    engine->RegisterObjectProperty("CursorShapeInfo", "int systemCursor", offsetof(CursorShapeInfo, systemCursor_));
    // bool CursorShapeInfo::systemDefined_ | File: ../UI/Cursor.h
    engine->RegisterObjectProperty("CursorShapeInfo", "bool systemDefined", offsetof(CursorShapeInfo, systemDefined_));
    // SharedPtr<Texture> CursorShapeInfo::texture_ | File: ../UI/Cursor.h
    // Error: type "SharedPtr<Texture>" can not automatically bind
    // explicit CursorShapeInfo::CursorShapeInfo(int systemCursor) | File: ../UI/Cursor.h
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(CursorShapeInfo_CursorShapeInfo_int), AS_CALL_CDECL_OBJFIRST);
    // CursorShapeInfo& CursorShapeInfo::operator=(const CursorShapeInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CursorShapeInfo>(engine, "CursorShapeInfo");
#ifdef REGISTER_MANUAL_PART_CursorShapeInfo
    REGISTER_MANUAL_PART_CursorShapeInfo(CursorShapeInfo, "CursorShapeInfo")
#endif

    // unsigned CustomGeometryVertex::color_ | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectProperty("CustomGeometryVertex", "uint color", offsetof(CustomGeometryVertex, color_));
    // Vector3 CustomGeometryVertex::normal_ | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectProperty("CustomGeometryVertex", "Vector3 normal", offsetof(CustomGeometryVertex, normal_));
    // Vector3 CustomGeometryVertex::position_ | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectProperty("CustomGeometryVertex", "Vector3 position", offsetof(CustomGeometryVertex, position_));
    // Vector4 CustomGeometryVertex::tangent_ | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectProperty("CustomGeometryVertex", "Vector4 tangent", offsetof(CustomGeometryVertex, tangent_));
    // Vector2 CustomGeometryVertex::texCoord_ | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectProperty("CustomGeometryVertex", "Vector2 texCoord", offsetof(CustomGeometryVertex, texCoord_));
    // CustomGeometryVertex& CustomGeometryVertex::operator=(const CustomGeometryVertex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CustomGeometryVertex>(engine, "CustomGeometryVertex");
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_CustomGeometryVertex
    REGISTER_MANUAL_PART_CustomGeometryVertex(CustomGeometryVertex, "CustomGeometryVertex")
#endif

}

}
