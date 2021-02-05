// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ValueAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ValueAnimation* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit ValueAnimation::ValueAnimation(Context* context) | File: ../Scene/ValueAnimation.h
static ValueAnimation* ValueAnimation_ValueAnimation_Context()
{
    return new ValueAnimation(GetScriptContext());
}

// ValueAnimationInfo::ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
static ValueAnimationInfo* ValueAnimationInfo_ValueAnimationInfo_ValueAnimation_WrapMode_float(ValueAnimation *animation, WrapMode wrapMode, float speed)
{
    return new ValueAnimationInfo(animation, wrapMode, speed);
}

// ValueAnimationInfo::ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
static ValueAnimationInfo* ValueAnimationInfo_ValueAnimationInfo_Object_ValueAnimation_WrapMode_float(Object *target, ValueAnimation *animation, WrapMode wrapMode, float speed)
{
    return new ValueAnimationInfo(target, animation, wrapMode, speed);
}

// ValueAnimationInfo::ValueAnimationInfo(const ValueAnimationInfo& other) | File: ../Scene/ValueAnimationInfo.h
static ValueAnimationInfo* ValueAnimationInfo_ValueAnimationInfo_ValueAnimationInfo(const ValueAnimationInfo &other)
{
    return new ValueAnimationInfo(other);
}

