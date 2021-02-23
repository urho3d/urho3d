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
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ValueAnimation, AddRef, (), void), AS_CALL_THISCALL);
    // bool ValueAnimation::BeginLoad(Deserializer& source) override | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool BeginLoad(Deserializer&)", AS_METHODPR(ValueAnimation, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool EndLoad()", AS_METHODPR(ValueAnimation, EndLoad, (), bool), AS_CALL_THISCALL);
    // Variant ValueAnimation::GetAnimationValue(float scaledTime) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "Variant GetAnimationValue(float) const", AS_METHODPR(ValueAnimation, GetAnimationValue, (float) const, Variant), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(ValueAnimation, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // float ValueAnimation::GetBeginTime() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetBeginTime() const", AS_METHODPR(ValueAnimation, GetBeginTime, () const, float), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool GetBlockEvents() const", AS_METHODPR(ValueAnimation, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetCategory() const", AS_METHODPR(ValueAnimation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_category() const", AS_METHODPR(ValueAnimation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ValueAnimation::GetEndTime() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetEndTime() const", AS_METHODPR(ValueAnimation, GetEndTime, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "VariantMap& GetEventDataMap() const", AS_METHODPR(ValueAnimation, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // void ValueAnimation::GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames) const | File: ../Scene/ValueAnimation.h
    // Error: type "PODVector<const VAnimEventFrame*>&" can not automatically bind
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "Object@+ GetEventSender() const", AS_METHODPR(ValueAnimation, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ValueAnimation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ValueAnimation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ValueAnimation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const VariantMap& get_globalVars() const", AS_METHODPR(ValueAnimation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // InterpMethod ValueAnimation::GetInterpolationMethod() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "InterpMethod GetInterpolationMethod() const", AS_METHODPR(ValueAnimation, GetInterpolationMethod, () const, InterpMethod), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "InterpMethod get_interpolationMethod() const", AS_METHODPR(ValueAnimation, GetInterpolationMethod, () const, InterpMethod), AS_CALL_THISCALL);
    // const Vector<VAnimKeyFrame>& ValueAnimation::GetKeyFrames() const | File: ../Scene/ValueAnimation.h
    // Error: type "const Vector<VAnimKeyFrame>&" can not automatically bind
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "uint GetMemoryUse() const", AS_METHODPR(ValueAnimation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "uint get_memoryUse() const", AS_METHODPR(ValueAnimation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetName() const", AS_METHODPR(ValueAnimation, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_name() const", AS_METHODPR(ValueAnimation, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "StringHash GetNameHash() const", AS_METHODPR(ValueAnimation, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // void* ValueAnimation::GetOwner() const | File: ../Scene/ValueAnimation.h
    // Error: type "void*" can not automatically bind
    // float ValueAnimation::GetSplineTension() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "float GetSplineTension() const", AS_METHODPR(ValueAnimation, GetSplineTension, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "float get_splineTension() const", AS_METHODPR(ValueAnimation, GetSplineTension, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ValueAnimation, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "StringHash GetType() const", AS_METHODPR(ValueAnimation, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "StringHash get_type() const", AS_METHODPR(ValueAnimation, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "const String& GetTypeName() const", AS_METHODPR(ValueAnimation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "const String& get_typeName() const", AS_METHODPR(ValueAnimation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "uint GetUseTimer()", AS_METHODPR(ValueAnimation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "uint get_useTimer()", AS_METHODPR(ValueAnimation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // VariantType ValueAnimation::GetValueType() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "VariantType GetValueType() const", AS_METHODPR(ValueAnimation, GetValueType, () const, VariantType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "VariantType get_valueType() const", AS_METHODPR(ValueAnimation, GetValueType, () const, VariantType), AS_CALL_THISCALL);
    // bool ValueAnimation::HasEventFrames() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasEventFrames() const", AS_METHODPR(ValueAnimation, HasEventFrames, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasEventHandlers() const", AS_METHODPR(ValueAnimation, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ValueAnimation, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ValueAnimation, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ValueAnimation, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool ValueAnimation::IsValid() const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool IsValid() const", AS_METHODPR(ValueAnimation, IsValid, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool Load(Deserializer&)", AS_METHODPR(ValueAnimation, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadFile(const String&in)", AS_METHODPR(ValueAnimation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "bool Load(const String&in)", AS_METHODPR(ValueAnimation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // bool ValueAnimation::LoadJSON(const JSONValue& source) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ValueAnimation, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool ValueAnimation::LoadXML(const XMLElement& source) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ValueAnimation, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ValueAnimation, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimation", "int Refs() const", AS_METHODPR(ValueAnimation, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "int get_refs() const", AS_METHODPR(ValueAnimation, Refs, () const, int), AS_CALL_THISCALL);
    // static void ValueAnimation::RegisterObject(Context* context) | File: ../Scene/ValueAnimation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ValueAnimation, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void ResetUseTimer()", AS_METHODPR(ValueAnimation, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool ValueAnimation::Save(Serializer& dest) const override | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool Save(Serializer&) const", AS_METHODPR(ValueAnimation, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveFile(const String&in) const", AS_METHODPR(ValueAnimation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "bool Save(const String&in) const", AS_METHODPR(ValueAnimation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // bool ValueAnimation::SaveJSON(JSONValue& dest) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ValueAnimation, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool ValueAnimation::SaveXML(XMLElement& dest) const | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SaveXML(XMLElement&) const", AS_METHODPR(ValueAnimation, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SendEvent(StringHash)", AS_METHODPR(ValueAnimation, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ValueAnimation, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(ValueAnimation, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetBlockEvents(bool)", AS_METHODPR(ValueAnimation, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void ValueAnimation::SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData=VariantMap()) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetEventFrame(float, const StringHash&in, const VariantMap&in = VariantMap())", AS_METHODPR(ValueAnimation, SetEventFrame, (float, const StringHash&, const VariantMap&), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ValueAnimation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ValueAnimation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void ValueAnimation::SetInterpolationMethod(InterpMethod method) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetInterpolationMethod(InterpMethod)", AS_METHODPR(ValueAnimation, SetInterpolationMethod, (InterpMethod), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_interpolationMethod(InterpMethod)", AS_METHODPR(ValueAnimation, SetInterpolationMethod, (InterpMethod), void), AS_CALL_THISCALL);
    // bool ValueAnimation::SetKeyFrame(float time, const Variant& value) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "bool SetKeyFrame(float, const Variant&in)", AS_METHODPR(ValueAnimation, SetKeyFrame, (float, const Variant&), bool), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetMemoryUse(uint)", AS_METHODPR(ValueAnimation, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetName(const String&in)", AS_METHODPR(ValueAnimation, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_name(const String&in)", AS_METHODPR(ValueAnimation, SetName, (const String&), void), AS_CALL_THISCALL);
    // void ValueAnimation::SetOwner(void* owner) | File: ../Scene/ValueAnimation.h
    // Error: type "void*" can not automatically bind
    // void ValueAnimation::SetSplineTension(float tension) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetSplineTension(float)", AS_METHODPR(ValueAnimation, SetSplineTension, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_splineTension(float)", AS_METHODPR(ValueAnimation, SetSplineTension, (float), void), AS_CALL_THISCALL);
    // void ValueAnimation::SetValueType(VariantType valueType) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectMethod("ValueAnimation", "void SetValueType(VariantType)", AS_METHODPR(ValueAnimation, SetValueType, (VariantType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_valueType(VariantType)", AS_METHODPR(ValueAnimation, SetValueType, (VariantType), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromAllEvents()", AS_METHODPR(ValueAnimation, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ValueAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ValueAnimation, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ValueAnimation, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ValueAnimation", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ValueAnimation, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // explicit ValueAnimation::ValueAnimation(Context* context) | File: ../Scene/ValueAnimation.h
    engine->RegisterObjectBehaviour("ValueAnimation", asBEHAVE_FACTORY, "ValueAnimation@+ f()", AS_FUNCTION(ValueAnimation_ValueAnimation_Context), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimation", "int WeakRefs() const", AS_METHODPR(ValueAnimation, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "int get_weakRefs() const", AS_METHODPR(ValueAnimation, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ValueAnimationInfo, AddRef, (), void), AS_CALL_THISCALL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "ValueAnimation@+ GetAnimation() const", AS_METHODPR(ValueAnimationInfo, GetAnimation, () const, ValueAnimation*), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "float GetSpeed() const", AS_METHODPR(ValueAnimationInfo, GetSpeed, () const, float), AS_CALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "Object@+ GetTarget() const", AS_METHODPR(ValueAnimationInfo, GetTarget, () const, Object*), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "float GetTime() const", AS_METHODPR(ValueAnimationInfo, GetTime, () const, float), AS_CALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "WrapMode GetWrapMode() const", AS_METHODPR(ValueAnimationInfo, GetWrapMode, () const, WrapMode), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "int Refs() const", AS_METHODPR(ValueAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimationInfo", "int get_refs() const", AS_METHODPR(ValueAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ValueAnimationInfo, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "void SetSpeed(float)", AS_METHODPR(ValueAnimationInfo, SetSpeed, (float), void), AS_CALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "bool SetTime(float)", AS_METHODPR(ValueAnimationInfo, SetTime, (float), bool), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "void SetWrapMode(WrapMode)", AS_METHODPR(ValueAnimationInfo, SetWrapMode, (WrapMode), void), AS_CALL_THISCALL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "bool Update(float)", AS_METHODPR(ValueAnimationInfo, Update, (float), bool), AS_CALL_THISCALL);
    // ValueAnimationInfo::ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ValueAnimationInfo_ValueAnimationInfo_ValueAnimation_WrapMode_float), AS_CALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(Object@+, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ValueAnimationInfo_ValueAnimationInfo_Object_ValueAnimation_WrapMode_float), AS_CALL_CDECL);
    // ValueAnimationInfo::ValueAnimationInfo(const ValueAnimationInfo& other) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectBehaviour("ValueAnimationInfo", asBEHAVE_FACTORY, "ValueAnimationInfo@+ f(const ValueAnimationInfo&in)", AS_FUNCTION(ValueAnimationInfo_ValueAnimationInfo_ValueAnimationInfo), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ValueAnimationInfo", "int WeakRefs() const", AS_METHODPR(ValueAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimationInfo", "int get_weakRefs() const", AS_METHODPR(ValueAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Variant", "void Clear()", AS_METHODPR(Variant, Clear, (), void), AS_CALL_THISCALL);
    // void Variant::FromString(const String& type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "void FromString(const String&in, const String&in)", AS_METHODPR(Variant, FromString, (const String&, const String&), void), AS_CALL_THISCALL);
    // void Variant::FromString(const char* type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // void Variant::FromString(VariantType type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "void FromString(VariantType, const String&in)", AS_METHODPR(Variant, FromString, (VariantType, const String&), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Variant", "bool GetBool() const", AS_METHODPR(Variant, GetBool, () const, bool), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& Variant::GetBuffer() const | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // PODVector<unsigned char>* Variant::GetBufferPtr() | File: ../Core/Variant.h
    // Error: type "PODVector<unsigned char>*" can not automatically bind
    // const Color& Variant::GetColor() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Color& GetColor() const", AS_METHODPR(Variant, GetColor, () const, const Color&), AS_CALL_THISCALL);
    // template<class T> T Variant::GetCustom() const | File: ../Core/Variant.h
    // Not registered because template
    // template<class T> T* Variant::GetCustomPtr() | File: ../Core/Variant.h
    // Not registered because template
    // CustomVariantValue* Variant::GetCustomVariantValuePtr() | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // const CustomVariantValue* Variant::GetCustomVariantValuePtr() const | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // double Variant::GetDouble() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "double GetDouble() const", AS_METHODPR(Variant, GetDouble, () const, double), AS_CALL_THISCALL);
    // float Variant::GetFloat() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "float GetFloat() const", AS_METHODPR(Variant, GetFloat, () const, float), AS_CALL_THISCALL);
    // int Variant::GetInt() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "int GetInt() const", AS_METHODPR(Variant, GetInt, () const, int), AS_CALL_THISCALL);
    // long long Variant::GetInt64() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "int64 GetInt64() const", AS_METHODPR(Variant, GetInt64, () const, long long), AS_CALL_THISCALL);
    // const IntRect& Variant::GetIntRect() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntRect& GetIntRect() const", AS_METHODPR(Variant, GetIntRect, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntVector2& Variant::GetIntVector2() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntVector2& GetIntVector2() const", AS_METHODPR(Variant, GetIntVector2, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector3& Variant::GetIntVector3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const IntVector3& GetIntVector3() const", AS_METHODPR(Variant, GetIntVector3, () const, const IntVector3&), AS_CALL_THISCALL);
    // const Matrix3& Variant::GetMatrix3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix3& GetMatrix3() const", AS_METHODPR(Variant, GetMatrix3, () const, const Matrix3&), AS_CALL_THISCALL);
    // const Matrix3x4& Variant::GetMatrix3x4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix3x4& GetMatrix3x4() const", AS_METHODPR(Variant, GetMatrix3x4, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // const Matrix4& Variant::GetMatrix4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Matrix4& GetMatrix4() const", AS_METHODPR(Variant, GetMatrix4, () const, const Matrix4&), AS_CALL_THISCALL);
    // RefCounted* Variant::GetPtr() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "RefCounted@+ GetPtr() const", AS_METHODPR(Variant, GetPtr, () const, RefCounted*), AS_CALL_THISCALL);
    // const Quaternion& Variant::GetQuaternion() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Quaternion& GetQuaternion() const", AS_METHODPR(Variant, GetQuaternion, () const, const Quaternion&), AS_CALL_THISCALL);
    // const Rect& Variant::GetRect() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Rect& GetRect() const", AS_METHODPR(Variant, GetRect, () const, const Rect&), AS_CALL_THISCALL);
    // const ResourceRef& Variant::GetResourceRef() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const ResourceRef& GetResourceRef() const", AS_METHODPR(Variant, GetResourceRef, () const, const ResourceRef&), AS_CALL_THISCALL);
    // const ResourceRefList& Variant::GetResourceRefList() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const ResourceRefList& GetResourceRefList() const", AS_METHODPR(Variant, GetResourceRefList, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // const String& Variant::GetString() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const String& GetString() const", AS_METHODPR(Variant, GetString, () const, const String&), AS_CALL_THISCALL);
    // StringHash Variant::GetStringHash() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "StringHash GetStringHash() const", AS_METHODPR(Variant, GetStringHash, () const, StringHash), AS_CALL_THISCALL);
    // const StringVector& Variant::GetStringVector() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Array<String>@ GetStringVector() const", AS_FUNCTION_OBJFIRST(Variant_GetStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // StringVector* Variant::GetStringVectorPtr() | File: ../Core/Variant.h
    // Error: type "StringVector*" can not automatically bind
    // VariantType Variant::GetType() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VariantType GetType() const", AS_METHODPR(Variant, GetType, () const, VariantType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VariantType get_type() const", AS_METHODPR(Variant, GetType, () const, VariantType), AS_CALL_THISCALL);
    // static VariantType Variant::GetTypeFromName(const String& typeName) | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalFunction("VariantType GetTypeFromName(const String&in)", AS_FUNCTIONPR(Variant::GetTypeFromName, (const String&), VariantType), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static VariantType Variant::GetTypeFromName(const char* typeName) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // String Variant::GetTypeName() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "String GetTypeName() const", AS_METHODPR(Variant, GetTypeName, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "String get_typeName() const", AS_METHODPR(Variant, GetTypeName, () const, String), AS_CALL_THISCALL);
    // static String Variant::GetTypeName(VariantType type) | File: ../Core/Variant.h
    engine->SetDefaultNamespace("Variant");
    engine->RegisterGlobalFunction("String GetTypeName(VariantType)", AS_FUNCTIONPR(Variant::GetTypeName, (VariantType), String), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // unsigned Variant::GetUInt() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "uint GetUInt() const", AS_METHODPR(Variant, GetUInt, () const, unsigned), AS_CALL_THISCALL);
    // unsigned long long Variant::GetUInt64() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "uint64 GetUInt64() const", AS_METHODPR(Variant, GetUInt64, () const, unsigned long long), AS_CALL_THISCALL);
    // const VariantMap& Variant::GetVariantMap() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const VariantMap& GetVariantMap() const", AS_METHODPR(Variant, GetVariantMap, () const, const VariantMap&), AS_CALL_THISCALL);
    // VariantMap* Variant::GetVariantMapPtr() | File: ../Core/Variant.h
    // Error: type "VariantMap*" can not automatically bind
    // const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // VariantVector* Variant::GetVariantVectorPtr() | File: ../Core/Variant.h
    // Error: type "VariantVector*" can not automatically bind
    // const Vector2& Variant::GetVector2() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector2& GetVector2() const", AS_METHODPR(Variant, GetVector2, () const, const Vector2&), AS_CALL_THISCALL);
    // const Vector3& Variant::GetVector3() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector3& GetVector3() const", AS_METHODPR(Variant, GetVector3, () const, const Vector3&), AS_CALL_THISCALL);
    // const Vector4& Variant::GetVector4() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "const Vector4& GetVector4() const", AS_METHODPR(Variant, GetVector4, () const, const Vector4&), AS_CALL_THISCALL);
    // VectorBuffer Variant::GetVectorBuffer() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetVectorBuffer() const", AS_METHODPR(Variant, GetVectorBuffer, () const, VectorBuffer), AS_CALL_THISCALL);
    // void* Variant::GetVoidPtr() const | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // bool Variant::IsCustom() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsCustom() const", AS_METHODPR(Variant, IsCustom, () const, bool), AS_CALL_THISCALL);
    // template<class T> bool Variant::IsCustomType() const | File: ../Core/Variant.h
    // Not registered because template
    // bool Variant::IsEmpty() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsEmpty() const", AS_METHODPR(Variant, IsEmpty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_empty() const", AS_METHODPR(Variant, IsEmpty, () const, bool), AS_CALL_THISCALL);
    // bool Variant::IsZero() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool IsZero() const", AS_METHODPR(Variant, IsZero, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_zero() const", AS_METHODPR(Variant, IsZero, () const, bool), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Variant& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Variant&in)", AS_METHODPR(Variant, operator=, (const Variant&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(int rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(int)", AS_METHODPR(Variant, operator=, (int), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(long long rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(int64)", AS_METHODPR(Variant, operator=, (long long), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(unsigned long long rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(uint64)", AS_METHODPR(Variant, operator=, (unsigned long long), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(unsigned rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(uint)", AS_METHODPR(Variant, operator=, (unsigned), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const StringHash& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const StringHash&in)", AS_METHODPR(Variant, operator=, (const StringHash&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(bool rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(bool)", AS_METHODPR(Variant, operator=, (bool), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(float rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(float)", AS_METHODPR(Variant, operator=, (float), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(double rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(double)", AS_METHODPR(Variant, operator=, (double), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Vector2& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector2&in)", AS_METHODPR(Variant, operator=, (const Vector2&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Vector3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector3&in)", AS_METHODPR(Variant, operator=, (const Vector3&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Vector4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector4&in)", AS_METHODPR(Variant, operator=, (const Vector4&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Quaternion& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Quaternion&in)", AS_METHODPR(Variant, operator=, (const Quaternion&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Color& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Color&in)", AS_METHODPR(Variant, operator=, (const Color&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const String& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const String&in)", AS_METHODPR(Variant, operator=, (const String&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const char* rhs) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant& Variant::operator=(const PODVector<unsigned char>& rhs) | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant& Variant::operator=(const VectorBuffer& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VectorBuffer&in)", AS_METHODPR(Variant, operator=, (const VectorBuffer&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(void* rhs) | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // Variant& Variant::operator=(const ResourceRef& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRef&in)", AS_METHODPR(Variant, operator=, (const ResourceRef&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const ResourceRefList& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRefList&in)", AS_METHODPR(Variant, operator=, (const ResourceRefList&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const VariantVector& rhs) | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant& Variant::operator=(const StringVector& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(Array<String>@+)", AS_FUNCTION_OBJFIRST(Variant_operatorequals_StringVector), AS_CALL_CDECL_OBJFIRST);
    // Variant& Variant::operator=(const VariantMap& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VariantMap&in)", AS_METHODPR(Variant, operator=, (const VariantMap&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Rect& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Rect&in)", AS_METHODPR(Variant, operator=, (const Rect&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const IntRect& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntRect&in)", AS_METHODPR(Variant, operator=, (const IntRect&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const IntVector2& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntVector2&in)", AS_METHODPR(Variant, operator=, (const IntVector2&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const IntVector3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntVector3&in)", AS_METHODPR(Variant, operator=, (const IntVector3&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(RefCounted* rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(RefCounted@+)", AS_METHODPR(Variant, operator=, (RefCounted*), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Matrix3& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3&in)", AS_METHODPR(Variant, operator=, (const Matrix3&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Matrix3x4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3x4&in)", AS_METHODPR(Variant, operator=, (const Matrix3x4&), Variant&), AS_CALL_THISCALL);
    // Variant& Variant::operator=(const Matrix4& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix4&in)", AS_METHODPR(Variant, operator=, (const Matrix4&), Variant&), AS_CALL_THISCALL);
    // template<class T> Variant& Variant::operator=(const CustomVariantValueImpl<T>& value) | File: ../Core/Variant.h
    // Not registered because template
    // bool Variant::operator==(const Variant& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Variant&in) const", AS_METHODPR(Variant, operator==, (const Variant&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(int rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(int) const", AS_METHODPR(Variant, operator==, (int) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(unsigned rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint) const", AS_METHODPR(Variant, operator==, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(long long rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(int64) const", AS_METHODPR(Variant, operator==, (long long) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(unsigned long long rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint64) const", AS_METHODPR(Variant, operator==, (unsigned long long) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(bool rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(bool) const", AS_METHODPR(Variant, operator==, (bool) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(float rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(float) const", AS_METHODPR(Variant, operator==, (float) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(double rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(double) const", AS_METHODPR(Variant, operator==, (double) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Vector2& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector2&in) const", AS_METHODPR(Variant, operator==, (const Vector2&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Vector3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector3&in) const", AS_METHODPR(Variant, operator==, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Vector4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector4&in) const", AS_METHODPR(Variant, operator==, (const Vector4&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Quaternion& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Quaternion&in) const", AS_METHODPR(Variant, operator==, (const Quaternion&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Color& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Color&in) const", AS_METHODPR(Variant, operator==, (const Color&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const String& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const String&in) const", AS_METHODPR(Variant, operator==, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const PODVector<unsigned char>& rhs) const | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Variant::operator==(const VectorBuffer& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VectorBuffer&in) const", AS_METHODPR(Variant, operator==, (const VectorBuffer&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(void* rhs) const | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // bool Variant::operator==(const ResourceRef& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRef&in) const", AS_METHODPR(Variant, operator==, (const ResourceRef&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const ResourceRefList& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRefList&in) const", AS_METHODPR(Variant, operator==, (const ResourceRefList&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const VariantVector& rhs) const | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Variant::operator==(const StringVector& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(Array<String>@+) const", AS_FUNCTION_OBJFIRST(Variant_operatorequalsequals_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Variant::operator==(const VariantMap& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VariantMap&in) const", AS_METHODPR(Variant, operator==, (const VariantMap&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Rect& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Rect&in) const", AS_METHODPR(Variant, operator==, (const Rect&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const IntRect& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntRect&in) const", AS_METHODPR(Variant, operator==, (const IntRect&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const IntVector2& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntVector2&in) const", AS_METHODPR(Variant, operator==, (const IntVector2&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const IntVector3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntVector3&in) const", AS_METHODPR(Variant, operator==, (const IntVector3&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const StringHash& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const StringHash&in) const", AS_METHODPR(Variant, operator==, (const StringHash&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(RefCounted* rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(RefCounted@+) const", AS_METHODPR(Variant, operator==, (RefCounted*) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Matrix3& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3&in) const", AS_METHODPR(Variant, operator==, (const Matrix3&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Matrix3x4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3x4&in) const", AS_METHODPR(Variant, operator==, (const Matrix3x4&) const, bool), AS_CALL_THISCALL);
    // bool Variant::operator==(const Matrix4& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix4&in) const", AS_METHODPR(Variant, operator==, (const Matrix4&) const, bool), AS_CALL_THISCALL);
    // void Variant::SetBuffer(const void* data, unsigned size) | File: ../Core/Variant.h
    // Error: type "const void*" can not automatically bind
    // template<class T> void Variant::SetCustom(const T& value) | File: ../Core/Variant.h
    // Not registered because template
    // void Variant::SetCustomVariantValue(const CustomVariantValue& value) | File: ../Core/Variant.h
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // String Variant::ToString() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "String ToString() const", AS_METHODPR(Variant, ToString, () const, String), AS_CALL_THISCALL);
    // Variant::Variant(int value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(Variant_Variant_int), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(long long value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int64)", AS_FUNCTION_OBJFIRST(Variant_Variant_longlong), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(Variant_Variant_unsigned), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(unsigned long long value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint64)", AS_FUNCTION_OBJFIRST(Variant_Variant_unsignedlonglong), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringHash& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_StringHash), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(bool value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(Variant_Variant_bool), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(float value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(Variant_Variant_float), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(double value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(Variant_Variant_double), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector2& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Vector2), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Vector4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Vector4), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Quaternion& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Quaternion), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Color& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Color), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_String), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const PODVector<unsigned char>& value) | File: ../Core/Variant.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant::Variant(const VectorBuffer& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_VectorBuffer), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(void* value) | File: ../Core/Variant.h
    // Error: type "void*" can not automatically bind
    // Variant::Variant(const ResourceRef& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_ResourceRef), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const ResourceRefList& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_ResourceRefList), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const VariantVector& value) | File: ../Core/Variant.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant::Variant(const VariantMap& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_VariantMap), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const StringVector& value) | File: ../Core/Variant.h
    // Error: type "const StringVector&" can not automatically bind
    // Variant::Variant(const Rect& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Rect), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntRect& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_IntRect), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector2& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_IntVector2), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const IntVector3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_IntVector3), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(RefCounted* value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", AS_FUNCTION_OBJFIRST(Variant_Variant_RefCounted), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Matrix3), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix3x4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Matrix3x4), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const Matrix4& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Matrix4), AS_CALL_CDECL_OBJFIRST);
    // template<class T> Variant::Variant(const CustomVariantValueImpl<T>& value) | File: ../Core/Variant.h
    // Not registered because template
    // Variant::Variant(const String& type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_String_String), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(VariantType type, const String& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(VariantType, const String&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_VariantType_String), AS_CALL_CDECL_OBJFIRST);
    // Variant::Variant(const char* type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(VariantType type, const char* value) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // Variant::Variant(const Variant& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant&in)", AS_FUNCTION_OBJFIRST(Variant_Variant_Variant), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("Vector2", "Vector2 Abs() const", AS_METHODPR(Vector2, Abs, () const, Vector2), AS_CALL_THISCALL);
    // float Vector2::AbsDotProduct(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", AS_METHODPR(Vector2, AbsDotProduct, (const Vector2&) const, float), AS_CALL_THISCALL);
    // float Vector2::Angle(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float Angle(const Vector2&in) const", AS_METHODPR(Vector2, Angle, (const Vector2&) const, float), AS_CALL_THISCALL);
    // const float* Vector2::Data() const | File: ../Math/Vector2.h
    // Error: type "const float*" can not automatically bind
    // float Vector2::DotProduct(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", AS_METHODPR(Vector2, DotProduct, (const Vector2&) const, float), AS_CALL_THISCALL);
    // bool Vector2::Equals(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool Equals(const Vector2&in) const", AS_METHODPR(Vector2, Equals, (const Vector2&) const, bool), AS_CALL_THISCALL);
    // bool Vector2::IsInf() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool IsInf() const", AS_METHODPR(Vector2, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Vector2::IsNaN() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool IsNaN() const", AS_METHODPR(Vector2, IsNaN, () const, bool), AS_CALL_THISCALL);
    // float Vector2::Length() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float Length() const", AS_METHODPR(Vector2, Length, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_length() const", AS_METHODPR(Vector2, Length, () const, float), AS_CALL_THISCALL);
    // float Vector2::LengthSquared() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float LengthSquared() const", AS_METHODPR(Vector2, LengthSquared, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", AS_METHODPR(Vector2, LengthSquared, () const, float), AS_CALL_THISCALL);
    // Vector2 Vector2::Lerp(const Vector2& rhs, float t) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", AS_METHODPR(Vector2, Lerp, (const Vector2&, float) const, Vector2), AS_CALL_THISCALL);
    // void Vector2::Normalize() | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "void Normalize()", AS_METHODPR(Vector2, Normalize, (), void), AS_CALL_THISCALL);
    // Vector2 Vector2::Normalized() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", AS_METHODPR(Vector2, Normalized, () const, Vector2), AS_CALL_THISCALL);
    // Vector2 Vector2::NormalizedOrDefault(const Vector2& defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 NormalizedOrDefault(const Vector2&in = Vector2::ZERO, float = M_LARGE_EPSILON) const", AS_METHODPR(Vector2, NormalizedOrDefault, (const Vector2&, float) const, Vector2), AS_CALL_THISCALL);
    // Vector2 Vector2::operator*(float rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", AS_METHODPR(Vector2, operator*, (float) const, Vector2), AS_CALL_THISCALL);
    // Vector2 Vector2::operator*(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2&in) const", AS_METHODPR(Vector2, operator*, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // Vector2& Vector2::operator*=(float rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(float)", AS_METHODPR(Vector2, operator*=, (float), Vector2&), AS_CALL_THISCALL);
    // Vector2& Vector2::operator*=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(const Vector2&in)", AS_METHODPR(Vector2, operator*=, (const Vector2&), Vector2&), AS_CALL_THISCALL);
    // Vector2 Vector2::operator+(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2&in) const", AS_METHODPR(Vector2, operator+, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // Vector2& Vector2::operator+=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opAddAssign(const Vector2&in)", AS_METHODPR(Vector2, operator+=, (const Vector2&), Vector2&), AS_CALL_THISCALL);
    // Vector2 Vector2::operator-() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", AS_METHODPR(Vector2, operator-, () const, Vector2), AS_CALL_THISCALL);
    // Vector2 Vector2::operator-(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2&in) const", AS_METHODPR(Vector2, operator-, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // Vector2& Vector2::operator-=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opSubAssign(const Vector2&in)", AS_METHODPR(Vector2, operator-=, (const Vector2&), Vector2&), AS_CALL_THISCALL);
    // Vector2 Vector2::operator/(float rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", AS_METHODPR(Vector2, operator/, (float) const, Vector2), AS_CALL_THISCALL);
    // Vector2 Vector2::operator/(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2&in) const", AS_METHODPR(Vector2, operator/, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // Vector2& Vector2::operator/=(float rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(float)", AS_METHODPR(Vector2, operator/=, (float), Vector2&), AS_CALL_THISCALL);
    // Vector2& Vector2::operator/=(const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(const Vector2&in)", AS_METHODPR(Vector2, operator/=, (const Vector2&), Vector2&), AS_CALL_THISCALL);
    // Vector2& Vector2::operator=(const Vector2& rhs) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2&in)", AS_METHODPR(Vector2, operator=, (const Vector2&), Vector2&), AS_CALL_THISCALL);
    // bool Vector2::operator==(const Vector2& rhs) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2&in) const", AS_METHODPR(Vector2, operator==, (const Vector2&) const, bool), AS_CALL_THISCALL);
    // float Vector2::ProjectOntoAxis(const Vector2& axis) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float ProjectOntoAxis(const Vector2&in) const", AS_METHODPR(Vector2, ProjectOntoAxis, (const Vector2&) const, float), AS_CALL_THISCALL);
    // Vector2 Vector2::ReNormalized(float minLength, float maxLength, const Vector2& defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "Vector2 ReNormalized(float, float, const Vector2&in = Vector2::ZERO, float = M_LARGE_EPSILON) const", AS_METHODPR(Vector2, ReNormalized, (float, float, const Vector2&, float) const, Vector2), AS_CALL_THISCALL);
    // String Vector2::ToString() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "String ToString() const", AS_METHODPR(Vector2, ToString, () const, String), AS_CALL_THISCALL);
    // Vector2::Vector2(const Vector2& vector) noexcept=default | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Vector2_Vector2_Vector2), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector2::Vector2(const IntVector2& vector) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", AS_FUNCTION_OBJFIRST(Vector2_Vector2_IntVector2), AS_CALL_CDECL_OBJFIRST);
    // Vector2::Vector2(float x, float y) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(Vector2_Vector2_float_float), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("Vector3", "Vector3 Abs() const", AS_METHODPR(Vector3, Abs, () const, Vector3), AS_CALL_THISCALL);
    // float Vector3::AbsDotProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", AS_METHODPR(Vector3, AbsDotProduct, (const Vector3&) const, float), AS_CALL_THISCALL);
    // float Vector3::Angle(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float Angle(const Vector3&in) const", AS_METHODPR(Vector3, Angle, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Vector3 Vector3::CrossProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", AS_METHODPR(Vector3, CrossProduct, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // const float* Vector3::Data() const | File: ../Math/Vector3.h
    // Error: type "const float*" can not automatically bind
    // float Vector3::DistanceToPlane(const Vector3& origin, const Vector3& normal) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DistanceToPlane(const Vector3&in, const Vector3&in) const", AS_METHODPR(Vector3, DistanceToPlane, (const Vector3&, const Vector3&) const, float), AS_CALL_THISCALL);
    // float Vector3::DistanceToPoint(const Vector3& point) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DistanceToPoint(const Vector3&in) const", AS_METHODPR(Vector3, DistanceToPoint, (const Vector3&) const, float), AS_CALL_THISCALL);
    // float Vector3::DotProduct(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", AS_METHODPR(Vector3, DotProduct, (const Vector3&) const, float), AS_CALL_THISCALL);
    // bool Vector3::Equals(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool Equals(const Vector3&in) const", AS_METHODPR(Vector3, Equals, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Vector3::IsInf() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool IsInf() const", AS_METHODPR(Vector3, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Vector3::IsNaN() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool IsNaN() const", AS_METHODPR(Vector3, IsNaN, () const, bool), AS_CALL_THISCALL);
    // float Vector3::Length() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float Length() const", AS_METHODPR(Vector3, Length, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_length() const", AS_METHODPR(Vector3, Length, () const, float), AS_CALL_THISCALL);
    // float Vector3::LengthSquared() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float LengthSquared() const", AS_METHODPR(Vector3, LengthSquared, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_lengthSquared() const", AS_METHODPR(Vector3, LengthSquared, () const, float), AS_CALL_THISCALL);
    // Vector3 Vector3::Lerp(const Vector3& rhs, float t) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", AS_METHODPR(Vector3, Lerp, (const Vector3&, float) const, Vector3), AS_CALL_THISCALL);
    // void Vector3::Normalize() | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "void Normalize()", AS_METHODPR(Vector3, Normalize, (), void), AS_CALL_THISCALL);
    // Vector3 Vector3::Normalized() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Normalized() const", AS_METHODPR(Vector3, Normalized, () const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::NormalizedOrDefault(const Vector3& defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 NormalizedOrDefault(const Vector3&in = Vector3::ZERO, float = M_LARGE_EPSILON) const", AS_METHODPR(Vector3, NormalizedOrDefault, (const Vector3&, float) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::operator*(float rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", AS_METHODPR(Vector3, operator*, (float) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::operator*(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3&in) const", AS_METHODPR(Vector3, operator*, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3& Vector3::operator*=(float rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(float)", AS_METHODPR(Vector3, operator*=, (float), Vector3&), AS_CALL_THISCALL);
    // Vector3& Vector3::operator*=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3&in)", AS_METHODPR(Vector3, operator*=, (const Vector3&), Vector3&), AS_CALL_THISCALL);
    // Vector3 Vector3::operator+(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3&in) const", AS_METHODPR(Vector3, operator+, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3& Vector3::operator+=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3&in)", AS_METHODPR(Vector3, operator+=, (const Vector3&), Vector3&), AS_CALL_THISCALL);
    // Vector3 Vector3::operator-() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", AS_METHODPR(Vector3, operator-, () const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::operator-(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3&in) const", AS_METHODPR(Vector3, operator-, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3& Vector3::operator-=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3&in)", AS_METHODPR(Vector3, operator-=, (const Vector3&), Vector3&), AS_CALL_THISCALL);
    // Vector3 Vector3::operator/(float rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", AS_METHODPR(Vector3, operator/, (float) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::operator/(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3&in) const", AS_METHODPR(Vector3, operator/, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3& Vector3::operator/=(float rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(float)", AS_METHODPR(Vector3, operator/=, (float), Vector3&), AS_CALL_THISCALL);
    // Vector3& Vector3::operator/=(const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3&in)", AS_METHODPR(Vector3, operator/=, (const Vector3&), Vector3&), AS_CALL_THISCALL);
    // Vector3& Vector3::operator=(const Vector3& rhs) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3&in)", AS_METHODPR(Vector3, operator=, (const Vector3&), Vector3&), AS_CALL_THISCALL);
    // bool Vector3::operator==(const Vector3& rhs) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3&in) const", AS_METHODPR(Vector3, operator==, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // Vector3 Vector3::Orthogonalize(const Vector3& axis) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 Orthogonalize(const Vector3&in) const", AS_METHODPR(Vector3, Orthogonalize, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // float Vector3::ProjectOntoAxis(const Vector3& axis) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float ProjectOntoAxis(const Vector3&in) const", AS_METHODPR(Vector3, ProjectOntoAxis, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Vector3 Vector3::ProjectOntoLine(const Vector3& from, const Vector3& to, bool clamped=false) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoLine(const Vector3&in, const Vector3&in, bool = false) const", AS_METHODPR(Vector3, ProjectOntoLine, (const Vector3&, const Vector3&, bool) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::ProjectOntoPlane(const Vector3& origin, const Vector3& normal) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoPlane(const Vector3&in, const Vector3&in) const", AS_METHODPR(Vector3, ProjectOntoPlane, (const Vector3&, const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Vector3::ReNormalized(float minLength, float maxLength, const Vector3& defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "Vector3 ReNormalized(float, float, const Vector3&in = Vector3::ZERO, float = M_LARGE_EPSILON) const", AS_METHODPR(Vector3, ReNormalized, (float, float, const Vector3&, float) const, Vector3), AS_CALL_THISCALL);
    // unsigned Vector3::ToHash() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "uint ToHash() const", AS_METHODPR(Vector3, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String Vector3::ToString() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "String ToString() const", AS_METHODPR(Vector3, ToString, () const, String), AS_CALL_THISCALL);
    // Vector3::Vector3(const Vector3& vector) noexcept=default | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector2& vector, float z) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_Vector2_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const Vector2& vector) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_Vector2), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector3::Vector3(const IntVector3& vector) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_IntVector3), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y, float z) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(Vector3_Vector3_float_float), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("Vector4", "Vector4 Abs() const", AS_METHODPR(Vector4, Abs, () const, Vector4), AS_CALL_THISCALL);
    // float Vector4::AbsDotProduct(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float AbsDotProduct(const Vector4&in) const", AS_METHODPR(Vector4, AbsDotProduct, (const Vector4&) const, float), AS_CALL_THISCALL);
    // const float* Vector4::Data() const | File: ../Math/Vector4.h
    // Error: type "const float*" can not automatically bind
    // float Vector4::DotProduct(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float DotProduct(const Vector4&in) const", AS_METHODPR(Vector4, DotProduct, (const Vector4&) const, float), AS_CALL_THISCALL);
    // bool Vector4::Equals(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool Equals(const Vector4&in) const", AS_METHODPR(Vector4, Equals, (const Vector4&) const, bool), AS_CALL_THISCALL);
    // bool Vector4::IsInf() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool IsInf() const", AS_METHODPR(Vector4, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Vector4::IsNaN() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool IsNaN() const", AS_METHODPR(Vector4, IsNaN, () const, bool), AS_CALL_THISCALL);
    // Vector4 Vector4::Lerp(const Vector4& rhs, float t) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", AS_METHODPR(Vector4, Lerp, (const Vector4&, float) const, Vector4), AS_CALL_THISCALL);
    // explicit Vector4::operator Vector2() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector2 opConv() const", AS_METHODPR(Vector4, operator Vector2, () const, Vector2), AS_CALL_THISCALL);
    // explicit Vector4::operator Vector3() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector3 opConv() const", AS_METHODPR(Vector4, operator Vector3, () const, Vector3), AS_CALL_THISCALL);
    // Vector4 Vector4::operator*(float rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", AS_METHODPR(Vector4, operator*, (float) const, Vector4), AS_CALL_THISCALL);
    // Vector4 Vector4::operator*(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4&in) const", AS_METHODPR(Vector4, operator*, (const Vector4&) const, Vector4), AS_CALL_THISCALL);
    // Vector4& Vector4::operator*=(float rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(float)", AS_METHODPR(Vector4, operator*=, (float), Vector4&), AS_CALL_THISCALL);
    // Vector4& Vector4::operator*=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(const Vector4&in)", AS_METHODPR(Vector4, operator*=, (const Vector4&), Vector4&), AS_CALL_THISCALL);
    // Vector4 Vector4::operator+(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4&in) const", AS_METHODPR(Vector4, operator+, (const Vector4&) const, Vector4), AS_CALL_THISCALL);
    // Vector4& Vector4::operator+=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opAddAssign(const Vector4&in)", AS_METHODPR(Vector4, operator+=, (const Vector4&), Vector4&), AS_CALL_THISCALL);
    // Vector4 Vector4::operator-() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", AS_METHODPR(Vector4, operator-, () const, Vector4), AS_CALL_THISCALL);
    // Vector4 Vector4::operator-(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4&in) const", AS_METHODPR(Vector4, operator-, (const Vector4&) const, Vector4), AS_CALL_THISCALL);
    // Vector4& Vector4::operator-=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opSubAssign(const Vector4&in)", AS_METHODPR(Vector4, operator-=, (const Vector4&), Vector4&), AS_CALL_THISCALL);
    // Vector4 Vector4::operator/(float rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", AS_METHODPR(Vector4, operator/, (float) const, Vector4), AS_CALL_THISCALL);
    // Vector4 Vector4::operator/(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4&in) const", AS_METHODPR(Vector4, operator/, (const Vector4&) const, Vector4), AS_CALL_THISCALL);
    // Vector4& Vector4::operator/=(float rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(float)", AS_METHODPR(Vector4, operator/=, (float), Vector4&), AS_CALL_THISCALL);
    // Vector4& Vector4::operator/=(const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(const Vector4&in)", AS_METHODPR(Vector4, operator/=, (const Vector4&), Vector4&), AS_CALL_THISCALL);
    // Vector4& Vector4::operator=(const Vector4& rhs) noexcept=default | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "Vector4& opAssign(const Vector4&in)", AS_METHODPR(Vector4, operator=, (const Vector4&), Vector4&), AS_CALL_THISCALL);
    // bool Vector4::operator==(const Vector4& rhs) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "bool opEquals(const Vector4&in) const", AS_METHODPR(Vector4, operator==, (const Vector4&) const, bool), AS_CALL_THISCALL);
    // float Vector4::operator[](unsigned index) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float opIndex(uint) const", AS_METHODPR(Vector4, operator[], (unsigned) const, float), AS_CALL_THISCALL);
    // float& Vector4::operator[](unsigned index) | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float& opIndex(uint)", AS_METHODPR(Vector4, operator[], (unsigned), float&), AS_CALL_THISCALL);
    // float Vector4::ProjectOntoAxis(const Vector3& axis) const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float ProjectOntoAxis(const Vector3&in) const", AS_METHODPR(Vector4, ProjectOntoAxis, (const Vector3&) const, float), AS_CALL_THISCALL);
    // unsigned Vector4::ToHash() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "uint ToHash() const", AS_METHODPR(Vector4, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String Vector4::ToString() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "String ToString() const", AS_METHODPR(Vector4, ToString, () const, String), AS_CALL_THISCALL);
    // Vector4::Vector4(const Vector4& vector) noexcept=default | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Vector4_Vector4_Vector4), AS_CALL_CDECL_OBJFIRST);
    // Vector4::Vector4(const Vector3& vector, float w) noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", AS_FUNCTION_OBJFIRST(Vector4_Vector4_Vector3_float), AS_CALL_CDECL_OBJFIRST);
    // Vector4::Vector4(float x, float y, float z, float w) noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Vector4_Vector4_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h
    // Error: type "const float*" can not automatically bind
#ifdef REGISTER_MANUAL_PART_Vector4
    REGISTER_MANUAL_PART_Vector4(Vector4, "Vector4")
#endif

    // void VectorBase::Swap(VectorBase& rhs) | File: ../Container/VectorBase.h
    engine->RegisterObjectMethod("VectorBase", "void Swap(VectorBase&)", AS_METHODPR(VectorBase, Swap, (VectorBase&), void), AS_CALL_THISCALL);
    // VectorBase& VectorBase::operator=(const VectorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VectorBase>(engine, "VectorBase");
#ifdef REGISTER_MANUAL_PART_VectorBase
    REGISTER_MANUAL_PART_VectorBase(VectorBase, "VectorBase")
#endif

    // void VectorBuffer::Clear() | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void Clear()", AS_METHODPR(VectorBuffer, Clear, (), void), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& VectorBuffer::GetBuffer() const | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetChecksum()", AS_METHODPR(VectorBuffer, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_checksum()", AS_METHODPR(VectorBuffer, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // const unsigned char* VectorBuffer::GetData() const | File: ../IO/VectorBuffer.h
    // Error: type "const unsigned char*" can not automatically bind
    // unsigned char* VectorBuffer::GetModifiableData() | File: ../IO/VectorBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("VectorBuffer", "const String& GetName() const", AS_METHODPR(VectorBuffer, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "const String& get_name() const", AS_METHODPR(VectorBuffer, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetPosition() const", AS_METHODPR(VectorBuffer, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_position() const", AS_METHODPR(VectorBuffer, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint GetSize() const", AS_METHODPR(VectorBuffer, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint get_size() const", AS_METHODPR(VectorBuffer, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool IsEof() const", AS_METHODPR(VectorBuffer, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "bool get_eof() const", AS_METHODPR(VectorBuffer, IsEof, () const, bool), AS_CALL_THISCALL);
    // unsigned VectorBuffer::Read(void* dest, unsigned size) override | File: ../IO/VectorBuffer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool ReadBool()", AS_METHODPR(VectorBuffer, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "BoundingBox ReadBoundingBox()", AS_METHODPR(VectorBuffer, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int8 ReadByte()", AS_METHODPR(VectorBuffer, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Color ReadColor()", AS_METHODPR(VectorBuffer, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "double ReadDouble()", AS_METHODPR(VectorBuffer, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadFileID()", AS_METHODPR(VectorBuffer, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "float ReadFloat()", AS_METHODPR(VectorBuffer, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int ReadInt()", AS_METHODPR(VectorBuffer, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int64 ReadInt64()", AS_METHODPR(VectorBuffer, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntRect ReadIntRect()", AS_METHODPR(VectorBuffer, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntVector2 ReadIntVector2()", AS_METHODPR(VectorBuffer, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "IntVector3 ReadIntVector3()", AS_METHODPR(VectorBuffer, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadLine()", AS_METHODPR(VectorBuffer, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix3 ReadMatrix3()", AS_METHODPR(VectorBuffer, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(VectorBuffer, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Matrix4 ReadMatrix4()", AS_METHODPR(VectorBuffer, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadNetID()", AS_METHODPR(VectorBuffer, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Quaternion ReadPackedQuaternion()", AS_METHODPR(VectorBuffer, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector3 ReadPackedVector3(float)", AS_METHODPR(VectorBuffer, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Quaternion ReadQuaternion()", AS_METHODPR(VectorBuffer, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Rect ReadRect()", AS_METHODPR(VectorBuffer, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "ResourceRef ReadResourceRef()", AS_METHODPR(VectorBuffer, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "ResourceRefList ReadResourceRefList()", AS_METHODPR(VectorBuffer, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "int16 ReadShort()", AS_METHODPR(VectorBuffer, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "String ReadString()", AS_METHODPR(VectorBuffer, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "StringHash ReadStringHash()", AS_METHODPR(VectorBuffer, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(VectorBuffer_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint8 ReadUByte()", AS_METHODPR(VectorBuffer, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadUInt()", AS_METHODPR(VectorBuffer, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint64 ReadUInt64()", AS_METHODPR(VectorBuffer, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint16 ReadUShort()", AS_METHODPR(VectorBuffer, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Variant ReadVariant()", AS_METHODPR(VectorBuffer, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Variant ReadVariant(VariantType)", AS_METHODPR(VectorBuffer, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "VariantMap ReadVariantMap()", AS_METHODPR(VectorBuffer, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector2 ReadVector2()", AS_METHODPR(VectorBuffer, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector3 ReadVector3()", AS_METHODPR(VectorBuffer, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "Vector4 ReadVector4()", AS_METHODPR(VectorBuffer, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint ReadVLE()", AS_METHODPR(VectorBuffer, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // void VectorBuffer::Resize(unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void Resize(uint)", AS_METHODPR(VectorBuffer, Resize, (unsigned), void), AS_CALL_THISCALL);
    // unsigned VectorBuffer::Seek(unsigned position) override | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint Seek(uint)", AS_METHODPR(VectorBuffer, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint SeekRelative(int)", AS_METHODPR(VectorBuffer, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // void VectorBuffer::SetData(const PODVector<unsigned char>& data) | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void VectorBuffer::SetData(const void* data, unsigned size) | File: ../IO/VectorBuffer.h
    // Error: type "const void*" can not automatically bind
    // void VectorBuffer::SetData(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectMethod("VectorBuffer", "void SetData(Deserializer&, uint)", AS_METHODPR(VectorBuffer, SetData, (Deserializer&, unsigned), void), AS_CALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("VectorBuffer", "void SetName(const String&in)", AS_METHODPR(VectorBuffer, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void set_name(const String&in)", AS_METHODPR(VectorBuffer, SetName, (const String&), void), AS_CALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("VectorBuffer", "uint Tell() const", AS_METHODPR(VectorBuffer, Tell, () const, unsigned), AS_CALL_THISCALL);
    // explicit VectorBuffer::VectorBuffer(const PODVector<unsigned char>& data) | File: ../IO/VectorBuffer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // VectorBuffer::VectorBuffer(const void* data, unsigned size) | File: ../IO/VectorBuffer.h
    // Error: type "void*" can not automatically bind
    // VectorBuffer::VectorBuffer(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer&, uint)", AS_FUNCTION_OBJFIRST(VectorBuffer_VectorBuffer_Deserializer_unsigned), AS_CALL_CDECL_OBJFIRST);
    // unsigned VectorBuffer::Write(const void* data, unsigned size) override | File: ../IO/VectorBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteBool(bool)", AS_METHODPR(VectorBuffer, WriteBool, (bool), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteBoundingBox(const BoundingBox&in)", AS_METHODPR(VectorBuffer, WriteBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteByte(int8)", AS_METHODPR(VectorBuffer, WriteByte, (signed char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteColor(const Color&in)", AS_METHODPR(VectorBuffer, WriteColor, (const Color&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteDouble(double)", AS_METHODPR(VectorBuffer, WriteDouble, (double), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteFileID(const String&in)", AS_METHODPR(VectorBuffer, WriteFileID, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteFloat(float)", AS_METHODPR(VectorBuffer, WriteFloat, (float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteInt(int)", AS_METHODPR(VectorBuffer, WriteInt, (int), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteInt64(int64)", AS_METHODPR(VectorBuffer, WriteInt64, (long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntRect(const IntRect&in)", AS_METHODPR(VectorBuffer, WriteIntRect, (const IntRect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntVector2(const IntVector2&in)", AS_METHODPR(VectorBuffer, WriteIntVector2, (const IntVector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteIntVector3(const IntVector3&in)", AS_METHODPR(VectorBuffer, WriteIntVector3, (const IntVector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteLine(const String&in)", AS_METHODPR(VectorBuffer, WriteLine, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix3(const Matrix3&in)", AS_METHODPR(VectorBuffer, WriteMatrix3, (const Matrix3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix3x4(const Matrix3x4&in)", AS_METHODPR(VectorBuffer, WriteMatrix3x4, (const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteMatrix4(const Matrix4&in)", AS_METHODPR(VectorBuffer, WriteMatrix4, (const Matrix4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteNetID(uint)", AS_METHODPR(VectorBuffer, WriteNetID, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WritePackedQuaternion(const Quaternion&in)", AS_METHODPR(VectorBuffer, WritePackedQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WritePackedVector3(const Vector3&in, float)", AS_METHODPR(VectorBuffer, WritePackedVector3, (const Vector3&, float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteQuaternion(const Quaternion&in)", AS_METHODPR(VectorBuffer, WriteQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteRect(const Rect&in)", AS_METHODPR(VectorBuffer, WriteRect, (const Rect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteResourceRef(const ResourceRef&in)", AS_METHODPR(VectorBuffer, WriteResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteResourceRefList(const ResourceRefList&in)", AS_METHODPR(VectorBuffer, WriteResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteShort(int16)", AS_METHODPR(VectorBuffer, WriteShort, (short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteString(const String&in)", AS_METHODPR(VectorBuffer, WriteString, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteStringHash(const StringHash&in)", AS_METHODPR(VectorBuffer, WriteStringHash, (const StringHash&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(VectorBuffer_WriteStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUByte(uint8)", AS_METHODPR(VectorBuffer, WriteUByte, (unsigned char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUInt(uint)", AS_METHODPR(VectorBuffer, WriteUInt, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUInt64(uint64)", AS_METHODPR(VectorBuffer, WriteUInt64, (unsigned long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteUShort(uint16)", AS_METHODPR(VectorBuffer, WriteUShort, (unsigned short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariant(const Variant&in)", AS_METHODPR(VectorBuffer, WriteVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariantData(const Variant&in)", AS_METHODPR(VectorBuffer, WriteVariantData, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVariantMap(const VariantMap&in)", AS_METHODPR(VectorBuffer, WriteVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector2(const Vector2&in)", AS_METHODPR(VectorBuffer, WriteVector2, (const Vector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector3(const Vector3&in)", AS_METHODPR(VectorBuffer, WriteVector3, (const Vector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVector4(const Vector4&in)", AS_METHODPR(VectorBuffer, WriteVector4, (const Vector4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("VectorBuffer", "bool WriteVLE(uint)", AS_METHODPR(VectorBuffer, WriteVLE, (unsigned), bool), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(VertexBuffer, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "void ClearDataLost()", AS_METHODPR(VertexBuffer, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool GetBlockEvents() const", AS_METHODPR(VertexBuffer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // unsigned long long VertexBuffer::GetBufferHash(unsigned streamIndex) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint64 GetBufferHash(uint)", AS_METHODPR(VertexBuffer, GetBufferHash, (unsigned), unsigned long long), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const String& GetCategory() const", AS_METHODPR(VertexBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const String& get_category() const", AS_METHODPR(VertexBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const VertexElement* VertexBuffer::GetElement(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // static const VertexElement* VertexBuffer::GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    // Error: type "const VertexElement*" can not automatically bind
    // VertexMaskFlags VertexBuffer::GetElementMask() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "VertexMaskFlags GetElementMask() const", AS_METHODPR(VertexBuffer, GetElementMask, () const, VertexMaskFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "VertexMaskFlags get_elementMask() const", AS_METHODPR(VertexBuffer, GetElementMask, () const, VertexMaskFlags), AS_CALL_THISCALL);
    // unsigned VertexBuffer::GetElementOffset(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetElementOffset(VertexElementSemantic, uint8 = 0) const", AS_METHODPR(VertexBuffer, GetElementOffset, (VertexElementSemantic, unsigned char) const, unsigned), AS_CALL_THISCALL);
    // unsigned VertexBuffer::GetElementOffset(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetElementOffset(VertexElementType, VertexElementSemantic, uint8 = 0) const", AS_METHODPR(VertexBuffer, GetElementOffset, (VertexElementType, VertexElementSemantic, unsigned char) const, unsigned), AS_CALL_THISCALL);
    // static unsigned VertexBuffer::GetElementOffset(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetElementOffset(Array<VertexElement>@+, VertexElementType, VertexElementSemantic, uint8 = 0)", AS_FUNCTION(VertexBuffer_GetElementOffset_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const PODVector<VertexElement>& VertexBuffer::GetElements() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "Array<VertexElement>@ GetElements() const", AS_FUNCTION_OBJFIRST(VertexBuffer_GetElements_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("VertexBuffer", "Array<VertexElement>@ get_elements() const", AS_FUNCTION_OBJFIRST(VertexBuffer_GetElements_void), AS_CALL_CDECL_OBJFIRST);
    // static PODVector<VertexElement> VertexBuffer::GetElements(unsigned elementMask) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("Array<VertexElement>@ GetElements(uint)", AS_FUNCTION(VertexBuffer_GetElements_unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "VariantMap& GetEventDataMap() const", AS_METHODPR(VertexBuffer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "Object@+ GetEventSender() const", AS_METHODPR(VertexBuffer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(VertexBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(VertexBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(VertexBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const VariantMap& get_globalVars() const", AS_METHODPR(VertexBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetGPUObjectName() const", AS_METHODPR(VertexBuffer, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "Graphics@+ GetGraphics() const", AS_METHODPR(VertexBuffer, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // unsigned char* VertexBuffer::GetShadowData() const | File: ../Graphics/VertexBuffer.h
    // Error: type "unsigned char*" can not automatically bind
    // SharedArrayPtr<unsigned char> VertexBuffer::GetShadowDataShared() const | File: ../Graphics/VertexBuffer.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(VertexBuffer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "StringHash GetType() const", AS_METHODPR(VertexBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "StringHash get_type() const", AS_METHODPR(VertexBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "const String& GetTypeName() const", AS_METHODPR(VertexBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "const String& get_typeName() const", AS_METHODPR(VertexBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned VertexBuffer::GetVertexCount() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetVertexCount() const", AS_METHODPR(VertexBuffer, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "uint get_vertexCount() const", AS_METHODPR(VertexBuffer, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    // unsigned VertexBuffer::GetVertexSize() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "uint GetVertexSize() const", AS_METHODPR(VertexBuffer, GetVertexSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "uint get_vertexSize() const", AS_METHODPR(VertexBuffer, GetVertexSize, () const, unsigned), AS_CALL_THISCALL);
    // static unsigned VertexBuffer::GetVertexSize(const PODVector<VertexElement>& elements) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetVertexSize(Array<VertexElement>@+)", AS_FUNCTION(VertexBuffer_GetVertexSize_PODVectorVertexElement), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned VertexBuffer::GetVertexSize(unsigned elementMask) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("uint GetVertexSize(uint)", AS_FUNCTIONPR(VertexBuffer::GetVertexSize, (unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool VertexBuffer::HasElement(VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasElement(VertexElementSemantic, uint8 = 0) const", AS_METHODPR(VertexBuffer, HasElement, (VertexElementSemantic, unsigned char) const, bool), AS_CALL_THISCALL);
    // bool VertexBuffer::HasElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasElement(VertexElementType, VertexElementSemantic, uint8 = 0) const", AS_METHODPR(VertexBuffer, HasElement, (VertexElementType, VertexElementSemantic, unsigned char) const, bool), AS_CALL_THISCALL);
    // static bool VertexBuffer::HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index=0) | File: ../Graphics/VertexBuffer.h
    engine->SetDefaultNamespace("VertexBuffer");
    engine->RegisterGlobalFunction("bool HasElement(Array<VertexElement>@+, VertexElementType, VertexElementSemantic, uint8 = 0)", AS_FUNCTION(VertexBuffer_HasElement_PODVectorVertexElement_VertexElementType_VertexElementSemantic_unsignedchar), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasEventHandlers() const", AS_METHODPR(VertexBuffer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasPendingData() const", AS_METHODPR(VertexBuffer, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(VertexBuffer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(VertexBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsDataLost() const", AS_METHODPR(VertexBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_dataLost() const", AS_METHODPR(VertexBuffer, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool VertexBuffer::IsDynamic() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsDynamic() const", AS_METHODPR(VertexBuffer, IsDynamic, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_dynamic() const", AS_METHODPR(VertexBuffer, IsDynamic, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(VertexBuffer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool VertexBuffer::IsLocked() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsLocked() const", AS_METHODPR(VertexBuffer, IsLocked, () const, bool), AS_CALL_THISCALL);
    // bool VertexBuffer::IsShadowed() const | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool IsShadowed() const", AS_METHODPR(VertexBuffer, IsShadowed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "bool get_shadowed() const", AS_METHODPR(VertexBuffer, IsShadowed, () const, bool), AS_CALL_THISCALL);
    // void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
    // Error: type "void*" can not automatically bind
    // void VertexBuffer::OnDeviceLost() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnDeviceLost()", AS_METHODPR(VertexBuffer, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void VertexBuffer::OnDeviceReset() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnDeviceReset()", AS_METHODPR(VertexBuffer, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(VertexBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("VertexBuffer", "int Refs() const", AS_METHODPR(VertexBuffer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "int get_refs() const", AS_METHODPR(VertexBuffer, Refs, () const, int), AS_CALL_THISCALL);
    // void VertexBuffer::Release() override | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void Release()", AS_METHODPR(VertexBuffer, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(VertexBuffer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SendEvent(StringHash)", AS_METHODPR(VertexBuffer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(VertexBuffer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetBlockEvents(bool)", AS_METHODPR(VertexBuffer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // bool VertexBuffer::SetData(const void* data) | File: ../Graphics/VertexBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
    // Error: type "const void*" can not automatically bind
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(VertexBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(VertexBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void VertexBuffer::SetShadowed(bool enable) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void SetShadowed(bool)", AS_METHODPR(VertexBuffer, SetShadowed, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "void set_shadowed(bool)", AS_METHODPR(VertexBuffer, SetShadowed, (bool), void), AS_CALL_THISCALL);
    // bool VertexBuffer::SetSize(unsigned vertexCount, const PODVector<VertexElement>& elements, bool dynamic=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool SetSize(uint, Array<VertexElement>@+, bool = false)", AS_FUNCTION_OBJFIRST(VertexBuffer_SetSize_unsigned_PODVectorVertexElement_bool), AS_CALL_CDECL_OBJFIRST);
    // bool VertexBuffer::SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "bool SetSize(uint, uint, bool = false)", AS_METHODPR(VertexBuffer, SetSize, (unsigned, unsigned, bool), bool), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void VertexBuffer::Unlock() | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectMethod("VertexBuffer", "void Unlock()", AS_METHODPR(VertexBuffer, Unlock, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromAllEvents()", AS_METHODPR(VertexBuffer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(VertexBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(VertexBuffer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(VertexBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("VertexBuffer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(VertexBuffer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // static void VertexBuffer::UpdateOffsets(PODVector<VertexElement>& elements) | File: ../Graphics/VertexBuffer.h
    // Error: type "PODVector<VertexElement>&" can not automatically bind
    // explicit VertexBuffer::VertexBuffer(Context* context, bool forceHeadless=false) | File: ../Graphics/VertexBuffer.h
    engine->RegisterObjectBehaviour("VertexBuffer", asBEHAVE_FACTORY, "VertexBuffer@+ f(bool = false)", AS_FUNCTION(VertexBuffer_VertexBuffer_Context_bool), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("VertexBuffer", "int WeakRefs() const", AS_METHODPR(VertexBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("VertexBuffer", "int get_weakRefs() const", AS_METHODPR(VertexBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("View", asBEHAVE_ADDREF, "void f()", AS_METHODPR(View, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool View::Define(RenderSurface* renderTarget, Viewport* viewport) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "bool Define(RenderSurface@+, Viewport@+)", AS_METHODPR(View, Define, (RenderSurface*, Viewport*), bool), AS_CALL_THISCALL);
    // void View::DrawFullscreenQuad(bool setIdentityProjection=false) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void DrawFullscreenQuad(bool = false)", AS_METHODPR(View, DrawFullscreenQuad, (bool), void), AS_CALL_THISCALL);
    // Texture* View::FindNamedTexture(const String& name, bool isRenderTarget, bool isVolumeMap=false) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Texture@+ FindNamedTexture(const String&in, bool, bool = false)", AS_METHODPR(View, FindNamedTexture, (const String&, bool, bool), Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool GetBlockEvents() const", AS_METHODPR(View, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // Camera* View::GetCamera() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Camera@+ GetCamera() const", AS_METHODPR(View, GetCamera, () const, Camera*), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const String& GetCategory() const", AS_METHODPR(View, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "const String& get_category() const", AS_METHODPR(View, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Camera* View::GetCullCamera() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Camera@+ GetCullCamera() const", AS_METHODPR(View, GetCullCamera, () const, Camera*), AS_CALL_THISCALL);
    // bool View::GetDrawDebug() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "bool GetDrawDebug() const", AS_METHODPR(View, GetDrawDebug, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "VariantMap& GetEventDataMap() const", AS_METHODPR(View, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "Object@+ GetEventSender() const", AS_METHODPR(View, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const FrameInfo& View::GetFrameInfo() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const FrameInfo& GetFrameInfo() const", AS_METHODPR(View, GetFrameInfo, () const, const FrameInfo&), AS_CALL_THISCALL);
    // const PODVector<Drawable*>& View::GetGeometries() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Drawable@>@ GetGeometries() const", AS_FUNCTION_OBJFIRST(View_GetGeometries_void), AS_CALL_CDECL_OBJFIRST);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(View, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(View, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const VariantMap& GetGlobalVars() const", AS_METHODPR(View, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "const VariantMap& get_globalVars() const", AS_METHODPR(View, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Graphics* View::GetGraphics() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Graphics@+ GetGraphics() const", AS_METHODPR(View, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // const Vector<LightBatchQueue>& View::GetLightQueues() const | File: ../Graphics/View.h
    // Error: type "const Vector<LightBatchQueue>&" can not automatically bind
    // const PODVector<Light*>& View::GetLights() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(View_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned View::GetNumActiveOccluders() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "uint GetNumActiveOccluders() const", AS_METHODPR(View, GetNumActiveOccluders, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Drawable*>& View::GetOccluders() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Array<Drawable@>@ GetOccluders() const", AS_FUNCTION_OBJFIRST(View_GetOccluders_void), AS_CALL_CDECL_OBJFIRST);
    // OcclusionBuffer* View::GetOcclusionBuffer() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "OcclusionBuffer@+ GetOcclusionBuffer() const", AS_METHODPR(View, GetOcclusionBuffer, () const, OcclusionBuffer*), AS_CALL_THISCALL);
    // Octree* View::GetOctree() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Octree@+ GetOctree() const", AS_METHODPR(View, GetOctree, () const, Octree*), AS_CALL_THISCALL);
    // Renderer* View::GetRenderer() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Renderer@+ GetRenderer() const", AS_METHODPR(View, GetRenderer, () const, Renderer*), AS_CALL_THISCALL);
    // RenderSurface* View::GetRenderTarget() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "RenderSurface@+ GetRenderTarget() const", AS_METHODPR(View, GetRenderTarget, () const, RenderSurface*), AS_CALL_THISCALL);
    // Scene* View::GetScene() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "Scene@+ GetScene() const", AS_METHODPR(View, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // View* View::GetSourceView() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "View@+ GetSourceView() const", AS_METHODPR(View, GetSourceView, () const, View*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(View, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "StringHash GetType() const", AS_METHODPR(View, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "StringHash get_type() const", AS_METHODPR(View, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "const String& GetTypeName() const", AS_METHODPR(View, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "const String& get_typeName() const", AS_METHODPR(View, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const IntRect& View::GetViewRect() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const IntRect& GetViewRect() const", AS_METHODPR(View, GetViewRect, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntVector2& View::GetViewSize() const | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "const IntVector2& GetViewSize() const", AS_METHODPR(View, GetViewSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasEventHandlers() const", AS_METHODPR(View, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(View, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(View, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "bool IsInstanceOf(StringHash) const", AS_METHODPR(View, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(View, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View", "int Refs() const", AS_METHODPR(View, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "int get_refs() const", AS_METHODPR(View, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View", asBEHAVE_RELEASE, "void f()", AS_METHODPR(View, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void View::Render() | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void Render()", AS_METHODPR(View, Render, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SendEvent(StringHash)", AS_METHODPR(View, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(View, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SetBlockEvents(bool)", AS_METHODPR(View, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void View::SetCameraShaderParameters(Camera* camera) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetCameraShaderParameters(Camera@+)", AS_METHODPR(View, SetCameraShaderParameters, (Camera*), void), AS_CALL_THISCALL);
    // void View::SetCommandShaderParameters(const RenderPathCommand& command) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetCommandShaderParameters(const RenderPathCommand&in)", AS_METHODPR(View, SetCommandShaderParameters, (const RenderPathCommand&), void), AS_CALL_THISCALL);
    // void View::SetGBufferShaderParameters(const IntVector2& texSize, const IntRect& viewRect) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetGBufferShaderParameters(const IntVector2&in, const IntRect&in)", AS_METHODPR(View, SetGBufferShaderParameters, (const IntVector2&, const IntRect&), void), AS_CALL_THISCALL);
    // void View::SetGlobalShaderParameters() | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void SetGlobalShaderParameters()", AS_METHODPR(View, SetGlobalShaderParameters, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(View, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(View, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromAllEvents()", AS_METHODPR(View, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(View_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(View, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(View, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(View, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void View::Update(const FrameInfo& frame) | File: ../Graphics/View.h
    engine->RegisterObjectMethod("View", "void Update(const FrameInfo&in)", AS_METHODPR(View, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // explicit View::View(Context* context) | File: ../Graphics/View.h
    engine->RegisterObjectBehaviour("View", asBEHAVE_FACTORY, "View@+ f()", AS_FUNCTION(View_View_Context), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View", "int WeakRefs() const", AS_METHODPR(View, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View", "int get_weakRefs() const", AS_METHODPR(View, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("View3D", "void AddChild(UIElement@+)", AS_METHODPR(View3D, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(View3D, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTag(const String&in)", AS_METHODPR(View3D, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(View3D, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(View3D_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void AdjustScissor(IntRect&)", AS_METHODPR(View3D, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void AllocateNetworkState()", AS_METHODPR(View3D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void ApplyAttributes()", AS_METHODPR(View3D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void BringToFront()", AS_METHODPR(View3D, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(View3D, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void DisableLayoutUpdate()", AS_METHODPR(View3D, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(View3D, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void EnableLayoutUpdate()", AS_METHODPR(View3D, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(View3D, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint FindChild(UIElement@+) const", AS_METHODPR(View3D, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool GetAnimationEnabled() const", AS_METHODPR(View3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_animationEnabled() const", AS_METHODPR(View3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const String& GetAppliedStyle() const", AS_METHODPR(View3D, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_style() const", AS_METHODPR(View3D, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttribute(uint) const", AS_METHODPR(View3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Variant get_attributes(uint) const", AS_METHODPR(View3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttribute(const String&in) const", AS_METHODPR(View3D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(View3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(View3D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(View3D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(View3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(View3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(View3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(View3D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool View3D::GetAutoUpdate() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "bool GetAutoUpdate() const", AS_METHODPR(View3D, GetAutoUpdate, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_autoUpdate() const", AS_METHODPR(View3D, GetAutoUpdate, () const, bool), AS_CALL_THISCALL);
    // void Window::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Window.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "BlendMode GetBlendMode() const", AS_METHODPR(View3D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "BlendMode get_blendMode() const", AS_METHODPR(View3D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool GetBlockEvents() const", AS_METHODPR(View3D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetBorder() const", AS_METHODPR(View3D, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_border() const", AS_METHODPR(View3D, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetBringToBack() const", AS_METHODPR(View3D, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_bringToBack() const", AS_METHODPR(View3D, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetBringToFront() const", AS_METHODPR(View3D, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_bringToFront() const", AS_METHODPR(View3D, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // Node* View3D::GetCameraNode() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Node@+ GetCameraNode() const", AS_METHODPR(View3D, GetCameraNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Node@+ get_cameraNode() const", AS_METHODPR(View3D, GetCameraNode, () const, Node*), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const String& GetCategory() const", AS_METHODPR(View3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_category() const", AS_METHODPR(View3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(uint) const", AS_METHODPR(View3D, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_children(uint) const", AS_METHODPR(View3D, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(View3D, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(View3D, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetChildOffset() const", AS_METHODPR(View3D, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_childOffset() const", AS_METHODPR(View3D, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(View3D_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(View3D_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(View3D_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetClipBorder() const", AS_METHODPR(View3D, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_clipBorder() const", AS_METHODPR(View3D, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetClipChildren() const", AS_METHODPR(View3D, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_clipChildren() const", AS_METHODPR(View3D, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetColor(Corner) const", AS_METHODPR(View3D, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_colors(Corner) const", AS_METHODPR(View3D, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetColorAttr() const", AS_METHODPR(View3D, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntRect GetCombinedScreenRect()", AS_METHODPR(View3D, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "IntRect get_combinedScreenRect()", AS_METHODPR(View3D, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(View3D, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // Texture2D* View3D::GetDepthTexture() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Texture2D@+ GetDepthTexture() const", AS_METHODPR(View3D, GetDepthTexture, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_depthTexture() const", AS_METHODPR(View3D, GetDepthTexture, () const, Texture2D*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Color& GetDerivedColor() const", AS_METHODPR(View3D, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "float GetDerivedOpacity() const", AS_METHODPR(View3D, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "float get_derivedOpacity() const", AS_METHODPR(View3D, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(View3D, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_disabledOffset() const", AS_METHODPR(View3D, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(View3D, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(View3D, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint GetDragButtonCount() const", AS_METHODPR(View3D, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_dragButtonCount() const", AS_METHODPR(View3D, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(View3D, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(View3D, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(View3D, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetElementEventSender() const", AS_METHODPR(View3D, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetEnableAnchor() const", AS_METHODPR(View3D, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enableAnchor() const", AS_METHODPR(View3D, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "VariantMap& GetEventDataMap() const", AS_METHODPR(View3D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "Object@+ GetEventSender() const", AS_METHODPR(View3D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool Window::GetFixedHeightResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetFixedHeightResizing() const", AS_METHODPR(View3D, GetFixedHeightResizing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedHeightResizing() const", AS_METHODPR(View3D, GetFixedHeightResizing, () const, bool), AS_CALL_THISCALL);
    // bool Window::GetFixedWidthResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetFixedWidthResizing() const", AS_METHODPR(View3D, GetFixedWidthResizing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedWidthResizing() const", AS_METHODPR(View3D, GetFixedWidthResizing, () const, bool), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "FocusMode GetFocusMode() const", AS_METHODPR(View3D, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "FocusMode get_focusMode() const", AS_METHODPR(View3D, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // unsigned View3D::GetFormat() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "uint GetFormat() const", AS_METHODPR(View3D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_format() const", AS_METHODPR(View3D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(View3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(View3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(View3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const VariantMap& get_globalVars() const", AS_METHODPR(View3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetHeight() const", AS_METHODPR(View3D, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_height() const", AS_METHODPR(View3D, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(View3D, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(View3D, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetHoverOffset() const", AS_METHODPR(View3D, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_hoverOffset() const", AS_METHODPR(View3D, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetImageBorder() const", AS_METHODPR(View3D, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_imageBorder() const", AS_METHODPR(View3D, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetImageRect() const", AS_METHODPR(View3D, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_imageRect() const", AS_METHODPR(View3D, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndent() const", AS_METHODPR(View3D, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indent() const", AS_METHODPR(View3D, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndentSpacing() const", AS_METHODPR(View3D, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indentSpacing() const", AS_METHODPR(View3D, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetIndentWidth() const", AS_METHODPR(View3D, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_indentWidth() const", AS_METHODPR(View3D, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(View3D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetLayoutBorder() const", AS_METHODPR(View3D, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_layoutBorder() const", AS_METHODPR(View3D, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetLayoutElementMaxSize() const", AS_METHODPR(View3D, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(View3D, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(View3D, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "LayoutMode GetLayoutMode() const", AS_METHODPR(View3D, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "LayoutMode get_layoutMode() const", AS_METHODPR(View3D, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetLayoutSpacing() const", AS_METHODPR(View3D, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_layoutSpacing() const", AS_METHODPR(View3D, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "Material@+ GetMaterial() const", AS_METHODPR(View3D, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Material@+ get_material() const", AS_METHODPR(View3D, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetMaterialAttr() const", AS_METHODPR(View3D, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetMaxAnchor() const", AS_METHODPR(View3D, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_maxAnchor() const", AS_METHODPR(View3D, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMaxHeight() const", AS_METHODPR(View3D, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_maxHeight() const", AS_METHODPR(View3D, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMaxOffset() const", AS_METHODPR(View3D, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_maxOffset() const", AS_METHODPR(View3D, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMaxSize() const", AS_METHODPR(View3D, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_maxSize() const", AS_METHODPR(View3D, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMaxWidth() const", AS_METHODPR(View3D, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_maxWidth() const", AS_METHODPR(View3D, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetMinAnchor() const", AS_METHODPR(View3D, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_minAnchor() const", AS_METHODPR(View3D, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMinHeight() const", AS_METHODPR(View3D, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_minHeight() const", AS_METHODPR(View3D, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMinOffset() const", AS_METHODPR(View3D, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_minOffset() const", AS_METHODPR(View3D, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetMinSize() const", AS_METHODPR(View3D, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_minSize() const", AS_METHODPR(View3D, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetMinWidth() const", AS_METHODPR(View3D, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_minWidth() const", AS_METHODPR(View3D, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // bool Window::GetModalAutoDismiss() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool GetModalAutoDismiss() const", AS_METHODPR(View3D, GetModalAutoDismiss, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_modalAutoDismiss() const", AS_METHODPR(View3D, GetModalAutoDismiss, () const, bool), AS_CALL_THISCALL);
    // const Color& Window::GetModalFrameColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const Color& GetModalFrameColor() const", AS_METHODPR(View3D, GetModalFrameColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_modalFrameColor() const", AS_METHODPR(View3D, GetModalFrameColor, () const, const Color&), AS_CALL_THISCALL);
    // const IntVector2& Window::GetModalFrameSize() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetModalFrameSize() const", AS_METHODPR(View3D, GetModalFrameSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_modalFrameSize() const", AS_METHODPR(View3D, GetModalFrameSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Color& Window::GetModalShadeColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const Color& GetModalShadeColor() const", AS_METHODPR(View3D, GetModalShadeColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Color& get_modalShadeColor() const", AS_METHODPR(View3D, GetModalShadeColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const String& GetName() const", AS_METHODPR(View3D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_name() const", AS_METHODPR(View3D, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "uint GetNumAttributes() const", AS_METHODPR(View3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_numAttributes() const", AS_METHODPR(View3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "uint GetNumChildren(bool = false) const", AS_METHODPR(View3D, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_numChildren(bool = false) const", AS_METHODPR(View3D, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "uint GetNumNetworkAttributes() const", AS_METHODPR(View3D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(View3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(View3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(View3D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "float GetOpacity() const", AS_METHODPR(View3D, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "float get_opacity() const", AS_METHODPR(View3D, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetParent() const", AS_METHODPR(View3D, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_parent() const", AS_METHODPR(View3D, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Vector2& GetPivot() const", AS_METHODPR(View3D, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const Vector2& get_pivot() const", AS_METHODPR(View3D, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetPosition() const", AS_METHODPR(View3D, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_position() const", AS_METHODPR(View3D, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetPriority() const", AS_METHODPR(View3D, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_priority() const", AS_METHODPR(View3D, GetPriority, () const, int), AS_CALL_THISCALL);
    // Texture2D* View3D::GetRenderTexture() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Texture2D@+ GetRenderTexture() const", AS_METHODPR(View3D, GetRenderTexture, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_renderTexture() const", AS_METHODPR(View3D, GetRenderTexture, () const, Texture2D*), AS_CALL_THISCALL);
    // const IntRect& Window::GetResizeBorder() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "const IntRect& GetResizeBorder() const", AS_METHODPR(View3D, GetResizeBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntRect& get_resizeBorder() const", AS_METHODPR(View3D, GetResizeBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ GetRoot() const", AS_METHODPR(View3D, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "UIElement@+ get_root() const", AS_METHODPR(View3D, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // Scene* View3D::GetScene() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Scene@+ GetScene() const", AS_METHODPR(View3D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Scene@+ get_scene() const", AS_METHODPR(View3D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetScreenPosition() const", AS_METHODPR(View3D, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_screenPosition() const", AS_METHODPR(View3D, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const IntVector2& GetSize() const", AS_METHODPR(View3D, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const IntVector2& get_size() const", AS_METHODPR(View3D, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetSortChildren() const", AS_METHODPR(View3D, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_sortChildren() const", AS_METHODPR(View3D, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(View3D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(View3D_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("View3D", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(View3D_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "Texture@+ GetTexture() const", AS_METHODPR(View3D, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture@+ get_texture() const", AS_METHODPR(View3D, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "ResourceRef GetTextureAttr() const", AS_METHODPR(View3D, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "TraversalMode GetTraversalMode() const", AS_METHODPR(View3D, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "TraversalMode get_traversalMode() const", AS_METHODPR(View3D, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "StringHash GetType() const", AS_METHODPR(View3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "StringHash get_type() const", AS_METHODPR(View3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "const String& GetTypeName() const", AS_METHODPR(View3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "const String& get_typeName() const", AS_METHODPR(View3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool GetUseDerivedOpacity() const", AS_METHODPR(View3D, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_useDerivedOpacity() const", AS_METHODPR(View3D, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(View3D, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "const VariantMap& GetVars() const", AS_METHODPR(View3D, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(View3D, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(View3D, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // Viewport* View3D::GetViewport() const | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "Viewport@+ GetViewport() const", AS_METHODPR(View3D, GetViewport, () const, Viewport*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Viewport@+ get_viewport() const", AS_METHODPR(View3D, GetViewport, () const, Viewport*), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "int GetWidth() const", AS_METHODPR(View3D, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_width() const", AS_METHODPR(View3D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasColorGradient() const", AS_METHODPR(View3D, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_colorGradient() const", AS_METHODPR(View3D, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasEventHandlers() const", AS_METHODPR(View3D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasFocus() const", AS_METHODPR(View3D, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_focus() const", AS_METHODPR(View3D, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(View3D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(View3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool HasTag(const String&in) const", AS_METHODPR(View3D, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void InsertChild(uint, UIElement@+)", AS_METHODPR(View3D, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsChildOf(UIElement@+) const", AS_METHODPR(View3D, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEditable() const", AS_METHODPR(View3D, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_editable() const", AS_METHODPR(View3D, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsElementEventSender() const", AS_METHODPR(View3D, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_elementEventSender() const", AS_METHODPR(View3D, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEnabled() const", AS_METHODPR(View3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enabled() const", AS_METHODPR(View3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsEnabledSelf() const", AS_METHODPR(View3D, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_enabledSelf() const", AS_METHODPR(View3D, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedHeight() const", AS_METHODPR(View3D, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedHeight() const", AS_METHODPR(View3D, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedSize() const", AS_METHODPR(View3D, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedSize() const", AS_METHODPR(View3D, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsFixedWidth() const", AS_METHODPR(View3D, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_fixedWidth() const", AS_METHODPR(View3D, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsHovering() const", AS_METHODPR(View3D, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_hovering() const", AS_METHODPR(View3D, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInside(IntVector2, bool)", AS_METHODPR(View3D, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(View3D, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(View3D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsInternal() const", AS_METHODPR(View3D, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_internal() const", AS_METHODPR(View3D, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsModal() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsModal() const", AS_METHODPR(View3D, IsModal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_modal() const", AS_METHODPR(View3D, IsModal, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsMovable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsMovable() const", AS_METHODPR(View3D, IsMovable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_movable() const", AS_METHODPR(View3D, IsMovable, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsResizable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "bool IsResizable() const", AS_METHODPR(View3D, IsResizable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_resizable() const", AS_METHODPR(View3D, IsResizable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsSelected() const", AS_METHODPR(View3D, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_selected() const", AS_METHODPR(View3D, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool IsTemporary() const", AS_METHODPR(View3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_temporary() const", AS_METHODPR(View3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "bool IsTiled() const", AS_METHODPR(View3D, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_tiled() const", AS_METHODPR(View3D, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsVisible() const", AS_METHODPR(View3D, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_visible() const", AS_METHODPR(View3D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsVisibleEffective() const", AS_METHODPR(View3D, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_visibleEffective() const", AS_METHODPR(View3D, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsWheelHandler() const", AS_METHODPR(View3D, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(View3D, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool Load(Deserializer&)", AS_METHODPR(View3D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(View3D, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(View3D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(View3D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(View3D, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool LoadXML(Deserializer&)", AS_METHODPR(View3D, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void MarkNetworkUpdate()", AS_METHODPR(View3D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(View3D, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(View3D, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(View3D, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(View3D, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(View3D, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(View3D, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(View3D, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // void Window::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(View3D, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(View3D, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(View3D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(View3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // void Window::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(View3D, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnIndentSet()", AS_METHODPR(View3D, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(View3D, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(View3D, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void View3D::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(View3D, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(View3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnSetEditable()", AS_METHODPR(View3D, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnTextInput(const String&in)", AS_METHODPR(View3D, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(View3D, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // void View3D::QueueUpdate() | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void QueueUpdate()", AS_METHODPR(View3D, QueueUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(View3D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(View3D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View3D", "int Refs() const", AS_METHODPR(View3D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_refs() const", AS_METHODPR(View3D, Refs, () const, int), AS_CALL_THISCALL);
    // static void View3D::RegisterObject(Context* context) | File: ../UI/View3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(View3D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void Remove()", AS_METHODPR(View3D, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveAllChildren()", AS_METHODPR(View3D, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveAllTags()", AS_METHODPR(View3D, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(View3D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(View3D, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void RemoveChildAtIndex(uint)", AS_METHODPR(View3D, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void RemoveInstanceDefault()", AS_METHODPR(View3D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void RemoveObjectAnimation()", AS_METHODPR(View3D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool RemoveTag(const String&in)", AS_METHODPR(View3D, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void ResetDeepEnabled()", AS_METHODPR(View3D, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void ResetToDefault()", AS_METHODPR(View3D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool Save(Serializer&) const", AS_METHODPR(View3D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SaveDefaultAttributes() const", AS_METHODPR(View3D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(View3D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SaveXML(XMLElement&) const", AS_METHODPR(View3D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(View3D, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(View3D, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SendEvent(StringHash)", AS_METHODPR(View3D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(View3D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(View3D, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAnimationEnabled(bool)", AS_METHODPR(View3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_animationEnabled(bool)", AS_METHODPR(View3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAnimationTime(float)", AS_METHODPR(View3D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(View3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(View3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(View3D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(View3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(View3D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(View3D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(View3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void View3D::SetAutoUpdate(bool enable) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetAutoUpdate(bool)", AS_METHODPR(View3D, SetAutoUpdate, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_autoUpdate(bool)", AS_METHODPR(View3D, SetAutoUpdate, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetBlendMode(BlendMode)", AS_METHODPR(View3D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_blendMode(BlendMode)", AS_METHODPR(View3D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SetBlockEvents(bool)", AS_METHODPR(View3D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetBorder(const IntRect&in)", AS_METHODPR(View3D, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_border(const IntRect&in)", AS_METHODPR(View3D, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetBringToBack(bool)", AS_METHODPR(View3D, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_bringToBack(bool)", AS_METHODPR(View3D, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetBringToFront(bool)", AS_METHODPR(View3D, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_bringToFront(bool)", AS_METHODPR(View3D, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(View3D, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetClipBorder(const IntRect&in)", AS_METHODPR(View3D, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_clipBorder(const IntRect&in)", AS_METHODPR(View3D, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetClipChildren(bool)", AS_METHODPR(View3D, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_clipChildren(bool)", AS_METHODPR(View3D, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetColor(const Color&in)", AS_METHODPR(View3D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_color(const Color&in)", AS_METHODPR(View3D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetColor(Corner, const Color&in)", AS_METHODPR(View3D, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_colors(Corner, const Color&in)", AS_METHODPR(View3D, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDeepEnabled(bool)", AS_METHODPR(View3D, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(View3D, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(View3D, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(View3D, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(View3D, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetDisabledOffset(int, int)", AS_METHODPR(View3D, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(View3D, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(View3D, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEditable(bool)", AS_METHODPR(View3D, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_editable(bool)", AS_METHODPR(View3D, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetElementEventSender(bool)", AS_METHODPR(View3D, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_elementEventSender(bool)", AS_METHODPR(View3D, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnableAnchor(bool)", AS_METHODPR(View3D, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_enableAnchor(bool)", AS_METHODPR(View3D, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnabled(bool)", AS_METHODPR(View3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_enabled(bool)", AS_METHODPR(View3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetEnabledRecursive(bool)", AS_METHODPR(View3D, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedHeight(int)", AS_METHODPR(View3D, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void Window::SetFixedHeightResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetFixedHeightResizing(bool)", AS_METHODPR(View3D, SetFixedHeightResizing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_fixedHeightResizing(bool)", AS_METHODPR(View3D, SetFixedHeightResizing, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(View3D, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedSize(int, int)", AS_METHODPR(View3D, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFixedWidth(int)", AS_METHODPR(View3D, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void Window::SetFixedWidthResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetFixedWidthResizing(bool)", AS_METHODPR(View3D, SetFixedWidthResizing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_fixedWidthResizing(bool)", AS_METHODPR(View3D, SetFixedWidthResizing, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFocus(bool)", AS_METHODPR(View3D, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_focus(bool)", AS_METHODPR(View3D, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetFocusMode(FocusMode)", AS_METHODPR(View3D, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_focusMode(FocusMode)", AS_METHODPR(View3D, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void View3D::SetFormat(unsigned format) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetFormat(uint)", AS_METHODPR(View3D, SetFormat, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_format(uint)", AS_METHODPR(View3D, SetFormat, (unsigned), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetFullImageRect()", AS_METHODPR(View3D, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(View3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(View3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHeight(int)", AS_METHODPR(View3D, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_height(int)", AS_METHODPR(View3D, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(View3D, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(View3D, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetHovering(bool)", AS_METHODPR(View3D, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(View3D, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(View3D, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetHoverOffset(int, int)", AS_METHODPR(View3D, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetImageBorder(const IntRect&in)", AS_METHODPR(View3D, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_imageBorder(const IntRect&in)", AS_METHODPR(View3D, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetImageRect(const IntRect&in)", AS_METHODPR(View3D, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_imageRect(const IntRect&in)", AS_METHODPR(View3D, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetIndent(int)", AS_METHODPR(View3D, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_indent(int)", AS_METHODPR(View3D, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetIndentSpacing(int)", AS_METHODPR(View3D, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_indentSpacing(int)", AS_METHODPR(View3D, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetInstanceDefault(bool)", AS_METHODPR(View3D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(View3D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetInternal(bool)", AS_METHODPR(View3D, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_internal(bool)", AS_METHODPR(View3D, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(View3D, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(View3D, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(View3D, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(View3D, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(View3D, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutMode(LayoutMode)", AS_METHODPR(View3D, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutMode(LayoutMode)", AS_METHODPR(View3D, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetLayoutSpacing(int)", AS_METHODPR(View3D, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_layoutSpacing(int)", AS_METHODPR(View3D, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetMaterial(Material@+)", AS_METHODPR(View3D, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_material(Material@+)", AS_METHODPR(View3D, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(View3D, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(View3D, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(View3D, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxAnchor(float, float)", AS_METHODPR(View3D, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxHeight(int)", AS_METHODPR(View3D, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxHeight(int)", AS_METHODPR(View3D, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(View3D, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(View3D, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(View3D, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxSize(const IntVector2&in)", AS_METHODPR(View3D, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxSize(int, int)", AS_METHODPR(View3D, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMaxWidth(int)", AS_METHODPR(View3D, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_maxWidth(int)", AS_METHODPR(View3D, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(View3D, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minAnchor(const Vector2&in)", AS_METHODPR(View3D, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinAnchor(float, float)", AS_METHODPR(View3D, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinHeight(int)", AS_METHODPR(View3D, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minHeight(int)", AS_METHODPR(View3D, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(View3D, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minOffset(const IntVector2&in)", AS_METHODPR(View3D, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinSize(const IntVector2&in)", AS_METHODPR(View3D, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minSize(const IntVector2&in)", AS_METHODPR(View3D, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinSize(int, int)", AS_METHODPR(View3D, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetMinWidth(int)", AS_METHODPR(View3D, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_minWidth(int)", AS_METHODPR(View3D, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void Window::SetModal(bool modal) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModal(bool)", AS_METHODPR(View3D, SetModal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modal(bool)", AS_METHODPR(View3D, SetModal, (bool), void), AS_CALL_THISCALL);
    // void Window::SetModalAutoDismiss(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalAutoDismiss(bool)", AS_METHODPR(View3D, SetModalAutoDismiss, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalAutoDismiss(bool)", AS_METHODPR(View3D, SetModalAutoDismiss, (bool), void), AS_CALL_THISCALL);
    // void Window::SetModalFrameColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalFrameColor(const Color&in)", AS_METHODPR(View3D, SetModalFrameColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalFrameColor(const Color&in)", AS_METHODPR(View3D, SetModalFrameColor, (const Color&), void), AS_CALL_THISCALL);
    // void Window::SetModalFrameSize(const IntVector2& size) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalFrameSize(const IntVector2&in)", AS_METHODPR(View3D, SetModalFrameSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalFrameSize(const IntVector2&in)", AS_METHODPR(View3D, SetModalFrameSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Window::SetModalShadeColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetModalShadeColor(const Color&in)", AS_METHODPR(View3D, SetModalShadeColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_modalShadeColor(const Color&in)", AS_METHODPR(View3D, SetModalShadeColor, (const Color&), void), AS_CALL_THISCALL);
    // void Window::SetMovable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetMovable(bool)", AS_METHODPR(View3D, SetMovable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_movable(bool)", AS_METHODPR(View3D, SetMovable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetName(const String&in)", AS_METHODPR(View3D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_name(const String&in)", AS_METHODPR(View3D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(View3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(View3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("View3D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(View3D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetOpacity(float)", AS_METHODPR(View3D, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_opacity(float)", AS_METHODPR(View3D, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(View3D, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPivot(const Vector2&in)", AS_METHODPR(View3D, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_pivot(const Vector2&in)", AS_METHODPR(View3D, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPivot(float, float)", AS_METHODPR(View3D, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPosition(const IntVector2&in)", AS_METHODPR(View3D, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_position(const IntVector2&in)", AS_METHODPR(View3D, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPosition(int, int)", AS_METHODPR(View3D, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetPriority(int)", AS_METHODPR(View3D, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_priority(int)", AS_METHODPR(View3D, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(View3D, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Window::SetResizable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetResizable(bool)", AS_METHODPR(View3D, SetResizable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_resizable(bool)", AS_METHODPR(View3D, SetResizable, (bool), void), AS_CALL_THISCALL);
    // void Window::SetResizeBorder(const IntRect& rect) | File: ../UI/Window.h
    engine->RegisterObjectMethod("View3D", "void SetResizeBorder(const IntRect&in)", AS_METHODPR(View3D, SetResizeBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_resizeBorder(const IntRect&in)", AS_METHODPR(View3D, SetResizeBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSelected(bool)", AS_METHODPR(View3D, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_selected(bool)", AS_METHODPR(View3D, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSize(const IntVector2&in)", AS_METHODPR(View3D, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_size(const IntVector2&in)", AS_METHODPR(View3D, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSize(int, int)", AS_METHODPR(View3D, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetSortChildren(bool)", AS_METHODPR(View3D, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_sortChildren(bool)", AS_METHODPR(View3D, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(View3D, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyle(const XMLElement&in)", AS_METHODPR(View3D, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(View3D, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(View3D_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void SetTemporary(bool)", AS_METHODPR(View3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_temporary(bool)", AS_METHODPR(View3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTexture(Texture@+)", AS_METHODPR(View3D, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_texture(Texture@+)", AS_METHODPR(View3D, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(View3D, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("View3D", "void SetTiled(bool)", AS_METHODPR(View3D, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_tiled(bool)", AS_METHODPR(View3D, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetTraversalMode(TraversalMode)", AS_METHODPR(View3D, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_traversalMode(TraversalMode)", AS_METHODPR(View3D, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetUseDerivedOpacity(bool)", AS_METHODPR(View3D, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_useDerivedOpacity(bool)", AS_METHODPR(View3D, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(View3D, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(View3D, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(View3D, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void View3D::SetView(Scene* scene, Camera* camera, bool ownScene=true) | File: ../UI/View3D.h
    engine->RegisterObjectMethod("View3D", "void SetView(Scene@+, Camera@+, bool = true)", AS_METHODPR(View3D, SetView, (Scene*, Camera*, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetVisible(bool)", AS_METHODPR(View3D, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_visible(bool)", AS_METHODPR(View3D, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SetWidth(int)", AS_METHODPR(View3D, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_width(int)", AS_METHODPR(View3D, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void SortChildren()", AS_METHODPR(View3D, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromAllEvents()", AS_METHODPR(View3D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(View3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(View3D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(View3D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("View3D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(View3D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void Update(float)", AS_METHODPR(View3D, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("View3D", "void UpdateLayout()", AS_METHODPR(View3D, UpdateLayout, (), void), AS_CALL_THISCALL);
    // explicit View3D::View3D(Context* context) | File: ../UI/View3D.h
    engine->RegisterObjectBehaviour("View3D", asBEHAVE_FACTORY, "View3D@+ f()", AS_FUNCTION(View3D_View3D_Context), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("View3D", "int WeakRefs() const", AS_METHODPR(View3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "int get_weakRefs() const", AS_METHODPR(View3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(View3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(View3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("View3D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(View3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Viewport, AddRef, (), void), AS_CALL_THISCALL);
    // void Viewport::AllocateView() | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void AllocateView()", AS_METHODPR(Viewport, AllocateView, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool GetBlockEvents() const", AS_METHODPR(Viewport, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // Camera* Viewport::GetCamera() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Camera@+ GetCamera() const", AS_METHODPR(Viewport, GetCamera, () const, Camera*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_camera() const", AS_METHODPR(Viewport, GetCamera, () const, Camera*), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const String& GetCategory() const", AS_METHODPR(Viewport, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const String& get_category() const", AS_METHODPR(Viewport, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Camera* Viewport::GetCullCamera() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Camera@+ GetCullCamera() const", AS_METHODPR(Viewport, GetCullCamera, () const, Camera*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_cullCamera() const", AS_METHODPR(Viewport, GetCullCamera, () const, Camera*), AS_CALL_THISCALL);
    // bool Viewport::GetDrawDebug() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "bool GetDrawDebug() const", AS_METHODPR(Viewport, GetDrawDebug, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "bool get_drawDebug() const", AS_METHODPR(Viewport, GetDrawDebug, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "VariantMap& GetEventDataMap() const", AS_METHODPR(Viewport, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "Object@+ GetEventSender() const", AS_METHODPR(Viewport, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Viewport, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Viewport, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Viewport, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const VariantMap& get_globalVars() const", AS_METHODPR(Viewport, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const IntRect& Viewport::GetRect() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "const IntRect& GetRect() const", AS_METHODPR(Viewport, GetRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const IntRect& get_rect() const", AS_METHODPR(Viewport, GetRect, () const, const IntRect&), AS_CALL_THISCALL);
    // RenderPath* Viewport::GetRenderPath() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "RenderPath@+ GetRenderPath() const", AS_METHODPR(Viewport, GetRenderPath, () const, RenderPath*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "RenderPath@+ get_renderPath() const", AS_METHODPR(Viewport, GetRenderPath, () const, RenderPath*), AS_CALL_THISCALL);
    // Scene* Viewport::GetScene() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Scene@+ GetScene() const", AS_METHODPR(Viewport, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Scene@+ get_scene() const", AS_METHODPR(Viewport, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Ray Viewport::GetScreenRay(int x, int y) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Ray GetScreenRay(int, int) const", AS_METHODPR(Viewport, GetScreenRay, (int, int) const, Ray), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Viewport, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "StringHash GetType() const", AS_METHODPR(Viewport, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "StringHash get_type() const", AS_METHODPR(Viewport, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "const String& GetTypeName() const", AS_METHODPR(Viewport, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const String& get_typeName() const", AS_METHODPR(Viewport, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // View* Viewport::GetView() const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "View@+ GetView() const", AS_METHODPR(Viewport, GetView, () const, View*), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasEventHandlers() const", AS_METHODPR(Viewport, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Viewport, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Viewport, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Viewport, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Viewport, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Viewport", "int Refs() const", AS_METHODPR(Viewport, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "int get_refs() const", AS_METHODPR(Viewport, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Viewport, ReleaseRef, (), void), AS_CALL_THISCALL);
    // Vector3 Viewport::ScreenToWorldPoint(int x, int y, float depth) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "Vector3 ScreenToWorldPoint(int, int, float) const", AS_METHODPR(Viewport, ScreenToWorldPoint, (int, int, float) const, Vector3), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SendEvent(StringHash)", AS_METHODPR(Viewport, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Viewport, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SetBlockEvents(bool)", AS_METHODPR(Viewport, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Viewport::SetCamera(Camera* camera) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetCamera(Camera@+)", AS_METHODPR(Viewport, SetCamera, (Camera*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_camera(Camera@+)", AS_METHODPR(Viewport, SetCamera, (Camera*), void), AS_CALL_THISCALL);
    // void Viewport::SetCullCamera(Camera* camera) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetCullCamera(Camera@+)", AS_METHODPR(Viewport, SetCullCamera, (Camera*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_cullCamera(Camera@+)", AS_METHODPR(Viewport, SetCullCamera, (Camera*), void), AS_CALL_THISCALL);
    // void Viewport::SetDrawDebug(bool enable) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetDrawDebug(bool)", AS_METHODPR(Viewport, SetDrawDebug, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_drawDebug(bool)", AS_METHODPR(Viewport, SetDrawDebug, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Viewport, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Viewport, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Viewport::SetRect(const IntRect& rect) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetRect(const IntRect&in)", AS_METHODPR(Viewport, SetRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_rect(const IntRect&in)", AS_METHODPR(Viewport, SetRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void Viewport::SetRenderPath(RenderPath* renderPath) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetRenderPath(RenderPath@+)", AS_METHODPR(Viewport, SetRenderPath, (RenderPath*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_renderPath(RenderPath@+)", AS_METHODPR(Viewport, SetRenderPath, (RenderPath*), void), AS_CALL_THISCALL);
    // bool Viewport::SetRenderPath(XMLFile* file) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "bool SetRenderPath(XMLFile@+)", AS_METHODPR(Viewport, SetRenderPath, (XMLFile*), bool), AS_CALL_THISCALL);
    // void Viewport::SetScene(Scene* scene) | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "void SetScene(Scene@+)", AS_METHODPR(Viewport, SetScene, (Scene*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_scene(Scene@+)", AS_METHODPR(Viewport, SetScene, (Scene*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromAllEvents()", AS_METHODPR(Viewport, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Viewport_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Viewport, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Viewport, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Viewport", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Viewport, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // explicit Viewport::Viewport(Context* context) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f()", AS_FUNCTION(Viewport_Viewport_Context), AS_CALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, RenderPath@+ = null)", AS_FUNCTION(Viewport_Viewport_Context_Scene_Camera_RenderPath), AS_CALL_CDECL);
    // Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath=nullptr) | File: ../Graphics/Viewport.h
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, const IntRect&in, RenderPath@+ = null)", AS_FUNCTION(Viewport_Viewport_Context_Scene_Camera_IntRect_RenderPath), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Viewport", "int WeakRefs() const", AS_METHODPR(Viewport, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "int get_weakRefs() const", AS_METHODPR(Viewport, WeakRefs, () const, int), AS_CALL_THISCALL);
    // IntVector2 Viewport::WorldToScreenPoint(const Vector3& worldPos) const | File: ../Graphics/Viewport.h
    engine->RegisterObjectMethod("Viewport", "IntVector2 WorldToScreenPoint(const Vector3&in) const", AS_METHODPR(Viewport, WorldToScreenPoint, (const Vector3&) const, IntVector2), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("VertexElement", "bool opEquals(const VertexElement&in) const", AS_METHODPR(VertexElement, operator==, (const VertexElement&) const, bool), AS_CALL_THISCALL);
    // VertexElement::VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index=0, bool perInstance=false) noexcept | File: ../Graphics/GraphicsDefs.h
    engine->RegisterObjectBehaviour("VertexElement", asBEHAVE_CONSTRUCT, "void f(VertexElementType, VertexElementSemantic, uint8 = 0, bool = false)", AS_FUNCTION_OBJFIRST(VertexElement_VertexElement_VertexElementType_VertexElementSemantic_unsignedchar_bool), AS_CALL_CDECL_OBJFIRST);
    // VertexElement& VertexElement::operator=(const VertexElement&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<VertexElement>(engine, "VertexElement");
#ifdef REGISTER_MANUAL_PART_VertexElement
    REGISTER_MANUAL_PART_VertexElement(VertexElement, "VertexElement")
#endif

}

}
