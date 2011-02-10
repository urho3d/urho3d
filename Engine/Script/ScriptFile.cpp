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
#include "ScriptInstance.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <angelscript.h>
#include <cstring>

#include "DebugNew.h"

static unsigned scriptNestingLevel = 0;
static unsigned highestScriptNestingLevel = 0;
ScriptFile* lastScriptFile = 0;

std::map<asIScriptModule*, ScriptFile*> moduleToFile;

ScriptFile::ScriptFile(ScriptEngine* scriptEngine, const std::string& name) :
    Resource(name),
    mScriptEngine(scriptEngine),
    mScriptModule(0),
    mCompiled(false)
{
    if (!mScriptEngine)
        EXCEPTION("Null script engine for ScriptFile");
}

ScriptFile::~ScriptFile()
{
    if (mScriptModule)
    {
        // Release script instances if any exist
        std::vector<ScriptInstance*> instances = mScriptInstances;
        for (std::vector<ScriptInstance*>::iterator i = instances.begin(); i != instances.end(); ++i)
            (*i)->releaseObject();
        
        // Perform a full garbage collection cycle, also clean up contexts which might still refer to the module's functions
        mScriptEngine->garbageCollect(true);
        
        // Remove the module
        moduleToFile.erase(mScriptModule);
        asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
        engine->DiscardModule(getName().c_str());
        mScriptModule = 0;
    }
    if (lastScriptFile == this)
        lastScriptFile = 0;
}

void ScriptFile::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Script_Load);
    
    // If script instances have created objects from this file, release them now
    // Make a copy of the vector because the script instances will remove themselves from the member vector
    std::vector<ScriptInstance*> instances = mScriptInstances;
    for (std::vector<ScriptInstance*>::iterator i = instances.begin(); i != instances.end(); ++i)
        (*i)->releaseObject();
    
    // Clear search caches, event handlers and function-to-file mappings
    mCompiled = false;
    mAllIncludeFiles.clear();
    mCheckedClasses.clear();
    mFunctions.clear();
    mMethods.clear();
    setMemoryUse(0);
    removeAllEventHandlers();
    
    // Create the module. Discard previous module if there was one
    if (mScriptModule)
        moduleToFile.erase(mScriptModule);
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    mScriptModule = engine->GetModule(getName().c_str(), asGM_ALWAYS_CREATE);
    if (!mScriptModule)
        EXCEPTION("Failed to create script module " + getName());
    
    // Add the initial section and check for includes
    addScriptSection(engine, source, cache);
    
    // Compile. Set script engine logging to retained mode so that potential exceptions can show all error info
    mScriptEngine->setLogMode(LOGMODE_RETAINED);
    mScriptEngine->clearLogMessages();
    int result = mScriptModule->Build();
    std::string errors = mScriptEngine->getLogMessages();
    mScriptEngine->setLogMode(LOGMODE_IMMEDIATE);
    if (result < 0)
        EXCEPTION("Failed to compile script module " + getName() + ":\n" + errors);
    if (!errors.empty())
        LOGWARNING(errors);
    
    LOGINFO("Compiled script module " + getName());
    mCompiled = true;
    moduleToFile[mScriptModule] = this;
    
    // Now let the script instances recreate their objects
    for (std::vector<ScriptInstance*>::iterator i = instances.begin(); i != instances.end(); ++i)
        (*i)->createObject();
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
}

void ScriptFile::addEventHandler(EventListener* sender, StringHash eventType, const std::string& handlerName)
{
    if ((!mCompiled) || (!sender))
        return;
    
    std::string declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* function = getFunction(declaration);
    if (!function)
    {
        LOGERROR("Event handler function " + declaration + " not found in " + getName());
        return;
    }
    
    subscribeToEvent(sender, eventType, EVENT_HANDLER(ScriptFile, handleSpecificScriptEvent));
    mSpecificEventHandlers[std::make_pair(sender, eventType)] = function;
}

bool ScriptFile::execute(const std::string& declaration, const std::vector<Variant>& parameters)
{
    asIScriptFunction* function = getFunction(declaration);
    if (!function)
    {
        LOGERROR("Function " + declaration + " not found in " + getName());
        return false;
    }
    
    return execute(getFunction(declaration), parameters);
}

bool ScriptFile::execute(asIScriptFunction* function, const std::vector<Variant>& parameters)
{
    PROFILE(Script_ExecuteFunction);
    
    if ((!mCompiled) || (!function))
        return false;
    
    // Prevent endless loop by nested script execution
    if (scriptNestingLevel >= MAX_SCRIPT_NESTING_LEVEL)
    {
        LOGERROR("Maximum script execution nesting level exceeded");
        return false;
    }
    
    asIScriptContext* context = mScriptEngine->getScriptFileContext(scriptNestingLevel);
    
    if (context->Prepare(function->GetId()) < 0)
        return false;
    
    lastScriptFile = this;
    setParameters(context, function, parameters);
    
    ++scriptNestingLevel;
    if (scriptNestingLevel > highestScriptNestingLevel)
        highestScriptNestingLevel = scriptNestingLevel;
    bool success = context->Execute() >= 0;
    --scriptNestingLevel;
    
    return success;
}

bool ScriptFile::execute(asIScriptObject* object, const std::string& declaration, const std::vector<Variant>& parameters)
{
    asIScriptFunction* method = getMethod(object, declaration);
    if (!method)
    {
        LOGERROR("Method " + declaration + " not found in " + getName());
        return false;
    }
    
    return execute(object, method, parameters);
}

