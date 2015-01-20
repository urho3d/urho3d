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
#include "../Script/APITemplates.h"
#include "../Resource/ResourceCache.h"
#include "../Script/ScriptAPI.h"
#include "../Script/ScriptFile.h"

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
        return 0;

    // Try first to reuse an existing, empty ScriptInstance
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
    {
        if ((*i)->GetType() == ScriptInstance::GetTypeStatic())
        {
            ScriptInstance* instance = static_cast<ScriptInstance*>(i->Get());
            asIScriptObject* object = instance->GetScriptObject();
            if (!object)
            {
                instance->CreateObject(file, className);
                return instance->GetScriptObject();
            }
        }
    }
    // Then create a new component if not found
    ScriptInstance* instance = ptr->CreateComponent<ScriptInstance>(mode);
    instance->CreateObject(file, className);
    return instance->GetScriptObject();
}

static void RegisterScriptFile(asIScriptEngine* engine)
{
    RegisterResource<ScriptFile>(engine, "ScriptFile");
    engine->RegisterObjectMethod("ScriptFile", "bool Execute(const String&in, const Array<Variant>@+ params = null)", asFUNCTION(ScriptFileExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", asFUNCTION(ScriptFileDelayedExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "void ClearDelayedExecute(const String&in declaration = String())", asMETHOD(ScriptFile, ClearDelayedExecute), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptFile", "bool get_compiled() const", asMETHOD(ScriptFile, IsCompiled), asCALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptFile@+ get_scriptFile()", asFUNCTION(GetScriptContextFile), asCALL_CDECL);
}

static asIScriptObject* NodeCreateScriptObject(const String& scriptFileName, const String& className, CreateMode mode, Node* ptr)
{
    ResourceCache* cache = GetScriptContext()->GetSubsystem<ResourceCache>();
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
            ScriptInstance* instance = static_cast<ScriptInstance*>(i->Get());
            asIScriptObject* object = instance->GetScriptObject();
            if (object)
                return object;
        }
    }

    return 0;
}

asIScriptObject* NodeGetNamedScriptObject(const String& className, Node* ptr)
{
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
    {
        if ((*i)->GetType() == ScriptInstance::GetTypeStatic())
        {
            ScriptInstance* instance = static_cast<ScriptInstance*>(i->Get());
            if (instance->GetClassName() == className)
            {
                asIScriptObject* object = instance->GetScriptObject();
                if (object)
                    return object;
            }
        }
    }

    return 0;
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

static void RegisterScriptInstance(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("Node", "ScriptObject@+ CreateScriptObject(ScriptFile@+, const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeCreateScriptObjectWithFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ CreateScriptObject(const String&in, const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeCreateScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ GetScriptObject() const", asFUNCTION(NodeGetScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ GetScriptObject(const String&in) const", asFUNCTION(NodeGetNamedScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Node", "ScriptObject@+ get_scriptObject() const", asFUNCTION(NodeGetScriptObject), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectMethod("Scene", "ScriptObject@+ CreateScriptObject(ScriptFile@+, const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeCreateScriptObjectWithFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ CreateScriptObject(const String&in, const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeCreateScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ GetScriptObject() const", asFUNCTION(NodeGetScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ GetScriptObject(const String&in) const", asFUNCTION(NodeGetNamedScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "ScriptObject@+ get_scriptObject() const", asFUNCTION(NodeGetScriptObject), asCALL_CDECL_OBJLAST);

    RegisterComponent<ScriptInstance>(engine, "ScriptInstance");
    engine->RegisterObjectMethod("ScriptInstance", "bool CreateObject(ScriptFile@+, const String&in)", asMETHODPR(ScriptInstance, CreateObject, (ScriptFile*, const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool Execute(const String&in, const Array<Variant>@+ params = null)", asFUNCTION(ScriptInstanceExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", asFUNCTION(ScriptInstanceDelayedExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void ClearDelayedExecute(const String&in declaration = String())", asMETHOD(ScriptInstance, ClearDelayedExecute), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_scriptFile(ScriptFile@+)", asMETHOD(ScriptInstance, SetScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptFile@+ get_scriptFile() const", asMETHOD(ScriptInstance, GetScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptObject@+ get_scriptObject() const", asMETHOD(ScriptInstance, GetScriptObject), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void set_className(const String&in)", asMETHOD(ScriptInstance, SetClassName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "const String& get_className() const", asMETHOD(ScriptInstance, GetClassName), asCALL_THISCALL);
    engine->RegisterGlobalFunction("ScriptInstance@+ get_self()", asFUNCTION(GetSelf), asCALL_CDECL);

    // Register convenience functions for controlling self, similar to event sending
    engine->RegisterGlobalFunction("void MarkNetworkUpdate()", asFUNCTION(SelfMarkNetworkUpdate), asCALL_CDECL);
    engine->RegisterGlobalFunction("void DelayedExecute(float, bool, const String&in, const Array<Variant>@+ params = null)", asFUNCTION(SelfDelayedExecute), asCALL_CDECL);
    engine->RegisterGlobalFunction("void ClearDelayedExecute(const String&in declaration = String())", asFUNCTION(SelfClearDelayedExecute), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Remove()", asFUNCTION(SelfRemove), asCALL_CDECL);
}

static Script* GetScript()
{
    return GetScriptContext()->GetSubsystem<Script>();
}

static void RegisterScript(asIScriptEngine* engine)
{
    engine->RegisterEnum("DumpMode");
    engine->RegisterEnumValue("DumpMode", "DOXYGEN", DOXYGEN);
    engine->RegisterEnumValue("DumpMode", "C_HEADER", C_HEADER);

    RegisterObject<Script>(engine, "Script");
    engine->RegisterObjectMethod("Script", "bool Execute(const String&in)", asMETHOD(Script, Execute), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void DumpAPI(DumpMode mode = DOXYGEN, const String&in sourceTree = String())", asMETHOD(Script, DumpAPI), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScriptFile(ScriptFile@+)", asMETHOD(Script, SetDefaultScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "ScriptFile@+ get_defaultScriptFile() const", asMETHOD(Script, GetDefaultScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_defaultScene(Scene@+)", asMETHOD(Script, SetDefaultScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "Scene@+ get_defaultScene() const", asMETHOD(Script, GetDefaultScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "void set_executeConsoleCommands(bool)", asMETHOD(Script, SetExecuteConsoleCommands), asCALL_THISCALL);
    engine->RegisterObjectMethod("Script", "bool get_executeConsoleCommands() const", asMETHOD(Script, GetExecuteConsoleCommands), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Script@+ get_script()", asFUNCTION(GetScript), asCALL_CDECL);
}

static void RegisterScriptObject(asIScriptEngine* engine)
{
    engine->RegisterInterface("ScriptObject");
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
