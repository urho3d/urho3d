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
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionBox2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void AllocateNetworkState()", asMETHODPR(CollisionBox2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ApplyAttributes()", asMETHODPR(CollisionBox2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionBox2D::CollisionBox2D(Context* context) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_FACTORY, "CollisionBox2D@+ f()", asFUNCTION(CollisionBox2D_CollisionBox2D_Context), asCALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void CreateFixture()", asMETHODPR(CollisionBox2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionBox2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // float CollisionBox2D::GetAngle() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAngle() const", asMETHODPR(CollisionBox2D, GetAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_angle() const", asMETHODPR(CollisionBox2D, GetAngle, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionBox2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_animationEnabled() const", asMETHODPR(CollisionBox2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionBox2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionBox2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionBox2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionBox2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionBox2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionBox2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionBox2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionBox2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionBox2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionBox2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetBlockEvents() const", asMETHODPR(CollisionBox2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const String& GetCategory() const", asMETHODPR(CollisionBox2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const String& get_category() const", asMETHODPR(CollisionBox2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetCategoryBits() const", asMETHODPR(CollisionBox2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_categoryBits() const", asMETHODPR(CollisionBox2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // const Vector2& CollisionBox2D::GetCenter() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& GetCenter() const", asMETHODPR(CollisionBox2D, GetCenter, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_center() const", asMETHODPR(CollisionBox2D, GetCenter, () const, const Vector2&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionBox2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetDensity() const", asMETHODPR(CollisionBox2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_density() const", asMETHODPR(CollisionBox2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionBox2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionBox2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetFriction() const", asMETHODPR(CollisionBox2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_friction() const", asMETHODPR(CollisionBox2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionBox2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionBox2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionBox2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionBox2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetGroupIndex() const", asMETHODPR(CollisionBox2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_groupIndex() const", asMETHODPR(CollisionBox2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetID() const", asMETHODPR(CollisionBox2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "uint get_id() const", asMETHODPR(CollisionBox2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetInertia() const", asMETHODPR(CollisionBox2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_inertia() const", asMETHODPR(CollisionBox2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionBox2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "int GetMaskBits() const", asMETHODPR(CollisionBox2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_maskBits() const", asMETHODPR(CollisionBox2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetMass() const", asMETHODPR(CollisionBox2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_mass() const", asMETHODPR(CollisionBox2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionBox2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionBox2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Node@+ GetNode() const", asMETHODPR(CollisionBox2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "Node@+ get_node() const", asMETHODPR(CollisionBox2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetNumAttributes() const", asMETHODPR(CollisionBox2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "uint get_numAttributes() const", asMETHODPR(CollisionBox2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionBox2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionBox2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionBox2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionBox2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "float GetRestitution() const", asMETHODPR(CollisionBox2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_restitution() const", asMETHODPR(CollisionBox2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "Scene@+ GetScene() const", asMETHODPR(CollisionBox2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // const Vector2& CollisionBox2D::GetSize() const | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& GetSize() const", asMETHODPR(CollisionBox2D, GetSize, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_size() const", asMETHODPR(CollisionBox2D, GetSize, () const, const Vector2&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionBox2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "StringHash GetType() const", asMETHODPR(CollisionBox2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "StringHash get_type() const", asMETHODPR(CollisionBox2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "const String& GetTypeName() const", asMETHODPR(CollisionBox2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const String& get_typeName() const", asMETHODPR(CollisionBox2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasEventHandlers() const", asMETHODPR(CollisionBox2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionBox2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionBox2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsEnabled() const", asMETHODPR(CollisionBox2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_enabled() const", asMETHODPR(CollisionBox2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionBox2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_enabledEffective() const", asMETHODPR(CollisionBox2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionBox2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsReplicated() const", asMETHODPR(CollisionBox2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_replicated() const", asMETHODPR(CollisionBox2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsTemporary() const", asMETHODPR(CollisionBox2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_temporary() const", asMETHODPR(CollisionBox2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool IsTrigger() const", asMETHODPR(CollisionBox2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool get_trigger() const", asMETHODPR(CollisionBox2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool Load(Deserializer&)", asMETHODPR(CollisionBox2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionBox2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionBox2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionBox2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionBox2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionBox2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionBox2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void OnSetEnabled()", asMETHODPR(CollisionBox2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionBox2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionBox2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionBox2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionBox2D", "int Refs() const", asMETHODPR(CollisionBox2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_refs() const", asMETHODPR(CollisionBox2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionBox2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionBox2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ReleaseFixture()", asMETHODPR(CollisionBox2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionBox2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionBox2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void Remove()", asMETHODPR(CollisionBox2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionBox2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionBox2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionBox2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void ResetToDefault()", asMETHODPR(CollisionBox2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool Save(Serializer&) const", asMETHODPR(CollisionBox2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionBox2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionBox2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionBox2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SendEvent(StringHash)", asMETHODPR(CollisionBox2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionBox2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void CollisionBox2D::SetAngle(float angle) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAngle(float)", asMETHODPR(CollisionBox2D, SetAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_angle(float)", asMETHODPR(CollisionBox2D, SetAngle, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionBox2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionBox2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAnimationTime(float)", asMETHODPR(CollisionBox2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionBox2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionBox2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionBox2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionBox2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionBox2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionBox2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionBox2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionBox2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCategoryBits(int)", asMETHODPR(CollisionBox2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_categoryBits(int)", asMETHODPR(CollisionBox2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionBox2D::SetCenter(const Vector2& center) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(const Vector2&in)", asMETHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    // void CollisionBox2D::SetCenter(float x, float y) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(float, float)", asMETHODPR(CollisionBox2D, SetCenter, (float, float), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetDensity(float)", asMETHODPR(CollisionBox2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_density(float)", asMETHODPR(CollisionBox2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetEnabled(bool)", asMETHODPR(CollisionBox2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_enabled(bool)", asMETHODPR(CollisionBox2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetFriction(float)", asMETHODPR(CollisionBox2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_friction(float)", asMETHODPR(CollisionBox2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionBox2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionBox2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetGroupIndex(int)", asMETHODPR(CollisionBox2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_groupIndex(int)", asMETHODPR(CollisionBox2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionBox2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionBox2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetMaskBits(int)", asMETHODPR(CollisionBox2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_maskBits(int)", asMETHODPR(CollisionBox2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionBox2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionBox2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionBox2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetRestitution(float)", asMETHODPR(CollisionBox2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_restitution(float)", asMETHODPR(CollisionBox2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void CollisionBox2D::SetSize(const Vector2& size) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(const Vector2&in)", asMETHODPR(CollisionBox2D, SetSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_size(const Vector2&in)", asMETHODPR(CollisionBox2D, SetSize, (const Vector2&), void), asCALL_THISCALL);
    // void CollisionBox2D::SetSize(float width, float height) | File: ../Urho2D/CollisionBox2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(float, float)", asMETHODPR(CollisionBox2D, SetSize, (float, float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetTemporary(bool)", asMETHODPR(CollisionBox2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_temporary(bool)", asMETHODPR(CollisionBox2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionBox2D", "void SetTrigger(bool)", asMETHODPR(CollisionBox2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_trigger(bool)", asMETHODPR(CollisionBox2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionBox2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionBox2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionBox2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionBox2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionBox2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionBox2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionBox2D", "int WeakRefs() const", asMETHODPR(CollisionBox2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "int get_weakRefs() const", asMETHODPR(CollisionBox2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionBox2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionBox2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionBox2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionBox2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionChain2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void AllocateNetworkState()", asMETHODPR(CollisionChain2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ApplyAttributes()", asMETHODPR(CollisionChain2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionChain2D::CollisionChain2D(Context* context) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_FACTORY, "CollisionChain2D@+ f()", asFUNCTION(CollisionChain2D_CollisionChain2D_Context), asCALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void CreateFixture()", asMETHODPR(CollisionChain2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionChain2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionChain2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_animationEnabled() const", asMETHODPR(CollisionChain2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionChain2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionChain2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionChain2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionChain2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionChain2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionChain2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionChain2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionChain2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionChain2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionChain2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetBlockEvents() const", asMETHODPR(CollisionChain2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const String& GetCategory() const", asMETHODPR(CollisionChain2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const String& get_category() const", asMETHODPR(CollisionChain2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetCategoryBits() const", asMETHODPR(CollisionChain2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_categoryBits() const", asMETHODPR(CollisionChain2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionChain2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetDensity() const", asMETHODPR(CollisionChain2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_density() const", asMETHODPR(CollisionChain2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionChain2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionChain2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetFriction() const", asMETHODPR(CollisionChain2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_friction() const", asMETHODPR(CollisionChain2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionChain2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionChain2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionChain2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionChain2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetGroupIndex() const", asMETHODPR(CollisionChain2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_groupIndex() const", asMETHODPR(CollisionChain2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetID() const", asMETHODPR(CollisionChain2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_id() const", asMETHODPR(CollisionChain2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetInertia() const", asMETHODPR(CollisionChain2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_inertia() const", asMETHODPR(CollisionChain2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionChain2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // bool CollisionChain2D::GetLoop() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool GetLoop() const", asMETHODPR(CollisionChain2D, GetLoop, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_loop() const", asMETHODPR(CollisionChain2D, GetLoop, () const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "int GetMaskBits() const", asMETHODPR(CollisionChain2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_maskBits() const", asMETHODPR(CollisionChain2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetMass() const", asMETHODPR(CollisionChain2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_mass() const", asMETHODPR(CollisionChain2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionChain2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionChain2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Node@+ GetNode() const", asMETHODPR(CollisionChain2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "Node@+ get_node() const", asMETHODPR(CollisionChain2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetNumAttributes() const", asMETHODPR(CollisionChain2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_numAttributes() const", asMETHODPR(CollisionChain2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionChain2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionChain2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionChain2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionChain2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "float GetRestitution() const", asMETHODPR(CollisionChain2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "float get_restitution() const", asMETHODPR(CollisionChain2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "Scene@+ GetScene() const", asMETHODPR(CollisionChain2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionChain2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "StringHash GetType() const", asMETHODPR(CollisionChain2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "StringHash get_type() const", asMETHODPR(CollisionChain2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "const String& GetTypeName() const", asMETHODPR(CollisionChain2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const String& get_typeName() const", asMETHODPR(CollisionChain2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const Vector2& CollisionChain2D::GetVertex(unsigned index) const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "const Vector2& GetVertex(uint) const", asMETHODPR(CollisionChain2D, GetVertex, (unsigned) const, const Vector2&), asCALL_THISCALL);
    // unsigned CollisionChain2D::GetVertexCount() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "uint GetVertexCount() const", asMETHODPR(CollisionChain2D, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_vertexCount() const", asMETHODPR(CollisionChain2D, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Vector2>& CollisionChain2D::GetVertices() const | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionChain2D_GetVertices_void), asCALL_CDECL_OBJFIRST);
    // PODVector<unsigned char> CollisionChain2D::GetVerticesAttr() const | File: ../Urho2D/CollisionChain2D.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasEventHandlers() const", asMETHODPR(CollisionChain2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionChain2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionChain2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsEnabled() const", asMETHODPR(CollisionChain2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_enabled() const", asMETHODPR(CollisionChain2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionChain2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_enabledEffective() const", asMETHODPR(CollisionChain2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionChain2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsReplicated() const", asMETHODPR(CollisionChain2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_replicated() const", asMETHODPR(CollisionChain2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsTemporary() const", asMETHODPR(CollisionChain2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_temporary() const", asMETHODPR(CollisionChain2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool IsTrigger() const", asMETHODPR(CollisionChain2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_trigger() const", asMETHODPR(CollisionChain2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool Load(Deserializer&)", asMETHODPR(CollisionChain2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionChain2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionChain2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionChain2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionChain2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionChain2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionChain2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void OnSetEnabled()", asMETHODPR(CollisionChain2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionChain2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionChain2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionChain2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionChain2D", "int Refs() const", asMETHODPR(CollisionChain2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_refs() const", asMETHODPR(CollisionChain2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionChain2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionChain2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ReleaseFixture()", asMETHODPR(CollisionChain2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionChain2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionChain2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void Remove()", asMETHODPR(CollisionChain2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionChain2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionChain2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionChain2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void ResetToDefault()", asMETHODPR(CollisionChain2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool Save(Serializer&) const", asMETHODPR(CollisionChain2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionChain2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionChain2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionChain2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SendEvent(StringHash)", asMETHODPR(CollisionChain2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionChain2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionChain2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionChain2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAnimationTime(float)", asMETHODPR(CollisionChain2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionChain2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionChain2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionChain2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionChain2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionChain2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionChain2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionChain2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionChain2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetCategoryBits(int)", asMETHODPR(CollisionChain2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_categoryBits(int)", asMETHODPR(CollisionChain2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetDensity(float)", asMETHODPR(CollisionChain2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_density(float)", asMETHODPR(CollisionChain2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetEnabled(bool)", asMETHODPR(CollisionChain2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_enabled(bool)", asMETHODPR(CollisionChain2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetFriction(float)", asMETHODPR(CollisionChain2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_friction(float)", asMETHODPR(CollisionChain2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionChain2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionChain2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetGroupIndex(int)", asMETHODPR(CollisionChain2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_groupIndex(int)", asMETHODPR(CollisionChain2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionChain2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionChain2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionChain2D::SetLoop(bool loop) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetLoop(bool)", asMETHODPR(CollisionChain2D, SetLoop, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_loop(bool)", asMETHODPR(CollisionChain2D, SetLoop, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetMaskBits(int)", asMETHODPR(CollisionChain2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_maskBits(int)", asMETHODPR(CollisionChain2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionChain2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionChain2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionChain2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetRestitution(float)", asMETHODPR(CollisionChain2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_restitution(float)", asMETHODPR(CollisionChain2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetTemporary(bool)", asMETHODPR(CollisionChain2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_temporary(bool)", asMETHODPR(CollisionChain2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetTrigger(bool)", asMETHODPR(CollisionChain2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_trigger(bool)", asMETHODPR(CollisionChain2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void CollisionChain2D::SetVertex(unsigned index, const Vector2& vertex) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertex(uint, const Vector2&in)", asMETHODPR(CollisionChain2D, SetVertex, (unsigned, const Vector2&), void), asCALL_THISCALL);
    // void CollisionChain2D::SetVertexCount(unsigned count) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertexCount(uint)", asMETHODPR(CollisionChain2D, SetVertexCount, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_vertexCount(uint)", asMETHODPR(CollisionChain2D, SetVertexCount, (unsigned), void), asCALL_THISCALL);
    // void CollisionChain2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionChain2D.h
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionChain2D_SetVertices_PODVectorVector2), asCALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionChain2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionChain2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionChain2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionChain2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionChain2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionChain2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionChain2D", "int WeakRefs() const", asMETHODPR(CollisionChain2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "int get_weakRefs() const", asMETHODPR(CollisionChain2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionChain2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionChain2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionChain2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionChain2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionCircle2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void AllocateNetworkState()", asMETHODPR(CollisionCircle2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ApplyAttributes()", asMETHODPR(CollisionCircle2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionCircle2D::CollisionCircle2D(Context* context) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_FACTORY, "CollisionCircle2D@+ f()", asFUNCTION(CollisionCircle2D_CollisionCircle2D_Context), asCALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void CreateFixture()", asMETHODPR(CollisionCircle2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionCircle2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionCircle2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_animationEnabled() const", asMETHODPR(CollisionCircle2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionCircle2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionCircle2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionCircle2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionCircle2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionCircle2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetBlockEvents() const", asMETHODPR(CollisionCircle2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& GetCategory() const", asMETHODPR(CollisionCircle2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& get_category() const", asMETHODPR(CollisionCircle2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetCategoryBits() const", asMETHODPR(CollisionCircle2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_categoryBits() const", asMETHODPR(CollisionCircle2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // const Vector2& CollisionCircle2D::GetCenter() const | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& GetCenter() const", asMETHODPR(CollisionCircle2D, GetCenter, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& get_center() const", asMETHODPR(CollisionCircle2D, GetCenter, () const, const Vector2&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionCircle2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetDensity() const", asMETHODPR(CollisionCircle2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_density() const", asMETHODPR(CollisionCircle2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionCircle2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionCircle2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetFriction() const", asMETHODPR(CollisionCircle2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_friction() const", asMETHODPR(CollisionCircle2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionCircle2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionCircle2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionCircle2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionCircle2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetGroupIndex() const", asMETHODPR(CollisionCircle2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_groupIndex() const", asMETHODPR(CollisionCircle2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetID() const", asMETHODPR(CollisionCircle2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "uint get_id() const", asMETHODPR(CollisionCircle2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetInertia() const", asMETHODPR(CollisionCircle2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_inertia() const", asMETHODPR(CollisionCircle2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionCircle2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int GetMaskBits() const", asMETHODPR(CollisionCircle2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_maskBits() const", asMETHODPR(CollisionCircle2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetMass() const", asMETHODPR(CollisionCircle2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_mass() const", asMETHODPR(CollisionCircle2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionCircle2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionCircle2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Node@+ GetNode() const", asMETHODPR(CollisionCircle2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "Node@+ get_node() const", asMETHODPR(CollisionCircle2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetNumAttributes() const", asMETHODPR(CollisionCircle2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "uint get_numAttributes() const", asMETHODPR(CollisionCircle2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionCircle2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionCircle2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionCircle2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionCircle2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionCircle2D::GetRadius() const | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetRadius() const", asMETHODPR(CollisionCircle2D, GetRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_radius() const", asMETHODPR(CollisionCircle2D, GetRadius, () const, float), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "float GetRestitution() const", asMETHODPR(CollisionCircle2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_restitution() const", asMETHODPR(CollisionCircle2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Scene@+ GetScene() const", asMETHODPR(CollisionCircle2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionCircle2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "StringHash GetType() const", asMETHODPR(CollisionCircle2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "StringHash get_type() const", asMETHODPR(CollisionCircle2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& GetTypeName() const", asMETHODPR(CollisionCircle2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const String& get_typeName() const", asMETHODPR(CollisionCircle2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasEventHandlers() const", asMETHODPR(CollisionCircle2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionCircle2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionCircle2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsEnabled() const", asMETHODPR(CollisionCircle2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_enabled() const", asMETHODPR(CollisionCircle2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionCircle2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_enabledEffective() const", asMETHODPR(CollisionCircle2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionCircle2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsReplicated() const", asMETHODPR(CollisionCircle2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_replicated() const", asMETHODPR(CollisionCircle2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsTemporary() const", asMETHODPR(CollisionCircle2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_temporary() const", asMETHODPR(CollisionCircle2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool IsTrigger() const", asMETHODPR(CollisionCircle2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool get_trigger() const", asMETHODPR(CollisionCircle2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool Load(Deserializer&)", asMETHODPR(CollisionCircle2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionCircle2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionCircle2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionCircle2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionCircle2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionCircle2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionCircle2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void OnSetEnabled()", asMETHODPR(CollisionCircle2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionCircle2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionCircle2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionCircle2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int Refs() const", asMETHODPR(CollisionCircle2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_refs() const", asMETHODPR(CollisionCircle2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionCircle2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionCircle2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ReleaseFixture()", asMETHODPR(CollisionCircle2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionCircle2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionCircle2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void Remove()", asMETHODPR(CollisionCircle2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionCircle2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionCircle2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionCircle2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void ResetToDefault()", asMETHODPR(CollisionCircle2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool Save(Serializer&) const", asMETHODPR(CollisionCircle2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionCircle2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionCircle2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionCircle2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SendEvent(StringHash)", asMETHODPR(CollisionCircle2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionCircle2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionCircle2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionCircle2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAnimationTime(float)", asMETHODPR(CollisionCircle2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionCircle2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionCircle2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionCircle2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionCircle2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionCircle2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionCircle2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionCircle2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionCircle2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCategoryBits(int)", asMETHODPR(CollisionCircle2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_categoryBits(int)", asMETHODPR(CollisionCircle2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionCircle2D::SetCenter(const Vector2& center) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(const Vector2&in)", asMETHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    // void CollisionCircle2D::SetCenter(float x, float y) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(float, float)", asMETHODPR(CollisionCircle2D, SetCenter, (float, float), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetDensity(float)", asMETHODPR(CollisionCircle2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_density(float)", asMETHODPR(CollisionCircle2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetEnabled(bool)", asMETHODPR(CollisionCircle2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_enabled(bool)", asMETHODPR(CollisionCircle2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetFriction(float)", asMETHODPR(CollisionCircle2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_friction(float)", asMETHODPR(CollisionCircle2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionCircle2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionCircle2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetGroupIndex(int)", asMETHODPR(CollisionCircle2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_groupIndex(int)", asMETHODPR(CollisionCircle2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionCircle2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionCircle2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetMaskBits(int)", asMETHODPR(CollisionCircle2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_maskBits(int)", asMETHODPR(CollisionCircle2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionCircle2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionCircle2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionCircle2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionCircle2D::SetRadius(float radius) | File: ../Urho2D/CollisionCircle2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetRadius(float)", asMETHODPR(CollisionCircle2D, SetRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_radius(float)", asMETHODPR(CollisionCircle2D, SetRadius, (float), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetRestitution(float)", asMETHODPR(CollisionCircle2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_restitution(float)", asMETHODPR(CollisionCircle2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetTemporary(bool)", asMETHODPR(CollisionCircle2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_temporary(bool)", asMETHODPR(CollisionCircle2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetTrigger(bool)", asMETHODPR(CollisionCircle2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_trigger(bool)", asMETHODPR(CollisionCircle2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionCircle2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionCircle2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionCircle2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionCircle2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionCircle2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionCircle2D", "int WeakRefs() const", asMETHODPR(CollisionCircle2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "int get_weakRefs() const", asMETHODPR(CollisionCircle2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionCircle2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionCircle2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionCircle2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionCircle2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionEdge2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void AllocateNetworkState()", asMETHODPR(CollisionEdge2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ApplyAttributes()", asMETHODPR(CollisionEdge2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionEdge2D::CollisionEdge2D(Context* context) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_FACTORY, "CollisionEdge2D@+ f()", asFUNCTION(CollisionEdge2D_CollisionEdge2D_Context), asCALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void CreateFixture()", asMETHODPR(CollisionEdge2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionEdge2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionEdge2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_animationEnabled() const", asMETHODPR(CollisionEdge2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionEdge2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionEdge2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionEdge2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionEdge2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionEdge2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetBlockEvents() const", asMETHODPR(CollisionEdge2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& GetCategory() const", asMETHODPR(CollisionEdge2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& get_category() const", asMETHODPR(CollisionEdge2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetCategoryBits() const", asMETHODPR(CollisionEdge2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_categoryBits() const", asMETHODPR(CollisionEdge2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionEdge2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetDensity() const", asMETHODPR(CollisionEdge2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_density() const", asMETHODPR(CollisionEdge2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionEdge2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionEdge2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetFriction() const", asMETHODPR(CollisionEdge2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_friction() const", asMETHODPR(CollisionEdge2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionEdge2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionEdge2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionEdge2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionEdge2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetGroupIndex() const", asMETHODPR(CollisionEdge2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_groupIndex() const", asMETHODPR(CollisionEdge2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetID() const", asMETHODPR(CollisionEdge2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "uint get_id() const", asMETHODPR(CollisionEdge2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetInertia() const", asMETHODPR(CollisionEdge2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_inertia() const", asMETHODPR(CollisionEdge2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionEdge2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int GetMaskBits() const", asMETHODPR(CollisionEdge2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_maskBits() const", asMETHODPR(CollisionEdge2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetMass() const", asMETHODPR(CollisionEdge2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_mass() const", asMETHODPR(CollisionEdge2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionEdge2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionEdge2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Node@+ GetNode() const", asMETHODPR(CollisionEdge2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "Node@+ get_node() const", asMETHODPR(CollisionEdge2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetNumAttributes() const", asMETHODPR(CollisionEdge2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "uint get_numAttributes() const", asMETHODPR(CollisionEdge2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionEdge2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionEdge2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionEdge2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionEdge2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "float GetRestitution() const", asMETHODPR(CollisionEdge2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "float get_restitution() const", asMETHODPR(CollisionEdge2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Scene@+ GetScene() const", asMETHODPR(CollisionEdge2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionEdge2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "StringHash GetType() const", asMETHODPR(CollisionEdge2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "StringHash get_type() const", asMETHODPR(CollisionEdge2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& GetTypeName() const", asMETHODPR(CollisionEdge2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const String& get_typeName() const", asMETHODPR(CollisionEdge2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const Vector2& CollisionEdge2D::GetVertex1() const | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& GetVertex1() const", asMETHODPR(CollisionEdge2D, GetVertex1, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex1() const", asMETHODPR(CollisionEdge2D, GetVertex1, () const, const Vector2&), asCALL_THISCALL);
    // const Vector2& CollisionEdge2D::GetVertex2() const | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& GetVertex2() const", asMETHODPR(CollisionEdge2D, GetVertex2, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex2() const", asMETHODPR(CollisionEdge2D, GetVertex2, () const, const Vector2&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasEventHandlers() const", asMETHODPR(CollisionEdge2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionEdge2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionEdge2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsEnabled() const", asMETHODPR(CollisionEdge2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_enabled() const", asMETHODPR(CollisionEdge2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionEdge2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_enabledEffective() const", asMETHODPR(CollisionEdge2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionEdge2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsReplicated() const", asMETHODPR(CollisionEdge2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_replicated() const", asMETHODPR(CollisionEdge2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsTemporary() const", asMETHODPR(CollisionEdge2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_temporary() const", asMETHODPR(CollisionEdge2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool IsTrigger() const", asMETHODPR(CollisionEdge2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool get_trigger() const", asMETHODPR(CollisionEdge2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool Load(Deserializer&)", asMETHODPR(CollisionEdge2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionEdge2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionEdge2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionEdge2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionEdge2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionEdge2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionEdge2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void OnSetEnabled()", asMETHODPR(CollisionEdge2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionEdge2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionEdge2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionEdge2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int Refs() const", asMETHODPR(CollisionEdge2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_refs() const", asMETHODPR(CollisionEdge2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionEdge2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionEdge2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ReleaseFixture()", asMETHODPR(CollisionEdge2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionEdge2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionEdge2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void Remove()", asMETHODPR(CollisionEdge2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionEdge2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionEdge2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionEdge2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void ResetToDefault()", asMETHODPR(CollisionEdge2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool Save(Serializer&) const", asMETHODPR(CollisionEdge2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionEdge2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionEdge2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionEdge2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SendEvent(StringHash)", asMETHODPR(CollisionEdge2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionEdge2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionEdge2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionEdge2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAnimationTime(float)", asMETHODPR(CollisionEdge2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionEdge2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionEdge2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionEdge2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionEdge2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionEdge2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionEdge2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionEdge2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionEdge2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetCategoryBits(int)", asMETHODPR(CollisionEdge2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_categoryBits(int)", asMETHODPR(CollisionEdge2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetDensity(float)", asMETHODPR(CollisionEdge2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_density(float)", asMETHODPR(CollisionEdge2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetEnabled(bool)", asMETHODPR(CollisionEdge2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_enabled(bool)", asMETHODPR(CollisionEdge2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetFriction(float)", asMETHODPR(CollisionEdge2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_friction(float)", asMETHODPR(CollisionEdge2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionEdge2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionEdge2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetGroupIndex(int)", asMETHODPR(CollisionEdge2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_groupIndex(int)", asMETHODPR(CollisionEdge2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionEdge2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionEdge2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetMaskBits(int)", asMETHODPR(CollisionEdge2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_maskBits(int)", asMETHODPR(CollisionEdge2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionEdge2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionEdge2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionEdge2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetRestitution(float)", asMETHODPR(CollisionEdge2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_restitution(float)", asMETHODPR(CollisionEdge2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetTemporary(bool)", asMETHODPR(CollisionEdge2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_temporary(bool)", asMETHODPR(CollisionEdge2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetTrigger(bool)", asMETHODPR(CollisionEdge2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_trigger(bool)", asMETHODPR(CollisionEdge2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void CollisionEdge2D::SetVertex1(const Vector2& vertex) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertex1(const Vector2&in)", asMETHODPR(CollisionEdge2D, SetVertex1, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex1(const Vector2&in)", asMETHODPR(CollisionEdge2D, SetVertex1, (const Vector2&), void), asCALL_THISCALL);
    // void CollisionEdge2D::SetVertex2(const Vector2& vertex) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertex2(const Vector2&in)", asMETHODPR(CollisionEdge2D, SetVertex2, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex2(const Vector2&in)", asMETHODPR(CollisionEdge2D, SetVertex2, (const Vector2&), void), asCALL_THISCALL);
    // void CollisionEdge2D::SetVertices(const Vector2& vertex1, const Vector2& vertex2) | File: ../Urho2D/CollisionEdge2D.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertices(const Vector2&in, const Vector2&in)", asMETHODPR(CollisionEdge2D, SetVertices, (const Vector2&, const Vector2&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionEdge2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionEdge2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionEdge2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionEdge2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionEdge2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionEdge2D", "int WeakRefs() const", asMETHODPR(CollisionEdge2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "int get_weakRefs() const", asMETHODPR(CollisionEdge2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionEdge2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionEdge2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionEdge2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionEdge2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionPolygon2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void AllocateNetworkState()", asMETHODPR(CollisionPolygon2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ApplyAttributes()", asMETHODPR(CollisionPolygon2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionPolygon2D::CollisionPolygon2D(Context* context) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_FACTORY, "CollisionPolygon2D@+ f()", asFUNCTION(CollisionPolygon2D_CollisionPolygon2D_Context), asCALL_CDECL);
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void CreateFixture()", asMETHODPR(CollisionPolygon2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionPolygon2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionPolygon2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_animationEnabled() const", asMETHODPR(CollisionPolygon2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionPolygon2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionPolygon2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionPolygon2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionPolygon2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionPolygon2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetBlockEvents() const", asMETHODPR(CollisionPolygon2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& GetCategory() const", asMETHODPR(CollisionPolygon2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& get_category() const", asMETHODPR(CollisionPolygon2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetCategoryBits() const", asMETHODPR(CollisionPolygon2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_categoryBits() const", asMETHODPR(CollisionPolygon2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionPolygon2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetDensity() const", asMETHODPR(CollisionPolygon2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_density() const", asMETHODPR(CollisionPolygon2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionPolygon2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionPolygon2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetFriction() const", asMETHODPR(CollisionPolygon2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_friction() const", asMETHODPR(CollisionPolygon2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionPolygon2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionPolygon2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionPolygon2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionPolygon2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetGroupIndex() const", asMETHODPR(CollisionPolygon2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_groupIndex() const", asMETHODPR(CollisionPolygon2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetID() const", asMETHODPR(CollisionPolygon2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_id() const", asMETHODPR(CollisionPolygon2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetInertia() const", asMETHODPR(CollisionPolygon2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_inertia() const", asMETHODPR(CollisionPolygon2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionPolygon2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int GetMaskBits() const", asMETHODPR(CollisionPolygon2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_maskBits() const", asMETHODPR(CollisionPolygon2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetMass() const", asMETHODPR(CollisionPolygon2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_mass() const", asMETHODPR(CollisionPolygon2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionPolygon2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionPolygon2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Node@+ GetNode() const", asMETHODPR(CollisionPolygon2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Node@+ get_node() const", asMETHODPR(CollisionPolygon2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetNumAttributes() const", asMETHODPR(CollisionPolygon2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_numAttributes() const", asMETHODPR(CollisionPolygon2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionPolygon2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionPolygon2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionPolygon2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionPolygon2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "float GetRestitution() const", asMETHODPR(CollisionPolygon2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "float get_restitution() const", asMETHODPR(CollisionPolygon2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Scene@+ GetScene() const", asMETHODPR(CollisionPolygon2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionPolygon2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "StringHash GetType() const", asMETHODPR(CollisionPolygon2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "StringHash get_type() const", asMETHODPR(CollisionPolygon2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& GetTypeName() const", asMETHODPR(CollisionPolygon2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const String& get_typeName() const", asMETHODPR(CollisionPolygon2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const Vector2& CollisionPolygon2D::GetVertex(unsigned index) const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Vector2& GetVertex(uint) const", asMETHODPR(CollisionPolygon2D, GetVertex, (unsigned) const, const Vector2&), asCALL_THISCALL);
    // unsigned CollisionPolygon2D::GetVertexCount() const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint GetVertexCount() const", asMETHODPR(CollisionPolygon2D, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_vertexCount() const", asMETHODPR(CollisionPolygon2D, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Vector2>& CollisionPolygon2D::GetVertices() const | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionPolygon2D_GetVertices_void), asCALL_CDECL_OBJFIRST);
    // PODVector<unsigned char> CollisionPolygon2D::GetVerticesAttr() const | File: ../Urho2D/CollisionPolygon2D.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasEventHandlers() const", asMETHODPR(CollisionPolygon2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionPolygon2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionPolygon2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsEnabled() const", asMETHODPR(CollisionPolygon2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_enabled() const", asMETHODPR(CollisionPolygon2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionPolygon2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_enabledEffective() const", asMETHODPR(CollisionPolygon2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionPolygon2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsReplicated() const", asMETHODPR(CollisionPolygon2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_replicated() const", asMETHODPR(CollisionPolygon2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsTemporary() const", asMETHODPR(CollisionPolygon2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_temporary() const", asMETHODPR(CollisionPolygon2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool IsTrigger() const", asMETHODPR(CollisionPolygon2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool get_trigger() const", asMETHODPR(CollisionPolygon2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool Load(Deserializer&)", asMETHODPR(CollisionPolygon2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionPolygon2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionPolygon2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionPolygon2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionPolygon2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionPolygon2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionPolygon2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void OnSetEnabled()", asMETHODPR(CollisionPolygon2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionPolygon2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionPolygon2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionPolygon2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int Refs() const", asMETHODPR(CollisionPolygon2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_refs() const", asMETHODPR(CollisionPolygon2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionPolygon2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionPolygon2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ReleaseFixture()", asMETHODPR(CollisionPolygon2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionPolygon2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionPolygon2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void Remove()", asMETHODPR(CollisionPolygon2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionPolygon2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionPolygon2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionPolygon2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void ResetToDefault()", asMETHODPR(CollisionPolygon2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool Save(Serializer&) const", asMETHODPR(CollisionPolygon2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionPolygon2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionPolygon2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionPolygon2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SendEvent(StringHash)", asMETHODPR(CollisionPolygon2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionPolygon2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionPolygon2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionPolygon2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAnimationTime(float)", asMETHODPR(CollisionPolygon2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionPolygon2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionPolygon2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionPolygon2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionPolygon2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionPolygon2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionPolygon2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionPolygon2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionPolygon2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetCategoryBits(int)", asMETHODPR(CollisionPolygon2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_categoryBits(int)", asMETHODPR(CollisionPolygon2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetDensity(float)", asMETHODPR(CollisionPolygon2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_density(float)", asMETHODPR(CollisionPolygon2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetEnabled(bool)", asMETHODPR(CollisionPolygon2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_enabled(bool)", asMETHODPR(CollisionPolygon2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetFriction(float)", asMETHODPR(CollisionPolygon2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_friction(float)", asMETHODPR(CollisionPolygon2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionPolygon2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionPolygon2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetGroupIndex(int)", asMETHODPR(CollisionPolygon2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_groupIndex(int)", asMETHODPR(CollisionPolygon2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionPolygon2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionPolygon2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetMaskBits(int)", asMETHODPR(CollisionPolygon2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_maskBits(int)", asMETHODPR(CollisionPolygon2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionPolygon2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionPolygon2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionPolygon2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetRestitution(float)", asMETHODPR(CollisionPolygon2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_restitution(float)", asMETHODPR(CollisionPolygon2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetTemporary(bool)", asMETHODPR(CollisionPolygon2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_temporary(bool)", asMETHODPR(CollisionPolygon2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetTrigger(bool)", asMETHODPR(CollisionPolygon2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_trigger(bool)", asMETHODPR(CollisionPolygon2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void CollisionPolygon2D::SetVertex(unsigned index, const Vector2& vertex) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertex(uint, const Vector2&in)", asMETHODPR(CollisionPolygon2D, SetVertex, (unsigned, const Vector2&), void), asCALL_THISCALL);
    // void CollisionPolygon2D::SetVertexCount(unsigned count) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertexCount(uint)", asMETHODPR(CollisionPolygon2D, SetVertexCount, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_vertexCount(uint)", asMETHODPR(CollisionPolygon2D, SetVertexCount, (unsigned), void), asCALL_THISCALL);
    // void CollisionPolygon2D::SetVertices(const PODVector<Vector2>& vertices) | File: ../Urho2D/CollisionPolygon2D.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionPolygon2D_SetVertices_PODVectorVector2), asCALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionPolygon2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionPolygon2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionPolygon2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionPolygon2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionPolygon2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "int WeakRefs() const", asMETHODPR(CollisionPolygon2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "int get_weakRefs() const", asMETHODPR(CollisionPolygon2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionPolygon2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionPolygon2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionPolygon2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionPolygon2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionShape, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void AllocateNetworkState()", asMETHODPR(CollisionShape, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void CollisionShape::ApplyAttributes() override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void ApplyAttributes()", asMETHODPR(CollisionShape, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CollisionShape::CollisionShape(Context* context) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_FACTORY, "CollisionShape@+ f()", asFUNCTION(CollisionShape_CollisionShape_Context), asCALL_CDECL);
    // void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionShape, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetAnimationEnabled() const", asMETHODPR(CollisionShape, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_animationEnabled() const", asMETHODPR(CollisionShape, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttribute(uint) const", asMETHODPR(CollisionShape, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Variant get_attributes(uint) const", asMETHODPR(CollisionShape, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionShape, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionShape, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionShape, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionShape, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionShape, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionShape, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionShape, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionShape, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetBlockEvents() const", asMETHODPR(CollisionShape, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const String& GetCategory() const", asMETHODPR(CollisionShape, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const String& get_category() const", asMETHODPR(CollisionShape, GetCategory, () const, const String&), asCALL_THISCALL);
    // btCollisionShape* CollisionShape::GetCollisionShape() const | File: ../Physics/CollisionShape.h
    // Error: type "btCollisionShape*" can not automatically bind
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionShape, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("CollisionShape", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionShape, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "Object@+ GetEventSender() const", asMETHODPR(CollisionShape, GetEventSender, () const, Object*), asCALL_THISCALL);
    // CollisionGeometryData* CollisionShape::GetGeometryData() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "CollisionGeometryData@+ GetGeometryData() const", asMETHODPR(CollisionShape, GetGeometryData, () const, CollisionGeometryData*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionShape, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionShape, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionShape, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionShape, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetID() const", asMETHODPR(CollisionShape, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_id() const", asMETHODPR(CollisionShape, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionShape, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned CollisionShape::GetLodLevel() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetLodLevel() const", asMETHODPR(CollisionShape, GetLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_lodLevel() const", asMETHODPR(CollisionShape, GetLodLevel, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape::GetMargin() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "float GetMargin() const", asMETHODPR(CollisionShape, GetMargin, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "float get_margin() const", asMETHODPR(CollisionShape, GetMargin, () const, float), asCALL_THISCALL);
    // Model* CollisionShape::GetModel() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "Model@+ GetModel() const", asMETHODPR(CollisionShape, GetModel, () const, Model*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Model@+ get_model() const", asMETHODPR(CollisionShape, GetModel, () const, Model*), asCALL_THISCALL);
    // ResourceRef CollisionShape::GetModelAttr() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "ResourceRef GetModelAttr() const", asMETHODPR(CollisionShape, GetModelAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Node@+ GetNode() const", asMETHODPR(CollisionShape, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Node@+ get_node() const", asMETHODPR(CollisionShape, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetNumAttributes() const", asMETHODPR(CollisionShape, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_numAttributes() const", asMETHODPR(CollisionShape, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionShape, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionShape, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionShape, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionShape, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // PhysicsWorld* CollisionShape::GetPhysicsWorld() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "PhysicsWorld@+ GetPhysicsWorld() const", asMETHODPR(CollisionShape, GetPhysicsWorld, () const, PhysicsWorld*), asCALL_THISCALL);
    // const Vector3& CollisionShape::GetPosition() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& GetPosition() const", asMETHODPR(CollisionShape, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_position() const", asMETHODPR(CollisionShape, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& CollisionShape::GetRotation() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& GetRotation() const", asMETHODPR(CollisionShape, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& get_rotation() const", asMETHODPR(CollisionShape, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "Scene@+ GetScene() const", asMETHODPR(CollisionShape, GetScene, () const, Scene*), asCALL_THISCALL);
    // ShapeType CollisionShape::GetShapeType() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "ShapeType GetShapeType() const", asMETHODPR(CollisionShape, GetShapeType, () const, ShapeType), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ShapeType get_shapeType() const", asMETHODPR(CollisionShape, GetShapeType, () const, ShapeType), asCALL_THISCALL);
    // const Vector3& CollisionShape::GetSize() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& GetSize() const", asMETHODPR(CollisionShape, GetSize, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_size() const", asMETHODPR(CollisionShape, GetSize, () const, const Vector3&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionShape, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "StringHash GetType() const", asMETHODPR(CollisionShape, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "StringHash get_type() const", asMETHODPR(CollisionShape, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "const String& GetTypeName() const", asMETHODPR(CollisionShape, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const String& get_typeName() const", asMETHODPR(CollisionShape, GetTypeName, () const, const String&), asCALL_THISCALL);
    // BoundingBox CollisionShape::GetWorldBoundingBox() const | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox GetWorldBoundingBox() const", asMETHODPR(CollisionShape, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox get_worldBoundingBox() const", asMETHODPR(CollisionShape, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasEventHandlers() const", asMETHODPR(CollisionShape, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionShape, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionShape, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsEnabled() const", asMETHODPR(CollisionShape, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_enabled() const", asMETHODPR(CollisionShape, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsEnabledEffective() const", asMETHODPR(CollisionShape, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_enabledEffective() const", asMETHODPR(CollisionShape, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionShape, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsReplicated() const", asMETHODPR(CollisionShape, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_replicated() const", asMETHODPR(CollisionShape, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool IsTemporary() const", asMETHODPR(CollisionShape, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_temporary() const", asMETHODPR(CollisionShape, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool Load(Deserializer&)", asMETHODPR(CollisionShape, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionShape, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionShape, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void MarkNetworkUpdate()", asMETHODPR(CollisionShape, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void CollisionShape::NotifyRigidBody(bool updateMass=true) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void NotifyRigidBody(bool = true)", asMETHODPR(CollisionShape, NotifyRigidBody, (bool), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionShape, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionShape, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionShape, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape::OnSetEnabled() override | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void OnSetEnabled()", asMETHODPR(CollisionShape, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void PrepareNetworkUpdate()", asMETHODPR(CollisionShape, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionShape, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionShape, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape", "int Refs() const", asMETHODPR(CollisionShape, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "int get_refs() const", asMETHODPR(CollisionShape, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionShape::RegisterObject(Context* context) | File: ../Physics/CollisionShape.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionShape, ReleaseRef, (), void), asCALL_THISCALL);
    // void CollisionShape::ReleaseShape() | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void ReleaseShape()", asMETHODPR(CollisionShape, ReleaseShape, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void Remove()", asMETHODPR(CollisionShape, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionShape, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveInstanceDefault()", asMETHODPR(CollisionShape, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void RemoveObjectAnimation()", asMETHODPR(CollisionShape, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void ResetToDefault()", asMETHODPR(CollisionShape, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool Save(Serializer&) const", asMETHODPR(CollisionShape, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionShape, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionShape, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionShape, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SendEvent(StringHash)", asMETHODPR(CollisionShape, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionShape, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionShape, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_animationEnabled(bool)", asMETHODPR(CollisionShape, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAnimationTime(float)", asMETHODPR(CollisionShape, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionShape, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionShape, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionShape, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionShape, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionShape, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionShape, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionShape, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SetBlockEvents(bool)", asMETHODPR(CollisionShape, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape::SetBox(const Vector3& size, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetBox(const Vector3&in, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetBox, (const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCapsule(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCapsule(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCapsule, (float, float, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCone(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCone(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCone, (float, float, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetConvexHull(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetConvexHull(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetConvexHull, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCustomConvexHull(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomConvexHull(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCustomConvexHull, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCustomGImpactMesh(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomGImpactMesh(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCustomGImpactMesh, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCustomTriangleMesh(CustomGeometry* custom, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomTriangleMesh(CustomGeometry@+, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCustomTriangleMesh, (CustomGeometry*, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetCylinder(float diameter, float height, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetCylinder(float, float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetCylinder, (float, float, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape", "void SetEnabled(bool)", asMETHODPR(CollisionShape, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_enabled(bool)", asMETHODPR(CollisionShape, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape::SetGImpactMesh(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetGImpactMesh(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetGImpactMesh, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionShape, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionShape, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetInstanceDefault(bool)", asMETHODPR(CollisionShape, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionShape, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape::SetLodLevel(unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetLodLevel(uint)", asMETHODPR(CollisionShape, SetLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_lodLevel(uint)", asMETHODPR(CollisionShape, SetLodLevel, (unsigned), void), asCALL_THISCALL);
    // void CollisionShape::SetMargin(float margin) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetMargin(float)", asMETHODPR(CollisionShape, SetMargin, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_margin(float)", asMETHODPR(CollisionShape, SetMargin, (float), void), asCALL_THISCALL);
    // void CollisionShape::SetModel(Model* model) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetModel(Model@+)", asMETHODPR(CollisionShape, SetModel, (Model*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_model(Model@+)", asMETHODPR(CollisionShape, SetModel, (Model*), void), asCALL_THISCALL);
    // void CollisionShape::SetModelAttr(const ResourceRef& value) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetModelAttr(const ResourceRef&in)", asMETHODPR(CollisionShape, SetModelAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionShape, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionShape, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionShape, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape::SetPosition(const Vector3& position) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetPosition(const Vector3&in)", asMETHODPR(CollisionShape, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_position(const Vector3&in)", asMETHODPR(CollisionShape, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void CollisionShape::SetRotation(const Quaternion& rotation) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetRotation(const Quaternion&in)", asMETHODPR(CollisionShape, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_rotation(const Quaternion&in)", asMETHODPR(CollisionShape, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetShapeType(ShapeType type) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetShapeType(ShapeType)", asMETHODPR(CollisionShape, SetShapeType, (ShapeType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_shapeType(ShapeType)", asMETHODPR(CollisionShape, SetShapeType, (ShapeType), void), asCALL_THISCALL);
    // void CollisionShape::SetSize(const Vector3& size) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetSize(const Vector3&in)", asMETHODPR(CollisionShape, SetSize, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_size(const Vector3&in)", asMETHODPR(CollisionShape, SetSize, (const Vector3&), void), asCALL_THISCALL);
    // void CollisionShape::SetSphere(float diameter, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetSphere(float, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetSphere, (float, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetStaticPlane(const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetStaticPlane(const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetStaticPlane, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTemporary(bool)", asMETHODPR(CollisionShape, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_temporary(bool)", asMETHODPR(CollisionShape, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape::SetTerrain(unsigned lodLevel=0) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTerrain(uint = 0)", asMETHODPR(CollisionShape, SetTerrain, (unsigned), void), asCALL_THISCALL);
    // void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(CollisionShape, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void CollisionShape::SetTriangleMesh(Model* model, unsigned lodLevel=0, const Vector3& scale=Vector3::ONE, const Vector3& position=Vector3::ZERO, const Quaternion& rotation=Quaternion::IDENTITY) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("CollisionShape", "void SetTriangleMesh(Model@+, uint = 0, const Vector3&in = Vector3::ONE, const Vector3&in = Vector3::ZERO, const Quaternion&in = Quaternion::IDENTITY)", asMETHODPR(CollisionShape, SetTriangleMesh, (Model*, unsigned, const Vector3&, const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionShape, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionShape_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionShape, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionShape, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionShape, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape", "int WeakRefs() const", asMETHODPR(CollisionShape, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "int get_weakRefs() const", asMETHODPR(CollisionShape, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionShape, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionShape, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionShape, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionShape2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionShape2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void AllocateNetworkState()", asMETHODPR(CollisionShape2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ApplyAttributes()", asMETHODPR(CollisionShape2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void CollisionShape2D::CreateFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void CreateFixture()", asMETHODPR(CollisionShape2D, CreateFixture, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CollisionShape2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetAnimationEnabled() const", asMETHODPR(CollisionShape2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_animationEnabled() const", asMETHODPR(CollisionShape2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttribute(uint) const", asMETHODPR(CollisionShape2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Variant get_attributes(uint) const", asMETHODPR(CollisionShape2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttribute(const String&in) const", asMETHODPR(CollisionShape2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CollisionShape2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CollisionShape2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CollisionShape2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CollisionShape2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(CollisionShape2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(CollisionShape2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CollisionShape2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetBlockEvents() const", asMETHODPR(CollisionShape2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const String& GetCategory() const", asMETHODPR(CollisionShape2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const String& get_category() const", asMETHODPR(CollisionShape2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // int CollisionShape2D::GetCategoryBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetCategoryBits() const", asMETHODPR(CollisionShape2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_categoryBits() const", asMETHODPR(CollisionShape2D, GetCategoryBits, () const, int), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(CollisionShape2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float CollisionShape2D::GetDensity() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetDensity() const", asMETHODPR(CollisionShape2D, GetDensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_density() const", asMETHODPR(CollisionShape2D, GetDensity, () const, float), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "VariantMap& GetEventDataMap() const", asMETHODPR(CollisionShape2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "Object@+ GetEventSender() const", asMETHODPR(CollisionShape2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // b2Fixture* CollisionShape2D::GetFixture() const | File: ../Urho2D/CollisionShape2D.h
    // Error: type "b2Fixture*" can not automatically bind
    // float CollisionShape2D::GetFriction() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetFriction() const", asMETHODPR(CollisionShape2D, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_friction() const", asMETHODPR(CollisionShape2D, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CollisionShape2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CollisionShape2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(CollisionShape2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const VariantMap& get_globalVars() const", asMETHODPR(CollisionShape2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int CollisionShape2D::GetGroupIndex() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetGroupIndex() const", asMETHODPR(CollisionShape2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_groupIndex() const", asMETHODPR(CollisionShape2D, GetGroupIndex, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetID() const", asMETHODPR(CollisionShape2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "uint get_id() const", asMETHODPR(CollisionShape2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float CollisionShape2D::GetInertia() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetInertia() const", asMETHODPR(CollisionShape2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_inertia() const", asMETHODPR(CollisionShape2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CollisionShape2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int CollisionShape2D::GetMaskBits() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "int GetMaskBits() const", asMETHODPR(CollisionShape2D, GetMaskBits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_maskBits() const", asMETHODPR(CollisionShape2D, GetMaskBits, () const, int), asCALL_THISCALL);
    // float CollisionShape2D::GetMass() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetMass() const", asMETHODPR(CollisionShape2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_mass() const", asMETHODPR(CollisionShape2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 CollisionShape2D::GetMassCenter() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "Vector2 GetMassCenter() const", asMETHODPR(CollisionShape2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Vector2 get_massCenter() const", asMETHODPR(CollisionShape2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Node@+ GetNode() const", asMETHODPR(CollisionShape2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "Node@+ get_node() const", asMETHODPR(CollisionShape2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetNumAttributes() const", asMETHODPR(CollisionShape2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "uint get_numAttributes() const", asMETHODPR(CollisionShape2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "uint GetNumNetworkAttributes() const", asMETHODPR(CollisionShape2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CollisionShape2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CollisionShape2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CollisionShape2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float CollisionShape2D::GetRestitution() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "float GetRestitution() const", asMETHODPR(CollisionShape2D, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "float get_restitution() const", asMETHODPR(CollisionShape2D, GetRestitution, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "Scene@+ GetScene() const", asMETHODPR(CollisionShape2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CollisionShape2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "StringHash GetType() const", asMETHODPR(CollisionShape2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "StringHash get_type() const", asMETHODPR(CollisionShape2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "const String& GetTypeName() const", asMETHODPR(CollisionShape2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "const String& get_typeName() const", asMETHODPR(CollisionShape2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasEventHandlers() const", asMETHODPR(CollisionShape2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CollisionShape2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CollisionShape2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsEnabled() const", asMETHODPR(CollisionShape2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_enabled() const", asMETHODPR(CollisionShape2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsEnabledEffective() const", asMETHODPR(CollisionShape2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_enabledEffective() const", asMETHODPR(CollisionShape2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(CollisionShape2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsReplicated() const", asMETHODPR(CollisionShape2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_replicated() const", asMETHODPR(CollisionShape2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsTemporary() const", asMETHODPR(CollisionShape2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_temporary() const", asMETHODPR(CollisionShape2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool CollisionShape2D::IsTrigger() const | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool IsTrigger() const", asMETHODPR(CollisionShape2D, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool get_trigger() const", asMETHODPR(CollisionShape2D, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool Load(Deserializer&)", asMETHODPR(CollisionShape2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CollisionShape2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(CollisionShape2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void MarkNetworkUpdate()", asMETHODPR(CollisionShape2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CollisionShape2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CollisionShape2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CollisionShape2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::OnSetEnabled() override | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void OnSetEnabled()", asMETHODPR(CollisionShape2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void PrepareNetworkUpdate()", asMETHODPR(CollisionShape2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CollisionShape2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CollisionShape2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape2D", "int Refs() const", asMETHODPR(CollisionShape2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_refs() const", asMETHODPR(CollisionShape2D, Refs, () const, int), asCALL_THISCALL);
    // static void CollisionShape2D::RegisterObject(Context* context) | File: ../Urho2D/CollisionShape2D.h
    // Not registered because have @nobind mark
    // void CollisionShape2D::ReleaseFixture() | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ReleaseFixture()", asMETHODPR(CollisionShape2D, ReleaseFixture, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionShape2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionShape2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void Remove()", asMETHODPR(CollisionShape2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CollisionShape2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveInstanceDefault()", asMETHODPR(CollisionShape2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void RemoveObjectAnimation()", asMETHODPR(CollisionShape2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void ResetToDefault()", asMETHODPR(CollisionShape2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool Save(Serializer&) const", asMETHODPR(CollisionShape2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveDefaultAttributes() const", asMETHODPR(CollisionShape2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(CollisionShape2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SaveXML(XMLElement&) const", asMETHODPR(CollisionShape2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SendEvent(StringHash)", asMETHODPR(CollisionShape2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CollisionShape2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAnimationEnabled(bool)", asMETHODPR(CollisionShape2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_animationEnabled(bool)", asMETHODPR(CollisionShape2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAnimationTime(float)", asMETHODPR(CollisionShape2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CollisionShape2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CollisionShape2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CollisionShape2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CollisionShape2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CollisionShape2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CollisionShape2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CollisionShape2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetBlockEvents(bool)", asMETHODPR(CollisionShape2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetCategoryBits(int categoryBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetCategoryBits(int)", asMETHODPR(CollisionShape2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_categoryBits(int)", asMETHODPR(CollisionShape2D, SetCategoryBits, (int), void), asCALL_THISCALL);
    // void CollisionShape2D::SetDensity(float density) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetDensity(float)", asMETHODPR(CollisionShape2D, SetDensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_density(float)", asMETHODPR(CollisionShape2D, SetDensity, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetEnabled(bool)", asMETHODPR(CollisionShape2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_enabled(bool)", asMETHODPR(CollisionShape2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetFriction(float friction) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetFriction(float)", asMETHODPR(CollisionShape2D, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_friction(float)", asMETHODPR(CollisionShape2D, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CollisionShape2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CollisionShape2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetGroupIndex(int groupIndex) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetGroupIndex(int)", asMETHODPR(CollisionShape2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_groupIndex(int)", asMETHODPR(CollisionShape2D, SetGroupIndex, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetInstanceDefault(bool)", asMETHODPR(CollisionShape2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CollisionShape2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetMaskBits(int maskBits) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetMaskBits(int)", asMETHODPR(CollisionShape2D, SetMaskBits, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_maskBits(int)", asMETHODPR(CollisionShape2D, SetMaskBits, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionShape2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CollisionShape2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CollisionShape2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CollisionShape2D::SetRestitution(float restitution) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetRestitution(float)", asMETHODPR(CollisionShape2D, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_restitution(float)", asMETHODPR(CollisionShape2D, SetRestitution, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetTemporary(bool)", asMETHODPR(CollisionShape2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_temporary(bool)", asMETHODPR(CollisionShape2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CollisionShape2D::SetTrigger(bool trigger) | File: ../Urho2D/CollisionShape2D.h
    engine->RegisterObjectMethod("CollisionShape2D", "void SetTrigger(bool)", asMETHODPR(CollisionShape2D, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "void set_trigger(bool)", asMETHODPR(CollisionShape2D, SetTrigger, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromAllEvents()", asMETHODPR(CollisionShape2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CollisionShape2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CollisionShape2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CollisionShape2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CollisionShape2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CollisionShape2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionShape2D", "int WeakRefs() const", asMETHODPR(CollisionShape2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape2D", "int get_weakRefs() const", asMETHODPR(CollisionShape2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CollisionShape2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CollisionShape2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CollisionShape2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CollisionShape2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Color", "Color Abs() const", asMETHODPR(Color, Abs, () const, Color), asCALL_THISCALL);
    // float Color::Average() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Average() const", asMETHODPR(Color, Average, () const, float), asCALL_THISCALL);
    // void Color::Bounds(float* min, float* max, bool clipped=false) const | File: ../Math/Color.h
    // Error: type "float*" can not automatically bind
    // float Color::Chroma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Chroma() const", asMETHODPR(Color, Chroma, () const, float), asCALL_THISCALL);
    // void Color::Clip(bool clipAlpha=false) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void Clip(bool = false)", asMETHODPR(Color, Clip, (bool), void), asCALL_THISCALL);
    // Color::Color(const Color& color) noexcept=default | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(Color_Color_Color), asCALL_CDECL_OBJFIRST);
    // Color::Color(const Color& color, float a) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in, float)", asFUNCTION(Color_Color_Color_float), asCALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Color_Color_float_float_float), asCALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b, float a) noexcept | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Color_Color_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Color::Color(const float* data) noexcept | File: ../Math/Color.h
    // Error: type "const float*" can not automatically bind
    // explicit Color::Color(unsigned color, const ChannelMask& mask=ABGR) | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // explicit Color::Color(const Vector3& color) | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Color_Color_Vector3), asCALL_CDECL_OBJFIRST);
    // explicit Color::Color(const Vector4& color) | File: ../Math/Color.h
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Color_Color_Vector4), asCALL_CDECL_OBJFIRST);
    // static float Color::ConvertGammaToLinear(float value) | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalFunction("float ConvertGammaToLinear(float)", asFUNCTIONPR(Color::ConvertGammaToLinear, (float), float), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static float Color::ConvertLinearToGamma(float value) | File: ../Math/Color.h
    engine->SetDefaultNamespace("Color");
    engine->RegisterGlobalFunction("float ConvertLinearToGamma(float)", asFUNCTIONPR(Color::ConvertLinearToGamma, (float), float), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const float* Color::Data() const | File: ../Math/Color.h
    // Error: type "const float*" can not automatically bind
    // bool Color::Equals(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "bool Equals(const Color&in) const", asMETHODPR(Color, Equals, (const Color&) const, bool), asCALL_THISCALL);
    // void Color::FromHSL(float h, float s, float l, float a=1.0f) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromHSL(float, float, float, float = 1.0f)", asMETHODPR(Color, FromHSL, (float, float, float, float), void), asCALL_THISCALL);
    // void Color::FromHSV(float h, float s, float v, float a=1.0f) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromHSV(float, float, float, float = 1.0f)", asMETHODPR(Color, FromHSV, (float, float, float, float), void), asCALL_THISCALL);
    // void Color::FromUInt(unsigned color) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void FromUInt(uint)", asMETHODPR(Color, FromUInt, (unsigned), void), asCALL_THISCALL);
    // void Color::FromUIntMask(unsigned color, const ChannelMask& mask) | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // Color Color::GammaToLinear() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color GammaToLinear() const", asMETHODPR(Color, GammaToLinear, () const, Color), asCALL_THISCALL);
    // float Color::Hue() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Hue() const", asMETHODPR(Color, Hue, () const, float), asCALL_THISCALL);
    // void Color::Invert(bool invertAlpha=false) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "void Invert(bool = false)", asMETHODPR(Color, Invert, (bool), void), asCALL_THISCALL);
    // Color Color::Lerp(const Color& rhs, float t) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color Lerp(const Color&in, float) const", asMETHODPR(Color, Lerp, (const Color&, float) const, Color), asCALL_THISCALL);
    // float Color::Lightness() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Lightness() const", asMETHODPR(Color, Lightness, () const, float), asCALL_THISCALL);
    // Color Color::LinearToGamma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color LinearToGamma() const", asMETHODPR(Color, LinearToGamma, () const, Color), asCALL_THISCALL);
    // float Color::Luma() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Luma() const", asMETHODPR(Color, Luma, () const, float), asCALL_THISCALL);
    // float Color::MaxRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float MaxRGB() const", asMETHODPR(Color, MaxRGB, () const, float), asCALL_THISCALL);
    // float Color::MinRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float MinRGB() const", asMETHODPR(Color, MinRGB, () const, float), asCALL_THISCALL);
    // Color Color::operator*(float rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", asMETHODPR(Color, operator*, (float) const, Color), asCALL_THISCALL);
    // Color Color::operator+(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color&in) const", asMETHODPR(Color, operator+, (const Color&) const, Color), asCALL_THISCALL);
    // Color& Color::operator+=(const Color& rhs) | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color& opAddAssign(const Color&in)", asMETHODPR(Color, operator+=, (const Color&), Color&), asCALL_THISCALL);
    // Color Color::operator-() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opNeg() const", asMETHODPR(Color, operator-, () const, Color), asCALL_THISCALL);
    // Color Color::operator-(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color opSub(const Color&in) const", asMETHODPR(Color, operator-, (const Color&) const, Color), asCALL_THISCALL);
    // Color& Color::operator=(const Color& rhs) noexcept=default | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Color& opAssign(const Color&in)", asMETHODPR(Color, operator=, (const Color&), Color&), asCALL_THISCALL);
    // bool Color::operator==(const Color& rhs) const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color&in) const", asMETHODPR(Color, operator==, (const Color&) const, bool), asCALL_THISCALL);
    // float Color::Range() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Range() const", asMETHODPR(Color, Range, () const, float), asCALL_THISCALL);
    // float Color::SaturationHSL() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SaturationHSL() const", asMETHODPR(Color, SaturationHSL, () const, float), asCALL_THISCALL);
    // float Color::SaturationHSV() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SaturationHSV() const", asMETHODPR(Color, SaturationHSV, () const, float), asCALL_THISCALL);
    // float Color::SumRGB() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float SumRGB() const", asMETHODPR(Color, SumRGB, () const, float), asCALL_THISCALL);
    // unsigned Color::ToHash() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToHash() const", asMETHODPR(Color, ToHash, () const, unsigned), asCALL_THISCALL);
    // Vector3 Color::ToHSL() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToHSL() const", asMETHODPR(Color, ToHSL, () const, Vector3), asCALL_THISCALL);
    // Vector3 Color::ToHSV() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToHSV() const", asMETHODPR(Color, ToHSV, () const, Vector3), asCALL_THISCALL);
    // String Color::ToString() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "String ToString() const", asMETHODPR(Color, ToString, () const, String), asCALL_THISCALL);
    // unsigned Color::ToUInt() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToUInt() const", asMETHODPR(Color, ToUInt, () const, unsigned), asCALL_THISCALL);
    // unsigned Color::ToUIntArgb() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "uint ToUIntArgb() const", asMETHODPR(Color, ToUIntArgb, () const, unsigned), asCALL_THISCALL);
    // unsigned Color::ToUIntMask(const ChannelMask& mask) const | File: ../Math/Color.h
    // Error: type "const ChannelMask&" can not automatically bind
    // Vector3 Color::ToVector3() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector3 ToVector3() const", asMETHODPR(Color, ToVector3, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 get_rgb() const", asMETHODPR(Color, ToVector3, () const, Vector3), asCALL_THISCALL);
    // Vector4 Color::ToVector4() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "Vector4 ToVector4() const", asMETHODPR(Color, ToVector4, () const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector4 get_rgba() const", asMETHODPR(Color, ToVector4, () const, Vector4), asCALL_THISCALL);
    // float Color::Value() const | File: ../Math/Color.h
    engine->RegisterObjectMethod("Color", "float Value() const", asMETHODPR(Color, Value, () const, float), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Color
    REGISTER_MANUAL_PART_Color(Color, "Color")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_ADDREF, "void f()", asMETHODPR(Component, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void AllocateNetworkState()", asMETHODPR(Component, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void ApplyAttributes()", asMETHODPR(Component, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Component::Component(Context* context) | File: ../Scene/Component.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_FACTORY, "Component@+ f()", asFUNCTION(Component_Component_Context), asCALL_CDECL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Component, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool GetAnimationEnabled() const", asMETHODPR(Component, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_animationEnabled() const", asMETHODPR(Component, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttribute(uint) const", asMETHODPR(Component, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Variant get_attributes(uint) const", asMETHODPR(Component, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttribute(const String&in) const", asMETHODPR(Component, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Component, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Component, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Component, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Component, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttributeDefault(uint) const", asMETHODPR(Component, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Variant get_attributeDefaults(uint) const", asMETHODPR(Component, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Component, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool GetBlockEvents() const", asMETHODPR(Component, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const String& GetCategory() const", asMETHODPR(Component, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const String& get_category() const", asMETHODPR(Component, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Component@+ GetComponent(StringHash) const", asMETHODPR(Component, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("Component", "VariantMap& GetEventDataMap() const", asMETHODPR(Component, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "Object@+ GetEventSender() const", asMETHODPR(Component, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Component, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Component, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const VariantMap& GetGlobalVars() const", asMETHODPR(Component, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const VariantMap& get_globalVars() const", asMETHODPR(Component, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "uint GetID() const", asMETHODPR(Component, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "uint get_id() const", asMETHODPR(Component, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Component, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Node@+ GetNode() const", asMETHODPR(Component, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "Node@+ get_node() const", asMETHODPR(Component, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "uint GetNumAttributes() const", asMETHODPR(Component, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "uint get_numAttributes() const", asMETHODPR(Component, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "uint GetNumNetworkAttributes() const", asMETHODPR(Component, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Component, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Component, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Component, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "Scene@+ GetScene() const", asMETHODPR(Component, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Component, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "StringHash GetType() const", asMETHODPR(Component, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "StringHash get_type() const", asMETHODPR(Component, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "const String& GetTypeName() const", asMETHODPR(Component, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "const String& get_typeName() const", asMETHODPR(Component, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasEventHandlers() const", asMETHODPR(Component, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Component, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Component, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsEnabled() const", asMETHODPR(Component, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_enabled() const", asMETHODPR(Component, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsEnabledEffective() const", asMETHODPR(Component, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_enabledEffective() const", asMETHODPR(Component, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "bool IsInstanceOf(StringHash) const", asMETHODPR(Component, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool IsReplicated() const", asMETHODPR(Component, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_replicated() const", asMETHODPR(Component, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool IsTemporary() const", asMETHODPR(Component, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool get_temporary() const", asMETHODPR(Component, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool Load(Deserializer&)", asMETHODPR(Component, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Component, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "bool LoadXML(const XMLElement&in)", asMETHODPR(Component, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void MarkNetworkUpdate()", asMETHODPR(Component, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Component, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Component, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Component, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void OnSetEnabled()", asMETHODPR(Component, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void PrepareNetworkUpdate()", asMETHODPR(Component, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Component, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Component, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Component", "int Refs() const", asMETHODPR(Component, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "int get_refs() const", asMETHODPR(Component, Refs, () const, int), asCALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Component", asBEHAVE_RELEASE, "void f()", asMETHODPR(Component, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void Remove()", asMETHODPR(Component, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Component, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void RemoveInstanceDefault()", asMETHODPR(Component, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void RemoveObjectAnimation()", asMETHODPR(Component, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void ResetToDefault()", asMETHODPR(Component, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool Save(Serializer&) const", asMETHODPR(Component, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SaveDefaultAttributes() const", asMETHODPR(Component, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool SaveJSON(JSONValue&) const", asMETHODPR(Component, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "bool SaveXML(XMLElement&) const", asMETHODPR(Component, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SendEvent(StringHash)", asMETHODPR(Component, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Component, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAnimationEnabled(bool)", asMETHODPR(Component, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_animationEnabled(bool)", asMETHODPR(Component, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAnimationTime(float)", asMETHODPR(Component, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Component, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Component, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Component, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Component, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Component, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Component, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Component, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SetBlockEvents(bool)", asMETHODPR(Component, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Component", "void SetEnabled(bool)", asMETHODPR(Component, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_enabled(bool)", asMETHODPR(Component, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Component, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Component, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetInstanceDefault(bool)", asMETHODPR(Component, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Component, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Component, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Component, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Component", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Component, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void SetTemporary(bool)", asMETHODPR(Component, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "void set_temporary(bool)", asMETHODPR(Component, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromAllEvents()", asMETHODPR(Component, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Component, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Component, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Component", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Component, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Component", "int WeakRefs() const", asMETHODPR(Component, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Component", "int get_weakRefs() const", asMETHODPR(Component, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Component, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Component, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Component", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Component, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Condition", "void Set()", asMETHODPR(Condition, Set, (), void), asCALL_THISCALL);
    // void Condition::Wait() | File: ../Core/Condition.h
    engine->RegisterObjectMethod("Condition", "void Wait()", asMETHODPR(Condition, Wait, (), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_ADDREF, "void f()", asMETHODPR(Connection, AddRef, (), void), asCALL_THISCALL);
    // void Connection::Ban() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void Ban()", asMETHODPR(Connection, Ban, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Connection::ConfigureNetworkSimulator(int latencyMs, float packetLoss) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void ConfigureNetworkSimulator(int, float)", asMETHODPR(Connection, ConfigureNetworkSimulator, (int, float), void), asCALL_THISCALL);
    // Connection::Connection(Context* context, bool isClient, const SLNet::AddressOrGUID& address, SLNet::RakPeerInterface* peer) | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Connection::Disconnect(int waitMSec=0) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void Disconnect(int = 0)", asMETHODPR(Connection, Disconnect, (int), void), asCALL_THISCALL);
    // String Connection::GetAddress() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "String GetAddress() const", asMETHODPR(Connection, GetAddress, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "String get_address() const", asMETHODPR(Connection, GetAddress, () const, String), asCALL_THISCALL);
    // const SLNet::AddressOrGUID& Connection::GetAddressOrGUID() const | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool GetBlockEvents() const", asMETHODPR(Connection, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // float Connection::GetBytesInPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetBytesInPerSec() const", asMETHODPR(Connection, GetBytesInPerSec, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_bytesInPerSec() const", asMETHODPR(Connection, GetBytesInPerSec, () const, float), asCALL_THISCALL);
    // float Connection::GetBytesOutPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetBytesOutPerSec() const", asMETHODPR(Connection, GetBytesOutPerSec, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_bytesOutPerSec() const", asMETHODPR(Connection, GetBytesOutPerSec, () const, float), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const String& GetCategory() const", asMETHODPR(Connection, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_category() const", asMETHODPR(Connection, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const Controls& Connection::GetControls() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Controls& GetControls() const", asMETHODPR(Connection, GetControls, () const, const Controls&), asCALL_THISCALL);
    // const String& Connection::GetDownloadName() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const String& GetDownloadName() const", asMETHODPR(Connection, GetDownloadName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_downloadName() const", asMETHODPR(Connection, GetDownloadName, () const, const String&), asCALL_THISCALL);
    // float Connection::GetDownloadProgress() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetDownloadProgress() const", asMETHODPR(Connection, GetDownloadProgress, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_downloadProgress() const", asMETHODPR(Connection, GetDownloadProgress, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "VariantMap& GetEventDataMap() const", asMETHODPR(Connection, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "Object@+ GetEventSender() const", asMETHODPR(Connection, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Connection, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Connection, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const VariantMap& GetGlobalVars() const", asMETHODPR(Connection, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const VariantMap& get_globalVars() const", asMETHODPR(Connection, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // VariantMap& Connection::GetIdentity() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "VariantMap& GetIdentity()", asMETHODPR(Connection, GetIdentity, (), VariantMap&), asCALL_THISCALL);
    // unsigned Connection::GetLastHeardTime() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint GetLastHeardTime() const", asMETHODPR(Connection, GetLastHeardTime, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_lastHeardTime() const", asMETHODPR(Connection, GetLastHeardTime, () const, unsigned), asCALL_THISCALL);
    // bool Connection::GetLogStatistics() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool GetLogStatistics() const", asMETHODPR(Connection, GetLogStatistics, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_logStatistics() const", asMETHODPR(Connection, GetLogStatistics, () const, bool), asCALL_THISCALL);
    // unsigned Connection::GetNumDownloads() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint GetNumDownloads() const", asMETHODPR(Connection, GetNumDownloads, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint get_numDownloads() const", asMETHODPR(Connection, GetNumDownloads, () const, unsigned), asCALL_THISCALL);
    // int Connection::GetPacketsInPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "int GetPacketsInPerSec() const", asMETHODPR(Connection, GetPacketsInPerSec, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_packetsInPerSec() const", asMETHODPR(Connection, GetPacketsInPerSec, () const, int), asCALL_THISCALL);
    // int Connection::GetPacketsOutPerSec() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "int GetPacketsOutPerSec() const", asMETHODPR(Connection, GetPacketsOutPerSec, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_packetsOutPerSec() const", asMETHODPR(Connection, GetPacketsOutPerSec, () const, int), asCALL_THISCALL);
    // PacketType Connection::GetPacketType(bool reliable, bool inOrder) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "PacketType GetPacketType(bool, bool)", asMETHODPR(Connection, GetPacketType, (bool, bool), PacketType), asCALL_THISCALL);
    // unsigned short Connection::GetPort() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint16 GetPort() const", asMETHODPR(Connection, GetPort, () const, unsigned short), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "uint16 get_port() const", asMETHODPR(Connection, GetPort, () const, unsigned short), asCALL_THISCALL);
    // const Vector3& Connection::GetPosition() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Vector3& GetPosition() const", asMETHODPR(Connection, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Vector3& get_position() const", asMETHODPR(Connection, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& Connection::GetRotation() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "const Quaternion& GetRotation() const", asMETHODPR(Connection, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const Quaternion& get_rotation() const", asMETHODPR(Connection, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // float Connection::GetRoundTripTime() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "float GetRoundTripTime() const", asMETHODPR(Connection, GetRoundTripTime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "float get_roundTripTime() const", asMETHODPR(Connection, GetRoundTripTime, () const, float), asCALL_THISCALL);
    // Scene* Connection::GetScene() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "Scene@+ GetScene() const", asMETHODPR(Connection, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "Scene@+ get_scene() const", asMETHODPR(Connection, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Connection, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned char Connection::GetTimeStamp() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "uint8 GetTimeStamp() const", asMETHODPR(Connection, GetTimeStamp, () const, unsigned char), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "StringHash GetType() const", asMETHODPR(Connection, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "StringHash get_type() const", asMETHODPR(Connection, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "const String& GetTypeName() const", asMETHODPR(Connection, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "const String& get_typeName() const", asMETHODPR(Connection, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasEventHandlers() const", asMETHODPR(Connection, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Connection, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Connection, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Connection::IsClient() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsClient() const", asMETHODPR(Connection, IsClient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_client() const", asMETHODPR(Connection, IsClient, () const, bool), asCALL_THISCALL);
    // bool Connection::IsConnected() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsConnected() const", asMETHODPR(Connection, IsConnected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connected() const", asMETHODPR(Connection, IsConnected, () const, bool), asCALL_THISCALL);
    // bool Connection::IsConnectPending() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsConnectPending() const", asMETHODPR(Connection, IsConnectPending, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_connectPending() const", asMETHODPR(Connection, IsConnectPending, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "bool IsInstanceOf(StringHash) const", asMETHODPR(Connection, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Connection::IsSceneLoaded() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "bool IsSceneLoaded() const", asMETHODPR(Connection, IsSceneLoaded, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "bool get_sceneLoaded() const", asMETHODPR(Connection, IsSceneLoaded, () const, bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Connection, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // bool Connection::ProcessMessage(int msgID, MemoryBuffer& buffer) | File: ../Network/Connection.h
    // Error: type "MemoryBuffer" can not automatically bind bacause have @nobind mark
    // void Connection::ProcessPendingLatestData() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void ProcessPendingLatestData()", asMETHODPR(Connection, ProcessPendingLatestData, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Connection", "int Refs() const", asMETHODPR(Connection, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_refs() const", asMETHODPR(Connection, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Connection", asBEHAVE_RELEASE, "void f()", asMETHODPR(Connection, ReleaseRef, (), void), asCALL_THISCALL);
    // void Connection::SendAllBuffers() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendAllBuffers()", asMETHODPR(Connection, SendAllBuffers, (), void), asCALL_THISCALL);
    // void Connection::SendBuffer(PacketType type) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendBuffer(PacketType)", asMETHODPR(Connection, SendBuffer, (PacketType), void), asCALL_THISCALL);
    // void Connection::SendClientUpdate() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendClientUpdate()", asMETHODPR(Connection, SendClientUpdate, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SendEvent(StringHash)", asMETHODPR(Connection, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Connection, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID=0) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendMessage(int, bool, bool, const VectorBuffer&in, uint = 0)", asMETHODPR(Connection, SendMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), asCALL_THISCALL);
    // void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID=0) | File: ../Network/Connection.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Connection::SendPackages() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendPackages()", asMETHODPR(Connection, SendPackages, (), void), asCALL_THISCALL);
    // void Connection::SendPackageToClient(PackageFile* package) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendPackageToClient(PackageFile@+)", asMETHODPR(Connection, SendPackageToClient, (PackageFile*), void), asCALL_THISCALL);
    // void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(StringHash, bool, const VariantMap&in = VariantMap())", asMETHODPR(Connection, SendRemoteEvent, (StringHash, bool, const VariantMap&), void), asCALL_THISCALL);
    // void Connection::SendRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvent(Node@+, StringHash, bool, const VariantMap&in = VariantMap())", asMETHODPR(Connection, SendRemoteEvent, (Node*, StringHash, bool, const VariantMap&), void), asCALL_THISCALL);
    // void Connection::SendRemoteEvents() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendRemoteEvents()", asMETHODPR(Connection, SendRemoteEvents, (), void), asCALL_THISCALL);
    // void Connection::SendServerUpdate() | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SendServerUpdate()", asMETHODPR(Connection, SendServerUpdate, (), void), asCALL_THISCALL);
    // void Connection::SetAddressOrGUID(const SLNet::AddressOrGUID& addr) | File: ../Network/Connection.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SetBlockEvents(bool)", asMETHODPR(Connection, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Connection::SetConnectPending(bool connectPending) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetConnectPending(bool)", asMETHODPR(Connection, SetConnectPending, (bool), void), asCALL_THISCALL);
    // void Connection::SetControls(const Controls& newControls) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetControls(const Controls&in)", asMETHODPR(Connection, SetControls, (const Controls&), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Connection, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Connection, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Connection::SetIdentity(const VariantMap& identity) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetIdentity(const VariantMap&in)", asMETHODPR(Connection, SetIdentity, (const VariantMap&), void), asCALL_THISCALL);
    // void Connection::SetLogStatistics(bool enable) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetLogStatistics(bool)", asMETHODPR(Connection, SetLogStatistics, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_logStatistics(bool)", asMETHODPR(Connection, SetLogStatistics, (bool), void), asCALL_THISCALL);
    // void Connection::SetPacketSizeLimit(int limit) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetPacketSizeLimit(int)", asMETHODPR(Connection, SetPacketSizeLimit, (int), void), asCALL_THISCALL);
    // void Connection::SetPosition(const Vector3& position) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetPosition(const Vector3&in)", asMETHODPR(Connection, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_position(const Vector3&in)", asMETHODPR(Connection, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Connection::SetRotation(const Quaternion& rotation) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetRotation(const Quaternion&in)", asMETHODPR(Connection, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_rotation(const Quaternion&in)", asMETHODPR(Connection, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Connection::SetScene(Scene* newScene) | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "void SetScene(Scene@+)", asMETHODPR(Connection, SetScene, (Scene*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "void set_scene(Scene@+)", asMETHODPR(Connection, SetScene, (Scene*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String Connection::ToString() const | File: ../Network/Connection.h
    engine->RegisterObjectMethod("Connection", "String ToString() const", asMETHODPR(Connection, ToString, () const, String), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromAllEvents()", asMETHODPR(Connection, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Connection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Connection, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Connection, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Connection", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Connection, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Connection", "int WeakRefs() const", asMETHODPR(Connection, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Connection", "int get_weakRefs() const", asMETHODPR(Connection, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Console", "void AddAutoComplete(const String&in)", asMETHODPR(Console, AddAutoComplete, (const String&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_ADDREF, "void f()", asMETHODPR(Console, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit Console::Console(Context* context) | File: ../Engine/Console.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_FACTORY, "Console@+ f()", asFUNCTION(Console_Console_Context), asCALL_CDECL);
    // void Console::CopySelectedRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void CopySelectedRows() const", asMETHODPR(Console, CopySelectedRows, () const, void), asCALL_THISCALL);
    // BorderImage* Console::GetBackground() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "BorderImage@+ GetBackground() const", asMETHODPR(Console, GetBackground, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "BorderImage@+ get_background() const", asMETHODPR(Console, GetBackground, () const, BorderImage*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool GetBlockEvents() const", asMETHODPR(Console, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const String& GetCategory() const", asMETHODPR(Console, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_category() const", asMETHODPR(Console, GetCategory, () const, const String&), asCALL_THISCALL);
    // Button* Console::GetCloseButton() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "Button@+ GetCloseButton() const", asMETHODPR(Console, GetCloseButton, () const, Button*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "Button@+ get_closeButton() const", asMETHODPR(Console, GetCloseButton, () const, Button*), asCALL_THISCALL);
    // const String& Console::GetCommandInterpreter() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "const String& GetCommandInterpreter() const", asMETHODPR(Console, GetCommandInterpreter, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_commandInterpreter() const", asMETHODPR(Console, GetCommandInterpreter, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* Console::GetDefaultStyle() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "XMLFile@+ GetDefaultStyle() const", asMETHODPR(Console, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "XMLFile@+ get_defaultStyle() const", asMETHODPR(Console, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "VariantMap& GetEventDataMap() const", asMETHODPR(Console, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "Object@+ GetEventSender() const", asMETHODPR(Console, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool Console::GetFocusOnShow() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool GetFocusOnShow() const", asMETHODPR(Console, GetFocusOnShow, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_focusOnShow() const", asMETHODPR(Console, GetFocusOnShow, () const, bool), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Console, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Console, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const VariantMap& GetGlobalVars() const", asMETHODPR(Console, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const VariantMap& get_globalVars() const", asMETHODPR(Console, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Console::GetHistoryPosition() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetHistoryPosition() const", asMETHODPR(Console, GetHistoryPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_historyPosition() const", asMETHODPR(Console, GetHistoryPosition, () const, unsigned), asCALL_THISCALL);
    // const String& Console::GetHistoryRow(unsigned index) const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "const String& GetHistoryRow(uint) const", asMETHODPR(Console, GetHistoryRow, (unsigned) const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_historyRow(uint) const", asMETHODPR(Console, GetHistoryRow, (unsigned) const, const String&), asCALL_THISCALL);
    // LineEdit* Console::GetLineEdit() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "LineEdit@+ GetLineEdit() const", asMETHODPR(Console, GetLineEdit, () const, LineEdit*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "LineEdit@+ get_lineEdit() const", asMETHODPR(Console, GetLineEdit, () const, LineEdit*), asCALL_THISCALL);
    // unsigned Console::GetNumBufferedRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumBufferedRows() const", asMETHODPR(Console, GetNumBufferedRows, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numBufferedRows() const", asMETHODPR(Console, GetNumBufferedRows, () const, unsigned), asCALL_THISCALL);
    // unsigned Console::GetNumHistoryRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumHistoryRows() const", asMETHODPR(Console, GetNumHistoryRows, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numHistoryRows() const", asMETHODPR(Console, GetNumHistoryRows, () const, unsigned), asCALL_THISCALL);
    // unsigned Console::GetNumRows() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "uint GetNumRows() const", asMETHODPR(Console, GetNumRows, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numRows() const", asMETHODPR(Console, GetNumRows, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Console, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "StringHash GetType() const", asMETHODPR(Console, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "StringHash get_type() const", asMETHODPR(Console, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "const String& GetTypeName() const", asMETHODPR(Console, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_typeName() const", asMETHODPR(Console, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasEventHandlers() const", asMETHODPR(Console, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Console, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Console, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Console::IsAutoVisibleOnError() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool IsAutoVisibleOnError() const", asMETHODPR(Console, IsAutoVisibleOnError, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_autoVisibleOnError() const", asMETHODPR(Console, IsAutoVisibleOnError, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "bool IsInstanceOf(StringHash) const", asMETHODPR(Console, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Console::IsVisible() const | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "bool IsVisible() const", asMETHODPR(Console, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_visible() const", asMETHODPR(Console, IsVisible, () const, bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Console, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Console", "int Refs() const", asMETHODPR(Console, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "int get_refs() const", asMETHODPR(Console, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Console", asBEHAVE_RELEASE, "void f()", asMETHODPR(Console, ReleaseRef, (), void), asCALL_THISCALL);
    // void Console::RemoveAutoComplete(const String& option) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void RemoveAutoComplete(const String&in)", asMETHODPR(Console, RemoveAutoComplete, (const String&), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SendEvent(StringHash)", asMETHODPR(Console, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Console, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Console::SetAutoVisibleOnError(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetAutoVisibleOnError(bool)", asMETHODPR(Console, SetAutoVisibleOnError, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_autoVisibleOnError(bool)", asMETHODPR(Console, SetAutoVisibleOnError, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SetBlockEvents(bool)", asMETHODPR(Console, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Console::SetCommandInterpreter(const String& interpreter) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetCommandInterpreter(const String&in)", asMETHODPR(Console, SetCommandInterpreter, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_commandInterpreter(const String&in)", asMETHODPR(Console, SetCommandInterpreter, (const String&), void), asCALL_THISCALL);
    // void Console::SetDefaultStyle(XMLFile* style) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Console, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Console, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void Console::SetFocusOnShow(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetFocusOnShow(bool)", asMETHODPR(Console, SetFocusOnShow, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_focusOnShow(bool)", asMETHODPR(Console, SetFocusOnShow, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Console, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Console, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Console::SetNumBufferedRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumBufferedRows(uint)", asMETHODPR(Console, SetNumBufferedRows, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numBufferedRows(uint)", asMETHODPR(Console, SetNumBufferedRows, (unsigned), void), asCALL_THISCALL);
    // void Console::SetNumHistoryRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumHistoryRows(uint)", asMETHODPR(Console, SetNumHistoryRows, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numHistoryRows(uint)", asMETHODPR(Console, SetNumHistoryRows, (unsigned), void), asCALL_THISCALL);
    // void Console::SetNumRows(unsigned rows) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetNumRows(uint)", asMETHODPR(Console, SetNumRows, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numRows(uint)", asMETHODPR(Console, SetNumRows, (unsigned), void), asCALL_THISCALL);
    // void Console::SetVisible(bool enable) | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void SetVisible(bool)", asMETHODPR(Console, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_visible(bool)", asMETHODPR(Console, SetVisible, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Console::Toggle() | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void Toggle()", asMETHODPR(Console, Toggle, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromAllEvents()", asMETHODPR(Console, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Console_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Console, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Console, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Console", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Console, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Console::UpdateElements() | File: ../Engine/Console.h
    engine->RegisterObjectMethod("Console", "void UpdateElements()", asMETHODPR(Console, UpdateElements, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Console", "int WeakRefs() const", asMETHODPR(Console, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "int get_weakRefs() const", asMETHODPR(Console, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConstantBuffer, AddRef, (), void), asCALL_THISCALL);
    // void ConstantBuffer::Apply() | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void Apply()", asMETHODPR(ConstantBuffer, Apply, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "void ClearDataLost()", asMETHODPR(ConstantBuffer, ClearDataLost, (), void), asCALL_THISCALL);
    // explicit ConstantBuffer::ConstantBuffer(Context* context) | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_FACTORY, "ConstantBuffer@+ f()", asFUNCTION(ConstantBuffer_ConstantBuffer_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool GetBlockEvents() const", asMETHODPR(ConstantBuffer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const String& GetCategory() const", asMETHODPR(ConstantBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const String& get_category() const", asMETHODPR(ConstantBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "VariantMap& GetEventDataMap() const", asMETHODPR(ConstantBuffer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "Object@+ GetEventSender() const", asMETHODPR(ConstantBuffer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ConstantBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ConstantBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const VariantMap& GetGlobalVars() const", asMETHODPR(ConstantBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const VariantMap& get_globalVars() const", asMETHODPR(ConstantBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "uint GetGPUObjectName() const", asMETHODPR(ConstantBuffer, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "Graphics@+ GetGraphics() const", asMETHODPR(ConstantBuffer, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // unsigned ConstantBuffer::GetSize() const | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "uint GetSize() const", asMETHODPR(ConstantBuffer, GetSize, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ConstantBuffer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "StringHash GetType() const", asMETHODPR(ConstantBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "StringHash get_type() const", asMETHODPR(ConstantBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "const String& GetTypeName() const", asMETHODPR(ConstantBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "const String& get_typeName() const", asMETHODPR(ConstantBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasEventHandlers() const", asMETHODPR(ConstantBuffer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasPendingData() const", asMETHODPR(ConstantBuffer, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ConstantBuffer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ConstantBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsDataLost() const", asMETHODPR(ConstantBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "bool get_dataLost() const", asMETHODPR(ConstantBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool ConstantBuffer::IsDirty() const | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsDirty() const", asMETHODPR(ConstantBuffer, IsDirty, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool IsInstanceOf(StringHash) const", asMETHODPR(ConstantBuffer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnDeviceLost()", asMETHODPR(ConstantBuffer, OnDeviceLost, (), void), asCALL_THISCALL);
    // void ConstantBuffer::OnDeviceReset() override | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnDeviceReset()", asMETHODPR(ConstantBuffer, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ConstantBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstantBuffer", "int Refs() const", asMETHODPR(ConstantBuffer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "int get_refs() const", asMETHODPR(ConstantBuffer, Refs, () const, int), asCALL_THISCALL);
    // void ConstantBuffer::Release() override | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "void Release()", asMETHODPR(ConstantBuffer, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConstantBuffer", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConstantBuffer, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SendEvent(StringHash)", asMETHODPR(ConstantBuffer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ConstantBuffer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SetBlockEvents(bool)", asMETHODPR(ConstantBuffer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ConstantBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ConstantBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void ConstantBuffer::SetParameter(unsigned offset, unsigned size, const void* data) | File: ../Graphics/ConstantBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool ConstantBuffer::SetSize(unsigned size) | File: ../Graphics/ConstantBuffer.h
    engine->RegisterObjectMethod("ConstantBuffer", "bool SetSize(uint)", asMETHODPR(ConstantBuffer, SetSize, (unsigned), bool), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromAllEvents()", asMETHODPR(ConstantBuffer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ConstantBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ConstantBuffer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ConstantBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ConstantBuffer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ConstantBuffer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConstantBuffer", "int WeakRefs() const", asMETHODPR(ConstantBuffer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstantBuffer", "int get_weakRefs() const", asMETHODPR(ConstantBuffer, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Context", asBEHAVE_ADDREF, "void f()", asMETHODPR(Context, AddRef, (), void), asCALL_THISCALL);
    // Context::Context() | File: ../Core/Context.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_FACTORY, "Context@+ f()", asFUNCTION(Context_Context_void), asCALL_CDECL);
    // void Context::CopyBaseAttributes(StringHash baseType, StringHash derivedType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void CopyBaseAttributes(StringHash, StringHash)", asMETHODPR(Context, CopyBaseAttributes, (StringHash, StringHash), void), asCALL_THISCALL);
    // template<class T, class U> void Context::CopyBaseAttributes() | File: ../Core/Context.h
    // Not registered because template
    // template<class T> SharedPtr<T> Context::CreateObject() | File: ../Core/Context.h
    // Not registered because template
    // SharedPtr<Object> Context::CreateObject(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ CreateObject(StringHash)", asFUNCTION(Context_CreateObject_StringHash), asCALL_CDECL_OBJFIRST);
    // const HashMap<StringHash, Vector<AttributeInfo>>& Context::GetAllAttributes() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, Vector<AttributeInfo>>&" can not automatically bind
    // AttributeInfo* Context::GetAttribute(StringHash objectType, const char* name) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> AttributeInfo*  Context::GetAttribute(const char* name) | File: ../Core/Context.h
    // Not registered because template
    // const Vector<AttributeInfo>* Context::GetAttributes(StringHash type) const | File: ../Core/Context.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // VariantMap& Context::GetEventDataMap() | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "VariantMap& GetEventDataMap()", asMETHODPR(Context, GetEventDataMap, (), VariantMap&), asCALL_THISCALL);
    // EventHandler* Context::GetEventHandler() const | File: ../Core/Context.h
    // Error: type "EventHandler*" can not automatically bind
    // EventReceiverGroup* Context::GetEventReceivers(Object* sender, StringHash eventType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "EventReceiverGroup@+ GetEventReceivers(Object@+, StringHash)", asMETHODPR(Context, GetEventReceivers, (Object*, StringHash), EventReceiverGroup*), asCALL_THISCALL);
    // EventReceiverGroup* Context::GetEventReceivers(StringHash eventType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "EventReceiverGroup@+ GetEventReceivers(StringHash)", asMETHODPR(Context, GetEventReceivers, (StringHash), EventReceiverGroup*), asCALL_THISCALL);
    // Object* Context::GetEventSender() const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ GetEventSender() const", asMETHODPR(Context, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Context::GetGlobalVar(StringHash key) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Context, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Context::GetGlobalVars() const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const VariantMap& GetGlobalVars() const", asMETHODPR(Context, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector<AttributeInfo>* Context::GetNetworkAttributes(StringHash type) const | File: ../Core/Context.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const HashMap<String, Vector<StringHash>>& Context::GetObjectCategories() const | File: ../Core/Context.h
    // Error: type "const HashMap<String, Vector<StringHash>>&" can not automatically bind
    // const HashMap<StringHash, SharedPtr<ObjectFactory>>& Context::GetObjectFactories() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, SharedPtr<ObjectFactory>>&" can not automatically bind
    // Object* Context::GetSubsystem(StringHash type) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Context, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Context::GetSubsystem() const | File: ../Core/Context.h
    // Not registered because template
    // const HashMap<StringHash, SharedPtr<Object>>& Context::GetSubsystems() const | File: ../Core/Context.h
    // Error: type "const HashMap<StringHash, SharedPtr<Object>>&" can not automatically bind
    // const String& Context::GetTypeName(StringHash objectType) const | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "const String& GetTypeName(StringHash) const", asMETHODPR(Context, GetTypeName, (StringHash) const, const String&), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Context", "int Refs() const", asMETHODPR(Context, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Context", "int get_refs() const", asMETHODPR(Context, Refs, () const, int), asCALL_THISCALL);
    // AttributeHandle Context::RegisterAttribute(StringHash objectType, const AttributeInfo& attr) | File: ../Core/Context.h
    // Error: type "AttributeHandle" can not automatically bind bacause have @nobind mark
    // template<class T> AttributeHandle Context::RegisterAttribute(const AttributeInfo& attr) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RegisterFactory(ObjectFactory* factory) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RegisterFactory(ObjectFactory@+)", asMETHODPR(Context, RegisterFactory, (ObjectFactory*), void), asCALL_THISCALL);
    // void Context::RegisterFactory(ObjectFactory* factory, const char* category) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::RegisterFactory() | File: ../Core/Context.h
    // Not registered because template
    // template<class T> void Context::RegisterFactory(const char* category) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RegisterSubsystem(Object* object) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RegisterSubsystem(Object@+)", asMETHODPR(Context, RegisterSubsystem, (Object*), void), asCALL_THISCALL);
    // template<class T> T*  Context::RegisterSubsystem() | File: ../Core/Context.h
    // Not registered because template
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Context", asBEHAVE_RELEASE, "void f()", asMETHODPR(Context, ReleaseRef, (), void), asCALL_THISCALL);
    // void Context::ReleaseSDL() | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void ReleaseSDL()", asMETHODPR(Context, ReleaseSDL, (), void), asCALL_THISCALL);
    // void Context::RemoveAllAttributes(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RemoveAllAttributes(StringHash)", asMETHODPR(Context, RemoveAllAttributes, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Context::RemoveAllAttributes() | File: ../Core/Context.h
    // Not registered because template
    // void Context::RemoveAttribute(StringHash objectType, const char* name) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::RemoveAttribute(const char* name) | File: ../Core/Context.h
    // Not registered because template
    // void Context::RemoveSubsystem(StringHash objectType) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void RemoveSubsystem(StringHash)", asMETHODPR(Context, RemoveSubsystem, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Context::RemoveSubsystem() | File: ../Core/Context.h
    // Not registered because template
    // bool Context::RequireSDL(unsigned int sdlFlags) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "bool RequireSDL(uint)", asMETHODPR(Context, RequireSDL, (unsigned int), bool), asCALL_THISCALL);
    // void Context::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Context.h
    engine->RegisterObjectMethod("Context", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Context, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Context::UpdateAttributeDefaultValue(StringHash objectType, const char* name, const Variant& defaultValue) | File: ../Core/Context.h
    // Error: type "const char*" can not automatically bind
    // template<class T> void Context::UpdateAttributeDefaultValue(const char* name, const Variant& defaultValue) | File: ../Core/Context.h
    // Not registered because template
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Context", "int WeakRefs() const", asMETHODPR(Context, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Context", "int get_weakRefs() const", asMETHODPR(Context, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Controls", "bool IsDown(uint) const", asMETHODPR(Controls, IsDown, (unsigned) const, bool), asCALL_THISCALL);
    // bool Controls::IsPressed(unsigned button, const Controls& previousControls) const | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "bool IsPressed(uint, const Controls&in) const", asMETHODPR(Controls, IsPressed, (unsigned, const Controls&) const, bool), asCALL_THISCALL);
    // void Controls::Reset() | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "void Reset()", asMETHODPR(Controls, Reset, (), void), asCALL_THISCALL);
    // void Controls::Set(unsigned buttons, bool down=true) | File: ../Input/Controls.h
    engine->RegisterObjectMethod("Controls", "void Set(uint, bool = true)", asMETHODPR(Controls, Set, (unsigned, bool), void), asCALL_THISCALL);
    // Controls& Controls::operator=(const Controls&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Controls>(engine, "Controls");
#ifdef REGISTER_MANUAL_PART_Controls
    REGISTER_MANUAL_PART_Controls(Controls, "Controls")
#endif

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_ADDREF, "void f()", asMETHODPR(CrowdAgent, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void AllocateNetworkState()", asMETHODPR(CrowdAgent, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void CrowdAgent::ApplyAttributes() override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void ApplyAttributes()", asMETHODPR(CrowdAgent, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CrowdAgent::CrowdAgent(Context* context) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_FACTORY, "CrowdAgent@+ f()", asFUNCTION(CrowdAgent_CrowdAgent_Context), asCALL_CDECL);
    // void CrowdAgent::DrawDebugGeometry(bool depthTest) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void DrawDebugGeometry(bool)", asMETHODPR(CrowdAgent, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // void CrowdAgent::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CrowdAgent, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // Vector3 CrowdAgent::GetActualVelocity() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetActualVelocity() const", asMETHODPR(CrowdAgent, GetActualVelocity, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_actualVelocity() const", asMETHODPR(CrowdAgent, GetActualVelocity, () const, Vector3), asCALL_THISCALL);
    // int CrowdAgent::GetAgentCrowdId() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "int GetAgentCrowdId() const", asMETHODPR(CrowdAgent, GetAgentCrowdId, () const, int), asCALL_THISCALL);
    // CrowdAgentState CrowdAgent::GetAgentState() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentState GetAgentState() const", asMETHODPR(CrowdAgent, GetAgentState, () const, CrowdAgentState), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentState get_agentState() const", asMETHODPR(CrowdAgent, GetAgentState, () const, CrowdAgentState), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetAnimationEnabled() const", asMETHODPR(CrowdAgent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_animationEnabled() const", asMETHODPR(CrowdAgent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttribute(uint) const", asMETHODPR(CrowdAgent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Variant get_attributes(uint) const", asMETHODPR(CrowdAgent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttribute(const String&in) const", asMETHODPR(CrowdAgent, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CrowdAgent, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CrowdAgent, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CrowdAgent, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CrowdAgent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttributeDefault(uint) const", asMETHODPR(CrowdAgent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Variant get_attributeDefaults(uint) const", asMETHODPR(CrowdAgent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CrowdAgent, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetBlockEvents() const", asMETHODPR(CrowdAgent, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const String& GetCategory() const", asMETHODPR(CrowdAgent, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const String& get_category() const", asMETHODPR(CrowdAgent, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Component@+ GetComponent(StringHash) const", asMETHODPR(CrowdAgent, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetDesiredVelocity() const", asMETHODPR(CrowdAgent, GetDesiredVelocity, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_desiredVelocity() const", asMETHODPR(CrowdAgent, GetDesiredVelocity, () const, Vector3), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "VariantMap& GetEventDataMap() const", asMETHODPR(CrowdAgent, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "Object@+ GetEventSender() const", asMETHODPR(CrowdAgent, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CrowdAgent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CrowdAgent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const VariantMap& GetGlobalVars() const", asMETHODPR(CrowdAgent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const VariantMap& get_globalVars() const", asMETHODPR(CrowdAgent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float CrowdAgent::GetHeight() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetHeight() const", asMETHODPR(CrowdAgent, GetHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_height() const", asMETHODPR(CrowdAgent, GetHeight, () const, float), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetID() const", asMETHODPR(CrowdAgent, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_id() const", asMETHODPR(CrowdAgent, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CrowdAgent, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float CrowdAgent::GetMaxAccel() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetMaxAccel() const", asMETHODPR(CrowdAgent, GetMaxAccel, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_maxAccel() const", asMETHODPR(CrowdAgent, GetMaxAccel, () const, float), asCALL_THISCALL);
    // float CrowdAgent::GetMaxSpeed() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetMaxSpeed() const", asMETHODPR(CrowdAgent, GetMaxSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_maxSpeed() const", asMETHODPR(CrowdAgent, GetMaxSpeed, () const, float), asCALL_THISCALL);
    // NavigationPushiness CrowdAgent::GetNavigationPushiness() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "NavigationPushiness GetNavigationPushiness() const", asMETHODPR(CrowdAgent, GetNavigationPushiness, () const, NavigationPushiness), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "NavigationPushiness get_navigationPushiness() const", asMETHODPR(CrowdAgent, GetNavigationPushiness, () const, NavigationPushiness), asCALL_THISCALL);
    // NavigationQuality CrowdAgent::GetNavigationQuality() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "NavigationQuality GetNavigationQuality() const", asMETHODPR(CrowdAgent, GetNavigationQuality, () const, NavigationQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "NavigationQuality get_navigationQuality() const", asMETHODPR(CrowdAgent, GetNavigationQuality, () const, NavigationQuality), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Node@+ GetNode() const", asMETHODPR(CrowdAgent, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Node@+ get_node() const", asMETHODPR(CrowdAgent, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetNumAttributes() const", asMETHODPR(CrowdAgent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_numAttributes() const", asMETHODPR(CrowdAgent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetNumNetworkAttributes() const", asMETHODPR(CrowdAgent, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CrowdAgent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CrowdAgent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CrowdAgent, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned CrowdAgent::GetObstacleAvoidanceType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetObstacleAvoidanceType() const", asMETHODPR(CrowdAgent, GetObstacleAvoidanceType, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_obstacleAvoidanceType() const", asMETHODPR(CrowdAgent, GetObstacleAvoidanceType, () const, unsigned), asCALL_THISCALL);
    // Vector3 CrowdAgent::GetPosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 GetPosition() const", asMETHODPR(CrowdAgent, GetPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "Vector3 get_position() const", asMETHODPR(CrowdAgent, GetPosition, () const, Vector3), asCALL_THISCALL);
    // unsigned CrowdAgent::GetQueryFilterType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "uint GetQueryFilterType() const", asMETHODPR(CrowdAgent, GetQueryFilterType, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "uint get_queryFilterType() const", asMETHODPR(CrowdAgent, GetQueryFilterType, () const, unsigned), asCALL_THISCALL);
    // float CrowdAgent::GetRadius() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "float GetRadius() const", asMETHODPR(CrowdAgent, GetRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "float get_radius() const", asMETHODPR(CrowdAgent, GetRadius, () const, float), asCALL_THISCALL);
    // CrowdAgentRequestedTarget CrowdAgent::GetRequestedTargetType() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentRequestedTarget GetRequestedTargetType() const", asMETHODPR(CrowdAgent, GetRequestedTargetType, () const, CrowdAgentRequestedTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentRequestedTarget get_requestedTargetType() const", asMETHODPR(CrowdAgent, GetRequestedTargetType, () const, CrowdAgentRequestedTarget), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "Scene@+ GetScene() const", asMETHODPR(CrowdAgent, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CrowdAgent, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector3& CrowdAgent::GetTargetPosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& GetTargetPosition() const", asMETHODPR(CrowdAgent, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& get_targetPosition() const", asMETHODPR(CrowdAgent, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    // CrowdAgentTargetState CrowdAgent::GetTargetState() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentTargetState GetTargetState() const", asMETHODPR(CrowdAgent, GetTargetState, () const, CrowdAgentTargetState), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "CrowdAgentTargetState get_targetState() const", asMETHODPR(CrowdAgent, GetTargetState, () const, CrowdAgentTargetState), asCALL_THISCALL);
    // const Vector3& CrowdAgent::GetTargetVelocity() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& GetTargetVelocity() const", asMETHODPR(CrowdAgent, GetTargetVelocity, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const Vector3& get_targetVelocity() const", asMETHODPR(CrowdAgent, GetTargetVelocity, () const, const Vector3&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "StringHash GetType() const", asMETHODPR(CrowdAgent, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "StringHash get_type() const", asMETHODPR(CrowdAgent, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "const String& GetTypeName() const", asMETHODPR(CrowdAgent, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "const String& get_typeName() const", asMETHODPR(CrowdAgent, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool CrowdAgent::GetUpdateNodePosition() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool GetUpdateNodePosition() const", asMETHODPR(CrowdAgent, GetUpdateNodePosition, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_updateNodePosition() const", asMETHODPR(CrowdAgent, GetUpdateNodePosition, () const, bool), asCALL_THISCALL);
    // bool CrowdAgent::HasArrived() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasArrived() const", asMETHODPR(CrowdAgent, HasArrived, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_arrived() const", asMETHODPR(CrowdAgent, HasArrived, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasEventHandlers() const", asMETHODPR(CrowdAgent, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool CrowdAgent::HasRequestedTarget() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasRequestedTarget() const", asMETHODPR(CrowdAgent, HasRequestedTarget, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_requestedTarget() const", asMETHODPR(CrowdAgent, HasRequestedTarget, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CrowdAgent, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CrowdAgent, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsEnabled() const", asMETHODPR(CrowdAgent, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_enabled() const", asMETHODPR(CrowdAgent, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsEnabledEffective() const", asMETHODPR(CrowdAgent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_enabledEffective() const", asMETHODPR(CrowdAgent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool CrowdAgent::IsInCrowd() const | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsInCrowd() const", asMETHODPR(CrowdAgent, IsInCrowd, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_inCrowd() const", asMETHODPR(CrowdAgent, IsInCrowd, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsInstanceOf(StringHash) const", asMETHODPR(CrowdAgent, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsReplicated() const", asMETHODPR(CrowdAgent, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_replicated() const", asMETHODPR(CrowdAgent, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool IsTemporary() const", asMETHODPR(CrowdAgent, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool get_temporary() const", asMETHODPR(CrowdAgent, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool Load(Deserializer&)", asMETHODPR(CrowdAgent, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CrowdAgent, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool LoadXML(const XMLElement&in)", asMETHODPR(CrowdAgent, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void MarkNetworkUpdate()", asMETHODPR(CrowdAgent, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CrowdAgent, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CrowdAgent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CrowdAgent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void CrowdAgent::OnSetEnabled() override | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void OnSetEnabled()", asMETHODPR(CrowdAgent, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void PrepareNetworkUpdate()", asMETHODPR(CrowdAgent, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CrowdAgent, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CrowdAgent, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdAgent", "int Refs() const", asMETHODPR(CrowdAgent, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "int get_refs() const", asMETHODPR(CrowdAgent, Refs, () const, int), asCALL_THISCALL);
    // static void CrowdAgent::RegisterObject(Context* context) | File: ../Navigation/CrowdAgent.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdAgent", asBEHAVE_RELEASE, "void f()", asMETHODPR(CrowdAgent, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void Remove()", asMETHODPR(CrowdAgent, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CrowdAgent, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveInstanceDefault()", asMETHODPR(CrowdAgent, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void RemoveObjectAnimation()", asMETHODPR(CrowdAgent, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void CrowdAgent::ResetTarget() | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void ResetTarget()", asMETHODPR(CrowdAgent, ResetTarget, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void ResetToDefault()", asMETHODPR(CrowdAgent, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool Save(Serializer&) const", asMETHODPR(CrowdAgent, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveDefaultAttributes() const", asMETHODPR(CrowdAgent, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveJSON(JSONValue&) const", asMETHODPR(CrowdAgent, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SaveXML(XMLElement&) const", asMETHODPR(CrowdAgent, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SendEvent(StringHash)", asMETHODPR(CrowdAgent, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CrowdAgent, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAnimationEnabled(bool)", asMETHODPR(CrowdAgent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_animationEnabled(bool)", asMETHODPR(CrowdAgent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAnimationTime(float)", asMETHODPR(CrowdAgent, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CrowdAgent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CrowdAgent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CrowdAgent, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CrowdAgent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CrowdAgent, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CrowdAgent, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CrowdAgent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetBlockEvents(bool)", asMETHODPR(CrowdAgent, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetEnabled(bool)", asMETHODPR(CrowdAgent, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_enabled(bool)", asMETHODPR(CrowdAgent, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CrowdAgent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CrowdAgent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CrowdAgent::SetHeight(float height) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetHeight(float)", asMETHODPR(CrowdAgent, SetHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_height(float)", asMETHODPR(CrowdAgent, SetHeight, (float), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetInstanceDefault(bool)", asMETHODPR(CrowdAgent, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CrowdAgent, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CrowdAgent::SetMaxAccel(float maxAccel) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetMaxAccel(float)", asMETHODPR(CrowdAgent, SetMaxAccel, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_maxAccel(float)", asMETHODPR(CrowdAgent, SetMaxAccel, (float), void), asCALL_THISCALL);
    // void CrowdAgent::SetMaxSpeed(float maxSpeed) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetMaxSpeed(float)", asMETHODPR(CrowdAgent, SetMaxSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_maxSpeed(float)", asMETHODPR(CrowdAgent, SetMaxSpeed, (float), void), asCALL_THISCALL);
    // void CrowdAgent::SetNavigationPushiness(NavigationPushiness val) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetNavigationPushiness(NavigationPushiness)", asMETHODPR(CrowdAgent, SetNavigationPushiness, (NavigationPushiness), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_navigationPushiness(NavigationPushiness)", asMETHODPR(CrowdAgent, SetNavigationPushiness, (NavigationPushiness), void), asCALL_THISCALL);
    // void CrowdAgent::SetNavigationQuality(NavigationQuality val) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetNavigationQuality(NavigationQuality)", asMETHODPR(CrowdAgent, SetNavigationQuality, (NavigationQuality), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_navigationQuality(NavigationQuality)", asMETHODPR(CrowdAgent, SetNavigationQuality, (NavigationQuality), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CrowdAgent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CrowdAgent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CrowdAgent, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CrowdAgent::SetObstacleAvoidanceType(unsigned obstacleAvoidanceType) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetObstacleAvoidanceType(uint)", asMETHODPR(CrowdAgent, SetObstacleAvoidanceType, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_obstacleAvoidanceType(uint)", asMETHODPR(CrowdAgent, SetObstacleAvoidanceType, (unsigned), void), asCALL_THISCALL);
    // void CrowdAgent::SetQueryFilterType(unsigned queryFilterType) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetQueryFilterType(uint)", asMETHODPR(CrowdAgent, SetQueryFilterType, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_queryFilterType(uint)", asMETHODPR(CrowdAgent, SetQueryFilterType, (unsigned), void), asCALL_THISCALL);
    // void CrowdAgent::SetRadius(float radius) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetRadius(float)", asMETHODPR(CrowdAgent, SetRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_radius(float)", asMETHODPR(CrowdAgent, SetRadius, (float), void), asCALL_THISCALL);
    // void CrowdAgent::SetTargetPosition(const Vector3& position) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTargetPosition(const Vector3&in)", asMETHODPR(CrowdAgent, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_targetPosition(const Vector3&in)", asMETHODPR(CrowdAgent, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void CrowdAgent::SetTargetVelocity(const Vector3& velocity) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTargetVelocity(const Vector3&in)", asMETHODPR(CrowdAgent, SetTargetVelocity, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_targetVelocity(const Vector3&in)", asMETHODPR(CrowdAgent, SetTargetVelocity, (const Vector3&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetTemporary(bool)", asMETHODPR(CrowdAgent, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_temporary(bool)", asMETHODPR(CrowdAgent, SetTemporary, (bool), void), asCALL_THISCALL);
    // void CrowdAgent::SetUpdateNodePosition(bool unodepos) | File: ../Navigation/CrowdAgent.h
    engine->RegisterObjectMethod("CrowdAgent", "void SetUpdateNodePosition(bool)", asMETHODPR(CrowdAgent, SetUpdateNodePosition, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "void set_updateNodePosition(bool)", asMETHODPR(CrowdAgent, SetUpdateNodePosition, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromAllEvents()", asMETHODPR(CrowdAgent, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CrowdAgent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CrowdAgent, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CrowdAgent, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdAgent", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CrowdAgent, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdAgent", "int WeakRefs() const", asMETHODPR(CrowdAgent, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdAgent", "int get_weakRefs() const", asMETHODPR(CrowdAgent, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CrowdAgent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CrowdAgent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdAgent", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CrowdAgent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_ADDREF, "void f()", asMETHODPR(CrowdManager, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void AllocateNetworkState()", asMETHODPR(CrowdManager, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void CrowdManager::ApplyAttributes() override | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void ApplyAttributes()", asMETHODPR(CrowdManager, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit CrowdManager::CrowdManager(Context* context) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_FACTORY, "CrowdManager@+ f()", asFUNCTION(CrowdManager_CrowdManager_Context), asCALL_CDECL);
    // void CrowdManager::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CrowdManager, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void CrowdManager::DrawDebugGeometry(bool depthTest) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void DrawDebugGeometry(bool)", asMETHODPR(CrowdManager, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // void CrowdManager::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, int queryFilterType) | File: ../Navigation/CrowdManager.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // PODVector<CrowdAgent*> CrowdManager::GetAgents(Node* node=nullptr, bool inCrowdFilter=true) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "Array<CrowdAgent@>@ GetAgents(Node@+ = null, bool = true) const", asFUNCTION(CrowdManager_GetAgents_Node_bool), asCALL_CDECL_OBJFIRST);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetAnimationEnabled() const", asMETHODPR(CrowdManager, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_animationEnabled() const", asMETHODPR(CrowdManager, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float CrowdManager::GetAreaCost(unsigned queryFilterType, unsigned areaID) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAreaCost(uint, uint) const", asMETHODPR(CrowdManager, GetAreaCost, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttribute(uint) const", asMETHODPR(CrowdManager, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Variant get_attributes(uint) const", asMETHODPR(CrowdManager, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttribute(const String&in) const", asMETHODPR(CrowdManager, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CrowdManager, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CrowdManager, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CrowdManager, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CrowdManager, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttributeDefault(uint) const", asMETHODPR(CrowdManager, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Variant get_attributeDefaults(uint) const", asMETHODPR(CrowdManager, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CrowdManager, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetBlockEvents() const", asMETHODPR(CrowdManager, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const String& GetCategory() const", asMETHODPR(CrowdManager, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const String& get_category() const", asMETHODPR(CrowdManager, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Component@+ GetComponent(StringHash) const", asMETHODPR(CrowdManager, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("CrowdManager", "VariantMap& GetEventDataMap() const", asMETHODPR(CrowdManager, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "Object@+ GetEventSender() const", asMETHODPR(CrowdManager, GetEventSender, () const, Object*), asCALL_THISCALL);
    // unsigned short CrowdManager::GetExcludeFlags(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint16 GetExcludeFlags(uint) const", asMETHODPR(CrowdManager, GetExcludeFlags, (unsigned) const, unsigned short), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CrowdManager, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CrowdManager, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const VariantMap& GetGlobalVars() const", asMETHODPR(CrowdManager, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const VariantMap& get_globalVars() const", asMETHODPR(CrowdManager, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetID() const", asMETHODPR(CrowdManager, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_id() const", asMETHODPR(CrowdManager, GetID, () const, unsigned), asCALL_THISCALL);
    // unsigned short CrowdManager::GetIncludeFlags(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint16 GetIncludeFlags(uint) const", asMETHODPR(CrowdManager, GetIncludeFlags, (unsigned) const, unsigned short), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CrowdManager, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float CrowdManager::GetMaxAgentRadius() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "float GetMaxAgentRadius() const", asMETHODPR(CrowdManager, GetMaxAgentRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "float get_maxAgentRadius() const", asMETHODPR(CrowdManager, GetMaxAgentRadius, () const, float), asCALL_THISCALL);
    // unsigned CrowdManager::GetMaxAgents() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetMaxAgents() const", asMETHODPR(CrowdManager, GetMaxAgents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_maxAgents() const", asMETHODPR(CrowdManager, GetMaxAgents, () const, unsigned), asCALL_THISCALL);
    // NavigationMesh* CrowdManager::GetNavigationMesh() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "NavigationMesh@+ GetNavigationMesh() const", asMETHODPR(CrowdManager, GetNavigationMesh, () const, NavigationMesh*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "NavigationMesh@+ get_navMesh() const", asMETHODPR(CrowdManager, GetNavigationMesh, () const, NavigationMesh*), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Node@+ GetNode() const", asMETHODPR(CrowdManager, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "Node@+ get_node() const", asMETHODPR(CrowdManager, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned CrowdManager::GetNumAreas(unsigned queryFilterType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumAreas(uint) const", asMETHODPR(CrowdManager, GetNumAreas, (unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numAreas(uint) const", asMETHODPR(CrowdManager, GetNumAreas, (unsigned) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumAttributes() const", asMETHODPR(CrowdManager, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numAttributes() const", asMETHODPR(CrowdManager, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumNetworkAttributes() const", asMETHODPR(CrowdManager, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned CrowdManager::GetNumObstacleAvoidanceTypes() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumObstacleAvoidanceTypes() const", asMETHODPR(CrowdManager, GetNumObstacleAvoidanceTypes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numObstacleAvoidanceTypes() const", asMETHODPR(CrowdManager, GetNumObstacleAvoidanceTypes, () const, unsigned), asCALL_THISCALL);
    // unsigned CrowdManager::GetNumQueryFilterTypes() const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "uint GetNumQueryFilterTypes() const", asMETHODPR(CrowdManager, GetNumQueryFilterTypes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "uint get_numQueryFilterTypes() const", asMETHODPR(CrowdManager, GetNumQueryFilterTypes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CrowdManager, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CrowdManager, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CrowdManager, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // const CrowdObstacleAvoidanceParams& CrowdManager::GetObstacleAvoidanceParams(unsigned obstacleAvoidanceType) const | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "const CrowdObstacleAvoidanceParams& GetObstacleAvoidanceParams(uint) const", asMETHODPR(CrowdManager, GetObstacleAvoidanceParams, (unsigned) const, const CrowdObstacleAvoidanceParams&), asCALL_THISCALL);
    // VariantVector CrowdManager::GetObstacleAvoidanceTypesAttr() const | File: ../Navigation/CrowdManager.h
    // Error: type "VariantVector" can not automatically bind
    // VariantVector CrowdManager::GetQueryFilterTypesAttr() const | File: ../Navigation/CrowdManager.h
    // Error: type "VariantVector" can not automatically bind
    // Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef* randomRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "dtPolyRef*" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "Scene@+ GetScene() const", asMETHODPR(CrowdManager, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CrowdManager, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "StringHash GetType() const", asMETHODPR(CrowdManager, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "StringHash get_type() const", asMETHODPR(CrowdManager, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "const String& GetTypeName() const", asMETHODPR(CrowdManager, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "const String& get_typeName() const", asMETHODPR(CrowdManager, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasEventHandlers() const", asMETHODPR(CrowdManager, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CrowdManager, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CrowdManager, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsEnabled() const", asMETHODPR(CrowdManager, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_enabled() const", asMETHODPR(CrowdManager, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsEnabledEffective() const", asMETHODPR(CrowdManager, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_enabledEffective() const", asMETHODPR(CrowdManager, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsInstanceOf(StringHash) const", asMETHODPR(CrowdManager, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsReplicated() const", asMETHODPR(CrowdManager, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_replicated() const", asMETHODPR(CrowdManager, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool IsTemporary() const", asMETHODPR(CrowdManager, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool get_temporary() const", asMETHODPR(CrowdManager, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool Load(Deserializer&)", asMETHODPR(CrowdManager, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CrowdManager, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "bool LoadXML(const XMLElement&in)", asMETHODPR(CrowdManager, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void MarkNetworkUpdate()", asMETHODPR(CrowdManager, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 CrowdManager::MoveAlongSurface(const Vector3& start, const Vector3& end, int queryFilterType, int maxVisited=3) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "Vector3 MoveAlongSurface(const Vector3&in, const Vector3&in, int, int = 3)", asMETHODPR(CrowdManager, MoveAlongSurface, (const Vector3&, const Vector3&, int, int), Vector3), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CrowdManager, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CrowdManager, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CrowdManager, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void OnSetEnabled()", asMETHODPR(CrowdManager, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void PrepareNetworkUpdate()", asMETHODPR(CrowdManager, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
    // Error: type "Vector3*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CrowdManager, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CrowdManager, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdManager", "int Refs() const", asMETHODPR(CrowdManager, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "int get_refs() const", asMETHODPR(CrowdManager, Refs, () const, int), asCALL_THISCALL);
    // static void CrowdManager::RegisterObject(Context* context) | File: ../Navigation/CrowdManager.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CrowdManager", asBEHAVE_RELEASE, "void f()", asMETHODPR(CrowdManager, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void Remove()", asMETHODPR(CrowdManager, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CrowdManager, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveInstanceDefault()", asMETHODPR(CrowdManager, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void RemoveObjectAnimation()", asMETHODPR(CrowdManager, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void CrowdManager::ResetCrowdTarget(Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void ResetCrowdTarget(Node@+ = null)", asMETHODPR(CrowdManager, ResetCrowdTarget, (Node*), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void ResetToDefault()", asMETHODPR(CrowdManager, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool Save(Serializer&) const", asMETHODPR(CrowdManager, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveDefaultAttributes() const", asMETHODPR(CrowdManager, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveJSON(JSONValue&) const", asMETHODPR(CrowdManager, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "bool SaveXML(XMLElement&) const", asMETHODPR(CrowdManager, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SendEvent(StringHash)", asMETHODPR(CrowdManager, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CrowdManager, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAnimationEnabled(bool)", asMETHODPR(CrowdManager, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_animationEnabled(bool)", asMETHODPR(CrowdManager, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAnimationTime(float)", asMETHODPR(CrowdManager, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void CrowdManager::SetAreaCost(unsigned queryFilterType, unsigned areaID, float cost) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAreaCost(uint, uint, float)", asMETHODPR(CrowdManager, SetAreaCost, (unsigned, unsigned, float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CrowdManager, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CrowdManager, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CrowdManager, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CrowdManager, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CrowdManager, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CrowdManager, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CrowdManager, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SetBlockEvents(bool)", asMETHODPR(CrowdManager, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void CrowdManager::SetCrowdTarget(const Vector3& position, Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetCrowdTarget(const Vector3&in, Node@+ = null)", asMETHODPR(CrowdManager, SetCrowdTarget, (const Vector3&, Node*), void), asCALL_THISCALL);
    // void CrowdManager::SetCrowdVelocity(const Vector3& velocity, Node* node=nullptr) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetCrowdVelocity(const Vector3&in, Node@+ = null)", asMETHODPR(CrowdManager, SetCrowdVelocity, (const Vector3&, Node*), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CrowdManager", "void SetEnabled(bool)", asMETHODPR(CrowdManager, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_enabled(bool)", asMETHODPR(CrowdManager, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CrowdManager::SetExcludeFlags(unsigned queryFilterType, unsigned short flags) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetExcludeFlags(uint, uint16)", asMETHODPR(CrowdManager, SetExcludeFlags, (unsigned, unsigned short), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CrowdManager, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CrowdManager, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void CrowdManager::SetIncludeFlags(unsigned queryFilterType, unsigned short flags) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetIncludeFlags(uint, uint16)", asMETHODPR(CrowdManager, SetIncludeFlags, (unsigned, unsigned short), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetInstanceDefault(bool)", asMETHODPR(CrowdManager, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CrowdManager, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void CrowdManager::SetMaxAgentRadius(float maxAgentRadius) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetMaxAgentRadius(float)", asMETHODPR(CrowdManager, SetMaxAgentRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_maxAgentRadius(float)", asMETHODPR(CrowdManager, SetMaxAgentRadius, (float), void), asCALL_THISCALL);
    // void CrowdManager::SetMaxAgents(unsigned maxAgents) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetMaxAgents(uint)", asMETHODPR(CrowdManager, SetMaxAgents, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_maxAgents(uint)", asMETHODPR(CrowdManager, SetMaxAgents, (unsigned), void), asCALL_THISCALL);
    // void CrowdManager::SetNavigationMesh(NavigationMesh* navMesh) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetNavigationMesh(NavigationMesh@+)", asMETHODPR(CrowdManager, SetNavigationMesh, (NavigationMesh*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_navMesh(NavigationMesh@+)", asMETHODPR(CrowdManager, SetNavigationMesh, (NavigationMesh*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CrowdManager, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CrowdManager, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CrowdManager, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void CrowdManager::SetObstacleAvoidanceParams(unsigned obstacleAvoidanceType, const CrowdObstacleAvoidanceParams& params) | File: ../Navigation/CrowdManager.h
    engine->RegisterObjectMethod("CrowdManager", "void SetObstacleAvoidanceParams(uint, const CrowdObstacleAvoidanceParams&in)", asMETHODPR(CrowdManager, SetObstacleAvoidanceParams, (unsigned, const CrowdObstacleAvoidanceParams&), void), asCALL_THISCALL);
    // void CrowdManager::SetObstacleAvoidanceTypesAttr(const VariantVector& value) | File: ../Navigation/CrowdManager.h
    // Error: type "const VariantVector&" can not automatically bind
    // void CrowdManager::SetQueryFilterTypesAttr(const VariantVector& value) | File: ../Navigation/CrowdManager.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void SetTemporary(bool)", asMETHODPR(CrowdManager, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "void set_temporary(bool)", asMETHODPR(CrowdManager, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromAllEvents()", asMETHODPR(CrowdManager, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CrowdManager_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CrowdManager, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CrowdManager, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CrowdManager", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CrowdManager, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CrowdManager", "int WeakRefs() const", asMETHODPR(CrowdManager, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CrowdManager", "int get_weakRefs() const", asMETHODPR(CrowdManager, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CrowdManager, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CrowdManager, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CrowdManager", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CrowdManager, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Cursor", "void AddChild(UIElement@+)", asMETHODPR(Cursor, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_ADDREF, "void f()", asMETHODPR(Cursor, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTag(const String&in)", asMETHODPR(Cursor, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Cursor, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AddTags(Array<String>@+)", asFUNCTION(Cursor_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void AdjustScissor(IntRect&)", asMETHODPR(Cursor, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void AllocateNetworkState()", asMETHODPR(Cursor, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void ApplyAttributes()", asMETHODPR(Cursor, ApplyAttributes, (), void), asCALL_THISCALL);
    // void Cursor::ApplyOSCursorShape() | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void ApplyOSCursorShape()", asMETHODPR(Cursor, ApplyOSCursorShape, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void BringToFront()", asMETHODPR(Cursor, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Cursor, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // explicit Cursor::Cursor(Context* context) | File: ../UI/Cursor.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_FACTORY, "Cursor@+ f()", asFUNCTION(Cursor_Cursor_Context), asCALL_CDECL);
    // void Cursor::DefineShape(const String& shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void DefineShape(const String&in, Image@+, const IntRect&in, const IntVector2&in)", asMETHODPR(Cursor, DefineShape, (const String&, Image*, const IntRect&, const IntVector2&), void), asCALL_THISCALL);
    // void Cursor::DefineShape(CursorShape shape, Image* image, const IntRect& imageRect, const IntVector2& hotSpot) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void DefineShape(CursorShape, Image@+, const IntRect&in, const IntVector2&in)", asMETHODPR(Cursor, DefineShape, (CursorShape, Image*, const IntRect&, const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void DisableLayoutUpdate()", asMETHODPR(Cursor, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Cursor, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void EnableLayoutUpdate()", asMETHODPR(Cursor, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Cursor, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint FindChild(UIElement@+) const", asMETHODPR(Cursor, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool GetAnimationEnabled() const", asMETHODPR(Cursor, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_animationEnabled() const", asMETHODPR(Cursor, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const String& GetAppliedStyle() const", asMETHODPR(Cursor, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_style() const", asMETHODPR(Cursor, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttribute(uint) const", asMETHODPR(Cursor, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Variant get_attributes(uint) const", asMETHODPR(Cursor, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttribute(const String&in) const", asMETHODPR(Cursor, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Cursor, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Cursor, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Cursor, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Cursor, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttributeDefault(uint) const", asMETHODPR(Cursor, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Variant get_attributeDefaults(uint) const", asMETHODPR(Cursor, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Cursor, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Cursor::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Cursor.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "BlendMode GetBlendMode() const", asMETHODPR(Cursor, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "BlendMode get_blendMode() const", asMETHODPR(Cursor, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool GetBlockEvents() const", asMETHODPR(Cursor, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetBorder() const", asMETHODPR(Cursor, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_border() const", asMETHODPR(Cursor, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetBringToBack() const", asMETHODPR(Cursor, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_bringToBack() const", asMETHODPR(Cursor, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetBringToFront() const", asMETHODPR(Cursor, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_bringToFront() const", asMETHODPR(Cursor, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const String& GetCategory() const", asMETHODPR(Cursor, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_category() const", asMETHODPR(Cursor, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(uint) const", asMETHODPR(Cursor, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_children(uint) const", asMETHODPR(Cursor, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Cursor, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Cursor, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetChildOffset() const", asMETHODPR(Cursor, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_childOffset() const", asMETHODPR(Cursor, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Cursor_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Cursor_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Cursor_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetClipBorder() const", asMETHODPR(Cursor, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_clipBorder() const", asMETHODPR(Cursor, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetClipChildren() const", asMETHODPR(Cursor, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_clipChildren() const", asMETHODPR(Cursor, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetColor(Corner) const", asMETHODPR(Cursor, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Color& get_colors(Corner) const", asMETHODPR(Cursor, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetColorAttr() const", asMETHODPR(Cursor, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntRect GetCombinedScreenRect()", asMETHODPR(Cursor, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "IntRect get_combinedScreenRect()", asMETHODPR(Cursor, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Cursor, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Color& GetDerivedColor() const", asMETHODPR(Cursor, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "float GetDerivedOpacity() const", asMETHODPR(Cursor, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "float get_derivedOpacity() const", asMETHODPR(Cursor, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetDisabledOffset() const", asMETHODPR(Cursor, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_disabledOffset() const", asMETHODPR(Cursor, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Cursor, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Cursor, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint GetDragButtonCount() const", asMETHODPR(Cursor, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_dragButtonCount() const", asMETHODPR(Cursor, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Cursor, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Cursor, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Cursor, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetElementEventSender() const", asMETHODPR(Cursor, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetEnableAnchor() const", asMETHODPR(Cursor, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enableAnchor() const", asMETHODPR(Cursor, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "VariantMap& GetEventDataMap() const", asMETHODPR(Cursor, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "Object@+ GetEventSender() const", asMETHODPR(Cursor, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "FocusMode GetFocusMode() const", asMETHODPR(Cursor, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "FocusMode get_focusMode() const", asMETHODPR(Cursor, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Cursor, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Cursor, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const VariantMap& GetGlobalVars() const", asMETHODPR(Cursor, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const VariantMap& get_globalVars() const", asMETHODPR(Cursor, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetHeight() const", asMETHODPR(Cursor, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_height() const", asMETHODPR(Cursor, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Cursor, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Cursor, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetHoverOffset() const", asMETHODPR(Cursor, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_hoverOffset() const", asMETHODPR(Cursor, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetImageBorder() const", asMETHODPR(Cursor, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_imageBorder() const", asMETHODPR(Cursor, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetImageRect() const", asMETHODPR(Cursor, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_imageRect() const", asMETHODPR(Cursor, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndent() const", asMETHODPR(Cursor, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indent() const", asMETHODPR(Cursor, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndentSpacing() const", asMETHODPR(Cursor, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indentSpacing() const", asMETHODPR(Cursor, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetIndentWidth() const", asMETHODPR(Cursor, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_indentWidth() const", asMETHODPR(Cursor, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Cursor, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntRect& GetLayoutBorder() const", asMETHODPR(Cursor, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntRect& get_layoutBorder() const", asMETHODPR(Cursor, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetLayoutElementMaxSize() const", asMETHODPR(Cursor, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Cursor, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Cursor, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "LayoutMode GetLayoutMode() const", asMETHODPR(Cursor, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "LayoutMode get_layoutMode() const", asMETHODPR(Cursor, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetLayoutSpacing() const", asMETHODPR(Cursor, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_layoutSpacing() const", asMETHODPR(Cursor, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "Material@+ GetMaterial() const", asMETHODPR(Cursor, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Material@+ get_material() const", asMETHODPR(Cursor, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetMaterialAttr() const", asMETHODPR(Cursor, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetMaxAnchor() const", asMETHODPR(Cursor, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_maxAnchor() const", asMETHODPR(Cursor, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMaxHeight() const", asMETHODPR(Cursor, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_maxHeight() const", asMETHODPR(Cursor, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMaxOffset() const", asMETHODPR(Cursor, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_maxOffset() const", asMETHODPR(Cursor, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMaxSize() const", asMETHODPR(Cursor, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_maxSize() const", asMETHODPR(Cursor, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMaxWidth() const", asMETHODPR(Cursor, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_maxWidth() const", asMETHODPR(Cursor, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetMinAnchor() const", asMETHODPR(Cursor, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_minAnchor() const", asMETHODPR(Cursor, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMinHeight() const", asMETHODPR(Cursor, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_minHeight() const", asMETHODPR(Cursor, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMinOffset() const", asMETHODPR(Cursor, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_minOffset() const", asMETHODPR(Cursor, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetMinSize() const", asMETHODPR(Cursor, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_minSize() const", asMETHODPR(Cursor, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetMinWidth() const", asMETHODPR(Cursor, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_minWidth() const", asMETHODPR(Cursor, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const String& GetName() const", asMETHODPR(Cursor, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_name() const", asMETHODPR(Cursor, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumAttributes() const", asMETHODPR(Cursor, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_numAttributes() const", asMETHODPR(Cursor, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumChildren(bool = false) const", asMETHODPR(Cursor, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "uint get_numChildren(bool = false) const", asMETHODPR(Cursor, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "uint GetNumNetworkAttributes() const", asMETHODPR(Cursor, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Cursor, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Cursor, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Cursor, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "float GetOpacity() const", asMETHODPR(Cursor, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "float get_opacity() const", asMETHODPR(Cursor, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetParent() const", asMETHODPR(Cursor, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_parent() const", asMETHODPR(Cursor, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Vector2& GetPivot() const", asMETHODPR(Cursor, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const Vector2& get_pivot() const", asMETHODPR(Cursor, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetPosition() const", asMETHODPR(Cursor, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_position() const", asMETHODPR(Cursor, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetPriority() const", asMETHODPR(Cursor, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_priority() const", asMETHODPR(Cursor, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ GetRoot() const", asMETHODPR(Cursor, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "UIElement@+ get_root() const", asMETHODPR(Cursor, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetScreenPosition() const", asMETHODPR(Cursor, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_screenPosition() const", asMETHODPR(Cursor, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const String& Cursor::GetShape() const | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "const String& GetShape() const", asMETHODPR(Cursor, GetShape, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_shape() const", asMETHODPR(Cursor, GetShape, () const, const String&), asCALL_THISCALL);
    // VariantVector Cursor::GetShapesAttr() const | File: ../UI/Cursor.h
    // Error: type "VariantVector" can not automatically bind
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const IntVector2& GetSize() const", asMETHODPR(Cursor, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& get_size() const", asMETHODPR(Cursor, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetSortChildren() const", asMETHODPR(Cursor, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_sortChildren() const", asMETHODPR(Cursor, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Cursor, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "Array<String>@ GetTags() const", asFUNCTION(Cursor_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Cursor", "Array<String>@ get_tags() const", asFUNCTION(Cursor_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "Texture@+ GetTexture() const", asMETHODPR(Cursor, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "Texture@+ get_texture() const", asMETHODPR(Cursor, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "ResourceRef GetTextureAttr() const", asMETHODPR(Cursor, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "TraversalMode GetTraversalMode() const", asMETHODPR(Cursor, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "TraversalMode get_traversalMode() const", asMETHODPR(Cursor, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "StringHash GetType() const", asMETHODPR(Cursor, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "StringHash get_type() const", asMETHODPR(Cursor, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "const String& GetTypeName() const", asMETHODPR(Cursor, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_typeName() const", asMETHODPR(Cursor, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool GetUseDerivedOpacity() const", asMETHODPR(Cursor, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_useDerivedOpacity() const", asMETHODPR(Cursor, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // bool Cursor::GetUseSystemShapes() const | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "bool GetUseSystemShapes() const", asMETHODPR(Cursor, GetUseSystemShapes, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_useSystemShapes() const", asMETHODPR(Cursor, GetUseSystemShapes, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Cursor, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "const VariantMap& GetVars() const", asMETHODPR(Cursor, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Cursor, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Cursor, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "int GetWidth() const", asMETHODPR(Cursor, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_width() const", asMETHODPR(Cursor, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasColorGradient() const", asMETHODPR(Cursor, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_colorGradient() const", asMETHODPR(Cursor, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasEventHandlers() const", asMETHODPR(Cursor, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasFocus() const", asMETHODPR(Cursor, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_focus() const", asMETHODPR(Cursor, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Cursor, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Cursor, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool HasTag(const String&in) const", asMETHODPR(Cursor, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void InsertChild(uint, UIElement@+)", asMETHODPR(Cursor, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsChildOf(UIElement@+) const", asMETHODPR(Cursor, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEditable() const", asMETHODPR(Cursor, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_editable() const", asMETHODPR(Cursor, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsElementEventSender() const", asMETHODPR(Cursor, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_elementEventSender() const", asMETHODPR(Cursor, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEnabled() const", asMETHODPR(Cursor, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enabled() const", asMETHODPR(Cursor, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsEnabledSelf() const", asMETHODPR(Cursor, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_enabledSelf() const", asMETHODPR(Cursor, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedHeight() const", asMETHODPR(Cursor, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedHeight() const", asMETHODPR(Cursor, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedSize() const", asMETHODPR(Cursor, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedSize() const", asMETHODPR(Cursor, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsFixedWidth() const", asMETHODPR(Cursor, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_fixedWidth() const", asMETHODPR(Cursor, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsHovering() const", asMETHODPR(Cursor, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_hovering() const", asMETHODPR(Cursor, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInside(IntVector2, bool)", asMETHODPR(Cursor, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Cursor, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "bool IsInstanceOf(StringHash) const", asMETHODPR(Cursor, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsInternal() const", asMETHODPR(Cursor, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_internal() const", asMETHODPR(Cursor, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsSelected() const", asMETHODPR(Cursor, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_selected() const", asMETHODPR(Cursor, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool IsTemporary() const", asMETHODPR(Cursor, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_temporary() const", asMETHODPR(Cursor, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "bool IsTiled() const", asMETHODPR(Cursor, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_tiled() const", asMETHODPR(Cursor, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsVisible() const", asMETHODPR(Cursor, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_visible() const", asMETHODPR(Cursor, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsVisibleEffective() const", asMETHODPR(Cursor, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_visibleEffective() const", asMETHODPR(Cursor, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsWheelHandler() const", asMETHODPR(Cursor, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Cursor, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool Load(Deserializer&)", asMETHODPR(Cursor, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Cursor, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Cursor, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(const XMLElement&in)", asMETHODPR(Cursor, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Cursor, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool LoadXML(Deserializer&)", asMETHODPR(Cursor, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void MarkNetworkUpdate()", asMETHODPR(Cursor, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Cursor, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Cursor, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Cursor, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Cursor, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Cursor, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Cursor, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Cursor, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Cursor, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Cursor, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Cursor, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Cursor, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Cursor, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnIndentSet()", asMETHODPR(Cursor, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Cursor, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Cursor, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Cursor, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Cursor, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnSetEditable()", asMETHODPR(Cursor, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnTextInput(const String&in)", asMETHODPR(Cursor, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Cursor, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Cursor, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Cursor, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Cursor", "int Refs() const", asMETHODPR(Cursor, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_refs() const", asMETHODPR(Cursor, Refs, () const, int), asCALL_THISCALL);
    // static void Cursor::RegisterObject(Context* context) | File: ../UI/Cursor.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Cursor", asBEHAVE_RELEASE, "void f()", asMETHODPR(Cursor, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void Remove()", asMETHODPR(Cursor, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAllChildren()", asMETHODPR(Cursor, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAllTags()", asMETHODPR(Cursor, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Cursor, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Cursor, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void RemoveChildAtIndex(uint)", asMETHODPR(Cursor, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveInstanceDefault()", asMETHODPR(Cursor, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void RemoveObjectAnimation()", asMETHODPR(Cursor, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool RemoveTag(const String&in)", asMETHODPR(Cursor, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void ResetDeepEnabled()", asMETHODPR(Cursor, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void ResetToDefault()", asMETHODPR(Cursor, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool Save(Serializer&) const", asMETHODPR(Cursor, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SaveDefaultAttributes() const", asMETHODPR(Cursor, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "bool SaveJSON(JSONValue&) const", asMETHODPR(Cursor, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SaveXML(XMLElement&) const", asMETHODPR(Cursor, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Cursor, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Cursor, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SendEvent(StringHash)", asMETHODPR(Cursor, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Cursor, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Cursor, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAnimationEnabled(bool)", asMETHODPR(Cursor, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_animationEnabled(bool)", asMETHODPR(Cursor, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAnimationTime(float)", asMETHODPR(Cursor, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Cursor, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Cursor, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Cursor, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Cursor, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Cursor, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Cursor, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Cursor, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetBlendMode(BlendMode)", asMETHODPR(Cursor, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_blendMode(BlendMode)", asMETHODPR(Cursor, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SetBlockEvents(bool)", asMETHODPR(Cursor, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetBorder(const IntRect&in)", asMETHODPR(Cursor, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_border(const IntRect&in)", asMETHODPR(Cursor, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetBringToBack(bool)", asMETHODPR(Cursor, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_bringToBack(bool)", asMETHODPR(Cursor, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetBringToFront(bool)", asMETHODPR(Cursor, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_bringToFront(bool)", asMETHODPR(Cursor, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Cursor, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetClipBorder(const IntRect&in)", asMETHODPR(Cursor, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_clipBorder(const IntRect&in)", asMETHODPR(Cursor, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetClipChildren(bool)", asMETHODPR(Cursor, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_clipChildren(bool)", asMETHODPR(Cursor, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetColor(const Color&in)", asMETHODPR(Cursor, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_color(const Color&in)", asMETHODPR(Cursor, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetColor(Corner, const Color&in)", asMETHODPR(Cursor, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_colors(Corner, const Color&in)", asMETHODPR(Cursor, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDeepEnabled(bool)", asMETHODPR(Cursor, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Cursor, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Cursor, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(Cursor, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(Cursor, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetDisabledOffset(int, int)", asMETHODPR(Cursor, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Cursor, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Cursor, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEditable(bool)", asMETHODPR(Cursor, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_editable(bool)", asMETHODPR(Cursor, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetElementEventSender(bool)", asMETHODPR(Cursor, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_elementEventSender(bool)", asMETHODPR(Cursor, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnableAnchor(bool)", asMETHODPR(Cursor, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_enableAnchor(bool)", asMETHODPR(Cursor, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnabled(bool)", asMETHODPR(Cursor, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_enabled(bool)", asMETHODPR(Cursor, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetEnabledRecursive(bool)", asMETHODPR(Cursor, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedHeight(int)", asMETHODPR(Cursor, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Cursor, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedSize(int, int)", asMETHODPR(Cursor, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFixedWidth(int)", asMETHODPR(Cursor, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFocus(bool)", asMETHODPR(Cursor, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_focus(bool)", asMETHODPR(Cursor, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetFocusMode(FocusMode)", asMETHODPR(Cursor, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_focusMode(FocusMode)", asMETHODPR(Cursor, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetFullImageRect()", asMETHODPR(Cursor, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Cursor, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Cursor, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHeight(int)", asMETHODPR(Cursor, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_height(int)", asMETHODPR(Cursor, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Cursor, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Cursor, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetHovering(bool)", asMETHODPR(Cursor, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(Cursor, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(Cursor, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetHoverOffset(int, int)", asMETHODPR(Cursor, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetImageBorder(const IntRect&in)", asMETHODPR(Cursor, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_imageBorder(const IntRect&in)", asMETHODPR(Cursor, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetImageRect(const IntRect&in)", asMETHODPR(Cursor, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_imageRect(const IntRect&in)", asMETHODPR(Cursor, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetIndent(int)", asMETHODPR(Cursor, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_indent(int)", asMETHODPR(Cursor, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetIndentSpacing(int)", asMETHODPR(Cursor, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_indentSpacing(int)", asMETHODPR(Cursor, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetInstanceDefault(bool)", asMETHODPR(Cursor, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Cursor, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetInternal(bool)", asMETHODPR(Cursor, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_internal(bool)", asMETHODPR(Cursor, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Cursor, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Cursor, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Cursor, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Cursor, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Cursor, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutMode(LayoutMode)", asMETHODPR(Cursor, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutMode(LayoutMode)", asMETHODPR(Cursor, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetLayoutSpacing(int)", asMETHODPR(Cursor, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_layoutSpacing(int)", asMETHODPR(Cursor, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetMaterial(Material@+)", asMETHODPR(Cursor, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_material(Material@+)", asMETHODPR(Cursor, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Cursor, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Cursor, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Cursor, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxAnchor(float, float)", asMETHODPR(Cursor, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxHeight(int)", asMETHODPR(Cursor, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxHeight(int)", asMETHODPR(Cursor, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Cursor, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Cursor, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Cursor, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxSize(const IntVector2&in)", asMETHODPR(Cursor, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxSize(int, int)", asMETHODPR(Cursor, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMaxWidth(int)", asMETHODPR(Cursor, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_maxWidth(int)", asMETHODPR(Cursor, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Cursor, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minAnchor(const Vector2&in)", asMETHODPR(Cursor, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinAnchor(float, float)", asMETHODPR(Cursor, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinHeight(int)", asMETHODPR(Cursor, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minHeight(int)", asMETHODPR(Cursor, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Cursor, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minOffset(const IntVector2&in)", asMETHODPR(Cursor, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinSize(const IntVector2&in)", asMETHODPR(Cursor, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minSize(const IntVector2&in)", asMETHODPR(Cursor, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinSize(int, int)", asMETHODPR(Cursor, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetMinWidth(int)", asMETHODPR(Cursor, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_minWidth(int)", asMETHODPR(Cursor, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetName(const String&in)", asMETHODPR(Cursor, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_name(const String&in)", asMETHODPR(Cursor, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Cursor, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Cursor, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Cursor", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Cursor, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetOpacity(float)", asMETHODPR(Cursor, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_opacity(float)", asMETHODPR(Cursor, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Cursor, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPivot(const Vector2&in)", asMETHODPR(Cursor, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_pivot(const Vector2&in)", asMETHODPR(Cursor, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPivot(float, float)", asMETHODPR(Cursor, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPosition(const IntVector2&in)", asMETHODPR(Cursor, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_position(const IntVector2&in)", asMETHODPR(Cursor, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPosition(int, int)", asMETHODPR(Cursor, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetPriority(int)", asMETHODPR(Cursor, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_priority(int)", asMETHODPR(Cursor, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Cursor, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSelected(bool)", asMETHODPR(Cursor, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_selected(bool)", asMETHODPR(Cursor, SetSelected, (bool), void), asCALL_THISCALL);
    // void Cursor::SetShape(const String& shape) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetShape(const String&in)", asMETHODPR(Cursor, SetShape, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_shape(const String&in)", asMETHODPR(Cursor, SetShape, (const String&), void), asCALL_THISCALL);
    // void Cursor::SetShape(CursorShape shape) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetShape(CursorShape)", asMETHODPR(Cursor, SetShape, (CursorShape), void), asCALL_THISCALL);
    // void Cursor::SetShapesAttr(const VariantVector& value) | File: ../UI/Cursor.h
    // Error: type "const VariantVector&" can not automatically bind
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSize(const IntVector2&in)", asMETHODPR(Cursor, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_size(const IntVector2&in)", asMETHODPR(Cursor, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSize(int, int)", asMETHODPR(Cursor, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetSortChildren(bool)", asMETHODPR(Cursor, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_sortChildren(bool)", asMETHODPR(Cursor, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Cursor, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyle(const XMLElement&in)", asMETHODPR(Cursor, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Cursor, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetTags(Array<String>@+)", asFUNCTION(Cursor_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void SetTemporary(bool)", asMETHODPR(Cursor, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_temporary(bool)", asMETHODPR(Cursor, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTexture(Texture@+)", asMETHODPR(Cursor, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_texture(Texture@+)", asMETHODPR(Cursor, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Cursor, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Cursor", "void SetTiled(bool)", asMETHODPR(Cursor, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_tiled(bool)", asMETHODPR(Cursor, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetTraversalMode(TraversalMode)", asMETHODPR(Cursor, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_traversalMode(TraversalMode)", asMETHODPR(Cursor, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetUseDerivedOpacity(bool)", asMETHODPR(Cursor, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_useDerivedOpacity(bool)", asMETHODPR(Cursor, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void Cursor::SetUseSystemShapes(bool enable) | File: ../UI/Cursor.h
    engine->RegisterObjectMethod("Cursor", "void SetUseSystemShapes(bool)", asMETHODPR(Cursor, SetUseSystemShapes, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_useSystemShapes(bool)", asMETHODPR(Cursor, SetUseSystemShapes, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Cursor, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Cursor, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Cursor, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetVisible(bool)", asMETHODPR(Cursor, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_visible(bool)", asMETHODPR(Cursor, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SetWidth(int)", asMETHODPR(Cursor, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_width(int)", asMETHODPR(Cursor, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void SortChildren()", asMETHODPR(Cursor, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromAllEvents()", asMETHODPR(Cursor, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Cursor_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Cursor, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Cursor, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Cursor", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Cursor, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void Update(float)", asMETHODPR(Cursor, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Cursor", "void UpdateLayout()", asMETHODPR(Cursor, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Cursor", "int WeakRefs() const", asMETHODPR(Cursor, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "int get_weakRefs() const", asMETHODPR(Cursor, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Cursor, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Cursor, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Cursor", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Cursor, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("CustomGeometry", "void AddLight(Light@+)", asMETHODPR(CustomGeometry, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_ADDREF, "void f()", asMETHODPR(CustomGeometry, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void AddVertexLight(Light@+)", asMETHODPR(CustomGeometry, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void AllocateNetworkState()", asMETHODPR(CustomGeometry, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void ApplyAttributes()", asMETHODPR(CustomGeometry, ApplyAttributes, (), void), asCALL_THISCALL);
    // void CustomGeometry::BeginGeometry(unsigned index, PrimitiveType type) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void BeginGeometry(uint, PrimitiveType)", asMETHODPR(CustomGeometry, BeginGeometry, (unsigned, PrimitiveType), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void CustomGeometry::Clear() | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void Clear()", asMETHODPR(CustomGeometry, Clear, (), void), asCALL_THISCALL);
    // void CustomGeometry::Commit() | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void Commit()", asMETHODPR(CustomGeometry, Commit, (), void), asCALL_THISCALL);
    // explicit CustomGeometry::CustomGeometry(Context* context) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_FACTORY, "CustomGeometry@+ f()", asFUNCTION(CustomGeometry_CustomGeometry_Context), asCALL_CDECL);
    // void CustomGeometry::DefineColor(const Color& color) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineColor(const Color&in)", asMETHODPR(CustomGeometry, DefineColor, (const Color&), void), asCALL_THISCALL);
    // void CustomGeometry::DefineGeometry(unsigned index, PrimitiveType type, unsigned numVertices, bool hasNormals, bool hasColors, bool hasTexCoords, bool hasTangents) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineGeometry(uint, PrimitiveType, uint, bool, bool, bool, bool)", asMETHODPR(CustomGeometry, DefineGeometry, (unsigned, PrimitiveType, unsigned, bool, bool, bool, bool), void), asCALL_THISCALL);
    // void CustomGeometry::DefineNormal(const Vector3& normal) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineNormal(const Vector3&in)", asMETHODPR(CustomGeometry, DefineNormal, (const Vector3&), void), asCALL_THISCALL);
    // void CustomGeometry::DefineTangent(const Vector4& tangent) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineTangent(const Vector4&in)", asMETHODPR(CustomGeometry, DefineTangent, (const Vector4&), void), asCALL_THISCALL);
    // void CustomGeometry::DefineTexCoord(const Vector2& texCoord) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineTexCoord(const Vector2&in)", asMETHODPR(CustomGeometry, DefineTexCoord, (const Vector2&), void), asCALL_THISCALL);
    // void CustomGeometry::DefineVertex(const Vector3& position) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void DefineVertex(const Vector3&in)", asMETHODPR(CustomGeometry, DefineVertex, (const Vector3&), void), asCALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(CustomGeometry, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool CustomGeometry::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(CustomGeometry, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetAnimationEnabled() const", asMETHODPR(CustomGeometry, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_animationEnabled() const", asMETHODPR(CustomGeometry, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttribute(uint) const", asMETHODPR(CustomGeometry, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Variant get_attributes(uint) const", asMETHODPR(CustomGeometry, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttribute(const String&in) const", asMETHODPR(CustomGeometry, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CustomGeometry, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CustomGeometry, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CustomGeometry, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CustomGeometry, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttributeDefault(uint) const", asMETHODPR(CustomGeometry, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Variant get_attributeDefaults(uint) const", asMETHODPR(CustomGeometry, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CustomGeometry, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetBlockEvents() const", asMETHODPR(CustomGeometry, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& GetBoundingBox() const", asMETHODPR(CustomGeometry, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& get_boundingBox() const", asMETHODPR(CustomGeometry, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetCastShadows() const", asMETHODPR(CustomGeometry, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_castShadows() const", asMETHODPR(CustomGeometry, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const String& GetCategory() const", asMETHODPR(CustomGeometry, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const String& get_category() const", asMETHODPR(CustomGeometry, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Component@+ GetComponent(StringHash) const", asMETHODPR(CustomGeometry, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("CustomGeometry", "float GetDistance() const", asMETHODPR(CustomGeometry, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint8 GetDrawableFlags() const", asMETHODPR(CustomGeometry, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetDrawDistance() const", asMETHODPR(CustomGeometry, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_drawDistance() const", asMETHODPR(CustomGeometry, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "VariantMap& GetEventDataMap() const", asMETHODPR(CustomGeometry, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "Object@+ GetEventSender() const", asMETHODPR(CustomGeometry, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Light@+ GetFirstLight() const", asMETHODPR(CustomGeometry, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // PODVector<unsigned char> CustomGeometry::GetGeometryDataAttr() const | File: ../Graphics/CustomGeometry.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CustomGeometry, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CustomGeometry, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const VariantMap& GetGlobalVars() const", asMETHODPR(CustomGeometry, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const VariantMap& get_globalVars() const", asMETHODPR(CustomGeometry, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetID() const", asMETHODPR(CustomGeometry, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_id() const", asMETHODPR(CustomGeometry, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CustomGeometry, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetLightMask() const", asMETHODPR(CustomGeometry, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_lightMask() const", asMETHODPR(CustomGeometry, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Array<Light@>@ GetLights() const", asFUNCTION(CustomGeometry_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetLodBias() const", asMETHODPR(CustomGeometry, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_lodBias() const", asMETHODPR(CustomGeometry, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetLodDistance() const", asMETHODPR(CustomGeometry, GetLodDistance, () const, float), asCALL_THISCALL);
    // Geometry* CustomGeometry::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(CustomGeometry, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* CustomGeometry::GetMaterial(unsigned index=0) const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "Material@+ GetMaterial(uint = 0) const", asMETHODPR(CustomGeometry, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Material@+ get_materials(uint = 0) const", asMETHODPR(CustomGeometry, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    // const ResourceRefList& CustomGeometry::GetMaterialsAttr() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "const ResourceRefList& GetMaterialsAttr() const", asMETHODPR(CustomGeometry, GetMaterialsAttr, () const, const ResourceRefList&), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetMaxLights() const", asMETHODPR(CustomGeometry, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_maxLights() const", asMETHODPR(CustomGeometry, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetMaxZ() const", asMETHODPR(CustomGeometry, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetMinZ() const", asMETHODPR(CustomGeometry, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Node@+ GetNode() const", asMETHODPR(CustomGeometry, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Node@+ get_node() const", asMETHODPR(CustomGeometry, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumAttributes() const", asMETHODPR(CustomGeometry, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numAttributes() const", asMETHODPR(CustomGeometry, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned CustomGeometry::GetNumGeometries() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumGeometries() const", asMETHODPR(CustomGeometry, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numGeometries() const", asMETHODPR(CustomGeometry, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumNetworkAttributes() const", asMETHODPR(CustomGeometry, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned CustomGeometry::GetNumOccluderTriangles() override | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumOccluderTriangles()", asMETHODPR(CustomGeometry, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // unsigned CustomGeometry::GetNumVertices(unsigned index) const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetNumVertices(uint) const", asMETHODPR(CustomGeometry, GetNumVertices, (unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_numVertices(uint) const", asMETHODPR(CustomGeometry, GetNumVertices, (unsigned) const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CustomGeometry, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CustomGeometry, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CustomGeometry, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "Scene@+ GetScene() const", asMETHODPR(CustomGeometry, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetShadowDistance() const", asMETHODPR(CustomGeometry, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "float get_shadowDistance() const", asMETHODPR(CustomGeometry, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetShadowMask() const", asMETHODPR(CustomGeometry, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_shadowMask() const", asMETHODPR(CustomGeometry, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "float GetSortValue() const", asMETHODPR(CustomGeometry, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CustomGeometry, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "StringHash GetType() const", asMETHODPR(CustomGeometry, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "StringHash get_type() const", asMETHODPR(CustomGeometry, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "const String& GetTypeName() const", asMETHODPR(CustomGeometry, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const String& get_typeName() const", asMETHODPR(CustomGeometry, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(CustomGeometry, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // CustomGeometryVertex* CustomGeometry::GetVertex(unsigned geometryIndex, unsigned vertexNum) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "CustomGeometryVertex@+ GetVertex(uint, uint)", asMETHODPR(CustomGeometry, GetVertex, (unsigned, unsigned), CustomGeometryVertex*), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Array<Light@>@ GetVertexLights() const", asFUNCTION(CustomGeometry_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // Vector<PODVector<CustomGeometryVertex>>& CustomGeometry::GetVertices() | File: ../Graphics/CustomGeometry.h
    // Error: type "Vector<PODVector<CustomGeometryVertex>>&" can not automatically bind
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetViewMask() const", asMETHODPR(CustomGeometry, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_viewMask() const", asMETHODPR(CustomGeometry, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(CustomGeometry, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(CustomGeometry, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "Zone@+ GetZone() const", asMETHODPR(CustomGeometry, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "Zone@+ get_zone() const", asMETHODPR(CustomGeometry, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "uint GetZoneMask() const", asMETHODPR(CustomGeometry, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "uint get_zoneMask() const", asMETHODPR(CustomGeometry, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasBasePass(uint) const", asMETHODPR(CustomGeometry, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasEventHandlers() const", asMETHODPR(CustomGeometry, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CustomGeometry, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CustomGeometry, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool CustomGeometry::IsDynamic() const | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsDynamic() const", asMETHODPR(CustomGeometry, IsDynamic, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_dynamic() const", asMETHODPR(CustomGeometry, IsDynamic, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsEnabled() const", asMETHODPR(CustomGeometry, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_enabled() const", asMETHODPR(CustomGeometry, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsEnabledEffective() const", asMETHODPR(CustomGeometry, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_enabledEffective() const", asMETHODPR(CustomGeometry, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInstanceOf(StringHash) const", asMETHODPR(CustomGeometry, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView() const", asMETHODPR(CustomGeometry, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_inView() const", asMETHODPR(CustomGeometry, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView(Camera@+) const", asMETHODPR(CustomGeometry, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(CustomGeometry, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsOccludee() const", asMETHODPR(CustomGeometry, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_occludee() const", asMETHODPR(CustomGeometry, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsOccluder() const", asMETHODPR(CustomGeometry, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_occluder() const", asMETHODPR(CustomGeometry, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsReplicated() const", asMETHODPR(CustomGeometry, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_replicated() const", asMETHODPR(CustomGeometry, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsTemporary() const", asMETHODPR(CustomGeometry, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool get_temporary() const", asMETHODPR(CustomGeometry, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool IsZoneDirty() const", asMETHODPR(CustomGeometry, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void LimitLights()", asMETHODPR(CustomGeometry, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void LimitVertexLights(bool)", asMETHODPR(CustomGeometry, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool Load(Deserializer&)", asMETHODPR(CustomGeometry, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CustomGeometry, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool LoadXML(const XMLElement&in)", asMETHODPR(CustomGeometry, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkForUpdate()", asMETHODPR(CustomGeometry, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkInView(const FrameInfo&in)", asMETHODPR(CustomGeometry, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkInView(uint)", asMETHODPR(CustomGeometry, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void MarkNetworkUpdate()", asMETHODPR(CustomGeometry, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CustomGeometry, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CustomGeometry, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CustomGeometry, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void OnSetEnabled()", asMETHODPR(CustomGeometry, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void PrepareNetworkUpdate()", asMETHODPR(CustomGeometry, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void CustomGeometry::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/CustomGeometry.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CustomGeometry, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CustomGeometry, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CustomGeometry", "int Refs() const", asMETHODPR(CustomGeometry, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "int get_refs() const", asMETHODPR(CustomGeometry, Refs, () const, int), asCALL_THISCALL);
    // static void CustomGeometry::RegisterObject(Context* context) | File: ../Graphics/CustomGeometry.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CustomGeometry", asBEHAVE_RELEASE, "void f()", asMETHODPR(CustomGeometry, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void Remove()", asMETHODPR(CustomGeometry, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CustomGeometry, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveInstanceDefault()", asMETHODPR(CustomGeometry, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void RemoveObjectAnimation()", asMETHODPR(CustomGeometry, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void ResetToDefault()", asMETHODPR(CustomGeometry, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool Save(Serializer&) const", asMETHODPR(CustomGeometry, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveDefaultAttributes() const", asMETHODPR(CustomGeometry, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveJSON(JSONValue&) const", asMETHODPR(CustomGeometry, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SaveXML(XMLElement&) const", asMETHODPR(CustomGeometry, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SendEvent(StringHash)", asMETHODPR(CustomGeometry, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CustomGeometry, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAnimationEnabled(bool)", asMETHODPR(CustomGeometry, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_animationEnabled(bool)", asMETHODPR(CustomGeometry, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAnimationTime(float)", asMETHODPR(CustomGeometry, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CustomGeometry, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CustomGeometry, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CustomGeometry, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CustomGeometry, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CustomGeometry, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CustomGeometry, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CustomGeometry, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetBasePass(uint)", asMETHODPR(CustomGeometry, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetBlockEvents(bool)", asMETHODPR(CustomGeometry, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetCastShadows(bool)", asMETHODPR(CustomGeometry, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_castShadows(bool)", asMETHODPR(CustomGeometry, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetDrawDistance(float)", asMETHODPR(CustomGeometry, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_drawDistance(float)", asMETHODPR(CustomGeometry, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void CustomGeometry::SetDynamic(bool enable) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetDynamic(bool)", asMETHODPR(CustomGeometry, SetDynamic, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_dynamic(bool)", asMETHODPR(CustomGeometry, SetDynamic, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetEnabled(bool)", asMETHODPR(CustomGeometry, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_enabled(bool)", asMETHODPR(CustomGeometry, SetEnabled, (bool), void), asCALL_THISCALL);
    // void CustomGeometry::SetGeometryDataAttr(const PODVector<unsigned char>& value) | File: ../Graphics/CustomGeometry.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CustomGeometry, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CustomGeometry, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetInstanceDefault(bool)", asMETHODPR(CustomGeometry, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CustomGeometry, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetLightMask(uint)", asMETHODPR(CustomGeometry, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_lightMask(uint)", asMETHODPR(CustomGeometry, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetLodBias(float)", asMETHODPR(CustomGeometry, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_lodBias(float)", asMETHODPR(CustomGeometry, SetLodBias, (float), void), asCALL_THISCALL);
    // void CustomGeometry::SetMaterial(Material* material) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaterial(Material@+)", asMETHODPR(CustomGeometry, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_material(Material@+)", asMETHODPR(CustomGeometry, SetMaterial, (Material*), void), asCALL_THISCALL);
    // bool CustomGeometry::SetMaterial(unsigned index, Material* material) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "bool SetMaterial(uint, Material@+)", asMETHODPR(CustomGeometry, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "bool set_materials(uint, Material@+)", asMETHODPR(CustomGeometry, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    // void CustomGeometry::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaterialsAttr(const ResourceRefList&in)", asMETHODPR(CustomGeometry, SetMaterialsAttr, (const ResourceRefList&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMaxLights(uint)", asMETHODPR(CustomGeometry, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_maxLights(uint)", asMETHODPR(CustomGeometry, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetMinMaxZ(float, float)", asMETHODPR(CustomGeometry, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void CustomGeometry::SetNumGeometries(unsigned num) | File: ../Graphics/CustomGeometry.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetNumGeometries(uint)", asMETHODPR(CustomGeometry, SetNumGeometries, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_numGeometries(uint)", asMETHODPR(CustomGeometry, SetNumGeometries, (unsigned), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CustomGeometry, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CustomGeometry, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CustomGeometry, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetOccludee(bool)", asMETHODPR(CustomGeometry, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_occludee(bool)", asMETHODPR(CustomGeometry, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetOccluder(bool)", asMETHODPR(CustomGeometry, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_occluder(bool)", asMETHODPR(CustomGeometry, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetShadowDistance(float)", asMETHODPR(CustomGeometry, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_shadowDistance(float)", asMETHODPR(CustomGeometry, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetShadowMask(uint)", asMETHODPR(CustomGeometry, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_shadowMask(uint)", asMETHODPR(CustomGeometry, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetSortValue(float)", asMETHODPR(CustomGeometry, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetTemporary(bool)", asMETHODPR(CustomGeometry, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_temporary(bool)", asMETHODPR(CustomGeometry, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetViewMask(uint)", asMETHODPR(CustomGeometry, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_viewMask(uint)", asMETHODPR(CustomGeometry, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetZone(Zone@+, bool = false)", asMETHODPR(CustomGeometry, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void SetZoneMask(uint)", asMETHODPR(CustomGeometry, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "void set_zoneMask(uint)", asMETHODPR(CustomGeometry, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromAllEvents()", asMETHODPR(CustomGeometry, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CustomGeometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CustomGeometry, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CustomGeometry, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CustomGeometry", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CustomGeometry, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void Update(const FrameInfo&in)", asMETHODPR(CustomGeometry, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(CustomGeometry, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("CustomGeometry", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(CustomGeometry, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CustomGeometry", "int WeakRefs() const", asMETHODPR(CustomGeometry, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CustomGeometry", "int get_weakRefs() const", asMETHODPR(CustomGeometry, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CustomGeometry, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CustomGeometry, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CustomGeometry", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CustomGeometry, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CollisionGeometryData", asBEHAVE_ADDREF, "void f()", asMETHODPR(CollisionGeometryData, AddRef, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionGeometryData", "int Refs() const", asMETHODPR(CollisionGeometryData, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionGeometryData", "int get_refs() const", asMETHODPR(CollisionGeometryData, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CollisionGeometryData", asBEHAVE_RELEASE, "void f()", asMETHODPR(CollisionGeometryData, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CollisionGeometryData", "int WeakRefs() const", asMETHODPR(CollisionGeometryData, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionGeometryData", "int get_weakRefs() const", asMETHODPR(CollisionGeometryData, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f()", asFUNCTION(ColorFrame_ColorFrame_void), asCALL_CDECL);
    // explicit ColorFrame::ColorFrame(const Color& color) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in)", asFUNCTION(ColorFrame_ColorFrame_Color), asCALL_CDECL);
    // ColorFrame::ColorFrame(const Color& color, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_FACTORY, "ColorFrame@+ f(const Color&in, float)", asFUNCTION(ColorFrame_ColorFrame_Color_float), asCALL_CDECL);
    // Color ColorFrame::Interpolate(const ColorFrame& next, float time) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ColorFrame", "Color Interpolate(const ColorFrame&in, float) const", asMETHODPR(ColorFrame, Interpolate, (const ColorFrame&, float) const, Color), asCALL_THISCALL);
    // ColorFrame& ColorFrame::operator=(const ColorFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ColorFrame>(engine, "ColorFrame");
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ColorFrame", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_ADDREF, "void f()", asMETHODPR(ConvexData, AddRef, (), void), asCALL_THISCALL);
    // void ConvexData::BuildHull(const PODVector<Vector3>& vertices) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectMethod("ConvexData", "void BuildHull(Array<Vector3>@+)", asFUNCTION(ConvexData_BuildHull_PODVectorVector3), asCALL_CDECL_OBJFIRST);
    // ConvexData::ConvexData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(Model@+, uint)", asFUNCTION(ConvexData_ConvexData_Model_unsigned), asCALL_CDECL);
    // explicit ConvexData::ConvexData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_FACTORY, "ConvexData@+ f(CustomGeometry@+)", asFUNCTION(ConvexData_ConvexData_CustomGeometry), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConvexData", "int Refs() const", asMETHODPR(ConvexData, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConvexData", "int get_refs() const", asMETHODPR(ConvexData, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ConvexData", asBEHAVE_RELEASE, "void f()", asMETHODPR(ConvexData, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ConvexData", "int WeakRefs() const", asMETHODPR(ConvexData, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConvexData", "int get_weakRefs() const", asMETHODPR(ConvexData, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CursorShapeInfo", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(CursorShapeInfo_CursorShapeInfo_int), asCALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CustomGeometryVertex", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_CustomGeometryVertex
    REGISTER_MANUAL_PART_CustomGeometryVertex(CustomGeometryVertex, "CustomGeometryVertex")
#endif

}

}
