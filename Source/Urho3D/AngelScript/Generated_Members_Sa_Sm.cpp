// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
static void Scene_AddTags_StringVector(Scene* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
static CScriptArray* Scene_GetChildren_void(Scene* ptr)
{
    const Vector<SharedPtr<Node>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
static CScriptArray* Scene_GetChildren_bool(Scene* ptr, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
static CScriptArray* Scene_GetChildrenWithComponent_StringHash_bool(Scene* ptr, StringHash type, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildrenWithComponent(type, recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
static CScriptArray* Scene_GetChildrenWithTag_String_bool(Scene* ptr, const String& tag, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
static CScriptArray* Scene_GetComponents_void(Scene* ptr)
{
    const Vector<SharedPtr<Component>>& result = ptr->GetComponents();
    return VectorToHandleArray(result, "Array<Component@>");
}

// const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
static CScriptArray* Scene_GetDependencyNodes_void(Scene* ptr)
{
    const PODVector<Node*>& result = ptr->GetDependencyNodes();
    return VectorToHandleArray(result, "Array<Node@>");
}

// const Vector<SharedPtr<PackageFile>>& Scene::GetRequiredPackageFiles() const | File: ../Scene/Scene.h
static CScriptArray* Scene_GetRequiredPackageFiles_void(Scene* ptr)
{
    const Vector<SharedPtr<PackageFile>>& result = ptr->GetRequiredPackageFiles();
    return VectorToHandleArray(result, "Array<PackageFile@>");
}

// const StringVector& Node::GetTags() const | File: ../Scene/Node.h
static CScriptArray* Scene_GetTags_void(Scene* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit Scene::Scene(Context* context) | File: ../Scene/Scene.h
static Scene* Scene_Scene_Context()
{
    return new Scene(GetScriptContext());
}

// void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
static void Scene_SetTags_StringVector(Scene* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Scene_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Scene* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ScrollBar_AddTags_StringVector(ScrollBar* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* ScrollBar_GetChildren_void(ScrollBar* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* ScrollBar_GetChildren_bool(ScrollBar* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* ScrollBar_GetChildrenWithTag_String_bool(ScrollBar* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* ScrollBar_GetTags_void(ScrollBar* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit ScrollBar::ScrollBar(Context* context) | File: ../UI/ScrollBar.h
static ScrollBar* ScrollBar_ScrollBar_Context()
{
    return new ScrollBar(GetScriptContext());
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ScrollBar_SetTags_StringVector(ScrollBar* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ScrollBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ScrollBar* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ScrollView_AddTags_StringVector(ScrollView* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* ScrollView_GetChildren_void(ScrollView* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* ScrollView_GetChildren_bool(ScrollView* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* ScrollView_GetChildrenWithTag_String_bool(ScrollView* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* ScrollView_GetTags_void(ScrollView* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit ScrollView::ScrollView(Context* context) | File: ../UI/ScrollView.h
static ScrollView* ScrollView_ScrollView_Context()
{
    return new ScrollView(GetScriptContext());
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ScrollView_SetTags_StringVector(ScrollView* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ScrollView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ScrollView* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Serializable::Serializable(Context* context) | File: ../Scene/Serializable.h
static Serializable* Serializable_Serializable_Context()
{
    return new Serializable(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Serializable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Serializable* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
static bool Serializer_WriteStringVector_StringVector(Serializer* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->WriteStringVector(value);
    return result;
}

// explicit Shader::Shader(Context* context) | File: ../Graphics/Shader.h
static Shader* Shader_Shader_Context()
{
    return new Shader(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Shader_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Shader* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Graphics/Material.h
static ShaderParameterAnimationInfo* ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_Material_String_ValueAnimation_WrapMode_float(Material *material, const String &name, ValueAnimation *attributeAnimation, WrapMode wrapMode, float speed)
{
    return new ShaderParameterAnimationInfo(material, name, attributeAnimation, wrapMode, speed);
}

// ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other) | File: ../Graphics/Material.h
static ShaderParameterAnimationInfo* ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo &other)
{
    return new ShaderParameterAnimationInfo(other);
}

// ShaderPrecache::ShaderPrecache(Context* context, const String& fileName) | File: ../Graphics/ShaderPrecache.h
static ShaderPrecache* ShaderPrecache_ShaderPrecache_Context_String(const String &fileName)
{
    return new ShaderPrecache(GetScriptContext(), fileName);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ShaderPrecache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ShaderPrecache* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) | File: ../Graphics/ShaderVariation.h
static ShaderVariation* ShaderVariation_ShaderVariation_Shader_ShaderType(Shader *owner, ShaderType type)
{
    return new ShaderVariation(owner, type);
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Skybox_GetLights_void(Skybox* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Skybox_GetVertexLights_void(Skybox* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit Skybox::Skybox(Context* context) | File: ../Graphics/Skybox.h
static Skybox* Skybox_Skybox_Context()
{
    return new Skybox(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Skybox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Skybox* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Slider_AddTags_StringVector(Slider* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Slider_GetChildren_void(Slider* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Slider_GetChildren_bool(Slider* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Slider_GetChildrenWithTag_String_bool(Slider* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Slider_GetTags_void(Slider* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Slider_SetTags_StringVector(Slider* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// explicit Slider::Slider(Context* context) | File: ../UI/Slider.h
static Slider* Slider_Slider_Context()
{
    return new Slider(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Slider_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Slider* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit SmoothedTransform::SmoothedTransform(Context* context) | File: ../Scene/SmoothedTransform.h
static SmoothedTransform* SmoothedTransform_SmoothedTransform_Context()
{
    return new SmoothedTransform(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SmoothedTransform_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SmoothedTransform* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// ShaderParameter::ShaderParameter(const String& name, unsigned glType, int location) | File: ../Graphics/ShaderVariation.h
static void ShaderParameter_ShaderParameter_String_unsigned_int(ShaderParameter* ptr, const String &name, unsigned glType, int location)
{
    new(ptr) ShaderParameter(name, glType, location);
}

// ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer) | File: ../Graphics/ShaderVariation.h
static void ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned_unsigned(ShaderParameter* ptr, ShaderType type, const String &name, unsigned offset, unsigned size, unsigned buffer)
{
    new(ptr) ShaderParameter(type, name, offset, size, buffer);
}

// ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount) | File: ../Graphics/ShaderVariation.h
static void ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned(ShaderParameter* ptr, ShaderType type, const String &name, unsigned reg, unsigned regCount)
{
    new(ptr) ShaderParameter(type, name, reg, regCount);
}

void ASRegisterGenerated_Members_Sa_Sm(asIScriptEngine* engine)
{
    // void Node::AddChild(Node* node, unsigned index=M_MAX_UNSIGNED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddChild(Node@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Scene, AddChild, (Node*, unsigned), void), AS_CALL_THISCALL);
    // void Node::AddComponent(Component* component, unsigned id, CreateMode mode) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddComponent(Component@+, uint, CreateMode)", AS_METHODPR(Scene, AddComponent, (Component*, unsigned, CreateMode), void), AS_CALL_THISCALL);
    // void Node::AddListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddListener(Component@+)", AS_METHODPR(Scene, AddListener, (Component*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Scene, AddRef, (), void), AS_CALL_THISCALL);
    // void Scene::AddReplicationState(NodeReplicationState* state) override | File: ../Scene/Scene.h
    // Error: type "NodeReplicationState*" can not automatically bind
    // void Scene::AddRequiredPackageFile(PackageFile* package) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void AddRequiredPackageFile(PackageFile@+)", AS_METHODPR(Scene, AddRequiredPackageFile, (PackageFile*), void), AS_CALL_THISCALL);
    // void Node::AddTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTag(const String&in)", AS_METHODPR(Scene, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void Node::AddTags(const String& tags, char separator=';') | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Scene, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Scene_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void AllocateNetworkState()", AS_METHODPR(Scene, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Node::ApplyAttributes() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ApplyAttributes()", AS_METHODPR(Scene, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void Scene::BeginThreadedUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void BeginThreadedUpdate()", AS_METHODPR(Scene, BeginThreadedUpdate, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Scene::CleanupConnection(Connection* connection) | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // void Scene::Clear(bool clearReplicated=true, bool clearLocal=true) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void Clear(bool = true, bool = true)", AS_METHODPR(Scene, Clear, (bool, bool), void), AS_CALL_THISCALL);
    // void Scene::ClearRequiredPackageFiles() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ClearRequiredPackageFiles()", AS_METHODPR(Scene, ClearRequiredPackageFiles, (), void), AS_CALL_THISCALL);
    // Node* Node::Clone(CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ Clone(CreateMode = REPLICATED)", AS_METHODPR(Scene, Clone, (CreateMode), Node*), AS_CALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CloneComponent(Component@+, uint = 0)", AS_METHODPR(Scene, CloneComponent, (Component*, unsigned), Component*), AS_CALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, CreateMode mode, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CloneComponent(Component@+, CreateMode, uint = 0)", AS_METHODPR(Scene, CloneComponent, (Component*, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // void Scene::ComponentAdded(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ComponentAdded(Component@+)", AS_METHODPR(Scene, ComponentAdded, (Component*), void), AS_CALL_THISCALL);
    // void Scene::ComponentRemoved(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ComponentRemoved(Component@+)", AS_METHODPR(Scene, ComponentRemoved, (Component*), void), AS_CALL_THISCALL);
    // Node* Node::CreateChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0, bool = false)", AS_METHODPR(Scene, CreateChild, (const String&, CreateMode, unsigned, bool), Node*), AS_CALL_THISCALL);
    // Node* Node::CreateChild(unsigned id, CreateMode mode, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateChild(uint, CreateMode, bool = false)", AS_METHODPR(Scene, CreateChild, (unsigned, CreateMode, bool), Node*), AS_CALL_THISCALL);
    // Component* Node::CreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Scene, CreateComponent, (StringHash, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::CreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Node* Node::CreateTemporaryChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateTemporaryChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Scene, CreateTemporaryChild, (const String&, CreateMode, unsigned), Node*), AS_CALL_THISCALL);
    // void Scene::DelayedMarkedDirty(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void DelayedMarkedDirty(Component@+)", AS_METHODPR(Scene, DelayedMarkedDirty, (Component*), void), AS_CALL_THISCALL);
    // void Scene::EndThreadedUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void EndThreadedUpdate()", AS_METHODPR(Scene, EndThreadedUpdate, (), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "bool GetAnimationEnabled() const", AS_METHODPR(Scene, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_animationEnabled() const", AS_METHODPR(Scene, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // int Scene::GetAsyncLoadingMs() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "int GetAsyncLoadingMs() const", AS_METHODPR(Scene, GetAsyncLoadingMs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_asyncLoadingMs() const", AS_METHODPR(Scene, GetAsyncLoadingMs, () const, int), AS_CALL_THISCALL);
    // LoadMode Scene::GetAsyncLoadMode() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "LoadMode GetAsyncLoadMode() const", AS_METHODPR(Scene, GetAsyncLoadMode, () const, LoadMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "LoadMode get_asyncLoadMode() const", AS_METHODPR(Scene, GetAsyncLoadMode, () const, LoadMode), AS_CALL_THISCALL);
    // float Scene::GetAsyncProgress() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetAsyncProgress() const", AS_METHODPR(Scene, GetAsyncProgress, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_asyncProgress() const", AS_METHODPR(Scene, GetAsyncProgress, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttribute(uint) const", AS_METHODPR(Scene, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Variant get_attributes(uint) const", AS_METHODPR(Scene, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttribute(const String&in) const", AS_METHODPR(Scene, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Scene, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Scene, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Scene, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Scene, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Scene, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Scene, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Scene, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool GetBlockEvents() const", AS_METHODPR(Scene, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const String& GetCategory() const", AS_METHODPR(Scene, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_category() const", AS_METHODPR(Scene, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Scene::GetChecksum() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetChecksum() const", AS_METHODPR(Scene, GetChecksum, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_checksum() const", AS_METHODPR(Scene, GetChecksum, () const, unsigned), AS_CALL_THISCALL);
    // Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(uint) const", AS_METHODPR(Scene, GetChild, (unsigned) const, Node*), AS_CALL_THISCALL);
    // Node* Node::GetChild(const String& name, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Scene, GetChild, (const String&, bool) const, Node*), AS_CALL_THISCALL);
    // Node* Node::GetChild(const char* name, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "const char*" can not automatically bind
    // Node* Node::GetChild(StringHash nameHash, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(StringHash, bool = false) const", AS_METHODPR(Scene, GetChild, (StringHash, bool) const, Node*), AS_CALL_THISCALL);
    // const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Scene_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetChildren(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Scene_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildrenWithComponent(StringHash, bool = false) const", AS_FUNCTION_OBJFIRST(Scene_GetChildrenWithComponent_StringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // void Node::GetChildrenWithTag(PODVector<Node*>& dest, const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Scene_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // Component* Scene::GetComponent(unsigned id) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetComponent(uint) const", AS_METHODPR(Scene, GetComponent, (unsigned) const, Component*), AS_CALL_THISCALL);
    // Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // template<class T> T* Node::GetComponent(bool recursive=false) const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Component@>@ GetComponents() const", AS_FUNCTION_OBJFIRST(Scene_GetComponents_void), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetDependencyNodes() const", AS_FUNCTION_OBJFIRST(Scene_GetDependencyNodes_void), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* Node::GetDerivedComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive=false, bool clearVector=true) const | File: ../Scene/Node.h
    // Not registered because template
    // Vector3 Node::GetDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetDirection() const", AS_METHODPR(Scene, GetDirection, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_direction() const", AS_METHODPR(Scene, GetDirection, () const, Vector3), AS_CALL_THISCALL);
    // float Scene::GetElapsedTime() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetElapsedTime() const", AS_METHODPR(Scene, GetElapsedTime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_elapsedTime() const", AS_METHODPR(Scene, GetElapsedTime, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "VariantMap& GetEventDataMap() const", AS_METHODPR(Scene, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "Object@+ GetEventSender() const", AS_METHODPR(Scene, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const String& Scene::GetFileName() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "const String& GetFileName() const", AS_METHODPR(Scene, GetFileName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_fileName() const", AS_METHODPR(Scene, GetFileName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Scene::GetFreeComponentID(CreateMode mode) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetFreeComponentID(CreateMode)", AS_METHODPR(Scene, GetFreeComponentID, (CreateMode), unsigned), AS_CALL_THISCALL);
    // unsigned Scene::GetFreeNodeID(CreateMode mode) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetFreeNodeID(CreateMode)", AS_METHODPR(Scene, GetFreeNodeID, (CreateMode), unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Scene, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Scene, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Scene, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const VariantMap& get_globalVars() const", AS_METHODPR(Scene, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Node::GetID() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetID() const", AS_METHODPR(Scene, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_id() const", AS_METHODPR(Scene, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Scene, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const Vector<WeakPtr<Component>> Node::GetListeners() const | File: ../Scene/Node.h
    // Error: type "const Vector<WeakPtr<Component>>" can not automatically bind
    // const String& Node::GetName() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const String& GetName() const", AS_METHODPR(Scene, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_name() const", AS_METHODPR(Scene, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Node::GetNameHash() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "StringHash GetNameHash() const", AS_METHODPR(Scene, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetParentAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector3& Node::GetNetPositionAttr() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetNetPositionAttr() const", AS_METHODPR(Scene, GetNetPositionAttr, () const, const Vector3&), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetRotationAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Scene::GetNode(unsigned id) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetNode(uint) const", AS_METHODPR(Scene, GetNode, (unsigned) const, Node*), AS_CALL_THISCALL);
    // bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const | File: ../Scene/Scene.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "uint GetNumAttributes() const", AS_METHODPR(Scene, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_numAttributes() const", AS_METHODPR(Scene, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumChildren(bool = false) const", AS_METHODPR(Scene, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumComponents() const", AS_METHODPR(Scene, GetNumComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_numComponents() const", AS_METHODPR(Scene, GetNumComponents, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "uint GetNumNetworkAttributes() const", AS_METHODPR(Scene, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumNetworkComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumNetworkComponents() const", AS_METHODPR(Scene, GetNumNetworkComponents, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumPersistentChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumPersistentChildren() const", AS_METHODPR(Scene, GetNumPersistentChildren, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumPersistentComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumPersistentComponents() const", AS_METHODPR(Scene, GetNumPersistentComponents, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Scene, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Scene, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Scene, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Component* Node::GetOrCreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetOrCreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Scene, GetOrCreateComponent, (StringHash, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::GetOrCreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Connection* Node::GetOwner() const | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::GetParent() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetParent() const", AS_METHODPR(Scene, GetParent, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ get_parent() const", AS_METHODPR(Scene, GetParent, () const, Node*), AS_CALL_THISCALL);
    // Component* Node::GetParentComponent(StringHash type, bool fullTraversal=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetParentComponent(StringHash, bool = false) const", AS_METHODPR(Scene, GetParentComponent, (StringHash, bool) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::GetParentComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> T* Node::GetParentDerivedComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector3& Node::GetPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetPosition() const", AS_METHODPR(Scene, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Vector3& get_position() const", AS_METHODPR(Scene, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // Vector2 Node::GetPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetPosition2D() const", AS_METHODPR(Scene, GetPosition2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_position2D() const", AS_METHODPR(Scene, GetPosition2D, () const, Vector2), AS_CALL_THISCALL);
    // const Vector<SharedPtr<PackageFile>>& Scene::GetRequiredPackageFiles() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ GetRequiredPackageFiles() const", AS_FUNCTION_OBJFIRST(Scene_GetRequiredPackageFiles_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ get_requiredPackageFiles() const", AS_FUNCTION_OBJFIRST(Scene_GetRequiredPackageFiles_void), AS_CALL_CDECL_OBJFIRST);
    // Vector3 Node::GetRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetRight() const", AS_METHODPR(Scene, GetRight, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_right() const", AS_METHODPR(Scene, GetRight, () const, Vector3), AS_CALL_THISCALL);
    // const Quaternion& Node::GetRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Quaternion& GetRotation() const", AS_METHODPR(Scene, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Quaternion& get_rotation() const", AS_METHODPR(Scene, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // float Node::GetRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "float GetRotation2D() const", AS_METHODPR(Scene, GetRotation2D, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_rotation2D() const", AS_METHODPR(Scene, GetRotation2D, () const, float), AS_CALL_THISCALL);
    // const Vector3& Node::GetScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetScale() const", AS_METHODPR(Scene, GetScale, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Vector3& get_scale() const", AS_METHODPR(Scene, GetScale, () const, const Vector3&), AS_CALL_THISCALL);
    // Vector2 Node::GetScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetScale2D() const", AS_METHODPR(Scene, GetScale2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_scale2D() const", AS_METHODPR(Scene, GetScale2D, () const, Vector2), AS_CALL_THISCALL);
    // Scene* Node::GetScene() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Scene@+ GetScene() const", AS_METHODPR(Scene, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Scene@+ get_scene() const", AS_METHODPR(Scene, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Vector3 Node::GetSignedWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetSignedWorldScale() const", AS_METHODPR(Scene, GetSignedWorldScale, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_signedWorldScale() const", AS_METHODPR(Scene, GetSignedWorldScale, () const, Vector3), AS_CALL_THISCALL);
    // float Scene::GetSmoothingConstant() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetSmoothingConstant() const", AS_METHODPR(Scene, GetSmoothingConstant, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_smoothingConstant() const", AS_METHODPR(Scene, GetSmoothingConstant, () const, float), AS_CALL_THISCALL);
    // float Scene::GetSnapThreshold() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetSnapThreshold() const", AS_METHODPR(Scene, GetSnapThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_snapThreshold() const", AS_METHODPR(Scene, GetSnapThreshold, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Scene, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& Node::GetTags() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Scene_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Scene", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Scene_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // float Scene::GetTimeScale() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetTimeScale() const", AS_METHODPR(Scene, GetTimeScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_timeScale() const", AS_METHODPR(Scene, GetTimeScale, () const, float), AS_CALL_THISCALL);
    // Matrix3x4 Node::GetTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Matrix3x4 GetTransform() const", AS_METHODPR(Scene, GetTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Matrix3x4 get_transform() const", AS_METHODPR(Scene, GetTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "StringHash GetType() const", AS_METHODPR(Scene, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "StringHash get_type() const", AS_METHODPR(Scene, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const String& GetTypeName() const", AS_METHODPR(Scene, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_typeName() const", AS_METHODPR(Scene, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Vector3 Node::GetUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetUp() const", AS_METHODPR(Scene, GetUp, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_up() const", AS_METHODPR(Scene, GetUp, () const, Vector3), AS_CALL_THISCALL);
    // const Variant& Node::GetVar(StringHash key) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Variant& GetVar(StringHash) const", AS_METHODPR(Scene, GetVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const String& Scene::GetVarName(StringHash hash) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "const String& GetVarName(StringHash) const", AS_METHODPR(Scene, GetVarName, (StringHash) const, const String&), AS_CALL_THISCALL);
    // String Scene::GetVarNamesAttr() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "String GetVarNamesAttr() const", AS_METHODPR(Scene, GetVarNamesAttr, () const, String), AS_CALL_THISCALL);
    // const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const VariantMap& GetVars() const", AS_METHODPR(Scene, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldDirection() const", AS_METHODPR(Scene, GetWorldDirection, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldDirection() const", AS_METHODPR(Scene, GetWorldDirection, () const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldPosition() const", AS_METHODPR(Scene, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldPosition() const", AS_METHODPR(Scene, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::GetWorldPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetWorldPosition2D() const", AS_METHODPR(Scene, GetWorldPosition2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_worldPosition2D() const", AS_METHODPR(Scene, GetWorldPosition2D, () const, Vector2), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldRight() const", AS_METHODPR(Scene, GetWorldRight, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldRight() const", AS_METHODPR(Scene, GetWorldRight, () const, Vector3), AS_CALL_THISCALL);
    // Quaternion Node::GetWorldRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Quaternion GetWorldRotation() const", AS_METHODPR(Scene, GetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Quaternion get_worldRotation() const", AS_METHODPR(Scene, GetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    // float Node::GetWorldRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "float GetWorldRotation2D() const", AS_METHODPR(Scene, GetWorldRotation2D, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_worldRotation2D() const", AS_METHODPR(Scene, GetWorldRotation2D, () const, float), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldScale() const", AS_METHODPR(Scene, GetWorldScale, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldScale() const", AS_METHODPR(Scene, GetWorldScale, () const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::GetWorldScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetWorldScale2D() const", AS_METHODPR(Scene, GetWorldScale2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_worldScale2D() const", AS_METHODPR(Scene, GetWorldScale2D, () const, Vector2), AS_CALL_THISCALL);
    // const Matrix3x4& Node::GetWorldTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Matrix3x4& GetWorldTransform() const", AS_METHODPR(Scene, GetWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Matrix3x4& get_worldTransform() const", AS_METHODPR(Scene, GetWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldUp() const", AS_METHODPR(Scene, GetWorldUp, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldUp() const", AS_METHODPR(Scene, GetWorldUp, () const, Vector3), AS_CALL_THISCALL);
    // bool Node::HasComponent(StringHash type) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool HasComponent(StringHash) const", AS_METHODPR(Scene, HasComponent, (StringHash) const, bool), AS_CALL_THISCALL);
    // template<class T> bool Node::HasComponent() const | File: ../Scene/Node.h
    // Not registered because template
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasEventHandlers() const", AS_METHODPR(Scene, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Scene, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Scene, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Node::HasTag(const String& tag) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool HasTag(const String&in) const", AS_METHODPR(Scene, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ Instantiate(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_METHODPR(Scene, Instantiate, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), AS_CALL_THISCALL);
    // Node* Scene::InstantiateJSON(const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(const JSONValue&in, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_METHODPR(Scene, InstantiateJSON, (const JSONValue&, const Vector3&, const Quaternion&, CreateMode), Node*), AS_CALL_THISCALL);
    // Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_METHODPR(Scene, InstantiateJSON, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), AS_CALL_THISCALL);
    // Node* Scene::InstantiateXML(const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(const XMLElement&in, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_METHODPR(Scene, InstantiateXML, (const XMLElement&, const Vector3&, const Quaternion&, CreateMode), Node*), AS_CALL_THISCALL);
    // Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_METHODPR(Scene, InstantiateXML, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), AS_CALL_THISCALL);
    // bool Scene::IsAsyncLoading() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsAsyncLoading() const", AS_METHODPR(Scene, IsAsyncLoading, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_asyncLoading() const", AS_METHODPR(Scene, IsAsyncLoading, () const, bool), AS_CALL_THISCALL);
    // bool Node::IsChildOf(Node* node) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsChildOf(Node@+) const", AS_METHODPR(Scene, IsChildOf, (Node*) const, bool), AS_CALL_THISCALL);
    // bool Node::IsDirty() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsDirty() const", AS_METHODPR(Scene, IsDirty, () const, bool), AS_CALL_THISCALL);
    // bool Node::IsEnabled() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsEnabled() const", AS_METHODPR(Scene, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_enabled() const", AS_METHODPR(Scene, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Node::IsEnabledSelf() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsEnabledSelf() const", AS_METHODPR(Scene, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_enabledSelf() const", AS_METHODPR(Scene, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Scene, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Node::IsReplicated() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsReplicated() const", AS_METHODPR(Scene, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_replicated() const", AS_METHODPR(Scene, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // static bool Scene::IsReplicatedID(unsigned id) | File: ../Scene/Scene.h
    engine->SetDefaultNamespace("Scene");
    engine->RegisterGlobalFunction("bool IsReplicatedID(uint)", AS_FUNCTIONPR(Scene::IsReplicatedID, (unsigned), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool IsTemporary() const", AS_METHODPR(Scene, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_temporary() const", AS_METHODPR(Scene, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Scene::IsThreadedUpdate() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsThreadedUpdate() const", AS_METHODPR(Scene, IsThreadedUpdate, () const, bool), AS_CALL_THISCALL);
    // bool Scene::IsUpdateEnabled() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsUpdateEnabled() const", AS_METHODPR(Scene, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_updateEnabled() const", AS_METHODPR(Scene, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Scene::Load(Deserializer& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool Load(Deserializer&)", AS_METHODPR(Scene, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Scene::LoadAsync(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsync(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", AS_METHODPR(Scene, LoadAsync, (File*, LoadMode), bool), AS_CALL_THISCALL);
    // bool Scene::LoadAsyncJSON(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncJSON(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", AS_METHODPR(Scene, LoadAsyncJSON, (File*, LoadMode), bool), AS_CALL_THISCALL);
    // bool Scene::LoadAsyncXML(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncXML(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", AS_METHODPR(Scene, LoadAsyncXML, (File*, LoadMode), bool), AS_CALL_THISCALL);
    // bool Scene::LoadJSON(const JSONValue& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Scene, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Scene::LoadJSON(Deserializer& source) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(Deserializer&)", AS_METHODPR(Scene, LoadJSON, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Scene::LoadXML(const XMLElement& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Scene, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool Scene::LoadXML(Deserializer& source) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadXML(Deserializer&)", AS_METHODPR(Scene, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 LocalToWorld(const Vector3&in) const", AS_METHODPR(Scene, LocalToWorld, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 LocalToWorld(const Vector4&in) const", AS_METHODPR(Scene, LocalToWorld, (const Vector4&) const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::LocalToWorld2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 LocalToWorld2D(const Vector2&in) const", AS_METHODPR(Scene, LocalToWorld2D, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // bool Node::LookAt(const Vector3& target, const Vector3& up=Vector3::UP, TransformSpace space=TS_WORLD) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool LookAt(const Vector3&in, const Vector3&in = Vector3::UP, TransformSpace = TS_WORLD)", AS_METHODPR(Scene, LookAt, (const Vector3&, const Vector3&, TransformSpace), bool), AS_CALL_THISCALL);
    // void Node::MarkDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void MarkDirty()", AS_METHODPR(Scene, MarkDirty, (), void), AS_CALL_THISCALL);
    // void Scene::MarkNetworkUpdate() override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate()", AS_METHODPR(Scene, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Scene::MarkNetworkUpdate(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate(Node@+)", AS_METHODPR(Scene, MarkNetworkUpdate, (Node*), void), AS_CALL_THISCALL);
    // void Scene::MarkNetworkUpdate(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate(Component@+)", AS_METHODPR(Scene, MarkNetworkUpdate, (Component*), void), AS_CALL_THISCALL);
    // void Scene::MarkReplicationDirty(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkReplicationDirty(Node@+)", AS_METHODPR(Scene, MarkReplicationDirty, (Node*), void), AS_CALL_THISCALL);
    // void Scene::NodeAdded(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeAdded(Node@+)", AS_METHODPR(Scene, NodeAdded, (Node*), void), AS_CALL_THISCALL);
    // void Scene::NodeRemoved(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeRemoved(Node@+)", AS_METHODPR(Scene, NodeRemoved, (Node*), void), AS_CALL_THISCALL);
    // void Scene::NodeTagAdded(Node* node, const String& tag) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeTagAdded(Node@+, const String&in)", AS_METHODPR(Scene, NodeTagAdded, (Node*, const String&), void), AS_CALL_THISCALL);
    // void Scene::NodeTagRemoved(Node* node, const String& tag) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeTagRemoved(Node@+, const String&in)", AS_METHODPR(Scene, NodeTagRemoved, (Node*, const String&), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Scene, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Scene, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Scene, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Node::Pitch(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Pitch(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Pitch, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Scene::PrepareNetworkUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void PrepareNetworkUpdate()", AS_METHODPR(Scene, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Scene, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Scene, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Scene", "int Refs() const", AS_METHODPR(Scene, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_refs() const", AS_METHODPR(Scene, Refs, () const, int), AS_CALL_THISCALL);
    // static void Scene::RegisterObject(Context* context) | File: ../Scene/Scene.h
    // Not registered because have @nobind mark
    // void Scene::RegisterVar(const String& name) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void RegisterVar(const String&in)", AS_METHODPR(Scene, RegisterVar, (const String&), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Scene, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Node::Remove() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Remove()", AS_METHODPR(Scene, Remove, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllChildren() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllChildren()", AS_METHODPR(Scene, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllComponents() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllComponents()", AS_METHODPR(Scene, RemoveAllComponents, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllTags() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllTags()", AS_METHODPR(Scene, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Scene, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Node::RemoveChild(Node* node) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveChild(Node@+)", AS_METHODPR(Scene, RemoveChild, (Node*), void), AS_CALL_THISCALL);
    // void Node::RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveChildren(bool, bool, bool)", AS_METHODPR(Scene, RemoveChildren, (bool, bool, bool), void), AS_CALL_THISCALL);
    // void Node::RemoveComponent(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponent(Component@+)", AS_METHODPR(Scene, RemoveComponent, (Component*), void), AS_CALL_THISCALL);
    // void Node::RemoveComponent(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponent(StringHash)", AS_METHODPR(Scene, RemoveComponent, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Node::RemoveComponent() | File: ../Scene/Node.h
    // Not registered because template
    // void Node::RemoveComponents(bool removeReplicated, bool removeLocal) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponents(bool, bool)", AS_METHODPR(Scene, RemoveComponents, (bool, bool), void), AS_CALL_THISCALL);
    // void Node::RemoveComponents(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponents(StringHash)", AS_METHODPR(Scene, RemoveComponents, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Node::RemoveComponents() | File: ../Scene/Node.h
    // Not registered because template
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void RemoveInstanceDefault()", AS_METHODPR(Scene, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Node::RemoveListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveListener(Component@+)", AS_METHODPR(Scene, RemoveListener, (Component*), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void RemoveObjectAnimation()", AS_METHODPR(Scene, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool Node::RemoveTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool RemoveTag(const String&in)", AS_METHODPR(Scene, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void Node::ReorderComponent(Component* component, unsigned index) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ReorderComponent(Component@+, uint)", AS_METHODPR(Scene, ReorderComponent, (Component*, unsigned), void), AS_CALL_THISCALL);
    // void Node::ResetDeepEnabled() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ResetDeepEnabled()", AS_METHODPR(Scene, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Node::ResetScene() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ResetScene()", AS_METHODPR(Scene, ResetScene, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void ResetToDefault()", AS_METHODPR(Scene, ResetToDefault, (), void), AS_CALL_THISCALL);
    // void Node::Roll(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Roll(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Roll, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Rotate(const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Rotate(const Quaternion&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Rotate, (const Quaternion&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Rotate2D(float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Rotate2D(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Rotate2D, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RotateAround(const Vector3&in, const Quaternion&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, RotateAround, (const Vector3&, const Quaternion&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::RotateAround2D(const Vector2& point, float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RotateAround2D(const Vector2&in, float, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, RotateAround2D, (const Vector2&, float, TransformSpace), void), AS_CALL_THISCALL);
    // bool Scene::Save(Serializer& dest) const override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool Save(Serializer&) const", AS_METHODPR(Scene, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveDefaultAttributes() const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool SaveDefaultAttributes() const", AS_METHODPR(Scene, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Scene::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool SaveJSON(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Scene, SaveJSON, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveJSON(JSONValue& dest) const override | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Node::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Scene::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Scene, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveXML(XMLElement& dest) const override | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Node::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // void Node::Scale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale(float)", AS_METHODPR(Scene, Scale, (float), void), AS_CALL_THISCALL);
    // void Node::Scale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale(const Vector3&in)", AS_METHODPR(Scene, Scale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::Scale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale2D(const Vector2&in)", AS_METHODPR(Scene, Scale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // explicit Scene::Scene(Context* context) | File: ../Scene/Scene.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_FACTORY, "Scene@+ f()", AS_FUNCTION(Scene_Scene_Context), AS_CALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SendEvent(StringHash)", AS_METHODPR(Scene, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Scene, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAnimationEnabled(bool)", AS_METHODPR(Scene, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_animationEnabled(bool)", AS_METHODPR(Scene, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAnimationTime(float)", AS_METHODPR(Scene, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Scene::SetAsyncLoadingMs(int ms) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetAsyncLoadingMs(int)", AS_METHODPR(Scene, SetAsyncLoadingMs, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_asyncLoadingMs(int)", AS_METHODPR(Scene, SetAsyncLoadingMs, (int), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Scene, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Scene, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Scene, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Scene, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Scene, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Scene, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Scene, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SetBlockEvents(bool)", AS_METHODPR(Scene, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Node::SetDeepEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetDeepEnabled(bool)", AS_METHODPR(Scene, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void Node::SetDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetDirection(const Vector3&in)", AS_METHODPR(Scene, SetDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_direction(const Vector3&in)", AS_METHODPR(Scene, SetDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void Scene::SetElapsedTime(float time) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetElapsedTime(float)", AS_METHODPR(Scene, SetElapsedTime, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_elapsedTime(float)", AS_METHODPR(Scene, SetElapsedTime, (float), void), AS_CALL_THISCALL);
    // void Node::SetEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetEnabled(bool)", AS_METHODPR(Scene, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_enabled(bool)", AS_METHODPR(Scene, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Node::SetEnabledRecursive(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetEnabledRecursive(bool)", AS_METHODPR(Scene, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Scene, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Scene, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Node::SetID(unsigned id) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetID(uint)", AS_METHODPR(Scene, SetID, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_id(uint)", AS_METHODPR(Scene, SetID, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetInstanceDefault(bool)", AS_METHODPR(Scene, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Scene, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Node::SetName(const String& name) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetName(const String&in)", AS_METHODPR(Scene, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_name(const String&in)", AS_METHODPR(Scene, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Node::SetNetParentAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetNetPositionAttr(const Vector3& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetNetPositionAttr(const Vector3&in)", AS_METHODPR(Scene, SetNetPositionAttr, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetNetRotationAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Scene, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Scene, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Scene, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // void Node::SetParent(Node* parent) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetParent(Node@+)", AS_METHODPR(Scene, SetParent, (Node*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_parent(Node@+)", AS_METHODPR(Scene, SetParent, (Node*), void), AS_CALL_THISCALL);
    // void Node::SetPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition(const Vector3&in)", AS_METHODPR(Scene, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_position(const Vector3&in)", AS_METHODPR(Scene, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition2D(const Vector2&in)", AS_METHODPR(Scene, SetPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_position2D(const Vector2&in)", AS_METHODPR(Scene, SetPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition2D(float, float)", AS_METHODPR(Scene, SetPosition2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetPositionSilent(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPositionSilent(const Vector3&in)", AS_METHODPR(Scene, SetPositionSilent, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotation(const Quaternion&in)", AS_METHODPR(Scene, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_rotation(const Quaternion&in)", AS_METHODPR(Scene, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotation2D(float)", AS_METHODPR(Scene, SetRotation2D, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_rotation2D(float)", AS_METHODPR(Scene, SetRotation2D, (float), void), AS_CALL_THISCALL);
    // void Node::SetRotationSilent(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotationSilent(const Quaternion&in)", AS_METHODPR(Scene, SetRotationSilent, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale(float)", AS_METHODPR(Scene, SetScale, (float), void), AS_CALL_THISCALL);
    // void Node::SetScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale(const Vector3&in)", AS_METHODPR(Scene, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_scale(const Vector3&in)", AS_METHODPR(Scene, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale2D(const Vector2&in)", AS_METHODPR(Scene, SetScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_scale2D(const Vector2&in)", AS_METHODPR(Scene, SetScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale2D(float, float)", AS_METHODPR(Scene, SetScale2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetScaleSilent(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScaleSilent(const Vector3&in)", AS_METHODPR(Scene, SetScaleSilent, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetScene(Scene* scene) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScene(Scene@+)", AS_METHODPR(Scene, SetScene, (Scene*), void), AS_CALL_THISCALL);
    // void Scene::SetSmoothingConstant(float constant) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetSmoothingConstant(float)", AS_METHODPR(Scene, SetSmoothingConstant, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_smoothingConstant(float)", AS_METHODPR(Scene, SetSmoothingConstant, (float), void), AS_CALL_THISCALL);
    // void Scene::SetSnapThreshold(float threshold) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetSnapThreshold(float)", AS_METHODPR(Scene, SetSnapThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_snapThreshold(float)", AS_METHODPR(Scene, SetSnapThreshold, (float), void), AS_CALL_THISCALL);
    // void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Scene_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetTemporary(bool)", AS_METHODPR(Scene, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_temporary(bool)", AS_METHODPR(Scene, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Scene::SetTimeScale(float scale) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetTimeScale(float)", AS_METHODPR(Scene, SetTimeScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_timeScale(float)", AS_METHODPR(Scene, SetTimeScale, (float), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in, float)", AS_METHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Matrix3x4& matrix) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Matrix3x4&in)", AS_METHODPR(Scene, SetTransform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float)", AS_METHODPR(Scene, SetTransform2D, (const Vector2&, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float, float)", AS_METHODPR(Scene, SetTransform2D, (const Vector2&, float, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float, const Vector2&in)", AS_METHODPR(Scene, SetTransform2D, (const Vector2&, float, const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransformSilent(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Scene, SetTransformSilent, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Scene::SetUpdateEnabled(bool enable) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetUpdateEnabled(bool)", AS_METHODPR(Scene, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_updateEnabled(bool)", AS_METHODPR(Scene, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    // void Node::SetVar(StringHash key, const Variant& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Scene, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Scene::SetVarNamesAttr(const String& value) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetVarNamesAttr(const String&in)", AS_METHODPR(Scene, SetVarNamesAttr, (const String&), void), AS_CALL_THISCALL);
    // void Node::SetWorldDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldDirection(const Vector3&in)", AS_METHODPR(Scene, SetWorldDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldDirection(const Vector3&in)", AS_METHODPR(Scene, SetWorldDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition(const Vector3&in)", AS_METHODPR(Scene, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldPosition(const Vector3&in)", AS_METHODPR(Scene, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition2D(const Vector2&in)", AS_METHODPR(Scene, SetWorldPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldPosition2D(const Vector2&in)", AS_METHODPR(Scene, SetWorldPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition2D(float, float)", AS_METHODPR(Scene, SetWorldPosition2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldRotation(const Quaternion&in)", AS_METHODPR(Scene, SetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldRotation(const Quaternion&in)", AS_METHODPR(Scene, SetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetWorldRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldRotation2D(float)", AS_METHODPR(Scene, SetWorldRotation2D, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldRotation2D(float)", AS_METHODPR(Scene, SetWorldRotation2D, (float), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale(float)", AS_METHODPR(Scene, SetWorldScale, (float), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale(const Vector3&in)", AS_METHODPR(Scene, SetWorldScale, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldScale(const Vector3&in)", AS_METHODPR(Scene, SetWorldScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale2D(const Vector2&in)", AS_METHODPR(Scene, SetWorldScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldScale2D(const Vector2&in)", AS_METHODPR(Scene, SetWorldScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale2D(float, float)", AS_METHODPR(Scene, SetWorldScale2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", AS_METHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Matrix3x4& worldTransform) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Matrix3x4&in)", AS_METHODPR(Scene, SetWorldTransform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float)", AS_METHODPR(Scene, SetWorldTransform2D, (const Vector2&, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float, float)", AS_METHODPR(Scene, SetWorldTransform2D, (const Vector2&, float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float, const Vector2&in)", AS_METHODPR(Scene, SetWorldTransform2D, (const Vector2&, float, const Vector2&), void), AS_CALL_THISCALL);
    // void Scene::StopAsyncLoading() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void StopAsyncLoading()", AS_METHODPR(Scene, StopAsyncLoading, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Node::Translate(const Vector3& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Translate(const Vector3&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Translate, (const Vector3&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Translate2D(const Vector2& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Translate2D(const Vector2&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Translate2D, (const Vector2&, TransformSpace), void), AS_CALL_THISCALL);
    // void Scene::UnregisterAllVars() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void UnregisterAllVars()", AS_METHODPR(Scene, UnregisterAllVars, (), void), AS_CALL_THISCALL);
    // void Scene::UnregisterVar(const String& name) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void UnregisterVar(const String&in)", AS_METHODPR(Scene, UnregisterVar, (const String&), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromAllEvents()", AS_METHODPR(Scene, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Scene_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Scene, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Scene, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Scene, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Scene::Update(float timeStep) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void Update(float)", AS_METHODPR(Scene, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Scene", "int WeakRefs() const", AS_METHODPR(Scene, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_weakRefs() const", AS_METHODPR(Scene, WeakRefs, () const, int), AS_CALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 WorldToLocal(const Vector3&in) const", AS_METHODPR(Scene, WorldToLocal, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 WorldToLocal(const Vector4&in) const", AS_METHODPR(Scene, WorldToLocal, (const Vector4&) const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::WorldToLocal2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 WorldToLocal2D(const Vector2&in) const", AS_METHODPR(Scene, WorldToLocal2D, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Scene, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Scene, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Scene, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Node::Yaw(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Yaw(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Scene, Yaw, (float, TransformSpace), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Node
    REGISTER_MANUAL_PART_Node(Scene, "Scene")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Scene, "Scene")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Scene, "Scene")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Scene, "Scene")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Scene, "Scene")
#endif
#ifdef REGISTER_MANUAL_PART_Scene
    REGISTER_MANUAL_PART_Scene(Scene, "Scene")
#endif
    RegisterSubclass<Node, Scene>(engine, "Node", "Scene");
    RegisterSubclass<Animatable, Scene>(engine, "Animatable", "Scene");
    RegisterSubclass<Serializable, Scene>(engine, "Serializable", "Scene");
    RegisterSubclass<Object, Scene>(engine, "Object", "Scene");
    RegisterSubclass<RefCounted, Scene>(engine, "RefCounted", "Scene");

    // void SceneResolver::AddComponent(unsigned oldID, Component* component) | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void AddComponent(uint, Component@+)", AS_METHODPR(SceneResolver, AddComponent, (unsigned, Component*), void), AS_CALL_THISCALL);
    // void SceneResolver::AddNode(unsigned oldID, Node* node) | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void AddNode(uint, Node@+)", AS_METHODPR(SceneResolver, AddNode, (unsigned, Node*), void), AS_CALL_THISCALL);
    // void SceneResolver::Reset() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void Reset()", AS_METHODPR(SceneResolver, Reset, (), void), AS_CALL_THISCALL);
    // void SceneResolver::Resolve() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void Resolve()", AS_METHODPR(SceneResolver, Resolve, (), void), AS_CALL_THISCALL);
    // SceneResolver& SceneResolver::operator=(const SceneResolver&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SceneResolver>(engine, "SceneResolver");
#ifdef REGISTER_MANUAL_PART_SceneResolver
    REGISTER_MANUAL_PART_SceneResolver(SceneResolver, "SceneResolver")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddChild(UIElement@+)", AS_METHODPR(ScrollBar, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ScrollBar, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTag(const String&in)", AS_METHODPR(ScrollBar, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(ScrollBar, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ScrollBar_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AdjustScissor(IntRect&)", AS_METHODPR(ScrollBar, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void AllocateNetworkState()", AS_METHODPR(ScrollBar, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void ScrollBar::ApplyAttributes() override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void ApplyAttributes()", AS_METHODPR(ScrollBar, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void BringToFront()", AS_METHODPR(ScrollBar, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ScrollBar::ChangeValue(float delta) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void ChangeValue(float)", AS_METHODPR(ScrollBar, ChangeValue, (float), void), AS_CALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(ScrollBar, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void DisableLayoutUpdate()", AS_METHODPR(ScrollBar, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(ScrollBar, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void EnableLayoutUpdate()", AS_METHODPR(ScrollBar, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(ScrollBar, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint FindChild(UIElement@+) const", AS_METHODPR(ScrollBar, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetAnimationEnabled() const", AS_METHODPR(ScrollBar, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_animationEnabled() const", AS_METHODPR(ScrollBar, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetAppliedStyle() const", AS_METHODPR(ScrollBar, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_style() const", AS_METHODPR(ScrollBar, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttribute(uint) const", AS_METHODPR(ScrollBar, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Variant get_attributes(uint) const", AS_METHODPR(ScrollBar, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttribute(const String&in) const", AS_METHODPR(ScrollBar, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ScrollBar, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ScrollBar, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ScrollBar, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ScrollBar, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ScrollBar, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ScrollBar, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ScrollBar, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // Button* ScrollBar::GetBackButton() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Button@+ GetBackButton() const", AS_METHODPR(ScrollBar, GetBackButton, () const, Button*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_backButton() const", AS_METHODPR(ScrollBar, GetBackButton, () const, Button*), AS_CALL_THISCALL);
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "BlendMode GetBlendMode() const", AS_METHODPR(ScrollBar, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "BlendMode get_blendMode() const", AS_METHODPR(ScrollBar, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBlockEvents() const", AS_METHODPR(ScrollBar, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetBorder() const", AS_METHODPR(ScrollBar, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_border() const", AS_METHODPR(ScrollBar, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBringToBack() const", AS_METHODPR(ScrollBar, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_bringToBack() const", AS_METHODPR(ScrollBar, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBringToFront() const", AS_METHODPR(ScrollBar, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_bringToFront() const", AS_METHODPR(ScrollBar, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetCategory() const", AS_METHODPR(ScrollBar, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_category() const", AS_METHODPR(ScrollBar, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(uint) const", AS_METHODPR(ScrollBar, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_children(uint) const", AS_METHODPR(ScrollBar, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(ScrollBar, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(ScrollBar, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetChildOffset() const", AS_METHODPR(ScrollBar, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_childOffset() const", AS_METHODPR(ScrollBar, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(ScrollBar_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(ScrollBar_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(ScrollBar_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetClipBorder() const", AS_METHODPR(ScrollBar, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_clipBorder() const", AS_METHODPR(ScrollBar, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetClipChildren() const", AS_METHODPR(ScrollBar, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_clipChildren() const", AS_METHODPR(ScrollBar, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetColor(Corner) const", AS_METHODPR(ScrollBar, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Color& get_colors(Corner) const", AS_METHODPR(ScrollBar, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetColorAttr() const", AS_METHODPR(ScrollBar, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntRect GetCombinedScreenRect()", AS_METHODPR(ScrollBar, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "IntRect get_combinedScreenRect()", AS_METHODPR(ScrollBar, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(ScrollBar, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetDerivedColor() const", AS_METHODPR(ScrollBar, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "float GetDerivedOpacity() const", AS_METHODPR(ScrollBar, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_derivedOpacity() const", AS_METHODPR(ScrollBar, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(ScrollBar, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_disabledOffset() const", AS_METHODPR(ScrollBar, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(ScrollBar, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(ScrollBar, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetDragButtonCount() const", AS_METHODPR(ScrollBar, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_dragButtonCount() const", AS_METHODPR(ScrollBar, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(ScrollBar, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(ScrollBar, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(ScrollBar, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // float ScrollBar::GetEffectiveScrollStep() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetEffectiveScrollStep() const", AS_METHODPR(ScrollBar, GetEffectiveScrollStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_effectiveScrollStep() const", AS_METHODPR(ScrollBar, GetEffectiveScrollStep, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetElementEventSender() const", AS_METHODPR(ScrollBar, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetEnableAnchor() const", AS_METHODPR(ScrollBar, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enableAnchor() const", AS_METHODPR(ScrollBar, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "VariantMap& GetEventDataMap() const", AS_METHODPR(ScrollBar, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "Object@+ GetEventSender() const", AS_METHODPR(ScrollBar, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "FocusMode GetFocusMode() const", AS_METHODPR(ScrollBar, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "FocusMode get_focusMode() const", AS_METHODPR(ScrollBar, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // Button* ScrollBar::GetForwardButton() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Button@+ GetForwardButton() const", AS_METHODPR(ScrollBar, GetForwardButton, () const, Button*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_forwardButton() const", AS_METHODPR(ScrollBar, GetForwardButton, () const, Button*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ScrollBar, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ScrollBar, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ScrollBar, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& get_globalVars() const", AS_METHODPR(ScrollBar, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetHeight() const", AS_METHODPR(ScrollBar, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_height() const", AS_METHODPR(ScrollBar, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(ScrollBar, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(ScrollBar, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetHoverOffset() const", AS_METHODPR(ScrollBar, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_hoverOffset() const", AS_METHODPR(ScrollBar, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetImageBorder() const", AS_METHODPR(ScrollBar, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_imageBorder() const", AS_METHODPR(ScrollBar, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetImageRect() const", AS_METHODPR(ScrollBar, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_imageRect() const", AS_METHODPR(ScrollBar, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndent() const", AS_METHODPR(ScrollBar, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indent() const", AS_METHODPR(ScrollBar, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndentSpacing() const", AS_METHODPR(ScrollBar, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indentSpacing() const", AS_METHODPR(ScrollBar, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndentWidth() const", AS_METHODPR(ScrollBar, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indentWidth() const", AS_METHODPR(ScrollBar, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ScrollBar, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetLayoutBorder() const", AS_METHODPR(ScrollBar, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_layoutBorder() const", AS_METHODPR(ScrollBar, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetLayoutElementMaxSize() const", AS_METHODPR(ScrollBar, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(ScrollBar, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(ScrollBar, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "LayoutMode GetLayoutMode() const", AS_METHODPR(ScrollBar, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "LayoutMode get_layoutMode() const", AS_METHODPR(ScrollBar, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetLayoutSpacing() const", AS_METHODPR(ScrollBar, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_layoutSpacing() const", AS_METHODPR(ScrollBar, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "Material@+ GetMaterial() const", AS_METHODPR(ScrollBar, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Material@+ get_material() const", AS_METHODPR(ScrollBar, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetMaterialAttr() const", AS_METHODPR(ScrollBar, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetMaxAnchor() const", AS_METHODPR(ScrollBar, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_maxAnchor() const", AS_METHODPR(ScrollBar, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMaxHeight() const", AS_METHODPR(ScrollBar, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_maxHeight() const", AS_METHODPR(ScrollBar, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMaxOffset() const", AS_METHODPR(ScrollBar, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_maxOffset() const", AS_METHODPR(ScrollBar, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMaxSize() const", AS_METHODPR(ScrollBar, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_maxSize() const", AS_METHODPR(ScrollBar, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMaxWidth() const", AS_METHODPR(ScrollBar, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_maxWidth() const", AS_METHODPR(ScrollBar, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetMinAnchor() const", AS_METHODPR(ScrollBar, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_minAnchor() const", AS_METHODPR(ScrollBar, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMinHeight() const", AS_METHODPR(ScrollBar, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_minHeight() const", AS_METHODPR(ScrollBar, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMinOffset() const", AS_METHODPR(ScrollBar, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_minOffset() const", AS_METHODPR(ScrollBar, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMinSize() const", AS_METHODPR(ScrollBar, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_minSize() const", AS_METHODPR(ScrollBar, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMinWidth() const", AS_METHODPR(ScrollBar, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_minWidth() const", AS_METHODPR(ScrollBar, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetName() const", AS_METHODPR(ScrollBar, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_name() const", AS_METHODPR(ScrollBar, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumAttributes() const", AS_METHODPR(ScrollBar, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_numAttributes() const", AS_METHODPR(ScrollBar, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumChildren(bool = false) const", AS_METHODPR(ScrollBar, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_numChildren(bool = false) const", AS_METHODPR(ScrollBar, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumNetworkAttributes() const", AS_METHODPR(ScrollBar, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ScrollBar, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ScrollBar, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ScrollBar, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "float GetOpacity() const", AS_METHODPR(ScrollBar, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_opacity() const", AS_METHODPR(ScrollBar, GetOpacity, () const, float), AS_CALL_THISCALL);
    // Orientation ScrollBar::GetOrientation() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Orientation GetOrientation() const", AS_METHODPR(ScrollBar, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Orientation get_orientation() const", AS_METHODPR(ScrollBar, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetParent() const", AS_METHODPR(ScrollBar, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_parent() const", AS_METHODPR(ScrollBar, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetPivot() const", AS_METHODPR(ScrollBar, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_pivot() const", AS_METHODPR(ScrollBar, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetPosition() const", AS_METHODPR(ScrollBar, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_position() const", AS_METHODPR(ScrollBar, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetPriority() const", AS_METHODPR(ScrollBar, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_priority() const", AS_METHODPR(ScrollBar, GetPriority, () const, int), AS_CALL_THISCALL);
    // float ScrollBar::GetRange() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetRange() const", AS_METHODPR(ScrollBar, GetRange, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_range() const", AS_METHODPR(ScrollBar, GetRange, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetRoot() const", AS_METHODPR(ScrollBar, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_root() const", AS_METHODPR(ScrollBar, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetScreenPosition() const", AS_METHODPR(ScrollBar, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_screenPosition() const", AS_METHODPR(ScrollBar, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // float ScrollBar::GetScrollStep() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetScrollStep() const", AS_METHODPR(ScrollBar, GetScrollStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_scrollStep() const", AS_METHODPR(ScrollBar, GetScrollStep, () const, float), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetSize() const", AS_METHODPR(ScrollBar, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_size() const", AS_METHODPR(ScrollBar, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // Slider* ScrollBar::GetSlider() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Slider@+ GetSlider() const", AS_METHODPR(ScrollBar, GetSlider, () const, Slider*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Slider@+ get_slider() const", AS_METHODPR(ScrollBar, GetSlider, () const, Slider*), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetSortChildren() const", AS_METHODPR(ScrollBar, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_sortChildren() const", AS_METHODPR(ScrollBar, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // float ScrollBar::GetStepFactor() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetStepFactor() const", AS_METHODPR(ScrollBar, GetStepFactor, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_stepFactor() const", AS_METHODPR(ScrollBar, GetStepFactor, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ScrollBar, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(ScrollBar_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ScrollBar", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(ScrollBar_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "Texture@+ GetTexture() const", AS_METHODPR(ScrollBar, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Texture@+ get_texture() const", AS_METHODPR(ScrollBar, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetTextureAttr() const", AS_METHODPR(ScrollBar, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "TraversalMode GetTraversalMode() const", AS_METHODPR(ScrollBar, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "TraversalMode get_traversalMode() const", AS_METHODPR(ScrollBar, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "StringHash GetType() const", AS_METHODPR(ScrollBar, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "StringHash get_type() const", AS_METHODPR(ScrollBar, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetTypeName() const", AS_METHODPR(ScrollBar, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_typeName() const", AS_METHODPR(ScrollBar, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetUseDerivedOpacity() const", AS_METHODPR(ScrollBar, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_useDerivedOpacity() const", AS_METHODPR(ScrollBar, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // float ScrollBar::GetValue() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetValue() const", AS_METHODPR(ScrollBar, GetValue, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_value() const", AS_METHODPR(ScrollBar, GetValue, () const, float), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(ScrollBar, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& GetVars() const", AS_METHODPR(ScrollBar, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(ScrollBar, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(ScrollBar, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetWidth() const", AS_METHODPR(ScrollBar, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_width() const", AS_METHODPR(ScrollBar, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasColorGradient() const", AS_METHODPR(ScrollBar, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_colorGradient() const", AS_METHODPR(ScrollBar, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasEventHandlers() const", AS_METHODPR(ScrollBar, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasFocus() const", AS_METHODPR(ScrollBar, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_focus() const", AS_METHODPR(ScrollBar, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ScrollBar, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ScrollBar, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasTag(const String&in) const", AS_METHODPR(ScrollBar, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void InsertChild(uint, UIElement@+)", AS_METHODPR(ScrollBar, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsChildOf(UIElement@+) const", AS_METHODPR(ScrollBar, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEditable() const", AS_METHODPR(ScrollBar, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_editable() const", AS_METHODPR(ScrollBar, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsElementEventSender() const", AS_METHODPR(ScrollBar, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_elementEventSender() const", AS_METHODPR(ScrollBar, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEnabled() const", AS_METHODPR(ScrollBar, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enabled() const", AS_METHODPR(ScrollBar, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEnabledSelf() const", AS_METHODPR(ScrollBar, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enabledSelf() const", AS_METHODPR(ScrollBar, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedHeight() const", AS_METHODPR(ScrollBar, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedHeight() const", AS_METHODPR(ScrollBar, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedSize() const", AS_METHODPR(ScrollBar, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedSize() const", AS_METHODPR(ScrollBar, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedWidth() const", AS_METHODPR(ScrollBar, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedWidth() const", AS_METHODPR(ScrollBar, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsHovering() const", AS_METHODPR(ScrollBar, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_hovering() const", AS_METHODPR(ScrollBar, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInside(IntVector2, bool)", AS_METHODPR(ScrollBar, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(ScrollBar, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ScrollBar, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInternal() const", AS_METHODPR(ScrollBar, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_internal() const", AS_METHODPR(ScrollBar, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsSelected() const", AS_METHODPR(ScrollBar, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_selected() const", AS_METHODPR(ScrollBar, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsTemporary() const", AS_METHODPR(ScrollBar, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_temporary() const", AS_METHODPR(ScrollBar, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsTiled() const", AS_METHODPR(ScrollBar, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_tiled() const", AS_METHODPR(ScrollBar, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsVisible() const", AS_METHODPR(ScrollBar, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_visible() const", AS_METHODPR(ScrollBar, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsVisibleEffective() const", AS_METHODPR(ScrollBar, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_visibleEffective() const", AS_METHODPR(ScrollBar, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsWheelHandler() const", AS_METHODPR(ScrollBar, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(ScrollBar, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool Load(Deserializer&)", AS_METHODPR(ScrollBar, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ScrollBar, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ScrollBar, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ScrollBar, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ScrollBar, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(Deserializer&)", AS_METHODPR(ScrollBar, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void MarkNetworkUpdate()", AS_METHODPR(ScrollBar, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(ScrollBar, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(ScrollBar, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(ScrollBar, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ScrollBar, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ScrollBar, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollBar, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnIndentSet()", AS_METHODPR(ScrollBar, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ScrollBar, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(ScrollBar, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ScrollBar::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(ScrollBar, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ScrollBar, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void ScrollBar::OnSetEditable() override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void OnSetEditable()", AS_METHODPR(ScrollBar, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnTextInput(const String&in)", AS_METHODPR(ScrollBar, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ScrollBar, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ScrollBar, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ScrollBar, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollBar", "int Refs() const", AS_METHODPR(ScrollBar, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_refs() const", AS_METHODPR(ScrollBar, Refs, () const, int), AS_CALL_THISCALL);
    // static void ScrollBar::RegisterObject(Context* context) | File: ../UI/ScrollBar.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ScrollBar, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void Remove()", AS_METHODPR(ScrollBar, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAllChildren()", AS_METHODPR(ScrollBar, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAllTags()", AS_METHODPR(ScrollBar, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ScrollBar, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(ScrollBar, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveChildAtIndex(uint)", AS_METHODPR(ScrollBar, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveInstanceDefault()", AS_METHODPR(ScrollBar, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveObjectAnimation()", AS_METHODPR(ScrollBar, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool RemoveTag(const String&in)", AS_METHODPR(ScrollBar, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void ResetDeepEnabled()", AS_METHODPR(ScrollBar, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void ResetToDefault()", AS_METHODPR(ScrollBar, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool Save(Serializer&) const", AS_METHODPR(ScrollBar, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveDefaultAttributes() const", AS_METHODPR(ScrollBar, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ScrollBar, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveXML(XMLElement&) const", AS_METHODPR(ScrollBar, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(ScrollBar, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(ScrollBar, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // explicit ScrollBar::ScrollBar(Context* context) | File: ../UI/ScrollBar.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_FACTORY, "ScrollBar@+ f()", AS_FUNCTION(ScrollBar_ScrollBar_Context), AS_CALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SendEvent(StringHash)", AS_METHODPR(ScrollBar, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ScrollBar, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(ScrollBar, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAnimationEnabled(bool)", AS_METHODPR(ScrollBar, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_animationEnabled(bool)", AS_METHODPR(ScrollBar, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAnimationTime(float)", AS_METHODPR(ScrollBar, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ScrollBar, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ScrollBar, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ScrollBar, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ScrollBar, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ScrollBar, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ScrollBar, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ScrollBar, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBlendMode(BlendMode)", AS_METHODPR(ScrollBar, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_blendMode(BlendMode)", AS_METHODPR(ScrollBar, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBlockEvents(bool)", AS_METHODPR(ScrollBar, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_border(const IntRect&in)", AS_METHODPR(ScrollBar, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBringToBack(bool)", AS_METHODPR(ScrollBar, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_bringToBack(bool)", AS_METHODPR(ScrollBar, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBringToFront(bool)", AS_METHODPR(ScrollBar, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_bringToFront(bool)", AS_METHODPR(ScrollBar, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetClipBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_clipBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetClipChildren(bool)", AS_METHODPR(ScrollBar, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_clipChildren(bool)", AS_METHODPR(ScrollBar, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetColor(const Color&in)", AS_METHODPR(ScrollBar, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_color(const Color&in)", AS_METHODPR(ScrollBar, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetColor(Corner, const Color&in)", AS_METHODPR(ScrollBar, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_colors(Corner, const Color&in)", AS_METHODPR(ScrollBar, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDeepEnabled(bool)", AS_METHODPR(ScrollBar, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(ScrollBar, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(ScrollBar, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDisabledOffset(int, int)", AS_METHODPR(ScrollBar, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(ScrollBar, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(ScrollBar, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEditable(bool)", AS_METHODPR(ScrollBar, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_editable(bool)", AS_METHODPR(ScrollBar, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetElementEventSender(bool)", AS_METHODPR(ScrollBar, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_elementEventSender(bool)", AS_METHODPR(ScrollBar, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnableAnchor(bool)", AS_METHODPR(ScrollBar, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_enableAnchor(bool)", AS_METHODPR(ScrollBar, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnabled(bool)", AS_METHODPR(ScrollBar, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_enabled(bool)", AS_METHODPR(ScrollBar, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnabledRecursive(bool)", AS_METHODPR(ScrollBar, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedHeight(int)", AS_METHODPR(ScrollBar, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedSize(int, int)", AS_METHODPR(ScrollBar, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedWidth(int)", AS_METHODPR(ScrollBar, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFocus(bool)", AS_METHODPR(ScrollBar, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_focus(bool)", AS_METHODPR(ScrollBar, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFocusMode(FocusMode)", AS_METHODPR(ScrollBar, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_focusMode(FocusMode)", AS_METHODPR(ScrollBar, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFullImageRect()", AS_METHODPR(ScrollBar, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ScrollBar, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ScrollBar, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHeight(int)", AS_METHODPR(ScrollBar, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_height(int)", AS_METHODPR(ScrollBar, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(ScrollBar, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(ScrollBar, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHovering(bool)", AS_METHODPR(ScrollBar, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHoverOffset(int, int)", AS_METHODPR(ScrollBar, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetImageBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_imageBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetImageRect(const IntRect&in)", AS_METHODPR(ScrollBar, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_imageRect(const IntRect&in)", AS_METHODPR(ScrollBar, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetIndent(int)", AS_METHODPR(ScrollBar, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_indent(int)", AS_METHODPR(ScrollBar, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetIndentSpacing(int)", AS_METHODPR(ScrollBar, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_indentSpacing(int)", AS_METHODPR(ScrollBar, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInstanceDefault(bool)", AS_METHODPR(ScrollBar, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ScrollBar, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInternal(bool)", AS_METHODPR(ScrollBar, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_internal(bool)", AS_METHODPR(ScrollBar, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(ScrollBar, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(ScrollBar, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(ScrollBar, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(ScrollBar, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutMode(LayoutMode)", AS_METHODPR(ScrollBar, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutMode(LayoutMode)", AS_METHODPR(ScrollBar, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutSpacing(int)", AS_METHODPR(ScrollBar, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutSpacing(int)", AS_METHODPR(ScrollBar, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaterial(Material@+)", AS_METHODPR(ScrollBar, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_material(Material@+)", AS_METHODPR(ScrollBar, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(ScrollBar, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(ScrollBar, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(ScrollBar, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxAnchor(float, float)", AS_METHODPR(ScrollBar, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxHeight(int)", AS_METHODPR(ScrollBar, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxHeight(int)", AS_METHODPR(ScrollBar, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxSize(int, int)", AS_METHODPR(ScrollBar, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxWidth(int)", AS_METHODPR(ScrollBar, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxWidth(int)", AS_METHODPR(ScrollBar, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(ScrollBar, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minAnchor(const Vector2&in)", AS_METHODPR(ScrollBar, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinAnchor(float, float)", AS_METHODPR(ScrollBar, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinHeight(int)", AS_METHODPR(ScrollBar, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minHeight(int)", AS_METHODPR(ScrollBar, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minOffset(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinSize(int, int)", AS_METHODPR(ScrollBar, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinWidth(int)", AS_METHODPR(ScrollBar, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minWidth(int)", AS_METHODPR(ScrollBar, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetName(const String&in)", AS_METHODPR(ScrollBar, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_name(const String&in)", AS_METHODPR(ScrollBar, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ScrollBar, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ScrollBar, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ScrollBar, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetOpacity(float)", AS_METHODPR(ScrollBar, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_opacity(float)", AS_METHODPR(ScrollBar, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void ScrollBar::SetOrientation(Orientation orientation) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetOrientation(Orientation)", AS_METHODPR(ScrollBar, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_orientation(Orientation)", AS_METHODPR(ScrollBar, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(ScrollBar, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPivot(const Vector2&in)", AS_METHODPR(ScrollBar, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_pivot(const Vector2&in)", AS_METHODPR(ScrollBar, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPivot(float, float)", AS_METHODPR(ScrollBar, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPosition(const IntVector2&in)", AS_METHODPR(ScrollBar, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_position(const IntVector2&in)", AS_METHODPR(ScrollBar, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPosition(int, int)", AS_METHODPR(ScrollBar, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPriority(int)", AS_METHODPR(ScrollBar, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_priority(int)", AS_METHODPR(ScrollBar, SetPriority, (int), void), AS_CALL_THISCALL);
    // void ScrollBar::SetRange(float range) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetRange(float)", AS_METHODPR(ScrollBar, SetRange, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_range(float)", AS_METHODPR(ScrollBar, SetRange, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(ScrollBar, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void ScrollBar::SetScrollStep(float step) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetScrollStep(float)", AS_METHODPR(ScrollBar, SetScrollStep, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_scrollStep(float)", AS_METHODPR(ScrollBar, SetScrollStep, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSelected(bool)", AS_METHODPR(ScrollBar, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_selected(bool)", AS_METHODPR(ScrollBar, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSize(const IntVector2&in)", AS_METHODPR(ScrollBar, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_size(const IntVector2&in)", AS_METHODPR(ScrollBar, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSize(int, int)", AS_METHODPR(ScrollBar, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSortChildren(bool)", AS_METHODPR(ScrollBar, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_sortChildren(bool)", AS_METHODPR(ScrollBar, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // void ScrollBar::SetStepFactor(float factor) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetStepFactor(float)", AS_METHODPR(ScrollBar, SetStepFactor, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_stepFactor(float)", AS_METHODPR(ScrollBar, SetStepFactor, (float), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(ScrollBar, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyle(const XMLElement&in)", AS_METHODPR(ScrollBar, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(ScrollBar, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ScrollBar_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTemporary(bool)", AS_METHODPR(ScrollBar, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_temporary(bool)", AS_METHODPR(ScrollBar, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTexture(Texture@+)", AS_METHODPR(ScrollBar, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_texture(Texture@+)", AS_METHODPR(ScrollBar, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(ScrollBar, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTiled(bool)", AS_METHODPR(ScrollBar, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_tiled(bool)", AS_METHODPR(ScrollBar, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTraversalMode(TraversalMode)", AS_METHODPR(ScrollBar, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_traversalMode(TraversalMode)", AS_METHODPR(ScrollBar, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetUseDerivedOpacity(bool)", AS_METHODPR(ScrollBar, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_useDerivedOpacity(bool)", AS_METHODPR(ScrollBar, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void ScrollBar::SetValue(float value) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetValue(float)", AS_METHODPR(ScrollBar, SetValue, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_value(float)", AS_METHODPR(ScrollBar, SetValue, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(ScrollBar, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(ScrollBar, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(ScrollBar, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVisible(bool)", AS_METHODPR(ScrollBar, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_visible(bool)", AS_METHODPR(ScrollBar, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetWidth(int)", AS_METHODPR(ScrollBar, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_width(int)", AS_METHODPR(ScrollBar, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SortChildren()", AS_METHODPR(ScrollBar, SortChildren, (), void), AS_CALL_THISCALL);
    // void ScrollBar::StepBack() | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void StepBack()", AS_METHODPR(ScrollBar, StepBack, (), void), AS_CALL_THISCALL);
    // void ScrollBar::StepForward() | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void StepForward()", AS_METHODPR(ScrollBar, StepForward, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromAllEvents()", AS_METHODPR(ScrollBar, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ScrollBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ScrollBar, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ScrollBar, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ScrollBar, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void Update(float)", AS_METHODPR(ScrollBar, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void UpdateLayout()", AS_METHODPR(ScrollBar, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollBar", "int WeakRefs() const", AS_METHODPR(ScrollBar, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_weakRefs() const", AS_METHODPR(ScrollBar, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ScrollBar, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ScrollBar, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ScrollBar, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ScrollBar, "ScrollBar")
#endif
#ifdef REGISTER_MANUAL_PART_ScrollBar
    REGISTER_MANUAL_PART_ScrollBar(ScrollBar, "ScrollBar")
#endif
    RegisterSubclass<BorderImage, ScrollBar>(engine, "BorderImage", "ScrollBar");
    RegisterSubclass<UIElement, ScrollBar>(engine, "UIElement", "ScrollBar");
    RegisterSubclass<Animatable, ScrollBar>(engine, "Animatable", "ScrollBar");
    RegisterSubclass<Serializable, ScrollBar>(engine, "Serializable", "ScrollBar");
    RegisterSubclass<Object, ScrollBar>(engine, "Object", "ScrollBar");
    RegisterSubclass<RefCounted, ScrollBar>(engine, "RefCounted", "ScrollBar");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddChild(UIElement@+)", AS_METHODPR(ScrollView, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ScrollView, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTag(const String&in)", AS_METHODPR(ScrollView, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(ScrollView, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ScrollView_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AdjustScissor(IntRect&)", AS_METHODPR(ScrollView, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void AllocateNetworkState()", AS_METHODPR(ScrollView, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void ScrollView::ApplyAttributes() override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void ApplyAttributes()", AS_METHODPR(ScrollView, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void BringToFront()", AS_METHODPR(ScrollView, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(ScrollView, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void DisableLayoutUpdate()", AS_METHODPR(ScrollView, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(ScrollView, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void EnableLayoutUpdate()", AS_METHODPR(ScrollView, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(ScrollView, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint FindChild(UIElement@+) const", AS_METHODPR(ScrollView, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool GetAnimationEnabled() const", AS_METHODPR(ScrollView, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_animationEnabled() const", AS_METHODPR(ScrollView, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetAppliedStyle() const", AS_METHODPR(ScrollView, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_style() const", AS_METHODPR(ScrollView, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttribute(uint) const", AS_METHODPR(ScrollView, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "Variant get_attributes(uint) const", AS_METHODPR(ScrollView, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttribute(const String&in) const", AS_METHODPR(ScrollView, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ScrollView, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ScrollView, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ScrollView, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ScrollView, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ScrollView, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ScrollView, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ScrollView, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool ScrollView::GetAutoDisableChildren() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetAutoDisableChildren() const", AS_METHODPR(ScrollView, GetAutoDisableChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_autoDisableChildren() const", AS_METHODPR(ScrollView, GetAutoDisableChildren, () const, bool), AS_CALL_THISCALL);
    // float ScrollView::GetAutoDisableThreshold() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetAutoDisableThreshold() const", AS_METHODPR(ScrollView, GetAutoDisableThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_autoDisableThreshold() const", AS_METHODPR(ScrollView, GetAutoDisableThreshold, () const, float), AS_CALL_THISCALL);
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBlockEvents() const", AS_METHODPR(ScrollView, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBringToBack() const", AS_METHODPR(ScrollView, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_bringToBack() const", AS_METHODPR(ScrollView, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBringToFront() const", AS_METHODPR(ScrollView, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_bringToFront() const", AS_METHODPR(ScrollView, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetCategory() const", AS_METHODPR(ScrollView, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_category() const", AS_METHODPR(ScrollView, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(uint) const", AS_METHODPR(ScrollView, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_children(uint) const", AS_METHODPR(ScrollView, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(ScrollView, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(ScrollView, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetChildOffset() const", AS_METHODPR(ScrollView, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_childOffset() const", AS_METHODPR(ScrollView, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(ScrollView_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(ScrollView_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(ScrollView_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntRect& GetClipBorder() const", AS_METHODPR(ScrollView, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntRect& get_clipBorder() const", AS_METHODPR(ScrollView, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetClipChildren() const", AS_METHODPR(ScrollView, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_clipChildren() const", AS_METHODPR(ScrollView, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetColor(Corner) const", AS_METHODPR(ScrollView, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Color& get_colors(Corner) const", AS_METHODPR(ScrollView, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetColorAttr() const", AS_METHODPR(ScrollView, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntRect GetCombinedScreenRect()", AS_METHODPR(ScrollView, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "IntRect get_combinedScreenRect()", AS_METHODPR(ScrollView, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // UIElement* ScrollView::GetContentElement() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetContentElement() const", AS_METHODPR(ScrollView, GetContentElement, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_contentElement() const", AS_METHODPR(ScrollView, GetContentElement, () const, UIElement*), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(ScrollView, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetDerivedColor() const", AS_METHODPR(ScrollView, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "float GetDerivedOpacity() const", AS_METHODPR(ScrollView, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_derivedOpacity() const", AS_METHODPR(ScrollView, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(ScrollView, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(ScrollView, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint GetDragButtonCount() const", AS_METHODPR(ScrollView, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_dragButtonCount() const", AS_METHODPR(ScrollView, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(ScrollView, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(ScrollView, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(ScrollView, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetElementEventSender() const", AS_METHODPR(ScrollView, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetEnableAnchor() const", AS_METHODPR(ScrollView, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enableAnchor() const", AS_METHODPR(ScrollView, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "VariantMap& GetEventDataMap() const", AS_METHODPR(ScrollView, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "Object@+ GetEventSender() const", AS_METHODPR(ScrollView, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "FocusMode GetFocusMode() const", AS_METHODPR(ScrollView, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "FocusMode get_focusMode() const", AS_METHODPR(ScrollView, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ScrollView, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ScrollView, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ScrollView, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& get_globalVars() const", AS_METHODPR(ScrollView, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetHeight() const", AS_METHODPR(ScrollView, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_height() const", AS_METHODPR(ScrollView, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(ScrollView, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(ScrollView, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // ScrollBar* ScrollView::GetHorizontalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ GetHorizontalScrollBar() const", AS_METHODPR(ScrollView, GetHorizontalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_horizontalScrollBar() const", AS_METHODPR(ScrollView, GetHorizontalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    // bool ScrollView::GetHorizontalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetHorizontalScrollBarVisible() const", AS_METHODPR(ScrollView, GetHorizontalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_horizontalScrollBarVisible() const", AS_METHODPR(ScrollView, GetHorizontalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndent() const", AS_METHODPR(ScrollView, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indent() const", AS_METHODPR(ScrollView, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndentSpacing() const", AS_METHODPR(ScrollView, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indentSpacing() const", AS_METHODPR(ScrollView, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndentWidth() const", AS_METHODPR(ScrollView, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indentWidth() const", AS_METHODPR(ScrollView, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ScrollView, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntRect& GetLayoutBorder() const", AS_METHODPR(ScrollView, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntRect& get_layoutBorder() const", AS_METHODPR(ScrollView, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetLayoutElementMaxSize() const", AS_METHODPR(ScrollView, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(ScrollView, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(ScrollView, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "LayoutMode GetLayoutMode() const", AS_METHODPR(ScrollView, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "LayoutMode get_layoutMode() const", AS_METHODPR(ScrollView, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetLayoutSpacing() const", AS_METHODPR(ScrollView, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_layoutSpacing() const", AS_METHODPR(ScrollView, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetMaxAnchor() const", AS_METHODPR(ScrollView, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_maxAnchor() const", AS_METHODPR(ScrollView, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMaxHeight() const", AS_METHODPR(ScrollView, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_maxHeight() const", AS_METHODPR(ScrollView, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMaxOffset() const", AS_METHODPR(ScrollView, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_maxOffset() const", AS_METHODPR(ScrollView, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMaxSize() const", AS_METHODPR(ScrollView, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_maxSize() const", AS_METHODPR(ScrollView, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMaxWidth() const", AS_METHODPR(ScrollView, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_maxWidth() const", AS_METHODPR(ScrollView, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetMinAnchor() const", AS_METHODPR(ScrollView, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_minAnchor() const", AS_METHODPR(ScrollView, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMinHeight() const", AS_METHODPR(ScrollView, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_minHeight() const", AS_METHODPR(ScrollView, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMinOffset() const", AS_METHODPR(ScrollView, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_minOffset() const", AS_METHODPR(ScrollView, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMinSize() const", AS_METHODPR(ScrollView, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_minSize() const", AS_METHODPR(ScrollView, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMinWidth() const", AS_METHODPR(ScrollView, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_minWidth() const", AS_METHODPR(ScrollView, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetName() const", AS_METHODPR(ScrollView, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_name() const", AS_METHODPR(ScrollView, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumAttributes() const", AS_METHODPR(ScrollView, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_numAttributes() const", AS_METHODPR(ScrollView, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumChildren(bool = false) const", AS_METHODPR(ScrollView, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_numChildren(bool = false) const", AS_METHODPR(ScrollView, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumNetworkAttributes() const", AS_METHODPR(ScrollView, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ScrollView, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ScrollView, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ScrollView, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "float GetOpacity() const", AS_METHODPR(ScrollView, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_opacity() const", AS_METHODPR(ScrollView, GetOpacity, () const, float), AS_CALL_THISCALL);
    // float ScrollView::GetPageStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetPageStep() const", AS_METHODPR(ScrollView, GetPageStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_pageStep() const", AS_METHODPR(ScrollView, GetPageStep, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetParent() const", AS_METHODPR(ScrollView, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_parent() const", AS_METHODPR(ScrollView, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetPivot() const", AS_METHODPR(ScrollView, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_pivot() const", AS_METHODPR(ScrollView, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetPosition() const", AS_METHODPR(ScrollView, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_position() const", AS_METHODPR(ScrollView, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetPriority() const", AS_METHODPR(ScrollView, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_priority() const", AS_METHODPR(ScrollView, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetRoot() const", AS_METHODPR(ScrollView, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_root() const", AS_METHODPR(ScrollView, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetScreenPosition() const", AS_METHODPR(ScrollView, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_screenPosition() const", AS_METHODPR(ScrollView, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool ScrollView::GetScrollBarsAutoVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetScrollBarsAutoVisible() const", AS_METHODPR(ScrollView, GetScrollBarsAutoVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_scrollBarsAutoVisible() const", AS_METHODPR(ScrollView, GetScrollBarsAutoVisible, () const, bool), AS_CALL_THISCALL);
    // float ScrollView::GetScrollDeceleration() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollDeceleration() const", AS_METHODPR(ScrollView, GetScrollDeceleration, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollDeceleration() const", AS_METHODPR(ScrollView, GetScrollDeceleration, () const, float), AS_CALL_THISCALL);
    // BorderImage* ScrollView::GetScrollPanel() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "BorderImage@+ GetScrollPanel() const", AS_METHODPR(ScrollView, GetScrollPanel, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "BorderImage@+ get_scrollPanel() const", AS_METHODPR(ScrollView, GetScrollPanel, () const, BorderImage*), AS_CALL_THISCALL);
    // float ScrollView::GetScrollSnapEpsilon() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollSnapEpsilon() const", AS_METHODPR(ScrollView, GetScrollSnapEpsilon, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollSnapEpsilon() const", AS_METHODPR(ScrollView, GetScrollSnapEpsilon, () const, float), AS_CALL_THISCALL);
    // float ScrollView::GetScrollStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollStep() const", AS_METHODPR(ScrollView, GetScrollStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollStep() const", AS_METHODPR(ScrollView, GetScrollStep, () const, float), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetSize() const", AS_METHODPR(ScrollView, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_size() const", AS_METHODPR(ScrollView, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetSortChildren() const", AS_METHODPR(ScrollView, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_sortChildren() const", AS_METHODPR(ScrollView, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ScrollView, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(ScrollView_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ScrollView", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(ScrollView_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "TraversalMode GetTraversalMode() const", AS_METHODPR(ScrollView, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "TraversalMode get_traversalMode() const", AS_METHODPR(ScrollView, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "StringHash GetType() const", AS_METHODPR(ScrollView, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "StringHash get_type() const", AS_METHODPR(ScrollView, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetTypeName() const", AS_METHODPR(ScrollView, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_typeName() const", AS_METHODPR(ScrollView, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetUseDerivedOpacity() const", AS_METHODPR(ScrollView, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_useDerivedOpacity() const", AS_METHODPR(ScrollView, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(ScrollView, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& GetVars() const", AS_METHODPR(ScrollView, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(ScrollView, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(ScrollView, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // ScrollBar* ScrollView::GetVerticalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ GetVerticalScrollBar() const", AS_METHODPR(ScrollView, GetVerticalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_verticalScrollBar() const", AS_METHODPR(ScrollView, GetVerticalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    // bool ScrollView::GetVerticalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetVerticalScrollBarVisible() const", AS_METHODPR(ScrollView, GetVerticalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_verticalScrollBarVisible() const", AS_METHODPR(ScrollView, GetVerticalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& ScrollView::GetViewPosition() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetViewPosition() const", AS_METHODPR(ScrollView, GetViewPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_viewPosition() const", AS_METHODPR(ScrollView, GetViewPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetWidth() const", AS_METHODPR(ScrollView, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_width() const", AS_METHODPR(ScrollView, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasColorGradient() const", AS_METHODPR(ScrollView, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_colorGradient() const", AS_METHODPR(ScrollView, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasEventHandlers() const", AS_METHODPR(ScrollView, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasFocus() const", AS_METHODPR(ScrollView, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_focus() const", AS_METHODPR(ScrollView, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ScrollView, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ScrollView, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasTag(const String&in) const", AS_METHODPR(ScrollView, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void InsertChild(uint, UIElement@+)", AS_METHODPR(ScrollView, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsChildOf(UIElement@+) const", AS_METHODPR(ScrollView, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEditable() const", AS_METHODPR(ScrollView, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_editable() const", AS_METHODPR(ScrollView, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsElementEventSender() const", AS_METHODPR(ScrollView, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_elementEventSender() const", AS_METHODPR(ScrollView, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEnabled() const", AS_METHODPR(ScrollView, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enabled() const", AS_METHODPR(ScrollView, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEnabledSelf() const", AS_METHODPR(ScrollView, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enabledSelf() const", AS_METHODPR(ScrollView, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedHeight() const", AS_METHODPR(ScrollView, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedHeight() const", AS_METHODPR(ScrollView, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedSize() const", AS_METHODPR(ScrollView, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedSize() const", AS_METHODPR(ScrollView, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedWidth() const", AS_METHODPR(ScrollView, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedWidth() const", AS_METHODPR(ScrollView, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsHovering() const", AS_METHODPR(ScrollView, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_hovering() const", AS_METHODPR(ScrollView, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInside(IntVector2, bool)", AS_METHODPR(ScrollView, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(ScrollView, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ScrollView, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInternal() const", AS_METHODPR(ScrollView, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_internal() const", AS_METHODPR(ScrollView, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsSelected() const", AS_METHODPR(ScrollView, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_selected() const", AS_METHODPR(ScrollView, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool IsTemporary() const", AS_METHODPR(ScrollView, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_temporary() const", AS_METHODPR(ScrollView, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsVisible() const", AS_METHODPR(ScrollView, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_visible() const", AS_METHODPR(ScrollView, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsVisibleEffective() const", AS_METHODPR(ScrollView, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_visibleEffective() const", AS_METHODPR(ScrollView, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // bool ScrollView::IsWheelHandler() const override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool IsWheelHandler() const", AS_METHODPR(ScrollView, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(ScrollView, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool Load(Deserializer&)", AS_METHODPR(ScrollView, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ScrollView, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ScrollView, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ScrollView, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ScrollView, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(Deserializer&)", AS_METHODPR(ScrollView, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void MarkNetworkUpdate()", AS_METHODPR(ScrollView, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollView, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(ScrollView, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollView, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollView, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ScrollView, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(ScrollView, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(ScrollView, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ScrollView, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollView, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ScrollView, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ScrollView, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ScrollView, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnIndentSet()", AS_METHODPR(ScrollView, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void ScrollView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ScrollView, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(ScrollView, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ScrollView::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(ScrollView, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ScrollView, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnSetEditable()", AS_METHODPR(ScrollView, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnTextInput(const String&in)", AS_METHODPR(ScrollView, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // void ScrollView::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ScrollView, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ScrollView, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ScrollView, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollView", "int Refs() const", AS_METHODPR(ScrollView, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_refs() const", AS_METHODPR(ScrollView, Refs, () const, int), AS_CALL_THISCALL);
    // static void ScrollView::RegisterObject(Context* context) | File: ../UI/ScrollView.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ScrollView, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void Remove()", AS_METHODPR(ScrollView, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAllChildren()", AS_METHODPR(ScrollView, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAllTags()", AS_METHODPR(ScrollView, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ScrollView, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(ScrollView, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveChildAtIndex(uint)", AS_METHODPR(ScrollView, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveInstanceDefault()", AS_METHODPR(ScrollView, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveObjectAnimation()", AS_METHODPR(ScrollView, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool RemoveTag(const String&in)", AS_METHODPR(ScrollView, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void ResetDeepEnabled()", AS_METHODPR(ScrollView, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void ResetToDefault()", AS_METHODPR(ScrollView, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool Save(Serializer&) const", AS_METHODPR(ScrollView, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveDefaultAttributes() const", AS_METHODPR(ScrollView, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ScrollView, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveXML(XMLElement&) const", AS_METHODPR(ScrollView, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(ScrollView, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(ScrollView, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // explicit ScrollView::ScrollView(Context* context) | File: ../UI/ScrollView.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_FACTORY, "ScrollView@+ f()", AS_FUNCTION(ScrollView_ScrollView_Context), AS_CALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SendEvent(StringHash)", AS_METHODPR(ScrollView, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ScrollView, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(ScrollView, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAnimationEnabled(bool)", AS_METHODPR(ScrollView, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_animationEnabled(bool)", AS_METHODPR(ScrollView, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAnimationTime(float)", AS_METHODPR(ScrollView, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ScrollView, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ScrollView, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ScrollView, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ScrollView, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ScrollView, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ScrollView, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ScrollView, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void ScrollView::SetAutoDisableChildren(bool disable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetAutoDisableChildren(bool)", AS_METHODPR(ScrollView, SetAutoDisableChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableChildren(bool)", AS_METHODPR(ScrollView, SetAutoDisableChildren, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetAutoDisableThreshold(float amount) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetAutoDisableThreshold(float)", AS_METHODPR(ScrollView, SetAutoDisableThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableThreshold(float)", AS_METHODPR(ScrollView, SetAutoDisableThreshold, (float), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SetBlockEvents(bool)", AS_METHODPR(ScrollView, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetBringToBack(bool)", AS_METHODPR(ScrollView, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_bringToBack(bool)", AS_METHODPR(ScrollView, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetBringToFront(bool)", AS_METHODPR(ScrollView, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_bringToFront(bool)", AS_METHODPR(ScrollView, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(ScrollView, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetClipBorder(const IntRect&in)", AS_METHODPR(ScrollView, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_clipBorder(const IntRect&in)", AS_METHODPR(ScrollView, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetClipChildren(bool)", AS_METHODPR(ScrollView, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_clipChildren(bool)", AS_METHODPR(ScrollView, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetColor(const Color&in)", AS_METHODPR(ScrollView, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_color(const Color&in)", AS_METHODPR(ScrollView, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetColor(Corner, const Color&in)", AS_METHODPR(ScrollView, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_colors(Corner, const Color&in)", AS_METHODPR(ScrollView, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void ScrollView::SetContentElement(UIElement* element) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetContentElement(UIElement@+)", AS_METHODPR(ScrollView, SetContentElement, (UIElement*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_contentElement(UIElement@+)", AS_METHODPR(ScrollView, SetContentElement, (UIElement*), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDeepEnabled(bool)", AS_METHODPR(ScrollView, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(ScrollView, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(ScrollView, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(ScrollView, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(ScrollView, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEditable(bool)", AS_METHODPR(ScrollView, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_editable(bool)", AS_METHODPR(ScrollView, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetElementEventSender(bool)", AS_METHODPR(ScrollView, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_elementEventSender(bool)", AS_METHODPR(ScrollView, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnableAnchor(bool)", AS_METHODPR(ScrollView, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_enableAnchor(bool)", AS_METHODPR(ScrollView, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnabled(bool)", AS_METHODPR(ScrollView, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_enabled(bool)", AS_METHODPR(ScrollView, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnabledRecursive(bool)", AS_METHODPR(ScrollView, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedHeight(int)", AS_METHODPR(ScrollView, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedSize(int, int)", AS_METHODPR(ScrollView, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedWidth(int)", AS_METHODPR(ScrollView, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFocus(bool)", AS_METHODPR(ScrollView, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_focus(bool)", AS_METHODPR(ScrollView, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFocusMode(FocusMode)", AS_METHODPR(ScrollView, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_focusMode(FocusMode)", AS_METHODPR(ScrollView, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ScrollView, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ScrollView, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHeight(int)", AS_METHODPR(ScrollView, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_height(int)", AS_METHODPR(ScrollView, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(ScrollView, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(ScrollView, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void ScrollView::SetHorizontalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetHorizontalScrollBarVisible(bool)", AS_METHODPR(ScrollView, SetHorizontalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_horizontalScrollBarVisible(bool)", AS_METHODPR(ScrollView, SetHorizontalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHovering(bool)", AS_METHODPR(ScrollView, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetIndent(int)", AS_METHODPR(ScrollView, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_indent(int)", AS_METHODPR(ScrollView, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetIndentSpacing(int)", AS_METHODPR(ScrollView, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_indentSpacing(int)", AS_METHODPR(ScrollView, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetInstanceDefault(bool)", AS_METHODPR(ScrollView, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ScrollView, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetInternal(bool)", AS_METHODPR(ScrollView, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_internal(bool)", AS_METHODPR(ScrollView, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(ScrollView, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(ScrollView, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(ScrollView, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(ScrollView, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(ScrollView, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutMode(LayoutMode)", AS_METHODPR(ScrollView, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutMode(LayoutMode)", AS_METHODPR(ScrollView, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutSpacing(int)", AS_METHODPR(ScrollView, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutSpacing(int)", AS_METHODPR(ScrollView, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(ScrollView, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(ScrollView, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxAnchor(float, float)", AS_METHODPR(ScrollView, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxHeight(int)", AS_METHODPR(ScrollView, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxHeight(int)", AS_METHODPR(ScrollView, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(ScrollView, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(ScrollView, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxSize(int, int)", AS_METHODPR(ScrollView, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxWidth(int)", AS_METHODPR(ScrollView, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxWidth(int)", AS_METHODPR(ScrollView, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(ScrollView, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minAnchor(const Vector2&in)", AS_METHODPR(ScrollView, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinAnchor(float, float)", AS_METHODPR(ScrollView, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinHeight(int)", AS_METHODPR(ScrollView, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minHeight(int)", AS_METHODPR(ScrollView, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(ScrollView, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minOffset(const IntVector2&in)", AS_METHODPR(ScrollView, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinSize(int, int)", AS_METHODPR(ScrollView, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinWidth(int)", AS_METHODPR(ScrollView, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minWidth(int)", AS_METHODPR(ScrollView, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetName(const String&in)", AS_METHODPR(ScrollView, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_name(const String&in)", AS_METHODPR(ScrollView, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ScrollView, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ScrollView, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ScrollView, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetOpacity(float)", AS_METHODPR(ScrollView, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_opacity(float)", AS_METHODPR(ScrollView, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetPageStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetPageStep(float)", AS_METHODPR(ScrollView, SetPageStep, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_pageStep(float)", AS_METHODPR(ScrollView, SetPageStep, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(ScrollView, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPivot(const Vector2&in)", AS_METHODPR(ScrollView, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_pivot(const Vector2&in)", AS_METHODPR(ScrollView, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPivot(float, float)", AS_METHODPR(ScrollView, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPosition(const IntVector2&in)", AS_METHODPR(ScrollView, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_position(const IntVector2&in)", AS_METHODPR(ScrollView, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPosition(int, int)", AS_METHODPR(ScrollView, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPriority(int)", AS_METHODPR(ScrollView, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_priority(int)", AS_METHODPR(ScrollView, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(ScrollView, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollBarsAutoVisible(bool enable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollBarsAutoVisible(bool)", AS_METHODPR(ScrollView, SetScrollBarsAutoVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollBarsAutoVisible(bool)", AS_METHODPR(ScrollView, SetScrollBarsAutoVisible, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollBarsVisible(bool, bool)", AS_METHODPR(ScrollView, SetScrollBarsVisible, (bool, bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollDeceleration(float deceleration) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollDeceleration(float)", AS_METHODPR(ScrollView, SetScrollDeceleration, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollDeceleration(float)", AS_METHODPR(ScrollView, SetScrollDeceleration, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollSnapEpsilon(float snap) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollSnapEpsilon(float)", AS_METHODPR(ScrollView, SetScrollSnapEpsilon, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollSnapEpsilon(float)", AS_METHODPR(ScrollView, SetScrollSnapEpsilon, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollStep(float)", AS_METHODPR(ScrollView, SetScrollStep, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollStep(float)", AS_METHODPR(ScrollView, SetScrollStep, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSelected(bool)", AS_METHODPR(ScrollView, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_selected(bool)", AS_METHODPR(ScrollView, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSize(const IntVector2&in)", AS_METHODPR(ScrollView, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_size(const IntVector2&in)", AS_METHODPR(ScrollView, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSize(int, int)", AS_METHODPR(ScrollView, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSortChildren(bool)", AS_METHODPR(ScrollView, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_sortChildren(bool)", AS_METHODPR(ScrollView, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(ScrollView, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyle(const XMLElement&in)", AS_METHODPR(ScrollView, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(ScrollView, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ScrollView_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetTemporary(bool)", AS_METHODPR(ScrollView, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_temporary(bool)", AS_METHODPR(ScrollView, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetTraversalMode(TraversalMode)", AS_METHODPR(ScrollView, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_traversalMode(TraversalMode)", AS_METHODPR(ScrollView, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetUseDerivedOpacity(bool)", AS_METHODPR(ScrollView, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_useDerivedOpacity(bool)", AS_METHODPR(ScrollView, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(ScrollView, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(ScrollView, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(ScrollView, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void ScrollView::SetVerticalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetVerticalScrollBarVisible(bool)", AS_METHODPR(ScrollView, SetVerticalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_verticalScrollBarVisible(bool)", AS_METHODPR(ScrollView, SetVerticalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPosition(const IntVector2& position) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPosition(const IntVector2&in)", AS_METHODPR(ScrollView, SetViewPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_viewPosition(const IntVector2&in)", AS_METHODPR(ScrollView, SetViewPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPosition(int x, int y) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPosition(int, int)", AS_METHODPR(ScrollView, SetViewPosition, (int, int), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPositionAttr(const IntVector2& value) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPositionAttr(const IntVector2&in)", AS_METHODPR(ScrollView, SetViewPositionAttr, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVisible(bool)", AS_METHODPR(ScrollView, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_visible(bool)", AS_METHODPR(ScrollView, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetWidth(int)", AS_METHODPR(ScrollView, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_width(int)", AS_METHODPR(ScrollView, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SortChildren()", AS_METHODPR(ScrollView, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromAllEvents()", AS_METHODPR(ScrollView, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ScrollView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ScrollView, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ScrollView, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ScrollView, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void ScrollView::Update(float timeStep) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void Update(float)", AS_METHODPR(ScrollView, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void UpdateLayout()", AS_METHODPR(ScrollView, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollView", "int WeakRefs() const", AS_METHODPR(ScrollView, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_weakRefs() const", AS_METHODPR(ScrollView, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ScrollView, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ScrollView, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ScrollView, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(ScrollView, "ScrollView")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ScrollView, "ScrollView")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ScrollView, "ScrollView")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ScrollView, "ScrollView")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ScrollView, "ScrollView")
#endif
#ifdef REGISTER_MANUAL_PART_ScrollView
    REGISTER_MANUAL_PART_ScrollView(ScrollView, "ScrollView")
#endif
    RegisterSubclass<UIElement, ScrollView>(engine, "UIElement", "ScrollView");
    RegisterSubclass<Animatable, ScrollView>(engine, "Animatable", "ScrollView");
    RegisterSubclass<Serializable, ScrollView>(engine, "Serializable", "ScrollView");
    RegisterSubclass<Object, ScrollView>(engine, "Object", "ScrollView");
    RegisterSubclass<RefCounted, ScrollView>(engine, "RefCounted", "ScrollView");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Serializable, AddRef, (), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void AllocateNetworkState()", AS_METHODPR(Serializable, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void ApplyAttributes()", AS_METHODPR(Serializable, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttribute(uint) const", AS_METHODPR(Serializable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "Variant get_attributes(uint) const", AS_METHODPR(Serializable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttribute(const String&in) const", AS_METHODPR(Serializable, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Serializable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Serializable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Serializable, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool GetBlockEvents() const", AS_METHODPR(Serializable, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const String& GetCategory() const", AS_METHODPR(Serializable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const String& get_category() const", AS_METHODPR(Serializable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "VariantMap& GetEventDataMap() const", AS_METHODPR(Serializable, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "Object@+ GetEventSender() const", AS_METHODPR(Serializable, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Serializable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Serializable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Serializable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const VariantMap& get_globalVars() const", AS_METHODPR(Serializable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Serializable, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "uint GetNumAttributes() const", AS_METHODPR(Serializable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "uint get_numAttributes() const", AS_METHODPR(Serializable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "uint GetNumNetworkAttributes() const", AS_METHODPR(Serializable, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Serializable, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "StringHash GetType() const", AS_METHODPR(Serializable, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "StringHash get_type() const", AS_METHODPR(Serializable, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const String& GetTypeName() const", AS_METHODPR(Serializable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const String& get_typeName() const", AS_METHODPR(Serializable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasEventHandlers() const", AS_METHODPR(Serializable, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Serializable, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Serializable, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Serializable, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool IsTemporary() const", AS_METHODPR(Serializable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "bool get_temporary() const", AS_METHODPR(Serializable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool Load(Deserializer&)", AS_METHODPR(Serializable, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::LoadJSON(const JSONValue& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Serializable, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::LoadXML(const XMLElement& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Serializable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void MarkNetworkUpdate()", AS_METHODPR(Serializable, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Serializable, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Serializable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Serializable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Serializable, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Serializable, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Serializable", "int Refs() const", AS_METHODPR(Serializable, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "int get_refs() const", AS_METHODPR(Serializable, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Serializable, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void RemoveInstanceDefault()", AS_METHODPR(Serializable, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void ResetToDefault()", AS_METHODPR(Serializable, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool Save(Serializer&) const", AS_METHODPR(Serializable, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveDefaultAttributes() const", AS_METHODPR(Serializable, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveJSON(JSONValue& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Serializable, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveXML(XMLElement& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveXML(XMLElement&) const", AS_METHODPR(Serializable, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SendEvent(StringHash)", AS_METHODPR(Serializable, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Serializable, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // explicit Serializable::Serializable(Context* context) | File: ../Scene/Serializable.h
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_FACTORY, "Serializable@+ f()", AS_FUNCTION(Serializable_Serializable_Context), AS_CALL_CDECL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Serializable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Serializable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Serializable, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SetBlockEvents(bool)", AS_METHODPR(Serializable, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Serializable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Serializable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetInstanceDefault(bool)", AS_METHODPR(Serializable, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Serializable, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetTemporary(bool)", AS_METHODPR(Serializable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "void set_temporary(bool)", AS_METHODPR(Serializable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromAllEvents()", AS_METHODPR(Serializable, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Serializable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Serializable, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Serializable, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Serializable, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Serializable", "int WeakRefs() const", AS_METHODPR(Serializable, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "int get_weakRefs() const", AS_METHODPR(Serializable, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Serializable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Serializable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Serializable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Serializable, "Serializable")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Serializable, "Serializable")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Serializable, "Serializable")
#endif
    RegisterSubclass<Object, Serializable>(engine, "Object", "Serializable");
    RegisterSubclass<RefCounted, Serializable>(engine, "RefCounted", "Serializable");

    // virtual unsigned Serializer::Write(const void* data, unsigned size)=0 | File: ../IO/Serializer.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteBool(bool)", AS_METHODPR(Serializer, WriteBool, (bool), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteBoundingBox(const BoundingBox&in)", AS_METHODPR(Serializer, WriteBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteByte(int8)", AS_METHODPR(Serializer, WriteByte, (signed char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteColor(const Color&in)", AS_METHODPR(Serializer, WriteColor, (const Color&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteDouble(double)", AS_METHODPR(Serializer, WriteDouble, (double), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteFileID(const String&in)", AS_METHODPR(Serializer, WriteFileID, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteFloat(float)", AS_METHODPR(Serializer, WriteFloat, (float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteInt(int)", AS_METHODPR(Serializer, WriteInt, (int), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteInt64(int64)", AS_METHODPR(Serializer, WriteInt64, (long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntRect(const IntRect&in)", AS_METHODPR(Serializer, WriteIntRect, (const IntRect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntVector2(const IntVector2&in)", AS_METHODPR(Serializer, WriteIntVector2, (const IntVector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntVector3(const IntVector3&in)", AS_METHODPR(Serializer, WriteIntVector3, (const IntVector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteLine(const String&in)", AS_METHODPR(Serializer, WriteLine, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix3(const Matrix3&in)", AS_METHODPR(Serializer, WriteMatrix3, (const Matrix3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix3x4(const Matrix3x4&in)", AS_METHODPR(Serializer, WriteMatrix3x4, (const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix4(const Matrix4&in)", AS_METHODPR(Serializer, WriteMatrix4, (const Matrix4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteNetID(uint)", AS_METHODPR(Serializer, WriteNetID, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WritePackedQuaternion(const Quaternion&in)", AS_METHODPR(Serializer, WritePackedQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WritePackedVector3(const Vector3&in, float)", AS_METHODPR(Serializer, WritePackedVector3, (const Vector3&, float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteQuaternion(const Quaternion&in)", AS_METHODPR(Serializer, WriteQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteRect(const Rect&in)", AS_METHODPR(Serializer, WriteRect, (const Rect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteResourceRef(const ResourceRef&in)", AS_METHODPR(Serializer, WriteResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteResourceRefList(const ResourceRefList&in)", AS_METHODPR(Serializer, WriteResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteShort(int16)", AS_METHODPR(Serializer, WriteShort, (short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteString(const String&in)", AS_METHODPR(Serializer, WriteString, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteStringHash(const StringHash&in)", AS_METHODPR(Serializer, WriteStringHash, (const StringHash&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(Serializer_WriteStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUByte(uint8)", AS_METHODPR(Serializer, WriteUByte, (unsigned char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUInt(uint)", AS_METHODPR(Serializer, WriteUInt, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUInt64(uint64)", AS_METHODPR(Serializer, WriteUInt64, (unsigned long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUShort(uint16)", AS_METHODPR(Serializer, WriteUShort, (unsigned short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariant(const Variant&in)", AS_METHODPR(Serializer, WriteVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariantData(const Variant&in)", AS_METHODPR(Serializer, WriteVariantData, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariantMap(const VariantMap&in)", AS_METHODPR(Serializer, WriteVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector2(const Vector2&in)", AS_METHODPR(Serializer, WriteVector2, (const Vector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector3(const Vector3&in)", AS_METHODPR(Serializer, WriteVector3, (const Vector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector4(const Vector4&in)", AS_METHODPR(Serializer, WriteVector4, (const Vector4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVLE(uint)", AS_METHODPR(Serializer, WriteVLE, (unsigned), bool), AS_CALL_THISCALL);
    // Serializer& Serializer::operator=(const Serializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Serializer>(engine, "Serializer");
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(Serializer, "Serializer")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Shader, AddRef, (), void), AS_CALL_THISCALL);
    // bool Shader::BeginLoad(Deserializer& source) override | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "bool BeginLoad(Deserializer&)", AS_METHODPR(Shader, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Shader::EndLoad() override | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "bool EndLoad()", AS_METHODPR(Shader, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Shader, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool GetBlockEvents() const", AS_METHODPR(Shader, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const String& GetCategory() const", AS_METHODPR(Shader, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_category() const", AS_METHODPR(Shader, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "VariantMap& GetEventDataMap() const", AS_METHODPR(Shader, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "Object@+ GetEventSender() const", AS_METHODPR(Shader, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Shader, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Shader, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Shader, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const VariantMap& get_globalVars() const", AS_METHODPR(Shader, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "uint GetMemoryUse() const", AS_METHODPR(Shader, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "uint get_memoryUse() const", AS_METHODPR(Shader, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "const String& GetName() const", AS_METHODPR(Shader, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_name() const", AS_METHODPR(Shader, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "StringHash GetNameHash() const", AS_METHODPR(Shader, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // const String& Shader::GetSourceCode(ShaderType type) const | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "const String& GetSourceCode(ShaderType) const", AS_METHODPR(Shader, GetSourceCode, (ShaderType) const, const String&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Shader, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Shader::GetTimeStamp() const | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "uint GetTimeStamp() const", AS_METHODPR(Shader, GetTimeStamp, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "StringHash GetType() const", AS_METHODPR(Shader, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "StringHash get_type() const", AS_METHODPR(Shader, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const String& GetTypeName() const", AS_METHODPR(Shader, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_typeName() const", AS_METHODPR(Shader, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "uint GetUseTimer()", AS_METHODPR(Shader, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "uint get_useTimer()", AS_METHODPR(Shader, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // ShaderVariation* Shader::GetVariation(ShaderType type, const String& defines) | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "ShaderVariation@+ GetVariation(ShaderType, const String&in)", AS_METHODPR(Shader, GetVariation, (ShaderType, const String&), ShaderVariation*), AS_CALL_THISCALL);
    // ShaderVariation* Shader::GetVariation(ShaderType type, const char* defines) | File: ../Graphics/Shader.h
    // Error: type "const char*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasEventHandlers() const", AS_METHODPR(Shader, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Shader, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Shader, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Shader, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool Load(Deserializer&)", AS_METHODPR(Shader, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool LoadFile(const String&in)", AS_METHODPR(Shader, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "bool Load(const String&in)", AS_METHODPR(Shader, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Shader, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Shader", "int Refs() const", AS_METHODPR(Shader, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "int get_refs() const", AS_METHODPR(Shader, Refs, () const, int), AS_CALL_THISCALL);
    // static void Shader::RegisterObject(Context* context) | File: ../Graphics/Shader.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Shader, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void ResetUseTimer()", AS_METHODPR(Shader, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool Save(Serializer&) const", AS_METHODPR(Shader, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool SaveFile(const String&in) const", AS_METHODPR(Shader, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "bool Save(const String&in) const", AS_METHODPR(Shader, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SendEvent(StringHash)", AS_METHODPR(Shader, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Shader, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Shader, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SetBlockEvents(bool)", AS_METHODPR(Shader, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Shader, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Shader, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetMemoryUse(uint)", AS_METHODPR(Shader, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetName(const String&in)", AS_METHODPR(Shader, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "void set_name(const String&in)", AS_METHODPR(Shader, SetName, (const String&), void), AS_CALL_THISCALL);
    // explicit Shader::Shader(Context* context) | File: ../Graphics/Shader.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_FACTORY, "Shader@+ f()", AS_FUNCTION(Shader_Shader_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromAllEvents()", AS_METHODPR(Shader, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Shader_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Shader, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Shader, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Shader, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Shader", "int WeakRefs() const", AS_METHODPR(Shader, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "int get_weakRefs() const", AS_METHODPR(Shader, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Shader, "Shader")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Shader, "Shader")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Shader, "Shader")
#endif
#ifdef REGISTER_MANUAL_PART_Shader
    REGISTER_MANUAL_PART_Shader(Shader, "Shader")
#endif
    RegisterSubclass<Resource, Shader>(engine, "Resource", "Shader");
    RegisterSubclass<Object, Shader>(engine, "Object", "Shader");
    RegisterSubclass<RefCounted, Shader>(engine, "RefCounted", "Shader");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ShaderParameterAnimationInfo, AddRef, (), void), AS_CALL_THISCALL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "ValueAnimation@+ GetAnimation() const", AS_METHODPR(ShaderParameterAnimationInfo, GetAnimation, () const, ValueAnimation*), AS_CALL_THISCALL);
    // const String& ShaderParameterAnimationInfo::GetName() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "const String& GetName() const", AS_METHODPR(ShaderParameterAnimationInfo, GetName, () const, const String&), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "float GetSpeed() const", AS_METHODPR(ShaderParameterAnimationInfo, GetSpeed, () const, float), AS_CALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "Object@+ GetTarget() const", AS_METHODPR(ShaderParameterAnimationInfo, GetTarget, () const, Object*), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "float GetTime() const", AS_METHODPR(ShaderParameterAnimationInfo, GetTime, () const, float), AS_CALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "WrapMode GetWrapMode() const", AS_METHODPR(ShaderParameterAnimationInfo, GetWrapMode, () const, WrapMode), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int Refs() const", AS_METHODPR(ShaderParameterAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int get_refs() const", AS_METHODPR(ShaderParameterAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ShaderParameterAnimationInfo, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "void SetSpeed(float)", AS_METHODPR(ShaderParameterAnimationInfo, SetSpeed, (float), void), AS_CALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "bool SetTime(float)", AS_METHODPR(ShaderParameterAnimationInfo, SetTime, (float), bool), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "void SetWrapMode(WrapMode)", AS_METHODPR(ShaderParameterAnimationInfo, SetWrapMode, (WrapMode), void), AS_CALL_THISCALL);
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(Material@+, const String&in, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_Material_String_ValueAnimation_WrapMode_float), AS_CALL_CDECL);
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(const ShaderParameterAnimationInfo&in)", AS_FUNCTION(ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_ShaderParameterAnimationInfo), AS_CALL_CDECL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "bool Update(float)", AS_METHODPR(ShaderParameterAnimationInfo, Update, (float), bool), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int WeakRefs() const", AS_METHODPR(ShaderParameterAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int get_weakRefs() const", AS_METHODPR(ShaderParameterAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ValueAnimationInfo
    REGISTER_MANUAL_PART_ValueAnimationInfo(ShaderParameterAnimationInfo, "ShaderParameterAnimationInfo")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ShaderParameterAnimationInfo, "ShaderParameterAnimationInfo")
#endif
#ifdef REGISTER_MANUAL_PART_ShaderParameterAnimationInfo
    REGISTER_MANUAL_PART_ShaderParameterAnimationInfo(ShaderParameterAnimationInfo, "ShaderParameterAnimationInfo")
#endif
    RegisterSubclass<ValueAnimationInfo, ShaderParameterAnimationInfo>(engine, "ValueAnimationInfo", "ShaderParameterAnimationInfo");
    RegisterSubclass<RefCounted, ShaderParameterAnimationInfo>(engine, "RefCounted", "ShaderParameterAnimationInfo");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ShaderPrecache, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool GetBlockEvents() const", AS_METHODPR(ShaderPrecache, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const String& GetCategory() const", AS_METHODPR(ShaderPrecache, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const String& get_category() const", AS_METHODPR(ShaderPrecache, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "VariantMap& GetEventDataMap() const", AS_METHODPR(ShaderPrecache, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "Object@+ GetEventSender() const", AS_METHODPR(ShaderPrecache, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ShaderPrecache, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ShaderPrecache, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ShaderPrecache, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const VariantMap& get_globalVars() const", AS_METHODPR(ShaderPrecache, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ShaderPrecache, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "StringHash GetType() const", AS_METHODPR(ShaderPrecache, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "StringHash get_type() const", AS_METHODPR(ShaderPrecache, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const String& GetTypeName() const", AS_METHODPR(ShaderPrecache, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const String& get_typeName() const", AS_METHODPR(ShaderPrecache, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasEventHandlers() const", AS_METHODPR(ShaderPrecache, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ShaderPrecache, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ShaderPrecache, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ShaderPrecache, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // static void ShaderPrecache::LoadShaders(Graphics* graphics, Deserializer& source) | File: ../Graphics/ShaderPrecache.h
    engine->SetDefaultNamespace("ShaderPrecache");
    engine->RegisterGlobalFunction("void LoadShaders(Graphics@+, Deserializer&)", AS_FUNCTIONPR(ShaderPrecache::LoadShaders, (Graphics*, Deserializer&), void), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ShaderPrecache, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderPrecache", "int Refs() const", AS_METHODPR(ShaderPrecache, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "int get_refs() const", AS_METHODPR(ShaderPrecache, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ShaderPrecache, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SendEvent(StringHash)", AS_METHODPR(ShaderPrecache, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ShaderPrecache, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SetBlockEvents(bool)", AS_METHODPR(ShaderPrecache, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ShaderPrecache, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ShaderPrecache, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // ShaderPrecache::ShaderPrecache(Context* context, const String& fileName) | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_FACTORY, "ShaderPrecache@+ f(const String&in)", AS_FUNCTION(ShaderPrecache_ShaderPrecache_Context_String), AS_CALL_CDECL);
    // void ShaderPrecache::StoreShaders(ShaderVariation* vs, ShaderVariation* ps) | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectMethod("ShaderPrecache", "void StoreShaders(ShaderVariation@+, ShaderVariation@+)", AS_METHODPR(ShaderPrecache, StoreShaders, (ShaderVariation*, ShaderVariation*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromAllEvents()", AS_METHODPR(ShaderPrecache, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ShaderPrecache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ShaderPrecache, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ShaderPrecache, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ShaderPrecache, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderPrecache", "int WeakRefs() const", AS_METHODPR(ShaderPrecache, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "int get_weakRefs() const", AS_METHODPR(ShaderPrecache, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ShaderPrecache, "ShaderPrecache")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ShaderPrecache, "ShaderPrecache")
#endif
#ifdef REGISTER_MANUAL_PART_ShaderPrecache
    REGISTER_MANUAL_PART_ShaderPrecache(ShaderPrecache, "ShaderPrecache")
#endif
    RegisterSubclass<Object, ShaderPrecache>(engine, "Object", "ShaderPrecache");
    RegisterSubclass<RefCounted, ShaderPrecache>(engine, "RefCounted", "ShaderPrecache");

    // const char* ShaderVariation::elementSemanticNames[] | File: ../Graphics/ShaderVariation.h
    // Error: type "const char*" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ShaderVariation, AddRef, (), void), AS_CALL_THISCALL);
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "void ClearDataLost()", AS_METHODPR(ShaderVariation, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool ShaderVariation::Create() | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool Create()", AS_METHODPR(ShaderVariation, Create, (), bool), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& ShaderVariation::GetByteCode() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const String& ShaderVariation::GetCompilerOutput() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetCompilerOutput() const", AS_METHODPR(ShaderVariation, GetCompilerOutput, () const, const String&), AS_CALL_THISCALL);
    // const unsigned* ShaderVariation::GetConstantBufferSizes() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const unsigned*" can not automatically bind
    // const String& ShaderVariation::GetDefines() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetDefines() const", AS_METHODPR(ShaderVariation, GetDefines, () const, const String&), AS_CALL_THISCALL);
    // const String& ShaderVariation::GetDefinesClipPlane() | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetDefinesClipPlane()", AS_METHODPR(ShaderVariation, GetDefinesClipPlane, (), const String&), AS_CALL_THISCALL);
    // unsigned long long ShaderVariation::GetElementHash() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "uint64 GetElementHash() const", AS_METHODPR(ShaderVariation, GetElementHash, () const, unsigned long long), AS_CALL_THISCALL);
    // String ShaderVariation::GetFullName() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "String GetFullName() const", AS_METHODPR(ShaderVariation, GetFullName, () const, String), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "uint GetGPUObjectName() const", AS_METHODPR(ShaderVariation, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "Graphics@+ GetGraphics() const", AS_METHODPR(ShaderVariation, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // const String& ShaderVariation::GetName() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetName() const", AS_METHODPR(ShaderVariation, GetName, () const, const String&), AS_CALL_THISCALL);
    // Shader* ShaderVariation::GetOwner() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "Shader@+ GetOwner() const", AS_METHODPR(ShaderVariation, GetOwner, () const, Shader*), AS_CALL_THISCALL);
    // const HashMap<StringHash, ShaderParameter>& ShaderVariation::GetParameters() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const HashMap<StringHash, ShaderParameter>&" can not automatically bind
    // ShaderType ShaderVariation::GetShaderType() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "ShaderType GetShaderType() const", AS_METHODPR(ShaderVariation, GetShaderType, () const, ShaderType), AS_CALL_THISCALL);
    // bool ShaderVariation::HasParameter(StringHash param) const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasParameter(StringHash) const", AS_METHODPR(ShaderVariation, HasParameter, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasPendingData() const", AS_METHODPR(ShaderVariation, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool ShaderVariation::HasTextureUnit(TextureUnit unit) const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasTextureUnit(TextureUnit) const", AS_METHODPR(ShaderVariation, HasTextureUnit, (TextureUnit) const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "bool IsDataLost() const", AS_METHODPR(ShaderVariation, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "bool get_dataLost() const", AS_METHODPR(ShaderVariation, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // void ShaderVariation::OnDeviceLost() override | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void OnDeviceLost()", AS_METHODPR(ShaderVariation, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "void OnDeviceReset()", AS_METHODPR(ShaderVariation, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderVariation", "int Refs() const", AS_METHODPR(ShaderVariation, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "int get_refs() const", AS_METHODPR(ShaderVariation, Refs, () const, int), AS_CALL_THISCALL);
    // void ShaderVariation::Release() override | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void Release()", AS_METHODPR(ShaderVariation, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ShaderVariation, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ShaderVariation::SetDefines(const String& defines) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void SetDefines(const String&in)", AS_METHODPR(ShaderVariation, SetDefines, (const String&), void), AS_CALL_THISCALL);
    // void ShaderVariation::SetName(const String& name) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void SetName(const String&in)", AS_METHODPR(ShaderVariation, SetName, (const String&), void), AS_CALL_THISCALL);
    // ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_FACTORY, "ShaderVariation@+ f(Shader@+, ShaderType)", AS_FUNCTION(ShaderVariation_ShaderVariation_Shader_ShaderType), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderVariation", "int WeakRefs() const", AS_METHODPR(ShaderVariation, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "int get_weakRefs() const", AS_METHODPR(ShaderVariation, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ShaderVariation, "ShaderVariation")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(ShaderVariation, "ShaderVariation")
#endif
#ifdef REGISTER_MANUAL_PART_ShaderVariation
    REGISTER_MANUAL_PART_ShaderVariation(ShaderVariation, "ShaderVariation")
#endif
    RegisterSubclass<RefCounted, ShaderVariation>(engine, "RefCounted", "ShaderVariation");

    // void Skeleton::ClearBones() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void ClearBones()", AS_METHODPR(Skeleton, ClearBones, (), void), AS_CALL_THISCALL);
    // void Skeleton::Define(const Skeleton& src) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void Define(const Skeleton&in)", AS_METHODPR(Skeleton, Define, (const Skeleton&), void), AS_CALL_THISCALL);
    // Bone* Skeleton::GetBone(unsigned index) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(uint)", AS_METHODPR(Skeleton, GetBone, (unsigned), Bone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_bones(uint)", AS_METHODPR(Skeleton, GetBone, (unsigned), Bone*), AS_CALL_THISCALL);
    // Bone* Skeleton::GetBone(const String& name) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const String&in)", AS_METHODPR(Skeleton, GetBone, (const String&), Bone*), AS_CALL_THISCALL);
    // Bone* Skeleton::GetBone(const char* name) | File: ../Graphics/Skeleton.h
    // Error: type "const char*" can not automatically bind
    // Bone* Skeleton::GetBone(const StringHash& boneNameHash) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const StringHash&in)", AS_METHODPR(Skeleton, GetBone, (const StringHash&), Bone*), AS_CALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const String& boneName) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(const String&in) const", AS_METHODPR(Skeleton, GetBoneIndex, (const String&) const, unsigned), AS_CALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const StringHash& boneNameHash) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(const StringHash&in) const", AS_METHODPR(Skeleton, GetBoneIndex, (const StringHash&) const, unsigned), AS_CALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const Bone* bone) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(Bone@+) const", AS_METHODPR(Skeleton, GetBoneIndex, (const Bone*) const, unsigned), AS_CALL_THISCALL);
    // Bone* Skeleton::GetBoneParent(const Bone* bone) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBoneParent(Bone@+)", AS_METHODPR(Skeleton, GetBoneParent, (const Bone*), Bone*), AS_CALL_THISCALL);
    // const Vector<Bone>& Skeleton::GetBones() const | File: ../Graphics/Skeleton.h
    // Error: type "const Vector<Bone>&" can not automatically bind
    // Vector<Bone>& Skeleton::GetModifiableBones() | File: ../Graphics/Skeleton.h
    // Error: type "Vector<Bone>&" can not automatically bind
    // unsigned Skeleton::GetNumBones() const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetNumBones() const", AS_METHODPR(Skeleton, GetNumBones, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "uint get_numBones() const", AS_METHODPR(Skeleton, GetNumBones, () const, unsigned), AS_CALL_THISCALL);
    // Bone* Skeleton::GetRootBone() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetRootBone()", AS_METHODPR(Skeleton, GetRootBone, (), Bone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_rootBone()", AS_METHODPR(Skeleton, GetRootBone, (), Bone*), AS_CALL_THISCALL);
    // bool Skeleton::Load(Deserializer& source) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "bool Load(Deserializer&)", AS_METHODPR(Skeleton, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // void Skeleton::Reset() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void Reset()", AS_METHODPR(Skeleton, Reset, (), void), AS_CALL_THISCALL);
    // void Skeleton::ResetSilent() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void ResetSilent()", AS_METHODPR(Skeleton, ResetSilent, (), void), AS_CALL_THISCALL);
    // bool Skeleton::Save(Serializer& dest) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "bool Save(Serializer&) const", AS_METHODPR(Skeleton, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // void Skeleton::SetRootBoneIndex(unsigned index) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void SetRootBoneIndex(uint)", AS_METHODPR(Skeleton, SetRootBoneIndex, (unsigned), void), AS_CALL_THISCALL);
    // Skeleton& Skeleton::operator=(const Skeleton&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Skeleton>(engine, "Skeleton");
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Skeleton
    REGISTER_MANUAL_PART_Skeleton(Skeleton, "Skeleton")
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void AddLight(Light@+)", AS_METHODPR(Skybox, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Skybox, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void AddVertexLight(Light@+)", AS_METHODPR(Skybox, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void AllocateNetworkState()", AS_METHODPR(Skybox, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void ApplyAttributes()", AS_METHODPR(Skybox, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void ApplyMaterialList(const String&in = String::EMPTY)", AS_METHODPR(Skybox, ApplyMaterialList, (const String&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Skybox, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Skybox, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool GetAnimationEnabled() const", AS_METHODPR(Skybox, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_animationEnabled() const", AS_METHODPR(Skybox, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttribute(uint) const", AS_METHODPR(Skybox, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Variant get_attributes(uint) const", AS_METHODPR(Skybox, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttribute(const String&in) const", AS_METHODPR(Skybox, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Skybox, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Skybox, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Skybox, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Skybox, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Skybox, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Skybox, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Skybox, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool GetBlockEvents() const", AS_METHODPR(Skybox, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Skybox, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Skybox, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool GetCastShadows() const", AS_METHODPR(Skybox, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_castShadows() const", AS_METHODPR(Skybox, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const String& GetCategory() const", AS_METHODPR(Skybox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const String& get_category() const", AS_METHODPR(Skybox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Skybox, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Skybox", "float GetDistance() const", AS_METHODPR(Skybox, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint8 GetDrawableFlags() const", AS_METHODPR(Skybox, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetDrawDistance() const", AS_METHODPR(Skybox, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_drawDistance() const", AS_METHODPR(Skybox, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "VariantMap& GetEventDataMap() const", AS_METHODPR(Skybox, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "Object@+ GetEventSender() const", AS_METHODPR(Skybox, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Light@+ GetFirstLight() const", AS_METHODPR(Skybox, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Skybox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Skybox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Skybox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const VariantMap& get_globalVars() const", AS_METHODPR(Skybox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "uint GetID() const", AS_METHODPR(Skybox, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_id() const", AS_METHODPR(Skybox, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Skybox, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetLightMask() const", AS_METHODPR(Skybox, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_lightMask() const", AS_METHODPR(Skybox, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Skybox_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetLodBias() const", AS_METHODPR(Skybox, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_lodBias() const", AS_METHODPR(Skybox, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetLodDistance() const", AS_METHODPR(Skybox, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Skybox, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Material@+ GetMaterial() const", AS_METHODPR(Skybox, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ get_material() const", AS_METHODPR(Skybox, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Material@+ GetMaterial(uint) const", AS_METHODPR(Skybox, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ get_materials(uint) const", AS_METHODPR(Skybox, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "const ResourceRefList& GetMaterialsAttr() const", AS_METHODPR(Skybox, GetMaterialsAttr, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetMaxLights() const", AS_METHODPR(Skybox, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_maxLights() const", AS_METHODPR(Skybox, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetMaxZ() const", AS_METHODPR(Skybox, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetMinZ() const", AS_METHODPR(Skybox, GetMinZ, () const, float), AS_CALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Model@+ GetModel() const", AS_METHODPR(Skybox, GetModel, () const, Model*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Model@+ get_model() const", AS_METHODPR(Skybox, GetModel, () const, Model*), AS_CALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "ResourceRef GetModelAttr() const", AS_METHODPR(Skybox, GetModelAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Node@+ GetNode() const", AS_METHODPR(Skybox, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Node@+ get_node() const", AS_METHODPR(Skybox, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumAttributes() const", AS_METHODPR(Skybox, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_numAttributes() const", AS_METHODPR(Skybox, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumGeometries() const", AS_METHODPR(Skybox, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_numGeometries() const", AS_METHODPR(Skybox, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumNetworkAttributes() const", AS_METHODPR(Skybox, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumOccluderTriangles()", AS_METHODPR(Skybox, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Skybox, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Skybox, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Skybox, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetOcclusionLodLevel() const", AS_METHODPR(Skybox, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_occlusionLodLevel() const", AS_METHODPR(Skybox, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Scene@+ GetScene() const", AS_METHODPR(Skybox, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetShadowDistance() const", AS_METHODPR(Skybox, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_shadowDistance() const", AS_METHODPR(Skybox, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetShadowMask() const", AS_METHODPR(Skybox, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_shadowMask() const", AS_METHODPR(Skybox, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetSortValue() const", AS_METHODPR(Skybox, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Skybox, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "StringHash GetType() const", AS_METHODPR(Skybox, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "StringHash get_type() const", AS_METHODPR(Skybox, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const String& GetTypeName() const", AS_METHODPR(Skybox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const String& get_typeName() const", AS_METHODPR(Skybox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Skybox, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Skybox_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetViewMask() const", AS_METHODPR(Skybox, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_viewMask() const", AS_METHODPR(Skybox, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Skybox, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Skybox, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Zone@+ GetZone() const", AS_METHODPR(Skybox, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Zone@+ get_zone() const", AS_METHODPR(Skybox, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetZoneMask() const", AS_METHODPR(Skybox, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_zoneMask() const", AS_METHODPR(Skybox, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool HasBasePass(uint) const", AS_METHODPR(Skybox, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasEventHandlers() const", AS_METHODPR(Skybox, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Skybox, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Skybox, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsEnabled() const", AS_METHODPR(Skybox, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_enabled() const", AS_METHODPR(Skybox, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsEnabledEffective() const", AS_METHODPR(Skybox, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_enabledEffective() const", AS_METHODPR(Skybox, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool IsInside(const Vector3&in) const", AS_METHODPR(Skybox, IsInside, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool IsInsideLocal(const Vector3&in) const", AS_METHODPR(Skybox, IsInsideLocal, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Skybox, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView() const", AS_METHODPR(Skybox, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_inView() const", AS_METHODPR(Skybox, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView(Camera@+) const", AS_METHODPR(Skybox, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Skybox, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsOccludee() const", AS_METHODPR(Skybox, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_occludee() const", AS_METHODPR(Skybox, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsOccluder() const", AS_METHODPR(Skybox, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_occluder() const", AS_METHODPR(Skybox, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsReplicated() const", AS_METHODPR(Skybox, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_replicated() const", AS_METHODPR(Skybox, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool IsTemporary() const", AS_METHODPR(Skybox, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_temporary() const", AS_METHODPR(Skybox, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsZoneDirty() const", AS_METHODPR(Skybox, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void LimitLights()", AS_METHODPR(Skybox, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void LimitVertexLights(bool)", AS_METHODPR(Skybox, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool Load(Deserializer&)", AS_METHODPR(Skybox, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Skybox, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Skybox, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkForUpdate()", AS_METHODPR(Skybox, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Skybox, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkInView(uint)", AS_METHODPR(Skybox, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void MarkNetworkUpdate()", AS_METHODPR(Skybox, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Skybox, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Skybox, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Skybox, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void OnSetEnabled()", AS_METHODPR(Skybox, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void PrepareNetworkUpdate()", AS_METHODPR(Skybox, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Skybox::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/Skybox.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Skybox, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Skybox, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Skybox", "int Refs() const", AS_METHODPR(Skybox, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "int get_refs() const", AS_METHODPR(Skybox, Refs, () const, int), AS_CALL_THISCALL);
    // static void Skybox::RegisterObject(Context* context) | File: ../Graphics/Skybox.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Skybox, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void Remove()", AS_METHODPR(Skybox, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Skybox, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveInstanceDefault()", AS_METHODPR(Skybox, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveObjectAnimation()", AS_METHODPR(Skybox, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void ResetToDefault()", AS_METHODPR(Skybox, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool Save(Serializer&) const", AS_METHODPR(Skybox, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SaveDefaultAttributes() const", AS_METHODPR(Skybox, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Skybox, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool SaveXML(XMLElement&) const", AS_METHODPR(Skybox, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SendEvent(StringHash)", AS_METHODPR(Skybox, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Skybox, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAnimationEnabled(bool)", AS_METHODPR(Skybox, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_animationEnabled(bool)", AS_METHODPR(Skybox, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAnimationTime(float)", AS_METHODPR(Skybox, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Skybox, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Skybox, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Skybox, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Skybox, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Skybox, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Skybox, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Skybox, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetBasePass(uint)", AS_METHODPR(Skybox, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SetBlockEvents(bool)", AS_METHODPR(Skybox, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetCastShadows(bool)", AS_METHODPR(Skybox, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_castShadows(bool)", AS_METHODPR(Skybox, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetDrawDistance(float)", AS_METHODPR(Skybox, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_drawDistance(float)", AS_METHODPR(Skybox, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void SetEnabled(bool)", AS_METHODPR(Skybox, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_enabled(bool)", AS_METHODPR(Skybox, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Skybox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Skybox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetInstanceDefault(bool)", AS_METHODPR(Skybox, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Skybox, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetLightMask(uint)", AS_METHODPR(Skybox, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_lightMask(uint)", AS_METHODPR(Skybox, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetLodBias(float)", AS_METHODPR(Skybox, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_lodBias(float)", AS_METHODPR(Skybox, SetLodBias, (float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetMaterial(Material@+)", AS_METHODPR(Skybox, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_material(Material@+)", AS_METHODPR(Skybox, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool SetMaterial(uint, Material@+)", AS_METHODPR(Skybox, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool set_materials(uint, Material@+)", AS_METHODPR(Skybox, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetMaterialsAttr(const ResourceRefList&in)", AS_METHODPR(Skybox, SetMaterialsAttr, (const ResourceRefList&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetMaxLights(uint)", AS_METHODPR(Skybox, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_maxLights(uint)", AS_METHODPR(Skybox, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetMinMaxZ(float, float)", AS_METHODPR(Skybox, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetModelAttr(const ResourceRef&in)", AS_METHODPR(Skybox, SetModelAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Skybox, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Skybox, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Skybox, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetOccludee(bool)", AS_METHODPR(Skybox, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occludee(bool)", AS_METHODPR(Skybox, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetOccluder(bool)", AS_METHODPR(Skybox, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occluder(bool)", AS_METHODPR(Skybox, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetOcclusionLodLevel(uint)", AS_METHODPR(Skybox, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occlusionLodLevel(uint)", AS_METHODPR(Skybox, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetShadowDistance(float)", AS_METHODPR(Skybox, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_shadowDistance(float)", AS_METHODPR(Skybox, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetShadowMask(uint)", AS_METHODPR(Skybox, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_shadowMask(uint)", AS_METHODPR(Skybox, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetSortValue(float)", AS_METHODPR(Skybox, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetTemporary(bool)", AS_METHODPR(Skybox, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_temporary(bool)", AS_METHODPR(Skybox, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetViewMask(uint)", AS_METHODPR(Skybox, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_viewMask(uint)", AS_METHODPR(Skybox, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Skybox, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetZoneMask(uint)", AS_METHODPR(Skybox, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_zoneMask(uint)", AS_METHODPR(Skybox, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // explicit Skybox::Skybox(Context* context) | File: ../Graphics/Skybox.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_FACTORY, "Skybox@+ f()", AS_FUNCTION(Skybox_Skybox_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromAllEvents()", AS_METHODPR(Skybox, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Skybox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Skybox, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Skybox, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Skybox, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void Update(const FrameInfo&in)", AS_METHODPR(Skybox, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Skybox::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/Skybox.h
    engine->RegisterObjectMethod("Skybox", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Skybox, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Skybox, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Skybox", "int WeakRefs() const", AS_METHODPR(Skybox, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "int get_weakRefs() const", AS_METHODPR(Skybox, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Skybox, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Skybox, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Skybox, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_StaticModel
    REGISTER_MANUAL_PART_StaticModel(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Skybox, "Skybox")
#endif
#ifdef REGISTER_MANUAL_PART_Skybox
    REGISTER_MANUAL_PART_Skybox(Skybox, "Skybox")
#endif
    RegisterSubclass<StaticModel, Skybox>(engine, "StaticModel", "Skybox");
    RegisterSubclass<Drawable, Skybox>(engine, "Drawable", "Skybox");
    RegisterSubclass<Component, Skybox>(engine, "Component", "Skybox");
    RegisterSubclass<Animatable, Skybox>(engine, "Animatable", "Skybox");
    RegisterSubclass<Serializable, Skybox>(engine, "Serializable", "Skybox");
    RegisterSubclass<Object, Skybox>(engine, "Object", "Skybox");
    RegisterSubclass<RefCounted, Skybox>(engine, "RefCounted", "Skybox");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddChild(UIElement@+)", AS_METHODPR(Slider, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Slider, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTag(const String&in)", AS_METHODPR(Slider, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Slider, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Slider_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AdjustScissor(IntRect&)", AS_METHODPR(Slider, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void AllocateNetworkState()", AS_METHODPR(Slider, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void ApplyAttributes()", AS_METHODPR(Slider, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void BringToFront()", AS_METHODPR(Slider, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Slider::ChangeValue(float delta) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void ChangeValue(float)", AS_METHODPR(Slider, ChangeValue, (float), void), AS_CALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Slider, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void DisableLayoutUpdate()", AS_METHODPR(Slider, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Slider, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void EnableLayoutUpdate()", AS_METHODPR(Slider, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Slider, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint FindChild(UIElement@+) const", AS_METHODPR(Slider, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool GetAnimationEnabled() const", AS_METHODPR(Slider, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_animationEnabled() const", AS_METHODPR(Slider, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const String& GetAppliedStyle() const", AS_METHODPR(Slider, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_style() const", AS_METHODPR(Slider, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttribute(uint) const", AS_METHODPR(Slider, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Variant get_attributes(uint) const", AS_METHODPR(Slider, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttribute(const String&in) const", AS_METHODPR(Slider, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Slider, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Slider, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Slider, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Slider, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Slider, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Slider, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Slider, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "BlendMode GetBlendMode() const", AS_METHODPR(Slider, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "BlendMode get_blendMode() const", AS_METHODPR(Slider, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool GetBlockEvents() const", AS_METHODPR(Slider, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetBorder() const", AS_METHODPR(Slider, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_border() const", AS_METHODPR(Slider, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetBringToBack() const", AS_METHODPR(Slider, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_bringToBack() const", AS_METHODPR(Slider, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetBringToFront() const", AS_METHODPR(Slider, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_bringToFront() const", AS_METHODPR(Slider, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const String& GetCategory() const", AS_METHODPR(Slider, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_category() const", AS_METHODPR(Slider, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(uint) const", AS_METHODPR(Slider, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_children(uint) const", AS_METHODPR(Slider, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Slider, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Slider, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetChildOffset() const", AS_METHODPR(Slider, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_childOffset() const", AS_METHODPR(Slider, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Slider_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Slider_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Slider_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetClipBorder() const", AS_METHODPR(Slider, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_clipBorder() const", AS_METHODPR(Slider, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetClipChildren() const", AS_METHODPR(Slider, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_clipChildren() const", AS_METHODPR(Slider, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetColor(Corner) const", AS_METHODPR(Slider, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Color& get_colors(Corner) const", AS_METHODPR(Slider, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetColorAttr() const", AS_METHODPR(Slider, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntRect GetCombinedScreenRect()", AS_METHODPR(Slider, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "IntRect get_combinedScreenRect()", AS_METHODPR(Slider, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Slider, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetDerivedColor() const", AS_METHODPR(Slider, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "float GetDerivedOpacity() const", AS_METHODPR(Slider, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_derivedOpacity() const", AS_METHODPR(Slider, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(Slider, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_disabledOffset() const", AS_METHODPR(Slider, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Slider, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Slider, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint GetDragButtonCount() const", AS_METHODPR(Slider, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_dragButtonCount() const", AS_METHODPR(Slider, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Slider, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Slider, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Slider, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Slider, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetEnableAnchor() const", AS_METHODPR(Slider, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enableAnchor() const", AS_METHODPR(Slider, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "VariantMap& GetEventDataMap() const", AS_METHODPR(Slider, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "Object@+ GetEventSender() const", AS_METHODPR(Slider, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "FocusMode GetFocusMode() const", AS_METHODPR(Slider, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "FocusMode get_focusMode() const", AS_METHODPR(Slider, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Slider, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Slider, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Slider, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const VariantMap& get_globalVars() const", AS_METHODPR(Slider, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetHeight() const", AS_METHODPR(Slider, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_height() const", AS_METHODPR(Slider, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Slider, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Slider, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetHoverOffset() const", AS_METHODPR(Slider, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_hoverOffset() const", AS_METHODPR(Slider, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetImageBorder() const", AS_METHODPR(Slider, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_imageBorder() const", AS_METHODPR(Slider, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetImageRect() const", AS_METHODPR(Slider, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_imageRect() const", AS_METHODPR(Slider, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndent() const", AS_METHODPR(Slider, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indent() const", AS_METHODPR(Slider, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndentSpacing() const", AS_METHODPR(Slider, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indentSpacing() const", AS_METHODPR(Slider, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndentWidth() const", AS_METHODPR(Slider, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indentWidth() const", AS_METHODPR(Slider, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Slider, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // BorderImage* Slider::GetKnob() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "BorderImage@+ GetKnob() const", AS_METHODPR(Slider, GetKnob, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "BorderImage@+ get_knob() const", AS_METHODPR(Slider, GetKnob, () const, BorderImage*), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Slider, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_layoutBorder() const", AS_METHODPR(Slider, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetLayoutElementMaxSize() const", AS_METHODPR(Slider, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Slider, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Slider, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "LayoutMode GetLayoutMode() const", AS_METHODPR(Slider, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "LayoutMode get_layoutMode() const", AS_METHODPR(Slider, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetLayoutSpacing() const", AS_METHODPR(Slider, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_layoutSpacing() const", AS_METHODPR(Slider, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "Material@+ GetMaterial() const", AS_METHODPR(Slider, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Material@+ get_material() const", AS_METHODPR(Slider, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Slider, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Slider, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_maxAnchor() const", AS_METHODPR(Slider, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMaxHeight() const", AS_METHODPR(Slider, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_maxHeight() const", AS_METHODPR(Slider, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Slider, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_maxOffset() const", AS_METHODPR(Slider, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMaxSize() const", AS_METHODPR(Slider, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_maxSize() const", AS_METHODPR(Slider, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMaxWidth() const", AS_METHODPR(Slider, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_maxWidth() const", AS_METHODPR(Slider, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetMinAnchor() const", AS_METHODPR(Slider, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_minAnchor() const", AS_METHODPR(Slider, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMinHeight() const", AS_METHODPR(Slider, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_minHeight() const", AS_METHODPR(Slider, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMinOffset() const", AS_METHODPR(Slider, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_minOffset() const", AS_METHODPR(Slider, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMinSize() const", AS_METHODPR(Slider, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_minSize() const", AS_METHODPR(Slider, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMinWidth() const", AS_METHODPR(Slider, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_minWidth() const", AS_METHODPR(Slider, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const String& GetName() const", AS_METHODPR(Slider, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_name() const", AS_METHODPR(Slider, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "uint GetNumAttributes() const", AS_METHODPR(Slider, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_numAttributes() const", AS_METHODPR(Slider, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint GetNumChildren(bool = false) const", AS_METHODPR(Slider, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_numChildren(bool = false) const", AS_METHODPR(Slider, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "uint GetNumNetworkAttributes() const", AS_METHODPR(Slider, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Slider, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Slider, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Slider, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "float GetOpacity() const", AS_METHODPR(Slider, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_opacity() const", AS_METHODPR(Slider, GetOpacity, () const, float), AS_CALL_THISCALL);
    // Orientation Slider::GetOrientation() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "Orientation GetOrientation() const", AS_METHODPR(Slider, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Orientation get_orientation() const", AS_METHODPR(Slider, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetParent() const", AS_METHODPR(Slider, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_parent() const", AS_METHODPR(Slider, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetPivot() const", AS_METHODPR(Slider, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_pivot() const", AS_METHODPR(Slider, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetPosition() const", AS_METHODPR(Slider, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_position() const", AS_METHODPR(Slider, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetPriority() const", AS_METHODPR(Slider, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_priority() const", AS_METHODPR(Slider, GetPriority, () const, int), AS_CALL_THISCALL);
    // float Slider::GetRange() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetRange() const", AS_METHODPR(Slider, GetRange, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_range() const", AS_METHODPR(Slider, GetRange, () const, float), AS_CALL_THISCALL);
    // float Slider::GetRepeatRate() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetRepeatRate() const", AS_METHODPR(Slider, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_repeatRate() const", AS_METHODPR(Slider, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetRoot() const", AS_METHODPR(Slider, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_root() const", AS_METHODPR(Slider, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Slider, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_screenPosition() const", AS_METHODPR(Slider, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetSize() const", AS_METHODPR(Slider, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_size() const", AS_METHODPR(Slider, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetSortChildren() const", AS_METHODPR(Slider, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_sortChildren() const", AS_METHODPR(Slider, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Slider, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Slider_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Slider", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Slider_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "Texture@+ GetTexture() const", AS_METHODPR(Slider, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Texture@+ get_texture() const", AS_METHODPR(Slider, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetTextureAttr() const", AS_METHODPR(Slider, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "TraversalMode GetTraversalMode() const", AS_METHODPR(Slider, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "TraversalMode get_traversalMode() const", AS_METHODPR(Slider, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "StringHash GetType() const", AS_METHODPR(Slider, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "StringHash get_type() const", AS_METHODPR(Slider, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const String& GetTypeName() const", AS_METHODPR(Slider, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_typeName() const", AS_METHODPR(Slider, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetUseDerivedOpacity() const", AS_METHODPR(Slider, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_useDerivedOpacity() const", AS_METHODPR(Slider, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // float Slider::GetValue() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetValue() const", AS_METHODPR(Slider, GetValue, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_value() const", AS_METHODPR(Slider, GetValue, () const, float), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Slider, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const VariantMap& GetVars() const", AS_METHODPR(Slider, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Slider, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Slider, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetWidth() const", AS_METHODPR(Slider, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_width() const", AS_METHODPR(Slider, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasColorGradient() const", AS_METHODPR(Slider, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_colorGradient() const", AS_METHODPR(Slider, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasEventHandlers() const", AS_METHODPR(Slider, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasFocus() const", AS_METHODPR(Slider, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_focus() const", AS_METHODPR(Slider, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Slider, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Slider, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasTag(const String&in) const", AS_METHODPR(Slider, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Slider, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Slider, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEditable() const", AS_METHODPR(Slider, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_editable() const", AS_METHODPR(Slider, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsElementEventSender() const", AS_METHODPR(Slider, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_elementEventSender() const", AS_METHODPR(Slider, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEnabled() const", AS_METHODPR(Slider, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enabled() const", AS_METHODPR(Slider, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEnabledSelf() const", AS_METHODPR(Slider, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enabledSelf() const", AS_METHODPR(Slider, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedHeight() const", AS_METHODPR(Slider, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedHeight() const", AS_METHODPR(Slider, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedSize() const", AS_METHODPR(Slider, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedSize() const", AS_METHODPR(Slider, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedWidth() const", AS_METHODPR(Slider, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedWidth() const", AS_METHODPR(Slider, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsHovering() const", AS_METHODPR(Slider, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_hovering() const", AS_METHODPR(Slider, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInside(IntVector2, bool)", AS_METHODPR(Slider, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Slider, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Slider, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInternal() const", AS_METHODPR(Slider, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_internal() const", AS_METHODPR(Slider, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsSelected() const", AS_METHODPR(Slider, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_selected() const", AS_METHODPR(Slider, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool IsTemporary() const", AS_METHODPR(Slider, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_temporary() const", AS_METHODPR(Slider, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "bool IsTiled() const", AS_METHODPR(Slider, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_tiled() const", AS_METHODPR(Slider, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsVisible() const", AS_METHODPR(Slider, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_visible() const", AS_METHODPR(Slider, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsVisibleEffective() const", AS_METHODPR(Slider, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_visibleEffective() const", AS_METHODPR(Slider, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsWheelHandler() const", AS_METHODPR(Slider, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Slider, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool Load(Deserializer&)", AS_METHODPR(Slider, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Slider, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Slider, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Slider, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Slider, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(Deserializer&)", AS_METHODPR(Slider, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void MarkNetworkUpdate()", AS_METHODPR(Slider, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Slider::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Slider, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Slider::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Slider, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Slider, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Slider::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Slider, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Slider, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Slider, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Slider, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // void Slider::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Slider, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Slider::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Slider, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Slider, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Slider, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // void Slider::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Slider, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnIndentSet()", AS_METHODPR(Slider, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Slider, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Slider, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Slider::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Slider, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Slider, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnSetEditable()", AS_METHODPR(Slider, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnTextInput(const String&in)", AS_METHODPR(Slider, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Slider, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Slider, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Slider, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Slider", "int Refs() const", AS_METHODPR(Slider, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_refs() const", AS_METHODPR(Slider, Refs, () const, int), AS_CALL_THISCALL);
    // static void Slider::RegisterObject(Context* context) | File: ../UI/Slider.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Slider, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void Remove()", AS_METHODPR(Slider, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveAllChildren()", AS_METHODPR(Slider, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveAllTags()", AS_METHODPR(Slider, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Slider, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Slider, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveChildAtIndex(uint)", AS_METHODPR(Slider, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void RemoveInstanceDefault()", AS_METHODPR(Slider, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void RemoveObjectAnimation()", AS_METHODPR(Slider, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool RemoveTag(const String&in)", AS_METHODPR(Slider, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void ResetDeepEnabled()", AS_METHODPR(Slider, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void ResetToDefault()", AS_METHODPR(Slider, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool Save(Serializer&) const", AS_METHODPR(Slider, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SaveDefaultAttributes() const", AS_METHODPR(Slider, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Slider, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SaveXML(XMLElement&) const", AS_METHODPR(Slider, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Slider, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Slider, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SendEvent(StringHash)", AS_METHODPR(Slider, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Slider, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Slider, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAnimationEnabled(bool)", AS_METHODPR(Slider, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_animationEnabled(bool)", AS_METHODPR(Slider, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAnimationTime(float)", AS_METHODPR(Slider, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Slider, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Slider, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Slider, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Slider, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Slider, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Slider, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Slider, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetBlendMode(BlendMode)", AS_METHODPR(Slider, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_blendMode(BlendMode)", AS_METHODPR(Slider, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SetBlockEvents(bool)", AS_METHODPR(Slider, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetBorder(const IntRect&in)", AS_METHODPR(Slider, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_border(const IntRect&in)", AS_METHODPR(Slider, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetBringToBack(bool)", AS_METHODPR(Slider, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_bringToBack(bool)", AS_METHODPR(Slider, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetBringToFront(bool)", AS_METHODPR(Slider, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_bringToFront(bool)", AS_METHODPR(Slider, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Slider, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Slider, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Slider, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetClipChildren(bool)", AS_METHODPR(Slider, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_clipChildren(bool)", AS_METHODPR(Slider, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetColor(const Color&in)", AS_METHODPR(Slider, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_color(const Color&in)", AS_METHODPR(Slider, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetColor(Corner, const Color&in)", AS_METHODPR(Slider, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_colors(Corner, const Color&in)", AS_METHODPR(Slider, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDeepEnabled(bool)", AS_METHODPR(Slider, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Slider, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Slider, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(Slider, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(Slider, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetDisabledOffset(int, int)", AS_METHODPR(Slider, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Slider, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Slider, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEditable(bool)", AS_METHODPR(Slider, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_editable(bool)", AS_METHODPR(Slider, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetElementEventSender(bool)", AS_METHODPR(Slider, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_elementEventSender(bool)", AS_METHODPR(Slider, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnableAnchor(bool)", AS_METHODPR(Slider, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_enableAnchor(bool)", AS_METHODPR(Slider, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnabled(bool)", AS_METHODPR(Slider, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_enabled(bool)", AS_METHODPR(Slider, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnabledRecursive(bool)", AS_METHODPR(Slider, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedHeight(int)", AS_METHODPR(Slider, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Slider, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedSize(int, int)", AS_METHODPR(Slider, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedWidth(int)", AS_METHODPR(Slider, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFocus(bool)", AS_METHODPR(Slider, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_focus(bool)", AS_METHODPR(Slider, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFocusMode(FocusMode)", AS_METHODPR(Slider, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_focusMode(FocusMode)", AS_METHODPR(Slider, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetFullImageRect()", AS_METHODPR(Slider, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Slider, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Slider, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHeight(int)", AS_METHODPR(Slider, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_height(int)", AS_METHODPR(Slider, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Slider, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Slider, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHovering(bool)", AS_METHODPR(Slider, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(Slider, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(Slider, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetHoverOffset(int, int)", AS_METHODPR(Slider, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetImageBorder(const IntRect&in)", AS_METHODPR(Slider, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_imageBorder(const IntRect&in)", AS_METHODPR(Slider, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetImageRect(const IntRect&in)", AS_METHODPR(Slider, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_imageRect(const IntRect&in)", AS_METHODPR(Slider, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetIndent(int)", AS_METHODPR(Slider, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_indent(int)", AS_METHODPR(Slider, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetIndentSpacing(int)", AS_METHODPR(Slider, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_indentSpacing(int)", AS_METHODPR(Slider, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetInstanceDefault(bool)", AS_METHODPR(Slider, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Slider, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetInternal(bool)", AS_METHODPR(Slider, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_internal(bool)", AS_METHODPR(Slider, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Slider, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Slider, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Slider, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Slider, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Slider, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Slider, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutMode(LayoutMode)", AS_METHODPR(Slider, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutSpacing(int)", AS_METHODPR(Slider, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutSpacing(int)", AS_METHODPR(Slider, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetMaterial(Material@+)", AS_METHODPR(Slider, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_material(Material@+)", AS_METHODPR(Slider, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Slider, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Slider, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Slider, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxAnchor(float, float)", AS_METHODPR(Slider, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxHeight(int)", AS_METHODPR(Slider, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxHeight(int)", AS_METHODPR(Slider, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Slider, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Slider, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Slider, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Slider, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxSize(int, int)", AS_METHODPR(Slider, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxWidth(int)", AS_METHODPR(Slider, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxWidth(int)", AS_METHODPR(Slider, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Slider, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Slider, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinAnchor(float, float)", AS_METHODPR(Slider, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinHeight(int)", AS_METHODPR(Slider, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minHeight(int)", AS_METHODPR(Slider, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Slider, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Slider, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Slider, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minSize(const IntVector2&in)", AS_METHODPR(Slider, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinSize(int, int)", AS_METHODPR(Slider, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinWidth(int)", AS_METHODPR(Slider, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minWidth(int)", AS_METHODPR(Slider, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetName(const String&in)", AS_METHODPR(Slider, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_name(const String&in)", AS_METHODPR(Slider, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Slider, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Slider, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Slider, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetOpacity(float)", AS_METHODPR(Slider, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_opacity(float)", AS_METHODPR(Slider, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void Slider::SetOrientation(Orientation orientation) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetOrientation(Orientation)", AS_METHODPR(Slider, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_orientation(Orientation)", AS_METHODPR(Slider, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Slider, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPivot(const Vector2&in)", AS_METHODPR(Slider, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_pivot(const Vector2&in)", AS_METHODPR(Slider, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPivot(float, float)", AS_METHODPR(Slider, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPosition(const IntVector2&in)", AS_METHODPR(Slider, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_position(const IntVector2&in)", AS_METHODPR(Slider, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPosition(int, int)", AS_METHODPR(Slider, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPriority(int)", AS_METHODPR(Slider, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_priority(int)", AS_METHODPR(Slider, SetPriority, (int), void), AS_CALL_THISCALL);
    // void Slider::SetRange(float range) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetRange(float)", AS_METHODPR(Slider, SetRange, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_range(float)", AS_METHODPR(Slider, SetRange, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Slider, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Slider::SetRepeatRate(float rate) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetRepeatRate(float)", AS_METHODPR(Slider, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_repeatRate(float)", AS_METHODPR(Slider, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSelected(bool)", AS_METHODPR(Slider, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_selected(bool)", AS_METHODPR(Slider, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSize(const IntVector2&in)", AS_METHODPR(Slider, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_size(const IntVector2&in)", AS_METHODPR(Slider, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSize(int, int)", AS_METHODPR(Slider, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSortChildren(bool)", AS_METHODPR(Slider, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_sortChildren(bool)", AS_METHODPR(Slider, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Slider, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Slider, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Slider, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Slider_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetTemporary(bool)", AS_METHODPR(Slider, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_temporary(bool)", AS_METHODPR(Slider, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTexture(Texture@+)", AS_METHODPR(Slider, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_texture(Texture@+)", AS_METHODPR(Slider, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Slider, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTiled(bool)", AS_METHODPR(Slider, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_tiled(bool)", AS_METHODPR(Slider, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Slider, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_traversalMode(TraversalMode)", AS_METHODPR(Slider, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Slider, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_useDerivedOpacity(bool)", AS_METHODPR(Slider, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void Slider::SetValue(float value) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetValue(float)", AS_METHODPR(Slider, SetValue, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_value(float)", AS_METHODPR(Slider, SetValue, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Slider, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Slider, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Slider, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVisible(bool)", AS_METHODPR(Slider, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_visible(bool)", AS_METHODPR(Slider, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetWidth(int)", AS_METHODPR(Slider, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_width(int)", AS_METHODPR(Slider, SetWidth, (int), void), AS_CALL_THISCALL);
    // explicit Slider::Slider(Context* context) | File: ../UI/Slider.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_FACTORY, "Slider@+ f()", AS_FUNCTION(Slider_Slider_Context), AS_CALL_CDECL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SortChildren()", AS_METHODPR(Slider, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromAllEvents()", AS_METHODPR(Slider, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Slider_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Slider, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Slider, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Slider, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Slider::Update(float timeStep) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void Update(float)", AS_METHODPR(Slider, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void UpdateLayout()", AS_METHODPR(Slider, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Slider", "int WeakRefs() const", AS_METHODPR(Slider, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_weakRefs() const", AS_METHODPR(Slider, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Slider, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Slider, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Slider, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Slider, "Slider")
#endif
#ifdef REGISTER_MANUAL_PART_Slider
    REGISTER_MANUAL_PART_Slider(Slider, "Slider")
#endif
    RegisterSubclass<BorderImage, Slider>(engine, "BorderImage", "Slider");
    RegisterSubclass<UIElement, Slider>(engine, "UIElement", "Slider");
    RegisterSubclass<Animatable, Slider>(engine, "Animatable", "Slider");
    RegisterSubclass<Serializable, Slider>(engine, "Serializable", "Slider");
    RegisterSubclass<Object, Slider>(engine, "Object", "Slider");
    RegisterSubclass<RefCounted, Slider>(engine, "RefCounted", "Slider");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SmoothedTransform, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void AllocateNetworkState()", AS_METHODPR(SmoothedTransform, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void ApplyAttributes()", AS_METHODPR(SmoothedTransform, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(SmoothedTransform, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetAnimationEnabled() const", AS_METHODPR(SmoothedTransform, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_animationEnabled() const", AS_METHODPR(SmoothedTransform, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttribute(uint) const", AS_METHODPR(SmoothedTransform, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Variant get_attributes(uint) const", AS_METHODPR(SmoothedTransform, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttribute(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttributeDefault(uint) const", AS_METHODPR(SmoothedTransform, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Variant get_attributeDefaults(uint) const", AS_METHODPR(SmoothedTransform, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(SmoothedTransform, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetBlockEvents() const", AS_METHODPR(SmoothedTransform, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const String& GetCategory() const", AS_METHODPR(SmoothedTransform, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const String& get_category() const", AS_METHODPR(SmoothedTransform, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Component@+ GetComponent(StringHash) const", AS_METHODPR(SmoothedTransform, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("SmoothedTransform", "VariantMap& GetEventDataMap() const", AS_METHODPR(SmoothedTransform, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "Object@+ GetEventSender() const", AS_METHODPR(SmoothedTransform, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SmoothedTransform, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SmoothedTransform, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SmoothedTransform, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const VariantMap& get_globalVars() const", AS_METHODPR(SmoothedTransform, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetID() const", AS_METHODPR(SmoothedTransform, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "uint get_id() const", AS_METHODPR(SmoothedTransform, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(SmoothedTransform, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Node@+ GetNode() const", AS_METHODPR(SmoothedTransform, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Node@+ get_node() const", AS_METHODPR(SmoothedTransform, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetNumAttributes() const", AS_METHODPR(SmoothedTransform, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "uint get_numAttributes() const", AS_METHODPR(SmoothedTransform, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetNumNetworkAttributes() const", AS_METHODPR(SmoothedTransform, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(SmoothedTransform, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(SmoothedTransform, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(SmoothedTransform, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Scene@+ GetScene() const", AS_METHODPR(SmoothedTransform, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SmoothedTransform, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector3& SmoothedTransform::GetTargetPosition() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Vector3& GetTargetPosition() const", AS_METHODPR(SmoothedTransform, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Vector3& get_targetPosition() const", AS_METHODPR(SmoothedTransform, GetTargetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // const Quaternion& SmoothedTransform::GetTargetRotation() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Quaternion& GetTargetRotation() const", AS_METHODPR(SmoothedTransform, GetTargetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Quaternion& get_targetRotation() const", AS_METHODPR(SmoothedTransform, GetTargetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // Vector3 SmoothedTransform::GetTargetWorldPosition() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "Vector3 GetTargetWorldPosition() const", AS_METHODPR(SmoothedTransform, GetTargetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Vector3 get_targetWorldPosition() const", AS_METHODPR(SmoothedTransform, GetTargetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    // Quaternion SmoothedTransform::GetTargetWorldRotation() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "Quaternion GetTargetWorldRotation() const", AS_METHODPR(SmoothedTransform, GetTargetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Quaternion get_targetWorldRotation() const", AS_METHODPR(SmoothedTransform, GetTargetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "StringHash GetType() const", AS_METHODPR(SmoothedTransform, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "StringHash get_type() const", AS_METHODPR(SmoothedTransform, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const String& GetTypeName() const", AS_METHODPR(SmoothedTransform, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const String& get_typeName() const", AS_METHODPR(SmoothedTransform, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasEventHandlers() const", AS_METHODPR(SmoothedTransform, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SmoothedTransform, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SmoothedTransform, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsEnabled() const", AS_METHODPR(SmoothedTransform, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_enabled() const", AS_METHODPR(SmoothedTransform, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsEnabledEffective() const", AS_METHODPR(SmoothedTransform, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_enabledEffective() const", AS_METHODPR(SmoothedTransform, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool SmoothedTransform::IsInProgress() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsInProgress() const", AS_METHODPR(SmoothedTransform, IsInProgress, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_inProgress() const", AS_METHODPR(SmoothedTransform, IsInProgress, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SmoothedTransform, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsReplicated() const", AS_METHODPR(SmoothedTransform, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_replicated() const", AS_METHODPR(SmoothedTransform, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsTemporary() const", AS_METHODPR(SmoothedTransform, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_temporary() const", AS_METHODPR(SmoothedTransform, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool Load(Deserializer&)", AS_METHODPR(SmoothedTransform, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(SmoothedTransform, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool LoadXML(const XMLElement&in)", AS_METHODPR(SmoothedTransform, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void MarkNetworkUpdate()", AS_METHODPR(SmoothedTransform, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SmoothedTransform, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(SmoothedTransform, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(SmoothedTransform, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnSetEnabled()", AS_METHODPR(SmoothedTransform, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void PrepareNetworkUpdate()", AS_METHODPR(SmoothedTransform, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(SmoothedTransform, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(SmoothedTransform, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SmoothedTransform", "int Refs() const", AS_METHODPR(SmoothedTransform, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "int get_refs() const", AS_METHODPR(SmoothedTransform, Refs, () const, int), AS_CALL_THISCALL);
    // static void SmoothedTransform::RegisterObject(Context* context) | File: ../Scene/SmoothedTransform.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SmoothedTransform, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void Remove()", AS_METHODPR(SmoothedTransform, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(SmoothedTransform, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveInstanceDefault()", AS_METHODPR(SmoothedTransform, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveObjectAnimation()", AS_METHODPR(SmoothedTransform, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void ResetToDefault()", AS_METHODPR(SmoothedTransform, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool Save(Serializer&) const", AS_METHODPR(SmoothedTransform, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveDefaultAttributes() const", AS_METHODPR(SmoothedTransform, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveJSON(JSONValue&) const", AS_METHODPR(SmoothedTransform, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveXML(XMLElement&) const", AS_METHODPR(SmoothedTransform, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SendEvent(StringHash)", AS_METHODPR(SmoothedTransform, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SmoothedTransform, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAnimationEnabled(bool)", AS_METHODPR(SmoothedTransform, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_animationEnabled(bool)", AS_METHODPR(SmoothedTransform, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAnimationTime(float)", AS_METHODPR(SmoothedTransform, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(SmoothedTransform, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(SmoothedTransform, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(SmoothedTransform, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(SmoothedTransform, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(SmoothedTransform, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(SmoothedTransform, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(SmoothedTransform, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetBlockEvents(bool)", AS_METHODPR(SmoothedTransform, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetEnabled(bool)", AS_METHODPR(SmoothedTransform, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_enabled(bool)", AS_METHODPR(SmoothedTransform, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SmoothedTransform, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SmoothedTransform, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetInstanceDefault(bool)", AS_METHODPR(SmoothedTransform, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(SmoothedTransform, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(SmoothedTransform, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(SmoothedTransform, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(SmoothedTransform, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SmoothedTransform::SetTargetPosition(const Vector3& position) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetPosition(const Vector3&in)", AS_METHODPR(SmoothedTransform, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetPosition(const Vector3&in)", AS_METHODPR(SmoothedTransform, SetTargetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void SmoothedTransform::SetTargetRotation(const Quaternion& rotation) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetRotation(const Quaternion&in)", AS_METHODPR(SmoothedTransform, SetTargetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetRotation(const Quaternion&in)", AS_METHODPR(SmoothedTransform, SetTargetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void SmoothedTransform::SetTargetWorldPosition(const Vector3& position) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetWorldPosition(const Vector3&in)", AS_METHODPR(SmoothedTransform, SetTargetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldPosition(const Vector3&in)", AS_METHODPR(SmoothedTransform, SetTargetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void SmoothedTransform::SetTargetWorldRotation(const Quaternion& rotation) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetWorldRotation(const Quaternion&in)", AS_METHODPR(SmoothedTransform, SetTargetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldRotation(const Quaternion&in)", AS_METHODPR(SmoothedTransform, SetTargetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTemporary(bool)", AS_METHODPR(SmoothedTransform, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_temporary(bool)", AS_METHODPR(SmoothedTransform, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // explicit SmoothedTransform::SmoothedTransform(Context* context) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_FACTORY, "SmoothedTransform@+ f()", AS_FUNCTION(SmoothedTransform_SmoothedTransform_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromAllEvents()", AS_METHODPR(SmoothedTransform, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SmoothedTransform_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SmoothedTransform, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SmoothedTransform, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SmoothedTransform, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void SmoothedTransform::Update(float constant, float squaredSnapThreshold) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void Update(float, float)", AS_METHODPR(SmoothedTransform, Update, (float, float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SmoothedTransform", "int WeakRefs() const", AS_METHODPR(SmoothedTransform, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "int get_weakRefs() const", AS_METHODPR(SmoothedTransform, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(SmoothedTransform, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(SmoothedTransform, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(SmoothedTransform, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(SmoothedTransform, "SmoothedTransform")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(SmoothedTransform, "SmoothedTransform")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(SmoothedTransform, "SmoothedTransform")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SmoothedTransform, "SmoothedTransform")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SmoothedTransform, "SmoothedTransform")
#endif
#ifdef REGISTER_MANUAL_PART_SmoothedTransform
    REGISTER_MANUAL_PART_SmoothedTransform(SmoothedTransform, "SmoothedTransform")
#endif
    RegisterSubclass<Component, SmoothedTransform>(engine, "Component", "SmoothedTransform");
    RegisterSubclass<Animatable, SmoothedTransform>(engine, "Animatable", "SmoothedTransform");
    RegisterSubclass<Serializable, SmoothedTransform>(engine, "Serializable", "SmoothedTransform");
    RegisterSubclass<Object, SmoothedTransform>(engine, "Object", "SmoothedTransform");
    RegisterSubclass<RefCounted, SmoothedTransform>(engine, "RefCounted", "SmoothedTransform");

    // bool ScenePassInfo::allowInstancing_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("ScenePassInfo", "bool allowInstancing", offsetof(ScenePassInfo, allowInstancing_));
    // BatchQueue* ScenePassInfo::batchQueue_ | File: ../Graphics/View.h
    // BatchQueue* can not be registered
    // bool ScenePassInfo::markToStencil_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("ScenePassInfo", "bool markToStencil", offsetof(ScenePassInfo, markToStencil_));
    // unsigned ScenePassInfo::passIndex_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("ScenePassInfo", "uint passIndex", offsetof(ScenePassInfo, passIndex_));
    // bool ScenePassInfo::vertexLights_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("ScenePassInfo", "bool vertexLights", offsetof(ScenePassInfo, vertexLights_));
    // ScenePassInfo& ScenePassInfo::operator=(const ScenePassInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScenePassInfo>(engine, "ScenePassInfo");
#ifdef REGISTER_MANUAL_PART_ScenePassInfo
    REGISTER_MANUAL_PART_ScenePassInfo(ScenePassInfo, "ScenePassInfo")
#endif

    // Connection* ReplicationState::connection_ | File: ../Scene/ReplicationState.h
    // Connection* can not be registered
    // HashSet<unsigned> SceneReplicationState::dirtyNodes_ | File: ../Scene/ReplicationState.h
    // Error: type "HashSet<unsigned>" can not automatically bind
    // HashMap<unsigned, NodeReplicationState> SceneReplicationState::nodeStates_ | File: ../Scene/ReplicationState.h
    // Error: type "HashMap<unsigned, NodeReplicationState>" can not automatically bind
    // void SceneReplicationState::Clear() | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("SceneReplicationState", "void Clear()", AS_METHODPR(SceneReplicationState, Clear, (), void), AS_CALL_THISCALL);
    // SceneReplicationState& SceneReplicationState::operator=(const SceneReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SceneReplicationState>(engine, "SceneReplicationState");
#ifdef REGISTER_MANUAL_PART_ReplicationState
    REGISTER_MANUAL_PART_ReplicationState(SceneReplicationState, "SceneReplicationState")
#endif
#ifdef REGISTER_MANUAL_PART_SceneReplicationState
    REGISTER_MANUAL_PART_SceneReplicationState(SceneReplicationState, "SceneReplicationState")
#endif

    // SharedArrayPtr<unsigned char> ScratchBuffer::data_ | File: ../Graphics/Graphics.h
    // Error: type "SharedArrayPtr<unsigned char>" can not automatically bind
    // bool ScratchBuffer::reserved_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScratchBuffer", "bool reserved", offsetof(ScratchBuffer, reserved_));
    // unsigned ScratchBuffer::size_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScratchBuffer", "uint size", offsetof(ScratchBuffer, size_));
    // ScratchBuffer& ScratchBuffer::operator=(const ScratchBuffer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScratchBuffer>(engine, "ScratchBuffer");
#ifdef REGISTER_MANUAL_PART_ScratchBuffer
    REGISTER_MANUAL_PART_ScratchBuffer(ScratchBuffer, "ScratchBuffer")
#endif

    // bool ScreenModeParams::borderless_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool borderless", offsetof(ScreenModeParams, borderless_));
    // bool ScreenModeParams::fullscreen_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool fullscreen", offsetof(ScreenModeParams, fullscreen_));
    // bool ScreenModeParams::highDPI_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool highDPI", offsetof(ScreenModeParams, highDPI_));
    // int ScreenModeParams::monitor_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "int monitor", offsetof(ScreenModeParams, monitor_));
    // int ScreenModeParams::multiSample_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "int multiSample", offsetof(ScreenModeParams, multiSample_));
    // int ScreenModeParams::refreshRate_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "int refreshRate", offsetof(ScreenModeParams, refreshRate_));
    // bool ScreenModeParams::resizable_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool resizable", offsetof(ScreenModeParams, resizable_));
    // bool ScreenModeParams::tripleBuffer_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool tripleBuffer", offsetof(ScreenModeParams, tripleBuffer_));
    // bool ScreenModeParams::vsync_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("ScreenModeParams", "bool vsync", offsetof(ScreenModeParams, vsync_));
    // bool ScreenModeParams::EqualsExceptVSync(const ScreenModeParams& rhs) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("ScreenModeParams", "bool EqualsExceptVSync(const ScreenModeParams&in) const", AS_METHODPR(ScreenModeParams, EqualsExceptVSync, (const ScreenModeParams&) const, bool), AS_CALL_THISCALL);
    // bool ScreenModeParams::operator==(const ScreenModeParams& rhs) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("ScreenModeParams", "bool opEquals(const ScreenModeParams&in) const", AS_METHODPR(ScreenModeParams, operator==, (const ScreenModeParams&) const, bool), AS_CALL_THISCALL);
    // ScreenModeParams& ScreenModeParams::operator=(const ScreenModeParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ScreenModeParams>(engine, "ScreenModeParams");
#ifdef REGISTER_MANUAL_PART_ScreenModeParams
    REGISTER_MANUAL_PART_ScreenModeParams(ScreenModeParams, "ScreenModeParams")
#endif

    // unsigned ShaderParameter::buffer_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint buffer", offsetof(ShaderParameter, buffer_));
    // ConstantBuffer* ShaderParameter::bufferPtr_ | File: ../Graphics/ShaderVariation.h
    // ConstantBuffer* can not be registered
    // unsigned ShaderParameter::glType_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint glType", offsetof(ShaderParameter, glType_));
    // int ShaderParameter::location_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "int location", offsetof(ShaderParameter, location_));
    // String ShaderParameter::name_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "String name", offsetof(ShaderParameter, name_));
    // unsigned ShaderParameter::offset_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint offset", offsetof(ShaderParameter, offset_));
    // unsigned ShaderParameter::regCount_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint regCount", offsetof(ShaderParameter, regCount_));
    // unsigned ShaderParameter::register_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint register", offsetof(ShaderParameter, register_));
    // unsigned ShaderParameter::size_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "uint size", offsetof(ShaderParameter, size_));
    // ShaderType ShaderParameter::type_ | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectProperty("ShaderParameter", "ShaderType type", offsetof(ShaderParameter, type_));
    // ShaderParameter::ShaderParameter(const String& name, unsigned glType, int location) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(const String&in, uint, int)", AS_FUNCTION_OBJFIRST(ShaderParameter_ShaderParameter_String_unsigned_int), AS_CALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint, uint)", AS_FUNCTION_OBJFIRST(ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned_unsigned), AS_CALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint)", AS_FUNCTION_OBJFIRST(ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned), AS_CALL_CDECL_OBJFIRST);
    // ShaderParameter& ShaderParameter::operator=(const ShaderParameter&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ShaderParameter>(engine, "ShaderParameter");
#ifdef REGISTER_MANUAL_PART_ShaderParameter
    REGISTER_MANUAL_PART_ShaderParameter(ShaderParameter, "ShaderParameter")
#endif

    // float ShadowBatchQueue::farSplit_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("ShadowBatchQueue", "float farSplit", offsetof(ShadowBatchQueue, farSplit_));
    // float ShadowBatchQueue::nearSplit_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("ShadowBatchQueue", "float nearSplit", offsetof(ShadowBatchQueue, nearSplit_));
    // BatchQueue ShadowBatchQueue::shadowBatches_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("ShadowBatchQueue", "BatchQueue shadowBatches", offsetof(ShadowBatchQueue, shadowBatches_));
    // Camera* ShadowBatchQueue::shadowCamera_ | File: ../Graphics/Batch.h
    // Camera* can not be registered
    // IntRect ShadowBatchQueue::shadowViewport_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("ShadowBatchQueue", "IntRect shadowViewport", offsetof(ShadowBatchQueue, shadowViewport_));
    // ShadowBatchQueue& ShadowBatchQueue::operator=(const ShadowBatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ShadowBatchQueue>(engine, "ShadowBatchQueue");
#ifdef REGISTER_MANUAL_PART_ShadowBatchQueue
    REGISTER_MANUAL_PART_ShadowBatchQueue(ShadowBatchQueue, "ShadowBatchQueue")
#endif

#ifdef URHO3D_NAVIGATION
    // rcCompactHeightfield* NavBuildData::compactHeightField_ | File: ../Navigation/NavBuildData.h
    // rcCompactHeightfield* can not be registered
    // rcContourSet* SimpleNavBuildData::contourSet_ | File: ../Navigation/NavBuildData.h
    // rcContourSet* can not be registered
    // rcContext* NavBuildData::ctx_ | File: ../Navigation/NavBuildData.h
    // rcContext* can not be registered
    // rcHeightfield* NavBuildData::heightField_ | File: ../Navigation/NavBuildData.h
    // rcHeightfield* can not be registered
    // PODVector<int> NavBuildData::indices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<int>" can not automatically bind
    // PODVector<NavAreaStub> NavBuildData::navAreas_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<NavAreaStub>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshAreas_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshDir_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // PODVector<unsigned short> NavBuildData::offMeshFlags_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned short>" can not automatically bind
    // PODVector<float> NavBuildData::offMeshRadii_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<float>" can not automatically bind
    // PODVector<Vector3> NavBuildData::offMeshVertices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<Vector3>" can not automatically bind
    // rcPolyMesh* SimpleNavBuildData::polyMesh_ | File: ../Navigation/NavBuildData.h
    // rcPolyMesh* can not be registered
    // rcPolyMeshDetail* SimpleNavBuildData::polyMeshDetail_ | File: ../Navigation/NavBuildData.h
    // rcPolyMeshDetail* can not be registered
    // PODVector<Vector3> NavBuildData::vertices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<Vector3>" can not automatically bind
    // BoundingBox NavBuildData::worldBoundingBox_ | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectProperty("SimpleNavBuildData", "BoundingBox worldBoundingBox", offsetof(SimpleNavBuildData, worldBoundingBox_));
    // SimpleNavBuildData& SimpleNavBuildData::operator=(const SimpleNavBuildData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SimpleNavBuildData>(engine, "SimpleNavBuildData");
#ifdef REGISTER_MANUAL_PART_NavBuildData
    REGISTER_MANUAL_PART_NavBuildData(SimpleNavBuildData, "SimpleNavBuildData")
#endif
#ifdef REGISTER_MANUAL_PART_SimpleNavBuildData
    REGISTER_MANUAL_PART_SimpleNavBuildData(SimpleNavBuildData, "SimpleNavBuildData")
#endif
#endif

}

}
