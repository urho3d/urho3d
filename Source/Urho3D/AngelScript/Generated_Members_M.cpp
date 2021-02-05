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
    engine->RegisterObjectBehaviour("Material", asBEHAVE_ADDREF, "void f()", asMETHODPR(Material, AddRef, (), void), asCALL_THISCALL);
    // bool Material::BeginLoad(Deserializer& source) override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool BeginLoad(Deserializer&)", asMETHODPR(Material, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Material> Material::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Material@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(Material_Clone_String), asCALL_CDECL_OBJFIRST);
    // bool Material::EndLoad() override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool EndLoad()", asMETHODPR(Material, EndLoad, (), bool), asCALL_THISCALL);
    // bool Material::GetAlphaToCoverage() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetAlphaToCoverage() const", asMETHODPR(Material, GetAlphaToCoverage, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_alphaToCoverage() const", asMETHODPR(Material, GetAlphaToCoverage, () const, bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Material, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // unsigned Material::GetAuxViewFrameNumber() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetAuxViewFrameNumber() const", asMETHODPR(Material, GetAuxViewFrameNumber, () const, unsigned), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool GetBlockEvents() const", asMETHODPR(Material, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const String& GetCategory() const", asMETHODPR(Material, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_category() const", asMETHODPR(Material, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode Material::GetCullMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "CullMode GetCullMode() const", asMETHODPR(Material, GetCullMode, () const, CullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_cullMode() const", asMETHODPR(Material, GetCullMode, () const, CullMode), asCALL_THISCALL);
    // const BiasParameters& Material::GetDepthBias() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const BiasParameters& GetDepthBias() const", asMETHODPR(Material, GetDepthBias, () const, const BiasParameters&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const BiasParameters& get_depthBias() const", asMETHODPR(Material, GetDepthBias, () const, const BiasParameters&), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "VariantMap& GetEventDataMap() const", asMETHODPR(Material, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "Object@+ GetEventSender() const", asMETHODPR(Material, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FillMode Material::GetFillMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "FillMode GetFillMode() const", asMETHODPR(Material, GetFillMode, () const, FillMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "FillMode get_fillMode() const", asMETHODPR(Material, GetFillMode, () const, FillMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Material, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Material, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const VariantMap& GetGlobalVars() const", asMETHODPR(Material, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const VariantMap& get_globalVars() const", asMETHODPR(Material, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Material::GetLineAntiAlias() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetLineAntiAlias() const", asMETHODPR(Material, GetLineAntiAlias, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_lineAntiAlias() const", asMETHODPR(Material, GetLineAntiAlias, () const, bool), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "uint GetMemoryUse() const", asMETHODPR(Material, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_memoryUse() const", asMETHODPR(Material, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "const String& GetName() const", asMETHODPR(Material, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_name() const", asMETHODPR(Material, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "StringHash GetNameHash() const", asMETHODPR(Material, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned Material::GetNumTechniques() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetNumTechniques() const", asMETHODPR(Material, GetNumTechniques, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_numTechniques() const", asMETHODPR(Material, GetNumTechniques, () const, unsigned), asCALL_THISCALL);
    // bool Material::GetOcclusion() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetOcclusion() const", asMETHODPR(Material, GetOcclusion, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_occlusion() const", asMETHODPR(Material, GetOcclusion, () const, bool), asCALL_THISCALL);
    // Pass* Material::GetPass(unsigned index, const String& passName) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Pass@+ GetPass(uint, const String&in) const", asMETHODPR(Material, GetPass, (unsigned, const String&) const, Pass*), asCALL_THISCALL);
    // const String& Material::GetPixelShaderDefines() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const String& GetPixelShaderDefines() const", asMETHODPR(Material, GetPixelShaderDefines, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_pixelShaderDefines() const", asMETHODPR(Material, GetPixelShaderDefines, () const, const String&), asCALL_THISCALL);
    // unsigned char Material::GetRenderOrder() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint8 GetRenderOrder() const", asMETHODPR(Material, GetRenderOrder, () const, unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint8 get_renderOrder() const", asMETHODPR(Material, GetRenderOrder, () const, unsigned char), asCALL_THISCALL);
    // Scene* Material::GetScene() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Scene@+ GetScene() const", asMETHODPR(Material, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Scene@+ get_scene() const", asMETHODPR(Material, GetScene, () const, Scene*), asCALL_THISCALL);
    // const Variant& Material::GetShaderParameter(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const Variant& GetShaderParameter(const String&in) const", asMETHODPR(Material, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const Variant& get_shaderParameters(const String&in) const", asMETHODPR(Material, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    // ValueAnimation* Material::GetShaderParameterAnimation(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "ValueAnimation@+ GetShaderParameterAnimation(const String&in) const", asMETHODPR(Material, GetShaderParameterAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Material::GetShaderParameterAnimationSpeed(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "float GetShaderParameterAnimationSpeed(const String&in) const", asMETHODPR(Material, GetShaderParameterAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Material::GetShaderParameterAnimationWrapMode(const String& name) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "WrapMode GetShaderParameterAnimationWrapMode(const String&in) const", asMETHODPR(Material, GetShaderParameterAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // unsigned Material::GetShaderParameterHash() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "uint GetShaderParameterHash() const", asMETHODPR(Material, GetShaderParameterHash, () const, unsigned), asCALL_THISCALL);
    // const HashMap<StringHash, MaterialShaderParameter>& Material::GetShaderParameters() const | File: ../Graphics/Material.h
    // Error: type "const HashMap<StringHash, MaterialShaderParameter>&" can not automatically bind
    // CullMode Material::GetShadowCullMode() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "CullMode GetShadowCullMode() const", asMETHODPR(Material, GetShadowCullMode, () const, CullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_shadowCullMode() const", asMETHODPR(Material, GetShadowCullMode, () const, CullMode), asCALL_THISCALL);
    // bool Material::GetSpecular() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool GetSpecular() const", asMETHODPR(Material, GetSpecular, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Material, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Technique* Material::GetTechnique(unsigned index) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Technique@+ GetTechnique(uint) const", asMETHODPR(Material, GetTechnique, (unsigned) const, Technique*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Technique@+ get_techniques(uint) const", asMETHODPR(Material, GetTechnique, (unsigned) const, Technique*), asCALL_THISCALL);
    // const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const TechniqueEntry& GetTechniqueEntry(uint) const", asMETHODPR(Material, GetTechniqueEntry, (unsigned) const, const TechniqueEntry&), asCALL_THISCALL);
    // const Vector<TechniqueEntry>& Material::GetTechniques() const | File: ../Graphics/Material.h
    // Error: type "const Vector<TechniqueEntry>&" can not automatically bind
    // Texture* Material::GetTexture(TextureUnit unit) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "Texture@+ GetTexture(TextureUnit) const", asMETHODPR(Material, GetTexture, (TextureUnit) const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Texture@+ get_textures(TextureUnit) const", asMETHODPR(Material, GetTexture, (TextureUnit) const, Texture*), asCALL_THISCALL);
    // const HashMap<TextureUnit, SharedPtr<Texture>>& Material::GetTextures() const | File: ../Graphics/Material.h
    // Error: type "const HashMap<TextureUnit, SharedPtr<Texture>>&" can not automatically bind
    // static String Material::GetTextureUnitName(TextureUnit unit) | File: ../Graphics/Material.h
    engine->SetDefaultNamespace("Material");
    engine->RegisterGlobalFunction("String GetTextureUnitName(TextureUnit)", asFUNCTIONPR(Material::GetTextureUnitName, (TextureUnit), String), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "StringHash GetType() const", asMETHODPR(Material, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "StringHash get_type() const", asMETHODPR(Material, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "const String& GetTypeName() const", asMETHODPR(Material, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_typeName() const", asMETHODPR(Material, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "uint GetUseTimer()", asMETHODPR(Material, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_useTimer()", asMETHODPR(Material, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // const String& Material::GetVertexShaderDefines() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "const String& GetVertexShaderDefines() const", asMETHODPR(Material, GetVertexShaderDefines, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const String& get_vertexShaderDefines() const", asMETHODPR(Material, GetVertexShaderDefines, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasEventHandlers() const", asMETHODPR(Material, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Material, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Material, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "bool IsInstanceOf(StringHash) const", asMETHODPR(Material, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Material::Load(const XMLElement& source) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Load(const XMLElement&in)", asMETHODPR(Material, Load, (const XMLElement&), bool), asCALL_THISCALL);
    // bool Material::Load(const JSONValue& source) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Load(const JSONValue&in)", asMETHODPR(Material, Load, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "bool LoadFile(const String&in)", asMETHODPR(Material, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool Load(const String&in)", asMETHODPR(Material, LoadFile, (const String&), bool), asCALL_THISCALL);
    // void Material::MarkForAuxView(unsigned frameNumber) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void MarkForAuxView(uint)", asMETHODPR(Material, MarkForAuxView, (unsigned), void), asCALL_THISCALL);
    // explicit Material::Material(Context* context) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("Material", asBEHAVE_FACTORY, "Material@+ f()", asFUNCTION(Material_Material_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Material, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // static Variant Material::ParseShaderParameterValue(const String& value) | File: ../Graphics/Material.h
    engine->SetDefaultNamespace("Material");
    engine->RegisterGlobalFunction("Variant ParseShaderParameterValue(const String&in)", asFUNCTIONPR(Material::ParseShaderParameterValue, (const String&), Variant), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Material", "int Refs() const", asMETHODPR(Material, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "int get_refs() const", asMETHODPR(Material, Refs, () const, int), asCALL_THISCALL);
    // static void Material::RegisterObject(Context* context) | File: ../Graphics/Material.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Material", asBEHAVE_RELEASE, "void f()", asMETHODPR(Material, ReleaseRef, (), void), asCALL_THISCALL);
    // void Material::ReleaseShaders() | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void ReleaseShaders()", asMETHODPR(Material, ReleaseShaders, (), void), asCALL_THISCALL);
    // void Material::RemoveShaderParameter(const String& name) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void RemoveShaderParameter(const String&in)", asMETHODPR(Material, RemoveShaderParameter, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void ResetUseTimer()", asMETHODPR(Material, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool Material::Save(Serializer& dest) const override | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(Serializer&) const", asMETHODPR(Material, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool Material::Save(XMLElement& dest) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(XMLElement&) const", asMETHODPR(Material, Save, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool Material::Save(JSONValue& dest) const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "bool Save(JSONValue&) const", asMETHODPR(Material, Save, (JSONValue&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "bool SaveFile(const String&in) const", asMETHODPR(Material, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool Save(const String&in) const", asMETHODPR(Material, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SendEvent(StringHash)", asMETHODPR(Material, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Material, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Material::SetAlphaToCoverage(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetAlphaToCoverage(bool)", asMETHODPR(Material, SetAlphaToCoverage, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_alphaToCoverage(bool)", asMETHODPR(Material, SetAlphaToCoverage, (bool), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Material, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SetBlockEvents(bool)", asMETHODPR(Material, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Material::SetCullMode(CullMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetCullMode(CullMode)", asMETHODPR(Material, SetCullMode, (CullMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_cullMode(CullMode)", asMETHODPR(Material, SetCullMode, (CullMode), void), asCALL_THISCALL);
    // void Material::SetDepthBias(const BiasParameters& parameters) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetDepthBias(const BiasParameters&in)", asMETHODPR(Material, SetDepthBias, (const BiasParameters&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_depthBias(const BiasParameters&in)", asMETHODPR(Material, SetDepthBias, (const BiasParameters&), void), asCALL_THISCALL);
    // void Material::SetFillMode(FillMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetFillMode(FillMode)", asMETHODPR(Material, SetFillMode, (FillMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_fillMode(FillMode)", asMETHODPR(Material, SetFillMode, (FillMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Material, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Material, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Material::SetLineAntiAlias(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetLineAntiAlias(bool)", asMETHODPR(Material, SetLineAntiAlias, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_lineAntiAlias(bool)", asMETHODPR(Material, SetLineAntiAlias, (bool), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetMemoryUse(uint)", asMETHODPR(Material, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Material", "void SetName(const String&in)", asMETHODPR(Material, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_name(const String&in)", asMETHODPR(Material, SetName, (const String&), void), asCALL_THISCALL);
    // void Material::SetNumTechniques(unsigned num) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetNumTechniques(uint)", asMETHODPR(Material, SetNumTechniques, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_numTechniques(uint)", asMETHODPR(Material, SetNumTechniques, (unsigned), void), asCALL_THISCALL);
    // void Material::SetOcclusion(bool enable) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetOcclusion(bool)", asMETHODPR(Material, SetOcclusion, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_occlusion(bool)", asMETHODPR(Material, SetOcclusion, (bool), void), asCALL_THISCALL);
    // void Material::SetPixelShaderDefines(const String& defines) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetPixelShaderDefines(const String&in)", asMETHODPR(Material, SetPixelShaderDefines, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_pixelShaderDefines(const String&in)", asMETHODPR(Material, SetPixelShaderDefines, (const String&), void), asCALL_THISCALL);
    // void Material::SetRenderOrder(unsigned char order) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetRenderOrder(uint8)", asMETHODPR(Material, SetRenderOrder, (unsigned char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_renderOrder(uint8)", asMETHODPR(Material, SetRenderOrder, (unsigned char), void), asCALL_THISCALL);
    // void Material::SetScene(Scene* scene) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetScene(Scene@+)", asMETHODPR(Material, SetScene, (Scene*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_scene(Scene@+)", asMETHODPR(Material, SetScene, (Scene*), void), asCALL_THISCALL);
    // void Material::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameter(const String&in, const Variant&in)", asMETHODPR(Material, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shaderParameters(const String&in, const Variant&in)", asMETHODPR(Material, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    // void Material::SetShaderParameterAnimation(const String& name, ValueAnimation* animation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Material, SetShaderParameterAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Material::SetShaderParameterAnimationSpeed(const String& name, float speed) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimationSpeed(const String&in, float)", asMETHODPR(Material, SetShaderParameterAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Material::SetShaderParameterAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShaderParameterAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Material, SetShaderParameterAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Material::SetShadowCullMode(CullMode mode) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetShadowCullMode(CullMode)", asMETHODPR(Material, SetShadowCullMode, (CullMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shadowCullMode(CullMode)", asMETHODPR(Material, SetShadowCullMode, (CullMode), void), asCALL_THISCALL);
    // void Material::SetTechnique(unsigned index, Technique* tech, MaterialQuality qualityLevel=QUALITY_LOW, float lodDistance=0.0f) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetTechnique(uint, Technique@+, MaterialQuality = QUALITY_LOW, float = 0.0f)", asMETHODPR(Material, SetTechnique, (unsigned, Technique*, MaterialQuality, float), void), asCALL_THISCALL);
    // void Material::SetTexture(TextureUnit unit, Texture* texture) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetTexture(TextureUnit, Texture@+)", asMETHODPR(Material, SetTexture, (TextureUnit, Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_textures(TextureUnit, Texture@+)", asMETHODPR(Material, SetTexture, (TextureUnit, Texture*), void), asCALL_THISCALL);
    // void Material::SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, const Vector2&in)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    // void Material::SetUVTransform(const Vector2& offset, float rotation, float repeat) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, float)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, float), void), asCALL_THISCALL);
    // void Material::SetVertexShaderDefines(const String& defines) | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SetVertexShaderDefines(const String&in)", asMETHODPR(Material, SetVertexShaderDefines, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_vertexShaderDefines(const String&in)", asMETHODPR(Material, SetVertexShaderDefines, (const String&), void), asCALL_THISCALL);
    // void Material::SortTechniques() | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("Material", "void SortTechniques()", asMETHODPR(Material, SortTechniques, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromAllEvents()", asMETHODPR(Material, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Material_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Material, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Material, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Material", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Material, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Material", "int WeakRefs() const", asMETHODPR(Material, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "int get_weakRefs() const", asMETHODPR(Material, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Matrix2", "bool Equals(const Matrix2&in) const", asMETHODPR(Matrix2, Equals, (const Matrix2&) const, bool), asCALL_THISCALL);
    // Matrix2 Matrix2::Inverse() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Inverse() const", asMETHODPR(Matrix2, Inverse, () const, Matrix2), asCALL_THISCALL);
    // bool Matrix2::IsInf() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool IsInf() const", asMETHODPR(Matrix2, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix2::IsNaN() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool IsNaN() const", asMETHODPR(Matrix2, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix2::Matrix2(const Matrix2& matrix) noexcept=default | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", asFUNCTION(Matrix2_Matrix2_Matrix2), asCALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Matrix2_Matrix2_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Matrix2::Matrix2(const float* data) noexcept | File: ../Math/Matrix2.h
    // Error: type "const float*" can not automatically bind
    // Vector2 Matrix2::operator*(const Vector2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Matrix2, operator*, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator*(float rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(float) const", asMETHODPR(Matrix2, operator*, (float) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator*(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(const Matrix2&in) const", asMETHODPR(Matrix2, operator*, (const Matrix2&) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator+(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opAdd(const Matrix2&in) const", asMETHODPR(Matrix2, operator+, (const Matrix2&) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator-(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opSub(const Matrix2&in) const", asMETHODPR(Matrix2, operator-, (const Matrix2&) const, Matrix2), asCALL_THISCALL);
    // Matrix2& Matrix2::operator=(const Matrix2& rhs) noexcept=default | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2& opAssign(const Matrix2&in)", asMETHODPR(Matrix2, operator=, (const Matrix2&), Matrix2&), asCALL_THISCALL);
    // bool Matrix2::operator==(const Matrix2& rhs) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "bool opEquals(const Matrix2&in) const", asMETHODPR(Matrix2, operator==, (const Matrix2&) const, bool), asCALL_THISCALL);
    // Vector2 Matrix2::Scale() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Vector2 Scale() const", asMETHODPR(Matrix2, Scale, () const, Vector2), asCALL_THISCALL);
    // Matrix2 Matrix2::Scaled(const Vector2& scale) const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Scaled(const Vector2&in) const", asMETHODPR(Matrix2, Scaled, (const Vector2&) const, Matrix2), asCALL_THISCALL);
    // void Matrix2::SetScale(const Vector2& scale) | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "void SetScale(const Vector2&in)", asMETHODPR(Matrix2, SetScale, (const Vector2&), void), asCALL_THISCALL);
    // void Matrix2::SetScale(float scale) | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "void SetScale(float)", asMETHODPR(Matrix2, SetScale, (float), void), asCALL_THISCALL);
    // String Matrix2::ToString() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "String ToString() const", asMETHODPR(Matrix2, ToString, () const, String), asCALL_THISCALL);
    // Matrix2 Matrix2::Transpose() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Transpose() const", asMETHODPR(Matrix2, Transpose, () const, Matrix2), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Matrix3", "Vector3 Column(uint) const", asMETHODPR(Matrix3, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // const float* Matrix3::Data() const | File: ../Math/Matrix3.h
    // Error: type "const float*" can not automatically bind
    // float Matrix3::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "float Element(uint, uint) const", asMETHODPR(Matrix3, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix3::Equals(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool Equals(const Matrix3&in) const", asMETHODPR(Matrix3, Equals, (const Matrix3&) const, bool), asCALL_THISCALL);
    // Matrix3 Matrix3::Inverse() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Inverse() const", asMETHODPR(Matrix3, Inverse, () const, Matrix3), asCALL_THISCALL);
    // bool Matrix3::IsInf() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool IsInf() const", asMETHODPR(Matrix3, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix3::IsNaN() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool IsNaN() const", asMETHODPR(Matrix3, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3::Matrix3(const Matrix3& matrix) noexcept=default | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3_Matrix3_Matrix3), asCALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3_Matrix3_float_float_float_float_float_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Matrix3::Matrix3(const float* data) noexcept | File: ../Math/Matrix3.h
    // Error: type "const float*" can not automatically bind
    // Vector3 Matrix3::operator*(const Vector3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator*(float rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(float) const", asMETHODPR(Matrix3, operator*, (float) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator*(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(const Matrix3&in) const", asMETHODPR(Matrix3, operator*, (const Matrix3&) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator+(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opAdd(const Matrix3&in) const", asMETHODPR(Matrix3, operator+, (const Matrix3&) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator-(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opSub(const Matrix3&in) const", asMETHODPR(Matrix3, operator-, (const Matrix3&) const, Matrix3), asCALL_THISCALL);
    // Matrix3& Matrix3::operator=(const Matrix3& rhs) noexcept=default | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3& opAssign(const Matrix3&in)", asMETHODPR(Matrix3, operator=, (const Matrix3&), Matrix3&), asCALL_THISCALL);
    // bool Matrix3::operator==(const Matrix3& rhs) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "bool opEquals(const Matrix3&in) const", asMETHODPR(Matrix3, operator==, (const Matrix3&) const, bool), asCALL_THISCALL);
    // Vector3 Matrix3::Row(unsigned i) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 Row(uint) const", asMETHODPR(Matrix3, Row, (unsigned) const, Vector3), asCALL_THISCALL);
    // Vector3 Matrix3::Scale() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 Scale() const", asMETHODPR(Matrix3, Scale, () const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3::Scaled(const Vector3& scale) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Scaled(const Vector3&in) const", asMETHODPR(Matrix3, Scaled, (const Vector3&) const, Matrix3), asCALL_THISCALL);
    // void Matrix3::SetScale(const Vector3& scale) | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3, SetScale, (const Vector3&), void), asCALL_THISCALL);
    // void Matrix3::SetScale(float scale) | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "void SetScale(float)", asMETHODPR(Matrix3, SetScale, (float), void), asCALL_THISCALL);
    // Vector3 Matrix3::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3, SignedScale, (const Matrix3&) const, Vector3), asCALL_THISCALL);
    // String Matrix3::ToString() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "String ToString() const", asMETHODPR(Matrix3, ToString, () const, String), asCALL_THISCALL);
    // Matrix3 Matrix3::Transpose() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Transpose() const", asMETHODPR(Matrix3, Transpose, () const, Matrix3), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Column(uint) const", asMETHODPR(Matrix3x4, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // const float* Matrix3x4::Data() const | File: ../Math/Matrix3x4.h
    // Error: type "const float*" can not automatically bind
    // void Matrix3x4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix3x4, Decompose, (Vector3&, Quaternion&, Vector3&) const, void), asCALL_THISCALL);
    // float Matrix3x4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "float Element(uint, uint) const", asMETHODPR(Matrix3x4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix3x4::Equals(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool Equals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, Equals, (const Matrix3x4&) const, bool), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::Inverse() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 Inverse() const", asMETHODPR(Matrix3x4, Inverse, () const, Matrix3x4), asCALL_THISCALL);
    // bool Matrix3x4::IsInf() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool IsInf() const", asMETHODPR(Matrix3x4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix3x4::IsNaN() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool IsNaN() const", asMETHODPR(Matrix3x4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3x4::Matrix3x4(const Matrix3x4& matrix) noexcept=default | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(Matrix3x4_Matrix3x4_Matrix3x4), asCALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix3& matrix) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3x4_Matrix3x4_Matrix3), asCALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const Matrix4& matrix) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix3x4_Matrix3x4_Matrix4), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3x4_Matrix3x4_float_float_float_float_float_float_float_float_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Matrix3x4::Matrix3x4(const float* data) noexcept | File: ../Math/Matrix3x4.h
    // Error: type "const float*" can not automatically bind
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", asFUNCTION(Matrix3x4_Matrix3x4_Vector3_Quaternion_float), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", asFUNCTION(Matrix3x4_Matrix3x4_Vector3_Quaternion_Vector3), asCALL_CDECL_OBJFIRST);
    // Vector3 Matrix3x4::operator*(const Vector3& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Matrix3x4::operator*(const Vector4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector4&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector4&) const, Vector3), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(float rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(float) const", asMETHODPR(Matrix3x4, operator*, (float) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    // Matrix4 Matrix3x4::operator*(const Matrix4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator+(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opAdd(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator+, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator-(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opSub(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator-, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3x4& rhs) noexcept=default | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3x4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3x4&), Matrix3x4&), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3& rhs) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3&), Matrix3x4&), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix4& rhs) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix4&), Matrix3x4&), asCALL_THISCALL);
    // bool Matrix3x4::operator==(const Matrix3x4& rhs) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "bool opEquals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator==, (const Matrix3x4&) const, bool), asCALL_THISCALL);
    // Quaternion Matrix3x4::Rotation() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Quaternion Rotation() const", asMETHODPR(Matrix3x4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 Matrix3x4::RotationMatrix() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix3x4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Matrix3x4::Row(unsigned i) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector4 Row(uint) const", asMETHODPR(Matrix3x4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Matrix3x4::Scale() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Scale() const", asMETHODPR(Matrix3x4, Scale, () const, Vector3), asCALL_THISCALL);
    // void Matrix3x4::SetRotation(const Matrix3& rotation) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix3x4, SetRotation, (const Matrix3&), void), asCALL_THISCALL);
    // void Matrix3x4::SetScale(const Vector3& scale) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3x4, SetScale, (const Vector3&), void), asCALL_THISCALL);
    // void Matrix3x4::SetScale(float scale) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(float)", asMETHODPR(Matrix3x4, SetScale, (float), void), asCALL_THISCALL);
    // void Matrix3x4::SetTranslation(const Vector3& translation) | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix3x4, SetTranslation, (const Vector3&), void), asCALL_THISCALL);
    // Vector3 Matrix3x4::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3x4, SignedScale, (const Matrix3&) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3x4::ToMatrix3() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix3x4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // Matrix4 Matrix3x4::ToMatrix4() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 ToMatrix4() const", asMETHODPR(Matrix3x4, ToMatrix4, () const, Matrix4), asCALL_THISCALL);
    // String Matrix3x4::ToString() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "String ToString() const", asMETHODPR(Matrix3x4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Matrix3x4::Translation() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Translation() const", asMETHODPR(Matrix3x4, Translation, () const, Vector3), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Matrix4", "Vector4 Column(uint) const", asMETHODPR(Matrix4, Column, (unsigned) const, Vector4), asCALL_THISCALL);
    // const float* Matrix4::Data() const | File: ../Math/Matrix4.h
    // Error: type "const float*" can not automatically bind
    // void Matrix4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix4, Decompose, (Vector3&, Quaternion&, Vector3&) const, void), asCALL_THISCALL);
    // float Matrix4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "float Element(uint, uint) const", asMETHODPR(Matrix4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix4::Equals(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool Equals(const Matrix4&in) const", asMETHODPR(Matrix4, Equals, (const Matrix4&) const, bool), asCALL_THISCALL);
    // Matrix4 Matrix4::Inverse() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Inverse() const", asMETHODPR(Matrix4, Inverse, () const, Matrix4), asCALL_THISCALL);
    // bool Matrix4::IsInf() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool IsInf() const", asMETHODPR(Matrix4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix4::IsNaN() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool IsNaN() const", asMETHODPR(Matrix4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix4::Matrix4(const Matrix4& matrix) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix4_Matrix4_Matrix4), asCALL_CDECL_OBJFIRST);
    // explicit Matrix4::Matrix4(const Matrix3& matrix) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix4_Matrix4_Matrix3), asCALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix4_Matrix4_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Matrix4::Matrix4(const float* data) noexcept | File: ../Math/Matrix4.h
    // Error: type "const float*" can not automatically bind
    // Vector3 Matrix4::operator*(const Vector3& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix4, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector4 Matrix4::operator*(const Vector4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Matrix4, operator*, (const Vector4&) const, Vector4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(float rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(float) const", asMETHODPR(Matrix4, operator*, (float) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix3x4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix3x4&) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator+(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opAdd(const Matrix4&in) const", asMETHODPR(Matrix4, operator+, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator-(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opSub(const Matrix4&in) const", asMETHODPR(Matrix4, operator-, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix4& rhs) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix4&in)", asMETHODPR(Matrix4, operator=, (const Matrix4&), Matrix4&), asCALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix3& rhs) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix3&in)", asMETHODPR(Matrix4, operator=, (const Matrix3&), Matrix4&), asCALL_THISCALL);
    // bool Matrix4::operator==(const Matrix4& rhs) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "bool opEquals(const Matrix4&in) const", asMETHODPR(Matrix4, operator==, (const Matrix4&) const, bool), asCALL_THISCALL);
    // Quaternion Matrix4::Rotation() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Quaternion Rotation() const", asMETHODPR(Matrix4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 Matrix4::RotationMatrix() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Matrix4::Row(unsigned i) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector4 Row(uint) const", asMETHODPR(Matrix4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Matrix4::Scale() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 Scale() const", asMETHODPR(Matrix4, Scale, () const, Vector3), asCALL_THISCALL);
    // void Matrix4::SetRotation(const Matrix3& rotation) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix4, SetRotation, (const Matrix3&), void), asCALL_THISCALL);
    // void Matrix4::SetScale(const Vector3& scale) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix4, SetScale, (const Vector3&), void), asCALL_THISCALL);
    // void Matrix4::SetScale(float scale) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetScale(float)", asMETHODPR(Matrix4, SetScale, (float), void), asCALL_THISCALL);
    // void Matrix4::SetTranslation(const Vector3& translation) | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix4, SetTranslation, (const Vector3&), void), asCALL_THISCALL);
    // Vector3 Matrix4::SignedScale(const Matrix3& rotation) const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix4, SignedScale, (const Matrix3&) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix4::ToMatrix3() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // String Matrix4::ToString() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "String ToString() const", asMETHODPR(Matrix4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Matrix4::Translation() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Vector3 Translation() const", asMETHODPR(Matrix4, Translation, () const, Vector3), asCALL_THISCALL);
    // Matrix4 Matrix4::Transpose() const | File: ../Math/Matrix4.h
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Transpose() const", asMETHODPR(Matrix4, Transpose, () const, Matrix4), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Matrix4
    REGISTER_MANUAL_PART_Matrix4(Matrix4, "Matrix4")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddChild(UIElement@+)", asMETHODPR(Menu, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_ADDREF, "void f()", asMETHODPR(Menu, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTag(const String&in)", asMETHODPR(Menu, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Menu, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AddTags(Array<String>@+)", asFUNCTION(Menu_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void AdjustScissor(IntRect&)", asMETHODPR(Menu, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void AllocateNetworkState()", asMETHODPR(Menu, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void ApplyAttributes()", asMETHODPR(Menu, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void BringToFront()", asMETHODPR(Menu, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Menu, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void DisableLayoutUpdate()", asMETHODPR(Menu, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Menu, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void EnableLayoutUpdate()", asMETHODPR(Menu, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Menu, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint FindChild(UIElement@+) const", asMETHODPR(Menu, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // int Menu::GetAcceleratorKey() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "int GetAcceleratorKey() const", asMETHODPR(Menu, GetAcceleratorKey, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorKey() const", asMETHODPR(Menu, GetAcceleratorKey, () const, int), asCALL_THISCALL);
    // int Menu::GetAcceleratorQualifiers() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "int GetAcceleratorQualifiers() const", asMETHODPR(Menu, GetAcceleratorQualifiers, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorQualifiers() const", asMETHODPR(Menu, GetAcceleratorQualifiers, () const, int), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool GetAnimationEnabled() const", asMETHODPR(Menu, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_animationEnabled() const", asMETHODPR(Menu, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const String& GetAppliedStyle() const", asMETHODPR(Menu, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_style() const", asMETHODPR(Menu, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttribute(uint) const", asMETHODPR(Menu, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Variant get_attributes(uint) const", asMETHODPR(Menu, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttribute(const String&in) const", asMETHODPR(Menu, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Menu, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Menu, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Menu, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Menu, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttributeDefault(uint) const", asMETHODPR(Menu, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Variant get_attributeDefaults(uint) const", asMETHODPR(Menu, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Menu, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Button.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "BlendMode GetBlendMode() const", asMETHODPR(Menu, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "BlendMode get_blendMode() const", asMETHODPR(Menu, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool GetBlockEvents() const", asMETHODPR(Menu, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetBorder() const", asMETHODPR(Menu, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_border() const", asMETHODPR(Menu, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetBringToBack() const", asMETHODPR(Menu, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_bringToBack() const", asMETHODPR(Menu, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetBringToFront() const", asMETHODPR(Menu, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_bringToFront() const", asMETHODPR(Menu, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const String& GetCategory() const", asMETHODPR(Menu, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_category() const", asMETHODPR(Menu, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(uint) const", asMETHODPR(Menu, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_children(uint) const", asMETHODPR(Menu, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Menu, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Menu, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetChildOffset() const", asMETHODPR(Menu, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_childOffset() const", asMETHODPR(Menu, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Menu_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Menu_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Menu_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetClipBorder() const", asMETHODPR(Menu, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_clipBorder() const", asMETHODPR(Menu, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetClipChildren() const", asMETHODPR(Menu, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_clipChildren() const", asMETHODPR(Menu, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetColor(Corner) const", asMETHODPR(Menu, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Color& get_colors(Corner) const", asMETHODPR(Menu, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetColorAttr() const", asMETHODPR(Menu, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntRect GetCombinedScreenRect()", asMETHODPR(Menu, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "IntRect get_combinedScreenRect()", asMETHODPR(Menu, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Menu, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Color& GetDerivedColor() const", asMETHODPR(Menu, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "float GetDerivedOpacity() const", asMETHODPR(Menu, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_derivedOpacity() const", asMETHODPR(Menu, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetDisabledOffset() const", asMETHODPR(Menu, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_disabledOffset() const", asMETHODPR(Menu, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Menu, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Menu, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint GetDragButtonCount() const", asMETHODPR(Menu, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_dragButtonCount() const", asMETHODPR(Menu, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Menu, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Menu, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Menu, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetElementEventSender() const", asMETHODPR(Menu, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetEnableAnchor() const", asMETHODPR(Menu, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enableAnchor() const", asMETHODPR(Menu, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "VariantMap& GetEventDataMap() const", asMETHODPR(Menu, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "Object@+ GetEventSender() const", asMETHODPR(Menu, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "FocusMode GetFocusMode() const", asMETHODPR(Menu, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "FocusMode get_focusMode() const", asMETHODPR(Menu, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Menu, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Menu, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const VariantMap& GetGlobalVars() const", asMETHODPR(Menu, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const VariantMap& get_globalVars() const", asMETHODPR(Menu, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetHeight() const", asMETHODPR(Menu, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_height() const", asMETHODPR(Menu, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Menu, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Menu, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetHoverOffset() const", asMETHODPR(Menu, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_hoverOffset() const", asMETHODPR(Menu, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetImageBorder() const", asMETHODPR(Menu, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_imageBorder() const", asMETHODPR(Menu, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetImageRect() const", asMETHODPR(Menu, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_imageRect() const", asMETHODPR(Menu, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndent() const", asMETHODPR(Menu, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indent() const", asMETHODPR(Menu, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndentSpacing() const", asMETHODPR(Menu, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indentSpacing() const", asMETHODPR(Menu, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetIndentWidth() const", asMETHODPR(Menu, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_indentWidth() const", asMETHODPR(Menu, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Menu, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntRect& GetLayoutBorder() const", asMETHODPR(Menu, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntRect& get_layoutBorder() const", asMETHODPR(Menu, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetLayoutElementMaxSize() const", asMETHODPR(Menu, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Menu, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Menu, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "LayoutMode GetLayoutMode() const", asMETHODPR(Menu, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "LayoutMode get_layoutMode() const", asMETHODPR(Menu, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetLayoutSpacing() const", asMETHODPR(Menu, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_layoutSpacing() const", asMETHODPR(Menu, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "Material@+ GetMaterial() const", asMETHODPR(Menu, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Material@+ get_material() const", asMETHODPR(Menu, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetMaterialAttr() const", asMETHODPR(Menu, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetMaxAnchor() const", asMETHODPR(Menu, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_maxAnchor() const", asMETHODPR(Menu, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMaxHeight() const", asMETHODPR(Menu, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_maxHeight() const", asMETHODPR(Menu, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMaxOffset() const", asMETHODPR(Menu, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_maxOffset() const", asMETHODPR(Menu, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMaxSize() const", asMETHODPR(Menu, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_maxSize() const", asMETHODPR(Menu, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMaxWidth() const", asMETHODPR(Menu, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_maxWidth() const", asMETHODPR(Menu, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetMinAnchor() const", asMETHODPR(Menu, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_minAnchor() const", asMETHODPR(Menu, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMinHeight() const", asMETHODPR(Menu, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_minHeight() const", asMETHODPR(Menu, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMinOffset() const", asMETHODPR(Menu, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_minOffset() const", asMETHODPR(Menu, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetMinSize() const", asMETHODPR(Menu, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_minSize() const", asMETHODPR(Menu, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetMinWidth() const", asMETHODPR(Menu, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_minWidth() const", asMETHODPR(Menu, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const String& GetName() const", asMETHODPR(Menu, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_name() const", asMETHODPR(Menu, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "uint GetNumAttributes() const", asMETHODPR(Menu, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_numAttributes() const", asMETHODPR(Menu, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "uint GetNumChildren(bool = false) const", asMETHODPR(Menu, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "uint get_numChildren(bool = false) const", asMETHODPR(Menu, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "uint GetNumNetworkAttributes() const", asMETHODPR(Menu, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Menu, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Menu, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Menu, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "float GetOpacity() const", asMETHODPR(Menu, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_opacity() const", asMETHODPR(Menu, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetParent() const", asMETHODPR(Menu, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_parent() const", asMETHODPR(Menu, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Vector2& GetPivot() const", asMETHODPR(Menu, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const Vector2& get_pivot() const", asMETHODPR(Menu, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // UIElement* Menu::GetPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetPopup() const", asMETHODPR(Menu, GetPopup, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_popup() const", asMETHODPR(Menu, GetPopup, () const, UIElement*), asCALL_THISCALL);
    // const IntVector2& Menu::GetPopupOffset() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPopupOffset() const", asMETHODPR(Menu, GetPopupOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_popupOffset() const", asMETHODPR(Menu, GetPopupOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPosition() const", asMETHODPR(Menu, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_position() const", asMETHODPR(Menu, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPressedChildOffset() const", asMETHODPR(Menu, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_pressedChildOffset() const", asMETHODPR(Menu, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetPressedOffset() const", asMETHODPR(Menu, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_pressedOffset() const", asMETHODPR(Menu, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetPriority() const", asMETHODPR(Menu, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_priority() const", asMETHODPR(Menu, GetPriority, () const, int), asCALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "float GetRepeatDelay() const", asMETHODPR(Menu, GetRepeatDelay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_repeatDelay() const", asMETHODPR(Menu, GetRepeatDelay, () const, float), asCALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "float GetRepeatRate() const", asMETHODPR(Menu, GetRepeatRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "float get_repeatRate() const", asMETHODPR(Menu, GetRepeatRate, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ GetRoot() const", asMETHODPR(Menu, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_root() const", asMETHODPR(Menu, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetScreenPosition() const", asMETHODPR(Menu, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_screenPosition() const", asMETHODPR(Menu, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // bool Menu::GetShowPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool GetShowPopup() const", asMETHODPR(Menu, GetShowPopup, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_showPopup() const", asMETHODPR(Menu, GetShowPopup, () const, bool), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const IntVector2& GetSize() const", asMETHODPR(Menu, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_size() const", asMETHODPR(Menu, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetSortChildren() const", asMETHODPR(Menu, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_sortChildren() const", asMETHODPR(Menu, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Menu, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "Array<String>@ GetTags() const", asFUNCTION(Menu_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Menu", "Array<String>@ get_tags() const", asFUNCTION(Menu_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "Texture@+ GetTexture() const", asMETHODPR(Menu, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "Texture@+ get_texture() const", asMETHODPR(Menu, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "ResourceRef GetTextureAttr() const", asMETHODPR(Menu, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "TraversalMode GetTraversalMode() const", asMETHODPR(Menu, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "TraversalMode get_traversalMode() const", asMETHODPR(Menu, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "StringHash GetType() const", asMETHODPR(Menu, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "StringHash get_type() const", asMETHODPR(Menu, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "const String& GetTypeName() const", asMETHODPR(Menu, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const String& get_typeName() const", asMETHODPR(Menu, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool GetUseDerivedOpacity() const", asMETHODPR(Menu, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_useDerivedOpacity() const", asMETHODPR(Menu, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Menu, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "const VariantMap& GetVars() const", asMETHODPR(Menu, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Menu, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Menu, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "int GetWidth() const", asMETHODPR(Menu, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_width() const", asMETHODPR(Menu, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasColorGradient() const", asMETHODPR(Menu, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_colorGradient() const", asMETHODPR(Menu, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasEventHandlers() const", asMETHODPR(Menu, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasFocus() const", asMETHODPR(Menu, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_focus() const", asMETHODPR(Menu, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Menu, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Menu, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool HasTag(const String&in) const", asMETHODPR(Menu, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void InsertChild(uint, UIElement@+)", asMETHODPR(Menu, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsChildOf(UIElement@+) const", asMETHODPR(Menu, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEditable() const", asMETHODPR(Menu, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_editable() const", asMETHODPR(Menu, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsElementEventSender() const", asMETHODPR(Menu, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_elementEventSender() const", asMETHODPR(Menu, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEnabled() const", asMETHODPR(Menu, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enabled() const", asMETHODPR(Menu, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsEnabledSelf() const", asMETHODPR(Menu, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_enabledSelf() const", asMETHODPR(Menu, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedHeight() const", asMETHODPR(Menu, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedHeight() const", asMETHODPR(Menu, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedSize() const", asMETHODPR(Menu, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedSize() const", asMETHODPR(Menu, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsFixedWidth() const", asMETHODPR(Menu, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_fixedWidth() const", asMETHODPR(Menu, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsHovering() const", asMETHODPR(Menu, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_hovering() const", asMETHODPR(Menu, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInside(IntVector2, bool)", asMETHODPR(Menu, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Menu, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "bool IsInstanceOf(StringHash) const", asMETHODPR(Menu, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsInternal() const", asMETHODPR(Menu, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_internal() const", asMETHODPR(Menu, IsInternal, () const, bool), asCALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "bool IsPressed() const", asMETHODPR(Menu, IsPressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_pressed() const", asMETHODPR(Menu, IsPressed, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsSelected() const", asMETHODPR(Menu, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_selected() const", asMETHODPR(Menu, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool IsTemporary() const", asMETHODPR(Menu, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_temporary() const", asMETHODPR(Menu, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "bool IsTiled() const", asMETHODPR(Menu, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_tiled() const", asMETHODPR(Menu, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsVisible() const", asMETHODPR(Menu, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_visible() const", asMETHODPR(Menu, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsVisibleEffective() const", asMETHODPR(Menu, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_visibleEffective() const", asMETHODPR(Menu, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsWheelHandler() const", asMETHODPR(Menu, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Menu, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool Load(Deserializer&)", asMETHODPR(Menu, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Menu, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Menu, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Menu, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void MarkNetworkUpdate()", asMETHODPR(Menu, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit Menu::Menu(Context* context) | File: ../UI/Menu.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_FACTORY, "Menu@+ f()", asFUNCTION(Menu_Menu_Context), asCALL_CDECL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Menu, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Menu, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Menu, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Menu, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Menu, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Menu, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Menu, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Menu, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Menu, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Menu, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Menu, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Menu::OnHidePopup() | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnHidePopup()", asMETHODPR(Menu, OnHidePopup, (), void), asCALL_THISCALL);
    // void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Menu, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnIndentSet()", asMETHODPR(Menu, OnIndentSet, (), void), asCALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Menu, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Menu, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Menu, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Menu, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnSetEditable()", asMETHODPR(Menu, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void Menu::OnShowPopup() | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void OnShowPopup()", asMETHODPR(Menu, OnShowPopup, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnTextInput(const String&in)", asMETHODPR(Menu, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Menu, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Menu, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Menu, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Menu", "int Refs() const", asMETHODPR(Menu, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_refs() const", asMETHODPR(Menu, Refs, () const, int), asCALL_THISCALL);
    // static void Menu::RegisterObject(Context* context) | File: ../UI/Menu.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Menu", asBEHAVE_RELEASE, "void f()", asMETHODPR(Menu, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void Remove()", asMETHODPR(Menu, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveAllChildren()", asMETHODPR(Menu, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveAllTags()", asMETHODPR(Menu, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Menu, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Menu, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void RemoveChildAtIndex(uint)", asMETHODPR(Menu, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void RemoveInstanceDefault()", asMETHODPR(Menu, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void RemoveObjectAnimation()", asMETHODPR(Menu, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool RemoveTag(const String&in)", asMETHODPR(Menu, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void ResetDeepEnabled()", asMETHODPR(Menu, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void ResetToDefault()", asMETHODPR(Menu, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool Save(Serializer&) const", asMETHODPR(Menu, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SaveDefaultAttributes() const", asMETHODPR(Menu, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "bool SaveJSON(JSONValue&) const", asMETHODPR(Menu, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Menu::SaveXML(XMLElement& dest) const override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "bool SaveXML(XMLElement&) const", asMETHODPR(Menu, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Menu, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SendEvent(StringHash)", asMETHODPR(Menu, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Menu, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Menu::SetAccelerator(int key, int qualifiers) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetAccelerator(int, int)", asMETHODPR(Menu, SetAccelerator, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Menu, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAnimationEnabled(bool)", asMETHODPR(Menu, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_animationEnabled(bool)", asMETHODPR(Menu, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAnimationTime(float)", asMETHODPR(Menu, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Menu, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Menu, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Menu, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Menu, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Menu, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Menu, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Menu, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetBlendMode(BlendMode)", asMETHODPR(Menu, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_blendMode(BlendMode)", asMETHODPR(Menu, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SetBlockEvents(bool)", asMETHODPR(Menu, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetBorder(const IntRect&in)", asMETHODPR(Menu, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_border(const IntRect&in)", asMETHODPR(Menu, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetBringToBack(bool)", asMETHODPR(Menu, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_bringToBack(bool)", asMETHODPR(Menu, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetBringToFront(bool)", asMETHODPR(Menu, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_bringToFront(bool)", asMETHODPR(Menu, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Menu, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetClipBorder(const IntRect&in)", asMETHODPR(Menu, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_clipBorder(const IntRect&in)", asMETHODPR(Menu, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetClipChildren(bool)", asMETHODPR(Menu, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_clipChildren(bool)", asMETHODPR(Menu, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetColor(const Color&in)", asMETHODPR(Menu, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_color(const Color&in)", asMETHODPR(Menu, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetColor(Corner, const Color&in)", asMETHODPR(Menu, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_colors(Corner, const Color&in)", asMETHODPR(Menu, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDeepEnabled(bool)", asMETHODPR(Menu, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Menu, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Menu, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(Menu, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(Menu, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetDisabledOffset(int, int)", asMETHODPR(Menu, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Menu, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Menu, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEditable(bool)", asMETHODPR(Menu, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_editable(bool)", asMETHODPR(Menu, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetElementEventSender(bool)", asMETHODPR(Menu, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_elementEventSender(bool)", asMETHODPR(Menu, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnableAnchor(bool)", asMETHODPR(Menu, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_enableAnchor(bool)", asMETHODPR(Menu, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnabled(bool)", asMETHODPR(Menu, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_enabled(bool)", asMETHODPR(Menu, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetEnabledRecursive(bool)", asMETHODPR(Menu, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedHeight(int)", asMETHODPR(Menu, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Menu, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedSize(int, int)", asMETHODPR(Menu, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFixedWidth(int)", asMETHODPR(Menu, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFocus(bool)", asMETHODPR(Menu, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_focus(bool)", asMETHODPR(Menu, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetFocusMode(FocusMode)", asMETHODPR(Menu, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_focusMode(FocusMode)", asMETHODPR(Menu, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetFullImageRect()", asMETHODPR(Menu, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Menu, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Menu, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHeight(int)", asMETHODPR(Menu, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_height(int)", asMETHODPR(Menu, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Menu, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Menu, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetHovering(bool)", asMETHODPR(Menu, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(Menu, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(Menu, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetHoverOffset(int, int)", asMETHODPR(Menu, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetImageBorder(const IntRect&in)", asMETHODPR(Menu, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_imageBorder(const IntRect&in)", asMETHODPR(Menu, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetImageRect(const IntRect&in)", asMETHODPR(Menu, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_imageRect(const IntRect&in)", asMETHODPR(Menu, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetIndent(int)", asMETHODPR(Menu, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_indent(int)", asMETHODPR(Menu, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetIndentSpacing(int)", asMETHODPR(Menu, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_indentSpacing(int)", asMETHODPR(Menu, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetInstanceDefault(bool)", asMETHODPR(Menu, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Menu, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetInternal(bool)", asMETHODPR(Menu, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_internal(bool)", asMETHODPR(Menu, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Menu, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Menu, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Menu, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Menu, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Menu, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutMode(LayoutMode)", asMETHODPR(Menu, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutMode(LayoutMode)", asMETHODPR(Menu, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetLayoutSpacing(int)", asMETHODPR(Menu, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_layoutSpacing(int)", asMETHODPR(Menu, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetMaterial(Material@+)", asMETHODPR(Menu, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_material(Material@+)", asMETHODPR(Menu, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Menu, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Menu, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Menu, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxAnchor(float, float)", asMETHODPR(Menu, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxHeight(int)", asMETHODPR(Menu, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxHeight(int)", asMETHODPR(Menu, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Menu, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Menu, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Menu, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxSize(const IntVector2&in)", asMETHODPR(Menu, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxSize(int, int)", asMETHODPR(Menu, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMaxWidth(int)", asMETHODPR(Menu, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_maxWidth(int)", asMETHODPR(Menu, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Menu, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minAnchor(const Vector2&in)", asMETHODPR(Menu, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinAnchor(float, float)", asMETHODPR(Menu, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinHeight(int)", asMETHODPR(Menu, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minHeight(int)", asMETHODPR(Menu, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Menu, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minOffset(const IntVector2&in)", asMETHODPR(Menu, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinSize(const IntVector2&in)", asMETHODPR(Menu, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minSize(const IntVector2&in)", asMETHODPR(Menu, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinSize(int, int)", asMETHODPR(Menu, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetMinWidth(int)", asMETHODPR(Menu, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_minWidth(int)", asMETHODPR(Menu, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetName(const String&in)", asMETHODPR(Menu, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_name(const String&in)", asMETHODPR(Menu, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Menu, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Menu, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Menu", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Menu, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetOpacity(float)", asMETHODPR(Menu, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_opacity(float)", asMETHODPR(Menu, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Menu, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPivot(const Vector2&in)", asMETHODPR(Menu, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pivot(const Vector2&in)", asMETHODPR(Menu, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPivot(float, float)", asMETHODPR(Menu, SetPivot, (float, float), void), asCALL_THISCALL);
    // void Menu::SetPopup(UIElement* popup) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopup(UIElement@+)", asMETHODPR(Menu, SetPopup, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popup(UIElement@+)", asMETHODPR(Menu, SetPopup, (UIElement*), void), asCALL_THISCALL);
    // void Menu::SetPopupOffset(const IntVector2& offset) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopupOffset(const IntVector2&in)", asMETHODPR(Menu, SetPopupOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popupOffset(const IntVector2&in)", asMETHODPR(Menu, SetPopupOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Menu::SetPopupOffset(int x, int y) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void SetPopupOffset(int, int)", asMETHODPR(Menu, SetPopupOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPosition(const IntVector2&in)", asMETHODPR(Menu, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_position(const IntVector2&in)", asMETHODPR(Menu, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPosition(int, int)", asMETHODPR(Menu, SetPosition, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedChildOffset(const IntVector2&in)", asMETHODPR(Menu, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pressedChildOffset(const IntVector2&in)", asMETHODPR(Menu, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedChildOffset(int, int)", asMETHODPR(Menu, SetPressedChildOffset, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedOffset(const IntVector2&in)", asMETHODPR(Menu, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_pressedOffset(const IntVector2&in)", asMETHODPR(Menu, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetPressedOffset(int, int)", asMETHODPR(Menu, SetPressedOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetPriority(int)", asMETHODPR(Menu, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_priority(int)", asMETHODPR(Menu, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Menu, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeat(float, float)", asMETHODPR(Menu, SetRepeat, (float, float), void), asCALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeatDelay(float)", asMETHODPR(Menu, SetRepeatDelay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_repeatDelay(float)", asMETHODPR(Menu, SetRepeatDelay, (float), void), asCALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Menu", "void SetRepeatRate(float)", asMETHODPR(Menu, SetRepeatRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_repeatRate(float)", asMETHODPR(Menu, SetRepeatRate, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSelected(bool)", asMETHODPR(Menu, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_selected(bool)", asMETHODPR(Menu, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSize(const IntVector2&in)", asMETHODPR(Menu, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_size(const IntVector2&in)", asMETHODPR(Menu, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSize(int, int)", asMETHODPR(Menu, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetSortChildren(bool)", asMETHODPR(Menu, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_sortChildren(bool)", asMETHODPR(Menu, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Menu, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyle(const XMLElement&in)", asMETHODPR(Menu, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Menu, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetTags(Array<String>@+)", asFUNCTION(Menu_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void SetTemporary(bool)", asMETHODPR(Menu, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_temporary(bool)", asMETHODPR(Menu, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTexture(Texture@+)", asMETHODPR(Menu, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_texture(Texture@+)", asMETHODPR(Menu, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Menu, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Menu", "void SetTiled(bool)", asMETHODPR(Menu, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_tiled(bool)", asMETHODPR(Menu, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetTraversalMode(TraversalMode)", asMETHODPR(Menu, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_traversalMode(TraversalMode)", asMETHODPR(Menu, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetUseDerivedOpacity(bool)", asMETHODPR(Menu, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_useDerivedOpacity(bool)", asMETHODPR(Menu, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Menu, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Menu, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Menu, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetVisible(bool)", asMETHODPR(Menu, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_visible(bool)", asMETHODPR(Menu, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SetWidth(int)", asMETHODPR(Menu, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_width(int)", asMETHODPR(Menu, SetWidth, (int), void), asCALL_THISCALL);
    // void Menu::ShowPopup(bool enable) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void ShowPopup(bool)", asMETHODPR(Menu, ShowPopup, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_showPopup(bool)", asMETHODPR(Menu, ShowPopup, (bool), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void SortChildren()", asMETHODPR(Menu, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromAllEvents()", asMETHODPR(Menu, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Menu_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Menu, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Menu, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Menu", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Menu, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Menu::Update(float timeStep) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("Menu", "void Update(float)", asMETHODPR(Menu, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Menu", "void UpdateLayout()", asMETHODPR(Menu, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Menu", "int WeakRefs() const", asMETHODPR(Menu, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_weakRefs() const", asMETHODPR(Menu, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Menu, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Menu, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Menu", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Menu, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_ADDREF, "void f()", asMETHODPR(MessageBox, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool GetBlockEvents() const", asMETHODPR(MessageBox, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetCategory() const", asMETHODPR(MessageBox, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_category() const", asMETHODPR(MessageBox, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "VariantMap& GetEventDataMap() const", asMETHODPR(MessageBox, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "Object@+ GetEventSender() const", asMETHODPR(MessageBox, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(MessageBox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const Variant& get_globalVar(StringHash) const", asMETHODPR(MessageBox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const VariantMap& GetGlobalVars() const", asMETHODPR(MessageBox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const VariantMap& get_globalVars() const", asMETHODPR(MessageBox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const String& MessageBox::GetMessage() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetMessage() const", asMETHODPR(MessageBox, GetMessage, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_message() const", asMETHODPR(MessageBox, GetMessage, () const, const String&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(MessageBox, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& MessageBox::GetTitle() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetTitle() const", asMETHODPR(MessageBox, GetTitle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_title() const", asMETHODPR(MessageBox, GetTitle, () const, const String&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "StringHash GetType() const", asMETHODPR(MessageBox, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "StringHash get_type() const", asMETHODPR(MessageBox, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "const String& GetTypeName() const", asMETHODPR(MessageBox, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_typeName() const", asMETHODPR(MessageBox, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UIElement* MessageBox::GetWindow() const | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "UIElement@+ GetWindow() const", asMETHODPR(MessageBox, GetWindow, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "UIElement@+ get_window() const", asMETHODPR(MessageBox, GetWindow, () const, UIElement*), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasEventHandlers() const", asMETHODPR(MessageBox, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(MessageBox, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(MessageBox, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "bool IsInstanceOf(StringHash) const", asMETHODPR(MessageBox, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // explicit MessageBox::MessageBox(Context* context, const String& messageString=String::EMPTY, const String& titleString=String::EMPTY, XMLFile* layoutFile=nullptr, XMLFile* styleFile=nullptr) | File: ../UI/MessageBox.h
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_FACTORY, "MessageBox@+ f(const String&in = String::EMPTY, const String&in = String::EMPTY, XMLFile@+ = null, XMLFile@+ = null)", asFUNCTION(MessageBox_MessageBox_Context_String_String_XMLFile_XMLFile), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(MessageBox, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("MessageBox", "int Refs() const", asMETHODPR(MessageBox, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "int get_refs() const", asMETHODPR(MessageBox, Refs, () const, int), asCALL_THISCALL);
    // static void MessageBox::RegisterObject(Context* context) | File: ../UI/MessageBox.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_RELEASE, "void f()", asMETHODPR(MessageBox, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SendEvent(StringHash)", asMETHODPR(MessageBox, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(MessageBox, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SetBlockEvents(bool)", asMETHODPR(MessageBox, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(MessageBox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(MessageBox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void MessageBox::SetMessage(const String& text) | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "void SetMessage(const String&in)", asMETHODPR(MessageBox, SetMessage, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_message(const String&in)", asMETHODPR(MessageBox, SetMessage, (const String&), void), asCALL_THISCALL);
    // void MessageBox::SetTitle(const String& text) | File: ../UI/MessageBox.h
    engine->RegisterObjectMethod("MessageBox", "void SetTitle(const String&in)", asMETHODPR(MessageBox, SetTitle, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_title(const String&in)", asMETHODPR(MessageBox, SetTitle, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromAllEvents()", asMETHODPR(MessageBox, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(MessageBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(MessageBox, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(MessageBox, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("MessageBox", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(MessageBox, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("MessageBox", "int WeakRefs() const", asMETHODPR(MessageBox, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "int get_weakRefs() const", asMETHODPR(MessageBox, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Model", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Model, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Model, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_ADDREF, "void f()", asMETHODPR(Model, AddRef, (), void), asCALL_THISCALL);
    // bool Model::BeginLoad(Deserializer& source) override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool BeginLoad(Deserializer&)", asMETHODPR(Model, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Model> Model::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Model@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(Model_Clone_String), asCALL_CDECL_OBJFIRST);
    // bool Model::EndLoad() override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool EndLoad()", asMETHODPR(Model, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Model, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool GetBlockEvents() const", asMETHODPR(Model, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Model::GetBoundingBox() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Model, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const BoundingBox& get_boundingBox() const", asMETHODPR(Model, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const String& GetCategory() const", asMETHODPR(Model, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_category() const", asMETHODPR(Model, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "VariantMap& GetEventDataMap() const", asMETHODPR(Model, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "Object@+ GetEventSender() const", asMETHODPR(Model, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Vector<Vector<SharedPtr<Geometry>>>& Model::GetGeometries() const | File: ../Graphics/Model.h
    // Error: type "const Vector<Vector<SharedPtr<Geometry>>>&" can not automatically bind
    // Geometry* Model::GetGeometry(unsigned index, unsigned lodLevel) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Geometry@+ GetGeometry(uint, uint) const", asMETHODPR(Model, GetGeometry, (unsigned, unsigned) const, Geometry*), asCALL_THISCALL);
    // const Vector<PODVector<unsigned>>& Model::GetGeometryBoneMappings() const | File: ../Graphics/Model.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const Vector3& Model::GetGeometryCenter(unsigned index) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "const Vector3& GetGeometryCenter(uint) const", asMETHODPR(Model, GetGeometryCenter, (unsigned) const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Vector3& get_geometryCenters(uint) const", asMETHODPR(Model, GetGeometryCenter, (unsigned) const, const Vector3&), asCALL_THISCALL);
    // const PODVector<Vector3>& Model::GetGeometryCenters() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<Vector3>@ GetGeometryCenters() const", asFUNCTION(Model_GetGeometryCenters_void), asCALL_CDECL_OBJFIRST);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Model, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Model, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const VariantMap& GetGlobalVars() const", asMETHODPR(Model, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const VariantMap& get_globalVars() const", asMETHODPR(Model, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector<SharedPtr<IndexBuffer>>& Model::GetIndexBuffers() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<IndexBuffer@>@ GetIndexBuffers() const", asFUNCTION(Model_GetIndexBuffers_void), asCALL_CDECL_OBJFIRST);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "uint GetMemoryUse() const", asMETHODPR(Model, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_memoryUse() const", asMETHODPR(Model, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Model, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const Variant& get_metadata(const String&in) const", asMETHODPR(Model, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // const ModelMorph* Model::GetMorph(unsigned index) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(const String& name) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // const ModelMorph* Model::GetMorph(StringHash nameHash) const | File: ../Graphics/Model.h
    // Error: type "const ModelMorph*" can not automatically bind
    // unsigned Model::GetMorphRangeCount(unsigned bufferIndex) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetMorphRangeCount(uint) const", asMETHODPR(Model, GetMorphRangeCount, (unsigned) const, unsigned), asCALL_THISCALL);
    // unsigned Model::GetMorphRangeStart(unsigned bufferIndex) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetMorphRangeStart(uint) const", asMETHODPR(Model, GetMorphRangeStart, (unsigned) const, unsigned), asCALL_THISCALL);
    // const Vector<ModelMorph>& Model::GetMorphs() const | File: ../Graphics/Model.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "const String& GetName() const", asMETHODPR(Model, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_name() const", asMETHODPR(Model, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "StringHash GetNameHash() const", asMETHODPR(Model, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned Model::GetNumGeometries() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumGeometries() const", asMETHODPR(Model, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometries() const", asMETHODPR(Model, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned Model::GetNumGeometryLodLevels(unsigned index) const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumGeometryLodLevels(uint) const", asMETHODPR(Model, GetNumGeometryLodLevels, (unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometryLodLevels(uint) const", asMETHODPR(Model, GetNumGeometryLodLevels, (unsigned) const, unsigned), asCALL_THISCALL);
    // unsigned Model::GetNumMorphs() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "uint GetNumMorphs() const", asMETHODPR(Model, GetNumMorphs, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numMorphs() const", asMETHODPR(Model, GetNumMorphs, () const, unsigned), asCALL_THISCALL);
    // Skeleton& Model::GetSkeleton() | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Skeleton& GetSkeleton()", asMETHODPR(Model, GetSkeleton, (), Skeleton&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "Skeleton& get_skeleton()", asMETHODPR(Model, GetSkeleton, (), Skeleton&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Model, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "StringHash GetType() const", asMETHODPR(Model, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "StringHash get_type() const", asMETHODPR(Model, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "const String& GetTypeName() const", asMETHODPR(Model, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "const String& get_typeName() const", asMETHODPR(Model, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "uint GetUseTimer()", asMETHODPR(Model, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_useTimer()", asMETHODPR(Model, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // const Vector<SharedPtr<VertexBuffer>>& Model::GetVertexBuffers() const | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "Array<VertexBuffer@>@ GetVertexBuffers() const", asFUNCTION(Model_GetVertexBuffers_void), asCALL_CDECL_OBJFIRST);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasEventHandlers() const", asMETHODPR(Model, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool HasMetadata() const", asMETHODPR(Model, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool get_hasMetadata() const", asMETHODPR(Model, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Model, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Model, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "bool IsInstanceOf(StringHash) const", asMETHODPR(Model, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool Load(Deserializer&)", asMETHODPR(Model, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool LoadFile(const String&in)", asMETHODPR(Model, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool Load(const String&in)", asMETHODPR(Model, LoadFile, (const String&), bool), asCALL_THISCALL);
    // explicit Model::Model(Context* context) | File: ../Graphics/Model.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_FACTORY, "Model@+ f()", asFUNCTION(Model_Model_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Model, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Model", "int Refs() const", asMETHODPR(Model, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "int get_refs() const", asMETHODPR(Model, Refs, () const, int), asCALL_THISCALL);
    // static void Model::RegisterObject(Context* context) | File: ../Graphics/Model.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Model", asBEHAVE_RELEASE, "void f()", asMETHODPR(Model, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void RemoveAllMetadata()", asMETHODPR(Model, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void RemoveMetadata(const String&in)", asMETHODPR(Model, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void ResetUseTimer()", asMETHODPR(Model, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool Model::Save(Serializer& dest) const override | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool Save(Serializer&) const", asMETHODPR(Model, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "bool SaveFile(const String&in) const", asMETHODPR(Model, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool Save(const String&in) const", asMETHODPR(Model, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SendEvent(StringHash)", asMETHODPR(Model, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Model, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Model, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SetBlockEvents(bool)", asMETHODPR(Model, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Model::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetBoundingBox(const BoundingBox&in)", asMETHODPR(Model, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_boundingBox(const BoundingBox&in)", asMETHODPR(Model, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    // bool Model::SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetGeometry(uint, uint, Geometry@+)", asMETHODPR(Model, SetGeometry, (unsigned, unsigned, Geometry*), bool), asCALL_THISCALL);
    // void Model::SetGeometryBoneMappings(const Vector<PODVector<unsigned>>& geometryBoneMappings) | File: ../Graphics/Model.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // bool Model::SetGeometryCenter(unsigned index, const Vector3& center) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetGeometryCenter(uint, const Vector3&in)", asMETHODPR(Model, SetGeometryCenter, (unsigned, const Vector3&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool set_geometryCenters(uint, const Vector3&in)", asMETHODPR(Model, SetGeometryCenter, (unsigned, const Vector3&), bool), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Model, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Model, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // bool Model::SetIndexBuffers(const Vector<SharedPtr<IndexBuffer>>& buffers) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetIndexBuffers(Array<IndexBuffer@>@+)", asFUNCTION(Model_SetIndexBuffers_VectorSharedPtrIndexBuffer), asCALL_CDECL_OBJFIRST);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetMemoryUse(uint)", asMETHODPR(Model, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Model::SetMorphs(const Vector<ModelMorph>& morphs) | File: ../Graphics/Model.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Model", "void SetName(const String&in)", asMETHODPR(Model, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_name(const String&in)", asMETHODPR(Model, SetName, (const String&), void), asCALL_THISCALL);
    // void Model::SetNumGeometries(unsigned num) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetNumGeometries(uint)", asMETHODPR(Model, SetNumGeometries, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "void set_numGeometries(uint)", asMETHODPR(Model, SetNumGeometries, (unsigned), void), asCALL_THISCALL);
    // bool Model::SetNumGeometryLodLevels(unsigned index, unsigned num) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetNumGeometryLodLevels(uint, uint)", asMETHODPR(Model, SetNumGeometryLodLevels, (unsigned, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "bool set_numGeometryLodLevels(uint, uint)", asMETHODPR(Model, SetNumGeometryLodLevels, (unsigned, unsigned), bool), asCALL_THISCALL);
    // void Model::SetSkeleton(const Skeleton& skeleton) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "void SetSkeleton(const Skeleton&in)", asMETHODPR(Model, SetSkeleton, (const Skeleton&), void), asCALL_THISCALL);
    // bool Model::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, const PODVector<unsigned>& morphRangeStarts, const PODVector<unsigned>& morphRangeCounts) | File: ../Graphics/Model.h
    engine->RegisterObjectMethod("Model", "bool SetVertexBuffers(Array<VertexBuffer@>@+, Array<uint>@+, Array<uint>@+)", asFUNCTION(Model_SetVertexBuffers_VectorSharedPtrVertexBuffer_PODVectorunsigned_PODVectorunsigned), asCALL_CDECL_OBJFIRST);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromAllEvents()", asMETHODPR(Model, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Model_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Model, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Model, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Model", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Model, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Model", "int WeakRefs() const", asMETHODPR(Model, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "int get_weakRefs() const", asMETHODPR(Model, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Mutex", "void Acquire()", asMETHODPR(Mutex, Acquire, (), void), asCALL_THISCALL);
    // void Mutex::Release() | File: ../Core/Mutex.h
    engine->RegisterObjectMethod("Mutex", "void Release()", asMETHODPR(Mutex, Release, (), void), asCALL_THISCALL);
    // bool Mutex::TryAcquire() | File: ../Core/Mutex.h
    engine->RegisterObjectMethod("Mutex", "bool TryAcquire()", asMETHODPR(Mutex, TryAcquire, (), bool), asCALL_THISCALL);
    // Mutex& Mutex::operator=(const Mutex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Mutex>(engine, "Mutex");
#ifdef REGISTER_MANUAL_PART_Mutex
    REGISTER_MANUAL_PART_Mutex(Mutex, "Mutex")
#endif

    // explicit MutexLock::MutexLock(Mutex& mutex) | File: ../Core/Mutex.h
    engine->RegisterObjectBehaviour("MutexLock", asBEHAVE_CONSTRUCT, "void f(Mutex&)", asFUNCTION(MutexLock_MutexLock_Mutex), asCALL_CDECL_OBJFIRST);
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
