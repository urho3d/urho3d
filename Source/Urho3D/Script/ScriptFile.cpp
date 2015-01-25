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

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../Script/Script.h"
#include "../Script/ScriptFile.h"
#include "../Script/ScriptInstance.h"

#include <AngelScript/angelscript.h>
#include <cstring>

#include "../DebugNew.h"

namespace Urho3D
{

/// Helper class for saving AngelScript bytecode.
class ByteCodeSerializer : public asIBinaryStream
{
public:
    /// Construct.
    ByteCodeSerializer(Serializer& dest) :
        dest_(dest)
    {
    }
    
    /// Read from stream (no-op).
    virtual void Read(void* ptr, asUINT size)
    {
        // No-op, can not read from a Serializer
    }
    
    /// Write to stream.
    virtual void Write(const void* ptr, asUINT size)
    {
        dest_.Write(ptr, size);
    }
    
private:
    /// Destination stream.
    Serializer& dest_;
};

/// Helper class for loading AngelScript bytecode.
class ByteCodeDeserializer : public asIBinaryStream
{
public:
    /// Construct.
    ByteCodeDeserializer(MemoryBuffer& source) :
        source_(source)
    {
    }
    
    /// Read from stream.
    virtual void Read(void* ptr, asUINT size)
    {
        source_.Read(ptr, size);
    }
    
