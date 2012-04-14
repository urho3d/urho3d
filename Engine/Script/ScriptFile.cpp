//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "ArrayPtr.h"
#include "Context.h"
#include "FileSystem.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Script.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"

#include <angelscript.h>
#include <cstring>

#include "DebugNew.h"

OBJECTTYPESTATIC(ScriptFile);

ScriptFile::ScriptFile(Context* context) :
    Resource(context),
    script_(GetSubsystem<Script>()),
    scriptModule_(0),
    compiled_(false)
{
}

ScriptFile::~ScriptFile()
{
    ReleaseModule();
}

void ScriptFile::RegisterObject(Context* context)
{
    context->RegisterFactory<ScriptFile>();
}

bool ScriptFile::Load(Deserializer& source)
{
    PROFILE(LoadScript);
    
    ReleaseModule();
    
    // Create the module. Discard previous module if there was one
    if (scriptModule_)
        script_->GetModuleMap().Erase(scriptModule_);
    asIScriptEngine* engine = script_->GetScriptEngine();
    scriptModule_ = engine->GetModule(GetName().CString(), asGM_ALWAYS_CREATE);
    if (!scriptModule_)
    {
        LOGERROR("Failed to create script module " + GetName());
        return false;
    }
    
    // Add the initial section and check for includes
    if (!AddScriptSection(engine, source))
        return false;
    
    // Compile. Set script engine logging to retained mode so that potential exceptions can show all error info
    script_->SetLogMode(LOGMODE_RETAINED);
    script_->ClearLogMessages();
    int result = scriptModule_->Build();
    String errors = script_->GetLogMessages();
    script_->SetLogMode(LOGMODE_IMMEDIATE);
    if (result < 0)
    {
        LOGERROR("Failed to compile script module " + GetName() + ":\n" + errors);
        return false;
    }
    if (!errors.Empty())
        LOGWARNING(errors);
    
    LOGINFO("Compiled script module " + GetName());
    compiled_ = true;
    script_->GetModuleMap()[scriptModule_] = this;
    
    return true;
}

void ScriptFile::AddEventHandler(StringHash eventType, const String& handlerName)
{
    if (!compiled_)
        return;
    
    String declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* function = GetFunction(declaration);
    if (!function)
    {
        declaration = "void " + handlerName + "()";
        function = GetFunction(declaration);
        if (!function)
        {
            LOGERROR("Event handler function " + handlerName + " not found in " + GetName());
            return;
        }
    }
    
    SubscribeToEvent(eventType, HANDLER_USERDATA(ScriptFile, HandleScriptEvent, (void*)function));
}

void ScriptFile::AddEventHandler(Object* sender, StringHash eventType, const String& handlerName)
{
    if (!compiled_)
        return;
    
    if (!sender)
    {
        LOGERROR("Null event sender for event " + String(eventType) + ", handler " + handlerName);
        return;
    }
    
    String declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* function = GetFunction(declaration);
    if (!function)
    {
        declaration = "void " + handlerName + "()";
        function = GetFunction(declaration);
        if (!function)
        {
            LOGERROR("Event handler function " + handlerName + " not found in " + GetName());
            return;
        }
    }
    
    SubscribeToEvent(sender, eventType, HANDLER_USERDATA(ScriptFile, HandleScriptEvent, (void*)function));
}

bool ScriptFile::Execute(const String& declaration, const VariantVector& parameters, bool unprepare)
{
    asIScriptFunction* function = GetFunction(declaration);
    if (!function)
    {
        LOGERROR("Function " + declaration + " not found in " + GetName());
        return false;
    }
    
    return Execute(GetFunction(declaration), parameters, unprepare);
}

bool ScriptFile::Execute(asIScriptFunction* function, const VariantVector& parameters, bool unprepare)
{
    PROFILE(ExecuteFunction);
    
    if (!compiled_ || !function)
        return false;
    
    // It is possible that executing the function causes us to unload. Therefore do not rely on member variables
    // However, we are not prepared for the whole script system getting destroyed during execution (should never happen)
    Script* scriptSystem = script_;
    
    asIScriptContext* context = scriptSystem->GetScriptFileContext();
    if (!context)
    {
        LOGERROR("Maximum script execution nesting level exceeded");
        return false;
    }
    
    if (context->Prepare(function) < 0)
        return false;
    
    SetParameters(context, function, parameters);
    
    scriptSystem->IncScriptNestingLevel();
    bool success = context->Execute() >= 0;
    if (unprepare)
        context->Unprepare();
    scriptSystem->DecScriptNestingLevel();
    
    return success;
}

bool ScriptFile::Execute(asIScriptObject* object, const String& declaration, const VariantVector& parameters, bool unprepare)
{
    asIScriptFunction* method = GetMethod(object, declaration);
    if (!method)
    {
        LOGERROR("Method " + declaration + " not found in " + GetName());
        return false;
    }
    
    return Execute(object, method, parameters, unprepare);
}

