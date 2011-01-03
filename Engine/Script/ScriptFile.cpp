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
#include "Deserializer.h"
#include "Log.h"
#include "Profiler.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "SharedArrayPtr.h"

#include <angelscript.h>

#include "DebugNew.h"

static const int MAX_NESTING_LEVEL = 100;
static int executeNestingLevel = 0;

ScriptFile::ScriptFile(ScriptEngine* scriptEngine, const std::string& name) :
    Resource(name),
    mScriptEngine(scriptEngine),
    mScriptModule(0),
    mCompiled(false)
{
    if (!mScriptEngine)
        EXCEPTION("Null script engine");
}

ScriptFile::~ScriptFile()
{
    if (mScriptModule)
    {
        asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
        engine->DiscardModule(getName().c_str());
        mScriptModule = 0;
    }
}

void ScriptFile::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Script_Load);
    
    unsigned dataSize = source.getSize();
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.read((void*)buffer.getPtr(), dataSize);
    
    // Discard the previous module if there was one
    setMemoryUse(0);
    mCompiled = false;
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    mScriptModule = engine->GetModule(getName().c_str(), asGM_ALWAYS_CREATE);
    
    if (!mScriptModule)
        EXCEPTION("Failed to create script module " + getName());
    if (mScriptModule->AddScriptSection(getName().c_str(), (const char*)buffer.getPtr(), dataSize) < 0)
        EXCEPTION("Failed to add script section for script module " + getName());
    if (mScriptModule->Build() < 0)
        EXCEPTION("Failed to build script module " + getName());
    
    LOGINFO("Compiled script module " + getName());
    
    setMemoryUse(dataSize);
    mCompiled = true;
}

bool ScriptFile::execute(const std::string& declaration, asIScriptContext* context, const std::vector<Variant>& parameters)
{
    asIScriptFunction* function = getFunction(declaration);
    if (!function)
    {
        LOGERROR("Function " + declaration + " not found in " + getName());
        return false;
    }
    
    return execute(getFunction(declaration), context, parameters);
}

bool ScriptFile::execute(asIScriptFunction* function, asIScriptContext* context, const std::vector<Variant>& parameters)
{
    PROFILE(Script_Execute);
    
    if ((!mCompiled) || (!function))
        return false;
    
    if (!context)
        context = mScriptEngine->getImmediateContext();
    
    if (context->GetState() != asEXECUTION_ACTIVE)
    {
        if (context->Prepare(function->GetId()) < 0)
            return false;
        setParameters(context, function, parameters);
        return context->Execute() >= 0;
    }
    else
    {
        // Prevent endless loop by nested script event handling
        if (executeNestingLevel > MAX_NESTING_LEVEL)
        {
            LOGERROR("Maximum script execution nesting level exceeded");
            return false;
        }
        
        // If context is active, allocate a temp context to allow nested execution.
        // This is not recommended for performance reasons
        LOGDEBUG("Executing " + std::string(function->GetDeclaration()) + " in a temporary script context");
        asIScriptContext* tempContext = mScriptEngine->createScriptContext();
        tempContext->SetUserData(context->GetUserData());
        if (tempContext->Prepare(function->GetId()) < 0)
        {
            tempContext->Release();
            return false;
        }
        setParameters(tempContext, function, parameters);
        
        ++executeNestingLevel;
        bool success = tempContext->Execute() >= 0;
        tempContext->Release();
        --executeNestingLevel;
        
        return success;
    }
}

bool ScriptFile::execute(asIScriptObject* object, const std::string& declaration, asIScriptContext* context, const std::vector<Variant>& parameters)
{
    asIScriptFunction* method = getMethod(object, declaration);
    if (!method)
    {
        LOGERROR("Method " + declaration + " not found in " + getName());
        return false;
    }
    
    return execute(object, method, context, parameters);
}