// const StringVector& Variant::GetStringVector() const | File: ../Core/Variant.h
static CScriptArray* Variant_GetStringVector_void(Variant* ptr)
{
    const StringVector& result = ptr->GetStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// Variant& Variant::operator=(const StringVector& rhs) | File: ../Core/Variant.h
static Variant& Variant_operatorequals_StringVector(Variant* ptr, CScriptArray* rhs_conv)
{
    StringVector rhs = ArrayToVector<String>(rhs_conv);
    Variant& result = ptr->operator=(rhs);
    return result;
}

// bool Variant::operator==(const StringVector& rhs) const | File: ../Core/Variant.h
static bool Variant_operatorequalsequals_StringVector(Variant* ptr, CScriptArray* rhs_conv)
{
    StringVector rhs = ArrayToVector<String>(rhs_conv);
    bool result = ptr->operator==(rhs);
    return result;
}

// Variant::Variant(int value) | File: ../Core/Variant.h
static void Variant_Variant_int(Variant* ptr, int value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(long long value) | File: ../Core/Variant.h
static void Variant_Variant_longlong(Variant* ptr, long long value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(unsigned value) | File: ../Core/Variant.h
static void Variant_Variant_unsigned(Variant* ptr, unsigned value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(unsigned long long value) | File: ../Core/Variant.h
static void Variant_Variant_unsignedlonglong(Variant* ptr, unsigned long long value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const StringHash& value) | File: ../Core/Variant.h
static void Variant_Variant_StringHash(Variant* ptr, const StringHash &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(bool value) | File: ../Core/Variant.h
static void Variant_Variant_bool(Variant* ptr, bool value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(float value) | File: ../Core/Variant.h
static void Variant_Variant_float(Variant* ptr, float value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(double value) | File: ../Core/Variant.h
static void Variant_Variant_double(Variant* ptr, double value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Vector2& value) | File: ../Core/Variant.h
static void Variant_Variant_Vector2(Variant* ptr, const Vector2 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Vector3& value) | File: ../Core/Variant.h
static void Variant_Variant_Vector3(Variant* ptr, const Vector3 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Vector4& value) | File: ../Core/Variant.h
static void Variant_Variant_Vector4(Variant* ptr, const Vector4 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Quaternion& value) | File: ../Core/Variant.h
static void Variant_Variant_Quaternion(Variant* ptr, const Quaternion &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Color& value) | File: ../Core/Variant.h
static void Variant_Variant_Color(Variant* ptr, const Color &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const String& value) | File: ../Core/Variant.h
static void Variant_Variant_String(Variant* ptr, const String &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const VectorBuffer& value) | File: ../Core/Variant.h
static void Variant_Variant_VectorBuffer(Variant* ptr, const VectorBuffer &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const ResourceRef& value) | File: ../Core/Variant.h
static void Variant_Variant_ResourceRef(Variant* ptr, const ResourceRef &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const ResourceRefList& value) | File: ../Core/Variant.h
static void Variant_Variant_ResourceRefList(Variant* ptr, const ResourceRefList &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const VariantMap& value) | File: ../Core/Variant.h
static void Variant_Variant_VariantMap(Variant* ptr, const VariantMap &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Rect& value) | File: ../Core/Variant.h
static void Variant_Variant_Rect(Variant* ptr, const Rect &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const IntRect& value) | File: ../Core/Variant.h
static void Variant_Variant_IntRect(Variant* ptr, const IntRect &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const IntVector2& value) | File: ../Core/Variant.h
static void Variant_Variant_IntVector2(Variant* ptr, const IntVector2 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const IntVector3& value) | File: ../Core/Variant.h
static void Variant_Variant_IntVector3(Variant* ptr, const IntVector3 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(RefCounted* value) | File: ../Core/Variant.h
static void Variant_Variant_RefCounted(Variant* ptr, RefCounted *value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Matrix3& value) | File: ../Core/Variant.h
static void Variant_Variant_Matrix3(Variant* ptr, const Matrix3 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Matrix3x4& value) | File: ../Core/Variant.h
static void Variant_Variant_Matrix3x4(Variant* ptr, const Matrix3x4 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const Matrix4& value) | File: ../Core/Variant.h
static void Variant_Variant_Matrix4(Variant* ptr, const Matrix4 &value)
{
    new(ptr) Variant(value);
}

// Variant::Variant(const String& type, const String& value) | File: ../Core/Variant.h
static void Variant_Variant_String_String(Variant* ptr, const String &type, const String &value)
{
    new(ptr) Variant(type, value);
}

// Variant::Variant(VariantType type, const String& value) | File: ../Core/Variant.h
static void Variant_Variant_VariantType_String(Variant* ptr, VariantType type, const String &value)
{
    new(ptr) Variant(type, value);
}

// Variant::Variant(const Variant& value) | File: ../Core/Variant.h
static void Variant_Variant_Variant(Variant* ptr, const Variant &value)
{
    new(ptr) Variant(value);
}

// Vector2::Vector2(const Vector2& vector) noexcept=default | File: ../Math/Vector2.h
static void Vector2_Vector2_Vector2(Vector2* ptr, const Vector2 &vector)
{
    new(ptr) Vector2(vector);
}

// explicit Vector2::Vector2(const IntVector2& vector) noexcept | File: ../Math/Vector2.h
static void Vector2_Vector2_IntVector2(Vector2* ptr, const IntVector2 &vector)
{
    new(ptr) Vector2(vector);
}

// Vector2::Vector2(float x, float y) noexcept | File: ../Math/Vector2.h
static void Vector2_Vector2_float_float(Vector2* ptr, float x, float y)
{
    new(ptr) Vector2(x, y);
}

// Vector3::Vector3(const Vector3& vector) noexcept=default | File: ../Math/Vector3.h
static void Vector3_Vector3_Vector3(Vector3* ptr, const Vector3 &vector)
{
    new(ptr) Vector3(vector);
}

// Vector3::Vector3(const Vector2& vector, float z) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_Vector2_float(Vector3* ptr, const Vector2 &vector, float z)
{
    new(ptr) Vector3(vector, z);
}

// explicit Vector3::Vector3(const Vector2& vector) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_Vector2(Vector3* ptr, const Vector2 &vector)
{
    new(ptr) Vector3(vector);
}

// explicit Vector3::Vector3(const IntVector3& vector) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_IntVector3(Vector3* ptr, const IntVector3 &vector)
{
    new(ptr) Vector3(vector);
}

// Vector3::Vector3(float x, float y, float z) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_float_float_float(Vector3* ptr, float x, float y, float z)
{
    new(ptr) Vector3(x, y, z);
}

// Vector3::Vector3(float x, float y) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_float_float(Vector3* ptr, float x, float y)
{
    new(ptr) Vector3(x, y);
}

// Vector4::Vector4(const Vector4& vector) noexcept=default | File: ../Math/Vector4.h
static void Vector4_Vector4_Vector4(Vector4* ptr, const Vector4 &vector)
{
    new(ptr) Vector4(vector);
}

// Vector4::Vector4(const Vector3& vector, float w) noexcept | File: ../Math/Vector4.h
static void Vector4_Vector4_Vector3_float(Vector4* ptr, const Vector3 &vector, float w)
{
    new(ptr) Vector4(vector, w);
}

// Vector4::Vector4(float x, float y, float z, float w) noexcept | File: ../Math/Vector4.h
static void Vector4_Vector4_float_float_float_float(Vector4* ptr, float x, float y, float z, float w)
{
    new(ptr) Vector4(x, y, z, w);
}

// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* VectorBuffer_ReadStringVector_void(VectorBuffer* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// VectorBuffer::VectorBuffer(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h
static void VectorBuffer_VectorBuffer_Deserializer_unsigned(VectorBuffer* ptr, Deserializer &source, unsigned size)
{
    new(ptr) VectorBuffer(source, size);
}

// bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
static bool VectorBuffer_WriteStringVector_StringVector(VectorBuffer* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->WriteStringVector(value);
    return result;
}

// static unsigned VertexBuffer::GetElementOffset(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
static unsigned VertexBuffer_GetElementOffset_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar(CScriptArray* elements_conv, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    PODVector<VertexElement> elements = ArrayToPODVector<VertexElement>(elements_conv);
    unsigned result = VertexBuffer::GetElementOffset(elements, type, semantic, index);
    return result;
}

// const PODVector<VertexElement>& VertexBuffer::GetElements() const | File: ../Graphics/VertexBuffer.h
static CScriptArray* VertexBuffer_GetElements_void(VertexBuffer* ptr)
{
    const PODVector<VertexElement>& result = ptr->GetElements();
    return VectorToArray(result, "Array<VertexElement>");
}

// static PODVector<VertexElement> VertexBuffer::GetElements(unsigned elementMask) | File: ../Graphics/VertexBuffer.h
static CScriptArray* VertexBuffer_GetElements_unsigned(unsigned elementMask)
{
    PODVector<VertexElement> result = VertexBuffer::GetElements(elementMask);
    return VectorToArray(result, "Array<VertexElement>");
}

// static unsigned VertexBuffer::GetVertexSize(const PODVector<VertexElement>& elements) | File: ../Graphics/VertexBuffer.h
static unsigned VertexBuffer_GetVertexSize_PODVectorVertexElement(CScriptArray* elements_conv)
{
    PODVector<VertexElement> elements = ArrayToPODVector<VertexElement>(elements_conv);
    unsigned result = VertexBuffer::GetVertexSize(elements);
    return result;
}

// static bool VertexBuffer::HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
static bool VertexBuffer_HasElement_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar(CScriptArray* elements_conv, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    PODVector<VertexElement> elements = ArrayToPODVector<VertexElement>(elements_conv);
    bool result = VertexBuffer::HasElement(elements, type, semantic, index);
    return result;
}

// bool VertexBuffer::SetSize(unsigned vertexCount, const PODVector<VertexElement>& elements, bool dynamic=false) | File: ../Graphics/VertexBuffer.h
static bool VertexBuffer_SetSize_unsigned_PODVectorVertexElement_bool(VertexBuffer* ptr, unsigned vertexCount, CScriptArray* elements_conv, bool dynamic)
{
    PODVector<VertexElement> elements = ArrayToPODVector<VertexElement>(elements_conv);
    bool result = ptr->SetSize(vertexCount, elements, dynamic);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void VertexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(VertexBuffer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit VertexBuffer::VertexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/VertexBuffer.h
static VertexBuffer* VertexBuffer_VertexBuffer_Context_bool(bool forceHeadless=false)
{
    return new VertexBuffer(GetScriptContext(), forceHeadless);
}

// const PODVector<Drawable*>& View::GetGeometries() const | File: ../Graphics/View.h
static CScriptArray* View_GetGeometries_void(View* ptr)
{
    const PODVector<Drawable*>& result = ptr->GetGeometries();
    return VectorToHandleArray(result, "Array<Drawable@>");
}

// const PODVector<Light*>& View::GetLights() const | File: ../Graphics/View.h
static CScriptArray* View_GetLights_void(View* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Drawable*>& View::GetOccluders() const | File: ../Graphics/View.h
static CScriptArray* View_GetOccluders_void(View* ptr)
{
    const PODVector<Drawable*>& result = ptr->GetOccluders();
    return VectorToHandleArray(result, "Array<Drawable@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void View_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(View* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit View::View(Context* context) | File: ../Graphics/View.h
static View* View_View_Context()
{
    return new View(GetScriptContext());
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void View3D_AddTags_StringVector(View3D* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* View3D_GetChildren_void(View3D* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* View3D_GetChildren_bool(View3D* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* View3D_GetChildrenWithTag_String_bool(View3D* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* View3D_GetTags_void(View3D* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void View3D_SetTags_StringVector(View3D* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void View3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(View3D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit View3D::View3D(Context* context) | File: ../UI/View3D.h
static View3D* View3D_View3D_Context()
{
    return new View3D(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Viewport_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Viewport* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Viewport::Viewport(Context* context) | File: ../Graphics/Viewport.h
static Viewport* Viewport_Viewport_Context()
{
    return new Viewport(GetScriptContext());
}

// Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
static Viewport* Viewport_Viewport_Context_Scene_Camera_RenderPath(Scene *scene, Camera *camera, RenderPath *renderPath=nullptr)
{
    return new Viewport(GetScriptContext(), scene, camera, renderPath);
}

// Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
static Viewport* Viewport_Viewport_Context_Scene_Camera_IntRect_RenderPath(Scene *scene, Camera *camera, const IntRect &rect, RenderPath *renderPath=nullptr)
{
    return new Viewport(GetScriptContext(), scene, camera, rect, renderPath);
}

// VertexElement::VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0, bool perInstance=false) noexcept | File: ../Graphics/GraphicsDefs.h
static void VertexElement_VertexElement_VertexElementType_VertexElementSemantic_unsignedchar_bool(VertexElement* ptr, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0, bool perInstance=false)
{
    new(ptr) VertexElement(type, semantic, index, perInstance);
}

void ASRegisterGenerated_Members_V(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_ADDREF, "void f()", asMETHODPR(ValueAnimation, AddRef, (), void), asCALL_THISCALL);
    // bool ValueAnimation::BeginLoad(Deserializer& source) override | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool BeginLoad(Deserializer&)", asMETHODPR(ValueAnimation, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool EndLoad()", asMETHODPR(ValueAnimation, EndLoad, (), bool), asCALL_THISCALL);
    // Variant ValueAnimation::GetAnimationValue(float scaledTime) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "Variant GetAnimationValue(float) const", asMETHODPR(ValueAnimation, GetAnimationValue, (float) const, Variant), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(ValueAnimation, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // float ValueAnimation::GetBeginTime() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetBeginTime() const", asMETHODPR(ValueAnimation, GetBeginTime, () const, float), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool GetBlockEvents() const", asMETHODPR(ValueAnimation, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetCategory() const", asMETHODPR(ValueAnimation, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_category() const", asMETHODPR(ValueAnimation, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ValueAnimation::GetEndTime() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetEndTime() const", asMETHODPR(ValueAnimation, GetEndTime, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "VariantMap& GetEventDataMap() const", asMETHODPR(ValueAnimation, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // void ValueAnimation::GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames) const | File: ../Scene/ValueAnimation.h
    // Error: type "PODVector<const VAnimEventFrame*>&" can not automatically bind
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "Object@+ GetEventSender() const", asMETHODPR(ValueAnimation, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ValueAnimation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ValueAnimation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const VariantMap& GetGlobalVars() const", asMETHODPR(ValueAnimation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const VariantMap& get_globalVars() const", asMETHODPR(ValueAnimation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // InterpMethod ValueAnimation::GetInterpolationMethod() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "InterpMethod GetInterpolationMethod() const", asMETHODPR(ValueAnimation, GetInterpolationMethod, () const, InterpMethod), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "InterpMethod get_interpolationMethod() const", asMETHODPR(ValueAnimation, GetInterpolationMethod, () const, InterpMethod), asCALL_THISCALL);
    // const Vector<VAnimKeyFrame>& ValueAnimation::GetKeyFrames() const | File: ../Scene/ValueAnimation.h
    // Error: type "const Vector<VAnimKeyFrame>&" can not automatically bind
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "uint GetMemoryUse() const", asMETHODPR(ValueAnimation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "uint get_memoryUse() const", asMETHODPR(ValueAnimation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetName() const", asMETHODPR(ValueAnimation, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_name() const", asMETHODPR(ValueAnimation, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "StringHash GetNameHash() const", asMETHODPR(ValueAnimation, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // void* ValueAnimation::GetOwner() const | File: ../Scene/ValueAnimation.h
    // Error: type "void*" can not automatically bind
    // float ValueAnimation::GetSplineTension() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetSplineTension() const", asMETHODPR(ValueAnimation, GetSplineTension, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "float get_splineTension() const", asMETHODPR(ValueAnimation, GetSplineTension, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ValueAnimation, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "StringHash GetType() const", asMETHODPR(ValueAnimation, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "StringHash get_type() const", asMETHODPR(ValueAnimation, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetTypeName() const", asMETHODPR(ValueAnimation, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_typeName() const", asMETHODPR(ValueAnimation, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "uint GetUseTimer()", asMETHODPR(ValueAnimation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "uint get_useTimer()", asMETHODPR(ValueAnimation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // VariantType ValueAnimation::GetValueType() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "VariantType GetValueType() const", asMETHODPR(ValueAnimation, GetValueType, () const, VariantType), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "VariantType get_valueType() const", asMETHODPR(ValueAnimation, GetValueType, () const, VariantType), asCALL_THISCALL);
    // bool ValueAnimation::HasEventFrames() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasEventFrames() const", asMETHODPR(ValueAnimation, HasEventFrames, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasEventHandlers() const", asMETHODPR(ValueAnimation, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ValueAnimation, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ValueAnimation, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool IsInstanceOf(StringHash) const", asMETHODPR(ValueAnimation, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool ValueAnimation::IsValid() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool IsValid() const", asMETHODPR(ValueAnimation, IsValid, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool Load(Deserializer&)", asMETHODPR(ValueAnimation, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadFile(const String&in)", asMETHODPR(ValueAnimation, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "bool Load(const String&in)", asMETHODPR(ValueAnimation, LoadFile, (const String&), bool), asCALL_THISCALL);
    // bool ValueAnimation::LoadJSON(const JSONValue& source) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ValueAnimation, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool ValueAnimation::LoadXML(const XMLElement& source) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadXML(const XMLElement&in)", asMETHODPR(ValueAnimation, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ValueAnimation, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimation", "int Refs() const", asMETHODPR(ValueAnimation, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "int get_refs() const", asMETHODPR(ValueAnimation, Refs, () const, int), asCALL_THISCALL);
    // static void ValueAnimation::RegisterObject(Context* context) | File: ../Scene/ValueAnimation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_RELEASE, "void f()", asMETHODPR(ValueAnimation, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void ResetUseTimer()", asMETHODPR(ValueAnimation, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool ValueAnimation::Save(Serializer& dest) const override | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool Save(Serializer&) const", asMETHODPR(ValueAnimation, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveFile(const String&in) const", asMETHODPR(ValueAnimation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "bool Save(const String&in) const", asMETHODPR(ValueAnimation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // bool ValueAnimation::SaveJSON(JSONValue& dest) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveJSON(JSONValue&) const", asMETHODPR(ValueAnimation, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool ValueAnimation::SaveXML(XMLElement& dest) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveXML(XMLElement&) const", asMETHODPR(ValueAnimation, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SendEvent(StringHash)", asMETHODPR(ValueAnimation, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ValueAnimation, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(ValueAnimation, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetBlockEvents(bool)", asMETHODPR(ValueAnimation, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void ValueAnimation::SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData=VariantMap()) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetEventFrame(float, const StringHash&in, const VariantMap&in = VariantMap())", asMETHODPR(ValueAnimation, SetEventFrame, (float, const StringHash&, const VariantMap&), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ValueAnimation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ValueAnimation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void ValueAnimation::SetInterpolationMethod(InterpMethod method) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetInterpolationMethod(InterpMethod)", asMETHODPR(ValueAnimation, SetInterpolationMethod, (InterpMethod), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_interpolationMethod(InterpMethod)", asMETHODPR(ValueAnimation, SetInterpolationMethod, (InterpMethod), void), asCALL_THISCALL);
    // bool ValueAnimation::SetKeyFrame(float time, const Variant& value) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SetKeyFrame(float, const Variant&in)", asMETHODPR(ValueAnimation, SetKeyFrame, (float, const Variant&), bool), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetMemoryUse(uint)", asMETHODPR(ValueAnimation, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetName(const String&in)", asMETHODPR(ValueAnimation, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_name(const String&in)", asMETHODPR(ValueAnimation, SetName, (const String&), void), asCALL_THISCALL);
    // void ValueAnimation::SetOwner(void* owner) | File: ../Scene/ValueAnimation.h
    // Error: type "void*" can not automatically bind
    // void ValueAnimation::SetSplineTension(float tension) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetSplineTension(float)", asMETHODPR(ValueAnimation, SetSplineTension, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_splineTension(float)", asMETHODPR(ValueAnimation, SetSplineTension, (float), void), asCALL_THISCALL);
    // void ValueAnimation::SetValueType(VariantType valueType) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetValueType(VariantType)", asMETHODPR(ValueAnimation, SetValueType, (VariantType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_valueType(VariantType)", asMETHODPR(ValueAnimation, SetValueType, (VariantType), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromAllEvents()", asMETHODPR(ValueAnimation, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ValueAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ValueAnimation, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ValueAnimation, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ValueAnimation, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // explicit ValueAnimation::ValueAnimation(Context* context) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_FACTORY, "ValueAnimation@+ f()", asFUNCTION(ValueAnimation_ValueAnimation_Context), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimation", "int WeakRefs() const", asMETHODPR(ValueAnimation, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "int get_weakRefs() const", asMETHODPR(ValueAnimation, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(ValueAnimation, "ValueAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ValueAnimation, "ValueAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ValueAnimation, "ValueAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_ValueAnimation
    REGISTER_MANUAL_PART_ValueAnimation(ValueAnimation, "ValueAnimation")
#endif
    RegisterSubclass<Resource, ValueAnimation>(engine, "Resource", "ValueAnimation");
    RegisterSubclass<Object, ValueAnimation>(engine, "Object", "ValueAnimation");
    RegisterSubclass<RefCounted, ValueAnimation>(engine, "RefCounted", "ValueAnimation");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_ADDREF, "void f()", asMETHODPR(ValueAnimationInfo, AddRef, (), void), asCALL_THISCALL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "ValueAnimation@+ GetAnimation() const", asMETHODPR(ValueAnimationInfo, GetAnimation, () const, ValueAnimation*), asCALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "float GetSpeed() const", asMETHODPR(ValueAnimationInfo, GetSpeed, () const, float), asCALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "Object@+ GetTarget() const", asMETHODPR(ValueAnimationInfo, GetTarget, () const, Object*), asCALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "float GetTime() const", asMETHODPR(ValueAnimationInfo, GetTime, () const, float), asCALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "WrapMode GetWrapMode() const", asMETHODPR(ValueAnimationInfo, GetWrapMode, () const, WrapMode), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "int Refs() const", asMETHODPR(ValueAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimationInfo", "int get_refs() const", asMETHODPR(ValueAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_RELEASE, "void f()", asMETHODPR(ValueAnimationInfo, ReleaseRef, (), void), asCALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "void SetSpeed(float)", asMETHODPR(ValueAnimationInfo, SetSpeed, (float), void), asCALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "bool SetTime(float)", asMETHODPR(ValueAnimationInfo, SetTime, (float), bool), asCALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "void SetWrapMode(WrapMode)", asMETHODPR(ValueAnimationInfo, SetWrapMode, (WrapMode), void), asCALL_THISCALL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "bool Update(float)", asMETHODPR(ValueAnimationInfo, Update, (float), bool), asCALL_THISCALL);
    // ValueAnimationInfo::ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(ValueAnimation@+, WrapMode, float)", asFUNCTION(ValueAnimationInfo_ValueAnimationInfo_ValueAnimation_WrapMode_float), asCALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(Object@+, ValueAnimation@+, WrapMode, float)", asFUNCTION(ValueAnimationInfo_ValueAnimationInfo_Object_ValueAnimation_WrapMode_float), asCALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(const ValueAnimationInfo& other) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(const ValueAnimationInfo&in)", asFUNCTION(ValueAnimationInfo_ValueAnimationInfo_ValueAnimationInfo), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "int WeakRefs() const", asMETHODPR(ValueAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimationInfo", "int get_weakRefs() const", asMETHODPR(ValueAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ValueAnimationInfo, "ValueAnimationInfo")
#endif
#ifdef REGISTER_MANUAL_PART_ValueAnimationInfo
    REGISTER_MANUAL_PART_ValueAnimationInfo(ValueAnimationInfo, "ValueAnimationInfo")
#endif
    RegisterSubclass<RefCounted, ValueAnimationInfo>(engine, "RefCounted", "ValueAnimationInfo");

    // const Variant Variant::EMPTY | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalProperty("const Variant EMPTY", (void*)&Variant::EMPTY);
    engine->SetDefaultNamespace("");
    // const PODVector<unsigned char> Variant::emptyBuffer | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>" can not automatically bind
    // const ResourceRef Variant::emptyResourceRef | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalProperty("const ResourceRef emptyResourceRef", (void*)&Variant::emptyResourceRef);
    engine->SetDefaultNamespace("");
    // const ResourceRefList Variant::emptyResourceRefList | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalProperty("const ResourceRefList emptyResourceRefList", (void*)&Variant::emptyResourceRefList);
    engine->SetDefaultNamespace("");
    // const StringVector Variant::emptyStringVector | File: ../Core/Variant.h
    // Error: type "const StringVector" can not automatically bind
    // const VariantMap Variant::emptyVariantMap | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalProperty("const VariantMap emptyVariantMap", (void*)&Variant::emptyVariantMap);
    engine->SetDefaultNamespace("");
    // const VariantVector Variant::emptyVariantVector | File: ../Core/Variant.h
    // Error: type "const VariantVector" can not automatically bind
    // void Variant::Clear() | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "void Clear()", asMETHODPR(Variant, Clear, (), void), asCALL_THISCALL);
    // void Variant::FromString(const String& type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "void FromString(const String&in, const String&in)", asMETHODPR(Variant, FromString, (const String&, const String&), void), asCALL_THISCALL);
    // void Variant::FromString(const char* type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // void Variant::FromString(VariantType type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "void FromString(VariantType, const String&in)", asMETHODPR(Variant, FromString, (VariantType, const String&), void), asCALL_THISCALL);
    // void Variant::FromString(VariantType type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // template<class T> T Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> int Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> unsigned Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> long long Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> unsigned long long Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> StringHash Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> bool Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> float Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> double Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Vector2& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Vector3& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Vector4& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Quaternion& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Color& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const String& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Rect& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const IntRect& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const IntVector2& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const IntVector3& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const PODVector<unsigned char>& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> void* Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> RefCounted* Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Matrix3& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Matrix3x4& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> const Matrix4& Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> ResourceRef Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> ResourceRefList Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> VariantVector Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> StringVector Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> VariantMap Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Vector2 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Vector3 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Vector4 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Quaternion Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Color Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> String Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Rect Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> IntRect Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> IntVector2 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> IntVector3 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> PODVector<unsigned char> Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Matrix3 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Matrix3x4 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // template<> Matrix4 Variant::Get() const | File: ../Core/Variant.h
    // Not registered because template
    // bool Variant::GetBool() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool GetBool() const", asMETHODPR(Variant, GetBool, () const, bool), asCALL_THISCALL);
    // const PODVector<unsigned char>& Variant::GetBuffer() const | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // PODVector<unsigned char>* Variant::GetBufferPtr() | File: ../Core/Variant.h
    // Error: type "PODVector<unsigned char>*" can not automatically bind
    // const Color& Variant::GetColor() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Color& GetColor() const", asMETHODPR(Variant, GetColor, () const, const Color&), asCALL_THISCALL);
    // template<class T> T Variant::GetCustom() const | File: ../Core/Variant.h
    // Not registered because template
    // template<class T> T* Variant::GetCustomPtr() | File: ../Core/Variant.h
    // Not registered because template
    // CustomVariantValue* Variant::GetCustomVariantValuePtr() | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // const CustomVariantValue* Variant::GetCustomVariantValuePtr() const | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // double Variant::GetDouble() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "double GetDouble() const", asMETHODPR(Variant, GetDouble, () const, double), asCALL_THISCALL);
    // float Variant::GetFloat() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "float GetFloat() const", asMETHODPR(Variant, GetFloat, () const, float), asCALL_THISCALL);
    // int Variant::GetInt() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "int GetInt() const", asMETHODPR(Variant, GetInt, () const, int), asCALL_THISCALL);
    // long long Variant::GetInt64() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "int64 GetInt64() const", asMETHODPR(Variant, GetInt64, () const, long long), asCALL_THISCALL);
    // const IntRect& Variant::GetIntRect() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntRect& GetIntRect() const", asMETHODPR(Variant, GetIntRect, () const, const IntRect&), asCALL_THISCALL);
    // const IntVector2& Variant::GetIntVector2() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntVector2& GetIntVector2() const", asMETHODPR(Variant, GetIntVector2, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector3& Variant::GetIntVector3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntVector3& GetIntVector3() const", asMETHODPR(Variant, GetIntVector3, () const, const IntVector3&), asCALL_THISCALL);
    // const Matrix3& Variant::GetMatrix3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix3& GetMatrix3() const", asMETHODPR(Variant, GetMatrix3, () const, const Matrix3&), asCALL_THISCALL);
    // const Matrix3x4& Variant::GetMatrix3x4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix3x4& GetMatrix3x4() const", asMETHODPR(Variant, GetMatrix3x4, () const, const Matrix3x4&), asCALL_THISCALL);
    // const Matrix4& Variant::GetMatrix4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix4& GetMatrix4() const", asMETHODPR(Variant, GetMatrix4, () const, const Matrix4&), asCALL_THISCALL);
    // RefCounted* Variant::GetPtr() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "RefCounted@+ GetPtr() const", asMETHODPR(Variant, GetPtr, () const, RefCounted*), asCALL_THISCALL);
    // const Quaternion& Variant::GetQuaternion() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Quaternion& GetQuaternion() const", asMETHODPR(Variant, GetQuaternion, () const, const Quaternion&), asCALL_THISCALL);
    // const Rect& Variant::GetRect() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Rect& GetRect() const", asMETHODPR(Variant, GetRect, () const, const Rect&), asCALL_THISCALL);
    // const ResourceRef& Variant::GetResourceRef() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const ResourceRef& GetResourceRef() const", asMETHODPR(Variant, GetResourceRef, () const, const ResourceRef&), asCALL_THISCALL);
    // const ResourceRefList& Variant::GetResourceRefList() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const ResourceRefList& GetResourceRefList() const", asMETHODPR(Variant, GetResourceRefList, () const, const ResourceRefList&), asCALL_THISCALL);
    // const String& Variant::GetString() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const String& GetString() const", asMETHODPR(Variant, GetString, () const, const String&), asCALL_THISCALL);
    // StringHash Variant::GetStringHash() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "StringHash GetStringHash() const", asMETHODPR(Variant, GetStringHash, () const, StringHash), asCALL_THISCALL);
    // const StringVector& Variant::GetStringVector() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Array<String>@ GetStringVector() const", asFUNCTION(Variant_GetStringVector_void), asCALL_CDECL_OBJFIRST);
    // StringVector* Variant::GetStringVectorPtr() | File: ../Core/Variant.h
    // Error: type "StringVector*" can not automatically bind
    // VariantType Variant::GetType() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VariantType GetType() const", asMETHODPR(Variant, GetType, () const, VariantType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VariantType get_type() const", asMETHODPR(Variant, GetType, () const, VariantType), asCALL_THISCALL);
    // static VariantType Variant::GetTypeFromName(const String& typeName) | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalFunction("VariantType GetTypeFromName(const String&in)", asFUNCTIONPR(Variant::GetTypeFromName, (const String&), VariantType), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static VariantType Variant::GetTypeFromName(const char* typeName) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // String Variant::GetTypeName() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "String GetTypeName() const", asMETHODPR(Variant, GetTypeName, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "String get_typeName() const", asMETHODPR(Variant, GetTypeName, () const, String), asCALL_THISCALL);
    // static String Variant::GetTypeName(VariantType type) | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalFunction("String GetTypeName(VariantType)", asFUNCTIONPR(Variant::GetTypeName, (VariantType), String), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // unsigned Variant::GetUInt() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "uint GetUInt() const", asMETHODPR(Variant, GetUInt, () const, unsigned), asCALL_THISCALL);
    // unsigned long long Variant::GetUInt64() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "uint64 GetUInt64() const", asMETHODPR(Variant, GetUInt64, () const, unsigned long long), asCALL_THISCALL);
    // const VariantMap& Variant::GetVariantMap() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const VariantMap& GetVariantMap() const", asMETHODPR(Variant, GetVariantMap, () const, const VariantMap&), asCALL_THISCALL);
    // VariantMap* Variant::GetVariantMapPtr() | File: ../Core/Variant.h
    // Error: type "VariantMap*" can not automatically bind
    // const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // VariantVector* Variant::GetVariantVectorPtr() | File: ../Core/Variant.h
    // Error: type "VariantVector*" can not automatically bind
    // const Vector2& Variant::GetVector2() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector2& GetVector2() const", asMETHODPR(Variant, GetVector2, () const, const Vector2&), asCALL_THISCALL);
    // const Vector3& Variant::GetVector3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector3& GetVector3() const", asMETHODPR(Variant, GetVector3, () const, const Vector3&), asCALL_THISCALL);
    // const Vector4& Variant::GetVector4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector4& GetVector4() const", asMETHODPR(Variant, GetVector4, () const, const Vector4&), asCALL_THISCALL);
    // VectorBuffer Variant::GetVectorBuffer() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetVectorBuffer() const", asMETHODPR(Variant, GetVectorBuffer, () const, VectorBuffer), asCALL_THISCALL);
    // void* Variant::GetVoidPtr() const | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // bool Variant::IsCustom() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsCustom() const", asMETHODPR(Variant, IsCustom, () const, bool), asCALL_THISCALL);
    // template<class T> bool Variant::IsCustomType() const | File: ../Core/Variant.h
    // Not registered because template
    // bool Variant::IsEmpty() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsEmpty() const", asMETHODPR(Variant, IsEmpty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_empty() const", asMETHODPR(Variant, IsEmpty, () const, bool), asCALL_THISCALL);
    // bool Variant::IsZero() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsZero() const", asMETHODPR(Variant, IsZero, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_zero() const", asMETHODPR(Variant, IsZero, () const, bool), asCALL_THISCALL);
    // Variant& Variant::operator=(const Variant& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Variant&in)", asMETHODPR(Variant, operator=, (const Variant&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(int rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(int)", asMETHODPR(Variant, operator=, (int), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(long long rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(int64)", asMETHODPR(Variant, operator=, (long long), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(unsigned long long rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(uint64)", asMETHODPR(Variant, operator=, (unsigned long long), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(unsigned rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(uint)", asMETHODPR(Variant, operator=, (unsigned), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const StringHash& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const StringHash&in)", asMETHODPR(Variant, operator=, (const StringHash&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(bool rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(bool)", asMETHODPR(Variant, operator=, (bool), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(float rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(float)", asMETHODPR(Variant, operator=, (float), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(double rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(double)", asMETHODPR(Variant, operator=, (double), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Vector2& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector2&in)", asMETHODPR(Variant, operator=, (const Vector2&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Vector3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector3&in)", asMETHODPR(Variant, operator=, (const Vector3&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Vector4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector4&in)", asMETHODPR(Variant, operator=, (const Vector4&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Quaternion& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Quaternion&in)", asMETHODPR(Variant, operator=, (const Quaternion&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Color& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Color&in)", asMETHODPR(Variant, operator=, (const Color&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const String& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const String&in)", asMETHODPR(Variant, operator=, (const String&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const char* rhs) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant& Variant::operator=(const PODVector<unsigned char>& rhs) | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant& Variant::operator=(const VectorBuffer& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VectorBuffer&in)", asMETHODPR(Variant, operator=, (const VectorBuffer&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(void* rhs) | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // Variant& Variant::operator=(const ResourceRef& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRef&in)", asMETHODPR(Variant, operator=, (const ResourceRef&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const ResourceRefList& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRefList&in)", asMETHODPR(Variant, operator=, (const ResourceRefList&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const VariantVector& rhs) | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant& Variant::operator=(const StringVector& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(Array<String>@+)", asFUNCTION(Variant_operatorequals_StringVector), asCALL_CDECL_OBJFIRST);
    // Variant& Variant::operator=(const VariantMap& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VariantMap&in)", asMETHODPR(Variant, operator=, (const VariantMap&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Rect& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Rect&in)", asMETHODPR(Variant, operator=, (const Rect&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const IntRect& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntRect&in)", asMETHODPR(Variant, operator=, (const IntRect&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const IntVector2& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntVector2&in)", asMETHODPR(Variant, operator=, (const IntVector2&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const IntVector3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntVector3&in)", asMETHODPR(Variant, operator=, (const IntVector3&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(RefCounted* rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(RefCounted@+)", asMETHODPR(Variant, operator=, (RefCounted*), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Matrix3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3&in)", asMETHODPR(Variant, operator=, (const Matrix3&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Matrix3x4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3x4&in)", asMETHODPR(Variant, operator=, (const Matrix3x4&), Variant&), asCALL_THISCALL);
    // Variant& Variant::operator=(const Matrix4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix4&in)", asMETHODPR(Variant, operator=, (const Matrix4&), Variant&), asCALL_THISCALL);
    // template<class T> Variant& Variant::operator=(const CustomVariantValueImpl<T>& value) | File: ../Core/Variant.h
    // Not registered because template
    // bool Variant::operator==(const Variant& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Variant&in) const", asMETHODPR(Variant, operator==, (const Variant&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(int rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(int) const", asMETHODPR(Variant, operator==, (int) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(unsigned rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint) const", asMETHODPR(Variant, operator==, (unsigned) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(long long rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(int64) const", asMETHODPR(Variant, operator==, (long long) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(unsigned long long rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint64) const", asMETHODPR(Variant, operator==, (unsigned long long) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(bool rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(bool) const", asMETHODPR(Variant, operator==, (bool) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(float rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(float) const", asMETHODPR(Variant, operator==, (float) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(double rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(double) const", asMETHODPR(Variant, operator==, (double) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Vector2& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector2&in) const", asMETHODPR(Variant, operator==, (const Vector2&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Vector3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector3&in) const", asMETHODPR(Variant, operator==, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Vector4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector4&in) const", asMETHODPR(Variant, operator==, (const Vector4&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Quaternion& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Quaternion&in) const", asMETHODPR(Variant, operator==, (const Quaternion&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Color& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Color&in) const", asMETHODPR(Variant, operator==, (const Color&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const String& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const String&in) const", asMETHODPR(Variant, operator==, (const String&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const PODVector<unsigned char>& rhs) const | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Variant::operator==(const VectorBuffer& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VectorBuffer&in) const", asMETHODPR(Variant, operator==, (const VectorBuffer&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(void* rhs) const | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // bool Variant::operator==(const ResourceRef& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRef&in) const", asMETHODPR(Variant, operator==, (const ResourceRef&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const ResourceRefList& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRefList&in) const", asMETHODPR(Variant, operator==, (const ResourceRefList&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const VariantVector& rhs) const | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Variant::operator==(const StringVector& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(Array<String>@+) const", asFUNCTION(Variant_operatorequalsequals_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Variant::operator==(const VariantMap& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VariantMap&in) const", asMETHODPR(Variant, operator==, (const VariantMap&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Rect& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Rect&in) const", asMETHODPR(Variant, operator==, (const Rect&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const IntRect& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntRect&in) const", asMETHODPR(Variant, operator==, (const IntRect&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const IntVector2& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntVector2&in) const", asMETHODPR(Variant, operator==, (const IntVector2&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const IntVector3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntVector3&in) const", asMETHODPR(Variant, operator==, (const IntVector3&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const StringHash& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const StringHash&in) const", asMETHODPR(Variant, operator==, (const StringHash&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(RefCounted* rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(RefCounted@+) const", asMETHODPR(Variant, operator==, (RefCounted*) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Matrix3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3&in) const", asMETHODPR(Variant, operator==, (const Matrix3&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Matrix3x4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3x4&in) const", asMETHODPR(Variant, operator==, (const Matrix3x4&) const, bool), asCALL_THISCALL);
    // bool Variant::operator==(const Matrix4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix4&in) const", asMETHODPR(Variant, operator==, (const Matrix4&) const, bool), asCALL_THISCALL);
    // void Variant::SetBuffer(const void* data, unsigned size) | File: ../Core/Variant.h
    // Error: type "const void*" can not automatically bind
    // template<class T> void Variant::SetCustom(const T& value) | File: ../Core/Variant.h
    // Not registered because template
    // void Variant::SetCustomVariantValue(const CustomVariantValue& value) | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // String Variant::ToString() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "String ToString() const", asMETHODPR(Variant, ToString, () const, String), asCALL_THISCALL);
    // Variant::Variant(int value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(Variant_Variant_int), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(long long value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int64)", asFUNCTION(Variant_Variant_longlong), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(Variant_Variant_unsigned), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned long long value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint64)", asFUNCTION(Variant_Variant_unsignedlonglong), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringHash& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(Variant_Variant_StringHash), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(bool value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(Variant_Variant_bool), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(float value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Variant_Variant_float), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(double value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(Variant_Variant_double), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector2& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Variant_Variant_Vector2), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Variant_Variant_Vector3), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Variant_Variant_Vector4), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Quaternion& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(Variant_Variant_Quaternion), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Color& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(Variant_Variant_Color), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(Variant_Variant_String), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const PODVector<unsigned char>& value) | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant::Variant(const VectorBuffer& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", asFUNCTION(Variant_Variant_VectorBuffer), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(void* value) | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // Variant::Variant(const ResourceRef& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", asFUNCTION(Variant_Variant_ResourceRef), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const ResourceRefList& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", asFUNCTION(Variant_Variant_ResourceRefList), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const VariantVector& value) | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant::Variant(const VariantMap& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(Variant_Variant_VariantMap), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringVector& value) | File: ../Core/Variant.h
    // Error: type "const StringVector&" can not automatically bind
    // Variant::Variant(const Rect& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(Variant_Variant_Rect), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntRect& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", asFUNCTION(Variant_Variant_IntRect), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector2& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(Variant_Variant_IntVector2), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(Variant_Variant_IntVector3), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(RefCounted* value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", asFUNCTION(Variant_Variant_RefCounted), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Variant_Variant_Matrix3), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3x4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(Variant_Variant_Matrix3x4), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Variant_Variant_Matrix4), asCALL_CDECL_OBJFIRST);
    // template<class T> Variant::Variant(const CustomVariantValueImpl<T>& value) | File: ../Core/Variant.h
    // Not registered because template
    // Variant::Variant(const String& type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", asFUNCTION(Variant_Variant_String_String), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(VariantType type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(VariantType, const String&in)", asFUNCTION(Variant_Variant_VariantType_String), asCALL_CDECL_OBJFIRST);
    // Variant::Variant(const char* type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(VariantType type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const Variant& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant&in)", asFUNCTION(Variant_Variant_Variant), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_Variant
    REGISTER_MANUAL_PART_Variant(Variant, "Variant")
#endif

    // const Vector2 Vector2::DOWN | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 DOWN", (void*)&Vector2::DOWN);
    engine->SetDefaultNamespace("");
    // const Vector2 Vector2::LEFT | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 LEFT", (void*)&Vector2::LEFT);
    engine->SetDefaultNamespace("");
    // const Vector2 Vector2::ONE | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 ONE", (void*)&Vector2::ONE);
    engine->SetDefaultNamespace("");
    // const Vector2 Vector2::RIGHT | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 RIGHT", (void*)&Vector2::RIGHT);
    engine->SetDefaultNamespace("");
    // const Vector2 Vector2::UP | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 UP", (void*)&Vector2::UP);
    engine->SetDefaultNamespace("");
    // float Vector2::x_ | File: ../Math/Vector2.h
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, x_));
    // float Vector2::y_ | File: ../Math/Vector2.h
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, y_));
    // const Vector2 Vector2::ZERO | File: ../Math/Vector2.h
    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 ZERO", (void*)&Vector2::ZERO);
    engine->SetDefaultNamespace("");
    // Vector2 Vector2::Abs() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 Abs() const", asMETHODPR(Vector2, Abs, () const, Vector2), asCALL_THISCALL);
    // float Vector2::AbsDotProduct(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", asMETHODPR(Vector2, AbsDotProduct, (const Vector2&) const, float), asCALL_THISCALL);
    // float Vector2::Angle(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float Angle(const Vector2&in) const", asMETHODPR(Vector2, Angle, (const Vector2&) const, float), asCALL_THISCALL);
    // const float* Vector2::Data() const | File: ../Math/Vector2.h
    // Error: type "const float*" can not automatically bind
    // float Vector2::DotProduct(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", asMETHODPR(Vector2, DotProduct, (const Vector2&) const, float), asCALL_THISCALL);
    // bool Vector2::Equals(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool Equals(const Vector2&in) const", asMETHODPR(Vector2, Equals, (const Vector2&) const, bool), asCALL_THISCALL);
    // bool Vector2::IsInf() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool IsInf() const", asMETHODPR(Vector2, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector2::IsNaN() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool IsNaN() const", asMETHODPR(Vector2, IsNaN, () const, bool), asCALL_THISCALL);
    // float Vector2::Length() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float Length() const", asMETHODPR(Vector2, Length, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_length() const", asMETHODPR(Vector2, Length, () const, float), asCALL_THISCALL);
    // float Vector2::LengthSquared() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float LengthSquared() const", asMETHODPR(Vector2, LengthSquared, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", asMETHODPR(Vector2, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector2 Vector2::Lerp(const Vector2& rhs, float t) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", asMETHODPR(Vector2, Lerp, (const Vector2&, float) const, Vector2), asCALL_THISCALL);
    // void Vector2::Normalize() | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "void Normalize()", asMETHODPR(Vector2, Normalize, (), void), asCALL_THISCALL);
    // Vector2 Vector2::Normalized() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", asMETHODPR(Vector2, Normalized, () const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::NormalizedOrDefault(const Vector2& defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 NormalizedOrDefault(const Vector2&in = Vector2::ZERO, float = M_LARGE_EPSILON) const", asMETHODPR(Vector2, NormalizedOrDefault, (const Vector2&, float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator*(float rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", asMETHODPR(Vector2, operator*, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator*(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Vector2, operator*, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator*=(float rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(float)", asMETHODPR(Vector2, operator*=, (float), Vector2&), asCALL_THISCALL);
    // Vector2& Vector2::operator*=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(const Vector2&in)", asMETHODPR(Vector2, operator*=, (const Vector2&), Vector2&), asCALL_THISCALL);
    // Vector2 Vector2::operator+(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2&in) const", asMETHODPR(Vector2, operator+, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator+=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opAddAssign(const Vector2&in)", asMETHODPR(Vector2, operator+=, (const Vector2&), Vector2&), asCALL_THISCALL);
    // Vector2 Vector2::operator-() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", asMETHODPR(Vector2, operator-, () const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator-(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2&in) const", asMETHODPR(Vector2, operator-, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator-=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opSubAssign(const Vector2&in)", asMETHODPR(Vector2, operator-=, (const Vector2&), Vector2&), asCALL_THISCALL);
    // Vector2 Vector2::operator/(float rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", asMETHODPR(Vector2, operator/, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator/(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2&in) const", asMETHODPR(Vector2, operator/, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator/=(float rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(float)", asMETHODPR(Vector2, operator/=, (float), Vector2&), asCALL_THISCALL);
    // Vector2& Vector2::operator/=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(const Vector2&in)", asMETHODPR(Vector2, operator/=, (const Vector2&), Vector2&), asCALL_THISCALL);
    // Vector2& Vector2::operator=(const Vector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2&in)", asMETHODPR(Vector2, operator=, (const Vector2&), Vector2&), asCALL_THISCALL);
    // bool Vector2::operator==(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2&in) const", asMETHODPR(Vector2, operator==, (const Vector2&) const, bool), asCALL_THISCALL);
    // float Vector2::ProjectOntoAxis(const Vector2& axis) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float ProjectOntoAxis(const Vector2&in) const", asMETHODPR(Vector2, ProjectOntoAxis, (const Vector2&) const, float), asCALL_THISCALL);
    // Vector2 Vector2::ReNormalized(float minLength, float maxLength, const Vector2& defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 ReNormalized(float, float, const Vector2&in = Vector2::ZERO, float = M_LARGE_EPSILON) const", asMETHODPR(Vector2, ReNormalized, (float, float, const Vector2&, float) const, Vector2), asCALL_THISCALL);
    // String Vector2::ToString() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "String ToString() const", asMETHODPR(Vector2, ToString, () const, String), asCALL_THISCALL);
    // Vector2::Vector2(const Vector2& vector) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector2_Vector2_Vector2), asCALL_CDECL_OBJFIRST);
    // explicit Vector2::Vector2(const IntVector2& vector) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(Vector2_Vector2_IntVector2), asCALL_CDECL_OBJFIRST);
    // Vector2::Vector2(float x, float y) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector2_Vector2_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Vector2::Vector2(const float* data) noexcept | File: ../Math/Vector2.h
    // Error: type "const float*" can not automatically bind
#ifdef REGISTER_MANUAL_PART_Vector2
    REGISTER_MANUAL_PART_Vector2(Vector2, "Vector2")
#endif

    // const Vector3 Vector3::BACK | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 BACK", (void*)&Vector3::BACK);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::DOWN | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 DOWN", (void*)&Vector3::DOWN);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::FORWARD | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 FORWARD", (void*)&Vector3::FORWARD);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::LEFT | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 LEFT", (void*)&Vector3::LEFT);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::ONE | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 ONE", (void*)&Vector3::ONE);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::RIGHT | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 RIGHT", (void*)&Vector3::RIGHT);
    engine->SetDefaultNamespace("");
    // const Vector3 Vector3::UP | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 UP", (void*)&Vector3::UP);
    engine->SetDefaultNamespace("");
    // float Vector3::x_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("Vector3", "float x", offsetof(Vector3, x_));
    // float Vector3::y_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("Vector3", "float y", offsetof(Vector3, y_));
    // float Vector3::z_ | File: ../Math/Vector3.h
    engine->RegisterObjectProperty("Vector3", "float z", offsetof(Vector3, z_));
    // const Vector3 Vector3::ZERO | File: ../Math/Vector3.h
    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 ZERO", (void*)&Vector3::ZERO);
    engine->SetDefaultNamespace("");
    // Vector3 Vector3::Abs() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Abs() const", asMETHODPR(Vector3, Abs, () const, Vector3), asCALL_THISCALL);
    // float Vector3::AbsDotProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", asMETHODPR(Vector3, AbsDotProduct, (const Vector3&) const, float), asCALL_THISCALL);
    // float Vector3::Angle(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float Angle(const Vector3&in) const", asMETHODPR(Vector3, Angle, (const Vector3&) const, float), asCALL_THISCALL);
    // Vector3 Vector3::CrossProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", asMETHODPR(Vector3, CrossProduct, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // const float* Vector3::Data() const | File: ../Math/Vector3.h
    // Error: type "const float*" can not automatically bind
    // float Vector3::DistanceToPlane(const Vector3& origin, const Vector3& normal) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DistanceToPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, DistanceToPlane, (const Vector3&, const Vector3&) const, float), asCALL_THISCALL);
    // float Vector3::DistanceToPoint(const Vector3& point) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DistanceToPoint(const Vector3&in) const", asMETHODPR(Vector3, DistanceToPoint, (const Vector3&) const, float), asCALL_THISCALL);
    // float Vector3::DotProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", asMETHODPR(Vector3, DotProduct, (const Vector3&) const, float), asCALL_THISCALL);
    // bool Vector3::Equals(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool Equals(const Vector3&in) const", asMETHODPR(Vector3, Equals, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Vector3::IsInf() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool IsInf() const", asMETHODPR(Vector3, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector3::IsNaN() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool IsNaN() const", asMETHODPR(Vector3, IsNaN, () const, bool), asCALL_THISCALL);
    // float Vector3::Length() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float Length() const", asMETHODPR(Vector3, Length, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_length() const", asMETHODPR(Vector3, Length, () const, float), asCALL_THISCALL);
    // float Vector3::LengthSquared() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float LengthSquared() const", asMETHODPR(Vector3, LengthSquared, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_lengthSquared() const", asMETHODPR(Vector3, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector3 Vector3::Lerp(const Vector3& rhs, float t) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", asMETHODPR(Vector3, Lerp, (const Vector3&, float) const, Vector3), asCALL_THISCALL);
    // void Vector3::Normalize() | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "void Normalize()", asMETHODPR(Vector3, Normalize, (), void), asCALL_THISCALL);
    // Vector3 Vector3::Normalized() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Normalized() const", asMETHODPR(Vector3, Normalized, () const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::NormalizedOrDefault(const Vector3& defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 NormalizedOrDefault(const Vector3&in = Vector3::ZERO, float = M_LARGE_EPSILON) const", asMETHODPR(Vector3, NormalizedOrDefault, (const Vector3&, float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator*(float rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", asMETHODPR(Vector3, operator*, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator*(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Vector3, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator*=(float rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(float)", asMETHODPR(Vector3, operator*=, (float), Vector3&), asCALL_THISCALL);
    // Vector3& Vector3::operator*=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3&in)", asMETHODPR(Vector3, operator*=, (const Vector3&), Vector3&), asCALL_THISCALL);
    // Vector3 Vector3::operator+(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3&in) const", asMETHODPR(Vector3, operator+, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator+=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3&in)", asMETHODPR(Vector3, operator+=, (const Vector3&), Vector3&), asCALL_THISCALL);
    // Vector3 Vector3::operator-() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", asMETHODPR(Vector3, operator-, () const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator-(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3&in) const", asMETHODPR(Vector3, operator-, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator-=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3&in)", asMETHODPR(Vector3, operator-=, (const Vector3&), Vector3&), asCALL_THISCALL);
    // Vector3 Vector3::operator/(float rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", asMETHODPR(Vector3, operator/, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator/(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3&in) const", asMETHODPR(Vector3, operator/, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator/=(float rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(float)", asMETHODPR(Vector3, operator/=, (float), Vector3&), asCALL_THISCALL);
    // Vector3& Vector3::operator/=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3&in)", asMETHODPR(Vector3, operator/=, (const Vector3&), Vector3&), asCALL_THISCALL);
    // Vector3& Vector3::operator=(const Vector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3&in)", asMETHODPR(Vector3, operator=, (const Vector3&), Vector3&), asCALL_THISCALL);
    // bool Vector3::operator==(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3&in) const", asMETHODPR(Vector3, operator==, (const Vector3&) const, bool), asCALL_THISCALL);
    // Vector3 Vector3::Orthogonalize(const Vector3& axis) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Orthogonalize(const Vector3&in) const", asMETHODPR(Vector3, Orthogonalize, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // float Vector3::ProjectOntoAxis(const Vector3& axis) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoAxis, (const Vector3&) const, float), asCALL_THISCALL);
    // Vector3 Vector3::ProjectOntoLine(const Vector3& from, const Vector3& to, bool clamped=false) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoLine(const Vector3&in, const Vector3&in, bool = false) const", asMETHODPR(Vector3, ProjectOntoLine, (const Vector3&, const Vector3&, bool) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::ProjectOntoPlane(const Vector3& origin, const Vector3& normal) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoPlane, (const Vector3&, const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::ReNormalized(float minLength, float maxLength, const Vector3& defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ReNormalized(float, float, const Vector3&in = Vector3::ZERO, float = M_LARGE_EPSILON) const", asMETHODPR(Vector3, ReNormalized, (float, float, const Vector3&, float) const, Vector3), asCALL_THISCALL);
    // unsigned Vector3::ToHash() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "uint ToHash() const", asMETHODPR(Vector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String Vector3::ToString() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "String ToString() const", asMETHODPR(Vector3, ToString, () const, String), asCALL_THISCALL);
    // Vector3::Vector3(const Vector3& vector) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Vector3_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector2& vector, float z) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", asFUNCTION(Vector3_Vector3_Vector2_float), asCALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const Vector2& vector) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector3_Vector3_Vector2), asCALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const IntVector3& vector) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(Vector3_Vector3_IntVector3), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y, float z) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Vector3_Vector3_float_float_float), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector3_Vector3_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const float* data) noexcept | File: ../Math/Vector3.h
    // Error: type "const float*" can not automatically bind
#ifdef REGISTER_MANUAL_PART_Vector3
    REGISTER_MANUAL_PART_Vector3(Vector3, "Vector3")
#endif

    // const Vector4 Vector4::ONE | File: ../Math/Vector4.h
    engine->SetDefaultNamespace("Vector4");
    engine->RegisterGlobalProperty("const Vector4 ONE", (void*)&Vector4::ONE);
    engine->SetDefaultNamespace("");
    // float Vector4::w_ | File: ../Math/Vector4.h
    engine->RegisterObjectProperty("Vector4", "float w", offsetof(Vector4, w_));
    // float Vector4::x_ | File: ../Math/Vector4.h
    engine->RegisterObjectProperty("Vector4", "float x", offsetof(Vector4, x_));
    // float Vector4::y_ | File: ../Math/Vector4.h
    engine->RegisterObjectProperty("Vector4", "float y", offsetof(Vector4, y_));
    // float Vector4::z_ | File: ../Math/Vector4.h
    engine->RegisterObjectProperty("Vector4", "float z", offsetof(Vector4, z_));
    // const Vector4 Vector4::ZERO | File: ../Math/Vector4.h
    engine->SetDefaultNamespace("Vector4");
    engine->RegisterGlobalProperty("const Vector4 ZERO", (void*)&Vector4::ZERO);
    engine->SetDefaultNamespace("");
    // Vector4 Vector4::Abs() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 Abs() const", asMETHODPR(Vector4, Abs, () const, Vector4), asCALL_THISCALL);
    // float Vector4::AbsDotProduct(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float AbsDotProduct(const Vector4&in) const", asMETHODPR(Vector4, AbsDotProduct, (const Vector4&) const, float), asCALL_THISCALL);
    // const float* Vector4::Data() const | File: ../Math/Vector4.h
    // Error: type "const float*" can not automatically bind
    // float Vector4::DotProduct(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float DotProduct(const Vector4&in) const", asMETHODPR(Vector4, DotProduct, (const Vector4&) const, float), asCALL_THISCALL);
    // bool Vector4::Equals(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool Equals(const Vector4&in) const", asMETHODPR(Vector4, Equals, (const Vector4&) const, bool), asCALL_THISCALL);
    // bool Vector4::IsInf() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool IsInf() const", asMETHODPR(Vector4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector4::IsNaN() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool IsNaN() const", asMETHODPR(Vector4, IsNaN, () const, bool), asCALL_THISCALL);
    // Vector4 Vector4::Lerp(const Vector4& rhs, float t) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", asMETHODPR(Vector4, Lerp, (const Vector4&, float) const, Vector4), asCALL_THISCALL);
    // explicit Vector4::operator Vector2() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector2 opConv() const", asMETHODPR(Vector4, operator Vector2, () const, Vector2), asCALL_THISCALL);
    // explicit Vector4::operator Vector3() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector3 opConv() const", asMETHODPR(Vector4, operator Vector3, () const, Vector3), asCALL_THISCALL);
    // Vector4 Vector4::operator*(float rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", asMETHODPR(Vector4, operator*, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator*(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Vector4, operator*, (const Vector4&) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator*=(float rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(float)", asMETHODPR(Vector4, operator*=, (float), Vector4&), asCALL_THISCALL);
    // Vector4& Vector4::operator*=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(const Vector4&in)", asMETHODPR(Vector4, operator*=, (const Vector4&), Vector4&), asCALL_THISCALL);
    // Vector4 Vector4::operator+(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4&in) const", asMETHODPR(Vector4, operator+, (const Vector4&) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator+=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opAddAssign(const Vector4&in)", asMETHODPR(Vector4, operator+=, (const Vector4&), Vector4&), asCALL_THISCALL);
    // Vector4 Vector4::operator-() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", asMETHODPR(Vector4, operator-, () const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator-(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4&in) const", asMETHODPR(Vector4, operator-, (const Vector4&) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator-=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opSubAssign(const Vector4&in)", asMETHODPR(Vector4, operator-=, (const Vector4&), Vector4&), asCALL_THISCALL);
    // Vector4 Vector4::operator/(float rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", asMETHODPR(Vector4, operator/, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator/(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4&in) const", asMETHODPR(Vector4, operator/, (const Vector4&) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator/=(float rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(float)", asMETHODPR(Vector4, operator/=, (float), Vector4&), asCALL_THISCALL);
    // Vector4& Vector4::operator/=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(const Vector4&in)", asMETHODPR(Vector4, operator/=, (const Vector4&), Vector4&), asCALL_THISCALL);
    // Vector4& Vector4::operator=(const Vector4& rhs) noexcept=default | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opAssign(const Vector4&in)", asMETHODPR(Vector4, operator=, (const Vector4&), Vector4&), asCALL_THISCALL);
    // bool Vector4::operator==(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool opEquals(const Vector4&in) const", asMETHODPR(Vector4, operator==, (const Vector4&) const, bool), asCALL_THISCALL);
    // float Vector4::operator[](unsigned index) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float opIndex(uint) const", asMETHODPR(Vector4, operator[], (unsigned) const, float), asCALL_THISCALL);
    // float& Vector4::operator[](unsigned index) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float& opIndex(uint)", asMETHODPR(Vector4, operator[], (unsigned), float&), asCALL_THISCALL);
    // float Vector4::ProjectOntoAxis(const Vector3& axis) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector4, ProjectOntoAxis, (const Vector3&) const, float), asCALL_THISCALL);
    // unsigned Vector4::ToHash() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "uint ToHash() const", asMETHODPR(Vector4, ToHash, () const, unsigned), asCALL_THISCALL);
    // String Vector4::ToString() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "String ToString() const", asMETHODPR(Vector4, ToString, () const, String), asCALL_THISCALL);
    // Vector4::Vector4(const Vector4& vector) noexcept=default | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Vector4_Vector4_Vector4), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4(const Vector3& vector, float w) noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(Vector4_Vector4_Vector3_float), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4(float x, float y, float z, float w) noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Vector4_Vector4_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h
    // Error: type "const float*" can not automatically bind
#ifdef REGISTER_MANUAL_PART_Vector4
    REGISTER_MANUAL_PART_Vector4(Vector4, "Vector4")
#endif

    // void VectorBase::Swap(VectorBase& rhs) | File: ../Container/VectorBase.h
    engine->RegisterObjectMethod("VectorBase", "void Swap(VectorBase&)", asMETHODPR(VectorBase, Swap, (VectorBase&), void), asCALL_THISCALL);
    // VectorBase& VectorBase::operator=(const VectorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VectorBase>(engine, "VectorBase");
#ifdef REGISTER_MANUAL_PART_VectorBase
    REGISTER_MANUAL_PART_VectorBase(VectorBase, "VectorBase")
#endif

    // void VectorBuffer::Clear() | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void Clear()", asMETHODPR(VectorBuffer, Clear, (), void), asCALL_THISCALL);
    // const PODVector<unsigned char>& VectorBuffer::GetBuffer() const | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetChecksum()", asMETHODPR(VectorBuffer, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_checksum()", asMETHODPR(VectorBuffer, GetChecksum, (), unsigned), asCALL_THISCALL);
    // const unsigned char* VectorBuffer::GetData() const | File: ../IO/VectorBuffer.h
    // Error: type "const unsigned char*" can not automatically bind
    // unsigned char* VectorBuffer::GetModifiableData() | File: ../IO/VectorBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("VectorBuffer", "const String& GetName() const", asMETHODPR(VectorBuffer, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "const String& get_name() const", asMETHODPR(VectorBuffer, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetPosition() const", asMETHODPR(VectorBuffer, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_position() const", asMETHODPR(VectorBuffer, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetSize() const", asMETHODPR(VectorBuffer, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_size() const", asMETHODPR(VectorBuffer, GetSize, () const, unsigned), asCALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool IsEof() const", asMETHODPR(VectorBuffer, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "bool get_eof() const", asMETHODPR(VectorBuffer, IsEof, () const, bool), asCALL_THISCALL);
    // unsigned VectorBuffer::Read(void* dest, unsigned size) override | File: ../IO/VectorBuffer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool ReadBool()", asMETHODPR(VectorBuffer, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "BoundingBox ReadBoundingBox()", asMETHODPR(VectorBuffer, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int8 ReadByte()", asMETHODPR(VectorBuffer, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Color ReadColor()", asMETHODPR(VectorBuffer, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "double ReadDouble()", asMETHODPR(VectorBuffer, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadFileID()", asMETHODPR(VectorBuffer, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "float ReadFloat()", asMETHODPR(VectorBuffer, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int ReadInt()", asMETHODPR(VectorBuffer, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int64 ReadInt64()", asMETHODPR(VectorBuffer, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntRect ReadIntRect()", asMETHODPR(VectorBuffer, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntVector2 ReadIntVector2()", asMETHODPR(VectorBuffer, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntVector3 ReadIntVector3()", asMETHODPR(VectorBuffer, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadLine()", asMETHODPR(VectorBuffer, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix3 ReadMatrix3()", asMETHODPR(VectorBuffer, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(VectorBuffer, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix4 ReadMatrix4()", asMETHODPR(VectorBuffer, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadNetID()", asMETHODPR(VectorBuffer, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Quaternion ReadPackedQuaternion()", asMETHODPR(VectorBuffer, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector3 ReadPackedVector3(float)", asMETHODPR(VectorBuffer, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Quaternion ReadQuaternion()", asMETHODPR(VectorBuffer, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Rect ReadRect()", asMETHODPR(VectorBuffer, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "ResourceRef ReadResourceRef()", asMETHODPR(VectorBuffer, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "ResourceRefList ReadResourceRefList()", asMETHODPR(VectorBuffer, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int16 ReadShort()", asMETHODPR(VectorBuffer, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadString()", asMETHODPR(VectorBuffer, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "StringHash ReadStringHash()", asMETHODPR(VectorBuffer, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Array<String>@ ReadStringVector()", asFUNCTION(VectorBuffer_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint8 ReadUByte()", asMETHODPR(VectorBuffer, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadUInt()", asMETHODPR(VectorBuffer, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint64 ReadUInt64()", asMETHODPR(VectorBuffer, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint16 ReadUShort()", asMETHODPR(VectorBuffer, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Variant ReadVariant()", asMETHODPR(VectorBuffer, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Variant ReadVariant(VariantType)", asMETHODPR(VectorBuffer, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "VariantMap ReadVariantMap()", asMETHODPR(VectorBuffer, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector2 ReadVector2()", asMETHODPR(VectorBuffer, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector3 ReadVector3()", asMETHODPR(VectorBuffer, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector4 ReadVector4()", asMETHODPR(VectorBuffer, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadVLE()", asMETHODPR(VectorBuffer, ReadVLE, (), unsigned), asCALL_THISCALL);
    // void VectorBuffer::Resize(unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void Resize(uint)", asMETHODPR(VectorBuffer, Resize, (unsigned), void), asCALL_THISCALL);
    // unsigned VectorBuffer::Seek(unsigned position) override | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint Seek(uint)", asMETHODPR(VectorBuffer, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint SeekRelative(int)", asMETHODPR(VectorBuffer, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // void VectorBuffer::SetData(const PODVector<unsigned char>& data) | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void VectorBuffer::SetData(const void* data, unsigned size) | File: ../IO/VectorBuffer.h
    // Error: type "const void*" can not automatically bind
    // void VectorBuffer::SetData(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void SetData(Deserializer&, uint)", asMETHODPR(VectorBuffer, SetData, (Deserializer&, unsigned), void), asCALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("VectorBuffer", "void SetName(const String&in)", asMETHODPR(VectorBuffer, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void set_name(const String&in)", asMETHODPR(VectorBuffer, SetName, (const String&), void), asCALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint Tell() const", asMETHODPR(VectorBuffer, Tell, () const, unsigned), asCALL_THISCALL);
    // explicit VectorBuffer::VectorBuffer(const PODVector<unsigned char>& data) | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // VectorBuffer::VectorBuffer(const void* data, unsigned size) | File: ../IO/VectorBuffer.h
    // Error: type "void*" can not automatically bind
    // VectorBuffer::VectorBuffer(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer&, uint)", asFUNCTION(VectorBuffer_VectorBuffer_Deserializer_unsigned), asCALL_CDECL_OBJFIRST);
    // unsigned VectorBuffer::Write(const void* data, unsigned size) override | File: ../IO/VectorBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteBool(bool)", asMETHODPR(VectorBuffer, WriteBool, (bool), bool), asCALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(VectorBuffer, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteByte(int8)", asMETHODPR(VectorBuffer, WriteByte, (signed char), bool), asCALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteColor(const Color&in)", asMETHODPR(VectorBuffer, WriteColor, (const Color&), bool), asCALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteDouble(double)", asMETHODPR(VectorBuffer, WriteDouble, (double), bool), asCALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteFileID(const String&in)", asMETHODPR(VectorBuffer, WriteFileID, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteFloat(float)", asMETHODPR(VectorBuffer, WriteFloat, (float), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteInt(int)", asMETHODPR(VectorBuffer, WriteInt, (int), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteInt64(int64)", asMETHODPR(VectorBuffer, WriteInt64, (long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntRect(const IntRect&in)", asMETHODPR(VectorBuffer, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(VectorBuffer, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntVector3(const IntVector3&in)", asMETHODPR(VectorBuffer, WriteIntVector3, (const IntVector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteLine(const String&in)", asMETHODPR(VectorBuffer, WriteLine, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(VectorBuffer, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(VectorBuffer, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(VectorBuffer, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteNetID(uint)", asMETHODPR(VectorBuffer, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(VectorBuffer, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(VectorBuffer, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(VectorBuffer, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteRect(const Rect&in)", asMETHODPR(VectorBuffer, WriteRect, (const Rect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteResourceRef(const ResourceRef&in)", asMETHODPR(VectorBuffer, WriteResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteResourceRefList(const ResourceRefList&in)", asMETHODPR(VectorBuffer, WriteResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteShort(int16)", asMETHODPR(VectorBuffer, WriteShort, (short), bool), asCALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteString(const String&in)", asMETHODPR(VectorBuffer, WriteString, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteStringHash(const StringHash&in)", asMETHODPR(VectorBuffer, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteStringVector(Array<String>@+)", asFUNCTION(VectorBuffer_WriteStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUByte(uint8)", asMETHODPR(VectorBuffer, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUInt(uint)", asMETHODPR(VectorBuffer, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUInt64(uint64)", asMETHODPR(VectorBuffer, WriteUInt64, (unsigned long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUShort(uint16)", asMETHODPR(VectorBuffer, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariant(const Variant&in)", asMETHODPR(VectorBuffer, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariantData(const Variant&in)", asMETHODPR(VectorBuffer, WriteVariantData, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(VectorBuffer, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector2(const Vector2&in)", asMETHODPR(VectorBuffer, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector3(const Vector3&in)", asMETHODPR(VectorBuffer, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector4(const Vector4&in)", asMETHODPR(VectorBuffer, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVLE(uint)", asMETHODPR(VectorBuffer, WriteVLE, (unsigned), bool), asCALL_THISCALL);
    // VectorBuffer& VectorBuffer::operator=(const VectorBuffer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VectorBuffer>(engine, "VectorBuffer");
#ifdef REGISTER_MANUAL_PART_AbstractFile
    REGISTER_MANUAL_PART_AbstractFile(VectorBuffer, "VectorBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(VectorBuffer, "VectorBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(VectorBuffer, "VectorBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_VectorBuffer
    REGISTER_MANUAL_PART_VectorBuffer(VectorBuffer, "VectorBuffer")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_ADDREF, "void f()", asMETHODPR(VertexBuffer, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "void ClearDataLost()", asMETHODPR(VertexBuffer, ClearDataLost, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool GetBlockEvents() const", asMETHODPR(VertexBuffer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // unsigned long long VertexBuffer::GetBufferHash(unsigned streamIndex) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint64 GetBufferHash(uint)", asMETHODPR(VertexBuffer, GetBufferHash, (unsigned), unsigned long long), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const String& GetCategory() const", asMETHODPR(VertexBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const String& get_category() const", asMETHODPR(VertexBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const VertexElement* VertexBuffer::GetElement(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // static const VertexElement* VertexBuffer::GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // VertexMaskFlags VertexBuffer::GetElementMask() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "VertexMaskFlags GetElementMask() const", asMETHODPR(VertexBuffer, GetElementMask, () const, VertexMaskFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "VertexMaskFlags get_elementMask() const", asMETHODPR(VertexBuffer, GetElementMask, () const, VertexMaskFlags), asCALL_THISCALL);
    // unsigned VertexBuffer::GetElementOffset(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetElementOffset(VertexElementSemantic, uint8 = 0) const", asMETHODPR(VertexBuffer, GetElementOffset, (VertexElementSemantic, unsigned char) const, unsigned), asCALL_THISCALL);
    // unsigned VertexBuffer::GetElementOffset(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetElementOffset(VertexElementType, VertexElementSemantic, uint8 = 0) const", asMETHODPR(VertexBuffer, GetElementOffset, (VertexElementType, VertexElementSemantic, unsigned char) const, unsigned), asCALL_THISCALL);
    // static unsigned VertexBuffer::GetElementOffset(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetElementOffset(Array<VertexElement>@+, VertexElementType, VertexElementSemantic, uint8 = 0)", asFUNCTION(VertexBuffer_GetElementOffset_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const PODVector<VertexElement>& VertexBuffer::GetElements() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "Array<VertexElement>@ GetElements() const", asFUNCTION(VertexBuffer_GetElements_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("VertexBuffer", "Array<VertexElement>@ get_elements() const", asFUNCTION(VertexBuffer_GetElements_void), asCALL_CDECL_OBJFIRST);
    // static PODVector<VertexElement> VertexBuffer::GetElements(unsigned elementMask) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("Array<VertexElement>@ GetElements(uint)", asFUNCTION(VertexBuffer_GetElements_unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "VariantMap& GetEventDataMap() const", asMETHODPR(VertexBuffer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "Object@+ GetEventSender() const", asMETHODPR(VertexBuffer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(VertexBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(VertexBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const VariantMap& GetGlobalVars() const", asMETHODPR(VertexBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const VariantMap& get_globalVars() const", asMETHODPR(VertexBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetGPUObjectName() const", asMETHODPR(VertexBuffer, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "Graphics@+ GetGraphics() const", asMETHODPR(VertexBuffer, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // unsigned char* VertexBuffer::GetShadowData() const | File: ../Graphics/VertexBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> VertexBuffer::GetShadowDataShared() const | File: ../Graphics/VertexBuffer.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(VertexBuffer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "StringHash GetType() const", asMETHODPR(VertexBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "StringHash get_type() const", asMETHODPR(VertexBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const String& GetTypeName() const", asMETHODPR(VertexBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const String& get_typeName() const", asMETHODPR(VertexBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned VertexBuffer::GetVertexCount() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetVertexCount() const", asMETHODPR(VertexBuffer, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "uint get_vertexCount() const", asMETHODPR(VertexBuffer, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    // unsigned VertexBuffer::GetVertexSize() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetVertexSize() const", asMETHODPR(VertexBuffer, GetVertexSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "uint get_vertexSize() const", asMETHODPR(VertexBuffer, GetVertexSize, () const, unsigned), asCALL_THISCALL);
    // static unsigned VertexBuffer::GetVertexSize(const PODVector<VertexElement>& elements) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetVertexSize(Array<VertexElement>@+)", asFUNCTION(VertexBuffer_GetVertexSize_PODVectorVertexElement), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned VertexBuffer::GetVertexSize(unsigned elementMask) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetVertexSize(uint)", asFUNCTIONPR(VertexBuffer::GetVertexSize, (unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool VertexBuffer::HasElement(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasElement(VertexElementSemantic, uint8 = 0) const", asMETHODPR(VertexBuffer, HasElement, (VertexElementSemantic, unsigned char) const, bool), asCALL_THISCALL);
    // bool VertexBuffer::HasElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasElement(VertexElementType, VertexElementSemantic, uint8 = 0) const", asMETHODPR(VertexBuffer, HasElement, (VertexElementType, VertexElementSemantic, unsigned char) const, bool), asCALL_THISCALL);
    // static bool VertexBuffer::HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("bool HasElement(Array<VertexElement>@+, VertexElementType, VertexElementSemantic, uint8 = 0)", asFUNCTION(VertexBuffer_HasElement_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasEventHandlers() const", asMETHODPR(VertexBuffer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasPendingData() const", asMETHODPR(VertexBuffer, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(VertexBuffer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(VertexBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsDataLost() const", asMETHODPR(VertexBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_dataLost() const", asMETHODPR(VertexBuffer, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool VertexBuffer::IsDynamic() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsDynamic() const", asMETHODPR(VertexBuffer, IsDynamic, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_dynamic() const", asMETHODPR(VertexBuffer, IsDynamic, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsInstanceOf(StringHash) const", asMETHODPR(VertexBuffer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool VertexBuffer::IsLocked() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsLocked() const", asMETHODPR(VertexBuffer, IsLocked, () const, bool), asCALL_THISCALL);
    // bool VertexBuffer::IsShadowed() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsShadowed() const", asMETHODPR(VertexBuffer, IsShadowed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_shadowed() const", asMETHODPR(VertexBuffer, IsShadowed, () const, bool), asCALL_THISCALL);
    // void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
    // Error: type "void*" can not automatically bind
    // void VertexBuffer::OnDeviceLost() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnDeviceLost()", asMETHODPR(VertexBuffer, OnDeviceLost, (), void), asCALL_THISCALL);
    // void VertexBuffer::OnDeviceReset() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnDeviceReset()", asMETHODPR(VertexBuffer, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(VertexBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("VertexBuffer", "int Refs() const", asMETHODPR(VertexBuffer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "int get_refs() const", asMETHODPR(VertexBuffer, Refs, () const, int), asCALL_THISCALL);
    // void VertexBuffer::Release() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void Release()", asMETHODPR(VertexBuffer, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_RELEASE, "void f()", asMETHODPR(VertexBuffer, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SendEvent(StringHash)", asMETHODPR(VertexBuffer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(VertexBuffer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetBlockEvents(bool)", asMETHODPR(VertexBuffer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // bool VertexBuffer::SetData(const void* data) | File: ../Graphics/VertexBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
    // Error: type "const void*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(VertexBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(VertexBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void VertexBuffer::SetShadowed(bool enable) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetShadowed(bool)", asMETHODPR(VertexBuffer, SetShadowed, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "void set_shadowed(bool)", asMETHODPR(VertexBuffer, SetShadowed, (bool), void), asCALL_THISCALL);
    // bool VertexBuffer::SetSize(unsigned vertexCount, const PODVector<VertexElement>& elements, bool dynamic=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool SetSize(uint, Array<VertexElement>@+, bool = false)", asFUNCTION(VertexBuffer_SetSize_unsigned_PODVectorVertexElement_bool), asCALL_CDECL_OBJFIRST);
    // bool VertexBuffer::SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool SetSize(uint, uint, bool = false)", asMETHODPR(VertexBuffer, SetSize, (unsigned, unsigned, bool), bool), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void VertexBuffer::Unlock() | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void Unlock()", asMETHODPR(VertexBuffer, Unlock, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromAllEvents()", asMETHODPR(VertexBuffer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(VertexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(VertexBuffer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(VertexBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(VertexBuffer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // static void VertexBuffer::UpdateOffsets(PODVector<VertexElement>& elements) | File: ../Graphics/VertexBuffer.h
    // Error: type "PODVector<VertexElement>&" can not automatically bind
    // explicit VertexBuffer::VertexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_FACTORY, "VertexBuffer@+ f(bool = false)", asFUNCTION(VertexBuffer_VertexBuffer_Context_bool), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("VertexBuffer", "int WeakRefs() const", asMETHODPR(VertexBuffer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "int get_weakRefs() const", asMETHODPR(VertexBuffer, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(VertexBuffer, "VertexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(VertexBuffer, "VertexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(VertexBuffer, "VertexBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_VertexBuffer
    REGISTER_MANUAL_PART_VertexBuffer(VertexBuffer, "VertexBuffer")
#endif
    RegisterSubclass<Object, VertexBuffer>(engine, "Object", "VertexBuffer");
    RegisterSubclass<RefCounted, VertexBuffer>(engine, "RefCounted", "VertexBuffer");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View", asBEHAVE_ADDREF, "void f()", asMETHODPR(View, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool View::Define(RenderSurface* renderTarget, Viewport* viewport) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "bool Define(RenderSurface@+, Viewport@+)", asMETHODPR(View, Define, (RenderSurface*, Viewport*), bool), asCALL_THISCALL);
    // void View::DrawFullscreenQuad(bool setIdentityProjection=false) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void DrawFullscreenQuad(bool = false)", asMETHODPR(View, DrawFullscreenQuad, (bool), void), asCALL_THISCALL);
    // Texture* View::FindNamedTexture(const String& name, bool isRenderTarget, bool isVolumeMap=false) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Texture@+ FindNamedTexture(const String&in, bool, bool = false)", asMETHODPR(View, FindNamedTexture, (const String&, bool, bool), Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool GetBlockEvents() const", asMETHODPR(View, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // Camera* View::GetCamera() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Camera@+ GetCamera() const", asMETHODPR(View, GetCamera, () const, Camera*), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const String& GetCategory() const", asMETHODPR(View, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "const String& get_category() const", asMETHODPR(View, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Camera* View::GetCullCamera() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Camera@+ GetCullCamera() const", asMETHODPR(View, GetCullCamera, () const, Camera*), asCALL_THISCALL);
    // bool View::GetDrawDebug() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "bool GetDrawDebug() const", asMETHODPR(View, GetDrawDebug, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "VariantMap& GetEventDataMap() const", asMETHODPR(View, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "Object@+ GetEventSender() const", asMETHODPR(View, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const FrameInfo& View::GetFrameInfo() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const FrameInfo& GetFrameInfo() const", asMETHODPR(View, GetFrameInfo, () const, const FrameInfo&), asCALL_THISCALL);
    // const PODVector<Drawable*>& View::GetGeometries() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Drawable@>@ GetGeometries() const", asFUNCTION(View_GetGeometries_void), asCALL_CDECL_OBJFIRST);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(View, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "const Variant& get_globalVar(StringHash) const", asMETHODPR(View, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const VariantMap& GetGlobalVars() const", asMETHODPR(View, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "const VariantMap& get_globalVars() const", asMETHODPR(View, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Graphics* View::GetGraphics() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Graphics@+ GetGraphics() const", asMETHODPR(View, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // const Vector<LightBatchQueue>& View::GetLightQueues() const | File: ../Graphics/View.h
    // Error: type "const Vector<LightBatchQueue>&" can not automatically bind
    // const PODVector<Light*>& View::GetLights() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Light@>@ GetLights() const", asFUNCTION(View_GetLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned View::GetNumActiveOccluders() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "uint GetNumActiveOccluders() const", asMETHODPR(View, GetNumActiveOccluders, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Drawable*>& View::GetOccluders() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Drawable@>@ GetOccluders() const", asFUNCTION(View_GetOccluders_void), asCALL_CDECL_OBJFIRST);
    // OcclusionBuffer* View::GetOcclusionBuffer() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "OcclusionBuffer@+ GetOcclusionBuffer() const", asMETHODPR(View, GetOcclusionBuffer, () const, OcclusionBuffer*), asCALL_THISCALL);
    // Octree* View::GetOctree() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Octree@+ GetOctree() const", asMETHODPR(View, GetOctree, () const, Octree*), asCALL_THISCALL);
    // Renderer* View::GetRenderer() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Renderer@+ GetRenderer() const", asMETHODPR(View, GetRenderer, () const, Renderer*), asCALL_THISCALL);
    // RenderSurface* View::GetRenderTarget() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "RenderSurface@+ GetRenderTarget() const", asMETHODPR(View, GetRenderTarget, () const, RenderSurface*), asCALL_THISCALL);
    // Scene* View::GetScene() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Scene@+ GetScene() const", asMETHODPR(View, GetScene, () const, Scene*), asCALL_THISCALL);
    // View* View::GetSourceView() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "View@+ GetSourceView() const", asMETHODPR(View, GetSourceView, () const, View*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(View, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "StringHash GetType() const", asMETHODPR(View, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "StringHash get_type() const", asMETHODPR(View, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const String& GetTypeName() const", asMETHODPR(View, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "const String& get_typeName() const", asMETHODPR(View, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const IntRect& View::GetViewRect() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const IntRect& GetViewRect() const", asMETHODPR(View, GetViewRect, () const, const IntRect&), asCALL_THISCALL);
    // const IntVector2& View::GetViewSize() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const IntVector2& GetViewSize() const", asMETHODPR(View, GetViewSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasEventHandlers() const", asMETHODPR(View, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(View, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(View, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool IsInstanceOf(StringHash) const", asMETHODPR(View, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(View, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View", "int Refs() const", asMETHODPR(View, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "int get_refs() const", asMETHODPR(View, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View", asBEHAVE_RELEASE, "void f()", asMETHODPR(View, ReleaseRef, (), void), asCALL_THISCALL);
    // void View::Render() | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void Render()", asMETHODPR(View, Render, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SendEvent(StringHash)", asMETHODPR(View, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(View, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SetBlockEvents(bool)", asMETHODPR(View, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void View::SetCameraShaderParameters(Camera* camera) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetCameraShaderParameters(Camera@+)", asMETHODPR(View, SetCameraShaderParameters, (Camera*), void), asCALL_THISCALL);
    // void View::SetCommandShaderParameters(const RenderPathCommand& command) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetCommandShaderParameters(const RenderPathCommand&in)", asMETHODPR(View, SetCommandShaderParameters, (const RenderPathCommand&), void), asCALL_THISCALL);
    // void View::SetGBufferShaderParameters(const IntVector2& texSize, const IntRect& viewRect) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetGBufferShaderParameters(const IntVector2&in, const IntRect&in)", asMETHODPR(View, SetGBufferShaderParameters, (const IntVector2&, const IntRect&), void), asCALL_THISCALL);
    // void View::SetGlobalShaderParameters() | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetGlobalShaderParameters()", asMETHODPR(View, SetGlobalShaderParameters, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(View, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(View, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromAllEvents()", asMETHODPR(View, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(View_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(View, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(View, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(View, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void View::Update(const FrameInfo& frame) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void Update(const FrameInfo&in)", asMETHODPR(View, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // explicit View::View(Context* context) | File: ../Graphics/View.h
    engine->RegisterObjectBehaviour("View", asBEHAVE_FACTORY, "View@+ f()", asFUNCTION(View_View_Context), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View", "int WeakRefs() const", asMETHODPR(View, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View", "int get_weakRefs() const", asMETHODPR(View, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(View, "View")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(View, "View")
#endif
#ifdef REGISTER_MANUAL_PART_View
    REGISTER_MANUAL_PART_View(View, "View")
#endif
    RegisterSubclass<Object, View>(engine, "Object", "View");
    RegisterSubclass<RefCounted, View>(engine, "RefCounted", "View");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddChild(UIElement@+)", asMETHODPR(View3D, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_ADDREF, "void f()", asMETHODPR(View3D, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTag(const String&in)", asMETHODPR(View3D, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTags(const String&in, int8 = ';')", asMETHODPR(View3D, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTags(Array<String>@+)", asFUNCTION(View3D_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AdjustScissor(IntRect&)", asMETHODPR(View3D, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void AllocateNetworkState()", asMETHODPR(View3D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void ApplyAttributes()", asMETHODPR(View3D, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void BringToFront()", asMETHODPR(View3D, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(View3D, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void DisableLayoutUpdate()", asMETHODPR(View3D, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(View3D, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void EnableLayoutUpdate()", asMETHODPR(View3D, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool FilterAttributes(XMLElement&) const", asMETHODPR(View3D, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint FindChild(UIElement@+) const", asMETHODPR(View3D, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool GetAnimationEnabled() const", asMETHODPR(View3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_animationEnabled() const", asMETHODPR(View3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const String& GetAppliedStyle() const", asMETHODPR(View3D, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_style() const", asMETHODPR(View3D, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttribute(uint) const", asMETHODPR(View3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Variant get_attributes(uint) const", asMETHODPR(View3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttribute(const String&in) const", asMETHODPR(View3D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(View3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(View3D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(View3D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(View3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttributeDefault(uint) const", asMETHODPR(View3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Variant get_attributeDefaults(uint) const", asMETHODPR(View3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(View3D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool View3D::GetAutoUpdate() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "bool GetAutoUpdate() const", asMETHODPR(View3D, GetAutoUpdate, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_autoUpdate() const", asMETHODPR(View3D, GetAutoUpdate, () const, bool), asCALL_THISCALL);
    // void Window::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Window.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "BlendMode GetBlendMode() const", asMETHODPR(View3D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "BlendMode get_blendMode() const", asMETHODPR(View3D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool GetBlockEvents() const", asMETHODPR(View3D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetBorder() const", asMETHODPR(View3D, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_border() const", asMETHODPR(View3D, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetBringToBack() const", asMETHODPR(View3D, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_bringToBack() const", asMETHODPR(View3D, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetBringToFront() const", asMETHODPR(View3D, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_bringToFront() const", asMETHODPR(View3D, GetBringToFront, () const, bool), asCALL_THISCALL);
    // Node* View3D::GetCameraNode() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Node@+ GetCameraNode() const", asMETHODPR(View3D, GetCameraNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Node@+ get_cameraNode() const", asMETHODPR(View3D, GetCameraNode, () const, Node*), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const String& GetCategory() const", asMETHODPR(View3D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_category() const", asMETHODPR(View3D, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(uint) const", asMETHODPR(View3D, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_children(uint) const", asMETHODPR(View3D, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(View3D, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(View3D, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetChildOffset() const", asMETHODPR(View3D, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_childOffset() const", asMETHODPR(View3D, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildren() const", asFUNCTION(View3D_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(View3D_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(View3D_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetClipBorder() const", asMETHODPR(View3D, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_clipBorder() const", asMETHODPR(View3D, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetClipChildren() const", asMETHODPR(View3D, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_clipChildren() const", asMETHODPR(View3D, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetColor(Corner) const", asMETHODPR(View3D, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_colors(Corner) const", asMETHODPR(View3D, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetColorAttr() const", asMETHODPR(View3D, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntRect GetCombinedScreenRect()", asMETHODPR(View3D, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "IntRect get_combinedScreenRect()", asMETHODPR(View3D, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(View3D, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // Texture2D* View3D::GetDepthTexture() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Texture2D@+ GetDepthTexture() const", asMETHODPR(View3D, GetDepthTexture, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_depthTexture() const", asMETHODPR(View3D, GetDepthTexture, () const, Texture2D*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetDerivedColor() const", asMETHODPR(View3D, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "float GetDerivedOpacity() const", asMETHODPR(View3D, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "float get_derivedOpacity() const", asMETHODPR(View3D, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetDisabledOffset() const", asMETHODPR(View3D, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_disabledOffset() const", asMETHODPR(View3D, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(View3D, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(View3D, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint GetDragButtonCount() const", asMETHODPR(View3D, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_dragButtonCount() const", asMETHODPR(View3D, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(View3D, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(View3D, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(View3D, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetElementEventSender() const", asMETHODPR(View3D, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetEnableAnchor() const", asMETHODPR(View3D, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enableAnchor() const", asMETHODPR(View3D, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "VariantMap& GetEventDataMap() const", asMETHODPR(View3D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "Object@+ GetEventSender() const", asMETHODPR(View3D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool Window::GetFixedHeightResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetFixedHeightResizing() const", asMETHODPR(View3D, GetFixedHeightResizing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedHeightResizing() const", asMETHODPR(View3D, GetFixedHeightResizing, () const, bool), asCALL_THISCALL);
    // bool Window::GetFixedWidthResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetFixedWidthResizing() const", asMETHODPR(View3D, GetFixedWidthResizing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedWidthResizing() const", asMETHODPR(View3D, GetFixedWidthResizing, () const, bool), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "FocusMode GetFocusMode() const", asMETHODPR(View3D, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "FocusMode get_focusMode() const", asMETHODPR(View3D, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // unsigned View3D::GetFormat() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "uint GetFormat() const", asMETHODPR(View3D, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_format() const", asMETHODPR(View3D, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(View3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(View3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const VariantMap& GetGlobalVars() const", asMETHODPR(View3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const VariantMap& get_globalVars() const", asMETHODPR(View3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetHeight() const", asMETHODPR(View3D, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_height() const", asMETHODPR(View3D, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(View3D, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(View3D, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetHoverOffset() const", asMETHODPR(View3D, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_hoverOffset() const", asMETHODPR(View3D, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetImageBorder() const", asMETHODPR(View3D, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_imageBorder() const", asMETHODPR(View3D, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetImageRect() const", asMETHODPR(View3D, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_imageRect() const", asMETHODPR(View3D, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndent() const", asMETHODPR(View3D, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indent() const", asMETHODPR(View3D, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndentSpacing() const", asMETHODPR(View3D, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indentSpacing() const", asMETHODPR(View3D, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndentWidth() const", asMETHODPR(View3D, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indentWidth() const", asMETHODPR(View3D, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(View3D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetLayoutBorder() const", asMETHODPR(View3D, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_layoutBorder() const", asMETHODPR(View3D, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetLayoutElementMaxSize() const", asMETHODPR(View3D, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(View3D, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_layoutFlexScale() const", asMETHODPR(View3D, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "LayoutMode GetLayoutMode() const", asMETHODPR(View3D, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "LayoutMode get_layoutMode() const", asMETHODPR(View3D, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetLayoutSpacing() const", asMETHODPR(View3D, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_layoutSpacing() const", asMETHODPR(View3D, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "Material@+ GetMaterial() const", asMETHODPR(View3D, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Material@+ get_material() const", asMETHODPR(View3D, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetMaterialAttr() const", asMETHODPR(View3D, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetMaxAnchor() const", asMETHODPR(View3D, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_maxAnchor() const", asMETHODPR(View3D, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMaxHeight() const", asMETHODPR(View3D, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_maxHeight() const", asMETHODPR(View3D, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMaxOffset() const", asMETHODPR(View3D, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_maxOffset() const", asMETHODPR(View3D, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMaxSize() const", asMETHODPR(View3D, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_maxSize() const", asMETHODPR(View3D, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMaxWidth() const", asMETHODPR(View3D, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_maxWidth() const", asMETHODPR(View3D, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetMinAnchor() const", asMETHODPR(View3D, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_minAnchor() const", asMETHODPR(View3D, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMinHeight() const", asMETHODPR(View3D, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_minHeight() const", asMETHODPR(View3D, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMinOffset() const", asMETHODPR(View3D, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_minOffset() const", asMETHODPR(View3D, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMinSize() const", asMETHODPR(View3D, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_minSize() const", asMETHODPR(View3D, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMinWidth() const", asMETHODPR(View3D, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_minWidth() const", asMETHODPR(View3D, GetMinWidth, () const, int), asCALL_THISCALL);
    // bool Window::GetModalAutoDismiss() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetModalAutoDismiss() const", asMETHODPR(View3D, GetModalAutoDismiss, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_modalAutoDismiss() const", asMETHODPR(View3D, GetModalAutoDismiss, () const, bool), asCALL_THISCALL);
    // const Color& Window::GetModalFrameColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const Color& GetModalFrameColor() const", asMETHODPR(View3D, GetModalFrameColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_modalFrameColor() const", asMETHODPR(View3D, GetModalFrameColor, () const, const Color&), asCALL_THISCALL);
    // const IntVector2& Window::GetModalFrameSize() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetModalFrameSize() const", asMETHODPR(View3D, GetModalFrameSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_modalFrameSize() const", asMETHODPR(View3D, GetModalFrameSize, () const, const IntVector2&), asCALL_THISCALL);
    // const Color& Window::GetModalShadeColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const Color& GetModalShadeColor() const", asMETHODPR(View3D, GetModalShadeColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_modalShadeColor() const", asMETHODPR(View3D, GetModalShadeColor, () const, const Color&), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const String& GetName() const", asMETHODPR(View3D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_name() const", asMETHODPR(View3D, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "uint GetNumAttributes() const", asMETHODPR(View3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_numAttributes() const", asMETHODPR(View3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint GetNumChildren(bool = false) const", asMETHODPR(View3D, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_numChildren(bool = false) const", asMETHODPR(View3D, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "uint GetNumNetworkAttributes() const", asMETHODPR(View3D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(View3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(View3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(View3D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "float GetOpacity() const", asMETHODPR(View3D, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "float get_opacity() const", asMETHODPR(View3D, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetParent() const", asMETHODPR(View3D, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_parent() const", asMETHODPR(View3D, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetPivot() const", asMETHODPR(View3D, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_pivot() const", asMETHODPR(View3D, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetPosition() const", asMETHODPR(View3D, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_position() const", asMETHODPR(View3D, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetPriority() const", asMETHODPR(View3D, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_priority() const", asMETHODPR(View3D, GetPriority, () const, int), asCALL_THISCALL);
    // Texture2D* View3D::GetRenderTexture() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Texture2D@+ GetRenderTexture() const", asMETHODPR(View3D, GetRenderTexture, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_renderTexture() const", asMETHODPR(View3D, GetRenderTexture, () const, Texture2D*), asCALL_THISCALL);
    // const IntRect& Window::GetResizeBorder() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetResizeBorder() const", asMETHODPR(View3D, GetResizeBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_resizeBorder() const", asMETHODPR(View3D, GetResizeBorder, () const, const IntRect&), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetRoot() const", asMETHODPR(View3D, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_root() const", asMETHODPR(View3D, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // Scene* View3D::GetScene() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Scene@+ GetScene() const", asMETHODPR(View3D, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Scene@+ get_scene() const", asMETHODPR(View3D, GetScene, () const, Scene*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetScreenPosition() const", asMETHODPR(View3D, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_screenPosition() const", asMETHODPR(View3D, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetSize() const", asMETHODPR(View3D, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_size() const", asMETHODPR(View3D, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetSortChildren() const", asMETHODPR(View3D, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_sortChildren() const", asMETHODPR(View3D, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(View3D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<String>@ GetTags() const", asFUNCTION(View3D_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("View3D", "Array<String>@ get_tags() const", asFUNCTION(View3D_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "Texture@+ GetTexture() const", asMETHODPR(View3D, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture@+ get_texture() const", asMETHODPR(View3D, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetTextureAttr() const", asMETHODPR(View3D, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "TraversalMode GetTraversalMode() const", asMETHODPR(View3D, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "TraversalMode get_traversalMode() const", asMETHODPR(View3D, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "StringHash GetType() const", asMETHODPR(View3D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "StringHash get_type() const", asMETHODPR(View3D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const String& GetTypeName() const", asMETHODPR(View3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_typeName() const", asMETHODPR(View3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetUseDerivedOpacity() const", asMETHODPR(View3D, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_useDerivedOpacity() const", asMETHODPR(View3D, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(View3D, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const VariantMap& GetVars() const", asMETHODPR(View3D, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(View3D, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(View3D, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // Viewport* View3D::GetViewport() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Viewport@+ GetViewport() const", asMETHODPR(View3D, GetViewport, () const, Viewport*), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Viewport@+ get_viewport() const", asMETHODPR(View3D, GetViewport, () const, Viewport*), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetWidth() const", asMETHODPR(View3D, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_width() const", asMETHODPR(View3D, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasColorGradient() const", asMETHODPR(View3D, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_colorGradient() const", asMETHODPR(View3D, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasEventHandlers() const", asMETHODPR(View3D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasFocus() const", asMETHODPR(View3D, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_focus() const", asMETHODPR(View3D, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(View3D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(View3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasTag(const String&in) const", asMETHODPR(View3D, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void InsertChild(uint, UIElement@+)", asMETHODPR(View3D, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsChildOf(UIElement@+) const", asMETHODPR(View3D, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEditable() const", asMETHODPR(View3D, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_editable() const", asMETHODPR(View3D, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsElementEventSender() const", asMETHODPR(View3D, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_elementEventSender() const", asMETHODPR(View3D, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEnabled() const", asMETHODPR(View3D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enabled() const", asMETHODPR(View3D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEnabledSelf() const", asMETHODPR(View3D, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enabledSelf() const", asMETHODPR(View3D, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedHeight() const", asMETHODPR(View3D, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedHeight() const", asMETHODPR(View3D, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedSize() const", asMETHODPR(View3D, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedSize() const", asMETHODPR(View3D, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedWidth() const", asMETHODPR(View3D, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedWidth() const", asMETHODPR(View3D, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsHovering() const", asMETHODPR(View3D, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_hovering() const", asMETHODPR(View3D, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInside(IntVector2, bool)", asMETHODPR(View3D, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(View3D, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool IsInstanceOf(StringHash) const", asMETHODPR(View3D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInternal() const", asMETHODPR(View3D, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_internal() const", asMETHODPR(View3D, IsInternal, () const, bool), asCALL_THISCALL);
    // bool Window::IsModal() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsModal() const", asMETHODPR(View3D, IsModal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_modal() const", asMETHODPR(View3D, IsModal, () const, bool), asCALL_THISCALL);
    // bool Window::IsMovable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsMovable() const", asMETHODPR(View3D, IsMovable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_movable() const", asMETHODPR(View3D, IsMovable, () const, bool), asCALL_THISCALL);
    // bool Window::IsResizable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsResizable() const", asMETHODPR(View3D, IsResizable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_resizable() const", asMETHODPR(View3D, IsResizable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsSelected() const", asMETHODPR(View3D, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_selected() const", asMETHODPR(View3D, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool IsTemporary() const", asMETHODPR(View3D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_temporary() const", asMETHODPR(View3D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "bool IsTiled() const", asMETHODPR(View3D, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_tiled() const", asMETHODPR(View3D, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsVisible() const", asMETHODPR(View3D, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_visible() const", asMETHODPR(View3D, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsVisibleEffective() const", asMETHODPR(View3D, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_visibleEffective() const", asMETHODPR(View3D, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsWheelHandler() const", asMETHODPR(View3D, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(View3D, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool Load(Deserializer&)", asMETHODPR(View3D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(View3D, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(View3D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(const XMLElement&in)", asMETHODPR(View3D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(View3D, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(Deserializer&)", asMETHODPR(View3D, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void MarkNetworkUpdate()", asMETHODPR(View3D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(View3D, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(View3D, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(View3D, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(View3D, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(View3D, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(View3D, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool OnDragDropTest(UIElement@+)", asMETHODPR(View3D, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // void Window::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(View3D, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(View3D, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(View3D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(View3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // void Window::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(View3D, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnIndentSet()", asMETHODPR(View3D, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(View3D, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnPositionSet(const IntVector2&in)", asMETHODPR(View3D, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void View3D::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(View3D, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(View3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnSetEditable()", asMETHODPR(View3D, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnTextInput(const String&in)", asMETHODPR(View3D, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(View3D, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // void View3D::QueueUpdate() | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void QueueUpdate()", asMETHODPR(View3D, QueueUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(View3D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(View3D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View3D", "int Refs() const", asMETHODPR(View3D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_refs() const", asMETHODPR(View3D, Refs, () const, int), asCALL_THISCALL);
    // static void View3D::RegisterObject(Context* context) | File: ../UI/View3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_RELEASE, "void f()", asMETHODPR(View3D, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void Remove()", asMETHODPR(View3D, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveAllChildren()", asMETHODPR(View3D, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveAllTags()", asMETHODPR(View3D, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(View3D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(View3D, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveChildAtIndex(uint)", asMETHODPR(View3D, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void RemoveInstanceDefault()", asMETHODPR(View3D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void RemoveObjectAnimation()", asMETHODPR(View3D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool RemoveTag(const String&in)", asMETHODPR(View3D, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void ResetDeepEnabled()", asMETHODPR(View3D, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void ResetToDefault()", asMETHODPR(View3D, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool Save(Serializer&) const", asMETHODPR(View3D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SaveDefaultAttributes() const", asMETHODPR(View3D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool SaveJSON(JSONValue&) const", asMETHODPR(View3D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SaveXML(XMLElement&) const", asMETHODPR(View3D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(View3D, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(View3D, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SendEvent(StringHash)", asMETHODPR(View3D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(View3D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(View3D, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAnimationEnabled(bool)", asMETHODPR(View3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_animationEnabled(bool)", asMETHODPR(View3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAnimationTime(float)", asMETHODPR(View3D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(View3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(View3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(View3D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(View3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(View3D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(View3D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(View3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void View3D::SetAutoUpdate(bool enable) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetAutoUpdate(bool)", asMETHODPR(View3D, SetAutoUpdate, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_autoUpdate(bool)", asMETHODPR(View3D, SetAutoUpdate, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetBlendMode(BlendMode)", asMETHODPR(View3D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_blendMode(BlendMode)", asMETHODPR(View3D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SetBlockEvents(bool)", asMETHODPR(View3D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetBorder(const IntRect&in)", asMETHODPR(View3D, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_border(const IntRect&in)", asMETHODPR(View3D, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetBringToBack(bool)", asMETHODPR(View3D, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_bringToBack(bool)", asMETHODPR(View3D, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetBringToFront(bool)", asMETHODPR(View3D, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_bringToFront(bool)", asMETHODPR(View3D, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetChildOffset(const IntVector2&in)", asMETHODPR(View3D, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetClipBorder(const IntRect&in)", asMETHODPR(View3D, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_clipBorder(const IntRect&in)", asMETHODPR(View3D, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetClipChildren(bool)", asMETHODPR(View3D, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_clipChildren(bool)", asMETHODPR(View3D, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetColor(const Color&in)", asMETHODPR(View3D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_color(const Color&in)", asMETHODPR(View3D, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetColor(Corner, const Color&in)", asMETHODPR(View3D, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_colors(Corner, const Color&in)", asMETHODPR(View3D, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDeepEnabled(bool)", asMETHODPR(View3D, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(View3D, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_defaultStyle(XMLFile@+)", asMETHODPR(View3D, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(View3D, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(View3D, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetDisabledOffset(int, int)", asMETHODPR(View3D, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(View3D, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(View3D, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEditable(bool)", asMETHODPR(View3D, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_editable(bool)", asMETHODPR(View3D, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetElementEventSender(bool)", asMETHODPR(View3D, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_elementEventSender(bool)", asMETHODPR(View3D, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnableAnchor(bool)", asMETHODPR(View3D, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_enableAnchor(bool)", asMETHODPR(View3D, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnabled(bool)", asMETHODPR(View3D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_enabled(bool)", asMETHODPR(View3D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnabledRecursive(bool)", asMETHODPR(View3D, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedHeight(int)", asMETHODPR(View3D, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void Window::SetFixedHeightResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetFixedHeightResizing(bool)", asMETHODPR(View3D, SetFixedHeightResizing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_fixedHeightResizing(bool)", asMETHODPR(View3D, SetFixedHeightResizing, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedSize(const IntVector2&in)", asMETHODPR(View3D, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedSize(int, int)", asMETHODPR(View3D, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedWidth(int)", asMETHODPR(View3D, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void Window::SetFixedWidthResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetFixedWidthResizing(bool)", asMETHODPR(View3D, SetFixedWidthResizing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_fixedWidthResizing(bool)", asMETHODPR(View3D, SetFixedWidthResizing, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFocus(bool)", asMETHODPR(View3D, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_focus(bool)", asMETHODPR(View3D, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFocusMode(FocusMode)", asMETHODPR(View3D, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_focusMode(FocusMode)", asMETHODPR(View3D, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void View3D::SetFormat(unsigned format) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetFormat(uint)", asMETHODPR(View3D, SetFormat, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_format(uint)", asMETHODPR(View3D, SetFormat, (unsigned), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetFullImageRect()", asMETHODPR(View3D, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(View3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(View3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHeight(int)", asMETHODPR(View3D, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_height(int)", asMETHODPR(View3D, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(View3D, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(View3D, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHovering(bool)", asMETHODPR(View3D, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(View3D, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(View3D, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetHoverOffset(int, int)", asMETHODPR(View3D, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetImageBorder(const IntRect&in)", asMETHODPR(View3D, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_imageBorder(const IntRect&in)", asMETHODPR(View3D, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetImageRect(const IntRect&in)", asMETHODPR(View3D, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_imageRect(const IntRect&in)", asMETHODPR(View3D, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetIndent(int)", asMETHODPR(View3D, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_indent(int)", asMETHODPR(View3D, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetIndentSpacing(int)", asMETHODPR(View3D, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_indentSpacing(int)", asMETHODPR(View3D, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetInstanceDefault(bool)", asMETHODPR(View3D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(View3D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetInternal(bool)", asMETHODPR(View3D, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_internal(bool)", asMETHODPR(View3D, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(View3D, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(View3D, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutBorder(const IntRect&in)", asMETHODPR(View3D, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(View3D, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(View3D, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutMode(LayoutMode)", asMETHODPR(View3D, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutMode(LayoutMode)", asMETHODPR(View3D, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutSpacing(int)", asMETHODPR(View3D, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutSpacing(int)", asMETHODPR(View3D, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetMaterial(Material@+)", asMETHODPR(View3D, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_material(Material@+)", asMETHODPR(View3D, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(View3D, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(View3D, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxAnchor(const Vector2&in)", asMETHODPR(View3D, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxAnchor(float, float)", asMETHODPR(View3D, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxHeight(int)", asMETHODPR(View3D, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxHeight(int)", asMETHODPR(View3D, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(View3D, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxOffset(const IntVector2&in)", asMETHODPR(View3D, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxSize(const IntVector2&in)", asMETHODPR(View3D, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxSize(const IntVector2&in)", asMETHODPR(View3D, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxSize(int, int)", asMETHODPR(View3D, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxWidth(int)", asMETHODPR(View3D, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxWidth(int)", asMETHODPR(View3D, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinAnchor(const Vector2&in)", asMETHODPR(View3D, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minAnchor(const Vector2&in)", asMETHODPR(View3D, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinAnchor(float, float)", asMETHODPR(View3D, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinHeight(int)", asMETHODPR(View3D, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minHeight(int)", asMETHODPR(View3D, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinOffset(const IntVector2&in)", asMETHODPR(View3D, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minOffset(const IntVector2&in)", asMETHODPR(View3D, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinSize(const IntVector2&in)", asMETHODPR(View3D, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minSize(const IntVector2&in)", asMETHODPR(View3D, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinSize(int, int)", asMETHODPR(View3D, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinWidth(int)", asMETHODPR(View3D, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minWidth(int)", asMETHODPR(View3D, SetMinWidth, (int), void), asCALL_THISCALL);
    // void Window::SetModal(bool modal) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModal(bool)", asMETHODPR(View3D, SetModal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modal(bool)", asMETHODPR(View3D, SetModal, (bool), void), asCALL_THISCALL);
    // void Window::SetModalAutoDismiss(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalAutoDismiss(bool)", asMETHODPR(View3D, SetModalAutoDismiss, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalAutoDismiss(bool)", asMETHODPR(View3D, SetModalAutoDismiss, (bool), void), asCALL_THISCALL);
    // void Window::SetModalFrameColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalFrameColor(const Color&in)", asMETHODPR(View3D, SetModalFrameColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalFrameColor(const Color&in)", asMETHODPR(View3D, SetModalFrameColor, (const Color&), void), asCALL_THISCALL);
    // void Window::SetModalFrameSize(const IntVector2& size) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalFrameSize(const IntVector2&in)", asMETHODPR(View3D, SetModalFrameSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalFrameSize(const IntVector2&in)", asMETHODPR(View3D, SetModalFrameSize, (const IntVector2&), void), asCALL_THISCALL);
    // void Window::SetModalShadeColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalShadeColor(const Color&in)", asMETHODPR(View3D, SetModalShadeColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalShadeColor(const Color&in)", asMETHODPR(View3D, SetModalShadeColor, (const Color&), void), asCALL_THISCALL);
    // void Window::SetMovable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetMovable(bool)", asMETHODPR(View3D, SetMovable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_movable(bool)", asMETHODPR(View3D, SetMovable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetName(const String&in)", asMETHODPR(View3D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_name(const String&in)", asMETHODPR(View3D, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(View3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(View3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(View3D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetOpacity(float)", asMETHODPR(View3D, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_opacity(float)", asMETHODPR(View3D, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(View3D, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPivot(const Vector2&in)", asMETHODPR(View3D, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_pivot(const Vector2&in)", asMETHODPR(View3D, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPivot(float, float)", asMETHODPR(View3D, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPosition(const IntVector2&in)", asMETHODPR(View3D, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_position(const IntVector2&in)", asMETHODPR(View3D, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPosition(int, int)", asMETHODPR(View3D, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPriority(int)", asMETHODPR(View3D, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_priority(int)", asMETHODPR(View3D, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetRenderTexture(Texture2D@+)", asMETHODPR(View3D, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Window::SetResizable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetResizable(bool)", asMETHODPR(View3D, SetResizable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_resizable(bool)", asMETHODPR(View3D, SetResizable, (bool), void), asCALL_THISCALL);
    // void Window::SetResizeBorder(const IntRect& rect) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetResizeBorder(const IntRect&in)", asMETHODPR(View3D, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_resizeBorder(const IntRect&in)", asMETHODPR(View3D, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSelected(bool)", asMETHODPR(View3D, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_selected(bool)", asMETHODPR(View3D, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSize(const IntVector2&in)", asMETHODPR(View3D, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_size(const IntVector2&in)", asMETHODPR(View3D, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSize(int, int)", asMETHODPR(View3D, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSortChildren(bool)", asMETHODPR(View3D, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_sortChildren(bool)", asMETHODPR(View3D, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(View3D, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyle(const XMLElement&in)", asMETHODPR(View3D, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(View3D, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetTags(Array<String>@+)", asFUNCTION(View3D_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetTemporary(bool)", asMETHODPR(View3D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_temporary(bool)", asMETHODPR(View3D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTexture(Texture@+)", asMETHODPR(View3D, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_texture(Texture@+)", asMETHODPR(View3D, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(View3D, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTiled(bool)", asMETHODPR(View3D, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_tiled(bool)", asMETHODPR(View3D, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetTraversalMode(TraversalMode)", asMETHODPR(View3D, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_traversalMode(TraversalMode)", asMETHODPR(View3D, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetUseDerivedOpacity(bool)", asMETHODPR(View3D, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_useDerivedOpacity(bool)", asMETHODPR(View3D, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVar(StringHash, const Variant&in)", asMETHODPR(View3D, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(View3D, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(View3D, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void View3D::SetView(Scene* scene, Camera* camera, bool ownScene=true) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetView(Scene@+, Camera@+, bool = true)", asMETHODPR(View3D, SetView, (Scene*, Camera*, bool), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVisible(bool)", asMETHODPR(View3D, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_visible(bool)", asMETHODPR(View3D, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetWidth(int)", asMETHODPR(View3D, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_width(int)", asMETHODPR(View3D, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SortChildren()", asMETHODPR(View3D, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromAllEvents()", asMETHODPR(View3D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(View3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(View3D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(View3D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(View3D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void Update(float)", asMETHODPR(View3D, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void UpdateLayout()", asMETHODPR(View3D, UpdateLayout, (), void), asCALL_THISCALL);
    // explicit View3D::View3D(Context* context) | File: ../UI/View3D.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_FACTORY, "View3D@+ f()", asFUNCTION(View3D_View3D_Context), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View3D", "int WeakRefs() const", asMETHODPR(View3D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_weakRefs() const", asMETHODPR(View3D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(View3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(View3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(View3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Window
    REGISTER_MANUAL_PART_Window(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(View3D, "View3D")
#endif
#ifdef REGISTER_MANUAL_PART_View3D
    REGISTER_MANUAL_PART_View3D(View3D, "View3D")
#endif
    RegisterSubclass<Window, View3D>(engine, "Window", "View3D");
    RegisterSubclass<BorderImage, View3D>(engine, "BorderImage", "View3D");
    RegisterSubclass<UIElement, View3D>(engine, "UIElement", "View3D");
    RegisterSubclass<Animatable, View3D>(engine, "Animatable", "View3D");
    RegisterSubclass<Serializable, View3D>(engine, "Serializable", "View3D");
    RegisterSubclass<Object, View3D>(engine, "Object", "View3D");
    RegisterSubclass<RefCounted, View3D>(engine, "RefCounted", "View3D");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_ADDREF, "void f()", asMETHODPR(Viewport, AddRef, (), void), asCALL_THISCALL);
    // void Viewport::AllocateView() | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void AllocateView()", asMETHODPR(Viewport, AllocateView, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool GetBlockEvents() const", asMETHODPR(Viewport, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // Camera* Viewport::GetCamera() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Camera@+ GetCamera() const", asMETHODPR(Viewport, GetCamera, () const, Camera*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_camera() const", asMETHODPR(Viewport, GetCamera, () const, Camera*), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const String& GetCategory() const", asMETHODPR(Viewport, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const String& get_category() const", asMETHODPR(Viewport, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Camera* Viewport::GetCullCamera() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Camera@+ GetCullCamera() const", asMETHODPR(Viewport, GetCullCamera, () const, Camera*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_cullCamera() const", asMETHODPR(Viewport, GetCullCamera, () const, Camera*), asCALL_THISCALL);
    // bool Viewport::GetDrawDebug() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "bool GetDrawDebug() const", asMETHODPR(Viewport, GetDrawDebug, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "bool get_drawDebug() const", asMETHODPR(Viewport, GetDrawDebug, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "VariantMap& GetEventDataMap() const", asMETHODPR(Viewport, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "Object@+ GetEventSender() const", asMETHODPR(Viewport, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Viewport, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Viewport, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const VariantMap& GetGlobalVars() const", asMETHODPR(Viewport, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const VariantMap& get_globalVars() const", asMETHODPR(Viewport, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const IntRect& Viewport::GetRect() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "const IntRect& GetRect() const", asMETHODPR(Viewport, GetRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const IntRect& get_rect() const", asMETHODPR(Viewport, GetRect, () const, const IntRect&), asCALL_THISCALL);
    // RenderPath* Viewport::GetRenderPath() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "RenderPath@+ GetRenderPath() const", asMETHODPR(Viewport, GetRenderPath, () const, RenderPath*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "RenderPath@+ get_renderPath() const", asMETHODPR(Viewport, GetRenderPath, () const, RenderPath*), asCALL_THISCALL);
    // Scene* Viewport::GetScene() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Scene@+ GetScene() const", asMETHODPR(Viewport, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Scene@+ get_scene() const", asMETHODPR(Viewport, GetScene, () const, Scene*), asCALL_THISCALL);
    // Ray Viewport::GetScreenRay(int x, int y) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Ray GetScreenRay(int, int) const", asMETHODPR(Viewport, GetScreenRay, (int, int) const, Ray), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Viewport, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "StringHash GetType() const", asMETHODPR(Viewport, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "StringHash get_type() const", asMETHODPR(Viewport, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const String& GetTypeName() const", asMETHODPR(Viewport, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const String& get_typeName() const", asMETHODPR(Viewport, GetTypeName, () const, const String&), asCALL_THISCALL);
    // View* Viewport::GetView() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "View@+ GetView() const", asMETHODPR(Viewport, GetView, () const, View*), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasEventHandlers() const", asMETHODPR(Viewport, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Viewport, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Viewport, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool IsInstanceOf(StringHash) const", asMETHODPR(Viewport, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Viewport, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Viewport", "int Refs() const", asMETHODPR(Viewport, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "int get_refs() const", asMETHODPR(Viewport, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_RELEASE, "void f()", asMETHODPR(Viewport, ReleaseRef, (), void), asCALL_THISCALL);
    // Vector3 Viewport::ScreenToWorldPoint(int x, int y, float depth) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Vector3 ScreenToWorldPoint(int, int, float) const", asMETHODPR(Viewport, ScreenToWorldPoint, (int, int, float) const, Vector3), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SendEvent(StringHash)", asMETHODPR(Viewport, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Viewport, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SetBlockEvents(bool)", asMETHODPR(Viewport, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Viewport::SetCamera(Camera* camera) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetCamera(Camera@+)", asMETHODPR(Viewport, SetCamera, (Camera*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_camera(Camera@+)", asMETHODPR(Viewport, SetCamera, (Camera*), void), asCALL_THISCALL);
    // void Viewport::SetCullCamera(Camera* camera) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetCullCamera(Camera@+)", asMETHODPR(Viewport, SetCullCamera, (Camera*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_cullCamera(Camera@+)", asMETHODPR(Viewport, SetCullCamera, (Camera*), void), asCALL_THISCALL);
    // void Viewport::SetDrawDebug(bool enable) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetDrawDebug(bool)", asMETHODPR(Viewport, SetDrawDebug, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_drawDebug(bool)", asMETHODPR(Viewport, SetDrawDebug, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Viewport, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Viewport, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Viewport::SetRect(const IntRect& rect) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetRect(const IntRect&in)", asMETHODPR(Viewport, SetRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_rect(const IntRect&in)", asMETHODPR(Viewport, SetRect, (const IntRect&), void), asCALL_THISCALL);
    // void Viewport::SetRenderPath(RenderPath* renderPath) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetRenderPath(RenderPath@+)", asMETHODPR(Viewport, SetRenderPath, (RenderPath*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_renderPath(RenderPath@+)", asMETHODPR(Viewport, SetRenderPath, (RenderPath*), void), asCALL_THISCALL);
    // bool Viewport::SetRenderPath(XMLFile* file) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "bool SetRenderPath(XMLFile@+)", asMETHODPR(Viewport, SetRenderPath, (XMLFile*), bool), asCALL_THISCALL);
    // void Viewport::SetScene(Scene* scene) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetScene(Scene@+)", asMETHODPR(Viewport, SetScene, (Scene*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_scene(Scene@+)", asMETHODPR(Viewport, SetScene, (Scene*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromAllEvents()", asMETHODPR(Viewport, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Viewport_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Viewport, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Viewport, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Viewport, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // explicit Viewport::Viewport(Context* context) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f()", asFUNCTION(Viewport_Viewport_Context), asCALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, RenderPath@+ = null)", asFUNCTION(Viewport_Viewport_Context_Scene_Camera_RenderPath), asCALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, const IntRect&in, RenderPath@+ = null)", asFUNCTION(Viewport_Viewport_Context_Scene_Camera_IntRect_RenderPath), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Viewport", "int WeakRefs() const", asMETHODPR(Viewport, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "int get_weakRefs() const", asMETHODPR(Viewport, WeakRefs, () const, int), asCALL_THISCALL);
    // IntVector2 Viewport::WorldToScreenPoint(const Vector3& worldPos) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "IntVector2 WorldToScreenPoint(const Vector3&in) const", asMETHODPR(Viewport, WorldToScreenPoint, (const Vector3&) const, IntVector2), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Viewport, "Viewport")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Viewport, "Viewport")
#endif
#ifdef REGISTER_MANUAL_PART_Viewport
    REGISTER_MANUAL_PART_Viewport(Viewport, "Viewport")
#endif
    RegisterSubclass<Object, Viewport>(engine, "Object", "Viewport");
    RegisterSubclass<RefCounted, Viewport>(engine, "RefCounted", "Viewport");

    // VariantMap VAnimEventFrame::eventData_ | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectProperty("VAnimEventFrame", "VariantMap eventData", offsetof(VAnimEventFrame, eventData_));
    // StringHash VAnimEventFrame::eventType_ | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectProperty("VAnimEventFrame", "StringHash eventType", offsetof(VAnimEventFrame, eventType_));
    // float VAnimEventFrame::time_ | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectProperty("VAnimEventFrame", "float time", offsetof(VAnimEventFrame, time_));
    // VAnimEventFrame& VAnimEventFrame::operator=(const VAnimEventFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VAnimEventFrame>(engine, "VAnimEventFrame");
#ifdef REGISTER_MANUAL_PART_VAnimEventFrame
    REGISTER_MANUAL_PART_VAnimEventFrame(VAnimEventFrame, "VAnimEventFrame")
#endif

    // float VAnimKeyFrame::time_ | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectProperty("VAnimKeyFrame", "float time", offsetof(VAnimKeyFrame, time_));
    // Variant VAnimKeyFrame::value_ | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectProperty("VAnimKeyFrame", "Variant value", offsetof(VAnimKeyFrame, value_));
    // VAnimKeyFrame& VAnimKeyFrame::operator=(const VAnimKeyFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VAnimKeyFrame>(engine, "VAnimKeyFrame");
#ifdef REGISTER_MANUAL_PART_VAnimKeyFrame
    REGISTER_MANUAL_PART_VAnimKeyFrame(VAnimKeyFrame, "VAnimKeyFrame")
#endif

#ifdef URHO3D_URHO2D
    // unsigned Vertex2D::color_ | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectProperty("Vertex2D", "uint color", offsetof(Vertex2D, color_));
    // Vector3 Vertex2D::position_ | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectProperty("Vertex2D", "Vector3 position", offsetof(Vertex2D, position_));
    // Vector2 Vertex2D::uv_ | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectProperty("Vertex2D", "Vector2 uv", offsetof(Vertex2D, uv_));
    // Vertex2D& Vertex2D::operator=(const Vertex2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Vertex2D>(engine, "Vertex2D");
#ifdef REGISTER_MANUAL_PART_Vertex2D
    REGISTER_MANUAL_PART_Vertex2D(Vertex2D, "Vertex2D")
#endif
#endif

    // SharedArrayPtr<unsigned char> VertexBufferDesc::data_ | File: ../Graphics/Model.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // unsigned VertexBufferDesc::dataSize_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("VertexBufferDesc", "uint dataSize", offsetof(VertexBufferDesc, dataSize_));
    // unsigned VertexBufferDesc::vertexCount_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("VertexBufferDesc", "uint vertexCount", offsetof(VertexBufferDesc, vertexCount_));
    // PODVector<VertexElement> VertexBufferDesc::vertexElements_ | File: ../Graphics/Model.h
    // Error: type "PODVector<VertexElement>" can not automatically bind
    // VertexBufferDesc& VertexBufferDesc::operator=(const VertexBufferDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexBufferDesc>(engine, "VertexBufferDesc");
#ifdef REGISTER_MANUAL_PART_VertexBufferDesc
    REGISTER_MANUAL_PART_VertexBufferDesc(VertexBufferDesc, "VertexBufferDesc")
#endif

    // unsigned VertexBufferMorph::dataSize_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("VertexBufferMorph", "uint dataSize", offsetof(VertexBufferMorph, dataSize_));
    // VertexMaskFlags VertexBufferMorph::elementMask_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("VertexBufferMorph", "VertexMaskFlags elementMask", offsetof(VertexBufferMorph, elementMask_));
    // SharedArrayPtr<unsigned char> VertexBufferMorph::morphData_ | File: ../Graphics/Model.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // unsigned VertexBufferMorph::vertexCount_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("VertexBufferMorph", "uint vertexCount", offsetof(VertexBufferMorph, vertexCount_));
    // VertexBufferMorph& VertexBufferMorph::operator=(const VertexBufferMorph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexBufferMorph>(engine, "VertexBufferMorph");
#ifdef REGISTER_MANUAL_PART_VertexBufferMorph
    REGISTER_MANUAL_PART_VertexBufferMorph(VertexBufferMorph, "VertexBufferMorph")
#endif

    // unsigned char VertexElement::index_ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectProperty("VertexElement", "uint8 index", offsetof(VertexElement, index_));
    // unsigned VertexElement::offset_ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectProperty("VertexElement", "uint offset", offsetof(VertexElement, offset_));
    // bool VertexElement::perInstance_ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectProperty("VertexElement", "bool perInstance", offsetof(VertexElement, perInstance_));
    // VertexElementSemantic VertexElement::semantic_ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectProperty("VertexElement", "VertexElementSemantic semantic", offsetof(VertexElement, semantic_));
    // VertexElementType VertexElement::type_ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectProperty("VertexElement", "VertexElementType type", offsetof(VertexElement, type_));
    // bool VertexElement::operator==(const VertexElement& rhs) const | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectMethod("VertexElement", "bool opEquals(const VertexElement&in) const", asMETHODPR(VertexElement, operator==, (const VertexElement&) const, bool), asCALL_THISCALL);
    // VertexElement::VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0, bool perInstance=false) noexcept | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_CONSTRUCT, "void f(VertexElementType, VertexElementSemantic, uint8 = 0, bool = false)", asFUNCTION(VertexElement_VertexElement_VertexElementType_VertexElementSemantic_unsignedchar_bool), asCALL_CDECL_OBJFIRST);
    // VertexElement& VertexElement::operator=(const VertexElement&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexElement>(engine, "VertexElement");
#ifdef REGISTER_MANUAL_PART_VertexElement
    REGISTER_MANUAL_PART_VertexElement(VertexElement, "VertexElement")
#endif

}

}