bool ScriptFile::Execute(asIScriptObject* object, asIScriptFunction* method, const VariantVector& parameters, bool unprepare)
{
    PROFILE(ExecuteMethod);
    
    if (!compiled_ || !object || !method)
        return false;
    
    // It is possible that executing the method causes us to unload. Therefore do not rely on member variables
    // However, we are not prepared for the whole script system getting destroyed during execution (should never happen)
    Script* scriptSystem = script_;
    
    asIScriptContext* context = scriptSystem->GetScriptFileContext();
    if (!context)
    {
        LOGERROR("Maximum script execution nesting level exceeded");
        return false;
    }
    
    if (context->Prepare(method) < 0)
        return false;
    
    context->SetObject(object);
    SetParameters(context, method, parameters);
    
    scriptSystem->IncScriptNestingLevel();
    bool success = context->Execute() >= 0;
    if (unprepare)
        context->Unprepare();
    scriptSystem->DecScriptNestingLevel();
    
    return success;
}

asIScriptObject* ScriptFile::CreateObject(const String& className)
{
    PROFILE(CreateObject);
    
    if (!IsCompiled())
        return 0;
    
    asIScriptContext* context = script_->GetScriptFileContext();
    if (!context)
    {
        LOGERROR("Maximum script execution nesting level exceeded, can not create object");
        return 0;
    }
    
    asIScriptEngine* engine = script_->GetScriptEngine();
    asIObjectType *type = engine->GetObjectTypeById(scriptModule_->GetTypeIdByDecl(className.CString()));
    if (!type)
        return 0;
    
    // Ensure that the type implements the "ScriptObject" interface, so it can be returned to script properly
    bool found = false;
    Map<asIObjectType*, bool>::ConstIterator i = validClasses_.Find(type);
    if (i != validClasses_.End())
        found = i->second_;
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
        validClasses_[type] = found;
    }
    if (!found)
    {
        LOGERROR("Script class " + className + " does not implement the ScriptObject interface");
        return 0;
    }
    
    // Get the factory function id from the object type
    String factoryName = className + "@ " + className + "()";
    asIScriptFunction* factory = type->GetFactoryByDecl(factoryName.CString());
    if (!factory || context->Prepare(factory) < 0 || context->Execute() < 0)
        return 0;
    
    asIScriptObject* obj = *(static_cast<asIScriptObject**>(context->GetAddressOfReturnValue()));
    if (obj)
        obj->AddRef();
    
    return obj;
}

asIScriptFunction* ScriptFile::GetFunction(const String& declaration)
{
    if (!compiled_)
        return 0;
    
    HashMap<String, asIScriptFunction*>::ConstIterator i = functions_.Find(declaration);
    if (i != functions_.End())
        return i->second_;
    
    asIScriptFunction* function = scriptModule_->GetFunctionByDecl(declaration.CString());
    functions_[declaration] = function;
    return function;
}

asIScriptFunction* ScriptFile::GetMethod(asIScriptObject* object, const String& declaration)
{
    if (!compiled_ || !object)
        return 0;
    
    asIObjectType* type = object->GetObjectType();
    if (!type)
        return 0;
    Map<asIObjectType*, HashMap<String, asIScriptFunction*> >::ConstIterator i = methods_.Find(type);
    if (i != methods_.End())
    {
        HashMap<String, asIScriptFunction*>::ConstIterator j = i->second_.Find(declaration);
        if (j != i->second_.End())
            return j->second_;
    }
    
    asIScriptFunction* function = type->GetMethodByDecl(declaration.CString());
    methods_[type][declaration] = function;
    return function;
}

