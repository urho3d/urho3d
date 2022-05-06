// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../AngelScript/ScriptAPI.h"
#include "../AngelScript/ScriptFile.h"
#include "../Resource/ResourceCache.h"
//#include "../AngelScript/Generated_Templates.h"
#include "../AngelScript/Generated_Members.h"

namespace Urho3D
{

static bool ScriptFileExecute(const String& declaration, CScriptArray* srcParams, ScriptFile* ptr)
{
    VariantVector destParams(srcParams ? srcParams->GetSize() : 0);

    if (srcParams)
    {
        unsigned numParams = srcParams->GetSize();
        for (unsigned i = 0; i < numParams; ++i)
            destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    }

    return ptr->Execute(declaration, destParams);
}

static void ScriptFileDelayedExecute(float delay, bool repeat, const String& declaration, CScriptArray* srcParams, ScriptFile* ptr)
{
    VariantVector destParams(srcParams ? srcParams->GetSize() : 0);

    if (srcParams)
    {
        unsigned numParams = srcParams->GetSize();
        for (unsigned i = 0; i < numParams; ++i)
            destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    }

    ptr->DelayedExecute(delay, repeat, declaration, destParams);
}

static asIScriptObject* NodeCreateScriptObjectWithFile(ScriptFile* file, const String& className, CreateMode mode, Node* ptr)
{
    if (!file)
        return nullptr;

    // Try first to reuse an existing, empty ScriptInstance
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
    {
        if ((*i)->GetType() == ScriptInstance::GetTypeStatic())
        {
            auto* instance = static_cast<ScriptInstance*>(i->Get());
            asIScriptObject* object = instance->GetScriptObject();
            if (!object)
            {
                instance->CreateObject(file, className);
                return instance->GetScriptObject();
            }
        }
    }
    // Then create a new component if not found
    auto* instance = ptr->CreateComponent<ScriptInstance>(mode);
    instance->CreateObject(file, className);
    return instance->GetScriptObject();
}

static ScriptFile* ScriptFile_ScriptFile_Context()
{
    Context* context = GetScriptContext();
    return new ScriptFile(context);
}

static void RegisterScriptFile(asIScriptEngine* engine)
{
    /*
    RegisterResource<ScriptFile>(engine, "ScriptFile");
    engine->RegisterObjectMethod("ScriptFile", "bool Execute(const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptFileExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptFileDelayedExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void ClearDelayedExecute(const String&in declaration = String())", AS_METHOD(ScriptFile, ClearDelayedExecute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptFile", "bool get_compiled() const", AS_METHOD(ScriptFile, IsCompiled), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptFile@+ get_scriptFile()", AS_FUNCTION(GetScriptContextFile), AS_CALL_CDECL);
    */

    engine->RegisterObjectType("ScriptFile", 0, asOBJ_REF);

    RegisterMembers_Resource<ScriptFile>(engine, "ScriptFile");

    engine->RegisterObjectBehaviour("ScriptFile", asBEHAVE_FACTORY, "ScriptFile@+ f()", AS_FUNCTION(ScriptFile_ScriptFile_Context), AS_CALL_CDECL);

    engine->RegisterObjectMethod("ScriptFile", "bool Execute(const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptFileExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptFileDelayedExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void ClearDelayedExecute(const String&in declaration = String())", AS_METHOD(ScriptFile, ClearDelayedExecute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptFile", "bool get_compiled() const", AS_METHOD(ScriptFile, IsCompiled), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptFile@+ get_scriptFile()", AS_FUNCTION(GetScriptContextFile), AS_CALL_CDECL);

    // TODO: named constructor, base classes?
}

static asIScriptObject* NodeCreateScriptObject(const String& scriptFileName, const String& className, CreateMode mode, Node* ptr)
{
    auto* cache = GetScriptContext()->GetSubsystem<ResourceCache>();
    return NodeCreateScriptObjectWithFile(cache->GetResource<ScriptFile>(scriptFileName), className, mode, ptr);
}

asIScriptObject* NodeGetScriptObject(Node* ptr)
{
    // Get the first available ScriptInstance with an object
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
    {
        if ((*i)->GetType() == ScriptInstance::GetTypeStatic())
        {
            auto* instance = static_cast<ScriptInstance*>(i->Get());
            asIScriptObject* object = instance->GetScriptObject();
            if (object)
                return object;
        }
    }

    return nullptr;
}

asIScriptObject* NodeGetNamedScriptObject(const String& className, Node* ptr)
{
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
    {
        if ((*i)->GetType() == ScriptInstance::GetTypeStatic())
        {
            auto* instance = static_cast<ScriptInstance*>(i->Get());
            if (instance->IsA(className))
            {
                asIScriptObject* object = instance->GetScriptObject();
                if (object)
                    return object;
            }
        }
    }

    return nullptr;
}

static bool ScriptInstanceExecute(const String& declaration, CScriptArray* srcParams, ScriptInstance* ptr)
{
    VariantVector destParams(srcParams ? srcParams->GetSize() : 0);

    if (srcParams)
    {
        unsigned numParams = srcParams->GetSize();
        for (unsigned i = 0; i < numParams; ++i)
            destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    }

    return ptr->Execute(declaration, destParams);
}

static void ScriptInstanceDelayedExecute(float delay, bool repeat, const String& declaration, CScriptArray* srcParams, ScriptInstance* ptr)
{
    VariantVector destParams(srcParams ? srcParams->GetSize() : 0);

    if (srcParams)
    {
        unsigned numParams = srcParams->GetSize();
        for (unsigned i = 0; i < numParams; ++i)
            destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    }

    ptr->DelayedExecute(delay, repeat, declaration, destParams);
}

static ScriptInstance* GetSelf()
{
    return GetScriptContextInstance();
}

static void SelfDelayedExecute(float delay, bool repeat, const String& declaration, CScriptArray* srcParams)
{
    VariantVector destParams(srcParams ? srcParams->GetSize() : 0);

    if (srcParams)
    {
        unsigned numParams = srcParams->GetSize();
        for (unsigned i = 0; i < numParams; ++i)
            destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    }

    ScriptInstance* ptr = GetScriptContextInstance();
    if (ptr)
        ptr->DelayedExecute(delay, repeat, declaration, destParams);
    else
    {
        ScriptFile* file = GetScriptContextFile();
        if (file)
            file->DelayedExecute(delay, repeat, declaration, destParams);
    }
}

static void SelfClearDelayedExecute(const String& declaration)
{
    ScriptInstance* ptr = GetScriptContextInstance();
    if (ptr)
        ptr->ClearDelayedExecute(declaration);
    else
    {
        ScriptFile* file = GetScriptContextFile();
        if (file)
            file->ClearDelayedExecute(declaration);
    }
}

static void SelfMarkNetworkUpdate()
{
    ScriptInstance* ptr = GetScriptContextInstance();
    if (ptr)
        ptr->MarkNetworkUpdate();
}

static void SelfRemove()
{
    ScriptInstance* ptr = GetScriptContextInstance();
    if (ptr)
        ptr->Remove();
}

static ScriptInstance* ScriptInstance_ScriptInstance_Context()
{
    Context* context = GetScriptContext();
    return new ScriptInstance(context);
}

static void RegisterScriptInstance(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("Node", "ScriptObject@+ CreateScriptObject(ScriptFile@+, const String&in, CreateMode mode = REPLICATED)", AS_FUNCTION_OBJLAST(NodeCreateScriptObjectWithFile), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ CreateScriptObject(const String&in, const String&in, CreateMode mode = REPLICATED)", AS_FUNCTION_OBJLAST(NodeCreateScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ GetScriptObject() const", AS_FUNCTION_OBJLAST(NodeGetScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ GetScriptObject(const String&in) const", AS_FUNCTION_OBJLAST(NodeGetNamedScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ get_scriptObject() const", AS_FUNCTION_OBJLAST(NodeGetScriptObject), AS_CALL_CDECL_OBJLAST);

    engine->RegisterObjectMethod("Scene", "ScriptObject@+ CreateScriptObject(ScriptFile@+, const String&in, CreateMode mode = REPLICATED)", AS_FUNCTION_OBJLAST(NodeCreateScriptObjectWithFile), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ CreateScriptObject(const String&in, const String&in, CreateMode mode = REPLICATED)", AS_FUNCTION_OBJLAST(NodeCreateScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ GetScriptObject() const", AS_FUNCTION_OBJLAST(NodeGetScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ GetScriptObject(const String&in) const", AS_FUNCTION_OBJLAST(NodeGetNamedScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ get_scriptObject() const", AS_FUNCTION_OBJLAST(NodeGetScriptObject), AS_CALL_CDECL_OBJLAST);

    engine->RegisterObjectType("ScriptInstance", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("ScriptInstance", asBEHAVE_FACTORY, "ScriptInstance@+ f()", AS_FUNCTION(ScriptInstance_ScriptInstance_Context), AS_CALL_CDECL);

    RegisterMembers_Component<ScriptInstance>(engine, "ScriptInstance");

    RegisterSubclass<Component, ScriptInstance>(engine, "Component", "ScriptInstance");
    RegisterSubclass<Animatable, ScriptInstance>(engine, "Animatable", "ScriptInstance");
    RegisterSubclass<Serializable, ScriptInstance>(engine, "Serializable", "ScriptInstance");
    RegisterSubclass<Object, ScriptInstance>(engine, "Object", "ScriptInstance");
    RegisterSubclass<RefCounted, ScriptInstance>(engine, "RefCounted", "ScriptInstance");

    engine->RegisterObjectMethod("ScriptInstance", "bool CreateObject(ScriptFile@+, const String&in)", AS_METHODPR(ScriptInstance, CreateObject, (ScriptFile*, const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool Execute(const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptInstanceExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION(ScriptInstanceDelayedExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void ClearDelayedExecute(const String&in declaration = String())", AS_METHOD(ScriptInstance, ClearDelayedExecute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool IsA(const String&in declaration) const", AS_METHOD(ScriptInstance, IsA), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool HasMethod(const String&in declaration) const", AS_METHOD(ScriptInstance, HasMethod), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_scriptFile(ScriptFile@+)", AS_METHOD(ScriptInstance, SetScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptFile@+ get_scriptFile() const", AS_METHOD(ScriptInstance, GetScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptObject@+ get_scriptObject() const", AS_METHOD(ScriptInstance, GetScriptObject), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_className(const String&in)", AS_METHOD(ScriptInstance, SetClassName), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "const String& get_className() const", AS_METHOD(ScriptInstance, GetClassName), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptInstance@+ get_self()", AS_FUNCTION(GetSelf), AS_CALL_CDECL);



    /*
    RegisterComponent<ScriptInstance>(engine, "ScriptInstance");
    engine->RegisterObjectMethod("ScriptInstance", "bool CreateObject(ScriptFile@+, const String&in)", AS_METHODPR(ScriptInstance, CreateObject, (ScriptFile*, const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool Execute(const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION_OBJLAST(ScriptInstanceExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION(ScriptInstanceDelayedExecute), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void ClearDelayedExecute(const String&in declaration = String())", AS_METHOD(ScriptInstance, ClearDelayedExecute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool IsA(const String&in declaration) const", AS_METHOD(ScriptInstance, IsA), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool HasMethod(const String&in declaration) const", AS_METHOD(ScriptInstance, HasMethod), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_scriptFile(ScriptFile@+)", AS_METHOD(ScriptInstance, SetScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptFile@+ get_scriptFile() const", AS_METHOD(ScriptInstance, GetScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptObject@+ get_scriptObject() const", AS_METHOD(ScriptInstance, GetScriptObject), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_className(const String&in)", AS_METHOD(ScriptInstance, SetClassName), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "const String& get_className() const", AS_METHOD(ScriptInstance, GetClassName), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptInstance@+ get_self()", AS_FUNCTION(GetSelf), AS_CALL_CDECL);
    */

    // Register convenience functions for controlling self, similar to event sending
    engine->RegisterGlobalFunction("void MarkNetworkUpdate()", AS_FUNCTION(SelfMarkNetworkUpdate), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", AS_FUNCTION(SelfDelayedExecute), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void ClearDelayedExecute(const String&in declaration = String())", AS_FUNCTION(SelfClearDelayedExecute), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void Remove()", AS_FUNCTION(SelfRemove), AS_CALL_CDECL);
}

static Script* GetScript()
{
    return GetScriptContext()->GetSubsystem<Script>();
}

static Script* Script_Script_Context()
{
    Context* context = GetScriptContext();
    return new Script(context);
}

static void RegisterScript(asIScriptEngine* engine)
{
    engine->RegisterEnum("DumpMode");
    engine->RegisterEnumValue("DumpMode", "DOXYGEN", DOXYGEN);
    engine->RegisterEnumValue("DumpMode", "C_HEADER", C_HEADER);

    engine->RegisterObjectType("Script", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Script", asBEHAVE_FACTORY, "Script@+ f()", AS_FUNCTION(Script_Script_Context), AS_CALL_CDECL);
    RegisterMembers_Object<Script>(engine, "Script");

    engine->RegisterObjectMethod("Script", "bool Execute(const String&in)", AS_METHOD(Script, Execute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void DumpAPI(DumpMode mode = DOXYGEN, const String&in sourceTree = String())", AS_METHOD(Script, DumpAPI), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScriptFile(ScriptFile@+)", AS_METHOD(Script, SetDefaultScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "ScriptFile@+ get_defaultScriptFile() const", AS_METHOD(Script, GetDefaultScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScene(Scene@+)", AS_METHOD(Script, SetDefaultScene), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "Scene@+ get_defaultScene() const", AS_METHOD(Script, GetDefaultScene), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_executeConsoleCommands(bool)", AS_METHOD(Script, SetExecuteConsoleCommands), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "bool get_executeConsoleCommands() const", AS_METHOD(Script, GetExecuteConsoleCommands), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("Script@+ get_script()", AS_FUNCTION(GetScript), AS_CALL_CDECL);

    /*
    RegisterObject<Script>(engine, "Script");
    engine->RegisterObjectMethod("Script", "bool Execute(const String&in)", AS_METHOD(Script, Execute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void DumpAPI(DumpMode mode = DOXYGEN, const String&in sourceTree = String())", AS_METHOD(Script, DumpAPI), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScriptFile(ScriptFile@+)", AS_METHOD(Script, SetDefaultScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "ScriptFile@+ get_defaultScriptFile() const", AS_METHOD(Script, GetDefaultScriptFile), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScene(Scene@+)", AS_METHOD(Script, SetDefaultScene), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "Scene@+ get_defaultScene() const", AS_METHOD(Script, GetDefaultScene), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_executeConsoleCommands(bool)", AS_METHOD(Script, SetExecuteConsoleCommands), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Script", "bool get_executeConsoleCommands() const", AS_METHOD(Script, GetExecuteConsoleCommands), AS_CALL_THISCALL);
    engine->RegisterGlobalFunction("Script@+ get_script()", AS_FUNCTION(GetScript), AS_CALL_CDECL);
    */
}

static void RegisterScriptObject(asIScriptEngine* engine)
{
    engine->RegisterInterface("ScriptObject");
    engine->SetTypeInfoUserDataCleanupCallback(CleanupTypeInfoScriptInstance, eAttrMapUserIdx);
}

void RegisterScriptInterfaceAPI(asIScriptEngine* engine)
{
    RegisterScriptObject(engine);
}

void RegisterScriptAPI(asIScriptEngine* engine)
{
    RegisterScriptFile(engine);
    RegisterScriptInstance(engine);
    RegisterScript(engine);
}

}
