//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "PackageFile.h"
#include "Scene.h"

static void RegisterSerializable(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint AM_FILE", (void*)AM_FILE);
    engine->RegisterGlobalProperty("const uint AM_NET", (void*)AM_NET);
    engine->RegisterGlobalProperty("const uint AM_DEFAULT", (void*)AM_DEFAULT);
    engine->RegisterGlobalProperty("const uint AM_LATESTDATA", (void*)AM_LATESTDATA);
    engine->RegisterGlobalProperty("const uint AM_NOEDIT", (void*)AM_NOEDIT);
    
    RegisterSerializable<Serializable>(engine, "Serializable");
}

static void RegisterNode(asIScriptEngine* engine)
{
    engine->RegisterEnum("CreateMode");
    engine->RegisterEnumValue("CreateMode", "REPLICATED", REPLICATED);
    engine->RegisterEnumValue("CreateMode", "LOCAL", LOCAL);
    
    // Register Component first. At this point Node is not yet registered, so can not register GetNode for Component
    RegisterComponent<Component>(engine, "Component", false);
    RegisterNode<Node>(engine, "Node");
    RegisterObjectConstructor<Node>(engine, "Node");
    RegisterNamedObjectConstructor<Node>(engine, "Node");
    engine->RegisterGlobalFunction("Node@+ get_node()", asFUNCTION(GetScriptContextNode), asCALL_CDECL);
    
    // Now GetNode can be registered
    engine->RegisterObjectMethod("Component", "Node@+ get_node() const", asMETHOD(Component, GetNode), asCALL_THISCALL);
    
    // Register Variant GetPtr() for Node & Component
    engine->RegisterObjectMethod("Variant", "Node@+ GetNode() const", asFUNCTION(GetVariantPtr<Node>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Component@+ GetComponent() const", asFUNCTION(GetVariantPtr<Component>), asCALL_CDECL_OBJLAST);
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

static CScriptArray* SceneGetRequiredPackageFiles(Scene* ptr)
{
    return SharedPtrVectorToHandleArray<PackageFile>(ptr->GetRequiredPackageFiles(), "Array<PackageFile@>");
}

static CScriptArray* GetAvailableComponents(Scene* ptr)
{
    const Map<ShortStringHash, SharedPtr<ObjectFactory> >& factories = GetScriptContext()->GetObjectFactories();
    Vector<String> components;
    
    // Simply try to create each of the objects, and check which derive from Component.
    // This assumes that creating any of them does not have harmful side-effects
    for (Map<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories.Begin(); i != factories.End(); ++i)
    {
        SharedPtr<Object> object = i->second_->CreateObject();
        if (dynamic_cast<Component*>(object.Get()))
            components.Push(object->GetTypeName());
    }
    
    return VectorToArray<String>(components, "Array<String>");
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
    engine->RegisterObjectMethod("Scene", "void Clear()", asMETHOD(Scene, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void AddRequiredPackageFile(PackageFile@+)", asMETHOD(Scene, AddRequiredPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void ClearRequiredPackageFiles()", asMETHOD(Scene, ClearRequiredPackageFiles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void RegisterVar(const String&in)", asMETHOD(Scene, RegisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterVar(const String&in)", asMETHOD(Scene, UnregisterVar), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void UnregisterAllVars(const String&in)", asMETHOD(Scene, UnregisterAllVars), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Component@+ GetComponentByID(uint)", asMETHOD(Scene, GetComponentByID), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Node@+ GetNodeByID(uint)", asMETHOD(Scene, GetNodeByID), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "const String& GetVarName(ShortStringHash) const", asMETHOD(Scene, GetVarName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void Update(float)", asMETHOD(Scene, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "void set_active(bool)", asMETHOD(Scene, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "bool get_active() const", asMETHOD(Scene, IsActive), asCALL_THISCALL);
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
    
    // Register Variant GetPtr() for Scene
    engine->RegisterObjectMethod("Variant", "Scene@+ GetScene() const", asFUNCTION(GetVariantPtr<Scene>), asCALL_CDECL_OBJLAST);

    engine->RegisterGlobalFunction("Array<String>@ GetAvailableComponents()", asFUNCTION(GetAvailableComponents), asCALL_CDECL);
}

void RegisterSceneAPI(asIScriptEngine* engine)
{
    RegisterSerializable(engine);
    RegisterNode(engine);
    RegisterScene(engine);
}
