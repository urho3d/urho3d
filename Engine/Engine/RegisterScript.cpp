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
#include "Entity.h"
#include "Log.h"
#include "RegisterTemplates.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"

static bool ScriptFileExecute(const std::string& declaration, CScriptArray* srcParams, ScriptFile* ptr)
{
    if (!srcParams)
        return false;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    return ptr->execute(declaration, destParams);
}

static asIScriptObject* EntityCreateScriptObjectWithFile(ScriptFile* file, const std::string& className, Entity* ptr)
{
    if (!file)
    {
        LOGERROR("Null script file for createScriptObject");
        return 0;
    }
    
    try
    {
        // Try first to reuse an existing, empty ScriptInstance
        const std::vector<SharedPtr<Component> >& components = ptr->getComponents();
        for (std::vector<SharedPtr<Component> >::const_iterator i = components.begin(); i != components.end(); ++i)
        {
            if ((*i)->getType() == ScriptInstance::getTypeStatic())
            {
                ScriptInstance* instance = static_cast<ScriptInstance*>(i->getPtr());
                asIScriptObject* object = instance->getScriptObject();
                if (!object)
                {
                    instance->setScriptClass(file, className);
                    return instance->getScriptObject();
                }
            }
        }
        // Then create a new component if not found
        ScriptInstance* instance = ptr->createComponent<ScriptInstance>(ptr->getUniqueComponentName());
        instance->setScriptClass(file, className);
        return instance->getScriptObject();
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static asIScriptObject* EntityCreateScriptObject(const std::string& scriptFileName, const std::string& className, Entity* ptr)
{
    ResourceCache* cache = getEngine()->getResourceCache();
    return EntityCreateScriptObjectWithFile(cache->getResource<ScriptFile>(scriptFileName), className, ptr);
}

static void registerScriptFile(asIScriptEngine* engine)
{
    registerResource<ScriptFile>(engine, "ScriptFile");
    engine->RegisterObjectMethod("ScriptFile", "bool execute(const string& in, const array<Variant>@+)", asFUNCTION(ScriptFileExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "bool isCompiled() const", asMETHOD(ScriptFile, isCompiled), asCALL_THISCALL);
    registerRefCasts<Resource, ScriptFile>(engine, "Resource", "ScriptFile");
    
    engine->RegisterObjectMethod("Entity", "ScriptObject@+ createScriptObject(ScriptFile@+, const string& in)", asFUNCTION(EntityCreateScriptObjectWithFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Entity", "ScriptObject@+ createScriptObject(const string& in, const string& in)", asFUNCTION(EntityCreateScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("ScriptFile@+ getScriptFile()", asFUNCTION(getScriptContextFile), asCALL_CDECL);
    engine->RegisterGlobalFunction("ScriptFile@+ get_scriptFile()", asFUNCTION(getScriptContextFile), asCALL_CDECL);
}

static bool ScriptInstanceExecute(const std::string& declaration, CScriptArray* srcParams, ScriptInstance* ptr)
{
    if (!srcParams)
        return false;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams;
    destParams.resize(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    return ptr->execute(declaration, destParams);
}

static bool ScriptInstanceExecuteNoParams(const std::string& declaration, ScriptInstance* ptr)
{
    return ptr->execute(declaration);
}

static void ScriptInstanceDelayedExecute(float delay, const std::string& declaration, CScriptArray* srcParams, ScriptInstance* ptr)
{
    if (!srcParams)
        return;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams;
    destParams.resize(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    ptr->delayedExecute(delay, declaration, destParams);
}

static void ScriptInstanceDelayedExecuteNoParams(float delay, const std::string& declaration, ScriptInstance* ptr)
{
    ptr->delayedExecute(delay, declaration);
}

static ScriptInstance* GetSelf()
{
    return getScriptContextInstance();
}

static void SelfDelayedExecute(float delay, const std::string& declaration, CScriptArray* srcParams)
{
    ScriptInstance* ptr = getScriptContextInstance();
    if ((!ptr) || (!srcParams))
        return;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams;
    destParams.resize(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    ptr->delayedExecute(delay, declaration, destParams);
}

static void SelfDelayedExecuteNoParams(float delay, const std::string& declaration)
{
    ScriptInstance* ptr = getScriptContextInstance();
    if (!ptr)
        return;
    
    ptr->delayedExecute(delay, declaration);
}

static void SelfClearDelayedExecute()
{
    ScriptInstance* ptr = getScriptContextInstance();
    if (!ptr)
        return;
    
    ptr->clearDelayedExecute();
}

static void registerScriptInstance(asIScriptEngine* engine)
{
    registerComponent<ScriptInstance>(engine, "ScriptInstance");
    engine->RegisterObjectMethod("ScriptInstance", "bool setScriptClass(ScriptFile@+, const string& in)", asMETHOD(ScriptInstance, setScriptClass), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void setEnabled(bool)", asMETHOD(ScriptInstance, setEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void setFixedUpdateFps(int)", asMETHOD(ScriptInstance, setFixedUpdateFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool execute(const string& in, const array<Variant>@+)", asFUNCTION(ScriptInstanceExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "bool execute(const string& in)", asFUNCTION(ScriptInstanceExecuteNoParams), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void delayedExecute(float, const string& in, const array<Variant>@+)", asFUNCTION(ScriptInstanceDelayedExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void delayedExecute(float, const string& in)", asFUNCTION(ScriptInstanceDelayedExecuteNoParams), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "void clearDelayedExecute()", asMETHOD(ScriptInstance, clearDelayedExecute), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptFile@+ getScriptFile() const", asMETHOD(ScriptInstance, getScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptObject@+ getScriptObject() const", asMETHOD(ScriptInstance, getScriptObject), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "const string& getClassName() const", asMETHOD(ScriptInstance, getClassName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool isEnabled() const", asMETHOD(ScriptInstance, isEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "int getFixedUpdateFps() const", asMETHOD(ScriptInstance, getFixedUpdateFps), asCALL_THISCALL);
    registerRefCasts<Component, ScriptInstance>(engine, "Component", "ScriptInstance");
    
    engine->RegisterGlobalFunction("ScriptInstance@+ getSelf()", asFUNCTION(GetSelf), asCALL_CDECL);
    engine->RegisterGlobalFunction("ScriptInstance@+ get_self()", asFUNCTION(GetSelf), asCALL_CDECL);
    engine->RegisterGlobalFunction("void delayedExecute(float, const string& in, const array<Variant>@+)", asFUNCTION(SelfDelayedExecute), asCALL_CDECL);
    engine->RegisterGlobalFunction("void delayedExecute(float, const string& in)", asFUNCTION(SelfDelayedExecuteNoParams), asCALL_CDECL);
    engine->RegisterGlobalFunction("void clearDelayedExecute()", asFUNCTION(SelfClearDelayedExecute), asCALL_CDECL);
}

static bool ScriptEngineExecute(const std::string& line)
{
    ScriptEngine* scriptEngine = getEngine()->getScriptEngine();
    return scriptEngine->execute(line);
}

static void ScriptEngineGarbageCollect()
{
    ScriptEngine* scriptEngine = getEngine()->getScriptEngine();
    // Perform a full cycle
    scriptEngine->garbageCollect(true);
}

static void registerScriptEngine(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("bool execute(const string& in)", asFUNCTION(ScriptEngineExecute), asCALL_CDECL);
    engine->RegisterGlobalFunction("void garbageCollect()", asFUNCTION(ScriptEngineGarbageCollect), asCALL_CDECL);
}

void registerScriptLibrary(asIScriptEngine* engine)
{
    registerScriptFile(engine);
    registerScriptInstance(engine);
    registerScriptEngine(engine);
}