bool ScriptFile::AddScriptSection(asIScriptEngine* engine, Deserializer& source)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    unsigned dataSize = source.GetSize();
    SharedArrayPtr<char> buffer(new char[dataSize]);
    source.Read((void*)buffer.Get(), dataSize);
    
    // Pre-parse for includes
    // Adapted from Angelscript's scriptbuilder add-on
    Vector<String> includeFiles;
    unsigned pos = 0;
    while(pos < dataSize)
    {
        int len;
        asETokenClass t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
        if (t == asTC_COMMENT || t == asTC_WHITESPACE)
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
                String token(&buffer[pos], len);
                if (token == "include")
                {
                    pos += len;
                    t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
                    if (t == asTC_WHITESPACE)
                    {
                        pos += len;
                        t = engine->ParseToken(&buffer[pos], dataSize - pos, &len);
                    }
                    
                    if (t == asTC_VALUE && len > 2 && buffer[pos] == '"')
                    {
                        // Get the include file
                        String includeFile(&buffer[pos+1], len - 2);
                        pos += len;
                        
                        // If the file is not found as it is, add the path of current file
                        if (!cache->Exists(includeFile))
                            includeFile = GetPath(GetName()) + includeFile;
                        
                        String includeFileLower = includeFile.ToLower();
                        
                        // If not included yet, store it for later processing
                        if (!includeFiles_.Contains(includeFileLower))
                        {
                            includeFiles_.Insert(includeFileLower);
                            includeFiles.Push(includeFile);
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
            while (pos < dataSize && buffer[pos] != ';' && buffer[pos] != '{')
            {
                engine->ParseToken(&buffer[pos], 0, &len);
                pos += len;
            }
            // Skip entire statement block
            if (pos < dataSize && buffer[pos] == '{')
            {
                ++pos;
                // Find the end of the statement block
                int level = 1;
                while (level > 0 && pos < dataSize)
                {
                    asETokenClass t = engine->ParseToken(&buffer[pos], 0, &len);
                    if (t == asTC_KEYWORD)
                    {
                        if (buffer[pos] == '{')
                            ++level;
                        else if(buffer[pos] == '}')
                            --level;
                    }
                    pos += len;
                }
            }
            else
                ++pos;
        }
    }
    
    // Process includes first
    for (unsigned i = 0; i < includeFiles.Size(); ++i)
    {
        SharedPtr<File> file = cache->GetFile(includeFiles[i]);
        if (file)
        {
            if (!AddScriptSection(engine, *file))
                return false;
        }
        else
            return false;
    }
    
    // Then add this section
    if (scriptModule_->AddScriptSection(source.GetName().CString(), (const char*)buffer.Get(), dataSize) < 0)
    {
        LOGERROR("Failed to add script section " + source.GetName());
        return false;
    }
    
    SetMemoryUse(GetMemoryUse() + dataSize);
    return true;
}

void ScriptFile::SetParameters(asIScriptContext* context, asIScriptFunction* function, const VariantVector& parameters)
{
    unsigned paramCount = function->GetParamCount();
    for (unsigned i = 0; i < parameters.Size() && i < paramCount; ++i)
    {
        int paramType = function->GetParamTypeId(i);
        
        switch (paramType)
        {
        case asTYPEID_BOOL:
            context->SetArgByte(i, (unsigned char)parameters[i].GetBool());
            break;
            
        case asTYPEID_INT8:
        case asTYPEID_UINT8:
            context->SetArgByte(i, parameters[i].GetInt());
            break;
            
        case asTYPEID_INT16:
        case asTYPEID_UINT16:
            context->SetArgWord(i, parameters[i].GetInt());
            break;
            
        case asTYPEID_INT32:
        case asTYPEID_UINT32:
            context->SetArgDWord(i, parameters[i].GetInt());
            break;
            
        case asTYPEID_FLOAT:
            context->SetArgFloat(i, parameters[i].GetFloat());
            break;
            
        default:
            if (paramType & asTYPEID_APPOBJECT)
            {
                switch (parameters[i].GetType())
                {
                case VAR_VECTOR2:
                    context->SetArgObject(i, (void *)&parameters[i].GetVector2());
                    break;
                    
                case VAR_VECTOR3:
                    context->SetArgObject(i, (void *)&parameters[i].GetVector3());
                    break;
                    
                case VAR_VECTOR4:
                    context->SetArgObject(i, (void *)&parameters[i].GetVector4());
                    break;
                    
                case VAR_QUATERNION:
                    context->SetArgObject(i, (void *)&parameters[i].GetQuaternion());
                    break;
                    
                case VAR_STRING:
                    context->SetArgObject(i, (void *)&parameters[i].GetString());
                    break;
                    
                case VAR_PTR:
                    context->SetArgObject(i, (void *)parameters[i].GetPtr());
                    break;
                    
                default:
                    break;
                }
            }
            break;
        }
    }
}

void ScriptFile::ReleaseModule()
{
    if (scriptModule_)
    {
        script_->ClearObjectTypeCache();
        
        // Clear search caches and event handlers
        includeFiles_.Clear();
        validClasses_.Clear();
        functions_.Clear();
        methods_.Clear();
        UnsubscribeFromAllEventsWithUserData();
        
        // Remove the module
        script_->GetModuleMap().Erase(scriptModule_);
        asIScriptEngine* engine = script_->GetScriptEngine();
        engine->DiscardModule(GetName().CString());
        scriptModule_ = 0;
        compiled_ = false;
        SetMemoryUse(0);
    }
}

void ScriptFile::HandleScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if (!compiled_)
        return;
    
    asIScriptFunction* function = static_cast<asIScriptFunction*>(context_->GetEventHandler()->GetUserData());
    
    VariantVector parameters;
    if (function->GetParamCount() > 0)
    {
        parameters.Push(Variant((void*)&eventType));
        parameters.Push(Variant((void*)&eventData));
    }
    
    Execute(function, parameters);
}

ScriptFile* GetScriptContextFile()
{
    asIScriptContext* context = asGetActiveContext();
    asIScriptFunction* function = context->GetFunction();
    asIScriptModule* module = function->GetEngine()->GetModule(function->GetModuleName());
    Map<asIScriptModule*, ScriptFile*>& moduleMap = static_cast<Script*>(context->GetEngine()->GetUserData())->GetModuleMap();
    Map<asIScriptModule*, ScriptFile*>::ConstIterator i = moduleMap.Find(module);
    if (i != moduleMap.End())
        return i->second_;
    else
        return 0;
}
