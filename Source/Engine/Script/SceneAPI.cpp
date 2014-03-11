//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Precompiled.h"
#include "APITemplates.h"
#include "DebugRenderer.h"
#include "PackageFile.h"
#include "Scene.h"
#include "SmoothedTransform.h"
#include "Sort.h"
#include "SplinePath.h"

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

static bool NodeSaveXML(File* file, Node* ptr)
{
    if (file)
        return ptr->SaveXML(*file);
    else
        return false;
}

static void RegisterNode(asIScriptEngine* engine)
{
    engine->RegisterEnum("CreateMode");
    engine->RegisterEnumValue("CreateMode", "REPLICATED", REPLICATED);
    engine->RegisterEnumValue("CreateMode", "LOCAL", LOCAL);

    // Register Component first. At this point Node is not yet registered, so can not register GetNode for Component
    RegisterComponent<Component>(engine, "Component", false, false);
    RegisterNode<Node>(engine, "Node");
    
    engine->RegisterObjectMethod("Node", "void SetEnabled(bool, bool)", asMETHODPR(Node, SetEnabled, (bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_enabled(bool)", asMETHODPR(Node, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabled() const", asMETHOD(Node, IsEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool SaveXML(File@+)", asFUNCTION(NodeSaveXML), asCALL_CDECL_OBJLAST);
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
    
    // Register Variant GetPtr() for Serializable, Node & Component. These are deprecated, GetPtr() should be used instead.
    engine->RegisterObjectMethod("Variant", "Serializable@+ GetSerializable(const String&in binding = \"deprecated:GetSerializable\") const", asFUNCTION(GetVariantPtr<Serializable>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Node@+ GetNode(const String&in binding = \"deprecated:GetNode\") const", asFUNCTION(GetVariantPtr<Node>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Component@+ GetComponent(const String&in binding = \"deprecated:GetComponent\") const", asFUNCTION(GetVariantPtr<Component>), asCALL_CDECL_OBJLAST);
}

static bool SceneLoadXML(File* file, Scene* ptr)
{
    if (file)
        return ptr->LoadXML(*file);
    else
        return false;
}

static bool SceneSaveXML(File* file, Scene* ptr)
{
    if (file)
        return ptr->SaveXML(*file);
    else
        return false;
}

static Node* SceneInstantiate(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    if (file)
        return ptr->Instantiate(*file, position, rotation, mode);
    else
        return 0;
}

static Node* SceneInstantiateXML(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    if (file)
        return ptr->InstantiateXML(*file, position, rotation, mode);
    else
        return 0;
}

static Node* SceneInstantiateXMLFile(XMLFile* xml, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    if (xml)
        return ptr->InstantiateXML(xml->GetRoot(), position, rotation, mode);
    else
        return 0;
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
    const HashMap<String, Vector<ShortStringHash> >& categories = GetScriptContext()->GetObjectCategories();
    Vector<String> components;

    HashMap<String, Vector<ShortStringHash> >::ConstIterator i = categories.Find(category);
    if (i != categories.End())
    {
        const HashMap<ShortStringHash, SharedPtr<ObjectFactory> >& factories = GetScriptContext()->GetObjectFactories();
        const Vector<ShortStringHash>& factoryHashes = i->second_;
        components.Reserve(factoryHashes.Size());

        for (unsigned j = 0; j < factoryHashes.Size(); ++j)
        {
            HashMap<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator k = factories.Find(factoryHashes[j]);
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
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", asMETHOD(SplinePath, GetPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", asMETHOD(SplinePath, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", asMETHOD(SplinePath, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_position(float)", asMETHOD(SplinePath, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_controlledNode(Node@+)", asMETHOD(SplinePath, GetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", asMETHOD(SplinePath, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", asMETHOD(SplinePath, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 get_position() const", asMETHOD(SplinePath, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@ get_controlledNode() const", asMETHOD(SplinePath, GetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", asMETHOD(SplinePath, Move), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Reset()", asMETHOD(SplinePath, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_isFinished() const", asMETHOD(SplinePath, IsFinished), asCALL_THISCALL);
}

static void RegisterScene(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint FIRST_REPLICATED_ID", (void*)&FIRST_REPLICATED_ID);
    engine->RegisterGlobalProperty("const uint LAST_REPLICATED_ID", (void*)&LAST_REPLICATED_ID);
    engine->RegisterGlobalProperty("const uint FIRST_LOCAL_ID", (void*)&FIRST_LOCAL_ID);
    engine->RegisterGlobalProperty("const uint LAST_LOCAL_ID", (void*)&LAST_LOCAL_ID);

    RegisterNode<Scene>(engine, "Scene");
    RegisterObjectConstructor<Scene>(engine, "Scene");
    RegisterNamedObjectConstructor<Scene>(engine, "Scene");
    engine->RegisterObjectMethod("Scene", "bool LoadXML(File@+)", asFUNCTION(SceneLoadXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool SaveXML(File@+)", asFUNCTION(SceneSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool LoadAsync(File@+)", asMETHOD(Scene, LoadAsync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool LoadAsyncXML(File@+)", asMETHOD(Scene, LoadAsyncXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void StopAsyncLoading()", asMETHOD(Scene, StopAsyncLoading), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ Instantiate(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiate), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(XMLFile@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXMLFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Node@+ InstantiateXML(const XMLElement&in, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asMETHODPR(Scene, InstantiateXML, (const XMLElement&, const Vector3&, const Quaternion&, CreateMode), Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void Clear(bool clearReplicated = true, bool clearLocal = true)", asMETHOD(Scene, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void AddRequiredPackageFile(PackageFile@+)", asMETHOD(Scene, AddRequiredPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void ClearRequiredPackageFiles()", asMETHOD(Scene, ClearRequiredPackageFiles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void RegisterVar(const String&in)", asMETHOD(Scene, RegisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterVar(const String&in)", asMETHOD(Scene, UnregisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterAllVars(const String&in)", asMETHOD(Scene, UnregisterAllVars), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Component@+ GetComponent(uint)", asMETHODPR(Scene, GetComponent, (unsigned) const, Component*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ GetNode(uint)", asMETHOD(Scene, GetNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& GetVarName(ShortStringHash) const", asMETHOD(Scene, GetVarName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void Update(float)", asMETHOD(Scene, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_updateEnabled(bool)", asMETHOD(Scene, SetUpdateEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_updateEnabled() const", asMETHOD(Scene, IsUpdateEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_timeScale(float)", asMETHOD(Scene, SetTimeScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_timeScale() const", asMETHOD(Scene, GetTimeScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_elapsedTime(float)", asMETHOD(Scene, SetElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_elapsedTime() const", asMETHOD(Scene, GetElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_pixelsPerUnit(float)", asMETHOD(Scene, SetPixelsPerUnit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_pixelsPerUnit() const", asMETHOD(Scene, GetPixelsPerUnit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_smoothingConstant(float)", asMETHOD(Scene, SetSmoothingConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_smoothingConstant() const", asMETHOD(Scene, GetSmoothingConstant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_snapThreshold(float)", asMETHOD(Scene, SetSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_snapThreshold() const", asMETHOD(Scene, GetSnapThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_asyncLoading() const", asMETHOD(Scene, IsAsyncLoading), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "float get_asyncProgress() const", asMETHOD(Scene, GetAsyncProgress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "uint get_checksum() const", asMETHOD(Scene, GetChecksum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& get_fileName() const", asMETHOD(Scene, GetFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Array<PackageFile@>@ get_requiredPackageFiles() const", asFUNCTION(SceneGetRequiredPackageFiles), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "Scene@+ get_scene() const", asMETHOD(Node, GetScene), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Scene@+ get_scene()", asFUNCTION(GetScriptContextScene), asCALL_CDECL);

    // Register Variant GetPtr() for Scene. This is deprecated, GetPtr() should be used instead.
    engine->RegisterObjectMethod("Variant", "Scene@+ GetScene(const String&in binding = \"deprecated:GetScene\") const", asFUNCTION(GetVariantPtr<Scene>), asCALL_CDECL_OBJLAST);

    engine->RegisterGlobalFunction("Array<String>@ GetObjectCategories()", asFUNCTION(GetObjectCategories), asCALL_CDECL);
    engine->RegisterGlobalFunction("Array<String>@ GetObjectsByCategory(const String&in)", asFUNCTION(GetObjectsByCategory), asCALL_CDECL);
}

void RegisterSceneAPI(asIScriptEngine* engine)
{
    RegisterSerializable(engine);
    RegisterNode(engine);
    RegisterSmoothedTransform(engine);
    RegisterSplinePath(engine);
    RegisterScene(engine);
}

}
