// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// SharedPtr<Material> Material::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Material.h
static Material* Material_Clone_String(Material* ptr, const String& cloneName)
{
    SharedPtr<Material> result = ptr->Clone(cloneName);
    return result.Detach();
}

// explicit Material::Material(Context* context) | File: ../Graphics/Material.h
static Material* Material_Material_Context()
{
    return new Material(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Material_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Material* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// Matrix2::Matrix2(const Matrix2& matrix) noexcept=default | File: ../Math/Matrix2.h
static void Matrix2_Matrix2_Matrix2(Matrix2* ptr, const Matrix2 &matrix)
{
    new(ptr) Matrix2(matrix);
}

// Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept | File: ../Math/Matrix2.h
static void Matrix2_Matrix2_float_float_float_float(Matrix2* ptr, float v00, float v01, float v10, float v11)
{
    new(ptr) Matrix2(v00, v01, v10, v11);
}

// Matrix3::Matrix3(const Matrix3& matrix) noexcept=default | File: ../Math/Matrix3.h
static void Matrix3_Matrix3_Matrix3(Matrix3* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix3(matrix);
}

// Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept | File: ../Math/Matrix3.h
static void Matrix3_Matrix3_float_float_float_float_float_float_float_float_float(Matrix3* ptr, float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    new(ptr) Matrix3(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

// Matrix3x4::Matrix3x4(const Matrix3x4& matrix) noexcept=default | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_Matrix3x4(Matrix3x4* ptr, const Matrix3x4 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// explicit Matrix3x4::Matrix3x4(const Matrix3& matrix) noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_Matrix3(Matrix3x4* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// explicit Matrix3x4::Matrix3x4(const Matrix4& matrix) noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_Matrix4(Matrix3x4* ptr, const Matrix4 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_float_float_float_float_float_float_float_float_float_float_float_float(Matrix3x4* ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23)
{
    new(ptr) Matrix3x4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23);
}

// Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_Vector3_Quaternion_float(Matrix3x4* ptr, const Vector3 &translation, const Quaternion &rotation, float scale)
{
    new(ptr) Matrix3x4(translation, rotation, scale);
}

// Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept | File: ../Math/Matrix3x4.h
static void Matrix3x4_Matrix3x4_Vector3_Quaternion_Vector3(Matrix3x4* ptr, const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale)
{
    new(ptr) Matrix3x4(translation, rotation, scale);
}

// Matrix4::Matrix4(const Matrix4& matrix) noexcept | File: ../Math/Matrix4.h
static void Matrix4_Matrix4_Matrix4(Matrix4* ptr, const Matrix4 &matrix)
{
    new(ptr) Matrix4(matrix);
}

// explicit Matrix4::Matrix4(const Matrix3& matrix) noexcept | File: ../Math/Matrix4.h
static void Matrix4_Matrix4_Matrix3(Matrix4* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix4(matrix);
}

// Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept | File: ../Math/Matrix4.h
static void Matrix4_Matrix4_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float(Matrix4* ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
{
    new(ptr) Matrix4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Menu_AddTags_StringVector(Menu* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Menu_GetChildren_void(Menu* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Menu_GetChildren_bool(Menu* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Menu_GetChildrenWithTag_String_bool(Menu* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Menu_GetTags_void(Menu* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit Menu::Menu(Context* context) | File: ../UI/Menu.h
static Menu* Menu_Menu_Context()
{
    return new Menu(GetScriptContext());
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Menu_SetTags_StringVector(Menu* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Menu_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Menu* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit MessageBox::MessageBox(Context* context, const String& messageString=String::EMPTY, const String& titleString=String::EMPTY, XMLFile* layoutFile=nullptr, XMLFile* styleFile=nullptr) | File: ../UI/MessageBox.h
static MessageBox* MessageBox_MessageBox_Context_String_String_XMLFile_XMLFile(const String &messageString=String::EMPTY, const String &titleString=String::EMPTY, XMLFile *layoutFile=nullptr, XMLFile *styleFile=nullptr)
{
    return new MessageBox(GetScriptContext(), messageString, titleString, layoutFile, styleFile);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void MessageBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(MessageBox* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// SharedPtr<Model> Model::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Model.h
static Model* Model_Clone_String(Model* ptr, const String& cloneName)
{
    SharedPtr<Model> result = ptr->Clone(cloneName);
    return result.Detach();
}

// const PODVector<Vector3>& Model::GetGeometryCenters() const | File: ../Graphics/Model.h
static CScriptArray* Model_GetGeometryCenters_void(Model* ptr)
{
    const PODVector<Vector3>& result = ptr->GetGeometryCenters();
    return VectorToArray(result, "Array<Vector3>");
}

// const Vector<SharedPtr<IndexBuffer>>& Model::GetIndexBuffers() const | File: ../Graphics/Model.h
static CScriptArray* Model_GetIndexBuffers_void(Model* ptr)
{
    const Vector<SharedPtr<IndexBuffer>>& result = ptr->GetIndexBuffers();
    return VectorToHandleArray(result, "Array<IndexBuffer@>");
}

// const Vector<SharedPtr<VertexBuffer>>& Model::GetVertexBuffers() const | File: ../Graphics/Model.h
static CScriptArray* Model_GetVertexBuffers_void(Model* ptr)
{
    const Vector<SharedPtr<VertexBuffer>>& result = ptr->GetVertexBuffers();
    return VectorToHandleArray(result, "Array<VertexBuffer@>");
}

// explicit Model::Model(Context* context) | File: ../Graphics/Model.h
static Model* Model_Model_Context()
{
    return new Model(GetScriptContext());
}

// bool Model::SetIndexBuffers(const Vector<SharedPtr<IndexBuffer>>& buffers) | File: ../Graphics/Model.h
static bool Model_SetIndexBuffers_VectorSharedPtrIndexBuffer(Model* ptr, CScriptArray* buffers_conv)
{
    Vector<SharedPtr<IndexBuffer>> buffers = HandleArrayToVector<IndexBuffer>(buffers_conv);
    bool result = ptr->SetIndexBuffers(buffers);
    return result;
}

// bool Model::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, const PODVector<unsigned>& morphRangeStarts, const PODVector<unsigned>& morphRangeCounts) | File: ../Graphics/Model.h
static bool Model_SetVertexBuffers_VectorSharedPtrVertexBuffer_PODVectorunsigned_PODVectorunsigned(Model* ptr, CScriptArray* buffers_conv, CScriptArray* morphRangeStarts_conv, CScriptArray* morphRangeCounts_conv)
{
    Vector<SharedPtr<VertexBuffer>> buffers = HandleArrayToVector<VertexBuffer>(buffers_conv);
    PODVector<unsigned> morphRangeStarts = ArrayToPODVector<unsigned>(morphRangeStarts_conv);
    PODVector<unsigned> morphRangeCounts = ArrayToPODVector<unsigned>(morphRangeCounts_conv);
    bool result = ptr->SetVertexBuffers(buffers, morphRangeStarts, morphRangeCounts);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Model_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Model* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit MutexLock::MutexLock(Mutex& mutex) | File: ../Core/Mutex.h
static void MutexLock_MutexLock_Mutex(MutexLock* ptr, Mutex &mutex)
{
    new(ptr) MutexLock(mutex);
}

void ASRegisterGenerated_Members_M(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Material", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Material, AddRef, (), void), AS_CALL_THISCALL);
    // bool Material::BeginLoad(Deserializer& source) override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool BeginLoad(Deserializer&)", AS_METHODPR(Material, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Material> Material::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Material@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(Material_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // bool Material::EndLoad() override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool EndLoad()", AS_METHODPR(Material, EndLoad, (), bool), AS_CALL_THISCALL);
    // bool Material::GetAlphaToCoverage() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetAlphaToCoverage() const", AS_METHODPR(Material, GetAlphaToCoverage, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_alphaToCoverage() const", AS_METHODPR(Material, GetAlphaToCoverage, () const, bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Material, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // unsigned Material::GetAuxViewFrameNumber() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetAuxViewFrameNumber() const", AS_METHODPR(Material, GetAuxViewFrameNumber, () const, unsigned), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool GetBlockEvents() const", AS_METHODPR(Material, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const String& GetCategory() const", AS_METHODPR(Material, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_category() const", AS_METHODPR(Material, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode Material::GetCullMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "CullMode GetCullMode() const", AS_METHODPR(Material, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_cullMode() const", AS_METHODPR(Material, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    // const BiasParameters& Material::GetDepthBias() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const BiasParameters& GetDepthBias() const", AS_METHODPR(Material, GetDepthBias, () const, const BiasParameters&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const BiasParameters& get_depthBias() const", AS_METHODPR(Material, GetDepthBias, () const, const BiasParameters&), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "VariantMap& GetEventDataMap() const", AS_METHODPR(Material, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "Object@+ GetEventSender() const", AS_METHODPR(Material, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FillMode Material::GetFillMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "FillMode GetFillMode() const", AS_METHODPR(Material, GetFillMode, () const, FillMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "FillMode get_fillMode() const", AS_METHODPR(Material, GetFillMode, () const, FillMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Material, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Material, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Material, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const VariantMap& get_globalVars() const", AS_METHODPR(Material, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Material::GetLineAntiAlias() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetLineAntiAlias() const", AS_METHODPR(Material, GetLineAntiAlias, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_lineAntiAlias() const", AS_METHODPR(Material, GetLineAntiAlias, () const, bool), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "uint GetMemoryUse() const", AS_METHODPR(Material, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_memoryUse() const", AS_METHODPR(Material, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "const String& GetName() const", AS_METHODPR(Material, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_name() const", AS_METHODPR(Material, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "StringHash GetNameHash() const", AS_METHODPR(Material, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned Material::GetNumTechniques() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetNumTechniques() const", AS_METHODPR(Material, GetNumTechniques, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_numTechniques() const", AS_METHODPR(Material, GetNumTechniques, () const, unsigned), AS_CALL_THISCALL);
    // bool Material::GetOcclusion() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetOcclusion() const", AS_METHODPR(Material, GetOcclusion, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_occlusion() const", AS_METHODPR(Material, GetOcclusion, () const, bool), AS_CALL_THISCALL);
    // Pass* Material::GetPass(unsigned index, const String& passName) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Pass@+ GetPass(uint, const String&in) const", AS_METHODPR(Material, GetPass, (unsigned, const String&) const, Pass*), AS_CALL_THISCALL);
    // const String& Material::GetPixelShaderDefines() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const String& GetPixelShaderDefines() const", AS_METHODPR(Material, GetPixelShaderDefines, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_pixelShaderDefines() const", AS_METHODPR(Material, GetPixelShaderDefines, () const, const String&), AS_CALL_THISCALL);
    // unsigned char Material::GetRenderOrder() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint8 GetRenderOrder() const", AS_METHODPR(Material, GetRenderOrder, () const, unsigned char), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint8 get_renderOrder() const", AS_METHODPR(Material, GetRenderOrder, () const, unsigned char), AS_CALL_THISCALL);
    // Scene* Material::GetScene() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Scene@+ GetScene() const", AS_METHODPR(Material, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Scene@+ get_scene() const", AS_METHODPR(Material, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // const Variant& Material::GetShaderParameter(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const Variant& GetShaderParameter(const String&in) const", AS_METHODPR(Material, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const Variant& get_shaderParameters(const String&in) const", AS_METHODPR(Material, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // ValueAnimation* Material::GetShaderParameterAnimation(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "ValueAnimation@+ GetShaderParameterAnimation(const String&in) const", AS_METHODPR(Material, GetShaderParameterAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Material::GetShaderParameterAnimationSpeed(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "float GetShaderParameterAnimationSpeed(const String&in) const", AS_METHODPR(Material, GetShaderParameterAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Material::GetShaderParameterAnimationWrapMode(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "WrapMode GetShaderParameterAnimationWrapMode(const String&in) const", AS_METHODPR(Material, GetShaderParameterAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // unsigned Material::GetShaderParameterHash() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetShaderParameterHash() const", AS_METHODPR(Material, GetShaderParameterHash, () const, unsigned), AS_CALL_THISCALL);
    // const HashMap<StringHash, MaterialShaderParameter>& Material::GetShaderParameters() const | File: ../Graphics/Material.h
    // Error: type "const HashMap<StringHash, MaterialShaderParameter>&" can not automatically bind
    // CullMode Material::GetShadowCullMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "CullMode GetShadowCullMode() const", AS_METHODPR(Material, GetShadowCullMode, () const, CullMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_shadowCullMode() const", AS_METHODPR(Material, GetShadowCullMode, () const, CullMode), AS_CALL_THISCALL);
    // bool Material::GetSpecular() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetSpecular() const", AS_METHODPR(Material, GetSpecular, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Material, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Technique* Material::GetTechnique(unsigned index) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Technique@+ GetTechnique(uint) const", AS_METHODPR(Material, GetTechnique, (unsigned) const, Technique*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Technique@+ get_techniques(uint) const", AS_METHODPR(Material, GetTechnique, (unsigned) const, Technique*), AS_CALL_THISCALL);
    // const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const TechniqueEntry& GetTechniqueEntry(uint) const", AS_METHODPR(Material, GetTechniqueEntry, (unsigned) const, const TechniqueEntry&), AS_CALL_THISCALL);
    // const Vector<TechniqueEntry>& Material::GetTechniques() const | File: ../Graphics/Material.h
    // Error: type "const Vector<TechniqueEntry>&" can not automatically bind
    // Texture* Material::GetTexture(TextureUnit unit) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Texture@+ GetTexture(TextureUnit) const", AS_METHODPR(Material, GetTexture, (TextureUnit) const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Texture@+ get_textures(TextureUnit) const", AS_METHODPR(Material, GetTexture, (TextureUnit) const, Texture*), AS_CALL_THISCALL);
    // const HashMap<TextureUnit, SharedPtr<Texture>>& Material::GetTextures() const | File: ../Graphics/Material.h
    // Error: type "const HashMap<TextureUnit, SharedPtr<Texture>>&" can not automatically bind
    // static String Material::GetTextureUnitName(TextureUnit unit) | File: ../Graphics/Material.h
    engine->SetDefaultNamespace("Material");
    engine->RegisterGlobalFunction("String GetTextureUnitName(TextureUnit)", AS_FUNCTIONPR(Material::GetTextureUnitName, (TextureUnit), String), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "StringHash GetType() const", AS_METHODPR(Material, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "StringHash get_type() const", AS_METHODPR(Material, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const String& GetTypeName() const", AS_METHODPR(Material, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_typeName() const", AS_METHODPR(Material, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "uint GetUseTimer()", AS_METHODPR(Material, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_useTimer()", AS_METHODPR(Material, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // const String& Material::GetVertexShaderDefines() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const String& GetVertexShaderDefines() const", AS_METHODPR(Material, GetVertexShaderDefines, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_vertexShaderDefines() const", AS_METHODPR(Material, GetVertexShaderDefines, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasEventHandlers() const", AS_METHODPR(Material, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Material, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Material, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Material, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Material::Load(const XMLElement& source) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Load(const XMLElement&in)", AS_METHODPR(Material, Load, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool Material::Load(const JSONValue& source) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Load(const JSONValue&in)", AS_METHODPR(Material, Load, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "bool LoadFile(const String&in)", AS_METHODPR(Material, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool Load(const String&in)", AS_METHODPR(Material, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // void Material::MarkForAuxView(unsigned frameNumber) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void MarkForAuxView(uint)", AS_METHODPR(Material, MarkForAuxView, (unsigned), void), AS_CALL_THISCALL);
    // explicit Material::Material(Context* context) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("Material", asBEHAVE_FACTORY, "Material@+ f()", AS_FUNCTION(Material_Material_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Material, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // static Variant Material::ParseShaderParameterValue(const String& value) | File: ../Graphics/Material.h
    engine->SetDefaultNamespace("Material");
    engine->RegisterGlobalFunction("Variant ParseShaderParameterValue(const String&in)", AS_FUNCTIONPR(Material::ParseShaderParameterValue, (const String&), Variant), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Material", "int Refs() const", AS_METHODPR(Material, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "int get_refs() const", AS_METHODPR(Material, Refs, () const, int), AS_CALL_THISCALL);
    // static void Material::RegisterObject(Context* context) | File: ../Graphics/Material.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Material", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Material, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Material::ReleaseShaders() | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void ReleaseShaders()", AS_METHODPR(Material, ReleaseShaders, (), void), AS_CALL_THISCALL);
    // void Material::RemoveShaderParameter(const String& name) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void RemoveShaderParameter(const String&in)", AS_METHODPR(Material, RemoveShaderParameter, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void ResetUseTimer()", AS_METHODPR(Material, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool Material::Save(Serializer& dest) const override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(Serializer&) const", AS_METHODPR(Material, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool Material::Save(XMLElement& dest) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(XMLElement&) const", AS_METHODPR(Material, Save, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool Material::Save(JSONValue& dest) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(JSONValue&) const", AS_METHODPR(Material, Save, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "bool SaveFile(const String&in) const", AS_METHODPR(Material, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool Save(const String&in) const", AS_METHODPR(Material, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SendEvent(StringHash)", AS_METHODPR(Material, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Material, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Material::SetAlphaToCoverage(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetAlphaToCoverage(bool)", AS_METHODPR(Material, SetAlphaToCoverage, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_alphaToCoverage(bool)", AS_METHODPR(Material, SetAlphaToCoverage, (bool), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Material, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SetBlockEvents(bool)", AS_METHODPR(Material, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Material::SetCullMode(CullMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetCullMode(CullMode)", AS_METHODPR(Material, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_cullMode(CullMode)", AS_METHODPR(Material, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    // void Material::SetDepthBias(const BiasParameters& parameters) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetDepthBias(const BiasParameters&in)", AS_METHODPR(Material, SetDepthBias, (const BiasParameters&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_depthBias(const BiasParameters&in)", AS_METHODPR(Material, SetDepthBias, (const BiasParameters&), void), AS_CALL_THISCALL);
    // void Material::SetFillMode(FillMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetFillMode(FillMode)", AS_METHODPR(Material, SetFillMode, (FillMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_fillMode(FillMode)", AS_METHODPR(Material, SetFillMode, (FillMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Material, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Material, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Material::SetLineAntiAlias(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetLineAntiAlias(bool)", AS_METHODPR(Material, SetLineAntiAlias, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_lineAntiAlias(bool)", AS_METHODPR(Material, SetLineAntiAlias, (bool), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetMemoryUse(uint)", AS_METHODPR(Material, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetName(const String&in)", AS_METHODPR(Material, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_name(const String&in)", AS_METHODPR(Material, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Material::SetNumTechniques(unsigned num) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetNumTechniques(uint)", AS_METHODPR(Material, SetNumTechniques, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_numTechniques(uint)", AS_METHODPR(Material, SetNumTechniques, (unsigned), void), AS_CALL_THISCALL);
    // void Material::SetOcclusion(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetOcclusion(bool)", AS_METHODPR(Material, SetOcclusion, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_occlusion(bool)", AS_METHODPR(Material, SetOcclusion, (bool), void), AS_CALL_THISCALL);
    // void Material::SetPixelShaderDefines(const String& defines) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetPixelShaderDefines(const String&in)", AS_METHODPR(Material, SetPixelShaderDefines, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_pixelShaderDefines(const String&in)", AS_METHODPR(Material, SetPixelShaderDefines, (const String&), void), AS_CALL_THISCALL);
    // void Material::SetRenderOrder(unsigned char order) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetRenderOrder(uint8)", AS_METHODPR(Material, SetRenderOrder, (unsigned char), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_renderOrder(uint8)", AS_METHODPR(Material, SetRenderOrder, (unsigned char), void), AS_CALL_THISCALL);
    // void Material::SetScene(Scene* scene) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetScene(Scene@+)", AS_METHODPR(Material, SetScene, (Scene*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_scene(Scene@+)", AS_METHODPR(Material, SetScene, (Scene*), void), AS_CALL_THISCALL);
    // void Material::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameter(const String&in, const Variant&in)", AS_METHODPR(Material, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shaderParameters(const String&in, const Variant&in)", AS_METHODPR(Material, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void Material::SetShaderParameterAnimation(const String& name, ValueAnimation* animation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Material, SetShaderParameterAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Material::SetShaderParameterAnimationSpeed(const String& name, float speed) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimationSpeed(const String&in, float)", AS_METHODPR(Material, SetShaderParameterAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Material::SetShaderParameterAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Material, SetShaderParameterAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Material::SetShadowCullMode(CullMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShadowCullMode(CullMode)", AS_METHODPR(Material, SetShadowCullMode, (CullMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shadowCullMode(CullMode)", AS_METHODPR(Material, SetShadowCullMode, (CullMode), void), AS_CALL_THISCALL);
    // void Material::SetTechnique(unsigned index, Technique* tech, MaterialQuality qualityLevel=QUALITY_LOW, float lodDistance=0.0f) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetTechnique(uint, Technique@+, MaterialQuality = QUALITY_LOW, float = 0.0f)", AS_METHODPR(Material, SetTechnique, (unsigned, Technique*, MaterialQuality, float), void), AS_CALL_THISCALL);
    // void Material::SetTexture(TextureUnit unit, Texture* texture) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetTexture(TextureUnit, Texture@+)", AS_METHODPR(Material, SetTexture, (TextureUnit, Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_textures(TextureUnit, Texture@+)", AS_METHODPR(Material, SetTexture, (TextureUnit, Texture*), void), AS_CALL_THISCALL);
    // void Material::SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, const Vector2&in)", AS_METHODPR(Material, SetUVTransform, (const Vector2&, float, const Vector2&), void), AS_CALL_THISCALL);
    // void Material::SetUVTransform(const Vector2& offset, float rotation, float repeat) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, float)", AS_METHODPR(Material, SetUVTransform, (const Vector2&, float, float), void), AS_CALL_THISCALL);
    // void Material::SetVertexShaderDefines(const String& defines) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetVertexShaderDefines(const String&in)", AS_METHODPR(Material, SetVertexShaderDefines, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_vertexShaderDefines(const String&in)", AS_METHODPR(Material, SetVertexShaderDefines, (const String&), void), AS_CALL_THISCALL);
    // void Material::SortTechniques() | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SortTechniques()", AS_METHODPR(Material, SortTechniques, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromAllEvents()", AS_METHODPR(Material, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Material_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Material, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Material, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Material, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Material", "int WeakRefs() const", AS_METHODPR(Material, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Material", "int get_weakRefs() const", AS_METHODPR(Material, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Material, "Material")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Material, "Material")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Material, "Material")
#endif
#ifdef REGISTER_MANUAL_PART_Material
    REGISTER_MANUAL_PART_Material(Material, "Material")
#endif
    RegisterSubclass<Resource, Material>(engine, "Resource", "Material");
    RegisterSubclass<Object, Material>(engine, "Object", "Material");
    RegisterSubclass<RefCounted, Material>(engine, "RefCounted", "Material");

    // const Matrix2 Matrix2::IDENTITY | File: ../Math/Matrix2.h
    engine->SetDefaultNamespace("Matrix2");
    engine->RegisterGlobalProperty("const Matrix2 IDENTITY", (void*)&Matrix2::IDENTITY);
    engine->SetDefaultNamespace("");
    // float Matrix2::m00_ | File: ../Math/Matrix2.h
    engine->RegisterObjectProperty("Matrix2", "float m00", offsetof(Matrix2, m00_));
    // float Matrix2::m01_ | File: ../Math/Matrix2.h
    engine->RegisterObjectProperty("Matrix2", "float m01", offsetof(Matrix2, m01_));
    // float Matrix2::m10_ | File: ../Math/Matrix2.h
    engine->RegisterObjectProperty("Matrix2", "float m10", offsetof(Matrix2, m10_));
    // float Matrix2::m11_ | File: ../Math/Matrix2.h
    engine->RegisterObjectProperty("Matrix2", "float m11", offsetof(Matrix2, m11_));
    // const Matrix2 Matrix2::ZERO | File: ../Math/Matrix2.h
    engine->SetDefaultNamespace("Matrix2");
    engine->RegisterGlobalProperty("const Matrix2 ZERO", (void*)&Matrix2::ZERO);
    engine->SetDefaultNamespace("");
    // static void Matrix2::BulkTranspose(float* dest, const float* src, unsigned count) | File: ../Math/Matrix2.h
    // Error: type "float*" can not automatically bind
    // const float* Matrix2::Data() const | File: ../Math/Matrix2.h
    // Error: type "const float*" can not automatically bind
    // bool Matrix2::Equals(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool Equals(const Matrix2&in) const", AS_METHODPR(Matrix2, Equals, (const Matrix2&) const, bool), AS_CALL_THISCALL);
    // Matrix2 Matrix2::Inverse() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Inverse() const", AS_METHODPR(Matrix2, Inverse, () const, Matrix2), AS_CALL_THISCALL);
    // bool Matrix2::IsInf() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool IsInf() const", AS_METHODPR(Matrix2, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Matrix2::IsNaN() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool IsNaN() const", AS_METHODPR(Matrix2, IsNaN, () const, bool), AS_CALL_THISCALL);
    // Matrix2::Matrix2(const Matrix2& matrix) noexcept=default | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", AS_FUNCTION_OBJFIRST(Matrix2_Matrix2_Matrix2), AS_CALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix2_Matrix2_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix2::Matrix2(const float* data) noexcept | File: ../Math/Matrix2.h
    // Error: type "const float*" can not automatically bind
    // Vector2 Matrix2::operator*(const Vector2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Vector2 opMul(const Vector2&in) const", AS_METHODPR(Matrix2, operator*, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // Matrix2 Matrix2::operator*(float rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(float) const", AS_METHODPR(Matrix2, operator*, (float) const, Matrix2), AS_CALL_THISCALL);
    // Matrix2 Matrix2::operator*(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(const Matrix2&in) const", AS_METHODPR(Matrix2, operator*, (const Matrix2&) const, Matrix2), AS_CALL_THISCALL);
    // Matrix2 Matrix2::operator+(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opAdd(const Matrix2&in) const", AS_METHODPR(Matrix2, operator+, (const Matrix2&) const, Matrix2), AS_CALL_THISCALL);
    // Matrix2 Matrix2::operator-(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opSub(const Matrix2&in) const", AS_METHODPR(Matrix2, operator-, (const Matrix2&) const, Matrix2), AS_CALL_THISCALL);
    // Matrix2& Matrix2::operator=(const Matrix2& rhs) noexcept=default | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2& opAssign(const Matrix2&in)", AS_METHODPR(Matrix2, operator=, (const Matrix2&), Matrix2&), AS_CALL_THISCALL);
    // bool Matrix2::operator==(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool opEquals(const Matrix2&in) const", AS_METHODPR(Matrix2, operator==, (const Matrix2&) const, bool), AS_CALL_THISCALL);
    // Vector2 Matrix2::Scale() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Vector2 Scale() const", AS_METHODPR(Matrix2, Scale, () const, Vector2), AS_CALL_THISCALL);
    // Matrix2 Matrix2::Scaled(const Vector2& scale) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Scaled(const Vector2&in) const", AS_METHODPR(Matrix2, Scaled, (const Vector2&) const, Matrix2), AS_CALL_THISCALL);
    // void Matrix2::SetScale(const Vector2& scale) | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "void SetScale(const Vector2&in)", AS_METHODPR(Matrix2, SetScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void Matrix2::SetScale(float scale) | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "void SetScale(float)", AS_METHODPR(Matrix2, SetScale, (float), void), AS_CALL_THISCALL);
    // String Matrix2::ToString() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "String ToString() const", AS_METHODPR(Matrix2, ToString, () const, String), AS_CALL_THISCALL);
    // Matrix2 Matrix2::Transpose() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Transpose() const", AS_METHODPR(Matrix2, Transpose, () const, Matrix2), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Matrix2
    REGISTER_MANUAL_PART_Matrix2(Matrix2, "Matrix2")
#endif

    // const Matrix3 Matrix3::IDENTITY | File: ../Math/Matrix3.h
    engine->SetDefaultNamespace("Matrix3");
    engine->RegisterGlobalProperty("const Matrix3 IDENTITY", (void*)&Matrix3::IDENTITY);
    engine->SetDefaultNamespace("");
    // float Matrix3::m00_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m00", offsetof(Matrix3, m00_));
    // float Matrix3::m01_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m01", offsetof(Matrix3, m01_));
    // float Matrix3::m02_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m02", offsetof(Matrix3, m02_));
    // float Matrix3::m10_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m10", offsetof(Matrix3, m10_));
    // float Matrix3::m11_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m11", offsetof(Matrix3, m11_));
    // float Matrix3::m12_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m12", offsetof(Matrix3, m12_));
    // float Matrix3::m20_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m20", offsetof(Matrix3, m20_));
    // float Matrix3::m21_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m21", offsetof(Matrix3, m21_));
    // float Matrix3::m22_ | File: ../Math/Matrix3.h
    engine->RegisterObjectProperty("Matrix3", "float m22", offsetof(Matrix3, m22_));
    // const Matrix3 Matrix3::ZERO | File: ../Math/Matrix3.h
    engine->SetDefaultNamespace("Matrix3");
    engine->RegisterGlobalProperty("const Matrix3 ZERO", (void*)&Matrix3::ZERO);
    engine->SetDefaultNamespace("");
    // static void Matrix3::BulkTranspose(float* dest, const float* src, unsigned count) | File: ../Math/Matrix3.h
    // Error: type "float*" can not automatically bind
    // Vector3 Matrix3::Column(unsigned j) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 Column(uint) const", AS_METHODPR(Matrix3, Column, (unsigned) const, Vector3), AS_CALL_THISCALL);
    // const float* Matrix3::Data() const | File: ../Math/Matrix3.h
    // Error: type "const float*" can not automatically bind
    // float Matrix3::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "float Element(uint, uint) const", AS_METHODPR(Matrix3, Element, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // bool Matrix3::Equals(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool Equals(const Matrix3&in) const", AS_METHODPR(Matrix3, Equals, (const Matrix3&) const, bool), AS_CALL_THISCALL);
    // Matrix3 Matrix3::Inverse() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Inverse() const", AS_METHODPR(Matrix3, Inverse, () const, Matrix3), AS_CALL_THISCALL);
    // bool Matrix3::IsInf() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool IsInf() const", AS_METHODPR(Matrix3, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Matrix3::IsNaN() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool IsNaN() const", AS_METHODPR(Matrix3, IsNaN, () const, bool), AS_CALL_THISCALL);
    // Matrix3::Matrix3(const Matrix3& matrix) noexcept=default | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix3_Matrix3_Matrix3), AS_CALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix3_Matrix3_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3::Matrix3(const float* data) noexcept | File: ../Math/Matrix3.h
    // Error: type "const float*" can not automatically bind
    // Vector3 Matrix3::operator*(const Vector3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 opMul(const Vector3&in) const", AS_METHODPR(Matrix3, operator*, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Matrix3 Matrix3::operator*(float rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(float) const", AS_METHODPR(Matrix3, operator*, (float) const, Matrix3), AS_CALL_THISCALL);
    // Matrix3 Matrix3::operator*(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(const Matrix3&in) const", AS_METHODPR(Matrix3, operator*, (const Matrix3&) const, Matrix3), AS_CALL_THISCALL);
    // Matrix3 Matrix3::operator+(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opAdd(const Matrix3&in) const", AS_METHODPR(Matrix3, operator+, (const Matrix3&) const, Matrix3), AS_CALL_THISCALL);
    // Matrix3 Matrix3::operator-(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opSub(const Matrix3&in) const", AS_METHODPR(Matrix3, operator-, (const Matrix3&) const, Matrix3), AS_CALL_THISCALL);
    // Matrix3& Matrix3::operator=(const Matrix3& rhs) noexcept=default | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3& opAssign(const Matrix3&in)", AS_METHODPR(Matrix3, operator=, (const Matrix3&), Matrix3&), AS_CALL_THISCALL);
    // bool Matrix3::operator==(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool opEquals(const Matrix3&in) const", AS_METHODPR(Matrix3, operator==, (const Matrix3&) const, bool), AS_CALL_THISCALL);
    // Vector3 Matrix3::Row(unsigned i) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 Row(uint) const", AS_METHODPR(Matrix3, Row, (unsigned) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Matrix3::Scale() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 Scale() const", AS_METHODPR(Matrix3, Scale, () const, Vector3), AS_CALL_THISCALL);
    // Matrix3 Matrix3::Scaled(const Vector3& scale) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Scaled(const Vector3&in) const", AS_METHODPR(Matrix3, Scaled, (const Vector3&) const, Matrix3), AS_CALL_THISCALL);
    // void Matrix3::SetScale(const Vector3& scale) | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "void SetScale(const Vector3&in)", AS_METHODPR(Matrix3, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Matrix3::SetScale(float scale) | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "void SetScale(float)", AS_METHODPR(Matrix3, SetScale, (float), void), AS_CALL_THISCALL);
    // Vector3 Matrix3::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 SignedScale(const Matrix3&in) const", AS_METHODPR(Matrix3, SignedScale, (const Matrix3&) const, Vector3), AS_CALL_THISCALL);
    // String Matrix3::ToString() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "String ToString() const", AS_METHODPR(Matrix3, ToString, () const, String), AS_CALL_THISCALL);
    // Matrix3 Matrix3::Transpose() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Transpose() const", AS_METHODPR(Matrix3, Transpose, () const, Matrix3), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Matrix3
    REGISTER_MANUAL_PART_Matrix3(Matrix3, "Matrix3")
#endif

    // const Matrix3x4 Matrix3x4::IDENTITY | File: ../Math/Matrix3x4.h
    engine->SetDefaultNamespace("Matrix3x4");
    engine->RegisterGlobalProperty("const Matrix3x4 IDENTITY", (void*)&Matrix3x4::IDENTITY);
    engine->SetDefaultNamespace("");
    // float Matrix3x4::m00_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m00", offsetof(Matrix3x4, m00_));
    // float Matrix3x4::m01_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m01", offsetof(Matrix3x4, m01_));
    // float Matrix3x4::m02_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m02", offsetof(Matrix3x4, m02_));
    // float Matrix3x4::m03_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m03", offsetof(Matrix3x4, m03_));
    // float Matrix3x4::m10_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m10", offsetof(Matrix3x4, m10_));
    // float Matrix3x4::m11_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m11", offsetof(Matrix3x4, m11_));
    // float Matrix3x4::m12_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m12", offsetof(Matrix3x4, m12_));
    // float Matrix3x4::m13_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m13", offsetof(Matrix3x4, m13_));
    // float Matrix3x4::m20_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m20", offsetof(Matrix3x4, m20_));
    // float Matrix3x4::m21_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m21", offsetof(Matrix3x4, m21_));
    // float Matrix3x4::m22_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m22", offsetof(Matrix3x4, m22_));
    // float Matrix3x4::m23_ | File: ../Math/Matrix3x4.h
    engine->RegisterObjectProperty("Matrix3x4", "float m23", offsetof(Matrix3x4, m23_));
    // const Matrix3x4 Matrix3x4::ZERO | File: ../Math/Matrix3x4.h
    engine->SetDefaultNamespace("Matrix3x4");
    engine->RegisterGlobalProperty("const Matrix3x4 ZERO", (void*)&Matrix3x4::ZERO);
    engine->SetDefaultNamespace("");
    // Vector3 Matrix3x4::Column(unsigned j) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Column(uint) const", AS_METHODPR(Matrix3x4, Column, (unsigned) const, Vector3), AS_CALL_THISCALL);
    // const float* Matrix3x4::Data() const | File: ../Math/Matrix3x4.h
    // Error: type "const float*" can not automatically bind
    // void Matrix3x4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", AS_METHODPR(Matrix3x4, Decompose, (Vector3&, Quaternion&, Vector3&) const, void), AS_CALL_THISCALL);
    // float Matrix3x4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "float Element(uint, uint) const", AS_METHODPR(Matrix3x4, Element, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // bool Matrix3x4::Equals(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool Equals(const Matrix3x4&in) const", AS_METHODPR(Matrix3x4, Equals, (const Matrix3x4&) const, bool), AS_CALL_THISCALL);
    // Matrix3x4 Matrix3x4::Inverse() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 Inverse() const", AS_METHODPR(Matrix3x4, Inverse, () const, Matrix3x4), AS_CALL_THISCALL);
    // bool Matrix3x4::IsInf() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool IsInf() const", AS_METHODPR(Matrix3x4, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Matrix3x4::IsNaN() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool IsNaN() const", AS_METHODPR(Matrix3x4, IsNaN, () const, bool), AS_CALL_THISCALL);
    // Matrix3x4::Matrix3x4(const Matrix3x4& matrix) noexcept=default | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_Matrix3x4), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix3& matrix) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_Matrix3), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix4& matrix) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_Matrix4), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_float_float_float_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const float* data) noexcept | File: ../Math/Matrix3x4.h
    // Error: type "const float*" can not automatically bind
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_Vector3_Quaternion_float), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Matrix3x4_Matrix3x4_Vector3_Quaternion_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Vector3 Matrix3x4::operator*(const Vector3& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector3&in) const", AS_METHODPR(Matrix3x4, operator*, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Matrix3x4::operator*(const Vector4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector4&in) const", AS_METHODPR(Matrix3x4, operator*, (const Vector4&) const, Vector3), AS_CALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(float rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(float) const", AS_METHODPR(Matrix3x4, operator*, (float) const, Matrix3x4), AS_CALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(const Matrix3x4&in) const", AS_METHODPR(Matrix3x4, operator*, (const Matrix3x4&) const, Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Matrix3x4::operator*(const Matrix4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 opMul(const Matrix4&in) const", AS_METHODPR(Matrix3x4, operator*, (const Matrix4&) const, Matrix4), AS_CALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator+(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opAdd(const Matrix3x4&in) const", AS_METHODPR(Matrix3x4, operator+, (const Matrix3x4&) const, Matrix3x4), AS_CALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator-(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opSub(const Matrix3x4&in) const", AS_METHODPR(Matrix3x4, operator-, (const Matrix3x4&) const, Matrix3x4), AS_CALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3x4& rhs) noexcept=default | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3x4&in)", AS_METHODPR(Matrix3x4, operator=, (const Matrix3x4&), Matrix3x4&), AS_CALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3& rhs) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3&in)", AS_METHODPR(Matrix3x4, operator=, (const Matrix3&), Matrix3x4&), AS_CALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix4& rhs) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix4&in)", AS_METHODPR(Matrix3x4, operator=, (const Matrix4&), Matrix3x4&), AS_CALL_THISCALL);
    // bool Matrix3x4::operator==(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool opEquals(const Matrix3x4&in) const", AS_METHODPR(Matrix3x4, operator==, (const Matrix3x4&) const, bool), AS_CALL_THISCALL);
    // Quaternion Matrix3x4::Rotation() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Quaternion Rotation() const", AS_METHODPR(Matrix3x4, Rotation, () const, Quaternion), AS_CALL_THISCALL);
    // Matrix3 Matrix3x4::RotationMatrix() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 RotationMatrix() const", AS_METHODPR(Matrix3x4, RotationMatrix, () const, Matrix3), AS_CALL_THISCALL);
    // Vector4 Matrix3x4::Row(unsigned i) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector4 Row(uint) const", AS_METHODPR(Matrix3x4, Row, (unsigned) const, Vector4), AS_CALL_THISCALL);
    // Vector3 Matrix3x4::Scale() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Scale() const", AS_METHODPR(Matrix3x4, Scale, () const, Vector3), AS_CALL_THISCALL);
    // void Matrix3x4::SetRotation(const Matrix3& rotation) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetRotation(const Matrix3&in)", AS_METHODPR(Matrix3x4, SetRotation, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Matrix3x4::SetScale(const Vector3& scale) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(const Vector3&in)", AS_METHODPR(Matrix3x4, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Matrix3x4::SetScale(float scale) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(float)", AS_METHODPR(Matrix3x4, SetScale, (float), void), AS_CALL_THISCALL);
    // void Matrix3x4::SetTranslation(const Vector3& translation) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetTranslation(const Vector3&in)", AS_METHODPR(Matrix3x4, SetTranslation, (const Vector3&), void), AS_CALL_THISCALL);
    // Vector3 Matrix3x4::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 SignedScale(const Matrix3&in) const", AS_METHODPR(Matrix3x4, SignedScale, (const Matrix3&) const, Vector3), AS_CALL_THISCALL);
    // Matrix3 Matrix3x4::ToMatrix3() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 ToMatrix3() const", AS_METHODPR(Matrix3x4, ToMatrix3, () const, Matrix3), AS_CALL_THISCALL);
    // Matrix4 Matrix3x4::ToMatrix4() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 ToMatrix4() const", AS_METHODPR(Matrix3x4, ToMatrix4, () const, Matrix4), AS_CALL_THISCALL);
    // String Matrix3x4::ToString() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "String ToString() const", AS_METHODPR(Matrix3x4, ToString, () const, String), AS_CALL_THISCALL);
    // Vector3 Matrix3x4::Translation() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Translation() const", AS_METHODPR(Matrix3x4, Translation, () const, Vector3), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Matrix3x4
    REGISTER_MANUAL_PART_Matrix3x4(Matrix3x4, "Matrix3x4")
#endif

    // const Matrix4 Matrix4::IDENTITY | File: ../Math/Matrix4.h
    engine->SetDefaultNamespace("Matrix4");
    engine->RegisterGlobalProperty("const Matrix4 IDENTITY", (void*)&Matrix4::IDENTITY);
    engine->SetDefaultNamespace("");
    // float Matrix4::m00_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m00", offsetof(Matrix4, m00_));
    // float Matrix4::m01_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m01", offsetof(Matrix4, m01_));
    // float Matrix4::m02_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m02", offsetof(Matrix4, m02_));
    // float Matrix4::m03_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m03", offsetof(Matrix4, m03_));
    // float Matrix4::m10_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m10", offsetof(Matrix4, m10_));
    // float Matrix4::m11_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m11", offsetof(Matrix4, m11_));
    // float Matrix4::m12_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m12", offsetof(Matrix4, m12_));
    // float Matrix4::m13_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m13", offsetof(Matrix4, m13_));
    // float Matrix4::m20_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m20", offsetof(Matrix4, m20_));
    // float Matrix4::m21_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m21", offsetof(Matrix4, m21_));
    // float Matrix4::m22_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m22", offsetof(Matrix4, m22_));
    // float Matrix4::m23_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m23", offsetof(Matrix4, m23_));
    // float Matrix4::m30_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m30", offsetof(Matrix4, m30_));
    // float Matrix4::m31_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m31", offsetof(Matrix4, m31_));
    // float Matrix4::m32_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m32", offsetof(Matrix4, m32_));
    // float Matrix4::m33_ | File: ../Math/Matrix4.h
    engine->RegisterObjectProperty("Matrix4", "float m33", offsetof(Matrix4, m33_));
    // const Matrix4 Matrix4::ZERO | File: ../Math/Matrix4.h
    engine->SetDefaultNamespace("Matrix4");
    engine->RegisterGlobalProperty("const Matrix4 ZERO", (void*)&Matrix4::ZERO);
    engine->SetDefaultNamespace("");
    // static void Matrix4::BulkTranspose(float* dest, const float* src, unsigned count) | File: ../Math/Matrix4.h
    // Error: type "float*" can not automatically bind
    // Vector4 Matrix4::Column(unsigned j) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector4 Column(uint) const", AS_METHODPR(Matrix4, Column, (unsigned) const, Vector4), AS_CALL_THISCALL);
    // const float* Matrix4::Data() const | File: ../Math/Matrix4.h
    // Error: type "const float*" can not automatically bind
    // void Matrix4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", AS_METHODPR(Matrix4, Decompose, (Vector3&, Quaternion&, Vector3&) const, void), AS_CALL_THISCALL);
    // float Matrix4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "float Element(uint, uint) const", AS_METHODPR(Matrix4, Element, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // bool Matrix4::Equals(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool Equals(const Matrix4&in) const", AS_METHODPR(Matrix4, Equals, (const Matrix4&) const, bool), AS_CALL_THISCALL);
    // Matrix4 Matrix4::Inverse() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Inverse() const", AS_METHODPR(Matrix4, Inverse, () const, Matrix4), AS_CALL_THISCALL);
    // bool Matrix4::IsInf() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool IsInf() const", AS_METHODPR(Matrix4, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Matrix4::IsNaN() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool IsNaN() const", AS_METHODPR(Matrix4, IsNaN, () const, bool), AS_CALL_THISCALL);
    // Matrix4::Matrix4(const Matrix4& matrix) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", AS_FUNCTION_OBJFIRST(Matrix4_Matrix4_Matrix4), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix4::Matrix4(const Matrix3& matrix) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Matrix4_Matrix4_Matrix3), AS_CALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", AS_FUNCTION_OBJFIRST(Matrix4_Matrix4_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Matrix4::Matrix4(const float* data) noexcept | File: ../Math/Matrix4.h
    // Error: type "const float*" can not automatically bind
    // Vector3 Matrix4::operator*(const Vector3& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 opMul(const Vector3&in) const", AS_METHODPR(Matrix4, operator*, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector4 Matrix4::operator*(const Vector4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector4 opMul(const Vector4&in) const", AS_METHODPR(Matrix4, operator*, (const Vector4&) const, Vector4), AS_CALL_THISCALL);
    // Matrix4 Matrix4::operator*(float rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(float) const", AS_METHODPR(Matrix4, operator*, (float) const, Matrix4), AS_CALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix4&in) const", AS_METHODPR(Matrix4, operator*, (const Matrix4&) const, Matrix4), AS_CALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix3x4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix3x4&in) const", AS_METHODPR(Matrix4, operator*, (const Matrix3x4&) const, Matrix4), AS_CALL_THISCALL);
    // Matrix4 Matrix4::operator+(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opAdd(const Matrix4&in) const", AS_METHODPR(Matrix4, operator+, (const Matrix4&) const, Matrix4), AS_CALL_THISCALL);
    // Matrix4 Matrix4::operator-(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opSub(const Matrix4&in) const", AS_METHODPR(Matrix4, operator-, (const Matrix4&) const, Matrix4), AS_CALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix4& rhs) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix4&in)", AS_METHODPR(Matrix4, operator=, (const Matrix4&), Matrix4&), AS_CALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix3& rhs) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix3&in)", AS_METHODPR(Matrix4, operator=, (const Matrix3&), Matrix4&), AS_CALL_THISCALL);
    // bool Matrix4::operator==(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool opEquals(const Matrix4&in) const", AS_METHODPR(Matrix4, operator==, (const Matrix4&) const, bool), AS_CALL_THISCALL);
    // Quaternion Matrix4::Rotation() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Quaternion Rotation() const", AS_METHODPR(Matrix4, Rotation, () const, Quaternion), AS_CALL_THISCALL);
    // Matrix3 Matrix4::RotationMatrix() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix3 RotationMatrix() const", AS_METHODPR(Matrix4, RotationMatrix, () const, Matrix3), AS_CALL_THISCALL);
    // Vector4 Matrix4::Row(unsigned i) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector4 Row(uint) const", AS_METHODPR(Matrix4, Row, (unsigned) const, Vector4), AS_CALL_THISCALL);
    // Vector3 Matrix4::Scale() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 Scale() const", AS_METHODPR(Matrix4, Scale, () const, Vector3), AS_CALL_THISCALL);
    // void Matrix4::SetRotation(const Matrix3& rotation) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetRotation(const Matrix3&in)", AS_METHODPR(Matrix4, SetRotation, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Matrix4::SetScale(const Vector3& scale) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetScale(const Vector3&in)", AS_METHODPR(Matrix4, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Matrix4::SetScale(float scale) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetScale(float)", AS_METHODPR(Matrix4, SetScale, (float), void), AS_CALL_THISCALL);
    // void Matrix4::SetTranslation(const Vector3& translation) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetTranslation(const Vector3&in)", AS_METHODPR(Matrix4, SetTranslation, (const Vector3&), void), AS_CALL_THISCALL);
    // Vector3 Matrix4::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 SignedScale(const Matrix3&in) const", AS_METHODPR(Matrix4, SignedScale, (const Matrix3&) const, Vector3), AS_CALL_THISCALL);
    // Matrix3 Matrix4::ToMatrix3() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix3 ToMatrix3() const", AS_METHODPR(Matrix4, ToMatrix3, () const, Matrix3), AS_CALL_THISCALL);
    // String Matrix4::ToString() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "String ToString() const", AS_METHODPR(Matrix4, ToString, () const, String), AS_CALL_THISCALL);
    // Vector3 Matrix4::Translation() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 Translation() const", AS_METHODPR(Matrix4, Translation, () const, Vector3), AS_CALL_THISCALL);
    // Matrix4 Matrix4::Transpose() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Transpose() const", AS_METHODPR(Matrix4, Transpose, () const, Matrix4), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Matrix4
    REGISTER_MANUAL_PART_Matrix4(Matrix4, "Matrix4")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddChild(UIElement@+)", AS_METHODPR(Menu, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Menu, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTag(const String&in)", AS_METHODPR(Menu, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Menu, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Menu_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AdjustScissor(IntRect&)", AS_METHODPR(Menu, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void AllocateNetworkState()", AS_METHODPR(Menu, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void ApplyAttributes()", AS_METHODPR(Menu, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void BringToFront()", AS_METHODPR(Menu, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Menu, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void DisableLayoutUpdate()", AS_METHODPR(Menu, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Menu, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void EnableLayoutUpdate()", AS_METHODPR(Menu, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Menu, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint FindChild(UIElement@+) const", AS_METHODPR(Menu, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // int Menu::GetAcceleratorKey() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "int GetAcceleratorKey() const", AS_METHODPR(Menu, GetAcceleratorKey, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorKey() const", AS_METHODPR(Menu, GetAcceleratorKey, () const, int), AS_CALL_THISCALL);
    // int Menu::GetAcceleratorQualifiers() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "int GetAcceleratorQualifiers() const", AS_METHODPR(Menu, GetAcceleratorQualifiers, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorQualifiers() const", AS_METHODPR(Menu, GetAcceleratorQualifiers, () const, int), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool GetAnimationEnabled() const", AS_METHODPR(Menu, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_animationEnabled() const", AS_METHODPR(Menu, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const String& GetAppliedStyle() const", AS_METHODPR(Menu, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_style() const", AS_METHODPR(Menu, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttribute(uint) const", AS_METHODPR(Menu, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Variant get_attributes(uint) const", AS_METHODPR(Menu, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttribute(const String&in) const", AS_METHODPR(Menu, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Menu, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Menu, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Menu, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Menu, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Menu, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Menu, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Menu, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Button.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "BlendMode GetBlendMode() const", AS_METHODPR(Menu, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "BlendMode get_blendMode() const", AS_METHODPR(Menu, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool GetBlockEvents() const", AS_METHODPR(Menu, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetBorder() const", AS_METHODPR(Menu, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_border() const", AS_METHODPR(Menu, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetBringToBack() const", AS_METHODPR(Menu, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_bringToBack() const", AS_METHODPR(Menu, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetBringToFront() const", AS_METHODPR(Menu, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_bringToFront() const", AS_METHODPR(Menu, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const String& GetCategory() const", AS_METHODPR(Menu, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_category() const", AS_METHODPR(Menu, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(uint) const", AS_METHODPR(Menu, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_children(uint) const", AS_METHODPR(Menu, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Menu, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Menu, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetChildOffset() const", AS_METHODPR(Menu, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_childOffset() const", AS_METHODPR(Menu, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Menu_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Menu_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Menu_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetClipBorder() const", AS_METHODPR(Menu, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_clipBorder() const", AS_METHODPR(Menu, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetClipChildren() const", AS_METHODPR(Menu, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_clipChildren() const", AS_METHODPR(Menu, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetColor(Corner) const", AS_METHODPR(Menu, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Color& get_colors(Corner) const", AS_METHODPR(Menu, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetColorAttr() const", AS_METHODPR(Menu, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntRect GetCombinedScreenRect()", AS_METHODPR(Menu, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "IntRect get_combinedScreenRect()", AS_METHODPR(Menu, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Menu, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetDerivedColor() const", AS_METHODPR(Menu, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "float GetDerivedOpacity() const", AS_METHODPR(Menu, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_derivedOpacity() const", AS_METHODPR(Menu, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(Menu, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_disabledOffset() const", AS_METHODPR(Menu, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Menu, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Menu, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint GetDragButtonCount() const", AS_METHODPR(Menu, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_dragButtonCount() const", AS_METHODPR(Menu, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Menu, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Menu, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Menu, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Menu, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetEnableAnchor() const", AS_METHODPR(Menu, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enableAnchor() const", AS_METHODPR(Menu, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "VariantMap& GetEventDataMap() const", AS_METHODPR(Menu, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "Object@+ GetEventSender() const", AS_METHODPR(Menu, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "FocusMode GetFocusMode() const", AS_METHODPR(Menu, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "FocusMode get_focusMode() const", AS_METHODPR(Menu, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Menu, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Menu, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Menu, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const VariantMap& get_globalVars() const", AS_METHODPR(Menu, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetHeight() const", AS_METHODPR(Menu, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_height() const", AS_METHODPR(Menu, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Menu, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Menu, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetHoverOffset() const", AS_METHODPR(Menu, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_hoverOffset() const", AS_METHODPR(Menu, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetImageBorder() const", AS_METHODPR(Menu, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_imageBorder() const", AS_METHODPR(Menu, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetImageRect() const", AS_METHODPR(Menu, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_imageRect() const", AS_METHODPR(Menu, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndent() const", AS_METHODPR(Menu, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indent() const", AS_METHODPR(Menu, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndentSpacing() const", AS_METHODPR(Menu, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indentSpacing() const", AS_METHODPR(Menu, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndentWidth() const", AS_METHODPR(Menu, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indentWidth() const", AS_METHODPR(Menu, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Menu, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Menu, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_layoutBorder() const", AS_METHODPR(Menu, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetLayoutElementMaxSize() const", AS_METHODPR(Menu, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Menu, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Menu, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "LayoutMode GetLayoutMode() const", AS_METHODPR(Menu, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "LayoutMode get_layoutMode() const", AS_METHODPR(Menu, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetLayoutSpacing() const", AS_METHODPR(Menu, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_layoutSpacing() const", AS_METHODPR(Menu, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "Material@+ GetMaterial() const", AS_METHODPR(Menu, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Material@+ get_material() const", AS_METHODPR(Menu, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Menu, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Menu, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_maxAnchor() const", AS_METHODPR(Menu, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMaxHeight() const", AS_METHODPR(Menu, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_maxHeight() const", AS_METHODPR(Menu, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Menu, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_maxOffset() const", AS_METHODPR(Menu, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMaxSize() const", AS_METHODPR(Menu, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_maxSize() const", AS_METHODPR(Menu, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMaxWidth() const", AS_METHODPR(Menu, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_maxWidth() const", AS_METHODPR(Menu, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetMinAnchor() const", AS_METHODPR(Menu, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_minAnchor() const", AS_METHODPR(Menu, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMinHeight() const", AS_METHODPR(Menu, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_minHeight() const", AS_METHODPR(Menu, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMinOffset() const", AS_METHODPR(Menu, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_minOffset() const", AS_METHODPR(Menu, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMinSize() const", AS_METHODPR(Menu, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_minSize() const", AS_METHODPR(Menu, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMinWidth() const", AS_METHODPR(Menu, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_minWidth() const", AS_METHODPR(Menu, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const String& GetName() const", AS_METHODPR(Menu, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_name() const", AS_METHODPR(Menu, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "uint GetNumAttributes() const", AS_METHODPR(Menu, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_numAttributes() const", AS_METHODPR(Menu, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint GetNumChildren(bool = false) const", AS_METHODPR(Menu, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_numChildren(bool = false) const", AS_METHODPR(Menu, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "uint GetNumNetworkAttributes() const", AS_METHODPR(Menu, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Menu, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Menu, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Menu, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "float GetOpacity() const", AS_METHODPR(Menu, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_opacity() const", AS_METHODPR(Menu, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetParent() const", AS_METHODPR(Menu, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_parent() const", AS_METHODPR(Menu, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetPivot() const", AS_METHODPR(Menu, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_pivot() const", AS_METHODPR(Menu, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // UIElement* Menu::GetPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetPopup() const", AS_METHODPR(Menu, GetPopup, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_popup() const", AS_METHODPR(Menu, GetPopup, () const, UIElement*), AS_CALL_THISCALL);
    // const IntVector2& Menu::GetPopupOffset() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPopupOffset() const", AS_METHODPR(Menu, GetPopupOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_popupOffset() const", AS_METHODPR(Menu, GetPopupOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPosition() const", AS_METHODPR(Menu, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_position() const", AS_METHODPR(Menu, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPressedChildOffset() const", AS_METHODPR(Menu, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_pressedChildOffset() const", AS_METHODPR(Menu, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPressedOffset() const", AS_METHODPR(Menu, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_pressedOffset() const", AS_METHODPR(Menu, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetPriority() const", AS_METHODPR(Menu, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_priority() const", AS_METHODPR(Menu, GetPriority, () const, int), AS_CALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "float GetRepeatDelay() const", AS_METHODPR(Menu, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_repeatDelay() const", AS_METHODPR(Menu, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "float GetRepeatRate() const", AS_METHODPR(Menu, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_repeatRate() const", AS_METHODPR(Menu, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetRoot() const", AS_METHODPR(Menu, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_root() const", AS_METHODPR(Menu, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Menu, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_screenPosition() const", AS_METHODPR(Menu, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool Menu::GetShowPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool GetShowPopup() const", AS_METHODPR(Menu, GetShowPopup, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_showPopup() const", AS_METHODPR(Menu, GetShowPopup, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetSize() const", AS_METHODPR(Menu, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_size() const", AS_METHODPR(Menu, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetSortChildren() const", AS_METHODPR(Menu, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_sortChildren() const", AS_METHODPR(Menu, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Menu, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Menu_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Menu", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Menu_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "Texture@+ GetTexture() const", AS_METHODPR(Menu, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Texture@+ get_texture() const", AS_METHODPR(Menu, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetTextureAttr() const", AS_METHODPR(Menu, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "TraversalMode GetTraversalMode() const", AS_METHODPR(Menu, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "TraversalMode get_traversalMode() const", AS_METHODPR(Menu, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "StringHash GetType() const", AS_METHODPR(Menu, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "StringHash get_type() const", AS_METHODPR(Menu, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const String& GetTypeName() const", AS_METHODPR(Menu, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_typeName() const", AS_METHODPR(Menu, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetUseDerivedOpacity() const", AS_METHODPR(Menu, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_useDerivedOpacity() const", AS_METHODPR(Menu, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Menu, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const VariantMap& GetVars() const", AS_METHODPR(Menu, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Menu, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Menu, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetWidth() const", AS_METHODPR(Menu, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_width() const", AS_METHODPR(Menu, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasColorGradient() const", AS_METHODPR(Menu, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_colorGradient() const", AS_METHODPR(Menu, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasEventHandlers() const", AS_METHODPR(Menu, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasFocus() const", AS_METHODPR(Menu, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_focus() const", AS_METHODPR(Menu, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Menu, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Menu, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasTag(const String&in) const", AS_METHODPR(Menu, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Menu, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Menu, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEditable() const", AS_METHODPR(Menu, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_editable() const", AS_METHODPR(Menu, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsElementEventSender() const", AS_METHODPR(Menu, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_elementEventSender() const", AS_METHODPR(Menu, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEnabled() const", AS_METHODPR(Menu, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enabled() const", AS_METHODPR(Menu, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEnabledSelf() const", AS_METHODPR(Menu, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enabledSelf() const", AS_METHODPR(Menu, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedHeight() const", AS_METHODPR(Menu, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedHeight() const", AS_METHODPR(Menu, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedSize() const", AS_METHODPR(Menu, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedSize() const", AS_METHODPR(Menu, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedWidth() const", AS_METHODPR(Menu, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedWidth() const", AS_METHODPR(Menu, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsHovering() const", AS_METHODPR(Menu, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_hovering() const", AS_METHODPR(Menu, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInside(IntVector2, bool)", AS_METHODPR(Menu, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Menu, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Menu, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInternal() const", AS_METHODPR(Menu, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_internal() const", AS_METHODPR(Menu, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "bool IsPressed() const", AS_METHODPR(Menu, IsPressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_pressed() const", AS_METHODPR(Menu, IsPressed, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsSelected() const", AS_METHODPR(Menu, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_selected() const", AS_METHODPR(Menu, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool IsTemporary() const", AS_METHODPR(Menu, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_temporary() const", AS_METHODPR(Menu, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "bool IsTiled() const", AS_METHODPR(Menu, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_tiled() const", AS_METHODPR(Menu, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsVisible() const", AS_METHODPR(Menu, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_visible() const", AS_METHODPR(Menu, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsVisibleEffective() const", AS_METHODPR(Menu, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_visibleEffective() const", AS_METHODPR(Menu, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsWheelHandler() const", AS_METHODPR(Menu, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Menu, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool Load(Deserializer&)", AS_METHODPR(Menu, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Menu, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Menu, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Menu, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void MarkNetworkUpdate()", AS_METHODPR(Menu, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit Menu::Menu(Context* context) | File: ../UI/Menu.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_FACTORY, "Menu@+ f()", AS_FUNCTION(Menu_Menu_Context), AS_CALL_CDECL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Menu, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Menu, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Menu, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Menu, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Menu, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Menu, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Menu, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Menu, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Menu, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Menu, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Menu, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Menu::OnHidePopup() | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnHidePopup()", AS_METHODPR(Menu, OnHidePopup, (), void), AS_CALL_THISCALL);
    // void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Menu, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnIndentSet()", AS_METHODPR(Menu, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Menu, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Menu, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Menu, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Menu, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnSetEditable()", AS_METHODPR(Menu, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void Menu::OnShowPopup() | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnShowPopup()", AS_METHODPR(Menu, OnShowPopup, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnTextInput(const String&in)", AS_METHODPR(Menu, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Menu, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Menu, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Menu, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Menu", "int Refs() const", AS_METHODPR(Menu, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_refs() const", AS_METHODPR(Menu, Refs, () const, int), AS_CALL_THISCALL);
    // static void Menu::RegisterObject(Context* context) | File: ../UI/Menu.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Menu, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void Remove()", AS_METHODPR(Menu, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveAllChildren()", AS_METHODPR(Menu, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveAllTags()", AS_METHODPR(Menu, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Menu, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Menu, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveChildAtIndex(uint)", AS_METHODPR(Menu, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void RemoveInstanceDefault()", AS_METHODPR(Menu, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void RemoveObjectAnimation()", AS_METHODPR(Menu, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool RemoveTag(const String&in)", AS_METHODPR(Menu, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void ResetDeepEnabled()", AS_METHODPR(Menu, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void ResetToDefault()", AS_METHODPR(Menu, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool Save(Serializer&) const", AS_METHODPR(Menu, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SaveDefaultAttributes() const", AS_METHODPR(Menu, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Menu, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Menu::SaveXML(XMLElement& dest) const override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool SaveXML(XMLElement&) const", AS_METHODPR(Menu, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Menu, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SendEvent(StringHash)", AS_METHODPR(Menu, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Menu, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Menu::SetAccelerator(int key, int qualifiers) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetAccelerator(int, int)", AS_METHODPR(Menu, SetAccelerator, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Menu, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAnimationEnabled(bool)", AS_METHODPR(Menu, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_animationEnabled(bool)", AS_METHODPR(Menu, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAnimationTime(float)", AS_METHODPR(Menu, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Menu, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Menu, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Menu, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Menu, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Menu, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Menu, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Menu, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetBlendMode(BlendMode)", AS_METHODPR(Menu, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_blendMode(BlendMode)", AS_METHODPR(Menu, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SetBlockEvents(bool)", AS_METHODPR(Menu, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetBorder(const IntRect&in)", AS_METHODPR(Menu, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_border(const IntRect&in)", AS_METHODPR(Menu, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetBringToBack(bool)", AS_METHODPR(Menu, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_bringToBack(bool)", AS_METHODPR(Menu, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetBringToFront(bool)", AS_METHODPR(Menu, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_bringToFront(bool)", AS_METHODPR(Menu, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Menu, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Menu, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Menu, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetClipChildren(bool)", AS_METHODPR(Menu, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_clipChildren(bool)", AS_METHODPR(Menu, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetColor(const Color&in)", AS_METHODPR(Menu, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_color(const Color&in)", AS_METHODPR(Menu, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetColor(Corner, const Color&in)", AS_METHODPR(Menu, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_colors(Corner, const Color&in)", AS_METHODPR(Menu, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDeepEnabled(bool)", AS_METHODPR(Menu, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Menu, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Menu, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(Menu, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(Menu, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetDisabledOffset(int, int)", AS_METHODPR(Menu, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Menu, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Menu, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEditable(bool)", AS_METHODPR(Menu, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_editable(bool)", AS_METHODPR(Menu, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetElementEventSender(bool)", AS_METHODPR(Menu, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_elementEventSender(bool)", AS_METHODPR(Menu, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnableAnchor(bool)", AS_METHODPR(Menu, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_enableAnchor(bool)", AS_METHODPR(Menu, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnabled(bool)", AS_METHODPR(Menu, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_enabled(bool)", AS_METHODPR(Menu, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnabledRecursive(bool)", AS_METHODPR(Menu, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedHeight(int)", AS_METHODPR(Menu, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Menu, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedSize(int, int)", AS_METHODPR(Menu, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedWidth(int)", AS_METHODPR(Menu, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFocus(bool)", AS_METHODPR(Menu, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_focus(bool)", AS_METHODPR(Menu, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFocusMode(FocusMode)", AS_METHODPR(Menu, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_focusMode(FocusMode)", AS_METHODPR(Menu, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetFullImageRect()", AS_METHODPR(Menu, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Menu, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Menu, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHeight(int)", AS_METHODPR(Menu, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_height(int)", AS_METHODPR(Menu, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Menu, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Menu, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHovering(bool)", AS_METHODPR(Menu, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(Menu, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(Menu, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetHoverOffset(int, int)", AS_METHODPR(Menu, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetImageBorder(const IntRect&in)", AS_METHODPR(Menu, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_imageBorder(const IntRect&in)", AS_METHODPR(Menu, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetImageRect(const IntRect&in)", AS_METHODPR(Menu, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_imageRect(const IntRect&in)", AS_METHODPR(Menu, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetIndent(int)", AS_METHODPR(Menu, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_indent(int)", AS_METHODPR(Menu, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetIndentSpacing(int)", AS_METHODPR(Menu, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_indentSpacing(int)", AS_METHODPR(Menu, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetInstanceDefault(bool)", AS_METHODPR(Menu, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Menu, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetInternal(bool)", AS_METHODPR(Menu, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_internal(bool)", AS_METHODPR(Menu, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Menu, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Menu, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Menu, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Menu, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Menu, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Menu, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutMode(LayoutMode)", AS_METHODPR(Menu, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutSpacing(int)", AS_METHODPR(Menu, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutSpacing(int)", AS_METHODPR(Menu, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetMaterial(Material@+)", AS_METHODPR(Menu, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_material(Material@+)", AS_METHODPR(Menu, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Menu, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Menu, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Menu, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxAnchor(float, float)", AS_METHODPR(Menu, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxHeight(int)", AS_METHODPR(Menu, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxHeight(int)", AS_METHODPR(Menu, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Menu, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Menu, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Menu, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Menu, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxSize(int, int)", AS_METHODPR(Menu, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxWidth(int)", AS_METHODPR(Menu, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxWidth(int)", AS_METHODPR(Menu, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Menu, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Menu, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinAnchor(float, float)", AS_METHODPR(Menu, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinHeight(int)", AS_METHODPR(Menu, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minHeight(int)", AS_METHODPR(Menu, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Menu, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Menu, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Menu, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minSize(const IntVector2&in)", AS_METHODPR(Menu, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinSize(int, int)", AS_METHODPR(Menu, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinWidth(int)", AS_METHODPR(Menu, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minWidth(int)", AS_METHODPR(Menu, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetName(const String&in)", AS_METHODPR(Menu, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_name(const String&in)", AS_METHODPR(Menu, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Menu, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Menu, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Menu, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetOpacity(float)", AS_METHODPR(Menu, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_opacity(float)", AS_METHODPR(Menu, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Menu, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPivot(const Vector2&in)", AS_METHODPR(Menu, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pivot(const Vector2&in)", AS_METHODPR(Menu, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPivot(float, float)", AS_METHODPR(Menu, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void Menu::SetPopup(UIElement* popup) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopup(UIElement@+)", AS_METHODPR(Menu, SetPopup, (UIElement*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popup(UIElement@+)", AS_METHODPR(Menu, SetPopup, (UIElement*), void), AS_CALL_THISCALL);
    // void Menu::SetPopupOffset(const IntVector2& offset) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopupOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPopupOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popupOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPopupOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Menu::SetPopupOffset(int x, int y) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopupOffset(int, int)", AS_METHODPR(Menu, SetPopupOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPosition(const IntVector2&in)", AS_METHODPR(Menu, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_position(const IntVector2&in)", AS_METHODPR(Menu, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPosition(int, int)", AS_METHODPR(Menu, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedChildOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pressedChildOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedChildOffset(int, int)", AS_METHODPR(Menu, SetPressedChildOffset, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pressedOffset(const IntVector2&in)", AS_METHODPR(Menu, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedOffset(int, int)", AS_METHODPR(Menu, SetPressedOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPriority(int)", AS_METHODPR(Menu, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_priority(int)", AS_METHODPR(Menu, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Menu, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeat(float, float)", AS_METHODPR(Menu, SetRepeat, (float, float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeatDelay(float)", AS_METHODPR(Menu, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_repeatDelay(float)", AS_METHODPR(Menu, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeatRate(float)", AS_METHODPR(Menu, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_repeatRate(float)", AS_METHODPR(Menu, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSelected(bool)", AS_METHODPR(Menu, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_selected(bool)", AS_METHODPR(Menu, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSize(const IntVector2&in)", AS_METHODPR(Menu, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_size(const IntVector2&in)", AS_METHODPR(Menu, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSize(int, int)", AS_METHODPR(Menu, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSortChildren(bool)", AS_METHODPR(Menu, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_sortChildren(bool)", AS_METHODPR(Menu, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Menu, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Menu, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Menu, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Menu_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetTemporary(bool)", AS_METHODPR(Menu, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_temporary(bool)", AS_METHODPR(Menu, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTexture(Texture@+)", AS_METHODPR(Menu, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_texture(Texture@+)", AS_METHODPR(Menu, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Menu, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTiled(bool)", AS_METHODPR(Menu, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_tiled(bool)", AS_METHODPR(Menu, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Menu, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_traversalMode(TraversalMode)", AS_METHODPR(Menu, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Menu, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_useDerivedOpacity(bool)", AS_METHODPR(Menu, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Menu, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Menu, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Menu, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVisible(bool)", AS_METHODPR(Menu, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_visible(bool)", AS_METHODPR(Menu, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetWidth(int)", AS_METHODPR(Menu, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_width(int)", AS_METHODPR(Menu, SetWidth, (int), void), AS_CALL_THISCALL);
    // void Menu::ShowPopup(bool enable) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void ShowPopup(bool)", AS_METHODPR(Menu, ShowPopup, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_showPopup(bool)", AS_METHODPR(Menu, ShowPopup, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SortChildren()", AS_METHODPR(Menu, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromAllEvents()", AS_METHODPR(Menu, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Menu_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Menu, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Menu, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Menu, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Menu::Update(float timeStep) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void Update(float)", AS_METHODPR(Menu, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void UpdateLayout()", AS_METHODPR(Menu, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Menu", "int WeakRefs() const", AS_METHODPR(Menu, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_weakRefs() const", AS_METHODPR(Menu, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Menu, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Menu, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Menu, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Button
    REGISTER_MANUAL_PART_Button(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Menu, "Menu")
#endif
#ifdef REGISTER_MANUAL_PART_Menu
    REGISTER_MANUAL_PART_Menu(Menu, "Menu")
#endif
    RegisterSubclass<Button, Menu>(engine, "Button", "Menu");
    RegisterSubclass<BorderImage, Menu>(engine, "BorderImage", "Menu");
    RegisterSubclass<UIElement, Menu>(engine, "UIElement", "Menu");
    RegisterSubclass<Animatable, Menu>(engine, "Animatable", "Menu");
    RegisterSubclass<Serializable, Menu>(engine, "Serializable", "Menu");
    RegisterSubclass<Object, Menu>(engine, "Object", "Menu");
    RegisterSubclass<RefCounted, Menu>(engine, "RefCounted", "Menu");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_ADDREF, "void f()", AS_METHODPR(MessageBox, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool GetBlockEvents() const", AS_METHODPR(MessageBox, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetCategory() const", AS_METHODPR(MessageBox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_category() const", AS_METHODPR(MessageBox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "VariantMap& GetEventDataMap() const", AS_METHODPR(MessageBox, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "Object@+ GetEventSender() const", AS_METHODPR(MessageBox, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(MessageBox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(MessageBox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const VariantMap& GetGlobalVars() const", AS_METHODPR(MessageBox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const VariantMap& get_globalVars() const", AS_METHODPR(MessageBox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const String& MessageBox::GetMessage() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetMessage() const", AS_METHODPR(MessageBox, GetMessage, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_message() const", AS_METHODPR(MessageBox, GetMessage, () const, const String&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(MessageBox, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& MessageBox::GetTitle() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetTitle() const", AS_METHODPR(MessageBox, GetTitle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_title() const", AS_METHODPR(MessageBox, GetTitle, () const, const String&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "StringHash GetType() const", AS_METHODPR(MessageBox, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "StringHash get_type() const", AS_METHODPR(MessageBox, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetTypeName() const", AS_METHODPR(MessageBox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_typeName() const", AS_METHODPR(MessageBox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UIElement* MessageBox::GetWindow() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "UIElement@+ GetWindow() const", AS_METHODPR(MessageBox, GetWindow, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "UIElement@+ get_window() const", AS_METHODPR(MessageBox, GetWindow, () const, UIElement*), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasEventHandlers() const", AS_METHODPR(MessageBox, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(MessageBox, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(MessageBox, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool IsInstanceOf(StringHash) const", AS_METHODPR(MessageBox, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // explicit MessageBox::MessageBox(Context* context, const String& messageString=String::EMPTY, const String& titleString=String::EMPTY, XMLFile* layoutFile=nullptr, XMLFile* styleFile=nullptr) | File: ../UI/MessageBox.h
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_FACTORY, "MessageBox@+ f(const String&in = String::EMPTY, const String&in = String::EMPTY, XMLFile@+ = null, XMLFile@+ = null)", AS_FUNCTION(MessageBox_MessageBox_Context_String_String_XMLFile_XMLFile), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(MessageBox, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("MessageBox", "int Refs() const", AS_METHODPR(MessageBox, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "int get_refs() const", AS_METHODPR(MessageBox, Refs, () const, int), AS_CALL_THISCALL);
    // static void MessageBox::RegisterObject(Context* context) | File: ../UI/MessageBox.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_RELEASE, "void f()", AS_METHODPR(MessageBox, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SendEvent(StringHash)", AS_METHODPR(MessageBox, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(MessageBox, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SetBlockEvents(bool)", AS_METHODPR(MessageBox, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(MessageBox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(MessageBox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void MessageBox::SetMessage(const String& text) | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "void SetMessage(const String&in)", AS_METHODPR(MessageBox, SetMessage, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_message(const String&in)", AS_METHODPR(MessageBox, SetMessage, (const String&), void), AS_CALL_THISCALL);
    // void MessageBox::SetTitle(const String& text) | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "void SetTitle(const String&in)", AS_METHODPR(MessageBox, SetTitle, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_title(const String&in)", AS_METHODPR(MessageBox, SetTitle, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromAllEvents()", AS_METHODPR(MessageBox, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(MessageBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(MessageBox, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(MessageBox, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(MessageBox, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("MessageBox", "int WeakRefs() const", AS_METHODPR(MessageBox, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "int get_weakRefs() const", AS_METHODPR(MessageBox, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(MessageBox, "MessageBox")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(MessageBox, "MessageBox")
#endif
#ifdef REGISTER_MANUAL_PART_MessageBox
    REGISTER_MANUAL_PART_MessageBox(MessageBox, "MessageBox")
#endif
    RegisterSubclass<Object, MessageBox>(engine, "Object", "MessageBox");
    RegisterSubclass<RefCounted, MessageBox>(engine, "RefCounted", "MessageBox");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Model, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Model, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Model, AddRef, (), void), AS_CALL_THISCALL);
    // bool Model::BeginLoad(Deserializer& source) override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool BeginLoad(Deserializer&)", AS_METHODPR(Model, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Model> Model::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Model@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(Model_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // bool Model::EndLoad() override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool EndLoad()", AS_METHODPR(Model, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Model, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool GetBlockEvents() const", AS_METHODPR(Model, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Model::GetBoundingBox() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Model, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Model, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const String& GetCategory() const", AS_METHODPR(Model, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_category() const", AS_METHODPR(Model, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "VariantMap& GetEventDataMap() const", AS_METHODPR(Model, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "Object@+ GetEventSender() const", AS_METHODPR(Model, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Vector<Vector<SharedPtr<Geometry>>>& Model::GetGeometries() const | File: ../Graphics/Model.h
    // Error: type "const Vector<Vector<SharedPtr<Geometry>>>&" can not automatically bind
    // Geometry* Model::GetGeometry(unsigned index, unsigned lodLevel) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Geometry@+ GetGeometry(uint, uint) const", AS_METHODPR(Model, GetGeometry, (unsigned, unsigned) const, Geometry*), AS_CALL_THISCALL);
    // const Vector<PODVector<unsigned>>& Model::GetGeometryBoneMappings() const | File: ../Graphics/Model.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const Vector3& Model::GetGeometryCenter(unsigned index) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "const Vector3& GetGeometryCenter(uint) const", AS_METHODPR(Model, GetGeometryCenter, (unsigned) const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Vector3& get_geometryCenters(uint) const", AS_METHODPR(Model, GetGeometryCenter, (unsigned) const, const Vector3&), AS_CALL_THISCALL);
    // const PODVector<Vector3>& Model::GetGeometryCenters() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<Vector3>@ GetGeometryCenters() const", AS_FUNCTION_OBJFIRST(Model_GetGeometryCenters_void), AS_CALL_CDECL_OBJFIRST);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Model, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Model, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Model, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const VariantMap& get_globalVars() const", AS_METHODPR(Model, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<IndexBuffer>>& Model::GetIndexBuffers() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<IndexBuffer@>@ GetIndexBuffers() const", AS_FUNCTION_OBJFIRST(Model_GetIndexBuffers_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "uint GetMemoryUse() const", AS_METHODPR(Model, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_memoryUse() const", AS_METHODPR(Model, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Model, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Model, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // const ModelMorph* Model::GetMorph(unsigned index) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(const String& name) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(StringHash nameHash) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // unsigned Model::GetMorphRangeCount(unsigned bufferIndex) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetMorphRangeCount(uint) const", AS_METHODPR(Model, GetMorphRangeCount, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // unsigned Model::GetMorphRangeStart(unsigned bufferIndex) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetMorphRangeStart(uint) const", AS_METHODPR(Model, GetMorphRangeStart, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // const Vector<ModelMorph>& Model::GetMorphs() const | File: ../Graphics/Model.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "const String& GetName() const", AS_METHODPR(Model, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_name() const", AS_METHODPR(Model, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "StringHash GetNameHash() const", AS_METHODPR(Model, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned Model::GetNumGeometries() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumGeometries() const", AS_METHODPR(Model, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometries() const", AS_METHODPR(Model, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Model::GetNumGeometryLodLevels(unsigned index) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumGeometryLodLevels(uint) const", AS_METHODPR(Model, GetNumGeometryLodLevels, (unsigned) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometryLodLevels(uint) const", AS_METHODPR(Model, GetNumGeometryLodLevels, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // unsigned Model::GetNumMorphs() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumMorphs() const", AS_METHODPR(Model, GetNumMorphs, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numMorphs() const", AS_METHODPR(Model, GetNumMorphs, () const, unsigned), AS_CALL_THISCALL);
    // Skeleton& Model::GetSkeleton() | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Skeleton& GetSkeleton()", AS_METHODPR(Model, GetSkeleton, (), Skeleton&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "Skeleton& get_skeleton()", AS_METHODPR(Model, GetSkeleton, (), Skeleton&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Model, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "StringHash GetType() const", AS_METHODPR(Model, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "StringHash get_type() const", AS_METHODPR(Model, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const String& GetTypeName() const", AS_METHODPR(Model, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_typeName() const", AS_METHODPR(Model, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "uint GetUseTimer()", AS_METHODPR(Model, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_useTimer()", AS_METHODPR(Model, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // const Vector<SharedPtr<VertexBuffer>>& Model::GetVertexBuffers() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<VertexBuffer@>@ GetVertexBuffers() const", AS_FUNCTION_OBJFIRST(Model_GetVertexBuffers_void), AS_CALL_CDECL_OBJFIRST);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasEventHandlers() const", AS_METHODPR(Model, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool HasMetadata() const", AS_METHODPR(Model, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool get_hasMetadata() const", AS_METHODPR(Model, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Model, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Model, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Model, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool Load(Deserializer&)", AS_METHODPR(Model, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool LoadFile(const String&in)", AS_METHODPR(Model, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool Load(const String&in)", AS_METHODPR(Model, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // explicit Model::Model(Context* context) | File: ../Graphics/Model.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_FACTORY, "Model@+ f()", AS_FUNCTION(Model_Model_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Model, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Model", "int Refs() const", AS_METHODPR(Model, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "int get_refs() const", AS_METHODPR(Model, Refs, () const, int), AS_CALL_THISCALL);
    // static void Model::RegisterObject(Context* context) | File: ../Graphics/Model.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Model, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void RemoveAllMetadata()", AS_METHODPR(Model, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void RemoveMetadata(const String&in)", AS_METHODPR(Model, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void ResetUseTimer()", AS_METHODPR(Model, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool Model::Save(Serializer& dest) const override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool Save(Serializer&) const", AS_METHODPR(Model, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool SaveFile(const String&in) const", AS_METHODPR(Model, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool Save(const String&in) const", AS_METHODPR(Model, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SendEvent(StringHash)", AS_METHODPR(Model, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Model, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Model, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SetBlockEvents(bool)", AS_METHODPR(Model, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Model::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetBoundingBox(const BoundingBox&in)", AS_METHODPR(Model, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_boundingBox(const BoundingBox&in)", AS_METHODPR(Model, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    // bool Model::SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetGeometry(uint, uint, Geometry@+)", AS_METHODPR(Model, SetGeometry, (unsigned, unsigned, Geometry*), bool), AS_CALL_THISCALL);
    // void Model::SetGeometryBoneMappings(const Vector<PODVector<unsigned>>& geometryBoneMappings) | File: ../Graphics/Model.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // bool Model::SetGeometryCenter(unsigned index, const Vector3& center) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetGeometryCenter(uint, const Vector3&in)", AS_METHODPR(Model, SetGeometryCenter, (unsigned, const Vector3&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool set_geometryCenters(uint, const Vector3&in)", AS_METHODPR(Model, SetGeometryCenter, (unsigned, const Vector3&), bool), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Model, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Model, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // bool Model::SetIndexBuffers(const Vector<SharedPtr<IndexBuffer>>& buffers) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetIndexBuffers(Array<IndexBuffer@>@+)", AS_FUNCTION_OBJFIRST(Model_SetIndexBuffers_VectorSharedPtrIndexBuffer), AS_CALL_CDECL_OBJFIRST);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetMemoryUse(uint)", AS_METHODPR(Model, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Model::SetMorphs(const Vector<ModelMorph>& morphs) | File: ../Graphics/Model.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetName(const String&in)", AS_METHODPR(Model, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_name(const String&in)", AS_METHODPR(Model, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Model::SetNumGeometries(unsigned num) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetNumGeometries(uint)", AS_METHODPR(Model, SetNumGeometries, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_numGeometries(uint)", AS_METHODPR(Model, SetNumGeometries, (unsigned), void), AS_CALL_THISCALL);
    // bool Model::SetNumGeometryLodLevels(unsigned index, unsigned num) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetNumGeometryLodLevels(uint, uint)", AS_METHODPR(Model, SetNumGeometryLodLevels, (unsigned, unsigned), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool set_numGeometryLodLevels(uint, uint)", AS_METHODPR(Model, SetNumGeometryLodLevels, (unsigned, unsigned), bool), AS_CALL_THISCALL);
    // void Model::SetSkeleton(const Skeleton& skeleton) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetSkeleton(const Skeleton&in)", AS_METHODPR(Model, SetSkeleton, (const Skeleton&), void), AS_CALL_THISCALL);
    // bool Model::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, const PODVector<unsigned>& morphRangeStarts, const PODVector<unsigned>& morphRangeCounts) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetVertexBuffers(Array<VertexBuffer@>@+, Array<uint>@+, Array<uint>@+)", AS_FUNCTION_OBJFIRST(Model_SetVertexBuffers_VectorSharedPtrVertexBuffer_PODVectorunsigned_PODVectorunsigned), AS_CALL_CDECL_OBJFIRST);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromAllEvents()", AS_METHODPR(Model, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Model_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Model, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Model, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Model, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Model", "int WeakRefs() const", AS_METHODPR(Model, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Model", "int get_weakRefs() const", AS_METHODPR(Model, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Model, "Model")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Model, "Model")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Model, "Model")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Model, "Model")
#endif
#ifdef REGISTER_MANUAL_PART_Model
    REGISTER_MANUAL_PART_Model(Model, "Model")
#endif
    RegisterSubclass<ResourceWithMetadata, Model>(engine, "ResourceWithMetadata", "Model");
    RegisterSubclass<Resource, Model>(engine, "Resource", "Model");
    RegisterSubclass<Object, Model>(engine, "Object", "Model");
    RegisterSubclass<RefCounted, Model>(engine, "RefCounted", "Model");

    // void Mutex::Acquire() | File: ../Core/Mutex.h
    engine->RegisterObjectMethod("Mutex", "void Acquire()", AS_METHODPR(Mutex, Acquire, (), void), AS_CALL_THISCALL);
    // void Mutex::Release() | File: ../Core/Mutex.h
    engine->RegisterObjectMethod("Mutex", "void Release()", AS_METHODPR(Mutex, Release, (), void), AS_CALL_THISCALL);
    // bool Mutex::TryAcquire() | File: ../Core/Mutex.h
    engine->RegisterObjectMethod("Mutex", "bool TryAcquire()", AS_METHODPR(Mutex, TryAcquire, (), bool), AS_CALL_THISCALL);
    // Mutex& Mutex::operator=(const Mutex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Mutex>(engine, "Mutex");
#ifdef REGISTER_MANUAL_PART_Mutex
    REGISTER_MANUAL_PART_Mutex(Mutex, "Mutex")
#endif

    // explicit MutexLock::MutexLock(Mutex& mutex) | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_CONSTRUCT, "void f(Mutex&)", AS_FUNCTION_OBJFIRST(MutexLock_MutexLock_Mutex), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_MutexLock
    REGISTER_MANUAL_PART_MutexLock(MutexLock, "MutexLock")
#endif

#ifdef URHO3D_PHYSICS
    // btPersistentManifold* ManifoldPair::flippedManifold_ | File: ../Physics/PhysicsWorld.h
    // btPersistentManifold* can not be registered
    // btPersistentManifold* ManifoldPair::manifold_ | File: ../Physics/PhysicsWorld.h
    // btPersistentManifold* can not be registered
    // ManifoldPair& ManifoldPair::operator=(const ManifoldPair&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ManifoldPair>(engine, "ManifoldPair");
#ifdef REGISTER_MANUAL_PART_ManifoldPair
    REGISTER_MANUAL_PART_ManifoldPair(ManifoldPair, "ManifoldPair")
#endif
#endif

    // String MaterialShaderParameter::name_ | File: ../Graphics/Material.h
    engine->RegisterObjectProperty("MaterialShaderParameter", "String name", offsetof(MaterialShaderParameter, name_));
    // Variant MaterialShaderParameter::value_ | File: ../Graphics/Material.h
    engine->RegisterObjectProperty("MaterialShaderParameter", "Variant value", offsetof(MaterialShaderParameter, value_));
    // MaterialShaderParameter& MaterialShaderParameter::operator=(const MaterialShaderParameter&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<MaterialShaderParameter>(engine, "MaterialShaderParameter");
#ifdef REGISTER_MANUAL_PART_MaterialShaderParameter
    REGISTER_MANUAL_PART_MaterialShaderParameter(MaterialShaderParameter, "MaterialShaderParameter")
#endif

    // HashMap<unsigned, VertexBufferMorph> ModelMorph::buffers_ | File: ../Graphics/Model.h
    // Error: type "HashMap<unsigned, VertexBufferMorph>" can not automatically bind
    // String ModelMorph::name_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("ModelMorph", "String name", offsetof(ModelMorph, name_));
    // StringHash ModelMorph::nameHash_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("ModelMorph", "StringHash nameHash", offsetof(ModelMorph, nameHash_));
    // float ModelMorph::weight_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("ModelMorph", "float weight", offsetof(ModelMorph, weight_));
    // ModelMorph& ModelMorph::operator=(const ModelMorph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ModelMorph>(engine, "ModelMorph");
#ifdef REGISTER_MANUAL_PART_ModelMorph
    REGISTER_MANUAL_PART_ModelMorph(ModelMorph, "ModelMorph")
#endif

}

}
