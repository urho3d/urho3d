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

// Skeleton::Skeleton() | File: ../Graphics/Skeleton.h
static Skeleton* Skeleton_Skeleton_void()
{
    return new Skeleton();
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
    engine->RegisterObjectMethod("Scene", "void AddChild(Node@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Scene, AddChild, (Node*, unsigned), void), asCALL_THISCALL);
    // void Node::AddComponent(Component* component, unsigned id, CreateMode mode) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddComponent(Component@+, uint, CreateMode)", asMETHODPR(Scene, AddComponent, (Component*, unsigned, CreateMode), void), asCALL_THISCALL);
    // void Node::AddListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddListener(Component@+)", asMETHODPR(Scene, AddListener, (Component*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_ADDREF, "void f()", asMETHODPR(Scene, AddRef, (), void), asCALL_THISCALL);
    // void Scene::AddReplicationState(NodeReplicationState* state) override | File: ../Scene/Scene.h
    // Error: type "NodeReplicationState*" can not automatically bind
    // void Scene::AddRequiredPackageFile(PackageFile* package) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void AddRequiredPackageFile(PackageFile@+)", asMETHODPR(Scene, AddRequiredPackageFile, (PackageFile*), void), asCALL_THISCALL);
    // void Node::AddTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTag(const String&in)", asMETHODPR(Scene, AddTag, (const String&), void), asCALL_THISCALL);
    // void Node::AddTags(const String& tags, char separator=';') | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Scene, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void AddTags(Array<String>@+)", asFUNCTION(Scene_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void AllocateNetworkState()", asMETHODPR(Scene, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Node::ApplyAttributes() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ApplyAttributes()", asMETHODPR(Scene, ApplyAttributes, (), void), asCALL_THISCALL);
    // void Scene::BeginThreadedUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void BeginThreadedUpdate()", asMETHODPR(Scene, BeginThreadedUpdate, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Scene::CleanupConnection(Connection* connection) | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // void Scene::Clear(bool clearReplicated=true, bool clearLocal=true) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void Clear(bool = true, bool = true)", asMETHODPR(Scene, Clear, (bool, bool), void), asCALL_THISCALL);
    // void Scene::ClearRequiredPackageFiles() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ClearRequiredPackageFiles()", asMETHODPR(Scene, ClearRequiredPackageFiles, (), void), asCALL_THISCALL);
    // Node* Node::Clone(CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ Clone(CreateMode = REPLICATED)", asMETHODPR(Scene, Clone, (CreateMode), Node*), asCALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CloneComponent(Component@+, uint = 0)", asMETHODPR(Scene, CloneComponent, (Component*, unsigned), Component*), asCALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, CreateMode mode, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CloneComponent(Component@+, CreateMode, uint = 0)", asMETHODPR(Scene, CloneComponent, (Component*, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // void Scene::ComponentAdded(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ComponentAdded(Component@+)", asMETHODPR(Scene, ComponentAdded, (Component*), void), asCALL_THISCALL);
    // void Scene::ComponentRemoved(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void ComponentRemoved(Component@+)", asMETHODPR(Scene, ComponentRemoved, (Component*), void), asCALL_THISCALL);
    // Node* Node::CreateChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0, bool = false)", asMETHODPR(Scene, CreateChild, (const String&, CreateMode, unsigned, bool), Node*), asCALL_THISCALL);
    // Node* Node::CreateChild(unsigned id, CreateMode mode, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateChild(uint, CreateMode, bool = false)", asMETHODPR(Scene, CreateChild, (unsigned, CreateMode, bool), Node*), asCALL_THISCALL);
    // Component* Node::CreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ CreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Scene, CreateComponent, (StringHash, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // template<class T> T*  Node::CreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Node* Node::CreateTemporaryChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ CreateTemporaryChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Scene, CreateTemporaryChild, (const String&, CreateMode, unsigned), Node*), asCALL_THISCALL);
    // void Scene::DelayedMarkedDirty(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void DelayedMarkedDirty(Component@+)", asMETHODPR(Scene, DelayedMarkedDirty, (Component*), void), asCALL_THISCALL);
    // void Scene::EndThreadedUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void EndThreadedUpdate()", asMETHODPR(Scene, EndThreadedUpdate, (), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "bool GetAnimationEnabled() const", asMETHODPR(Scene, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_animationEnabled() const", asMETHODPR(Scene, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // int Scene::GetAsyncLoadingMs() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "int GetAsyncLoadingMs() const", asMETHODPR(Scene, GetAsyncLoadingMs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_asyncLoadingMs() const", asMETHODPR(Scene, GetAsyncLoadingMs, () const, int), asCALL_THISCALL);
    // LoadMode Scene::GetAsyncLoadMode() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "LoadMode GetAsyncLoadMode() const", asMETHODPR(Scene, GetAsyncLoadMode, () const, LoadMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "LoadMode get_asyncLoadMode() const", asMETHODPR(Scene, GetAsyncLoadMode, () const, LoadMode), asCALL_THISCALL);
    // float Scene::GetAsyncProgress() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetAsyncProgress() const", asMETHODPR(Scene, GetAsyncProgress, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_asyncProgress() const", asMETHODPR(Scene, GetAsyncProgress, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttribute(uint) const", asMETHODPR(Scene, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Variant get_attributes(uint) const", asMETHODPR(Scene, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttribute(const String&in) const", asMETHODPR(Scene, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Scene, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Scene, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Scene, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Scene, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttributeDefault(uint) const", asMETHODPR(Scene, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Variant get_attributeDefaults(uint) const", asMETHODPR(Scene, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Scene, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool GetBlockEvents() const", asMETHODPR(Scene, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const String& GetCategory() const", asMETHODPR(Scene, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_category() const", asMETHODPR(Scene, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Scene::GetChecksum() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetChecksum() const", asMETHODPR(Scene, GetChecksum, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_checksum() const", asMETHODPR(Scene, GetChecksum, () const, unsigned), asCALL_THISCALL);
    // Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(uint) const", asMETHODPR(Scene, GetChild, (unsigned) const, Node*), asCALL_THISCALL);
    // Node* Node::GetChild(const String& name, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(const String&in, bool = false) const", asMETHODPR(Scene, GetChild, (const String&, bool) const, Node*), asCALL_THISCALL);
    // Node* Node::GetChild(const char* name, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "const char*" can not automatically bind
    // Node* Node::GetChild(StringHash nameHash, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetChild(StringHash, bool = false) const", asMETHODPR(Scene, GetChild, (StringHash, bool) const, Node*), asCALL_THISCALL);
    // const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildren() const", asFUNCTION(Scene_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void Node::GetChildren(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildren(bool) const", asFUNCTION(Scene_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void Node::GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildrenWithComponent(StringHash, bool = false) const", asFUNCTION(Scene_GetChildrenWithComponent_StringHash_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // void Node::GetChildrenWithTag(PODVector<Node*>& dest, const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Scene_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // Component* Scene::GetComponent(unsigned id) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetComponent(uint) const", asMETHODPR(Scene, GetComponent, (unsigned) const, Component*), asCALL_THISCALL);
    // Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // template<class T> T*  Node::GetComponent(bool recursive=false) const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Component@>@ GetComponents() const", asFUNCTION(Scene_GetComponents_void), asCALL_CDECL_OBJFIRST);
    // void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetDependencyNodes() const", asFUNCTION(Scene_GetDependencyNodes_void), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  Node::GetDerivedComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive=false, bool clearVector=true) const | File: ../Scene/Node.h
    // Not registered because template
    // Vector3 Node::GetDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetDirection() const", asMETHODPR(Scene, GetDirection, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_direction() const", asMETHODPR(Scene, GetDirection, () const, Vector3), asCALL_THISCALL);
    // float Scene::GetElapsedTime() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetElapsedTime() const", asMETHODPR(Scene, GetElapsedTime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_elapsedTime() const", asMETHODPR(Scene, GetElapsedTime, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "VariantMap& GetEventDataMap() const", asMETHODPR(Scene, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "Object@+ GetEventSender() const", asMETHODPR(Scene, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const String& Scene::GetFileName() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "const String& GetFileName() const", asMETHODPR(Scene, GetFileName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_fileName() const", asMETHODPR(Scene, GetFileName, () const, const String&), asCALL_THISCALL);
    // unsigned Scene::GetFreeComponentID(CreateMode mode) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetFreeComponentID(CreateMode)", asMETHODPR(Scene, GetFreeComponentID, (CreateMode), unsigned), asCALL_THISCALL);
    // unsigned Scene::GetFreeNodeID(CreateMode mode) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "uint GetFreeNodeID(CreateMode)", asMETHODPR(Scene, GetFreeNodeID, (CreateMode), unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Scene, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Scene, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const VariantMap& GetGlobalVars() const", asMETHODPR(Scene, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const VariantMap& get_globalVars() const", asMETHODPR(Scene, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Node::GetID() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetID() const", asMETHODPR(Scene, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_id() const", asMETHODPR(Scene, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Scene, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const Vector<WeakPtr<Component>> Node::GetListeners() const | File: ../Scene/Node.h
    // Error: type "const Vector<WeakPtr<Component>>" can not automatically bind
    // const String& Node::GetName() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const String& GetName() const", asMETHODPR(Scene, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_name() const", asMETHODPR(Scene, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Node::GetNameHash() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "StringHash GetNameHash() const", asMETHODPR(Scene, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetParentAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector3& Node::GetNetPositionAttr() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetNetPositionAttr() const", asMETHODPR(Scene, GetNetPositionAttr, () const, const Vector3&), asCALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetRotationAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Scene::GetNode(unsigned id) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetNode(uint) const", asMETHODPR(Scene, GetNode, (unsigned) const, Node*), asCALL_THISCALL);
    // bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const | File: ../Scene/Scene.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "uint GetNumAttributes() const", asMETHODPR(Scene, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_numAttributes() const", asMETHODPR(Scene, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumChildren(bool = false) const", asMETHODPR(Scene, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumComponents() const", asMETHODPR(Scene, GetNumComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_numComponents() const", asMETHODPR(Scene, GetNumComponents, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "uint GetNumNetworkAttributes() const", asMETHODPR(Scene, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumNetworkComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumNetworkComponents() const", asMETHODPR(Scene, GetNumNetworkComponents, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumPersistentChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumPersistentChildren() const", asMETHODPR(Scene, GetNumPersistentChildren, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumPersistentComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "uint GetNumPersistentComponents() const", asMETHODPR(Scene, GetNumPersistentComponents, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Scene, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Scene, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Scene, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Component* Node::GetOrCreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetOrCreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Scene, GetOrCreateComponent, (StringHash, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // template<class T> T*  Node::GetOrCreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Connection* Node::GetOwner() const | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::GetParent() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Node@+ GetParent() const", asMETHODPR(Scene, GetParent, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ get_parent() const", asMETHODPR(Scene, GetParent, () const, Node*), asCALL_THISCALL);
    // Component* Node::GetParentComponent(StringHash type, bool fullTraversal=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Component@+ GetParentComponent(StringHash, bool = false) const", asMETHODPR(Scene, GetParentComponent, (StringHash, bool) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Node::GetParentComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> T*  Node::GetParentDerivedComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector3& Node::GetPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetPosition() const", asMETHODPR(Scene, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Vector3& get_position() const", asMETHODPR(Scene, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    // Vector2 Node::GetPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetPosition2D() const", asMETHODPR(Scene, GetPosition2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_position2D() const", asMETHODPR(Scene, GetPosition2D, () const, Vector2), asCALL_THISCALL);
    // const Vector<SharedPtr<PackageFile>>& Scene::GetRequiredPackageFiles() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ GetRequiredPackageFiles() const", asFUNCTION(Scene_GetRequiredPackageFiles_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ get_requiredPackageFiles() const", asFUNCTION(Scene_GetRequiredPackageFiles_void), asCALL_CDECL_OBJFIRST);
    // Vector3 Node::GetRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetRight() const", asMETHODPR(Scene, GetRight, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_right() const", asMETHODPR(Scene, GetRight, () const, Vector3), asCALL_THISCALL);
    // const Quaternion& Node::GetRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Quaternion& GetRotation() const", asMETHODPR(Scene, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Quaternion& get_rotation() const", asMETHODPR(Scene, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // float Node::GetRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "float GetRotation2D() const", asMETHODPR(Scene, GetRotation2D, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_rotation2D() const", asMETHODPR(Scene, GetRotation2D, () const, float), asCALL_THISCALL);
    // const Vector3& Node::GetScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Vector3& GetScale() const", asMETHODPR(Scene, GetScale, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Vector3& get_scale() const", asMETHODPR(Scene, GetScale, () const, const Vector3&), asCALL_THISCALL);
    // Vector2 Node::GetScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetScale2D() const", asMETHODPR(Scene, GetScale2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_scale2D() const", asMETHODPR(Scene, GetScale2D, () const, Vector2), asCALL_THISCALL);
    // Scene* Node::GetScene() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Scene@+ GetScene() const", asMETHODPR(Scene, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Scene@+ get_scene() const", asMETHODPR(Scene, GetScene, () const, Scene*), asCALL_THISCALL);
    // Vector3 Node::GetSignedWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetSignedWorldScale() const", asMETHODPR(Scene, GetSignedWorldScale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_signedWorldScale() const", asMETHODPR(Scene, GetSignedWorldScale, () const, Vector3), asCALL_THISCALL);
    // float Scene::GetSmoothingConstant() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetSmoothingConstant() const", asMETHODPR(Scene, GetSmoothingConstant, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_smoothingConstant() const", asMETHODPR(Scene, GetSmoothingConstant, () const, float), asCALL_THISCALL);
    // float Scene::GetSnapThreshold() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetSnapThreshold() const", asMETHODPR(Scene, GetSnapThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_snapThreshold() const", asMETHODPR(Scene, GetSnapThreshold, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Scene, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& Node::GetTags() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Array<String>@ GetTags() const", asFUNCTION(Scene_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Scene", "Array<String>@ get_tags() const", asFUNCTION(Scene_GetTags_void), asCALL_CDECL_OBJFIRST);
    // float Scene::GetTimeScale() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "float GetTimeScale() const", asMETHODPR(Scene, GetTimeScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_timeScale() const", asMETHODPR(Scene, GetTimeScale, () const, float), asCALL_THISCALL);
    // Matrix3x4 Node::GetTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Matrix3x4 GetTransform() const", asMETHODPR(Scene, GetTransform, () const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Matrix3x4 get_transform() const", asMETHODPR(Scene, GetTransform, () const, Matrix3x4), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "StringHash GetType() const", asMETHODPR(Scene, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "StringHash get_type() const", asMETHODPR(Scene, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "const String& GetTypeName() const", asMETHODPR(Scene, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_typeName() const", asMETHODPR(Scene, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Vector3 Node::GetUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetUp() const", asMETHODPR(Scene, GetUp, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_up() const", asMETHODPR(Scene, GetUp, () const, Vector3), asCALL_THISCALL);
    // const Variant& Node::GetVar(StringHash key) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Variant& GetVar(StringHash) const", asMETHODPR(Scene, GetVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const String& Scene::GetVarName(StringHash hash) const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "const String& GetVarName(StringHash) const", asMETHODPR(Scene, GetVarName, (StringHash) const, const String&), asCALL_THISCALL);
    // String Scene::GetVarNamesAttr() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "String GetVarNamesAttr() const", asMETHODPR(Scene, GetVarNamesAttr, () const, String), asCALL_THISCALL);
    // const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const VariantMap& GetVars() const", asMETHODPR(Scene, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // Vector3 Node::GetWorldDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldDirection() const", asMETHODPR(Scene, GetWorldDirection, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldDirection() const", asMETHODPR(Scene, GetWorldDirection, () const, Vector3), asCALL_THISCALL);
    // Vector3 Node::GetWorldPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldPosition() const", asMETHODPR(Scene, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldPosition() const", asMETHODPR(Scene, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    // Vector2 Node::GetWorldPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetWorldPosition2D() const", asMETHODPR(Scene, GetWorldPosition2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_worldPosition2D() const", asMETHODPR(Scene, GetWorldPosition2D, () const, Vector2), asCALL_THISCALL);
    // Vector3 Node::GetWorldRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldRight() const", asMETHODPR(Scene, GetWorldRight, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldRight() const", asMETHODPR(Scene, GetWorldRight, () const, Vector3), asCALL_THISCALL);
    // Quaternion Node::GetWorldRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Quaternion GetWorldRotation() const", asMETHODPR(Scene, GetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Quaternion get_worldRotation() const", asMETHODPR(Scene, GetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    // float Node::GetWorldRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "float GetWorldRotation2D() const", asMETHODPR(Scene, GetWorldRotation2D, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_worldRotation2D() const", asMETHODPR(Scene, GetWorldRotation2D, () const, float), asCALL_THISCALL);
    // Vector3 Node::GetWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldScale() const", asMETHODPR(Scene, GetWorldScale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldScale() const", asMETHODPR(Scene, GetWorldScale, () const, Vector3), asCALL_THISCALL);
    // Vector2 Node::GetWorldScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 GetWorldScale2D() const", asMETHODPR(Scene, GetWorldScale2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector2 get_worldScale2D() const", asMETHODPR(Scene, GetWorldScale2D, () const, Vector2), asCALL_THISCALL);
    // const Matrix3x4& Node::GetWorldTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "const Matrix3x4& GetWorldTransform() const", asMETHODPR(Scene, GetWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const Matrix3x4& get_worldTransform() const", asMETHODPR(Scene, GetWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    // Vector3 Node::GetWorldUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 GetWorldUp() const", asMETHODPR(Scene, GetWorldUp, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Vector3 get_worldUp() const", asMETHODPR(Scene, GetWorldUp, () const, Vector3), asCALL_THISCALL);
    // bool Node::HasComponent(StringHash type) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool HasComponent(StringHash) const", asMETHODPR(Scene, HasComponent, (StringHash) const, bool), asCALL_THISCALL);
    // template<class T> bool Node::HasComponent() const | File: ../Scene/Node.h
    // Not registered because template
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasEventHandlers() const", asMETHODPR(Scene, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Scene, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Scene, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Node::HasTag(const String& tag) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool HasTag(const String&in) const", asMETHODPR(Scene, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ Instantiate(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", asMETHODPR(Scene, Instantiate, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    // Node* Scene::InstantiateJSON(const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(const JSONValue&in, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", asMETHODPR(Scene, InstantiateJSON, (const JSONValue&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    // Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", asMETHODPR(Scene, InstantiateJSON, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    // Node* Scene::InstantiateXML(const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(const XMLElement&in, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", asMETHODPR(Scene, InstantiateXML, (const XMLElement&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    // Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(Deserializer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", asMETHODPR(Scene, InstantiateXML, (Deserializer&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    // bool Scene::IsAsyncLoading() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsAsyncLoading() const", asMETHODPR(Scene, IsAsyncLoading, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_asyncLoading() const", asMETHODPR(Scene, IsAsyncLoading, () const, bool), asCALL_THISCALL);
    // bool Node::IsChildOf(Node* node) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsChildOf(Node@+) const", asMETHODPR(Scene, IsChildOf, (Node*) const, bool), asCALL_THISCALL);
    // bool Node::IsDirty() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsDirty() const", asMETHODPR(Scene, IsDirty, () const, bool), asCALL_THISCALL);
    // bool Node::IsEnabled() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsEnabled() const", asMETHODPR(Scene, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_enabled() const", asMETHODPR(Scene, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Node::IsEnabledSelf() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsEnabledSelf() const", asMETHODPR(Scene, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_enabledSelf() const", asMETHODPR(Scene, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "bool IsInstanceOf(StringHash) const", asMETHODPR(Scene, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Node::IsReplicated() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool IsReplicated() const", asMETHODPR(Scene, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_replicated() const", asMETHODPR(Scene, IsReplicated, () const, bool), asCALL_THISCALL);
    // static bool Scene::IsReplicatedID(unsigned id) | File: ../Scene/Scene.h
    engine->SetDefaultNamespace("Scene");
    engine->RegisterGlobalFunction("bool IsReplicatedID(uint)", asFUNCTIONPR(Scene::IsReplicatedID, (unsigned), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool IsTemporary() const", asMETHODPR(Scene, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_temporary() const", asMETHODPR(Scene, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Scene::IsThreadedUpdate() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsThreadedUpdate() const", asMETHODPR(Scene, IsThreadedUpdate, () const, bool), asCALL_THISCALL);
    // bool Scene::IsUpdateEnabled() const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool IsUpdateEnabled() const", asMETHODPR(Scene, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_updateEnabled() const", asMETHODPR(Scene, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    // bool Scene::Load(Deserializer& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool Load(Deserializer&)", asMETHODPR(Scene, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Scene::LoadAsync(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsync(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", asMETHODPR(Scene, LoadAsync, (File*, LoadMode), bool), asCALL_THISCALL);
    // bool Scene::LoadAsyncJSON(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncJSON(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", asMETHODPR(Scene, LoadAsyncJSON, (File*, LoadMode), bool), asCALL_THISCALL);
    // bool Scene::LoadAsyncXML(File* file, LoadMode mode=LOAD_SCENE_AND_RESOURCES) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncXML(File@+, LoadMode = LOAD_SCENE_AND_RESOURCES)", asMETHODPR(Scene, LoadAsyncXML, (File*, LoadMode), bool), asCALL_THISCALL);
    // bool Scene::LoadJSON(const JSONValue& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Scene, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Scene::LoadJSON(Deserializer& source) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(Deserializer&)", asMETHODPR(Scene, LoadJSON, (Deserializer&), bool), asCALL_THISCALL);
    // bool Scene::LoadXML(const XMLElement& source) override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadXML(const XMLElement&in)", asMETHODPR(Scene, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // bool Scene::LoadXML(Deserializer& source) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool LoadXML(Deserializer&)", asMETHODPR(Scene, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 LocalToWorld(const Vector3&in) const", asMETHODPR(Scene, LocalToWorld, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 LocalToWorld(const Vector4&in) const", asMETHODPR(Scene, LocalToWorld, (const Vector4&) const, Vector3), asCALL_THISCALL);
    // Vector2 Node::LocalToWorld2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 LocalToWorld2D(const Vector2&in) const", asMETHODPR(Scene, LocalToWorld2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // bool Node::LookAt(const Vector3& target, const Vector3& up=Vector3::UP, TransformSpace space=TS_WORLD) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool LookAt(const Vector3&in, const Vector3&in = Vector3::UP, TransformSpace = TS_WORLD)", asMETHODPR(Scene, LookAt, (const Vector3&, const Vector3&, TransformSpace), bool), asCALL_THISCALL);
    // void Node::MarkDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void MarkDirty()", asMETHODPR(Scene, MarkDirty, (), void), asCALL_THISCALL);
    // void Scene::MarkNetworkUpdate() override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate()", asMETHODPR(Scene, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void Scene::MarkNetworkUpdate(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate(Node@+)", asMETHODPR(Scene, MarkNetworkUpdate, (Node*), void), asCALL_THISCALL);
    // void Scene::MarkNetworkUpdate(Component* component) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkNetworkUpdate(Component@+)", asMETHODPR(Scene, MarkNetworkUpdate, (Component*), void), asCALL_THISCALL);
    // void Scene::MarkReplicationDirty(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void MarkReplicationDirty(Node@+)", asMETHODPR(Scene, MarkReplicationDirty, (Node*), void), asCALL_THISCALL);
    // void Scene::NodeAdded(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeAdded(Node@+)", asMETHODPR(Scene, NodeAdded, (Node*), void), asCALL_THISCALL);
    // void Scene::NodeRemoved(Node* node) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeRemoved(Node@+)", asMETHODPR(Scene, NodeRemoved, (Node*), void), asCALL_THISCALL);
    // void Scene::NodeTagAdded(Node* node, const String& tag) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeTagAdded(Node@+, const String&in)", asMETHODPR(Scene, NodeTagAdded, (Node*, const String&), void), asCALL_THISCALL);
    // void Scene::NodeTagRemoved(Node* node, const String& tag) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void NodeTagRemoved(Node@+, const String&in)", asMETHODPR(Scene, NodeTagRemoved, (Node*, const String&), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Scene, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Scene, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Scene, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Node::Pitch(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Pitch(float, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Pitch, (float, TransformSpace), void), asCALL_THISCALL);
    // void Scene::PrepareNetworkUpdate() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void PrepareNetworkUpdate()", asMETHODPR(Scene, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Scene, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Scene, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Scene", "int Refs() const", asMETHODPR(Scene, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_refs() const", asMETHODPR(Scene, Refs, () const, int), asCALL_THISCALL);
    // static void Scene::RegisterObject(Context* context) | File: ../Scene/Scene.h
    // Not registered because have @nobind mark
    // void Scene::RegisterVar(const String& name) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void RegisterVar(const String&in)", asMETHODPR(Scene, RegisterVar, (const String&), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_RELEASE, "void f()", asMETHODPR(Scene, ReleaseRef, (), void), asCALL_THISCALL);
    // void Node::Remove() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Remove()", asMETHODPR(Scene, Remove, (), void), asCALL_THISCALL);
    // void Node::RemoveAllChildren() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllChildren()", asMETHODPR(Scene, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void Node::RemoveAllComponents() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllComponents()", asMETHODPR(Scene, RemoveAllComponents, (), void), asCALL_THISCALL);
    // void Node::RemoveAllTags() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveAllTags()", asMETHODPR(Scene, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Scene, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Node::RemoveChild(Node* node) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveChild(Node@+)", asMETHODPR(Scene, RemoveChild, (Node*), void), asCALL_THISCALL);
    // void Node::RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveChildren(bool, bool, bool)", asMETHODPR(Scene, RemoveChildren, (bool, bool, bool), void), asCALL_THISCALL);
    // void Node::RemoveComponent(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponent(Component@+)", asMETHODPR(Scene, RemoveComponent, (Component*), void), asCALL_THISCALL);
    // void Node::RemoveComponent(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponent(StringHash)", asMETHODPR(Scene, RemoveComponent, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Node::RemoveComponent() | File: ../Scene/Node.h
    // Not registered because template
    // void Node::RemoveComponents(bool removeReplicated, bool removeLocal) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponents(bool, bool)", asMETHODPR(Scene, RemoveComponents, (bool, bool), void), asCALL_THISCALL);
    // void Node::RemoveComponents(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveComponents(StringHash)", asMETHODPR(Scene, RemoveComponents, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Node::RemoveComponents() | File: ../Scene/Node.h
    // Not registered because template
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void RemoveInstanceDefault()", asMETHODPR(Scene, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Node::RemoveListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RemoveListener(Component@+)", asMETHODPR(Scene, RemoveListener, (Component*), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void RemoveObjectAnimation()", asMETHODPR(Scene, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool Node::RemoveTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool RemoveTag(const String&in)", asMETHODPR(Scene, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void Node::ReorderComponent(Component* component, unsigned index) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ReorderComponent(Component@+, uint)", asMETHODPR(Scene, ReorderComponent, (Component*, unsigned), void), asCALL_THISCALL);
    // void Node::ResetDeepEnabled() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ResetDeepEnabled()", asMETHODPR(Scene, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Node::ResetScene() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void ResetScene()", asMETHODPR(Scene, ResetScene, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void ResetToDefault()", asMETHODPR(Scene, ResetToDefault, (), void), asCALL_THISCALL);
    // void Node::Roll(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Roll(float, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Roll, (float, TransformSpace), void), asCALL_THISCALL);
    // void Node::Rotate(const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Rotate(const Quaternion&in, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Rotate, (const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    // void Node::Rotate2D(float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Rotate2D(float, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Rotate2D, (float, TransformSpace), void), asCALL_THISCALL);
    // void Node::RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RotateAround(const Vector3&in, const Quaternion&in, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, RotateAround, (const Vector3&, const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    // void Node::RotateAround2D(const Vector2& point, float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void RotateAround2D(const Vector2&in, float, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, RotateAround2D, (const Vector2&, float, TransformSpace), void), asCALL_THISCALL);
    // bool Scene::Save(Serializer& dest) const override | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool Save(Serializer&) const", asMETHODPR(Scene, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool Node::SaveDefaultAttributes() const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "bool SaveDefaultAttributes() const", asMETHODPR(Scene, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Scene::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool SaveJSON(Serializer&, const String&in = \"\t\") const", asMETHODPR(Scene, SaveJSON, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // bool Node::SaveJSON(JSONValue& dest) const override | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Node::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Scene::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Scene, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // bool Node::SaveXML(XMLElement& dest) const override | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // bool Node::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Scene.h
    // Not registered because have @manualbind mark
    // void Node::Scale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale(float)", asMETHODPR(Scene, Scale, (float), void), asCALL_THISCALL);
    // void Node::Scale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale(const Vector3&in)", asMETHODPR(Scene, Scale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::Scale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Scale2D(const Vector2&in)", asMETHODPR(Scene, Scale2D, (const Vector2&), void), asCALL_THISCALL);
    // explicit Scene::Scene(Context* context) | File: ../Scene/Scene.h
    engine->RegisterObjectBehaviour("Scene", asBEHAVE_FACTORY, "Scene@+ f()", asFUNCTION(Scene_Scene_Context), asCALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SendEvent(StringHash)", asMETHODPR(Scene, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Scene, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAnimationEnabled(bool)", asMETHODPR(Scene, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_animationEnabled(bool)", asMETHODPR(Scene, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAnimationTime(float)", asMETHODPR(Scene, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Scene::SetAsyncLoadingMs(int ms) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetAsyncLoadingMs(int)", asMETHODPR(Scene, SetAsyncLoadingMs, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_asyncLoadingMs(int)", asMETHODPR(Scene, SetAsyncLoadingMs, (int), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Scene, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Scene, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Scene, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Scene, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Scene, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Scene, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Scene, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SetBlockEvents(bool)", asMETHODPR(Scene, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Node::SetDeepEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetDeepEnabled(bool)", asMETHODPR(Scene, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void Node::SetDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetDirection(const Vector3&in)", asMETHODPR(Scene, SetDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_direction(const Vector3&in)", asMETHODPR(Scene, SetDirection, (const Vector3&), void), asCALL_THISCALL);
    // void Scene::SetElapsedTime(float time) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetElapsedTime(float)", asMETHODPR(Scene, SetElapsedTime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_elapsedTime(float)", asMETHODPR(Scene, SetElapsedTime, (float), void), asCALL_THISCALL);
    // void Node::SetEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetEnabled(bool)", asMETHODPR(Scene, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_enabled(bool)", asMETHODPR(Scene, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Node::SetEnabledRecursive(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetEnabledRecursive(bool)", asMETHODPR(Scene, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Scene, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Scene, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Node::SetID(unsigned id) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetID(uint)", asMETHODPR(Scene, SetID, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_id(uint)", asMETHODPR(Scene, SetID, (unsigned), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetInstanceDefault(bool)", asMETHODPR(Scene, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Scene, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Node::SetName(const String& name) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetName(const String&in)", asMETHODPR(Scene, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_name(const String&in)", asMETHODPR(Scene, SetName, (const String&), void), asCALL_THISCALL);
    // void Node::SetNetParentAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetNetPositionAttr(const Vector3& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetNetPositionAttr(const Vector3&in)", asMETHODPR(Scene, SetNetPositionAttr, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetNetRotationAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Scene, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Scene, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Scene", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Scene, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // void Node::SetParent(Node* parent) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetParent(Node@+)", asMETHODPR(Scene, SetParent, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_parent(Node@+)", asMETHODPR(Scene, SetParent, (Node*), void), asCALL_THISCALL);
    // void Node::SetPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition(const Vector3&in)", asMETHODPR(Scene, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_position(const Vector3&in)", asMETHODPR(Scene, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition2D(const Vector2&in)", asMETHODPR(Scene, SetPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_position2D(const Vector2&in)", asMETHODPR(Scene, SetPosition2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPosition2D(float, float)", asMETHODPR(Scene, SetPosition2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetPositionSilent(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetPositionSilent(const Vector3&in)", asMETHODPR(Scene, SetPositionSilent, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotation(const Quaternion&in)", asMETHODPR(Scene, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_rotation(const Quaternion&in)", asMETHODPR(Scene, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotation2D(float)", asMETHODPR(Scene, SetRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_rotation2D(float)", asMETHODPR(Scene, SetRotation2D, (float), void), asCALL_THISCALL);
    // void Node::SetRotationSilent(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetRotationSilent(const Quaternion&in)", asMETHODPR(Scene, SetRotationSilent, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale(float)", asMETHODPR(Scene, SetScale, (float), void), asCALL_THISCALL);
    // void Node::SetScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale(const Vector3&in)", asMETHODPR(Scene, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_scale(const Vector3&in)", asMETHODPR(Scene, SetScale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale2D(const Vector2&in)", asMETHODPR(Scene, SetScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_scale2D(const Vector2&in)", asMETHODPR(Scene, SetScale2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScale2D(float, float)", asMETHODPR(Scene, SetScale2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetScaleSilent(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScaleSilent(const Vector3&in)", asMETHODPR(Scene, SetScaleSilent, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetScene(Scene* scene) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetScene(Scene@+)", asMETHODPR(Scene, SetScene, (Scene*), void), asCALL_THISCALL);
    // void Scene::SetSmoothingConstant(float constant) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetSmoothingConstant(float)", asMETHODPR(Scene, SetSmoothingConstant, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_smoothingConstant(float)", asMETHODPR(Scene, SetSmoothingConstant, (float), void), asCALL_THISCALL);
    // void Scene::SetSnapThreshold(float threshold) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetSnapThreshold(float)", asMETHODPR(Scene, SetSnapThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_snapThreshold(float)", asMETHODPR(Scene, SetSnapThreshold, (float), void), asCALL_THISCALL);
    // void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTags(Array<String>@+)", asFUNCTION(Scene_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void SetTemporary(bool)", asMETHODPR(Scene, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_temporary(bool)", asMETHODPR(Scene, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Scene::SetTimeScale(float scale) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetTimeScale(float)", asMETHODPR(Scene, SetTimeScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_timeScale(float)", asMETHODPR(Scene, SetTimeScale, (float), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Scene, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Node::SetTransform(const Matrix3x4& matrix) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform(const Matrix3x4&in)", asMETHODPR(Scene, SetTransform, (const Matrix3x4&), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float)", asMETHODPR(Scene, SetTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float, float)", asMETHODPR(Scene, SetTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(Scene, SetTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    // void Node::SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetTransformSilent(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Scene, SetTransformSilent, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Scene::SetUpdateEnabled(bool enable) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetUpdateEnabled(bool)", asMETHODPR(Scene, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_updateEnabled(bool)", asMETHODPR(Scene, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    // void Node::SetVar(StringHash key, const Variant& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Scene, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Scene::SetVarNamesAttr(const String& value) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void SetVarNamesAttr(const String&in)", asMETHODPR(Scene, SetVarNamesAttr, (const String&), void), asCALL_THISCALL);
    // void Node::SetWorldDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldDirection(const Vector3&in)", asMETHODPR(Scene, SetWorldDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldDirection(const Vector3&in)", asMETHODPR(Scene, SetWorldDirection, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition(const Vector3&in)", asMETHODPR(Scene, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldPosition(const Vector3&in)", asMETHODPR(Scene, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition2D(const Vector2&in)", asMETHODPR(Scene, SetWorldPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldPosition2D(const Vector2&in)", asMETHODPR(Scene, SetWorldPosition2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldPosition2D(float, float)", asMETHODPR(Scene, SetWorldPosition2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetWorldRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldRotation(const Quaternion&in)", asMETHODPR(Scene, SetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldRotation(const Quaternion&in)", asMETHODPR(Scene, SetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetWorldRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldRotation2D(float)", asMETHODPR(Scene, SetWorldRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldRotation2D(float)", asMETHODPR(Scene, SetWorldRotation2D, (float), void), asCALL_THISCALL);
    // void Node::SetWorldScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale(float)", asMETHODPR(Scene, SetWorldScale, (float), void), asCALL_THISCALL);
    // void Node::SetWorldScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale(const Vector3&in)", asMETHODPR(Scene, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldScale(const Vector3&in)", asMETHODPR(Scene, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale2D(const Vector2&in)", asMETHODPR(Scene, SetWorldScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_worldScale2D(const Vector2&in)", asMETHODPR(Scene, SetWorldScale2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetWorldScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldScale2D(float, float)", asMETHODPR(Scene, SetWorldScale2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Scene, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Matrix3x4& worldTransform) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform(const Matrix3x4&in)", asMETHODPR(Scene, SetWorldTransform, (const Matrix3x4&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float)", asMETHODPR(Scene, SetWorldTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float, float)", asMETHODPR(Scene, SetWorldTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void SetWorldTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(Scene, SetWorldTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    // void Scene::StopAsyncLoading() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void StopAsyncLoading()", asMETHODPR(Scene, StopAsyncLoading, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Node::Translate(const Vector3& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Translate(const Vector3&in, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Translate, (const Vector3&, TransformSpace), void), asCALL_THISCALL);
    // void Node::Translate2D(const Vector2& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Translate2D(const Vector2&in, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Translate2D, (const Vector2&, TransformSpace), void), asCALL_THISCALL);
    // void Scene::UnregisterAllVars() | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void UnregisterAllVars()", asMETHODPR(Scene, UnregisterAllVars, (), void), asCALL_THISCALL);
    // void Scene::UnregisterVar(const String& name) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void UnregisterVar(const String&in)", asMETHODPR(Scene, UnregisterVar, (const String&), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromAllEvents()", asMETHODPR(Scene, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Scene_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Scene, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Scene, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Scene", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Scene, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Scene::Update(float timeStep) | File: ../Scene/Scene.h
    engine->RegisterObjectMethod("Scene", "void Update(float)", asMETHODPR(Scene, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Scene", "int WeakRefs() const", asMETHODPR(Scene, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_weakRefs() const", asMETHODPR(Scene, WeakRefs, () const, int), asCALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 WorldToLocal(const Vector3&in) const", asMETHODPR(Scene, WorldToLocal, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector3 WorldToLocal(const Vector4&in) const", asMETHODPR(Scene, WorldToLocal, (const Vector4&) const, Vector3), asCALL_THISCALL);
    // Vector2 Node::WorldToLocal2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "Vector2 WorldToLocal2D(const Vector2&in) const", asMETHODPR(Scene, WorldToLocal2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Scene, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Scene, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Scene", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Scene, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Node::Yaw(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "void Yaw(float, TransformSpace = TS_LOCAL)", asMETHODPR(Scene, Yaw, (float, TransformSpace), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("SceneResolver", "void AddComponent(uint, Component@+)", asMETHODPR(SceneResolver, AddComponent, (unsigned, Component*), void), asCALL_THISCALL);
    // void SceneResolver::AddNode(unsigned oldID, Node* node) | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void AddNode(uint, Node@+)", asMETHODPR(SceneResolver, AddNode, (unsigned, Node*), void), asCALL_THISCALL);
    // void SceneResolver::Reset() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void Reset()", asMETHODPR(SceneResolver, Reset, (), void), asCALL_THISCALL);
    // void SceneResolver::Resolve() | File: ../Scene/SceneResolver.h
    engine->RegisterObjectMethod("SceneResolver", "void Resolve()", asMETHODPR(SceneResolver, Resolve, (), void), asCALL_THISCALL);
    // SceneResolver& SceneResolver::operator=(const SceneResolver&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SceneResolver>(engine, "SceneResolver");
#ifdef REGISTER_MANUAL_PART_SceneResolver
    REGISTER_MANUAL_PART_SceneResolver(SceneResolver, "SceneResolver")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddChild(UIElement@+)", asMETHODPR(ScrollBar, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_ADDREF, "void f()", asMETHODPR(ScrollBar, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTag(const String&in)", asMETHODPR(ScrollBar, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTags(const String&in, int8 = ';')", asMETHODPR(ScrollBar, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AddTags(Array<String>@+)", asFUNCTION(ScrollBar_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void AdjustScissor(IntRect&)", asMETHODPR(ScrollBar, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void AllocateNetworkState()", asMETHODPR(ScrollBar, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void ScrollBar::ApplyAttributes() override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void ApplyAttributes()", asMETHODPR(ScrollBar, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void BringToFront()", asMETHODPR(ScrollBar, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ScrollBar::ChangeValue(float delta) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void ChangeValue(float)", asMETHODPR(ScrollBar, ChangeValue, (float), void), asCALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(ScrollBar, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void DisableLayoutUpdate()", asMETHODPR(ScrollBar, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(ScrollBar, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void EnableLayoutUpdate()", asMETHODPR(ScrollBar, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool FilterAttributes(XMLElement&) const", asMETHODPR(ScrollBar, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint FindChild(UIElement@+) const", asMETHODPR(ScrollBar, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetAnimationEnabled() const", asMETHODPR(ScrollBar, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_animationEnabled() const", asMETHODPR(ScrollBar, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetAppliedStyle() const", asMETHODPR(ScrollBar, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_style() const", asMETHODPR(ScrollBar, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttribute(uint) const", asMETHODPR(ScrollBar, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Variant get_attributes(uint) const", asMETHODPR(ScrollBar, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttribute(const String&in) const", asMETHODPR(ScrollBar, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ScrollBar, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ScrollBar, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ScrollBar, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ScrollBar, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttributeDefault(uint) const", asMETHODPR(ScrollBar, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Variant get_attributeDefaults(uint) const", asMETHODPR(ScrollBar, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ScrollBar, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // Button* ScrollBar::GetBackButton() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Button@+ GetBackButton() const", asMETHODPR(ScrollBar, GetBackButton, () const, Button*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_backButton() const", asMETHODPR(ScrollBar, GetBackButton, () const, Button*), asCALL_THISCALL);
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "BlendMode GetBlendMode() const", asMETHODPR(ScrollBar, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "BlendMode get_blendMode() const", asMETHODPR(ScrollBar, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBlockEvents() const", asMETHODPR(ScrollBar, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetBorder() const", asMETHODPR(ScrollBar, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_border() const", asMETHODPR(ScrollBar, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBringToBack() const", asMETHODPR(ScrollBar, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_bringToBack() const", asMETHODPR(ScrollBar, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetBringToFront() const", asMETHODPR(ScrollBar, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_bringToFront() const", asMETHODPR(ScrollBar, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetCategory() const", asMETHODPR(ScrollBar, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_category() const", asMETHODPR(ScrollBar, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(uint) const", asMETHODPR(ScrollBar, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_children(uint) const", asMETHODPR(ScrollBar, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(ScrollBar, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(ScrollBar, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetChildOffset() const", asMETHODPR(ScrollBar, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_childOffset() const", asMETHODPR(ScrollBar, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildren() const", asFUNCTION(ScrollBar_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(ScrollBar_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(ScrollBar_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetClipBorder() const", asMETHODPR(ScrollBar, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_clipBorder() const", asMETHODPR(ScrollBar, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetClipChildren() const", asMETHODPR(ScrollBar, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_clipChildren() const", asMETHODPR(ScrollBar, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetColor(Corner) const", asMETHODPR(ScrollBar, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Color& get_colors(Corner) const", asMETHODPR(ScrollBar, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetColorAttr() const", asMETHODPR(ScrollBar, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntRect GetCombinedScreenRect()", asMETHODPR(ScrollBar, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "IntRect get_combinedScreenRect()", asMETHODPR(ScrollBar, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(ScrollBar, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Color& GetDerivedColor() const", asMETHODPR(ScrollBar, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "float GetDerivedOpacity() const", asMETHODPR(ScrollBar, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_derivedOpacity() const", asMETHODPR(ScrollBar, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetDisabledOffset() const", asMETHODPR(ScrollBar, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_disabledOffset() const", asMETHODPR(ScrollBar, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(ScrollBar, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(ScrollBar, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetDragButtonCount() const", asMETHODPR(ScrollBar, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_dragButtonCount() const", asMETHODPR(ScrollBar, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(ScrollBar, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(ScrollBar, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(ScrollBar, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // float ScrollBar::GetEffectiveScrollStep() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetEffectiveScrollStep() const", asMETHODPR(ScrollBar, GetEffectiveScrollStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_effectiveScrollStep() const", asMETHODPR(ScrollBar, GetEffectiveScrollStep, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetElementEventSender() const", asMETHODPR(ScrollBar, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetEnableAnchor() const", asMETHODPR(ScrollBar, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enableAnchor() const", asMETHODPR(ScrollBar, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "VariantMap& GetEventDataMap() const", asMETHODPR(ScrollBar, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "Object@+ GetEventSender() const", asMETHODPR(ScrollBar, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "FocusMode GetFocusMode() const", asMETHODPR(ScrollBar, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "FocusMode get_focusMode() const", asMETHODPR(ScrollBar, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // Button* ScrollBar::GetForwardButton() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Button@+ GetForwardButton() const", asMETHODPR(ScrollBar, GetForwardButton, () const, Button*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_forwardButton() const", asMETHODPR(ScrollBar, GetForwardButton, () const, Button*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ScrollBar, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ScrollBar, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& GetGlobalVars() const", asMETHODPR(ScrollBar, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& get_globalVars() const", asMETHODPR(ScrollBar, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetHeight() const", asMETHODPR(ScrollBar, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_height() const", asMETHODPR(ScrollBar, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(ScrollBar, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(ScrollBar, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetHoverOffset() const", asMETHODPR(ScrollBar, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_hoverOffset() const", asMETHODPR(ScrollBar, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetImageBorder() const", asMETHODPR(ScrollBar, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_imageBorder() const", asMETHODPR(ScrollBar, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetImageRect() const", asMETHODPR(ScrollBar, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_imageRect() const", asMETHODPR(ScrollBar, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndent() const", asMETHODPR(ScrollBar, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indent() const", asMETHODPR(ScrollBar, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndentSpacing() const", asMETHODPR(ScrollBar, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indentSpacing() const", asMETHODPR(ScrollBar, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetIndentWidth() const", asMETHODPR(ScrollBar, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_indentWidth() const", asMETHODPR(ScrollBar, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ScrollBar, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& GetLayoutBorder() const", asMETHODPR(ScrollBar, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntRect& get_layoutBorder() const", asMETHODPR(ScrollBar, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetLayoutElementMaxSize() const", asMETHODPR(ScrollBar, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(ScrollBar, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_layoutFlexScale() const", asMETHODPR(ScrollBar, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "LayoutMode GetLayoutMode() const", asMETHODPR(ScrollBar, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "LayoutMode get_layoutMode() const", asMETHODPR(ScrollBar, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetLayoutSpacing() const", asMETHODPR(ScrollBar, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_layoutSpacing() const", asMETHODPR(ScrollBar, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "Material@+ GetMaterial() const", asMETHODPR(ScrollBar, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Material@+ get_material() const", asMETHODPR(ScrollBar, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetMaterialAttr() const", asMETHODPR(ScrollBar, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetMaxAnchor() const", asMETHODPR(ScrollBar, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_maxAnchor() const", asMETHODPR(ScrollBar, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMaxHeight() const", asMETHODPR(ScrollBar, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_maxHeight() const", asMETHODPR(ScrollBar, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMaxOffset() const", asMETHODPR(ScrollBar, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_maxOffset() const", asMETHODPR(ScrollBar, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMaxSize() const", asMETHODPR(ScrollBar, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_maxSize() const", asMETHODPR(ScrollBar, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMaxWidth() const", asMETHODPR(ScrollBar, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_maxWidth() const", asMETHODPR(ScrollBar, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetMinAnchor() const", asMETHODPR(ScrollBar, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_minAnchor() const", asMETHODPR(ScrollBar, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMinHeight() const", asMETHODPR(ScrollBar, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_minHeight() const", asMETHODPR(ScrollBar, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMinOffset() const", asMETHODPR(ScrollBar, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_minOffset() const", asMETHODPR(ScrollBar, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetMinSize() const", asMETHODPR(ScrollBar, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_minSize() const", asMETHODPR(ScrollBar, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetMinWidth() const", asMETHODPR(ScrollBar, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_minWidth() const", asMETHODPR(ScrollBar, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetName() const", asMETHODPR(ScrollBar, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_name() const", asMETHODPR(ScrollBar, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumAttributes() const", asMETHODPR(ScrollBar, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_numAttributes() const", asMETHODPR(ScrollBar, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumChildren(bool = false) const", asMETHODPR(ScrollBar, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "uint get_numChildren(bool = false) const", asMETHODPR(ScrollBar, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "uint GetNumNetworkAttributes() const", asMETHODPR(ScrollBar, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ScrollBar, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ScrollBar, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ScrollBar, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "float GetOpacity() const", asMETHODPR(ScrollBar, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_opacity() const", asMETHODPR(ScrollBar, GetOpacity, () const, float), asCALL_THISCALL);
    // Orientation ScrollBar::GetOrientation() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Orientation GetOrientation() const", asMETHODPR(ScrollBar, GetOrientation, () const, Orientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Orientation get_orientation() const", asMETHODPR(ScrollBar, GetOrientation, () const, Orientation), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetParent() const", asMETHODPR(ScrollBar, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_parent() const", asMETHODPR(ScrollBar, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& GetPivot() const", asMETHODPR(ScrollBar, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const Vector2& get_pivot() const", asMETHODPR(ScrollBar, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetPosition() const", asMETHODPR(ScrollBar, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_position() const", asMETHODPR(ScrollBar, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetPriority() const", asMETHODPR(ScrollBar, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_priority() const", asMETHODPR(ScrollBar, GetPriority, () const, int), asCALL_THISCALL);
    // float ScrollBar::GetRange() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetRange() const", asMETHODPR(ScrollBar, GetRange, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_range() const", asMETHODPR(ScrollBar, GetRange, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ GetRoot() const", asMETHODPR(ScrollBar, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ get_root() const", asMETHODPR(ScrollBar, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetScreenPosition() const", asMETHODPR(ScrollBar, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_screenPosition() const", asMETHODPR(ScrollBar, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // float ScrollBar::GetScrollStep() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetScrollStep() const", asMETHODPR(ScrollBar, GetScrollStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_scrollStep() const", asMETHODPR(ScrollBar, GetScrollStep, () const, float), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& GetSize() const", asMETHODPR(ScrollBar, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const IntVector2& get_size() const", asMETHODPR(ScrollBar, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // Slider* ScrollBar::GetSlider() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "Slider@+ GetSlider() const", asMETHODPR(ScrollBar, GetSlider, () const, Slider*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Slider@+ get_slider() const", asMETHODPR(ScrollBar, GetSlider, () const, Slider*), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetSortChildren() const", asMETHODPR(ScrollBar, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_sortChildren() const", asMETHODPR(ScrollBar, GetSortChildren, () const, bool), asCALL_THISCALL);
    // float ScrollBar::GetStepFactor() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetStepFactor() const", asMETHODPR(ScrollBar, GetStepFactor, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_stepFactor() const", asMETHODPR(ScrollBar, GetStepFactor, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ScrollBar, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "Array<String>@ GetTags() const", asFUNCTION(ScrollBar_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ScrollBar", "Array<String>@ get_tags() const", asFUNCTION(ScrollBar_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "Texture@+ GetTexture() const", asMETHODPR(ScrollBar, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Texture@+ get_texture() const", asMETHODPR(ScrollBar, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "ResourceRef GetTextureAttr() const", asMETHODPR(ScrollBar, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "TraversalMode GetTraversalMode() const", asMETHODPR(ScrollBar, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "TraversalMode get_traversalMode() const", asMETHODPR(ScrollBar, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "StringHash GetType() const", asMETHODPR(ScrollBar, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "StringHash get_type() const", asMETHODPR(ScrollBar, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "const String& GetTypeName() const", asMETHODPR(ScrollBar, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "const String& get_typeName() const", asMETHODPR(ScrollBar, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool GetUseDerivedOpacity() const", asMETHODPR(ScrollBar, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_useDerivedOpacity() const", asMETHODPR(ScrollBar, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // float ScrollBar::GetValue() const | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "float GetValue() const", asMETHODPR(ScrollBar, GetValue, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_value() const", asMETHODPR(ScrollBar, GetValue, () const, float), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(ScrollBar, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "const VariantMap& GetVars() const", asMETHODPR(ScrollBar, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(ScrollBar, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(ScrollBar, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "int GetWidth() const", asMETHODPR(ScrollBar, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_width() const", asMETHODPR(ScrollBar, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasColorGradient() const", asMETHODPR(ScrollBar, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_colorGradient() const", asMETHODPR(ScrollBar, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasEventHandlers() const", asMETHODPR(ScrollBar, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasFocus() const", asMETHODPR(ScrollBar, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_focus() const", asMETHODPR(ScrollBar, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ScrollBar, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ScrollBar, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool HasTag(const String&in) const", asMETHODPR(ScrollBar, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void InsertChild(uint, UIElement@+)", asMETHODPR(ScrollBar, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsChildOf(UIElement@+) const", asMETHODPR(ScrollBar, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEditable() const", asMETHODPR(ScrollBar, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_editable() const", asMETHODPR(ScrollBar, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsElementEventSender() const", asMETHODPR(ScrollBar, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_elementEventSender() const", asMETHODPR(ScrollBar, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEnabled() const", asMETHODPR(ScrollBar, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enabled() const", asMETHODPR(ScrollBar, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsEnabledSelf() const", asMETHODPR(ScrollBar, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_enabledSelf() const", asMETHODPR(ScrollBar, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedHeight() const", asMETHODPR(ScrollBar, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedHeight() const", asMETHODPR(ScrollBar, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedSize() const", asMETHODPR(ScrollBar, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedSize() const", asMETHODPR(ScrollBar, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsFixedWidth() const", asMETHODPR(ScrollBar, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_fixedWidth() const", asMETHODPR(ScrollBar, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsHovering() const", asMETHODPR(ScrollBar, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_hovering() const", asMETHODPR(ScrollBar, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInside(IntVector2, bool)", asMETHODPR(ScrollBar, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(ScrollBar, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInstanceOf(StringHash) const", asMETHODPR(ScrollBar, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsInternal() const", asMETHODPR(ScrollBar, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_internal() const", asMETHODPR(ScrollBar, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsSelected() const", asMETHODPR(ScrollBar, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_selected() const", asMETHODPR(ScrollBar, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsTemporary() const", asMETHODPR(ScrollBar, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_temporary() const", asMETHODPR(ScrollBar, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsTiled() const", asMETHODPR(ScrollBar, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_tiled() const", asMETHODPR(ScrollBar, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsVisible() const", asMETHODPR(ScrollBar, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_visible() const", asMETHODPR(ScrollBar, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsVisibleEffective() const", asMETHODPR(ScrollBar, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool get_visibleEffective() const", asMETHODPR(ScrollBar, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsWheelHandler() const", asMETHODPR(ScrollBar, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(ScrollBar, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool Load(Deserializer&)", asMETHODPR(ScrollBar, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ScrollBar, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ScrollBar, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(const XMLElement&in)", asMETHODPR(ScrollBar, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ScrollBar, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool LoadXML(Deserializer&)", asMETHODPR(ScrollBar, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void MarkNetworkUpdate()", asMETHODPR(ScrollBar, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollBar, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(ScrollBar, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollBar, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollBar, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ScrollBar, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(ScrollBar, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool OnDragDropTest(UIElement@+)", asMETHODPR(ScrollBar, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ScrollBar, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollBar, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ScrollBar, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ScrollBar, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollBar, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnIndentSet()", asMETHODPR(ScrollBar, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(ScrollBar, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnPositionSet(const IntVector2&in)", asMETHODPR(ScrollBar, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void ScrollBar::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(ScrollBar, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ScrollBar, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void ScrollBar::OnSetEditable() override | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void OnSetEditable()", asMETHODPR(ScrollBar, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnTextInput(const String&in)", asMETHODPR(ScrollBar, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(ScrollBar, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ScrollBar, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ScrollBar, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollBar", "int Refs() const", asMETHODPR(ScrollBar, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_refs() const", asMETHODPR(ScrollBar, Refs, () const, int), asCALL_THISCALL);
    // static void ScrollBar::RegisterObject(Context* context) | File: ../UI/ScrollBar.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_RELEASE, "void f()", asMETHODPR(ScrollBar, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void Remove()", asMETHODPR(ScrollBar, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAllChildren()", asMETHODPR(ScrollBar, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAllTags()", asMETHODPR(ScrollBar, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ScrollBar, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(ScrollBar, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveChildAtIndex(uint)", asMETHODPR(ScrollBar, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveInstanceDefault()", asMETHODPR(ScrollBar, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void RemoveObjectAnimation()", asMETHODPR(ScrollBar, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool RemoveTag(const String&in)", asMETHODPR(ScrollBar, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void ResetDeepEnabled()", asMETHODPR(ScrollBar, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void ResetToDefault()", asMETHODPR(ScrollBar, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool Save(Serializer&) const", asMETHODPR(ScrollBar, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveDefaultAttributes() const", asMETHODPR(ScrollBar, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveJSON(JSONValue&) const", asMETHODPR(ScrollBar, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveXML(XMLElement&) const", asMETHODPR(ScrollBar, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(ScrollBar, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(ScrollBar, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // explicit ScrollBar::ScrollBar(Context* context) | File: ../UI/ScrollBar.h
    engine->RegisterObjectBehaviour("ScrollBar", asBEHAVE_FACTORY, "ScrollBar@+ f()", asFUNCTION(ScrollBar_ScrollBar_Context), asCALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SendEvent(StringHash)", asMETHODPR(ScrollBar, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ScrollBar, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(ScrollBar, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAnimationEnabled(bool)", asMETHODPR(ScrollBar, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_animationEnabled(bool)", asMETHODPR(ScrollBar, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAnimationTime(float)", asMETHODPR(ScrollBar, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ScrollBar, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ScrollBar, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ScrollBar, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ScrollBar, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ScrollBar, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ScrollBar, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ScrollBar, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBlendMode(BlendMode)", asMETHODPR(ScrollBar, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_blendMode(BlendMode)", asMETHODPR(ScrollBar, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBlockEvents(bool)", asMETHODPR(ScrollBar, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_border(const IntRect&in)", asMETHODPR(ScrollBar, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBringToBack(bool)", asMETHODPR(ScrollBar, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_bringToBack(bool)", asMETHODPR(ScrollBar, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetBringToFront(bool)", asMETHODPR(ScrollBar, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_bringToFront(bool)", asMETHODPR(ScrollBar, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetChildOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetClipBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_clipBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetClipChildren(bool)", asMETHODPR(ScrollBar, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_clipChildren(bool)", asMETHODPR(ScrollBar, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetColor(const Color&in)", asMETHODPR(ScrollBar, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_color(const Color&in)", asMETHODPR(ScrollBar, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetColor(Corner, const Color&in)", asMETHODPR(ScrollBar, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_colors(Corner, const Color&in)", asMETHODPR(ScrollBar, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDeepEnabled(bool)", asMETHODPR(ScrollBar, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(ScrollBar, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_defaultStyle(XMLFile@+)", asMETHODPR(ScrollBar, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDisabledOffset(int, int)", asMETHODPR(ScrollBar, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(ScrollBar, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(ScrollBar, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEditable(bool)", asMETHODPR(ScrollBar, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_editable(bool)", asMETHODPR(ScrollBar, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetElementEventSender(bool)", asMETHODPR(ScrollBar, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_elementEventSender(bool)", asMETHODPR(ScrollBar, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnableAnchor(bool)", asMETHODPR(ScrollBar, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_enableAnchor(bool)", asMETHODPR(ScrollBar, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnabled(bool)", asMETHODPR(ScrollBar, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_enabled(bool)", asMETHODPR(ScrollBar, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetEnabledRecursive(bool)", asMETHODPR(ScrollBar, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedHeight(int)", asMETHODPR(ScrollBar, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedSize(int, int)", asMETHODPR(ScrollBar, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFixedWidth(int)", asMETHODPR(ScrollBar, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFocus(bool)", asMETHODPR(ScrollBar, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_focus(bool)", asMETHODPR(ScrollBar, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFocusMode(FocusMode)", asMETHODPR(ScrollBar, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_focusMode(FocusMode)", asMETHODPR(ScrollBar, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetFullImageRect()", asMETHODPR(ScrollBar, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ScrollBar, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ScrollBar, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHeight(int)", asMETHODPR(ScrollBar, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_height(int)", asMETHODPR(ScrollBar, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(ScrollBar, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(ScrollBar, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHovering(bool)", asMETHODPR(ScrollBar, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetHoverOffset(int, int)", asMETHODPR(ScrollBar, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetImageBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_imageBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetImageRect(const IntRect&in)", asMETHODPR(ScrollBar, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_imageRect(const IntRect&in)", asMETHODPR(ScrollBar, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetIndent(int)", asMETHODPR(ScrollBar, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_indent(int)", asMETHODPR(ScrollBar, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetIndentSpacing(int)", asMETHODPR(ScrollBar, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_indentSpacing(int)", asMETHODPR(ScrollBar, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInstanceDefault(bool)", asMETHODPR(ScrollBar, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ScrollBar, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetInternal(bool)", asMETHODPR(ScrollBar, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_internal(bool)", asMETHODPR(ScrollBar, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(ScrollBar, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutBorder(const IntRect&in)", asMETHODPR(ScrollBar, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(ScrollBar, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(ScrollBar, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutMode(LayoutMode)", asMETHODPR(ScrollBar, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutMode(LayoutMode)", asMETHODPR(ScrollBar, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetLayoutSpacing(int)", asMETHODPR(ScrollBar, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_layoutSpacing(int)", asMETHODPR(ScrollBar, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaterial(Material@+)", asMETHODPR(ScrollBar, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_material(Material@+)", asMETHODPR(ScrollBar, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(ScrollBar, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(ScrollBar, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxAnchor(const Vector2&in)", asMETHODPR(ScrollBar, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxAnchor(float, float)", asMETHODPR(ScrollBar, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxHeight(int)", asMETHODPR(ScrollBar, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxHeight(int)", asMETHODPR(ScrollBar, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxSize(int, int)", asMETHODPR(ScrollBar, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMaxWidth(int)", asMETHODPR(ScrollBar, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_maxWidth(int)", asMETHODPR(ScrollBar, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinAnchor(const Vector2&in)", asMETHODPR(ScrollBar, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minAnchor(const Vector2&in)", asMETHODPR(ScrollBar, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinAnchor(float, float)", asMETHODPR(ScrollBar, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinHeight(int)", asMETHODPR(ScrollBar, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minHeight(int)", asMETHODPR(ScrollBar, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minOffset(const IntVector2&in)", asMETHODPR(ScrollBar, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinSize(int, int)", asMETHODPR(ScrollBar, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetMinWidth(int)", asMETHODPR(ScrollBar, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_minWidth(int)", asMETHODPR(ScrollBar, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetName(const String&in)", asMETHODPR(ScrollBar, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_name(const String&in)", asMETHODPR(ScrollBar, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ScrollBar, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ScrollBar, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ScrollBar, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetOpacity(float)", asMETHODPR(ScrollBar, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_opacity(float)", asMETHODPR(ScrollBar, SetOpacity, (float), void), asCALL_THISCALL);
    // void ScrollBar::SetOrientation(Orientation orientation) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetOrientation(Orientation)", asMETHODPR(ScrollBar, SetOrientation, (Orientation), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_orientation(Orientation)", asMETHODPR(ScrollBar, SetOrientation, (Orientation), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(ScrollBar, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPivot(const Vector2&in)", asMETHODPR(ScrollBar, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_pivot(const Vector2&in)", asMETHODPR(ScrollBar, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPivot(float, float)", asMETHODPR(ScrollBar, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPosition(const IntVector2&in)", asMETHODPR(ScrollBar, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_position(const IntVector2&in)", asMETHODPR(ScrollBar, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPosition(int, int)", asMETHODPR(ScrollBar, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetPriority(int)", asMETHODPR(ScrollBar, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_priority(int)", asMETHODPR(ScrollBar, SetPriority, (int), void), asCALL_THISCALL);
    // void ScrollBar::SetRange(float range) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetRange(float)", asMETHODPR(ScrollBar, SetRange, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_range(float)", asMETHODPR(ScrollBar, SetRange, (float), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetRenderTexture(Texture2D@+)", asMETHODPR(ScrollBar, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void ScrollBar::SetScrollStep(float step) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetScrollStep(float)", asMETHODPR(ScrollBar, SetScrollStep, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_scrollStep(float)", asMETHODPR(ScrollBar, SetScrollStep, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSelected(bool)", asMETHODPR(ScrollBar, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_selected(bool)", asMETHODPR(ScrollBar, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSize(const IntVector2&in)", asMETHODPR(ScrollBar, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_size(const IntVector2&in)", asMETHODPR(ScrollBar, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSize(int, int)", asMETHODPR(ScrollBar, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetSortChildren(bool)", asMETHODPR(ScrollBar, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_sortChildren(bool)", asMETHODPR(ScrollBar, SetSortChildren, (bool), void), asCALL_THISCALL);
    // void ScrollBar::SetStepFactor(float factor) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetStepFactor(float)", asMETHODPR(ScrollBar, SetStepFactor, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_stepFactor(float)", asMETHODPR(ScrollBar, SetStepFactor, (float), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(ScrollBar, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyle(const XMLElement&in)", asMETHODPR(ScrollBar, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(ScrollBar, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTags(Array<String>@+)", asFUNCTION(ScrollBar_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTemporary(bool)", asMETHODPR(ScrollBar, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_temporary(bool)", asMETHODPR(ScrollBar, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTexture(Texture@+)", asMETHODPR(ScrollBar, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_texture(Texture@+)", asMETHODPR(ScrollBar, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(ScrollBar, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTiled(bool)", asMETHODPR(ScrollBar, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_tiled(bool)", asMETHODPR(ScrollBar, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetTraversalMode(TraversalMode)", asMETHODPR(ScrollBar, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_traversalMode(TraversalMode)", asMETHODPR(ScrollBar, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetUseDerivedOpacity(bool)", asMETHODPR(ScrollBar, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_useDerivedOpacity(bool)", asMETHODPR(ScrollBar, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void ScrollBar::SetValue(float value) | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void SetValue(float)", asMETHODPR(ScrollBar, SetValue, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_value(float)", asMETHODPR(ScrollBar, SetValue, (float), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVar(StringHash, const Variant&in)", asMETHODPR(ScrollBar, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(ScrollBar, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(ScrollBar, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetVisible(bool)", asMETHODPR(ScrollBar, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_visible(bool)", asMETHODPR(ScrollBar, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SetWidth(int)", asMETHODPR(ScrollBar, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_width(int)", asMETHODPR(ScrollBar, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void SortChildren()", asMETHODPR(ScrollBar, SortChildren, (), void), asCALL_THISCALL);
    // void ScrollBar::StepBack() | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void StepBack()", asMETHODPR(ScrollBar, StepBack, (), void), asCALL_THISCALL);
    // void ScrollBar::StepForward() | File: ../UI/ScrollBar.h
    engine->RegisterObjectMethod("ScrollBar", "void StepForward()", asMETHODPR(ScrollBar, StepForward, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromAllEvents()", asMETHODPR(ScrollBar, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ScrollBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ScrollBar, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ScrollBar, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollBar", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ScrollBar, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void Update(float)", asMETHODPR(ScrollBar, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollBar", "void UpdateLayout()", asMETHODPR(ScrollBar, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollBar", "int WeakRefs() const", asMETHODPR(ScrollBar, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "int get_weakRefs() const", asMETHODPR(ScrollBar, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ScrollBar, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ScrollBar, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollBar", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ScrollBar, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ScrollView", "void AddChild(UIElement@+)", asMETHODPR(ScrollView, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_ADDREF, "void f()", asMETHODPR(ScrollView, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTag(const String&in)", asMETHODPR(ScrollView, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTags(const String&in, int8 = ';')", asMETHODPR(ScrollView, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AddTags(Array<String>@+)", asFUNCTION(ScrollView_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void AdjustScissor(IntRect&)", asMETHODPR(ScrollView, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void AllocateNetworkState()", asMETHODPR(ScrollView, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void ScrollView::ApplyAttributes() override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void ApplyAttributes()", asMETHODPR(ScrollView, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void BringToFront()", asMETHODPR(ScrollView, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(ScrollView, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void DisableLayoutUpdate()", asMETHODPR(ScrollView, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(ScrollView, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void EnableLayoutUpdate()", asMETHODPR(ScrollView, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool FilterAttributes(XMLElement&) const", asMETHODPR(ScrollView, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint FindChild(UIElement@+) const", asMETHODPR(ScrollView, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool GetAnimationEnabled() const", asMETHODPR(ScrollView, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_animationEnabled() const", asMETHODPR(ScrollView, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetAppliedStyle() const", asMETHODPR(ScrollView, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_style() const", asMETHODPR(ScrollView, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttribute(uint) const", asMETHODPR(ScrollView, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "Variant get_attributes(uint) const", asMETHODPR(ScrollView, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttribute(const String&in) const", asMETHODPR(ScrollView, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ScrollView, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ScrollView, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ScrollView, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ScrollView, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttributeDefault(uint) const", asMETHODPR(ScrollView, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "Variant get_attributeDefaults(uint) const", asMETHODPR(ScrollView, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ScrollView, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool ScrollView::GetAutoDisableChildren() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetAutoDisableChildren() const", asMETHODPR(ScrollView, GetAutoDisableChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_autoDisableChildren() const", asMETHODPR(ScrollView, GetAutoDisableChildren, () const, bool), asCALL_THISCALL);
    // float ScrollView::GetAutoDisableThreshold() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetAutoDisableThreshold() const", asMETHODPR(ScrollView, GetAutoDisableThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_autoDisableThreshold() const", asMETHODPR(ScrollView, GetAutoDisableThreshold, () const, float), asCALL_THISCALL);
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBlockEvents() const", asMETHODPR(ScrollView, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBringToBack() const", asMETHODPR(ScrollView, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_bringToBack() const", asMETHODPR(ScrollView, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetBringToFront() const", asMETHODPR(ScrollView, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_bringToFront() const", asMETHODPR(ScrollView, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetCategory() const", asMETHODPR(ScrollView, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_category() const", asMETHODPR(ScrollView, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(uint) const", asMETHODPR(ScrollView, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_children(uint) const", asMETHODPR(ScrollView, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(ScrollView, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(ScrollView, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetChildOffset() const", asMETHODPR(ScrollView, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_childOffset() const", asMETHODPR(ScrollView, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildren() const", asFUNCTION(ScrollView_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(ScrollView_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(ScrollView_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntRect& GetClipBorder() const", asMETHODPR(ScrollView, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntRect& get_clipBorder() const", asMETHODPR(ScrollView, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetClipChildren() const", asMETHODPR(ScrollView, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_clipChildren() const", asMETHODPR(ScrollView, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetColor(Corner) const", asMETHODPR(ScrollView, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Color& get_colors(Corner) const", asMETHODPR(ScrollView, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetColorAttr() const", asMETHODPR(ScrollView, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntRect GetCombinedScreenRect()", asMETHODPR(ScrollView, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "IntRect get_combinedScreenRect()", asMETHODPR(ScrollView, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // UIElement* ScrollView::GetContentElement() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetContentElement() const", asMETHODPR(ScrollView, GetContentElement, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_contentElement() const", asMETHODPR(ScrollView, GetContentElement, () const, UIElement*), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(ScrollView, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Color& GetDerivedColor() const", asMETHODPR(ScrollView, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "float GetDerivedOpacity() const", asMETHODPR(ScrollView, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_derivedOpacity() const", asMETHODPR(ScrollView, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(ScrollView, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(ScrollView, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint GetDragButtonCount() const", asMETHODPR(ScrollView, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_dragButtonCount() const", asMETHODPR(ScrollView, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(ScrollView, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(ScrollView, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(ScrollView, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetElementEventSender() const", asMETHODPR(ScrollView, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetEnableAnchor() const", asMETHODPR(ScrollView, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enableAnchor() const", asMETHODPR(ScrollView, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "VariantMap& GetEventDataMap() const", asMETHODPR(ScrollView, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "Object@+ GetEventSender() const", asMETHODPR(ScrollView, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "FocusMode GetFocusMode() const", asMETHODPR(ScrollView, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "FocusMode get_focusMode() const", asMETHODPR(ScrollView, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ScrollView, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ScrollView, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& GetGlobalVars() const", asMETHODPR(ScrollView, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& get_globalVars() const", asMETHODPR(ScrollView, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetHeight() const", asMETHODPR(ScrollView, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_height() const", asMETHODPR(ScrollView, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(ScrollView, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(ScrollView, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // ScrollBar* ScrollView::GetHorizontalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ GetHorizontalScrollBar() const", asMETHODPR(ScrollView, GetHorizontalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_horizontalScrollBar() const", asMETHODPR(ScrollView, GetHorizontalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    // bool ScrollView::GetHorizontalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetHorizontalScrollBarVisible() const", asMETHODPR(ScrollView, GetHorizontalScrollBarVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_horizontalScrollBarVisible() const", asMETHODPR(ScrollView, GetHorizontalScrollBarVisible, () const, bool), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndent() const", asMETHODPR(ScrollView, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indent() const", asMETHODPR(ScrollView, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndentSpacing() const", asMETHODPR(ScrollView, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indentSpacing() const", asMETHODPR(ScrollView, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetIndentWidth() const", asMETHODPR(ScrollView, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_indentWidth() const", asMETHODPR(ScrollView, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ScrollView, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntRect& GetLayoutBorder() const", asMETHODPR(ScrollView, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntRect& get_layoutBorder() const", asMETHODPR(ScrollView, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetLayoutElementMaxSize() const", asMETHODPR(ScrollView, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(ScrollView, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_layoutFlexScale() const", asMETHODPR(ScrollView, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "LayoutMode GetLayoutMode() const", asMETHODPR(ScrollView, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "LayoutMode get_layoutMode() const", asMETHODPR(ScrollView, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetLayoutSpacing() const", asMETHODPR(ScrollView, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_layoutSpacing() const", asMETHODPR(ScrollView, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetMaxAnchor() const", asMETHODPR(ScrollView, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_maxAnchor() const", asMETHODPR(ScrollView, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMaxHeight() const", asMETHODPR(ScrollView, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_maxHeight() const", asMETHODPR(ScrollView, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMaxOffset() const", asMETHODPR(ScrollView, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_maxOffset() const", asMETHODPR(ScrollView, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMaxSize() const", asMETHODPR(ScrollView, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_maxSize() const", asMETHODPR(ScrollView, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMaxWidth() const", asMETHODPR(ScrollView, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_maxWidth() const", asMETHODPR(ScrollView, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetMinAnchor() const", asMETHODPR(ScrollView, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_minAnchor() const", asMETHODPR(ScrollView, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMinHeight() const", asMETHODPR(ScrollView, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_minHeight() const", asMETHODPR(ScrollView, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMinOffset() const", asMETHODPR(ScrollView, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_minOffset() const", asMETHODPR(ScrollView, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetMinSize() const", asMETHODPR(ScrollView, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_minSize() const", asMETHODPR(ScrollView, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetMinWidth() const", asMETHODPR(ScrollView, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_minWidth() const", asMETHODPR(ScrollView, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetName() const", asMETHODPR(ScrollView, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_name() const", asMETHODPR(ScrollView, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumAttributes() const", asMETHODPR(ScrollView, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_numAttributes() const", asMETHODPR(ScrollView, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumChildren(bool = false) const", asMETHODPR(ScrollView, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "uint get_numChildren(bool = false) const", asMETHODPR(ScrollView, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "uint GetNumNetworkAttributes() const", asMETHODPR(ScrollView, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ScrollView, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ScrollView, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ScrollView, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "float GetOpacity() const", asMETHODPR(ScrollView, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_opacity() const", asMETHODPR(ScrollView, GetOpacity, () const, float), asCALL_THISCALL);
    // float ScrollView::GetPageStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetPageStep() const", asMETHODPR(ScrollView, GetPageStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_pageStep() const", asMETHODPR(ScrollView, GetPageStep, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetParent() const", asMETHODPR(ScrollView, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_parent() const", asMETHODPR(ScrollView, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Vector2& GetPivot() const", asMETHODPR(ScrollView, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const Vector2& get_pivot() const", asMETHODPR(ScrollView, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetPosition() const", asMETHODPR(ScrollView, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_position() const", asMETHODPR(ScrollView, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetPriority() const", asMETHODPR(ScrollView, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_priority() const", asMETHODPR(ScrollView, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ GetRoot() const", asMETHODPR(ScrollView, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_root() const", asMETHODPR(ScrollView, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetScreenPosition() const", asMETHODPR(ScrollView, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_screenPosition() const", asMETHODPR(ScrollView, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // bool ScrollView::GetScrollBarsAutoVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetScrollBarsAutoVisible() const", asMETHODPR(ScrollView, GetScrollBarsAutoVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_scrollBarsAutoVisible() const", asMETHODPR(ScrollView, GetScrollBarsAutoVisible, () const, bool), asCALL_THISCALL);
    // float ScrollView::GetScrollDeceleration() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollDeceleration() const", asMETHODPR(ScrollView, GetScrollDeceleration, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollDeceleration() const", asMETHODPR(ScrollView, GetScrollDeceleration, () const, float), asCALL_THISCALL);
    // BorderImage* ScrollView::GetScrollPanel() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "BorderImage@+ GetScrollPanel() const", asMETHODPR(ScrollView, GetScrollPanel, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "BorderImage@+ get_scrollPanel() const", asMETHODPR(ScrollView, GetScrollPanel, () const, BorderImage*), asCALL_THISCALL);
    // float ScrollView::GetScrollSnapEpsilon() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollSnapEpsilon() const", asMETHODPR(ScrollView, GetScrollSnapEpsilon, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollSnapEpsilon() const", asMETHODPR(ScrollView, GetScrollSnapEpsilon, () const, float), asCALL_THISCALL);
    // float ScrollView::GetScrollStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "float GetScrollStep() const", asMETHODPR(ScrollView, GetScrollStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollStep() const", asMETHODPR(ScrollView, GetScrollStep, () const, float), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetSize() const", asMETHODPR(ScrollView, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_size() const", asMETHODPR(ScrollView, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetSortChildren() const", asMETHODPR(ScrollView, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_sortChildren() const", asMETHODPR(ScrollView, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ScrollView, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "Array<String>@ GetTags() const", asFUNCTION(ScrollView_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ScrollView", "Array<String>@ get_tags() const", asFUNCTION(ScrollView_GetTags_void), asCALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "TraversalMode GetTraversalMode() const", asMETHODPR(ScrollView, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "TraversalMode get_traversalMode() const", asMETHODPR(ScrollView, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "StringHash GetType() const", asMETHODPR(ScrollView, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "StringHash get_type() const", asMETHODPR(ScrollView, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "const String& GetTypeName() const", asMETHODPR(ScrollView, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const String& get_typeName() const", asMETHODPR(ScrollView, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool GetUseDerivedOpacity() const", asMETHODPR(ScrollView, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_useDerivedOpacity() const", asMETHODPR(ScrollView, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(ScrollView, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "const VariantMap& GetVars() const", asMETHODPR(ScrollView, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(ScrollView, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(ScrollView, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // ScrollBar* ScrollView::GetVerticalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ GetVerticalScrollBar() const", asMETHODPR(ScrollView, GetVerticalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_verticalScrollBar() const", asMETHODPR(ScrollView, GetVerticalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    // bool ScrollView::GetVerticalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool GetVerticalScrollBarVisible() const", asMETHODPR(ScrollView, GetVerticalScrollBarVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_verticalScrollBarVisible() const", asMETHODPR(ScrollView, GetVerticalScrollBarVisible, () const, bool), asCALL_THISCALL);
    // const IntVector2& ScrollView::GetViewPosition() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& GetViewPosition() const", asMETHODPR(ScrollView, GetViewPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_viewPosition() const", asMETHODPR(ScrollView, GetViewPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "int GetWidth() const", asMETHODPR(ScrollView, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_width() const", asMETHODPR(ScrollView, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasColorGradient() const", asMETHODPR(ScrollView, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_colorGradient() const", asMETHODPR(ScrollView, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasEventHandlers() const", asMETHODPR(ScrollView, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasFocus() const", asMETHODPR(ScrollView, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_focus() const", asMETHODPR(ScrollView, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ScrollView, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ScrollView, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool HasTag(const String&in) const", asMETHODPR(ScrollView, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void InsertChild(uint, UIElement@+)", asMETHODPR(ScrollView, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsChildOf(UIElement@+) const", asMETHODPR(ScrollView, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEditable() const", asMETHODPR(ScrollView, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_editable() const", asMETHODPR(ScrollView, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsElementEventSender() const", asMETHODPR(ScrollView, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_elementEventSender() const", asMETHODPR(ScrollView, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEnabled() const", asMETHODPR(ScrollView, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enabled() const", asMETHODPR(ScrollView, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsEnabledSelf() const", asMETHODPR(ScrollView, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_enabledSelf() const", asMETHODPR(ScrollView, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedHeight() const", asMETHODPR(ScrollView, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedHeight() const", asMETHODPR(ScrollView, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedSize() const", asMETHODPR(ScrollView, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedSize() const", asMETHODPR(ScrollView, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsFixedWidth() const", asMETHODPR(ScrollView, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_fixedWidth() const", asMETHODPR(ScrollView, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsHovering() const", asMETHODPR(ScrollView, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_hovering() const", asMETHODPR(ScrollView, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInside(IntVector2, bool)", asMETHODPR(ScrollView, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(ScrollView, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInstanceOf(StringHash) const", asMETHODPR(ScrollView, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsInternal() const", asMETHODPR(ScrollView, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_internal() const", asMETHODPR(ScrollView, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsSelected() const", asMETHODPR(ScrollView, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_selected() const", asMETHODPR(ScrollView, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool IsTemporary() const", asMETHODPR(ScrollView, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_temporary() const", asMETHODPR(ScrollView, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsVisible() const", asMETHODPR(ScrollView, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_visible() const", asMETHODPR(ScrollView, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsVisibleEffective() const", asMETHODPR(ScrollView, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_visibleEffective() const", asMETHODPR(ScrollView, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // bool ScrollView::IsWheelHandler() const override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "bool IsWheelHandler() const", asMETHODPR(ScrollView, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(ScrollView, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool Load(Deserializer&)", asMETHODPR(ScrollView, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ScrollView, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ScrollView, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(const XMLElement&in)", asMETHODPR(ScrollView, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ScrollView, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool LoadXML(Deserializer&)", asMETHODPR(ScrollView, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void MarkNetworkUpdate()", asMETHODPR(ScrollView, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollView, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(ScrollView, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollView, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollView, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ScrollView, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(ScrollView, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool OnDragDropTest(UIElement@+)", asMETHODPR(ScrollView, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ScrollView, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollView, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ScrollView, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ScrollView, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ScrollView, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnIndentSet()", asMETHODPR(ScrollView, OnIndentSet, (), void), asCALL_THISCALL);
    // void ScrollView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(ScrollView, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnPositionSet(const IntVector2&in)", asMETHODPR(ScrollView, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void ScrollView::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(ScrollView, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ScrollView, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnSetEditable()", asMETHODPR(ScrollView, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void OnTextInput(const String&in)", asMETHODPR(ScrollView, OnTextInput, (const String&), void), asCALL_THISCALL);
    // void ScrollView::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(ScrollView, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ScrollView, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ScrollView, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollView", "int Refs() const", asMETHODPR(ScrollView, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_refs() const", asMETHODPR(ScrollView, Refs, () const, int), asCALL_THISCALL);
    // static void ScrollView::RegisterObject(Context* context) | File: ../UI/ScrollView.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_RELEASE, "void f()", asMETHODPR(ScrollView, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void Remove()", asMETHODPR(ScrollView, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAllChildren()", asMETHODPR(ScrollView, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAllTags()", asMETHODPR(ScrollView, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ScrollView, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(ScrollView, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveChildAtIndex(uint)", asMETHODPR(ScrollView, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveInstanceDefault()", asMETHODPR(ScrollView, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void RemoveObjectAnimation()", asMETHODPR(ScrollView, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool RemoveTag(const String&in)", asMETHODPR(ScrollView, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void ResetDeepEnabled()", asMETHODPR(ScrollView, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void ResetToDefault()", asMETHODPR(ScrollView, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool Save(Serializer&) const", asMETHODPR(ScrollView, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveDefaultAttributes() const", asMETHODPR(ScrollView, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveJSON(JSONValue&) const", asMETHODPR(ScrollView, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveXML(XMLElement&) const", asMETHODPR(ScrollView, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(ScrollView, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(ScrollView, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // explicit ScrollView::ScrollView(Context* context) | File: ../UI/ScrollView.h
    engine->RegisterObjectBehaviour("ScrollView", asBEHAVE_FACTORY, "ScrollView@+ f()", asFUNCTION(ScrollView_ScrollView_Context), asCALL_CDECL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SendEvent(StringHash)", asMETHODPR(ScrollView, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ScrollView, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(ScrollView, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAnimationEnabled(bool)", asMETHODPR(ScrollView, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_animationEnabled(bool)", asMETHODPR(ScrollView, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAnimationTime(float)", asMETHODPR(ScrollView, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ScrollView, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ScrollView, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ScrollView, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ScrollView, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ScrollView, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ScrollView, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ScrollView, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void ScrollView::SetAutoDisableChildren(bool disable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetAutoDisableChildren(bool)", asMETHODPR(ScrollView, SetAutoDisableChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableChildren(bool)", asMETHODPR(ScrollView, SetAutoDisableChildren, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetAutoDisableThreshold(float amount) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetAutoDisableThreshold(float)", asMETHODPR(ScrollView, SetAutoDisableThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableThreshold(float)", asMETHODPR(ScrollView, SetAutoDisableThreshold, (float), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SetBlockEvents(bool)", asMETHODPR(ScrollView, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetBringToBack(bool)", asMETHODPR(ScrollView, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_bringToBack(bool)", asMETHODPR(ScrollView, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetBringToFront(bool)", asMETHODPR(ScrollView, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_bringToFront(bool)", asMETHODPR(ScrollView, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetChildOffset(const IntVector2&in)", asMETHODPR(ScrollView, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetClipBorder(const IntRect&in)", asMETHODPR(ScrollView, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_clipBorder(const IntRect&in)", asMETHODPR(ScrollView, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetClipChildren(bool)", asMETHODPR(ScrollView, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_clipChildren(bool)", asMETHODPR(ScrollView, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetColor(const Color&in)", asMETHODPR(ScrollView, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_color(const Color&in)", asMETHODPR(ScrollView, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetColor(Corner, const Color&in)", asMETHODPR(ScrollView, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_colors(Corner, const Color&in)", asMETHODPR(ScrollView, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void ScrollView::SetContentElement(UIElement* element) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetContentElement(UIElement@+)", asMETHODPR(ScrollView, SetContentElement, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_contentElement(UIElement@+)", asMETHODPR(ScrollView, SetContentElement, (UIElement*), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDeepEnabled(bool)", asMETHODPR(ScrollView, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(ScrollView, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_defaultStyle(XMLFile@+)", asMETHODPR(ScrollView, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(ScrollView, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(ScrollView, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEditable(bool)", asMETHODPR(ScrollView, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_editable(bool)", asMETHODPR(ScrollView, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetElementEventSender(bool)", asMETHODPR(ScrollView, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_elementEventSender(bool)", asMETHODPR(ScrollView, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnableAnchor(bool)", asMETHODPR(ScrollView, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_enableAnchor(bool)", asMETHODPR(ScrollView, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnabled(bool)", asMETHODPR(ScrollView, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_enabled(bool)", asMETHODPR(ScrollView, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetEnabledRecursive(bool)", asMETHODPR(ScrollView, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedHeight(int)", asMETHODPR(ScrollView, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedSize(const IntVector2&in)", asMETHODPR(ScrollView, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedSize(int, int)", asMETHODPR(ScrollView, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFixedWidth(int)", asMETHODPR(ScrollView, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFocus(bool)", asMETHODPR(ScrollView, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_focus(bool)", asMETHODPR(ScrollView, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetFocusMode(FocusMode)", asMETHODPR(ScrollView, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_focusMode(FocusMode)", asMETHODPR(ScrollView, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ScrollView, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ScrollView, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHeight(int)", asMETHODPR(ScrollView, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_height(int)", asMETHODPR(ScrollView, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(ScrollView, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(ScrollView, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void ScrollView::SetHorizontalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetHorizontalScrollBarVisible(bool)", asMETHODPR(ScrollView, SetHorizontalScrollBarVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_horizontalScrollBarVisible(bool)", asMETHODPR(ScrollView, SetHorizontalScrollBarVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetHovering(bool)", asMETHODPR(ScrollView, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetIndent(int)", asMETHODPR(ScrollView, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_indent(int)", asMETHODPR(ScrollView, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetIndentSpacing(int)", asMETHODPR(ScrollView, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_indentSpacing(int)", asMETHODPR(ScrollView, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetInstanceDefault(bool)", asMETHODPR(ScrollView, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ScrollView, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetInternal(bool)", asMETHODPR(ScrollView, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_internal(bool)", asMETHODPR(ScrollView, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(ScrollView, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(ScrollView, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutBorder(const IntRect&in)", asMETHODPR(ScrollView, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(ScrollView, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(ScrollView, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutMode(LayoutMode)", asMETHODPR(ScrollView, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutMode(LayoutMode)", asMETHODPR(ScrollView, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetLayoutSpacing(int)", asMETHODPR(ScrollView, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_layoutSpacing(int)", asMETHODPR(ScrollView, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(ScrollView, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxAnchor(const Vector2&in)", asMETHODPR(ScrollView, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxAnchor(float, float)", asMETHODPR(ScrollView, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxHeight(int)", asMETHODPR(ScrollView, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxHeight(int)", asMETHODPR(ScrollView, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(ScrollView, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxOffset(const IntVector2&in)", asMETHODPR(ScrollView, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxSize(const IntVector2&in)", asMETHODPR(ScrollView, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxSize(const IntVector2&in)", asMETHODPR(ScrollView, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxSize(int, int)", asMETHODPR(ScrollView, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMaxWidth(int)", asMETHODPR(ScrollView, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_maxWidth(int)", asMETHODPR(ScrollView, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinAnchor(const Vector2&in)", asMETHODPR(ScrollView, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minAnchor(const Vector2&in)", asMETHODPR(ScrollView, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinAnchor(float, float)", asMETHODPR(ScrollView, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinHeight(int)", asMETHODPR(ScrollView, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minHeight(int)", asMETHODPR(ScrollView, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinOffset(const IntVector2&in)", asMETHODPR(ScrollView, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minOffset(const IntVector2&in)", asMETHODPR(ScrollView, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinSize(const IntVector2&in)", asMETHODPR(ScrollView, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minSize(const IntVector2&in)", asMETHODPR(ScrollView, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinSize(int, int)", asMETHODPR(ScrollView, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetMinWidth(int)", asMETHODPR(ScrollView, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_minWidth(int)", asMETHODPR(ScrollView, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetName(const String&in)", asMETHODPR(ScrollView, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_name(const String&in)", asMETHODPR(ScrollView, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ScrollView, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ScrollView, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ScrollView", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ScrollView, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetOpacity(float)", asMETHODPR(ScrollView, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_opacity(float)", asMETHODPR(ScrollView, SetOpacity, (float), void), asCALL_THISCALL);
    // void ScrollView::SetPageStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetPageStep(float)", asMETHODPR(ScrollView, SetPageStep, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_pageStep(float)", asMETHODPR(ScrollView, SetPageStep, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(ScrollView, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPivot(const Vector2&in)", asMETHODPR(ScrollView, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_pivot(const Vector2&in)", asMETHODPR(ScrollView, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPivot(float, float)", asMETHODPR(ScrollView, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPosition(const IntVector2&in)", asMETHODPR(ScrollView, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_position(const IntVector2&in)", asMETHODPR(ScrollView, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPosition(int, int)", asMETHODPR(ScrollView, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetPriority(int)", asMETHODPR(ScrollView, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_priority(int)", asMETHODPR(ScrollView, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetRenderTexture(Texture2D@+)", asMETHODPR(ScrollView, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void ScrollView::SetScrollBarsAutoVisible(bool enable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollBarsAutoVisible(bool)", asMETHODPR(ScrollView, SetScrollBarsAutoVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollBarsAutoVisible(bool)", asMETHODPR(ScrollView, SetScrollBarsAutoVisible, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollBarsVisible(bool, bool)", asMETHODPR(ScrollView, SetScrollBarsVisible, (bool, bool), void), asCALL_THISCALL);
    // void ScrollView::SetScrollDeceleration(float deceleration) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollDeceleration(float)", asMETHODPR(ScrollView, SetScrollDeceleration, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollDeceleration(float)", asMETHODPR(ScrollView, SetScrollDeceleration, (float), void), asCALL_THISCALL);
    // void ScrollView::SetScrollSnapEpsilon(float snap) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollSnapEpsilon(float)", asMETHODPR(ScrollView, SetScrollSnapEpsilon, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollSnapEpsilon(float)", asMETHODPR(ScrollView, SetScrollSnapEpsilon, (float), void), asCALL_THISCALL);
    // void ScrollView::SetScrollStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetScrollStep(float)", asMETHODPR(ScrollView, SetScrollStep, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollStep(float)", asMETHODPR(ScrollView, SetScrollStep, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSelected(bool)", asMETHODPR(ScrollView, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_selected(bool)", asMETHODPR(ScrollView, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSize(const IntVector2&in)", asMETHODPR(ScrollView, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_size(const IntVector2&in)", asMETHODPR(ScrollView, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSize(int, int)", asMETHODPR(ScrollView, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetSortChildren(bool)", asMETHODPR(ScrollView, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_sortChildren(bool)", asMETHODPR(ScrollView, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(ScrollView, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyle(const XMLElement&in)", asMETHODPR(ScrollView, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(ScrollView, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetTags(Array<String>@+)", asFUNCTION(ScrollView_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void SetTemporary(bool)", asMETHODPR(ScrollView, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_temporary(bool)", asMETHODPR(ScrollView, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetTraversalMode(TraversalMode)", asMETHODPR(ScrollView, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_traversalMode(TraversalMode)", asMETHODPR(ScrollView, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetUseDerivedOpacity(bool)", asMETHODPR(ScrollView, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_useDerivedOpacity(bool)", asMETHODPR(ScrollView, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVar(StringHash, const Variant&in)", asMETHODPR(ScrollView, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(ScrollView, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(ScrollView, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void ScrollView::SetVerticalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetVerticalScrollBarVisible(bool)", asMETHODPR(ScrollView, SetVerticalScrollBarVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_verticalScrollBarVisible(bool)", asMETHODPR(ScrollView, SetVerticalScrollBarVisible, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetViewPosition(const IntVector2& position) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPosition(const IntVector2&in)", asMETHODPR(ScrollView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_viewPosition(const IntVector2&in)", asMETHODPR(ScrollView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void ScrollView::SetViewPosition(int x, int y) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPosition(int, int)", asMETHODPR(ScrollView, SetViewPosition, (int, int), void), asCALL_THISCALL);
    // void ScrollView::SetViewPositionAttr(const IntVector2& value) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void SetViewPositionAttr(const IntVector2&in)", asMETHODPR(ScrollView, SetViewPositionAttr, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetVisible(bool)", asMETHODPR(ScrollView, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_visible(bool)", asMETHODPR(ScrollView, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SetWidth(int)", asMETHODPR(ScrollView, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_width(int)", asMETHODPR(ScrollView, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void SortChildren()", asMETHODPR(ScrollView, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromAllEvents()", asMETHODPR(ScrollView, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ScrollView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ScrollView, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ScrollView, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ScrollView", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ScrollView, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void ScrollView::Update(float timeStep) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ScrollView", "void Update(float)", asMETHODPR(ScrollView, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ScrollView", "void UpdateLayout()", asMETHODPR(ScrollView, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ScrollView", "int WeakRefs() const", asMETHODPR(ScrollView, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "int get_weakRefs() const", asMETHODPR(ScrollView, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ScrollView, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ScrollView, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ScrollView", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ScrollView, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_ADDREF, "void f()", asMETHODPR(Serializable, AddRef, (), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void AllocateNetworkState()", asMETHODPR(Serializable, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void ApplyAttributes()", asMETHODPR(Serializable, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttribute(uint) const", asMETHODPR(Serializable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "Variant get_attributes(uint) const", asMETHODPR(Serializable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttribute(const String&in) const", asMETHODPR(Serializable, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttributeDefault(uint) const", asMETHODPR(Serializable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "Variant get_attributeDefaults(uint) const", asMETHODPR(Serializable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Serializable, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool GetBlockEvents() const", asMETHODPR(Serializable, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const String& GetCategory() const", asMETHODPR(Serializable, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const String& get_category() const", asMETHODPR(Serializable, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "VariantMap& GetEventDataMap() const", asMETHODPR(Serializable, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "Object@+ GetEventSender() const", asMETHODPR(Serializable, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Serializable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Serializable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const VariantMap& GetGlobalVars() const", asMETHODPR(Serializable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const VariantMap& get_globalVars() const", asMETHODPR(Serializable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Serializable, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "uint GetNumAttributes() const", asMETHODPR(Serializable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "uint get_numAttributes() const", asMETHODPR(Serializable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "uint GetNumNetworkAttributes() const", asMETHODPR(Serializable, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Serializable, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "StringHash GetType() const", asMETHODPR(Serializable, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "StringHash get_type() const", asMETHODPR(Serializable, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "const String& GetTypeName() const", asMETHODPR(Serializable, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "const String& get_typeName() const", asMETHODPR(Serializable, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasEventHandlers() const", asMETHODPR(Serializable, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Serializable, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Serializable, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "bool IsInstanceOf(StringHash) const", asMETHODPR(Serializable, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool IsTemporary() const", asMETHODPR(Serializable, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "bool get_temporary() const", asMETHODPR(Serializable, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool Load(Deserializer&)", asMETHODPR(Serializable, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual bool Serializable::LoadJSON(const JSONValue& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Serializable, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // virtual bool Serializable::LoadXML(const XMLElement& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool LoadXML(const XMLElement&in)", asMETHODPR(Serializable, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void MarkNetworkUpdate()", asMETHODPR(Serializable, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Serializable, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Serializable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Serializable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Serializable, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Serializable, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Serializable", "int Refs() const", asMETHODPR(Serializable, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "int get_refs() const", asMETHODPR(Serializable, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_RELEASE, "void f()", asMETHODPR(Serializable, ReleaseRef, (), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void RemoveInstanceDefault()", asMETHODPR(Serializable, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void ResetToDefault()", asMETHODPR(Serializable, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool Save(Serializer&) const", asMETHODPR(Serializable, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveDefaultAttributes() const", asMETHODPR(Serializable, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveJSON(JSONValue& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveJSON(JSONValue&) const", asMETHODPR(Serializable, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveXML(XMLElement& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SaveXML(XMLElement&) const", asMETHODPR(Serializable, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SendEvent(StringHash)", asMETHODPR(Serializable, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Serializable, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // explicit Serializable::Serializable(Context* context) | File: ../Scene/Serializable.h
    engine->RegisterObjectBehaviour("Serializable", asBEHAVE_FACTORY, "Serializable@+ f()", asFUNCTION(Serializable_Serializable_Context), asCALL_CDECL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Serializable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Serializable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Serializable, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SetBlockEvents(bool)", asMETHODPR(Serializable, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Serializable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Serializable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetInstanceDefault(bool)", asMETHODPR(Serializable, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Serializable, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void SetTemporary(bool)", asMETHODPR(Serializable, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "void set_temporary(bool)", asMETHODPR(Serializable, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromAllEvents()", asMETHODPR(Serializable, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Serializable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Serializable, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Serializable, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Serializable", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Serializable, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Serializable", "int WeakRefs() const", asMETHODPR(Serializable, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Serializable", "int get_weakRefs() const", asMETHODPR(Serializable, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Serializable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Serializable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Serializable", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Serializable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Serializer", "bool WriteBool(bool)", asMETHODPR(Serializer, WriteBool, (bool), bool), asCALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(Serializer, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteByte(int8)", asMETHODPR(Serializer, WriteByte, (signed char), bool), asCALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteColor(const Color&in)", asMETHODPR(Serializer, WriteColor, (const Color&), bool), asCALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteDouble(double)", asMETHODPR(Serializer, WriteDouble, (double), bool), asCALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteFileID(const String&in)", asMETHODPR(Serializer, WriteFileID, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteFloat(float)", asMETHODPR(Serializer, WriteFloat, (float), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteInt(int)", asMETHODPR(Serializer, WriteInt, (int), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteInt64(int64)", asMETHODPR(Serializer, WriteInt64, (long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntRect(const IntRect&in)", asMETHODPR(Serializer, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(Serializer, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteIntVector3(const IntVector3&in)", asMETHODPR(Serializer, WriteIntVector3, (const IntVector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteLine(const String&in)", asMETHODPR(Serializer, WriteLine, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(Serializer, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(Serializer, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(Serializer, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteNetID(uint)", asMETHODPR(Serializer, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(Serializer, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(Serializer, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(Serializer, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteRect(const Rect&in)", asMETHODPR(Serializer, WriteRect, (const Rect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteResourceRef(const ResourceRef&in)", asMETHODPR(Serializer, WriteResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteResourceRefList(const ResourceRefList&in)", asMETHODPR(Serializer, WriteResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteShort(int16)", asMETHODPR(Serializer, WriteShort, (short), bool), asCALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteString(const String&in)", asMETHODPR(Serializer, WriteString, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteStringHash(const StringHash&in)", asMETHODPR(Serializer, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteStringVector(Array<String>@+)", asFUNCTION(Serializer_WriteStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUByte(uint8)", asMETHODPR(Serializer, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUInt(uint)", asMETHODPR(Serializer, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUInt64(uint64)", asMETHODPR(Serializer, WriteUInt64, (unsigned long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteUShort(uint16)", asMETHODPR(Serializer, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariant(const Variant&in)", asMETHODPR(Serializer, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariantData(const Variant&in)", asMETHODPR(Serializer, WriteVariantData, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(Serializer, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector2(const Vector2&in)", asMETHODPR(Serializer, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector3(const Vector3&in)", asMETHODPR(Serializer, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVector4(const Vector4&in)", asMETHODPR(Serializer, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("Serializer", "bool WriteVLE(uint)", asMETHODPR(Serializer, WriteVLE, (unsigned), bool), asCALL_THISCALL);
    // Serializer& Serializer::operator=(const Serializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Serializer>(engine, "Serializer");
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(Serializer, "Serializer")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_ADDREF, "void f()", asMETHODPR(Shader, AddRef, (), void), asCALL_THISCALL);
    // bool Shader::BeginLoad(Deserializer& source) override | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "bool BeginLoad(Deserializer&)", asMETHODPR(Shader, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Shader::EndLoad() override | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "bool EndLoad()", asMETHODPR(Shader, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Shader, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool GetBlockEvents() const", asMETHODPR(Shader, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const String& GetCategory() const", asMETHODPR(Shader, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_category() const", asMETHODPR(Shader, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "VariantMap& GetEventDataMap() const", asMETHODPR(Shader, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "Object@+ GetEventSender() const", asMETHODPR(Shader, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Shader, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Shader, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const VariantMap& GetGlobalVars() const", asMETHODPR(Shader, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const VariantMap& get_globalVars() const", asMETHODPR(Shader, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "uint GetMemoryUse() const", asMETHODPR(Shader, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "uint get_memoryUse() const", asMETHODPR(Shader, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "const String& GetName() const", asMETHODPR(Shader, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_name() const", asMETHODPR(Shader, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "StringHash GetNameHash() const", asMETHODPR(Shader, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // const String& Shader::GetSourceCode(ShaderType type) const | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "const String& GetSourceCode(ShaderType) const", asMETHODPR(Shader, GetSourceCode, (ShaderType) const, const String&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Shader, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Shader::GetTimeStamp() const | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "uint GetTimeStamp() const", asMETHODPR(Shader, GetTimeStamp, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "StringHash GetType() const", asMETHODPR(Shader, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "StringHash get_type() const", asMETHODPR(Shader, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "const String& GetTypeName() const", asMETHODPR(Shader, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "const String& get_typeName() const", asMETHODPR(Shader, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "uint GetUseTimer()", asMETHODPR(Shader, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "uint get_useTimer()", asMETHODPR(Shader, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // ShaderVariation* Shader::GetVariation(ShaderType type, const String& defines) | File: ../Graphics/Shader.h
    engine->RegisterObjectMethod("Shader", "ShaderVariation@+ GetVariation(ShaderType, const String&in)", asMETHODPR(Shader, GetVariation, (ShaderType, const String&), ShaderVariation*), asCALL_THISCALL);
    // ShaderVariation* Shader::GetVariation(ShaderType type, const char* defines) | File: ../Graphics/Shader.h
    // Error: type "const char*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasEventHandlers() const", asMETHODPR(Shader, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Shader, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Shader, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "bool IsInstanceOf(StringHash) const", asMETHODPR(Shader, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool Load(Deserializer&)", asMETHODPR(Shader, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool LoadFile(const String&in)", asMETHODPR(Shader, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "bool Load(const String&in)", asMETHODPR(Shader, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Shader, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Shader", "int Refs() const", asMETHODPR(Shader, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "int get_refs() const", asMETHODPR(Shader, Refs, () const, int), asCALL_THISCALL);
    // static void Shader::RegisterObject(Context* context) | File: ../Graphics/Shader.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_RELEASE, "void f()", asMETHODPR(Shader, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void ResetUseTimer()", asMETHODPR(Shader, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool Save(Serializer&) const", asMETHODPR(Shader, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "bool SaveFile(const String&in) const", asMETHODPR(Shader, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "bool Save(const String&in) const", asMETHODPR(Shader, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SendEvent(StringHash)", asMETHODPR(Shader, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Shader, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Shader, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SetBlockEvents(bool)", asMETHODPR(Shader, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Shader, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Shader, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetMemoryUse(uint)", asMETHODPR(Shader, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Shader", "void SetName(const String&in)", asMETHODPR(Shader, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "void set_name(const String&in)", asMETHODPR(Shader, SetName, (const String&), void), asCALL_THISCALL);
    // explicit Shader::Shader(Context* context) | File: ../Graphics/Shader.h
    engine->RegisterObjectBehaviour("Shader", asBEHAVE_FACTORY, "Shader@+ f()", asFUNCTION(Shader_Shader_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromAllEvents()", asMETHODPR(Shader, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Shader_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Shader, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Shader, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Shader", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Shader, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Shader", "int WeakRefs() const", asMETHODPR(Shader, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Shader", "int get_weakRefs() const", asMETHODPR(Shader, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_ADDREF, "void f()", asMETHODPR(ShaderParameterAnimationInfo, AddRef, (), void), asCALL_THISCALL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "ValueAnimation@+ GetAnimation() const", asMETHODPR(ShaderParameterAnimationInfo, GetAnimation, () const, ValueAnimation*), asCALL_THISCALL);
    // const String& ShaderParameterAnimationInfo::GetName() const | File: ../Graphics/Material.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "const String& GetName() const", asMETHODPR(ShaderParameterAnimationInfo, GetName, () const, const String&), asCALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "float GetSpeed() const", asMETHODPR(ShaderParameterAnimationInfo, GetSpeed, () const, float), asCALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "Object@+ GetTarget() const", asMETHODPR(ShaderParameterAnimationInfo, GetTarget, () const, Object*), asCALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "float GetTime() const", asMETHODPR(ShaderParameterAnimationInfo, GetTime, () const, float), asCALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "WrapMode GetWrapMode() const", asMETHODPR(ShaderParameterAnimationInfo, GetWrapMode, () const, WrapMode), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int Refs() const", asMETHODPR(ShaderParameterAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int get_refs() const", asMETHODPR(ShaderParameterAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_RELEASE, "void f()", asMETHODPR(ShaderParameterAnimationInfo, ReleaseRef, (), void), asCALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "void SetSpeed(float)", asMETHODPR(ShaderParameterAnimationInfo, SetSpeed, (float), void), asCALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "bool SetTime(float)", asMETHODPR(ShaderParameterAnimationInfo, SetTime, (float), bool), asCALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "void SetWrapMode(WrapMode)", asMETHODPR(ShaderParameterAnimationInfo, SetWrapMode, (WrapMode), void), asCALL_THISCALL);
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* material, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(Material@+, const String&in, ValueAnimation@+, WrapMode, float)", asFUNCTION(ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_Material_String_ValueAnimation_WrapMode_float), asCALL_CDECL);
    // ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other) | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("ShaderParameterAnimationInfo", asBEHAVE_FACTORY, "ShaderParameterAnimationInfo@+ f(const ShaderParameterAnimationInfo&in)", asFUNCTION(ShaderParameterAnimationInfo_ShaderParameterAnimationInfo_ShaderParameterAnimationInfo), asCALL_CDECL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "bool Update(float)", asMETHODPR(ShaderParameterAnimationInfo, Update, (float), bool), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int WeakRefs() const", asMETHODPR(ShaderParameterAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderParameterAnimationInfo", "int get_weakRefs() const", asMETHODPR(ShaderParameterAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_ADDREF, "void f()", asMETHODPR(ShaderPrecache, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool GetBlockEvents() const", asMETHODPR(ShaderPrecache, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const String& GetCategory() const", asMETHODPR(ShaderPrecache, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const String& get_category() const", asMETHODPR(ShaderPrecache, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "VariantMap& GetEventDataMap() const", asMETHODPR(ShaderPrecache, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "Object@+ GetEventSender() const", asMETHODPR(ShaderPrecache, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ShaderPrecache, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ShaderPrecache, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const VariantMap& GetGlobalVars() const", asMETHODPR(ShaderPrecache, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const VariantMap& get_globalVars() const", asMETHODPR(ShaderPrecache, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ShaderPrecache, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "StringHash GetType() const", asMETHODPR(ShaderPrecache, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "StringHash get_type() const", asMETHODPR(ShaderPrecache, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "const String& GetTypeName() const", asMETHODPR(ShaderPrecache, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "const String& get_typeName() const", asMETHODPR(ShaderPrecache, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasEventHandlers() const", asMETHODPR(ShaderPrecache, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ShaderPrecache, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ShaderPrecache, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "bool IsInstanceOf(StringHash) const", asMETHODPR(ShaderPrecache, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // static void ShaderPrecache::LoadShaders(Graphics* graphics, Deserializer& source) | File: ../Graphics/ShaderPrecache.h
    engine->SetDefaultNamespace("ShaderPrecache");
    engine->RegisterGlobalFunction("void LoadShaders(Graphics@+, Deserializer&)", asFUNCTIONPR(ShaderPrecache::LoadShaders, (Graphics*, Deserializer&), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ShaderPrecache, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderPrecache", "int Refs() const", asMETHODPR(ShaderPrecache, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "int get_refs() const", asMETHODPR(ShaderPrecache, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_RELEASE, "void f()", asMETHODPR(ShaderPrecache, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SendEvent(StringHash)", asMETHODPR(ShaderPrecache, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ShaderPrecache, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SetBlockEvents(bool)", asMETHODPR(ShaderPrecache, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ShaderPrecache, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ShaderPrecache, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // ShaderPrecache::ShaderPrecache(Context* context, const String& fileName) | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectBehaviour("ShaderPrecache", asBEHAVE_FACTORY, "ShaderPrecache@+ f(const String&in)", asFUNCTION(ShaderPrecache_ShaderPrecache_Context_String), asCALL_CDECL);
    // void ShaderPrecache::StoreShaders(ShaderVariation* vs, ShaderVariation* ps) | File: ../Graphics/ShaderPrecache.h
    engine->RegisterObjectMethod("ShaderPrecache", "void StoreShaders(ShaderVariation@+, ShaderVariation@+)", asMETHODPR(ShaderPrecache, StoreShaders, (ShaderVariation*, ShaderVariation*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromAllEvents()", asMETHODPR(ShaderPrecache, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ShaderPrecache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ShaderPrecache, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ShaderPrecache, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ShaderPrecache", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ShaderPrecache, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderPrecache", "int WeakRefs() const", asMETHODPR(ShaderPrecache, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderPrecache", "int get_weakRefs() const", asMETHODPR(ShaderPrecache, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_ADDREF, "void f()", asMETHODPR(ShaderVariation, AddRef, (), void), asCALL_THISCALL);
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "void ClearDataLost()", asMETHODPR(ShaderVariation, ClearDataLost, (), void), asCALL_THISCALL);
    // bool ShaderVariation::Create() | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool Create()", asMETHODPR(ShaderVariation, Create, (), bool), asCALL_THISCALL);
    // const PODVector<unsigned char>& ShaderVariation::GetByteCode() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const String& ShaderVariation::GetCompilerOutput() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetCompilerOutput() const", asMETHODPR(ShaderVariation, GetCompilerOutput, () const, const String&), asCALL_THISCALL);
    // const unsigned* ShaderVariation::GetConstantBufferSizes() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const unsigned*" can not automatically bind
    // const String& ShaderVariation::GetDefines() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetDefines() const", asMETHODPR(ShaderVariation, GetDefines, () const, const String&), asCALL_THISCALL);
    // const String& ShaderVariation::GetDefinesClipPlane() | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetDefinesClipPlane()", asMETHODPR(ShaderVariation, GetDefinesClipPlane, (), const String&), asCALL_THISCALL);
    // unsigned long long ShaderVariation::GetElementHash() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "uint64 GetElementHash() const", asMETHODPR(ShaderVariation, GetElementHash, () const, unsigned long long), asCALL_THISCALL);
    // String ShaderVariation::GetFullName() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "String GetFullName() const", asMETHODPR(ShaderVariation, GetFullName, () const, String), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "uint GetGPUObjectName() const", asMETHODPR(ShaderVariation, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "Graphics@+ GetGraphics() const", asMETHODPR(ShaderVariation, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // const String& ShaderVariation::GetName() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "const String& GetName() const", asMETHODPR(ShaderVariation, GetName, () const, const String&), asCALL_THISCALL);
    // Shader* ShaderVariation::GetOwner() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "Shader@+ GetOwner() const", asMETHODPR(ShaderVariation, GetOwner, () const, Shader*), asCALL_THISCALL);
    // const HashMap<StringHash, ShaderParameter>& ShaderVariation::GetParameters() const | File: ../Graphics/ShaderVariation.h
    // Error: type "const HashMap<StringHash, ShaderParameter>&" can not automatically bind
    // ShaderType ShaderVariation::GetShaderType() const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "ShaderType GetShaderType() const", asMETHODPR(ShaderVariation, GetShaderType, () const, ShaderType), asCALL_THISCALL);
    // bool ShaderVariation::HasParameter(StringHash param) const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasParameter(StringHash) const", asMETHODPR(ShaderVariation, HasParameter, (StringHash) const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasPendingData() const", asMETHODPR(ShaderVariation, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool ShaderVariation::HasTextureUnit(TextureUnit unit) const | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "bool HasTextureUnit(TextureUnit) const", asMETHODPR(ShaderVariation, HasTextureUnit, (TextureUnit) const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "bool IsDataLost() const", asMETHODPR(ShaderVariation, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "bool get_dataLost() const", asMETHODPR(ShaderVariation, IsDataLost, () const, bool), asCALL_THISCALL);
    // void ShaderVariation::OnDeviceLost() override | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void OnDeviceLost()", asMETHODPR(ShaderVariation, OnDeviceLost, (), void), asCALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("ShaderVariation", "void OnDeviceReset()", asMETHODPR(ShaderVariation, OnDeviceReset, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderVariation", "int Refs() const", asMETHODPR(ShaderVariation, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "int get_refs() const", asMETHODPR(ShaderVariation, Refs, () const, int), asCALL_THISCALL);
    // void ShaderVariation::Release() override | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void Release()", asMETHODPR(ShaderVariation, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_RELEASE, "void f()", asMETHODPR(ShaderVariation, ReleaseRef, (), void), asCALL_THISCALL);
    // void ShaderVariation::SetDefines(const String& defines) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void SetDefines(const String&in)", asMETHODPR(ShaderVariation, SetDefines, (const String&), void), asCALL_THISCALL);
    // void ShaderVariation::SetName(const String& name) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectMethod("ShaderVariation", "void SetName(const String&in)", asMETHODPR(ShaderVariation, SetName, (const String&), void), asCALL_THISCALL);
    // ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderVariation", asBEHAVE_FACTORY, "ShaderVariation@+ f(Shader@+, ShaderType)", asFUNCTION(ShaderVariation_ShaderVariation_Shader_ShaderType), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ShaderVariation", "int WeakRefs() const", asMETHODPR(ShaderVariation, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShaderVariation", "int get_weakRefs() const", asMETHODPR(ShaderVariation, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Skeleton", "void ClearBones()", asMETHODPR(Skeleton, ClearBones, (), void), asCALL_THISCALL);
    // void Skeleton::Define(const Skeleton& src) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void Define(const Skeleton&in)", asMETHODPR(Skeleton, Define, (const Skeleton&), void), asCALL_THISCALL);
    // Bone* Skeleton::GetBone(unsigned index) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(uint)", asMETHODPR(Skeleton, GetBone, (unsigned), Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_bones(uint)", asMETHODPR(Skeleton, GetBone, (unsigned), Bone*), asCALL_THISCALL);
    // Bone* Skeleton::GetBone(const String& name) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const String&in)", asMETHODPR(Skeleton, GetBone, (const String&), Bone*), asCALL_THISCALL);
    // Bone* Skeleton::GetBone(const char* name) | File: ../Graphics/Skeleton.h
    // Error: type "const char*" can not automatically bind
    // Bone* Skeleton::GetBone(const StringHash& boneNameHash) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const StringHash&in)", asMETHODPR(Skeleton, GetBone, (const StringHash&), Bone*), asCALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const String& boneName) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(const String&in) const", asMETHODPR(Skeleton, GetBoneIndex, (const String&) const, unsigned), asCALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const StringHash& boneNameHash) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(const StringHash&in) const", asMETHODPR(Skeleton, GetBoneIndex, (const StringHash&) const, unsigned), asCALL_THISCALL);
    // unsigned Skeleton::GetBoneIndex(const Bone* bone) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetBoneIndex(Bone@+) const", asMETHODPR(Skeleton, GetBoneIndex, (const Bone*) const, unsigned), asCALL_THISCALL);
    // Bone* Skeleton::GetBoneParent(const Bone* bone) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBoneParent(Bone@+)", asMETHODPR(Skeleton, GetBoneParent, (const Bone*), Bone*), asCALL_THISCALL);
    // const Vector<Bone>& Skeleton::GetBones() const | File: ../Graphics/Skeleton.h
    // Error: type "const Vector<Bone>&" can not automatically bind
    // Vector<Bone>& Skeleton::GetModifiableBones() | File: ../Graphics/Skeleton.h
    // Error: type "Vector<Bone>&" can not automatically bind
    // unsigned Skeleton::GetNumBones() const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "uint GetNumBones() const", asMETHODPR(Skeleton, GetNumBones, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "uint get_numBones() const", asMETHODPR(Skeleton, GetNumBones, () const, unsigned), asCALL_THISCALL);
    // Bone* Skeleton::GetRootBone() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetRootBone()", asMETHODPR(Skeleton, GetRootBone, (), Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_rootBone()", asMETHODPR(Skeleton, GetRootBone, (), Bone*), asCALL_THISCALL);
    // bool Skeleton::Load(Deserializer& source) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "bool Load(Deserializer&)", asMETHODPR(Skeleton, Load, (Deserializer&), bool), asCALL_THISCALL);
    // void Skeleton::Reset() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void Reset()", asMETHODPR(Skeleton, Reset, (), void), asCALL_THISCALL);
    // void Skeleton::ResetSilent() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void ResetSilent()", asMETHODPR(Skeleton, ResetSilent, (), void), asCALL_THISCALL);
    // bool Skeleton::Save(Serializer& dest) const | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "bool Save(Serializer&) const", asMETHODPR(Skeleton, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // void Skeleton::SetRootBoneIndex(unsigned index) | File: ../Graphics/Skeleton.h
    engine->RegisterObjectMethod("Skeleton", "void SetRootBoneIndex(uint)", asMETHODPR(Skeleton, SetRootBoneIndex, (unsigned), void), asCALL_THISCALL);
    // Skeleton::Skeleton() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_FACTORY, "Skeleton@+ f()", asFUNCTION(Skeleton_Skeleton_void), asCALL_CDECL);
    // Skeleton& Skeleton::operator=(const Skeleton&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Skeleton>(engine, "Skeleton");
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Skeleton
    REGISTER_MANUAL_PART_Skeleton(Skeleton, "Skeleton")
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void AddLight(Light@+)", asMETHODPR(Skybox, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_ADDREF, "void f()", asMETHODPR(Skybox, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void AddVertexLight(Light@+)", asMETHODPR(Skybox, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void AllocateNetworkState()", asMETHODPR(Skybox, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void ApplyAttributes()", asMETHODPR(Skybox, ApplyAttributes, (), void), asCALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void ApplyMaterialList(const String&in = String::EMPTY)", asMETHODPR(Skybox, ApplyMaterialList, (const String&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Skybox, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Skybox, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool GetAnimationEnabled() const", asMETHODPR(Skybox, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_animationEnabled() const", asMETHODPR(Skybox, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttribute(uint) const", asMETHODPR(Skybox, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Variant get_attributes(uint) const", asMETHODPR(Skybox, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttribute(const String&in) const", asMETHODPR(Skybox, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Skybox, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Skybox, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Skybox, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Skybox, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttributeDefault(uint) const", asMETHODPR(Skybox, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Variant get_attributeDefaults(uint) const", asMETHODPR(Skybox, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Skybox, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool GetBlockEvents() const", asMETHODPR(Skybox, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Skybox, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& get_boundingBox() const", asMETHODPR(Skybox, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool GetCastShadows() const", asMETHODPR(Skybox, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_castShadows() const", asMETHODPR(Skybox, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const String& GetCategory() const", asMETHODPR(Skybox, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const String& get_category() const", asMETHODPR(Skybox, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Component@+ GetComponent(StringHash) const", asMETHODPR(Skybox, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Skybox", "float GetDistance() const", asMETHODPR(Skybox, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint8 GetDrawableFlags() const", asMETHODPR(Skybox, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetDrawDistance() const", asMETHODPR(Skybox, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_drawDistance() const", asMETHODPR(Skybox, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "VariantMap& GetEventDataMap() const", asMETHODPR(Skybox, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "Object@+ GetEventSender() const", asMETHODPR(Skybox, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Light@+ GetFirstLight() const", asMETHODPR(Skybox, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Skybox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Skybox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const VariantMap& GetGlobalVars() const", asMETHODPR(Skybox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const VariantMap& get_globalVars() const", asMETHODPR(Skybox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "uint GetID() const", asMETHODPR(Skybox, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_id() const", asMETHODPR(Skybox, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Skybox, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetLightMask() const", asMETHODPR(Skybox, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_lightMask() const", asMETHODPR(Skybox, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Array<Light@>@ GetLights() const", asFUNCTION(Skybox_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetLodBias() const", asMETHODPR(Skybox, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_lodBias() const", asMETHODPR(Skybox, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetLodDistance() const", asMETHODPR(Skybox, GetLodDistance, () const, float), asCALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Skybox, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Material@+ GetMaterial() const", asMETHODPR(Skybox, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ get_material() const", asMETHODPR(Skybox, GetMaterial, () const, Material*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Material@+ GetMaterial(uint) const", asMETHODPR(Skybox, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ get_materials(uint) const", asMETHODPR(Skybox, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "const ResourceRefList& GetMaterialsAttr() const", asMETHODPR(Skybox, GetMaterialsAttr, () const, const ResourceRefList&), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetMaxLights() const", asMETHODPR(Skybox, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_maxLights() const", asMETHODPR(Skybox, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetMaxZ() const", asMETHODPR(Skybox, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetMinZ() const", asMETHODPR(Skybox, GetMinZ, () const, float), asCALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "Model@+ GetModel() const", asMETHODPR(Skybox, GetModel, () const, Model*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Model@+ get_model() const", asMETHODPR(Skybox, GetModel, () const, Model*), asCALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "ResourceRef GetModelAttr() const", asMETHODPR(Skybox, GetModelAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Node@+ GetNode() const", asMETHODPR(Skybox, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Node@+ get_node() const", asMETHODPR(Skybox, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumAttributes() const", asMETHODPR(Skybox, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_numAttributes() const", asMETHODPR(Skybox, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumGeometries() const", asMETHODPR(Skybox, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_numGeometries() const", asMETHODPR(Skybox, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumNetworkAttributes() const", asMETHODPR(Skybox, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetNumOccluderTriangles()", asMETHODPR(Skybox, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Skybox, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Skybox, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Skybox, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "uint GetOcclusionLodLevel() const", asMETHODPR(Skybox, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_occlusionLodLevel() const", asMETHODPR(Skybox, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "Scene@+ GetScene() const", asMETHODPR(Skybox, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetShadowDistance() const", asMETHODPR(Skybox, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "float get_shadowDistance() const", asMETHODPR(Skybox, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetShadowMask() const", asMETHODPR(Skybox, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_shadowMask() const", asMETHODPR(Skybox, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "float GetSortValue() const", asMETHODPR(Skybox, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Skybox, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "StringHash GetType() const", asMETHODPR(Skybox, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "StringHash get_type() const", asMETHODPR(Skybox, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "const String& GetTypeName() const", asMETHODPR(Skybox, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const String& get_typeName() const", asMETHODPR(Skybox, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Skybox, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Skybox_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetViewMask() const", asMETHODPR(Skybox, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_viewMask() const", asMETHODPR(Skybox, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Skybox, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Skybox, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "Zone@+ GetZone() const", asMETHODPR(Skybox, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Zone@+ get_zone() const", asMETHODPR(Skybox, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "uint GetZoneMask() const", asMETHODPR(Skybox, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_zoneMask() const", asMETHODPR(Skybox, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool HasBasePass(uint) const", asMETHODPR(Skybox, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasEventHandlers() const", asMETHODPR(Skybox, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Skybox, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Skybox, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsEnabled() const", asMETHODPR(Skybox, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_enabled() const", asMETHODPR(Skybox, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsEnabledEffective() const", asMETHODPR(Skybox, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_enabledEffective() const", asMETHODPR(Skybox, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool IsInside(const Vector3&in) const", asMETHODPR(Skybox, IsInside, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool IsInsideLocal(const Vector3&in) const", asMETHODPR(Skybox, IsInsideLocal, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "bool IsInstanceOf(StringHash) const", asMETHODPR(Skybox, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView() const", asMETHODPR(Skybox, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_inView() const", asMETHODPR(Skybox, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView(Camera@+) const", asMETHODPR(Skybox, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Skybox, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsOccludee() const", asMETHODPR(Skybox, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_occludee() const", asMETHODPR(Skybox, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsOccluder() const", asMETHODPR(Skybox, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_occluder() const", asMETHODPR(Skybox, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool IsReplicated() const", asMETHODPR(Skybox, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_replicated() const", asMETHODPR(Skybox, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool IsTemporary() const", asMETHODPR(Skybox, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool get_temporary() const", asMETHODPR(Skybox, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "bool IsZoneDirty() const", asMETHODPR(Skybox, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void LimitLights()", asMETHODPR(Skybox, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void LimitVertexLights(bool)", asMETHODPR(Skybox, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool Load(Deserializer&)", asMETHODPR(Skybox, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Skybox, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "bool LoadXML(const XMLElement&in)", asMETHODPR(Skybox, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkForUpdate()", asMETHODPR(Skybox, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkInView(const FrameInfo&in)", asMETHODPR(Skybox, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void MarkInView(uint)", asMETHODPR(Skybox, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void MarkNetworkUpdate()", asMETHODPR(Skybox, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Skybox, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Skybox, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Skybox, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void OnSetEnabled()", asMETHODPR(Skybox, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void PrepareNetworkUpdate()", asMETHODPR(Skybox, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void Skybox::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/Skybox.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Skybox, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Skybox, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Skybox", "int Refs() const", asMETHODPR(Skybox, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "int get_refs() const", asMETHODPR(Skybox, Refs, () const, int), asCALL_THISCALL);
    // static void Skybox::RegisterObject(Context* context) | File: ../Graphics/Skybox.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_RELEASE, "void f()", asMETHODPR(Skybox, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void Remove()", asMETHODPR(Skybox, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Skybox, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveInstanceDefault()", asMETHODPR(Skybox, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void RemoveObjectAnimation()", asMETHODPR(Skybox, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void ResetToDefault()", asMETHODPR(Skybox, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool Save(Serializer&) const", asMETHODPR(Skybox, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SaveDefaultAttributes() const", asMETHODPR(Skybox, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool SaveJSON(JSONValue&) const", asMETHODPR(Skybox, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "bool SaveXML(XMLElement&) const", asMETHODPR(Skybox, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SendEvent(StringHash)", asMETHODPR(Skybox, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Skybox, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAnimationEnabled(bool)", asMETHODPR(Skybox, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_animationEnabled(bool)", asMETHODPR(Skybox, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAnimationTime(float)", asMETHODPR(Skybox, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Skybox, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Skybox, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Skybox, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Skybox, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Skybox, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Skybox, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Skybox, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetBasePass(uint)", asMETHODPR(Skybox, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SetBlockEvents(bool)", asMETHODPR(Skybox, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetCastShadows(bool)", asMETHODPR(Skybox, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_castShadows(bool)", asMETHODPR(Skybox, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetDrawDistance(float)", asMETHODPR(Skybox, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_drawDistance(float)", asMETHODPR(Skybox, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Skybox", "void SetEnabled(bool)", asMETHODPR(Skybox, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_enabled(bool)", asMETHODPR(Skybox, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Skybox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Skybox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetInstanceDefault(bool)", asMETHODPR(Skybox, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Skybox, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetLightMask(uint)", asMETHODPR(Skybox, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_lightMask(uint)", asMETHODPR(Skybox, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetLodBias(float)", asMETHODPR(Skybox, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_lodBias(float)", asMETHODPR(Skybox, SetLodBias, (float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetMaterial(Material@+)", asMETHODPR(Skybox, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_material(Material@+)", asMETHODPR(Skybox, SetMaterial, (Material*), void), asCALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "bool SetMaterial(uint, Material@+)", asMETHODPR(Skybox, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool set_materials(uint, Material@+)", asMETHODPR(Skybox, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetMaterialsAttr(const ResourceRefList&in)", asMETHODPR(Skybox, SetMaterialsAttr, (const ResourceRefList&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetMaxLights(uint)", asMETHODPR(Skybox, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_maxLights(uint)", asMETHODPR(Skybox, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetMinMaxZ(float, float)", asMETHODPR(Skybox, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetModelAttr(const ResourceRef&in)", asMETHODPR(Skybox, SetModelAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Skybox, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Skybox, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Skybox", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Skybox, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetOccludee(bool)", asMETHODPR(Skybox, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occludee(bool)", asMETHODPR(Skybox, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetOccluder(bool)", asMETHODPR(Skybox, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occluder(bool)", asMETHODPR(Skybox, SetOccluder, (bool), void), asCALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("Skybox", "void SetOcclusionLodLevel(uint)", asMETHODPR(Skybox, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_occlusionLodLevel(uint)", asMETHODPR(Skybox, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetShadowDistance(float)", asMETHODPR(Skybox, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_shadowDistance(float)", asMETHODPR(Skybox, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetShadowMask(uint)", asMETHODPR(Skybox, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_shadowMask(uint)", asMETHODPR(Skybox, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetSortValue(float)", asMETHODPR(Skybox, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void SetTemporary(bool)", asMETHODPR(Skybox, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_temporary(bool)", asMETHODPR(Skybox, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetViewMask(uint)", asMETHODPR(Skybox, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_viewMask(uint)", asMETHODPR(Skybox, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetZone(Zone@+, bool = false)", asMETHODPR(Skybox, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void SetZoneMask(uint)", asMETHODPR(Skybox, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_zoneMask(uint)", asMETHODPR(Skybox, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // explicit Skybox::Skybox(Context* context) | File: ../Graphics/Skybox.h
    engine->RegisterObjectBehaviour("Skybox", asBEHAVE_FACTORY, "Skybox@+ f()", asFUNCTION(Skybox_Skybox_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromAllEvents()", asMETHODPR(Skybox, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Skybox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Skybox, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Skybox, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Skybox", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Skybox, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void Update(const FrameInfo&in)", asMETHODPR(Skybox, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void Skybox::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/Skybox.h
    engine->RegisterObjectMethod("Skybox", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Skybox, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Skybox", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Skybox, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Skybox", "int WeakRefs() const", asMETHODPR(Skybox, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "int get_weakRefs() const", asMETHODPR(Skybox, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Skybox, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Skybox, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Skybox", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Skybox, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Slider", "void AddChild(UIElement@+)", asMETHODPR(Slider, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_ADDREF, "void f()", asMETHODPR(Slider, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTag(const String&in)", asMETHODPR(Slider, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Slider, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AddTags(Array<String>@+)", asFUNCTION(Slider_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void AdjustScissor(IntRect&)", asMETHODPR(Slider, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void AllocateNetworkState()", asMETHODPR(Slider, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void ApplyAttributes()", asMETHODPR(Slider, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void BringToFront()", asMETHODPR(Slider, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Slider::ChangeValue(float delta) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void ChangeValue(float)", asMETHODPR(Slider, ChangeValue, (float), void), asCALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Slider, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void DisableLayoutUpdate()", asMETHODPR(Slider, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Slider, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void EnableLayoutUpdate()", asMETHODPR(Slider, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Slider, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint FindChild(UIElement@+) const", asMETHODPR(Slider, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool GetAnimationEnabled() const", asMETHODPR(Slider, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_animationEnabled() const", asMETHODPR(Slider, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const String& GetAppliedStyle() const", asMETHODPR(Slider, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_style() const", asMETHODPR(Slider, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttribute(uint) const", asMETHODPR(Slider, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Variant get_attributes(uint) const", asMETHODPR(Slider, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttribute(const String&in) const", asMETHODPR(Slider, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Slider, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Slider, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Slider, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Slider, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttributeDefault(uint) const", asMETHODPR(Slider, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Variant get_attributeDefaults(uint) const", asMETHODPR(Slider, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Slider, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "BlendMode GetBlendMode() const", asMETHODPR(Slider, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "BlendMode get_blendMode() const", asMETHODPR(Slider, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool GetBlockEvents() const", asMETHODPR(Slider, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetBorder() const", asMETHODPR(Slider, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_border() const", asMETHODPR(Slider, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetBringToBack() const", asMETHODPR(Slider, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_bringToBack() const", asMETHODPR(Slider, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetBringToFront() const", asMETHODPR(Slider, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_bringToFront() const", asMETHODPR(Slider, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const String& GetCategory() const", asMETHODPR(Slider, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_category() const", asMETHODPR(Slider, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(uint) const", asMETHODPR(Slider, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_children(uint) const", asMETHODPR(Slider, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Slider, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Slider, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetChildOffset() const", asMETHODPR(Slider, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_childOffset() const", asMETHODPR(Slider, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Slider_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Slider_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Slider_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetClipBorder() const", asMETHODPR(Slider, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_clipBorder() const", asMETHODPR(Slider, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetClipChildren() const", asMETHODPR(Slider, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_clipChildren() const", asMETHODPR(Slider, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetColor(Corner) const", asMETHODPR(Slider, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Color& get_colors(Corner) const", asMETHODPR(Slider, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetColorAttr() const", asMETHODPR(Slider, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntRect GetCombinedScreenRect()", asMETHODPR(Slider, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "IntRect get_combinedScreenRect()", asMETHODPR(Slider, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Slider, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Color& GetDerivedColor() const", asMETHODPR(Slider, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "float GetDerivedOpacity() const", asMETHODPR(Slider, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_derivedOpacity() const", asMETHODPR(Slider, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetDisabledOffset() const", asMETHODPR(Slider, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_disabledOffset() const", asMETHODPR(Slider, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Slider, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Slider, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint GetDragButtonCount() const", asMETHODPR(Slider, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_dragButtonCount() const", asMETHODPR(Slider, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Slider, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Slider, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Slider, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetElementEventSender() const", asMETHODPR(Slider, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetEnableAnchor() const", asMETHODPR(Slider, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enableAnchor() const", asMETHODPR(Slider, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "VariantMap& GetEventDataMap() const", asMETHODPR(Slider, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "Object@+ GetEventSender() const", asMETHODPR(Slider, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "FocusMode GetFocusMode() const", asMETHODPR(Slider, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "FocusMode get_focusMode() const", asMETHODPR(Slider, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Slider, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Slider, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const VariantMap& GetGlobalVars() const", asMETHODPR(Slider, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const VariantMap& get_globalVars() const", asMETHODPR(Slider, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetHeight() const", asMETHODPR(Slider, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_height() const", asMETHODPR(Slider, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Slider, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Slider, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetHoverOffset() const", asMETHODPR(Slider, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_hoverOffset() const", asMETHODPR(Slider, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetImageBorder() const", asMETHODPR(Slider, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_imageBorder() const", asMETHODPR(Slider, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetImageRect() const", asMETHODPR(Slider, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_imageRect() const", asMETHODPR(Slider, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndent() const", asMETHODPR(Slider, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indent() const", asMETHODPR(Slider, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndentSpacing() const", asMETHODPR(Slider, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indentSpacing() const", asMETHODPR(Slider, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetIndentWidth() const", asMETHODPR(Slider, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_indentWidth() const", asMETHODPR(Slider, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Slider, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // BorderImage* Slider::GetKnob() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "BorderImage@+ GetKnob() const", asMETHODPR(Slider, GetKnob, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "BorderImage@+ get_knob() const", asMETHODPR(Slider, GetKnob, () const, BorderImage*), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntRect& GetLayoutBorder() const", asMETHODPR(Slider, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntRect& get_layoutBorder() const", asMETHODPR(Slider, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetLayoutElementMaxSize() const", asMETHODPR(Slider, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Slider, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Slider, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "LayoutMode GetLayoutMode() const", asMETHODPR(Slider, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "LayoutMode get_layoutMode() const", asMETHODPR(Slider, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetLayoutSpacing() const", asMETHODPR(Slider, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_layoutSpacing() const", asMETHODPR(Slider, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "Material@+ GetMaterial() const", asMETHODPR(Slider, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Material@+ get_material() const", asMETHODPR(Slider, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetMaterialAttr() const", asMETHODPR(Slider, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetMaxAnchor() const", asMETHODPR(Slider, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_maxAnchor() const", asMETHODPR(Slider, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMaxHeight() const", asMETHODPR(Slider, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_maxHeight() const", asMETHODPR(Slider, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMaxOffset() const", asMETHODPR(Slider, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_maxOffset() const", asMETHODPR(Slider, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMaxSize() const", asMETHODPR(Slider, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_maxSize() const", asMETHODPR(Slider, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMaxWidth() const", asMETHODPR(Slider, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_maxWidth() const", asMETHODPR(Slider, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetMinAnchor() const", asMETHODPR(Slider, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_minAnchor() const", asMETHODPR(Slider, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMinHeight() const", asMETHODPR(Slider, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_minHeight() const", asMETHODPR(Slider, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMinOffset() const", asMETHODPR(Slider, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_minOffset() const", asMETHODPR(Slider, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetMinSize() const", asMETHODPR(Slider, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_minSize() const", asMETHODPR(Slider, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetMinWidth() const", asMETHODPR(Slider, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_minWidth() const", asMETHODPR(Slider, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const String& GetName() const", asMETHODPR(Slider, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_name() const", asMETHODPR(Slider, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "uint GetNumAttributes() const", asMETHODPR(Slider, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_numAttributes() const", asMETHODPR(Slider, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "uint GetNumChildren(bool = false) const", asMETHODPR(Slider, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "uint get_numChildren(bool = false) const", asMETHODPR(Slider, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "uint GetNumNetworkAttributes() const", asMETHODPR(Slider, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Slider, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Slider, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Slider, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "float GetOpacity() const", asMETHODPR(Slider, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_opacity() const", asMETHODPR(Slider, GetOpacity, () const, float), asCALL_THISCALL);
    // Orientation Slider::GetOrientation() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "Orientation GetOrientation() const", asMETHODPR(Slider, GetOrientation, () const, Orientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Orientation get_orientation() const", asMETHODPR(Slider, GetOrientation, () const, Orientation), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetParent() const", asMETHODPR(Slider, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_parent() const", asMETHODPR(Slider, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Vector2& GetPivot() const", asMETHODPR(Slider, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const Vector2& get_pivot() const", asMETHODPR(Slider, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetPosition() const", asMETHODPR(Slider, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_position() const", asMETHODPR(Slider, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetPriority() const", asMETHODPR(Slider, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_priority() const", asMETHODPR(Slider, GetPriority, () const, int), asCALL_THISCALL);
    // float Slider::GetRange() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetRange() const", asMETHODPR(Slider, GetRange, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_range() const", asMETHODPR(Slider, GetRange, () const, float), asCALL_THISCALL);
    // float Slider::GetRepeatRate() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetRepeatRate() const", asMETHODPR(Slider, GetRepeatRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_repeatRate() const", asMETHODPR(Slider, GetRepeatRate, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ GetRoot() const", asMETHODPR(Slider, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "UIElement@+ get_root() const", asMETHODPR(Slider, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetScreenPosition() const", asMETHODPR(Slider, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_screenPosition() const", asMETHODPR(Slider, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const IntVector2& GetSize() const", asMETHODPR(Slider, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const IntVector2& get_size() const", asMETHODPR(Slider, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetSortChildren() const", asMETHODPR(Slider, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_sortChildren() const", asMETHODPR(Slider, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Slider, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "Array<String>@ GetTags() const", asFUNCTION(Slider_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Slider", "Array<String>@ get_tags() const", asFUNCTION(Slider_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "Texture@+ GetTexture() const", asMETHODPR(Slider, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Texture@+ get_texture() const", asMETHODPR(Slider, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "ResourceRef GetTextureAttr() const", asMETHODPR(Slider, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "TraversalMode GetTraversalMode() const", asMETHODPR(Slider, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "TraversalMode get_traversalMode() const", asMETHODPR(Slider, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "StringHash GetType() const", asMETHODPR(Slider, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "StringHash get_type() const", asMETHODPR(Slider, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "const String& GetTypeName() const", asMETHODPR(Slider, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "const String& get_typeName() const", asMETHODPR(Slider, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool GetUseDerivedOpacity() const", asMETHODPR(Slider, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_useDerivedOpacity() const", asMETHODPR(Slider, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // float Slider::GetValue() const | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "float GetValue() const", asMETHODPR(Slider, GetValue, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_value() const", asMETHODPR(Slider, GetValue, () const, float), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Slider, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "const VariantMap& GetVars() const", asMETHODPR(Slider, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Slider, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Slider, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "int GetWidth() const", asMETHODPR(Slider, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_width() const", asMETHODPR(Slider, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasColorGradient() const", asMETHODPR(Slider, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_colorGradient() const", asMETHODPR(Slider, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasEventHandlers() const", asMETHODPR(Slider, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasFocus() const", asMETHODPR(Slider, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_focus() const", asMETHODPR(Slider, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Slider, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Slider, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool HasTag(const String&in) const", asMETHODPR(Slider, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void InsertChild(uint, UIElement@+)", asMETHODPR(Slider, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsChildOf(UIElement@+) const", asMETHODPR(Slider, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEditable() const", asMETHODPR(Slider, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_editable() const", asMETHODPR(Slider, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsElementEventSender() const", asMETHODPR(Slider, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_elementEventSender() const", asMETHODPR(Slider, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEnabled() const", asMETHODPR(Slider, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enabled() const", asMETHODPR(Slider, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsEnabledSelf() const", asMETHODPR(Slider, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_enabledSelf() const", asMETHODPR(Slider, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedHeight() const", asMETHODPR(Slider, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedHeight() const", asMETHODPR(Slider, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedSize() const", asMETHODPR(Slider, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedSize() const", asMETHODPR(Slider, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsFixedWidth() const", asMETHODPR(Slider, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_fixedWidth() const", asMETHODPR(Slider, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsHovering() const", asMETHODPR(Slider, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_hovering() const", asMETHODPR(Slider, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInside(IntVector2, bool)", asMETHODPR(Slider, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Slider, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "bool IsInstanceOf(StringHash) const", asMETHODPR(Slider, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsInternal() const", asMETHODPR(Slider, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_internal() const", asMETHODPR(Slider, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsSelected() const", asMETHODPR(Slider, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_selected() const", asMETHODPR(Slider, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool IsTemporary() const", asMETHODPR(Slider, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_temporary() const", asMETHODPR(Slider, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "bool IsTiled() const", asMETHODPR(Slider, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_tiled() const", asMETHODPR(Slider, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsVisible() const", asMETHODPR(Slider, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_visible() const", asMETHODPR(Slider, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsVisibleEffective() const", asMETHODPR(Slider, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool get_visibleEffective() const", asMETHODPR(Slider, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsWheelHandler() const", asMETHODPR(Slider, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Slider, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool Load(Deserializer&)", asMETHODPR(Slider, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Slider, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Slider, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(const XMLElement&in)", asMETHODPR(Slider, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Slider, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool LoadXML(Deserializer&)", asMETHODPR(Slider, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void MarkNetworkUpdate()", asMETHODPR(Slider, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void Slider::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Slider, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Slider::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Slider, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Slider, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Slider::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Slider, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Slider, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Slider, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Slider, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // void Slider::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Slider, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Slider::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Slider, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Slider, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Slider, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // void Slider::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Slider, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnIndentSet()", asMETHODPR(Slider, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Slider, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Slider, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void Slider::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Slider, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Slider, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnSetEditable()", asMETHODPR(Slider, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnTextInput(const String&in)", asMETHODPR(Slider, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Slider, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Slider, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Slider, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Slider", "int Refs() const", asMETHODPR(Slider, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_refs() const", asMETHODPR(Slider, Refs, () const, int), asCALL_THISCALL);
    // static void Slider::RegisterObject(Context* context) | File: ../UI/Slider.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_RELEASE, "void f()", asMETHODPR(Slider, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void Remove()", asMETHODPR(Slider, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveAllChildren()", asMETHODPR(Slider, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveAllTags()", asMETHODPR(Slider, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Slider, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Slider, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void RemoveChildAtIndex(uint)", asMETHODPR(Slider, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void RemoveInstanceDefault()", asMETHODPR(Slider, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void RemoveObjectAnimation()", asMETHODPR(Slider, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool RemoveTag(const String&in)", asMETHODPR(Slider, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void ResetDeepEnabled()", asMETHODPR(Slider, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void ResetToDefault()", asMETHODPR(Slider, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool Save(Serializer&) const", asMETHODPR(Slider, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SaveDefaultAttributes() const", asMETHODPR(Slider, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "bool SaveJSON(JSONValue&) const", asMETHODPR(Slider, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SaveXML(XMLElement&) const", asMETHODPR(Slider, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Slider, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Slider, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SendEvent(StringHash)", asMETHODPR(Slider, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Slider, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Slider, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAnimationEnabled(bool)", asMETHODPR(Slider, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_animationEnabled(bool)", asMETHODPR(Slider, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAnimationTime(float)", asMETHODPR(Slider, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Slider, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Slider, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Slider, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Slider, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Slider, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Slider, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Slider, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetBlendMode(BlendMode)", asMETHODPR(Slider, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_blendMode(BlendMode)", asMETHODPR(Slider, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SetBlockEvents(bool)", asMETHODPR(Slider, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetBorder(const IntRect&in)", asMETHODPR(Slider, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_border(const IntRect&in)", asMETHODPR(Slider, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetBringToBack(bool)", asMETHODPR(Slider, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_bringToBack(bool)", asMETHODPR(Slider, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetBringToFront(bool)", asMETHODPR(Slider, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_bringToFront(bool)", asMETHODPR(Slider, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Slider, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetClipBorder(const IntRect&in)", asMETHODPR(Slider, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_clipBorder(const IntRect&in)", asMETHODPR(Slider, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetClipChildren(bool)", asMETHODPR(Slider, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_clipChildren(bool)", asMETHODPR(Slider, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetColor(const Color&in)", asMETHODPR(Slider, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_color(const Color&in)", asMETHODPR(Slider, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetColor(Corner, const Color&in)", asMETHODPR(Slider, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_colors(Corner, const Color&in)", asMETHODPR(Slider, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDeepEnabled(bool)", asMETHODPR(Slider, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Slider, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Slider, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(Slider, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(Slider, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetDisabledOffset(int, int)", asMETHODPR(Slider, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Slider, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Slider, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEditable(bool)", asMETHODPR(Slider, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_editable(bool)", asMETHODPR(Slider, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetElementEventSender(bool)", asMETHODPR(Slider, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_elementEventSender(bool)", asMETHODPR(Slider, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnableAnchor(bool)", asMETHODPR(Slider, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_enableAnchor(bool)", asMETHODPR(Slider, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnabled(bool)", asMETHODPR(Slider, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_enabled(bool)", asMETHODPR(Slider, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetEnabledRecursive(bool)", asMETHODPR(Slider, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedHeight(int)", asMETHODPR(Slider, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Slider, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedSize(int, int)", asMETHODPR(Slider, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFixedWidth(int)", asMETHODPR(Slider, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFocus(bool)", asMETHODPR(Slider, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_focus(bool)", asMETHODPR(Slider, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetFocusMode(FocusMode)", asMETHODPR(Slider, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_focusMode(FocusMode)", asMETHODPR(Slider, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetFullImageRect()", asMETHODPR(Slider, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Slider, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Slider, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHeight(int)", asMETHODPR(Slider, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_height(int)", asMETHODPR(Slider, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Slider, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Slider, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetHovering(bool)", asMETHODPR(Slider, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(Slider, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(Slider, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetHoverOffset(int, int)", asMETHODPR(Slider, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetImageBorder(const IntRect&in)", asMETHODPR(Slider, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_imageBorder(const IntRect&in)", asMETHODPR(Slider, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetImageRect(const IntRect&in)", asMETHODPR(Slider, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_imageRect(const IntRect&in)", asMETHODPR(Slider, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetIndent(int)", asMETHODPR(Slider, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_indent(int)", asMETHODPR(Slider, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetIndentSpacing(int)", asMETHODPR(Slider, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_indentSpacing(int)", asMETHODPR(Slider, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetInstanceDefault(bool)", asMETHODPR(Slider, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Slider, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetInternal(bool)", asMETHODPR(Slider, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_internal(bool)", asMETHODPR(Slider, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Slider, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Slider, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Slider, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Slider, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Slider, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutMode(LayoutMode)", asMETHODPR(Slider, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutMode(LayoutMode)", asMETHODPR(Slider, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetLayoutSpacing(int)", asMETHODPR(Slider, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_layoutSpacing(int)", asMETHODPR(Slider, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetMaterial(Material@+)", asMETHODPR(Slider, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_material(Material@+)", asMETHODPR(Slider, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Slider, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Slider, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Slider, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxAnchor(float, float)", asMETHODPR(Slider, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxHeight(int)", asMETHODPR(Slider, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxHeight(int)", asMETHODPR(Slider, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Slider, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Slider, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Slider, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxSize(const IntVector2&in)", asMETHODPR(Slider, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxSize(int, int)", asMETHODPR(Slider, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMaxWidth(int)", asMETHODPR(Slider, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_maxWidth(int)", asMETHODPR(Slider, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Slider, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minAnchor(const Vector2&in)", asMETHODPR(Slider, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinAnchor(float, float)", asMETHODPR(Slider, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinHeight(int)", asMETHODPR(Slider, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minHeight(int)", asMETHODPR(Slider, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Slider, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minOffset(const IntVector2&in)", asMETHODPR(Slider, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinSize(const IntVector2&in)", asMETHODPR(Slider, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minSize(const IntVector2&in)", asMETHODPR(Slider, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinSize(int, int)", asMETHODPR(Slider, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetMinWidth(int)", asMETHODPR(Slider, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_minWidth(int)", asMETHODPR(Slider, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetName(const String&in)", asMETHODPR(Slider, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_name(const String&in)", asMETHODPR(Slider, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Slider, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Slider, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Slider", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Slider, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetOpacity(float)", asMETHODPR(Slider, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_opacity(float)", asMETHODPR(Slider, SetOpacity, (float), void), asCALL_THISCALL);
    // void Slider::SetOrientation(Orientation orientation) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetOrientation(Orientation)", asMETHODPR(Slider, SetOrientation, (Orientation), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_orientation(Orientation)", asMETHODPR(Slider, SetOrientation, (Orientation), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Slider, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPivot(const Vector2&in)", asMETHODPR(Slider, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_pivot(const Vector2&in)", asMETHODPR(Slider, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPivot(float, float)", asMETHODPR(Slider, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPosition(const IntVector2&in)", asMETHODPR(Slider, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_position(const IntVector2&in)", asMETHODPR(Slider, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPosition(int, int)", asMETHODPR(Slider, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetPriority(int)", asMETHODPR(Slider, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_priority(int)", asMETHODPR(Slider, SetPriority, (int), void), asCALL_THISCALL);
    // void Slider::SetRange(float range) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetRange(float)", asMETHODPR(Slider, SetRange, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_range(float)", asMETHODPR(Slider, SetRange, (float), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Slider, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Slider::SetRepeatRate(float rate) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetRepeatRate(float)", asMETHODPR(Slider, SetRepeatRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_repeatRate(float)", asMETHODPR(Slider, SetRepeatRate, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSelected(bool)", asMETHODPR(Slider, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_selected(bool)", asMETHODPR(Slider, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSize(const IntVector2&in)", asMETHODPR(Slider, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_size(const IntVector2&in)", asMETHODPR(Slider, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSize(int, int)", asMETHODPR(Slider, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetSortChildren(bool)", asMETHODPR(Slider, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_sortChildren(bool)", asMETHODPR(Slider, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Slider, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyle(const XMLElement&in)", asMETHODPR(Slider, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Slider, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetTags(Array<String>@+)", asFUNCTION(Slider_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void SetTemporary(bool)", asMETHODPR(Slider, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_temporary(bool)", asMETHODPR(Slider, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTexture(Texture@+)", asMETHODPR(Slider, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_texture(Texture@+)", asMETHODPR(Slider, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Slider, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Slider", "void SetTiled(bool)", asMETHODPR(Slider, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_tiled(bool)", asMETHODPR(Slider, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetTraversalMode(TraversalMode)", asMETHODPR(Slider, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_traversalMode(TraversalMode)", asMETHODPR(Slider, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetUseDerivedOpacity(bool)", asMETHODPR(Slider, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_useDerivedOpacity(bool)", asMETHODPR(Slider, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void Slider::SetValue(float value) | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void SetValue(float)", asMETHODPR(Slider, SetValue, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_value(float)", asMETHODPR(Slider, SetValue, (float), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Slider, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Slider, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Slider, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetVisible(bool)", asMETHODPR(Slider, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_visible(bool)", asMETHODPR(Slider, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SetWidth(int)", asMETHODPR(Slider, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_width(int)", asMETHODPR(Slider, SetWidth, (int), void), asCALL_THISCALL);
    // explicit Slider::Slider(Context* context) | File: ../UI/Slider.h
    engine->RegisterObjectBehaviour("Slider", asBEHAVE_FACTORY, "Slider@+ f()", asFUNCTION(Slider_Slider_Context), asCALL_CDECL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void SortChildren()", asMETHODPR(Slider, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromAllEvents()", asMETHODPR(Slider, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Slider_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Slider, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Slider, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Slider", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Slider, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Slider::Update(float timeStep) override | File: ../UI/Slider.h
    engine->RegisterObjectMethod("Slider", "void Update(float)", asMETHODPR(Slider, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Slider", "void UpdateLayout()", asMETHODPR(Slider, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Slider", "int WeakRefs() const", asMETHODPR(Slider, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "int get_weakRefs() const", asMETHODPR(Slider, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Slider, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Slider, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Slider", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Slider, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_ADDREF, "void f()", asMETHODPR(SmoothedTransform, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void AllocateNetworkState()", asMETHODPR(SmoothedTransform, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void ApplyAttributes()", asMETHODPR(SmoothedTransform, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(SmoothedTransform, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetAnimationEnabled() const", asMETHODPR(SmoothedTransform, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_animationEnabled() const", asMETHODPR(SmoothedTransform, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttribute(uint) const", asMETHODPR(SmoothedTransform, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Variant get_attributes(uint) const", asMETHODPR(SmoothedTransform, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttribute(const String&in) const", asMETHODPR(SmoothedTransform, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(SmoothedTransform, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(SmoothedTransform, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(SmoothedTransform, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(SmoothedTransform, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttributeDefault(uint) const", asMETHODPR(SmoothedTransform, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Variant get_attributeDefaults(uint) const", asMETHODPR(SmoothedTransform, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(SmoothedTransform, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetBlockEvents() const", asMETHODPR(SmoothedTransform, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const String& GetCategory() const", asMETHODPR(SmoothedTransform, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const String& get_category() const", asMETHODPR(SmoothedTransform, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Component@+ GetComponent(StringHash) const", asMETHODPR(SmoothedTransform, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("SmoothedTransform", "VariantMap& GetEventDataMap() const", asMETHODPR(SmoothedTransform, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "Object@+ GetEventSender() const", asMETHODPR(SmoothedTransform, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SmoothedTransform, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SmoothedTransform, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const VariantMap& GetGlobalVars() const", asMETHODPR(SmoothedTransform, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const VariantMap& get_globalVars() const", asMETHODPR(SmoothedTransform, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetID() const", asMETHODPR(SmoothedTransform, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "uint get_id() const", asMETHODPR(SmoothedTransform, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(SmoothedTransform, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Node@+ GetNode() const", asMETHODPR(SmoothedTransform, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Node@+ get_node() const", asMETHODPR(SmoothedTransform, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetNumAttributes() const", asMETHODPR(SmoothedTransform, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "uint get_numAttributes() const", asMETHODPR(SmoothedTransform, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "uint GetNumNetworkAttributes() const", asMETHODPR(SmoothedTransform, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(SmoothedTransform, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(SmoothedTransform, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(SmoothedTransform, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "Scene@+ GetScene() const", asMETHODPR(SmoothedTransform, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SmoothedTransform, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const Vector3& SmoothedTransform::GetTargetPosition() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Vector3& GetTargetPosition() const", asMETHODPR(SmoothedTransform, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Vector3& get_targetPosition() const", asMETHODPR(SmoothedTransform, GetTargetPosition, () const, const Vector3&), asCALL_THISCALL);
    // const Quaternion& SmoothedTransform::GetTargetRotation() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "const Quaternion& GetTargetRotation() const", asMETHODPR(SmoothedTransform, GetTargetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Quaternion& get_targetRotation() const", asMETHODPR(SmoothedTransform, GetTargetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // Vector3 SmoothedTransform::GetTargetWorldPosition() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "Vector3 GetTargetWorldPosition() const", asMETHODPR(SmoothedTransform, GetTargetWorldPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Vector3 get_targetWorldPosition() const", asMETHODPR(SmoothedTransform, GetTargetWorldPosition, () const, Vector3), asCALL_THISCALL);
    // Quaternion SmoothedTransform::GetTargetWorldRotation() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "Quaternion GetTargetWorldRotation() const", asMETHODPR(SmoothedTransform, GetTargetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Quaternion get_targetWorldRotation() const", asMETHODPR(SmoothedTransform, GetTargetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "StringHash GetType() const", asMETHODPR(SmoothedTransform, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "StringHash get_type() const", asMETHODPR(SmoothedTransform, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "const String& GetTypeName() const", asMETHODPR(SmoothedTransform, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const String& get_typeName() const", asMETHODPR(SmoothedTransform, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasEventHandlers() const", asMETHODPR(SmoothedTransform, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SmoothedTransform, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SmoothedTransform, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsEnabled() const", asMETHODPR(SmoothedTransform, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_enabled() const", asMETHODPR(SmoothedTransform, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsEnabledEffective() const", asMETHODPR(SmoothedTransform, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_enabledEffective() const", asMETHODPR(SmoothedTransform, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool SmoothedTransform::IsInProgress() const | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsInProgress() const", asMETHODPR(SmoothedTransform, IsInProgress, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_inProgress() const", asMETHODPR(SmoothedTransform, IsInProgress, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsInstanceOf(StringHash) const", asMETHODPR(SmoothedTransform, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsReplicated() const", asMETHODPR(SmoothedTransform, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_replicated() const", asMETHODPR(SmoothedTransform, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool IsTemporary() const", asMETHODPR(SmoothedTransform, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_temporary() const", asMETHODPR(SmoothedTransform, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool Load(Deserializer&)", asMETHODPR(SmoothedTransform, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool LoadJSON(const JSONValue&in)", asMETHODPR(SmoothedTransform, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool LoadXML(const XMLElement&in)", asMETHODPR(SmoothedTransform, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void MarkNetworkUpdate()", asMETHODPR(SmoothedTransform, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SmoothedTransform, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(SmoothedTransform, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(SmoothedTransform, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void OnSetEnabled()", asMETHODPR(SmoothedTransform, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void PrepareNetworkUpdate()", asMETHODPR(SmoothedTransform, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(SmoothedTransform, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(SmoothedTransform, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SmoothedTransform", "int Refs() const", asMETHODPR(SmoothedTransform, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "int get_refs() const", asMETHODPR(SmoothedTransform, Refs, () const, int), asCALL_THISCALL);
    // static void SmoothedTransform::RegisterObject(Context* context) | File: ../Scene/SmoothedTransform.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_RELEASE, "void f()", asMETHODPR(SmoothedTransform, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void Remove()", asMETHODPR(SmoothedTransform, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(SmoothedTransform, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveInstanceDefault()", asMETHODPR(SmoothedTransform, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void RemoveObjectAnimation()", asMETHODPR(SmoothedTransform, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void ResetToDefault()", asMETHODPR(SmoothedTransform, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool Save(Serializer&) const", asMETHODPR(SmoothedTransform, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveDefaultAttributes() const", asMETHODPR(SmoothedTransform, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveJSON(JSONValue&) const", asMETHODPR(SmoothedTransform, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SaveXML(XMLElement&) const", asMETHODPR(SmoothedTransform, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SendEvent(StringHash)", asMETHODPR(SmoothedTransform, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SmoothedTransform, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAnimationEnabled(bool)", asMETHODPR(SmoothedTransform, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_animationEnabled(bool)", asMETHODPR(SmoothedTransform, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAnimationTime(float)", asMETHODPR(SmoothedTransform, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(SmoothedTransform, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool set_attributes(uint, const Variant&in)", asMETHODPR(SmoothedTransform, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(SmoothedTransform, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(SmoothedTransform, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(SmoothedTransform, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(SmoothedTransform, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(SmoothedTransform, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetBlockEvents(bool)", asMETHODPR(SmoothedTransform, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetEnabled(bool)", asMETHODPR(SmoothedTransform, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_enabled(bool)", asMETHODPR(SmoothedTransform, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SmoothedTransform, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SmoothedTransform, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetInstanceDefault(bool)", asMETHODPR(SmoothedTransform, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(SmoothedTransform, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(SmoothedTransform, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(SmoothedTransform, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(SmoothedTransform, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SmoothedTransform::SetTargetPosition(const Vector3& position) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetPosition(const Vector3&in)", asMETHODPR(SmoothedTransform, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetPosition(const Vector3&in)", asMETHODPR(SmoothedTransform, SetTargetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void SmoothedTransform::SetTargetRotation(const Quaternion& rotation) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetRotation(const Quaternion&in)", asMETHODPR(SmoothedTransform, SetTargetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetRotation(const Quaternion&in)", asMETHODPR(SmoothedTransform, SetTargetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void SmoothedTransform::SetTargetWorldPosition(const Vector3& position) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetWorldPosition(const Vector3&in)", asMETHODPR(SmoothedTransform, SetTargetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldPosition(const Vector3&in)", asMETHODPR(SmoothedTransform, SetTargetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    // void SmoothedTransform::SetTargetWorldRotation(const Quaternion& rotation) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTargetWorldRotation(const Quaternion&in)", asMETHODPR(SmoothedTransform, SetTargetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldRotation(const Quaternion&in)", asMETHODPR(SmoothedTransform, SetTargetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void SetTemporary(bool)", asMETHODPR(SmoothedTransform, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_temporary(bool)", asMETHODPR(SmoothedTransform, SetTemporary, (bool), void), asCALL_THISCALL);
    // explicit SmoothedTransform::SmoothedTransform(Context* context) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectBehaviour("SmoothedTransform", asBEHAVE_FACTORY, "SmoothedTransform@+ f()", asFUNCTION(SmoothedTransform_SmoothedTransform_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromAllEvents()", asMETHODPR(SmoothedTransform, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SmoothedTransform_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SmoothedTransform, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SmoothedTransform, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SmoothedTransform", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SmoothedTransform, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void SmoothedTransform::Update(float constant, float squaredSnapThreshold) | File: ../Scene/SmoothedTransform.h
    engine->RegisterObjectMethod("SmoothedTransform", "void Update(float, float)", asMETHODPR(SmoothedTransform, Update, (float, float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SmoothedTransform", "int WeakRefs() const", asMETHODPR(SmoothedTransform, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "int get_weakRefs() const", asMETHODPR(SmoothedTransform, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(SmoothedTransform, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(SmoothedTransform, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SmoothedTransform", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(SmoothedTransform, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("SceneReplicationState", "void Clear()", asMETHODPR(SceneReplicationState, Clear, (), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ScreenModeParams", "bool EqualsExceptVSync(const ScreenModeParams&in) const", asMETHODPR(ScreenModeParams, EqualsExceptVSync, (const ScreenModeParams&) const, bool), asCALL_THISCALL);
    // bool ScreenModeParams::operator==(const ScreenModeParams& rhs) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("ScreenModeParams", "bool opEquals(const ScreenModeParams&in) const", asMETHODPR(ScreenModeParams, operator==, (const ScreenModeParams&) const, bool), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(const String&in, uint, int)", asFUNCTION(ShaderParameter_ShaderParameter_String_unsigned_int), asCALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned offset, unsigned size, unsigned buffer) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint, uint)", asFUNCTION(ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned_unsigned), asCALL_CDECL_OBJFIRST);
    // ShaderParameter::ShaderParameter(ShaderType type, const String& name, unsigned reg, unsigned regCount) | File: ../Graphics/ShaderVariation.h
    engine->RegisterObjectBehaviour("ShaderParameter", asBEHAVE_CONSTRUCT, "void f(ShaderType, const String&in, uint, uint)", asFUNCTION(ShaderParameter_ShaderParameter_ShaderType_String_unsigned_unsigned), asCALL_CDECL_OBJFIRST);
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
