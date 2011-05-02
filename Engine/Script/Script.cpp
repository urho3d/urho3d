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
#include "Addons.h"
#include "Context.h"
#include "Log.h"
#include "Profiler.h"
#include "Scene.h"
#include "Script.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"
#include "StringUtils.h"

#include <angelscript.h>

#include "DebugNew.h"

/// Script object property info for script API dump
struct PropertyInfo
{
    PropertyInfo() :
        read_(false),
        write_(false),
        indexed_(false)
    {
    }
    
    std::string name_;
    std::string type_;
    bool read_;
    bool write_;
    bool indexed_;
};

void ExtractPropertyInfo(const std::string& functionName, const std::string& declaration, std::vector<PropertyInfo>& propertyInfos)
{
    std::string propertyName = functionName.substr(4);
    PropertyInfo* info = 0;
    for (unsigned k = 0; k < propertyInfos.size(); ++k)
    {
        if (propertyInfos[k].name_ == propertyName)
            info = &propertyInfos[k];
    }
    if (!info)
    {
        propertyInfos.resize(propertyInfos.size() + 1);
        info = &propertyInfos[propertyInfos.size() - 1];
        info->name_ = propertyName;
    }
    if (functionName.find("get_") != std::string::npos)
    {
        info->read_ = true;
        // Extract type from the return value
        std::vector<std::string> parts = Split(declaration, ' ');
        if (parts.size())
        {
            if (parts[0] != "const")
                info->type_ = parts[0];
            else if (parts.size() > 1)
                info->type_ = parts[1];
        }
        // If get method has parameters, it is indexed
        if (declaration.find("()") == std::string::npos)
        {
            info->indexed_ = true;
            info->type_ += "[]";
        }
    }
    if (functionName.find("set_") != std::string::npos)
        info->write_ = true;
}

OBJECTTYPESTATIC(Script);

Script::Script(Context* context) :
    Object(context),
    scriptEngine_(0),
    immediateContext_(0),
    scriptNestingLevel_(0)
{
    scriptEngine_ = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    if (!scriptEngine_)
    {
        LOGERROR("Could not create AngelScript engine");
        return;
    }
    
    scriptEngine_->SetUserData(this);
    scriptEngine_->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, true);
    scriptEngine_->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, true);
    scriptEngine_->SetEngineProperty(asEP_ALLOW_IMPLICIT_HANDLE_TYPES, true);
    scriptEngine_->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, true);
    scriptEngine_->SetMessageCallback(asMETHOD(Script, MessageCallback), this, asCALL_THISCALL);
    
    // Create the context for immediate execution
    immediateContext_ = scriptEngine_->CreateContext();
    immediateContext_->SetExceptionCallback(asMETHOD(Script, ExceptionCallback), this, asCALL_THISCALL);
    
    // Create the function/method contexts
    for (unsigned i = 0 ; i < MAX_SCRIPT_NESTING_LEVEL; ++i)
    {
        scriptFileContexts_.push_back(scriptEngine_->CreateContext());
        scriptFileContexts_[i]->SetExceptionCallback(asMETHOD(Script, ExceptionCallback), this, asCALL_THISCALL);
    }
    
    // Register the Array & String types
    RegisterArray(scriptEngine_);
    RegisterString(scriptEngine_);
}

Script::~Script()
{
    if (immediateContext_)
    {
        immediateContext_->Release();
        immediateContext_ = 0;
    }
    for (unsigned i = 0 ; i < MAX_SCRIPT_NESTING_LEVEL; ++i)
    {
        if (scriptFileContexts_[i])
            scriptFileContexts_[i]->Release();
    }
    scriptFileContexts_.clear();
    
    if (scriptEngine_)
    {
        scriptEngine_->Release();
        scriptEngine_ = 0;
    }
}

bool Script::Execute(const std::string& line)
{
    // Note: compiling code each time is slow. Not to be used for performance-critical or repeating activity
    PROFILE(ExecuteImmediate);
    
    std::string wrappedLine = "void f(){\n" + line + ";\n}";
    
    // If no immediate mode script file set, create a dummy module for compiling the line
    asIScriptModule* module = 0;
    if (defaultScriptFile_)
        module = defaultScriptFile_->GetScriptModule();
    if (!module)
        module = scriptEngine_->GetModule("ExecuteImmediate", asGM_CREATE_IF_NOT_EXISTS);
    if (!module)
        return false;
    
    asIScriptFunction *function = 0;
    if (module->CompileFunction("", wrappedLine.c_str(), -1, 0, &function) < 0)
        return false;
    
    if (immediateContext_->Prepare(function->GetId()) < 0)
    {
        function->Release();
        return false;
    }
    
    bool success = false;
    
    success = immediateContext_->Execute() >= 0;
    immediateContext_->Unprepare();
    function->Release();
    
    return success;
}