bool ScriptFile::execute(asIScriptObject* object, asIScriptFunction* method, asIScriptContext* context,
    const std::vector<Variant>& parameters)
{
    PROFILE(Script_Execute);
    
    if ((!mCompiled) || (!object) || (!method))
        return false;
    
    if (!context)
        context = mScriptEngine->getImmediateContext();
    
    if (context->GetState() != asEXECUTION_ACTIVE)
    {
        if (context->Prepare(method->GetId()) < 0)
            return false;
        context->SetObject(object);
        setParameters(context, method, parameters);
        return context->Execute() >= 0;
    }
    else
    {
        // Prevent endless loop by nested script event handling
        if (executeNestingLevel > MAX_NESTING_LEVEL)
        {
            LOGERROR("Maximum script execution nesting level exceeded");
            return false;
        }
        
        // If context is active, allocate a temp context to allow nested execution.
        // This is not recommended for performance reasons
        LOGDEBUG("Executing " + std::string(method->GetDeclaration()) + " in a temporary script context");
        asIScriptContext* tempContext = mScriptEngine->createScriptContext();
        tempContext->SetUserData(context->GetUserData());
        if (tempContext->Prepare(method->GetId()) < 0)
        {
            tempContext->Release();
            return false;
        }
        tempContext->SetObject(object);
        setParameters(tempContext, method, parameters);
        
        ++executeNestingLevel;
        bool success = tempContext->Execute() >= 0;
        tempContext->Release();
        --executeNestingLevel;
        
        return success;
    }
}

asIScriptObject* ScriptFile::createObject(const std::string& className, asIScriptContext* context)
{
    PROFILE(Script_CreateObject);
    
    if (!isCompiled())
        return 0;
    
    if (!context)
        context = mScriptEngine->getImmediateContext();
    
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    asIObjectType *type = engine->GetObjectTypeById(mScriptModule->GetTypeIdByDecl(className.c_str()));
    if (!type)
        return 0;
    
    // Get the factory function id from the object type
    std::string factoryName = className + "@ " + className + "()";
    int factoryId = type->GetFactoryIdByDecl(factoryName.c_str());
    if (factoryId < 0)
        return 0;
    if (context->Prepare(factoryId) < 0)
        return 0;
    if (context->Execute() < 0)
        return 0;
    
    asIScriptObject* obj = *(static_cast<asIScriptObject**>(context->GetAddressOfReturnValue()));
    if (obj)
        obj->AddRef();
    
    return obj;
}

asIScriptFunction* ScriptFile::getFunction(const std::string& declaration) const
{
    if (!mCompiled)
        return 0;
    
    int id = mScriptModule->GetFunctionIdByDecl(declaration.c_str());
    return mScriptModule->GetFunctionDescriptorById(id);
}

asIScriptFunction* ScriptFile::getMethod(asIScriptObject* object, const std::string& declaration) const
{
    if ((!mCompiled) || (!object))
        return 0;
    
    asIObjectType* type = object->GetObjectType();
    if (!type)
        return 0;
    
    int id = type->GetMethodIdByDecl(declaration.c_str());
    return mScriptModule->GetFunctionDescriptorById(id);
}

void ScriptFile::setParameters(asIScriptContext* context, asIScriptFunction* function, const std::vector<Variant>& parameters)
{
    unsigned paramCount = function->GetParamCount();
    for (unsigned i = 0; (i < parameters.size()) && (i < paramCount); ++i)
    {
        int paramType = function->GetParamTypeId(i);
        
        switch (paramType)
        {
        case asTYPEID_BOOL:
            context->SetArgByte(i, (unsigned char)parameters[i].getBool());
            break;
            
        case asTYPEID_INT8:
        case asTYPEID_UINT8:
            context->SetArgByte(i, parameters[i].getInt());
            break;
            
        case asTYPEID_INT16:
        case asTYPEID_UINT16:
            context->SetArgWord(i, parameters[i].getInt());
            break;
            
        case asTYPEID_INT32:
        case asTYPEID_UINT32:
            context->SetArgDWord(i, parameters[i].getInt());
            break;
            
        case asTYPEID_FLOAT:
            context->SetArgFloat(i, parameters[i].getFloat());
            break;
            
        default:
            if (paramType & asTYPEID_APPOBJECT)
            {
                switch (parameters[i].getType())
                {
                case VAR_VECTOR2:
                    context->SetArgObject(i, (void *)&parameters[i].getVector2());
                    break;
                case VAR_VECTOR3:
                    context->SetArgObject(i, (void *)&parameters[i].getVector3());
                    break;
                case VAR_VECTOR4:
                    context->SetArgObject(i, (void *)&parameters[i].getVector4());
                    break;
                case VAR_QUATERNION:
                    context->SetArgObject(i, (void *)&parameters[i].getQuaternion());
                    break;
                case VAR_STRING:
                    context->SetArgObject(i, (void *)&parameters[i].getString());
                    break;
                case VAR_PTR:
                    context->SetArgObject(i, (void *)parameters[i].getPtr());
                    break;
                }
            }
            break;
        }
    }
}
