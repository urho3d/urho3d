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
#include "File.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <angelscript.h>
#include <cstring>

#include "DebugNew.h"

static const int MAX_NESTING_LEVEL = 32;
static int executeNestingLevel = 0;
ScriptFile* lastScriptFile = 0;

ScriptFile::ScriptFile(ScriptEngine* scriptEngine, const std::string& name) :
    Resource(name),
    mScriptEngine(scriptEngine),
    mScriptModule(0),
    mScriptContext(0),
    mCompiled(false)
{
    if (!mScriptEngine)
        EXCEPTION("Null script engine for ScriptFile");
}

ScriptFile::~ScriptFile()
{
    if (mScriptModule)
    {
        asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
        engine->DiscardModule(getName().c_str());
        mScriptModule = 0;
    }
    if (mScriptContext)
    {
        mScriptContext->Release();
        mScriptContext = 0;
    }
    if (lastScriptFile == this)
        lastScriptFile = 0;
}

void ScriptFile::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Script_Load);
    
    // Discard the previous module if there was one
    mCompiled = false;
    mAllIncludeFiles.clear();
    setMemoryUse(0);
    removeAllEventHandlers();
    
    // Create the module
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    mScriptModule = engine->GetModule(getName().c_str(), asGM_ALWAYS_CREATE);
    if (!mScriptModule)
        EXCEPTION("Failed to create script module " + getName());
    
    // Add the initial section and check for includes
    addScriptSection(engine, source, cache);
    
    // Compile
    if (mScriptModule->Build() < 0)
        EXCEPTION("Failed to build script module " + getName());
    
    LOGINFO("Compiled script module " + getName());
    mCompiled = true;
}

void ScriptFile::addEventHandler(StringHash eventType, const std::string& handlerName)
{
    if (!mCompiled)
        return;
    
    std::string declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* function = getFunction(declaration);
    if (!function)
    {
        LOGERROR("Event handler function " + declaration + " not found in " + getName());
        return;
    }
    
    subscribeToEvent(eventType, EVENT_HANDLER(ScriptFile, handleScriptEvent));
    mEventHandlers[eventType] = function;
    
    // Create a context for script event handling if does not exist already
    if (!mScriptContext)
        mScriptContext = mScriptEngine->createScriptContext();
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
    PROFILE(Script_ExecuteFunction);
    
    if ((!mCompiled) || (!function))
        return false;
    
    if (!context)
        context = mScriptEngine->getImmediateContext();
    
    if (context->GetState() != asEXECUTION_ACTIVE)
    {
        if (context->Prepare(function->GetId()) < 0)
            return false;
        lastScriptFile = this;
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
        lastScriptFile = this;
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
    PROFILE(Script_ExecuteMethod);
    
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

void ScriptFile::addScriptSection(asIScriptEngine* engine, Deserializer& source, ResourceCache* cache)
{
    unsigned dataSize = source.getSize();
    SharedArrayPtr<char> buffer(new char[dataSize]);
    source.read((void*)buffer.getPtr(), dataSize);
    
    // Pre-parse for includes
    // Adapted from Angelscript's scriptbuilder add-on
    std::vector<std::string> includeFiles;
    unsigned pos = 0;
    while(pos < dataSize)
    {
        int len;
        asETokenClass t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
        if ((t == asTC_COMMENT) || (t == asTC_WHITESPACE))
        {
            pos += len;
            continue;
        }
        // Is this a preprocessor directive?
        if (buffer[pos] == '#')
        {
            int start = pos++;
            asETokenClass t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
            if (t == asTC_IDENTIFIER)
            {
                std::string token(&buffer[pos], len);
                if (token == "include")
                {
                    pos += len;
                    t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
                    if (t == asTC_WHITESPACE)
                    {
                        pos += len;
                        t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
                    }
                    
                    if ((t == asTC_VALUE) && (len > 2) && (buffer[pos] == '"'))
                    {
                        // Get the include file
                        std::string includeFile(&buffer[pos+1], len - 2);
                        pos += len;
                        
                        // If the file is not found as it is, add the path of current file
                        if (!cache->exists(includeFile))
                            includeFile = getPath(getName()) + includeFile;
                        
                        std::string includeFileLower = toLower(includeFile);
                        
                        // If not included yet, store it for later processing
                        if (mAllIncludeFiles.find(includeFileLower) == mAllIncludeFiles.end())
                        {
                            mAllIncludeFiles.insert(includeFileLower);
                            includeFiles.push_back(includeFile);
                        }
                        
                        // Overwrite the include directive with space characters to avoid compiler error
                        memset(&buffer[start], ' ', pos - start);
                    }
                }
            }
        }
        // Don't search includes within statement blocks or between tokens in statements
        else
        {
            int len;
            // Skip until ; or { whichever comes first
            while ((pos < dataSize) && (buffer[pos] != ';') && (buffer[pos] != '{' ))
            {
                engine->ParseToken(&buffer[pos], 0, &len);
                pos += len;
            }
            // Skip entire statement block
            if ((pos < dataSize) && (buffer[pos] == '{' ))
            {
                ++pos;
                // Find the end of the statement block
                int level = 1;
                while ((level > 0) && (pos < dataSize))
                {
                    asETokenClass t = engine->ParseToken(&buffer[pos], 0, &len);
                    if (t == asTC_KEYWORD)
                    {
                        if (buffer[pos] == '{')
                            level++;
                        else if(buffer[pos] == '}')
                            level--;
                    }
                    pos += len;
                }
            }
            else
                ++pos;
        }
    }
    
    // Process includes first
    for (unsigned i = 0; i < includeFiles.size(); ++i)
    {
        SharedPtr<File> file = cache->getFile(includeFiles[i]);
        addScriptSection(engine, *file, cache);
    }
    
    // Then add this section
    if (mScriptModule->AddScriptSection(source.getName().c_str(), (const char*)buffer.getPtr(), dataSize) < 0)
        EXCEPTION("Failed to add script section " + source.getName());
    
    setMemoryUse(getMemoryUse() + dataSize);
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

void ScriptFile::handleScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if (!mCompiled)
        return;
    
    std::map<StringHash, asIScriptFunction*>::iterator i = mEventHandlers.find(eventType);
    if (i == mEventHandlers.end())
        return;
    
    std::vector<Variant> parameters;
    parameters.push_back(Variant((void*)&eventType));
    parameters.push_back(Variant((void*)&eventData));
    execute(i->second, mScriptContext, parameters);
}

ScriptFile* getLastScriptFile()
{
    return lastScriptFile;
}
