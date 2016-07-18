//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/PackageFile.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/Scene.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/SplinePath.h"
#include "../Scene/ValueAnimation.h"

namespace Urho3D
{

static void RegisterSerializable(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint AM_FILE", (void*)&AM_FILE);
    engine->RegisterGlobalProperty("const uint AM_NET", (void*)&AM_NET);
    engine->RegisterGlobalProperty("const uint AM_DEFAULT", (void*)&AM_DEFAULT);
    engine->RegisterGlobalProperty("const uint AM_LATESTDATA", (void*)&AM_LATESTDATA);
    engine->RegisterGlobalProperty("const uint AM_NOEDIT", (void*)&AM_NOEDIT);
    engine->RegisterGlobalProperty("const uint AM_NODEID", (void*)&AM_NODEID);
    engine->RegisterGlobalProperty("const uint AM_COMPONENTID", (void*)&AM_COMPONENTID);
    engine->RegisterGlobalProperty("const uint AM_NODEIDVECTOR", (void*)&AM_NODEIDVECTOR);

    RegisterSerializable<Serializable>(engine, "Serializable");
}

static void ValueAnimationSetEventFrame(float time, const String& eventType, const VariantMap& eventData, ValueAnimation* ptr)
{
    ptr->SetEventFrame(time, eventType, eventData);
}

static void RegisterValueAnimation(asIScriptEngine* engine)
{
    engine->RegisterEnum("InterpMethod");
    engine->RegisterEnumValue("InterpMethod", "IM_NONE", IM_NONE);
    engine->RegisterEnumValue("InterpMethod", "IM_LINEAR", IM_LINEAR);
    engine->RegisterEnumValue("InterpMethod", "IM_SPLINE", IM_SPLINE);

    RegisterResource<ValueAnimation>(engine, "ValueAnimation");
    engine->RegisterObjectMethod("ValueAnimation", "void set_interpolationMethod(InterpMethod)", asMETHOD(ValueAnimation, SetInterpolationMethod), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "InterpMethod get_interpolationMethod() const", asMETHOD(ValueAnimation, GetInterpolationMethod), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_splineTension(float)", asMETHOD(ValueAnimation, SetSplineTension), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "float get_splineTension() const", asMETHOD(ValueAnimation, GetSplineTension), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void set_valueType(VariantType)", asMETHOD(ValueAnimation, SetValueType), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "VariantType get_valueType() const", asMETHOD(ValueAnimation, GetValueType), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void SetKeyFrame(float, const Variant&in)", asMETHOD(ValueAnimation, SetKeyFrame), asCALL_THISCALL);
    engine->RegisterObjectMethod("ValueAnimation", "void SetEventFrame(float, const String&in, const VariantMap&in eventData = VariantMap())", asFUNCTION(ValueAnimationSetEventFrame), asCALL_CDECL_OBJLAST);
}

static void RegisterObjectAnimation(asIScriptEngine* engine)
{
    engine->RegisterEnum("WrapMode");
    engine->RegisterEnumValue("WrapMode", "WM_LOOP", WM_LOOP);
    engine->RegisterEnumValue("WrapMode", "WM_ONCE", WM_ONCE);
    engine->RegisterEnumValue("WrapMode", "WM_CLAMP", WM_CLAMP);

    RegisterResource<ObjectAnimation>(engine, "ObjectAnimation");
    engine->RegisterObjectMethod("ObjectAnimation", "void AddAttributeAnimation(const String&in, ValueAnimation@+, WrapMode wrapMode=WM_LOOP, float speed=1.0f)", asMETHOD(ObjectAnimation, AddAttributeAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ObjectAnimation, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(ValueAnimation@+)", asMETHODPR(ObjectAnimation, RemoveAttributeAnimation, (ValueAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimationWrapMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "float GetAttributeAnimationSpeed(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimationSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "Variant get_attributeAnimations(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "Variant get_wrapModes(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimationWrapMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "Variant get_speeds(const String&in) const", asMETHOD(ObjectAnimation, GetAttributeAnimationSpeed), asCALL_THISCALL);
}


static void RegisterAnimatable(asIScriptEngine* engine)
{
    RegisterAnimatable<Animatable>(engine, "Animatable");
}

static bool NodeSaveXML(File* file, const String& indentation, Node* ptr)
{
    return file && ptr->SaveXML(*file, indentation);
}

static bool NodeSaveJSON(File* file, Node* ptr)
{
    return file && ptr->SaveJSON(*file);
}

static bool NodeSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, Node* ptr)
{
    return ptr->SaveXML(buffer, indentation);
}

static bool NodeSaveJSONVectorBuffer(VectorBuffer& buffer, Node* ptr)
{
    return ptr->SaveJSON(buffer);
}

static void RegisterNode(asIScriptEngine* engine)
{
    engine->RegisterEnum("CreateMode");
    engine->RegisterEnumValue("CreateMode", "REPLICATED", REPLICATED);
    engine->RegisterEnumValue("CreateMode", "LOCAL", LOCAL);

    engine->RegisterEnum("TransformSpace");
    engine->RegisterEnumValue("TransformSpace", "TS_LOCAL", TS_LOCAL);
    engine->RegisterEnumValue("TransformSpace", "TS_PARENT", TS_PARENT);
    engine->RegisterEnumValue("TransformSpace", "TS_WORLD", TS_WORLD);

    // Register Component first. At this point Node is not yet registered, so can not register GetNode for Component
    RegisterComponent<Component>(engine, "Component", false, false);
    RegisterNode<Node>(engine, "Node");

    engine->RegisterObjectMethod("Node", "void SetDeepEnabled(bool)", asMETHOD(Node, SetDeepEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void ResetDeepEnabled()", asMETHOD(Node, ResetDeepEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void SetEnabledRecursive(bool)", asMETHOD(Node, SetEnabledRecursive), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void MarkDirty()", asMETHOD(Node, MarkDirty), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_enabled(bool)", asMETHODPR(Node, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabled() const", asMETHOD(Node, IsEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabledSelf() const", asMETHOD(Node, IsEnabledSelf), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool SaveXML(File@+, const String&in indentation = \"\t\")", asFUNCTION(NodeSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", asFUNCTION(NodeSaveXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "bool SaveJSON(File@+)", asFUNCTION(NodeSaveJSON), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "bool SaveJSON(VectorBuffer&)", asFUNCTION(NodeSaveJSONVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "Node@+ Clone(CreateMode mode = REPLICATED)", asMETHOD(Node, Clone), asCALL_THISCALL);
    RegisterObjectConstructor<Node>(engine, "Node");
    RegisterNamedObjectConstructor<Node>(engine, "Node");
    engine->RegisterGlobalFunction("Node@+ get_node()", asFUNCTION(GetScriptContextNode), asCALL_CDECL);

    // Now GetNode can be registered
    engine->RegisterObjectMethod("Component", "Node@+ get_node() const", asMETHOD(Component, GetNode), asCALL_THISCALL);

    // Calling DebugRenderer is part of the Component API, so register it as early as possible
    RegisterComponent<DebugRenderer>(engine, "DebugRenderer", true, false);
    engine->RegisterObjectMethod("Component", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(Component, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(DebugRenderer, DrawDebugGeometry), asCALL_THISCALL);
}

static bool SceneLoadXML(File* file, Scene* ptr)
{
    return file && ptr->LoadXML(*file);
}

static bool SceneLoadXMLVectorBuffer(VectorBuffer& buffer, Scene* ptr)
{
    return ptr->LoadXML(buffer);
}

static CScriptArray* SceneGetNodesWithTag(const String& tag, Scene* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetNodesWithTag(nodes, tag);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

static bool SceneLoadJSONVectorBuffer(VectorBuffer& buffer, Scene* ptr)
{
    return ptr->LoadJSON(buffer);
}

static bool SceneLoadJSON(File* file, Scene* ptr)
{
    return file && ptr->LoadJSON(*file);
}

static bool SceneSaveXML(File* file, const String& indentation, Scene* ptr)
{
    return file && ptr->SaveXML(*file, indentation);
}

static bool SceneSaveJSON(File* file, const String& indentation, Scene* ptr)
{
    return file && ptr->SaveJSON(*file, indentation);
}

static bool SceneSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, Scene* ptr)
{
    return ptr->SaveXML(buffer, indentation);
}

static bool SceneSaveJSONVectorBuffer(VectorBuffer& buffer, const String& indentation, Scene* ptr)
{
    return ptr->SaveJSON(buffer, indentation);
}

static Node* SceneInstantiate(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->Instantiate(*file, position, rotation, mode) : 0;
}

static Node* SceneInstantiateVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->Instantiate(buffer, position, rotation, mode);
}

static Node* SceneInstantiateXML(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->InstantiateXML(*file, position, rotation, mode) : 0;
}

static Node* SceneInstantiateJSON(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->InstantiateJSON(*file, position, rotation, mode) : 0;
}

static Node* SceneInstantiateXMLVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->InstantiateXML(buffer, position, rotation, mode);
}

static Node* SceneInstantiateJSONVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->InstantiateJSON(buffer, position, rotation, mode);
}

static Node* SceneInstantiateXMLFile(XMLFile* xml, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return xml ? ptr->InstantiateXML(xml->GetRoot(), position, rotation, mode) : 0;
}

static Node* SceneInstantiateJSONFile(JSONFile* json, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return json ? ptr->InstantiateJSON(json->GetRoot(), position, rotation, mode) : 0;
}

static CScriptArray* SceneGetRequiredPackageFiles(Scene* ptr)
{
    return VectorToHandleArray<PackageFile>(ptr->GetRequiredPackageFiles(), "Array<PackageFile@>");
}

static CScriptArray* GetObjectCategories()
{
    Vector<String> categories = GetScriptContext()->GetObjectCategories().Keys();
    Sort(categories.Begin(), categories.End());
    return VectorToArray<String>(categories, "Array<String>");
}

static CScriptArray* GetObjectsByCategory(const String& category)
{
    const HashMap<String, Vector<StringHash> >& categories = GetScriptContext()->GetObjectCategories();
    Vector<String> components;

    HashMap<String, Vector<StringHash> >::ConstIterator i = categories.Find(category);
    if (i != categories.End())
    {
        const HashMap<StringHash, SharedPtr<ObjectFactory> >& factories = GetScriptContext()->GetObjectFactories();
        const Vector<StringHash>& factoryHashes = i->second_;
        components.Reserve(factoryHashes.Size());

        for (unsigned j = 0; j < factoryHashes.Size(); ++j)
        {
            HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator k = factories.Find(factoryHashes[j]);
            if (k != factories.End())
                components.Push(k->second_->GetTypeName());
        }
    }

    Sort(components.Begin(), components.End());
    return VectorToArray<String>(components, "Array<String>");
}

static void RegisterSmoothedTransform(asIScriptEngine* engine)
{
    RegisterComponent<SmoothedTransform>(engine, "SmoothedTransform");
    engine->RegisterObjectMethod("SmoothedTransform", "void Update(float, float)", asMETHOD(SmoothedTransform, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetPosition(const Vector3&in)", asMETHOD(SmoothedTransform, SetTargetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Vector3& get_targetPosition() const", asMETHOD(SmoothedTransform, GetTargetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetRotation(const Quaternion&in)", asMETHOD(SmoothedTransform, SetTargetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "const Quaternion& get_targetRotation() const", asMETHOD(SmoothedTransform, GetTargetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldPosition(const Vector3&in)", asMETHOD(SmoothedTransform, SetTargetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Vector3 get_targetWorldPosition() const", asMETHOD(SmoothedTransform, GetTargetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void set_targetWorldRotation(const Quaternion&in)", asMETHOD(SmoothedTransform, SetTargetWorldRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "Quaternion get_targetWorldRotation() const", asMETHOD(SmoothedTransform, GetTargetWorldRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "bool get_inProgress() const", asMETHOD(SmoothedTransform, IsInProgress), asCALL_THISCALL);
}

static void RegisterSplinePath(asIScriptEngine* engine)
{
    RegisterComponent<SplinePath>(engine, "SplinePath");
    engine->RegisterObjectMethod("SplinePath", "void AddControlPoint(Node@+ point, uint index = M_MAX_UNSIGNED)", asMETHOD(SplinePath, AddControlPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void RemoveControlPoint(Node@+ point)", asMETHOD(SplinePath, RemoveControlPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void ClearControlPoints()", asMETHOD(SplinePath, ClearControlPoints), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", asMETHOD(SplinePath, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", asMETHOD(SplinePath, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void SetPosition(float)", asMETHOD(SplinePath, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_controlledNode(Node@+)", asMETHOD(SplinePath, SetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", asMETHOD(SplinePath, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", asMETHOD(SplinePath, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_length() const", asMETHOD(SplinePath, GetLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPosition() const", asMETHOD(SplinePath, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@+ get_controlledNode() const", asMETHOD(SplinePath, GetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", asMETHOD(SplinePath, GetPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", asMETHOD(SplinePath, Move), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Reset()", asMETHOD(SplinePath, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_isFinished() const", asMETHOD(SplinePath, IsFinished), asCALL_THISCALL);
}

static void RegisterScene(asIScriptEngine* engine)
{
    engine->RegisterEnum("LoadMode");
    engine->RegisterEnumValue("LoadMode", "LOAD_RESOURCES_ONLY", LOAD_RESOURCES_ONLY);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE", LOAD_SCENE);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE_AND_RESOURCES", LOAD_SCENE_AND_RESOURCES);

    engine->RegisterGlobalProperty("const uint FIRST_REPLICATED_ID", (void*)&FIRST_REPLICATED_ID);
    engine->RegisterGlobalProperty("const uint LAST_REPLICATED_ID", (void*)&LAST_REPLICATED_ID);
    engine->RegisterGlobalProperty("const uint FIRST_LOCAL_ID", (void*)&FIRST_LOCAL_ID);
    engine->RegisterGlobalProperty("const uint LAST_LOCAL_ID", (void*)&LAST_LOCAL_ID);

    RegisterNode<Scene>(engine, "Scene");
    RegisterObjectConstructor<Scene>(engine, "Scene");
    RegisterNamedObjectConstructor<Scene>(engine, "Scene");
    engine->RegisterObjectMethod("Scene", "bool LoadXML(File@+)", asFUNCTION(SceneLoadXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool LoadXML(VectorBuffer&)", asFUNCTION(SceneLoadXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool SaveXML(File@+, const String&in indentation = \"\t\")", asFUNCTION(SceneSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", asFUNCTION(SceneSaveXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(File@+)", asFUNCTION(SceneLoadJSON), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool LoadJSON(VectorBuffer&)", asFUNCTION(SceneLoadJSONVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool SaveJSON(File@+, const String&in indentation = \"\t\")", asFUNCTION(SceneSaveJSON), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool SaveJSON(VectorBuffer&, const String&in indentation = \"\t\")", asFUNCTION(SceneSaveJSONVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool LoadAsync(File@+, LoadMode mode = LOAD_SCENE_AND_RESOURCES)", asMETHOD(Scene, LoadAsync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncXML(File@+, LoadMode mode = LOAD_SCENE_AND_RESOURCES)", asMETHOD(Scene, LoadAsyncXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void StopAsyncLoading()", asMETHOD(Scene, StopAsyncLoading), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "Node@+ Instantiate(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiate), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ Instantiate(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(XMLFile@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXMLFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(const XMLElement&in, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asMETHODPR(Scene, InstantiateXML, (const XMLElement&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSON), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSONVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(JSONFile@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSONFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateJSON(const JSONValue&in, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asMETHODPR(Scene, InstantiateJSON, (const JSONValue&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "void Clear(bool clearReplicated = true, bool clearLocal = true)", asMETHOD(Scene, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void AddRequiredPackageFile(PackageFile@+)", asMETHOD(Scene, AddRequiredPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void ClearRequiredPackageFiles()", asMETHOD(Scene, ClearRequiredPackageFiles), asCALL_THISCALL);
 
    engine->RegisterObjectMethod("Scene", "void RegisterVar(const String&in)", asMETHOD(Scene, RegisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterVar(const String&in)", asMETHOD(Scene, UnregisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterAllVars(const String&in)", asMETHOD(Scene, UnregisterAllVars), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "Array<Node@>@ GetNodesWithTag(const String&in) const", asFUNCTION(SceneGetNodesWithTag), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectMethod("Scene", "Component@+ GetComponent(uint) const", asMETHODPR(Scene, GetComponent, (unsigned) const, Component*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ GetNode(uint) const", asMETHOD(Scene, GetNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& GetVarName(StringHash) const", asMETHOD(Scene, GetVarName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void Update(float)", asMETHOD(Scene, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_updateEnabled(bool)", asMETHOD(Scene, SetUpdateEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_updateEnabled() const", asMETHOD(Scene, IsUpdateEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_timeScale(float)", asMETHOD(Scene, SetTimeScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_timeScale() const", asMETHOD(Scene, GetTimeScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_elapsedTime(float)", asMETHOD(Scene, SetElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_elapsedTime() const", asMETHOD(Scene, GetElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_smoothingConstant(float)", asMETHOD(Scene, SetSmoothingConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_smoothingConstant() const", asMETHOD(Scene, GetSmoothingConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_snapThreshold(float)", asMETHOD(Scene, SetSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_snapThreshold() const", asMETHOD(Scene, GetSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_asyncLoading() const", asMETHOD(Scene, IsAsyncLoading), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_asyncProgress() const", asMETHOD(Scene, GetAsyncProgress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "LoadMode get_asyncLoadMode() const", asMETHOD(Scene, GetAsyncLoadMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_asyncLoadingMs(int)", asMETHOD(Scene, SetAsyncLoadingMs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "int get_asyncLoadingMs() const", asMETHOD(Scene, GetAsyncLoadingMs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_checksum() const", asMETHOD(Scene, GetChecksum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_fileName() const", asMETHOD(Scene, GetFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ get_requiredPackageFiles() const", asFUNCTION(SceneGetRequiredPackageFiles), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "Scene@+ get_scene() const", asMETHOD(Node, GetScene), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Scene@+ get_scene()", asFUNCTION(GetScriptContextScene), asCALL_CDECL);

    engine->RegisterGlobalFunction("Array<String>@ GetObjectCategories()", asFUNCTION(GetObjectCategories), asCALL_CDECL);
    engine->RegisterGlobalFunction("Array<String>@ GetObjectsByCategory(const String&in)", asFUNCTION(GetObjectsByCategory), asCALL_CDECL);
}

void RegisterSceneAPI(asIScriptEngine* engine)
{
    RegisterSerializable(engine);
    RegisterValueAnimation(engine);
    RegisterObjectAnimation(engine);
    RegisterAnimatable(engine);
    RegisterNode(engine);
    RegisterSmoothedTransform(engine);
    RegisterSplinePath(engine);
    RegisterScene(engine);
}

}