bool ScriptFile::execute(asIScriptObject* object, asIScriptFunction* method, const std::vector<Variant>& parameters)
{
    PROFILE(Script_ExecuteMethod);
    
    if ((!mCompiled) || (!object) || (!method))
        return false;
    
    // Prevent endless loop by nested script execution
    if (scriptNestingLevel >= MAX_SCRIPT_NESTING_LEVEL)
    {
        LOGERROR("Maximum script execution nesting level exceeded");
        return false;
    }
    
    asIScriptContext* context = mScriptEngine->getScriptFileContext(scriptNestingLevel);
    
    // If context is active, allocate a temp context to allow nested execution.
    if (context->Prepare(method->GetId()) < 0)
        return false;

    context->SetObject(object);
    setParameters(context, method, parameters);
    
    ++scriptNestingLevel;
    if (scriptNestingLevel > highestScriptNestingLevel)
        highestScriptNestingLevel = scriptNestingLevel;
    bool success = context->Execute() >= 0;
    --scriptNestingLevel;
    
    return success;
}

asIScriptObject* ScriptFile::createObject(const std::string& className)
{
    PROFILE(Script_CreateObject);
    
    if (!isCompiled())
        return 0;
    
    // Prevent endless loop by nested script execution
    if (scriptNestingLevel >= MAX_SCRIPT_NESTING_LEVEL)
    {
        LOGERROR("Maximum script execution nesting level exceeded, can not create object");
        return 0;
    }
    
    asIScriptContext* context = mScriptEngine->getScriptFileContext(scriptNestingLevel);
    asIScriptEngine* engine = mScriptEngine->getAngelScriptEngine();
    asIObjectType *type = engine->GetObjectTypeById(mScriptModule->GetTypeIdByDecl(className.c_str()));
    if (!type)
        return 0;
    
    // Ensure that the type implements the "ScriptObject" interface, so it can be returned to script properly
    bool found = false;
    std::map<asIObjectType*, bool>::const_iterator i = mCheckedClasses.find(type);
    if (i != mCheckedClasses.end())
        found = i->second;
    else
    {
        unsigned numInterfaces = type->GetInterfaceCount();
        for (unsigned j = 0; j < numInterfaces; ++j)
        {
            asIObjectType* interfaceType = type->GetInterface(j);
            if (!strcmp(interfaceType->GetName(), "ScriptObject"))
            {
                found = true;
                break;
            }
        }
        mCheckedClasses[type] = found;
    }
    if (!found)
    {
        LOGERROR("Script class " + className + " does not implement the ScriptObject interface");
        return 0;
    }
    
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

asIScriptFunction* ScriptFile::getFunction(const std::string& declaration)
{
    if (!mCompiled)
        return 0;
    
    std::map<std::string, asIScriptFunction*>::const_iterator i = mFunctions.find(declaration);
    if (i != mFunctions.end())
        return i->second;
    
    int id = mScriptModule->GetFunctionIdByDecl(declaration.c_str());
    asIScriptFunction* function = mScriptModule->GetFunctionDescriptorById(id);
    mFunctions[declaration] = function;
    return function;
}

asIScriptFunction* ScriptFile::getMethod(asIScriptObject* object, const std::string& declaration)
{
    if ((!mCompiled) || (!object))
        return 0;
    
    asIObjectType* type = object->GetObjectType();
    if (!type)
        return 0;
    std::map<asIObjectType*, std::map<std::string, asIScriptFunction*> >::const_iterator i = mMethods.find(type);
    if (i != mMethods.end())
    {
        std::map<std::string, asIScriptFunction*>::const_iterator j = i->second.find(declaration);
        if (j != i->second.end())
            return j->second;
    }
    
    int id = type->GetMethodIdByDecl(declaration.c_str());
    asIScriptFunction* function = mScriptModule->GetFunctionDescriptorById(id);
    mMethods[type][declaration] = function;
    return function;
}

void ScriptFile::addScriptInstance(ScriptInstance* instance)
{
    mScriptInstances.push_back(instance);
}

void ScriptFile::removeScriptInstance(ScriptInstance* instance)
{
    for (std::vector<ScriptInstance*>::iterator i = mScriptInstances.begin(); i != mScriptInstances.end(); ++i)
    {
        if ((*i) == instance)
        {
            mScriptInstances.erase(i);
            break;
        }
    }
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
    execute(i->second, parameters);
}

void ScriptFile::handleSpecificScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if (!mCompiled)
        return;
    
    std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator i = mSpecificEventHandlers.find(std::make_pair(
        getEventSender(), eventType));
    if (i == mSpecificEventHandlers.end())
        return;
    
    std::vector<Variant> parameters;
    parameters.push_back(Variant((void*)&eventType));
    parameters.push_back(Variant((void*)&eventData));
    execute(i->second, parameters);
}

ScriptFile* getScriptContextFile()
{
    asIScriptFunction* function = asGetActiveContext()->GetFunction();
    asIScriptModule* module = function->GetEngine()->GetModule(function->GetModuleName());
    std::map<asIScriptModule*, ScriptFile*>::const_iterator i = moduleToFile.find(module);
    if (i != moduleToFile.end())
        return i->second;
    else
        return 0;
}

unsigned getScriptNestingLevel()
{
    return scriptNestingLevel;
}

unsigned getHighestScriptNestingLevel(bool reset)
{
    unsigned ret = highestScriptNestingLevel;
    if (reset)
        highestScriptNestingLevel = 0;
    return ret;
}