void Script::GarbageCollect(bool fullCycle)
{
    PROFILE(GarbageCollect);
    
    if (fullCycle)
        scriptEngine_->GarbageCollect(asGC_FULL_CYCLE);
    else
        scriptEngine_->GarbageCollect(asGC_ONE_STEP);
}

void Script::SetDefaultScriptFile(ScriptFile* file)
{
    defaultScriptFile_ = file;
}

void Script::SetDefaultScene(Scene* scene)
{
    defaultScene_ = scene;
}

void Script::SetLogMode(ScriptLogMode mode)
{
    logMode_ = mode;
}

void Script::ClearLogMessages()
{
    logMessages_.clear();
}

void Script::DumpAPI()
{
    LOGRAW("Urho3D script API:\n");
    
    std::vector<PropertyInfo> globalPropertyInfos;
    std::vector<std::string> globalFunctions;
    
    unsigned functions = scriptEngine_->GetGlobalFunctionCount();
    for (unsigned i = 0; i < functions; ++i)
    {
        unsigned id = scriptEngine_->GetGlobalFunctionIdByIndex(i);
        asIScriptFunction* function = scriptEngine_->GetFunctionDescriptorById(id);
        std::string functionName(function->GetName());
        std::string declaration(function->GetDeclaration());
        
        if ((functionName.find("set_") != std::string::npos) || (functionName.find("get_") != std::string::npos))
            ExtractPropertyInfo(functionName, declaration, globalPropertyInfos);
        else
            globalFunctions.push_back(declaration);
    }
    
    LOGRAW("\nGlobal functions:\n");
    
    for (unsigned i = 0; i < globalFunctions.size(); ++i)
        OutputAPIRow(globalFunctions[i]);
    
    LOGRAW("\nGlobal properties:\n");
    
    for (unsigned i = 0; i < globalPropertyInfos.size(); ++i)
    {
        // For now, skip write-only properties
        if (!globalPropertyInfos[i].read_)
            continue;
        
        OutputAPIRow(globalPropertyInfos[i].type_ + " " + globalPropertyInfos[i].name_, true);
    }
    
    LOGRAW("\nGlobal constants:\n");
    
    unsigned properties = scriptEngine_->GetGlobalPropertyCount();
    for (unsigned i = 0; i < properties; ++i)
    {
        const char* propertyName;
        const char* propertyDeclaration;
        int typeId;
        scriptEngine_->GetGlobalPropertyByIndex(i, &propertyName, &typeId);
        propertyDeclaration = scriptEngine_->GetTypeDeclaration(typeId);
        
        std::string type(propertyDeclaration);
        OutputAPIRow(type + " " + std::string(propertyName), true);
    }
    
    LOGRAW("\nClasses:\n");
    
    unsigned types = scriptEngine_->GetObjectTypeCount();
    for (unsigned i = 0; i < types; ++i)
    {
        asIObjectType* type = scriptEngine_->GetObjectTypeByIndex(i);
        if (type)
        {
            std::string typeName(type->GetName());
            std::vector<std::string> methodDeclarations;
            std::vector<PropertyInfo> propertyInfos;
            
            LOGRAW("\n" + typeName + "\n");
            
            unsigned methods = type->GetMethodCount();
            for (unsigned j = 0; j < methods; ++j)
            {
                asIScriptFunction* method = type->GetMethodDescriptorByIndex(j);
                std::string methodName(method->GetName());
                std::string declaration(method->GetDeclaration());
                if ((methodName.find("get_") == std::string::npos) && (methodName.find("set_") == std::string::npos))
                {
                    // Sanitate the method name. For now, skip the operators
                    if (declaration.find("::op") == std::string::npos)
                    {
                        std::string prefix(typeName + "::");
                        ReplaceInPlace(declaration, prefix, "");
                        methodDeclarations.push_back(declaration);
                    }
                }
                else
                    ExtractPropertyInfo(methodName, declaration, propertyInfos);
            }
            
            // Assume that the same property is never both an accessor property, and a direct one
            unsigned properties = type->GetPropertyCount();
            for (unsigned j = 0; j < properties; ++j)
            {
                const char* propertyName;
                const char* propertyDeclaration;
                int typeId;
                
                type->GetProperty(j, &propertyName, &typeId);
                propertyDeclaration = scriptEngine_->GetTypeDeclaration(typeId);
                
                PropertyInfo newInfo;
                newInfo.name_ = std::string(propertyName);
                newInfo.type_ = std::string(propertyDeclaration);
                newInfo.read_ = newInfo.write_ = true;
                propertyInfos.push_back(newInfo);
            }
            
            if (!methodDeclarations.empty())
            {
                LOGRAW("\nMethods:\n");
                for (unsigned j = 0; j < methodDeclarations.size(); ++j)
                    OutputAPIRow(methodDeclarations[j]);
            }
            
            if (!propertyInfos.empty())
            {
                LOGRAW("\nProperties:\n");
                for (unsigned j = 0; j < propertyInfos.size(); ++j)
                {
                    // For now, skip write-only properties
                    if (!propertyInfos[j].read_)
                        continue;
                    
                    std::string readOnly;
                    if (!propertyInfos[j].write_)
                        readOnly = " (readonly)";
                    
                    OutputAPIRow(propertyInfos[j].type_ + " " + propertyInfos[j].name_ + readOnly);
                }
            }
            
            LOGRAW("\n");
        }
    }
}

