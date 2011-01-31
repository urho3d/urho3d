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
#include "Engine.h"
#include "Entity.h"
#include "RegisterTemplates.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"

static bool ScriptFileExecute(const std::string& functionName, CScriptArray* srcParams, ScriptFile* ptr)
{
    if (!srcParams)
        return false;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams;
    destParams.resize(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    return ptr->execute(functionName, destParams);
}

static void registerScriptFile(asIScriptEngine* engine)
{
    registerResource<ScriptFile>(engine, "ScriptFile");
    engine->RegisterObjectMethod("ScriptFile", "bool execute(const string& in, const array<Variant>@+)", asFUNCTION(ScriptFileExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptFile", "bool isCompiled() const", asMETHOD(ScriptFile, isCompiled), asCALL_THISCALL);
    registerRefCasts<Resource, ScriptFile>(engine, "Resource", "ScriptFile");
}

static bool ScriptInstanceExecute(const std::string& methodName, CScriptArray* srcParams, ScriptInstance* ptr)
{
    if (!srcParams)
        return false;
    
    unsigned numParams = srcParams->GetSize();
    std::vector<Variant> destParams;
    destParams.resize(numParams);
    
    for (unsigned i = 0; i < numParams; ++i)
        destParams[i] = *(static_cast<Variant*>(srcParams->At(i)));
    
    return ptr->execute(methodName, destParams);
}

static ScriptInstance* GetSelf()
{
    return getScriptContextComponent();
}

static void registerScriptInstance(asIScriptEngine* engine)
{
    registerComponent<ScriptInstance>(engine, "ScriptInstance");
    engine->RegisterInterface("ScriptObject");
    engine->RegisterObjectMethod("ScriptInstance", "bool setScriptClass(ScriptFile@+, const string& in)", asMETHOD(ScriptInstance, setScriptClass), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "void setEnabled(bool)", asMETHOD(ScriptInstance, setEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool execute(const string& in, const array<Variant>@+)", asFUNCTION(ScriptInstanceExecute), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptFile@+ getScriptFile() const", asMETHOD(ScriptInstance, getScriptFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "ScriptObject@+ getScriptObject() const", asMETHOD(ScriptInstance, getScriptObject), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "const string& getClassName() const", asMETHOD(ScriptInstance, getClassName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool isRunning() const", asMETHOD(ScriptInstance, isRunning), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScriptInstance", "bool isEnabled() const", asMETHOD(ScriptInstance, isEnabled), asCALL_THISCALL);
    registerRefCasts<Component, ScriptInstance>(engine, "Component", "ScriptInstance");
    
    engine->RegisterGlobalFunction("ScriptInstance@+ getSelf()", asFUNCTION(GetSelf), asCALL_CDECL);
    engine->RegisterGlobalFunction("ScriptInstance@+ get_self()", asFUNCTION(GetSelf), asCALL_CDECL);
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