    /// Write to stream (no-op).
    virtual void Write(const void* ptr, asUINT size)
    {
    }
    
private:
    /// Source stream.
    MemoryBuffer& source_;
};

ScriptFile::ScriptFile(Context* context) :
    Resource(context),
    script_(GetSubsystem<Script>()),
    scriptModule_(0),
    compiled_(false),
    subscribed_(false)
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

bool ScriptFile::BeginLoad(Deserializer& source)
{
    ReleaseModule();
    loadByteCode_.Reset();
    
    asIScriptEngine* engine = script_->GetScriptEngine();
    
    {
        MutexLock lock(script_->GetModuleMutex());
    
        // Create the module. Discard previous module if there was one
        scriptModule_ = engine->GetModule(GetName().CString(), asGM_ALWAYS_CREATE);
        if (!scriptModule_)
        {
            LOGERROR("Failed to create script module " + GetName());
            return false;
        }
    }
    
    // Check if this file is precompiled bytecode
    if (source.ReadFileID() == "ASBC")
    {
        // Perform actual parsing in EndLoad(); read data now
        loadByteCodeSize_ = source.GetSize() - source.GetPosition();
        loadByteCode_ = new unsigned char[loadByteCodeSize_];
        source.Read(loadByteCode_.Get(), loadByteCodeSize_);
        return true;
    }
    else
        source.Seek(0);
    
    // Not bytecode: add the initial section and check for includes.
    // Perform actual building during EndLoad(), as AngelScript can not multithread module compilation,
    // and static initializers may access arbitrary engine functionality which may not be thread-safe
    return AddScriptSection(engine, source);
}

bool ScriptFile::EndLoad()
{
    bool success = false;

    // Load from bytecode if available, else compile
    if (loadByteCode_)
    {
        MemoryBuffer buffer(loadByteCode_.Get(), loadByteCodeSize_);
        ByteCodeDeserializer deserializer = ByteCodeDeserializer(buffer);

        if (scriptModule_->LoadByteCode(&deserializer) >= 0)
        {
            LOGINFO("Loaded script module " + GetName() + " from bytecode");
            success = true;
        }
    }
    else
    {
        int result = scriptModule_->Build();
        if (result >= 0)
        {
            LOGINFO("Compiled script module " + GetName());
            success = true;
        }
        else
            LOGERROR("Failed to compile script module " + GetName());
    }
    
    if (success)
    {
        compiled_ = true;
        // Map script module to script resource with userdata
        scriptModule_->SetUserData(this);
    }

    loadByteCode_.Reset();
    return success;
}

void ScriptFile::AddEventHandler(StringHash eventType, const String& handlerName)
{
    if (!compiled_)
        return;

    AddEventHandlerInternal(0, eventType, handlerName);
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

    AddEventHandlerInternal(sender, eventType, handlerName);
}

void ScriptFile::RemoveEventHandler(StringHash eventType)
{
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    if (i != eventInvokers_.End())
    {
        i->second_->UnsubscribeFromEvent(eventType);
        // If no longer have any subscribed events, remove the event invoker object
        if (!i->second_->HasEventHandlers())
            eventInvokers_.Erase(i);
    }
}

void ScriptFile::RemoveEventHandler(Object* sender, StringHash eventType)
{
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    if (i != eventInvokers_.End())
    {
        i->second_->UnsubscribeFromEvent(sender, eventType);
        if (!i->second_->HasEventHandlers())
            eventInvokers_.Erase(i);
    }
}

void ScriptFile::RemoveEventHandlers(Object* sender)
{
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    if (i != eventInvokers_.End())
    {
        i->second_->UnsubscribeFromEvents(sender);
        if (!i->second_->HasEventHandlers())
            eventInvokers_.Erase(i);
    }
}

void ScriptFile::RemoveEventHandlers()
{
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    if (i != eventInvokers_.End())
    {
        i->second_->UnsubscribeFromAllEvents();
        if (!i->second_->HasEventHandlers())
            eventInvokers_.Erase(i);
    }
}

void ScriptFile::RemoveEventHandlersExcept(const PODVector<StringHash>& exceptions)
{
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    if (i != eventInvokers_.End())
    {
        i->second_->UnsubscribeFromAllEventsExcept(exceptions, true);
        if (!i->second_->HasEventHandlers())
            eventInvokers_.Erase(i);
    }
}

bool ScriptFile::Execute(const String& declaration, const VariantVector& parameters, bool unprepare)
{
    asIScriptFunction* function = GetFunction(declaration);
    if (!function)
    {
        LOGERROR("Function " + declaration + " not found in " + GetName());
        return false;
    }
    
    return Execute(function, parameters, unprepare);
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

void ScriptFile::DelayedExecute(float delay, bool repeat, const String& declaration, const VariantVector& parameters)
{
    DelayedCall call;
    call.period_ = call.delay_ = Max(delay, 0.0f);
    call.repeat_ = repeat;
    call.declaration_ = declaration;
    call.parameters_ = parameters;
    delayedCalls_.Push(call);
    
    // Make sure we are registered to the application update event, because delayed calls are executed there
    if (!subscribed_)
    {
        SubscribeToEvent(E_UPDATE, HANDLER(ScriptFile, HandleUpdate));
        subscribed_ = true;
    }
}

void ScriptFile::ClearDelayedExecute(const String& declaration)
{
    if (declaration.Empty())
        delayedCalls_.Clear();
    else
    {
        for (Vector<DelayedCall>::Iterator i = delayedCalls_.Begin(); i != delayedCalls_.End();)
        {
            if (declaration == i->declaration_)
                i = delayedCalls_.Erase(i);
            else
                ++i;
        }
    }
}
asIScriptObject* ScriptFile::CreateObject(const String& className, bool useInterface)
{
    PROFILE(CreateObject);
    
    if (!compiled_)
        return 0;
    
    asIScriptContext* context = script_->GetScriptFileContext();
    asIObjectType* type = 0;
    if (useInterface)
    {
        asIObjectType* interfaceType = scriptModule_->GetObjectTypeByDecl(className.CString());

        if (!interfaceType)
            return 0;

        for (unsigned i = 0; i < scriptModule_->GetObjectTypeCount(); ++i)
        {
            asIObjectType* t = scriptModule_->GetObjectTypeByIndex(i);
            if (t->Implements(interfaceType))
            {
                type = t;
                break;
            }
        }
    }
    else
    {
       type = scriptModule_->GetObjectTypeByDecl(className.CString());
    }

    if (!type)
        return 0;
    
    // Ensure that the type implements the "ScriptObject" interface, so it can be returned to script properly
    bool found = false;
    HashMap<asIObjectType*, bool>::ConstIterator i = validClasses_.Find(type);
    if (i != validClasses_.End())
        found = i->second_;
    else
    {
        asIObjectType* scriptObjectType = scriptModule_->GetObjectTypeByDecl("ScriptObject");

        found = type->Implements(scriptObjectType);
        validClasses_[type] = found;
    }
    
    if (!found)
    {
        LOGERRORF("Script class %s does not implement the ScriptObject interface", type->GetName());
        return 0;
    }
    
    // Get the factory function id from the object type
    String factoryName = String(type->GetName()) + "@ " + type->GetName() + "()";
    asIScriptFunction* factory = type->GetFactoryByDecl(factoryName.CString());
    if (!factory || context->Prepare(factory) < 0 || context->Execute() < 0)
        return 0;
    
    asIScriptObject* obj = *(static_cast<asIScriptObject**>(context->GetAddressOfReturnValue()));
    if (obj)
        obj->AddRef();
    
    return obj;
}

bool ScriptFile::SaveByteCode(Serializer& dest)
{
    if (compiled_)
    {
        dest.WriteFileID("ASBC");
        ByteCodeSerializer serializer = ByteCodeSerializer(dest);
        return scriptModule_->SaveByteCode(&serializer, true) >= 0;
    }
    else
        return false;
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
    HashMap<asIObjectType*, HashMap<String, asIScriptFunction*> >::ConstIterator i = methods_.Find(type);
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

void ScriptFile::CleanupEventInvoker(asIScriptObject* object)
{
    eventInvokers_.Erase(object);
}

void ScriptFile::AddEventHandlerInternal(Object* sender, StringHash eventType, const String& handlerName)
{
    String declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* function = 0;
    asIScriptObject* receiver = static_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());

    if (receiver)
        function = GetMethod(receiver, declaration);
    else
        function = GetFunction(declaration);

    if (!function)
    {
        declaration = "void " + handlerName + "()";

        if (receiver)
            function = GetMethod(receiver, declaration);
        else
            function = GetFunction(declaration);

        if (!function)
        {
            LOGERROR("Event handler function " + handlerName + " not found in " + GetName());
            return;
        }
    }

    HashMap<asIScriptObject*, SharedPtr<ScriptEventInvoker> >::Iterator i = eventInvokers_.Find(receiver);
    // Remove previous handler in case an object pointer gets reused
    if (i != eventInvokers_.End() && !i->second_->IsObjectAlive())
    {
        eventInvokers_.Erase(i);
        i = eventInvokers_.End();
    }
    if (i == eventInvokers_.End())
        i = eventInvokers_.Insert(MakePair(receiver, SharedPtr<ScriptEventInvoker>(new ScriptEventInvoker(this, receiver))));

    if (!sender)
    {
        i->second_->SubscribeToEvent(eventType, new EventHandlerImpl<ScriptEventInvoker>
            (i->second_, &ScriptEventInvoker::HandleScriptEvent, (void*)function));
    }
    else
    {
        i->second_->SubscribeToEvent(sender, eventType, new EventHandlerImpl<ScriptEventInvoker>
            (i->second_, &ScriptEventInvoker::HandleScriptEvent, (void*)function));
    }
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
                        
                        // If the file is not found as it is, add the path of current file but only if it is found there
                        if (!cache->Exists(includeFile))
                        {
                            String prefixedIncludeFile = GetPath(GetName()) + includeFile;
                            if (cache->Exists(prefixedIncludeFile))
                                includeFile = prefixedIncludeFile;
                        }
                        
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
        cache->StoreResourceDependency(this, includeFiles[i]);
        SharedPtr<File> file = cache->GetFile(includeFiles[i]);
        if (file)
        {
            if (!AddScriptSection(engine, *file))
                return false;
        }
        else
        {
            LOGERROR("Could not process all the include directives in " + GetName() + ": missing " + includeFiles[i]);
            return false;
        }
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
        int paramTypeId;
        function->GetParam(i, &paramTypeId);
        
        switch (paramTypeId)
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
            if (paramTypeId & asTYPEID_APPOBJECT)
            {
                switch (parameters[i].GetType())
                {
                case VAR_VECTOR2:
                    context->SetArgObject(i, (void*)&parameters[i].GetVector2());
                    break;
                    
                case VAR_VECTOR3:
                    context->SetArgObject(i, (void*)&parameters[i].GetVector3());
                    break;
                    
                case VAR_VECTOR4:
                    context->SetArgObject(i, (void*)&parameters[i].GetVector4());
                    break;
                    
                case VAR_QUATERNION:
                    context->SetArgObject(i, (void*)&parameters[i].GetQuaternion());
                    break;
                    
                case VAR_STRING:
                    context->SetArgObject(i, (void*)&parameters[i].GetString());
                    break;
                    
                case VAR_VOIDPTR:
                    context->SetArgObject(i, parameters[i].GetVoidPtr());
                    break;
                    
                case VAR_PTR:
                    context->SetArgObject(i, (void*)parameters[i].GetPtr());
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
        // Clear search caches and event handlers
        includeFiles_.Clear();
        validClasses_.Clear();
        functions_.Clear();
        methods_.Clear();
        delayedCalls_.Clear();
        eventInvokers_.Clear();
        
        asIScriptEngine* engine = script_->GetScriptEngine();
        scriptModule_->SetUserData(0);
        
        // Remove the module
        {
            MutexLock lock(script_->GetModuleMutex());
            
            script_->ClearObjectTypeCache();
            engine->DiscardModule(GetName().CString());
        }
        
        scriptModule_ = 0;
        compiled_ = false;
        SetMemoryUse(0);
        
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        cache->ResetDependencies(this);
    }
}

void ScriptFile::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!compiled_)
        return;
    
    using namespace Update;
    
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Execute delayed calls
    for (unsigned i = 0; i < delayedCalls_.Size();)
    {
        DelayedCall& call = delayedCalls_[i];
        bool remove = false;
        
        call.delay_ -= timeStep;
        if (call.delay_ <= 0.0f)
        {
            if (!call.repeat_)
                remove = true;
            else
                call.delay_ += call.period_;
            
            Execute(call.declaration_, call.parameters_);
        }
        
        if (remove)
            delayedCalls_.Erase(i);
        else
            ++i;
    }
}

ScriptEventInvoker::ScriptEventInvoker(ScriptFile* file, asIScriptObject* object) :
    Object(file->GetContext()),
    file_(file),
    sharedBool_(0),
    object_(object)
{
    if (object_)
    {
        sharedBool_ = object_->GetEngine()->GetWeakRefFlagOfScriptObject(object_, object_->GetObjectType());
        if (sharedBool_)
            sharedBool_->AddRef();
    }
}

ScriptEventInvoker::~ScriptEventInvoker()
{
    if (sharedBool_)
        sharedBool_->Release();

    sharedBool_ = 0;
    object_ = 0;
}

bool ScriptEventInvoker::IsObjectAlive() const
{
    if (sharedBool_)
    {
        // Return inverse as Get returns true when an asIScriptObject is dead.
        return !sharedBool_->Get();
    }

    return true;
}

void ScriptEventInvoker::HandleScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if (!file_->IsCompiled())
        return;

    asIScriptFunction* method = static_cast<asIScriptFunction*>(GetEventHandler()->GetUserData());

    if (object_ && !IsObjectAlive())
    {
        file_->CleanupEventInvoker(object_);
        return;
    }

    VariantVector parameters;
    if (method->GetParamCount() > 0)
    {
        parameters.Push(Variant((void*)&eventType));
        parameters.Push(Variant((void*)&eventData));
    }

    if (object_)
        file_->Execute(object_, method, parameters);
    else
        file_->Execute(method, parameters);
}

ScriptFile* GetScriptContextFile()
{
    asIScriptContext* context = asGetActiveContext();
    asIScriptFunction* function = context ? context->GetFunction() : 0;
    asIScriptModule* module = function ? function->GetEngine()->GetModule(function->GetModuleName()) : 0;
    if (module)
        return static_cast<ScriptFile*>(module->GetUserData());
    else
        return 0;
}

}