void Script::MessageCallback(const asSMessageInfo* msg)
{
    std::string message = std::string(msg->section) + " (" + ToString(msg->row) + "," + ToString(msg->col) + ") " +
        std::string(msg->message);
    
    if (logMode_ == LOGMODE_IMMEDIATE)
    {
        switch (msg->type)
        {
        case asMSGTYPE_ERROR:
            LOGERROR(message);
            break;
            
        case asMSGTYPE_WARNING:
            LOGWARNING(message);
            break;
            
        default:
            LOGINFO(message);
            break;
        }
    }
    else
    {
        // Ignore info messages in retained mode
        if ((msg->type == asMSGTYPE_ERROR) || (msg->type == asMSGTYPE_WARNING))
            logMessages_ += message + "\n";
    }
}

void Script::ExceptionCallback(asIScriptContext* context)
{
    int funcId = context->GetExceptionFunction();
    const asIScriptFunction *function = scriptEngine_->GetFunctionDescriptorById(funcId);
    std::string message = "Exception '" + std::string(context->GetExceptionString()) + "' in '" +
        std::string(function->GetDeclaration()) + "'";
    
    asSMessageInfo msg;
    msg.row = context->GetExceptionLineNumber(&msg.col, &msg.section);
    msg.type = asMSGTYPE_ERROR;
    msg.message = message.c_str();
    
    MessageCallback(&msg);
}

asIScriptContext* Script::GetScriptFileContext() const
{
    return scriptNestingLevel_ < scriptFileContexts_.size() ? scriptFileContexts_[scriptNestingLevel_] : 0;
}

ScriptFile* Script::GetDefaultScriptFile() const
{
    return defaultScriptFile_;
}

Scene* Script::GetDefaultScene() const
{
    return defaultScene_;
}

asIObjectType* Script::GetObjectType(const char* declaration)
{
    std::map<const char*, asIObjectType*>::const_iterator i = objectTypes_.find(declaration);
    if (i != objectTypes_.end())
        return i->second;
    
    asIObjectType* type = scriptEngine_->GetObjectTypeById(scriptEngine_->GetTypeIdByDecl(declaration));
    objectTypes_[declaration] = type;
    return type;
}

void Script::OutputAPIRow(const std::string& row, bool removeReference)
{
    std::string out = row;
    ReplaceInPlace(out, "double", "float");
    ReplaceInPlace(out, "&in", "&");
    ReplaceInPlace(out, "&out", "&");
    if (removeReference)
        ReplaceInPlace(out, "&", "");
    
    LOGRAW(out + "\n");
}

void RegisterScriptLibrary(Context* context)
{
    ScriptFile::RegisterObject(context);
    ScriptInstance::RegisterObject(context);
}
