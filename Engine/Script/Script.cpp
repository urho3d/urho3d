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
#include "Addons.h"
#include "Context.h"
#include "Log.h"
#include "Profiler.h"
#include "Scene.h"
#include "Script.h"
#include "ScriptFile.h"
#include "ScriptInstance.h"

#include <angelscript.h>

#include "DebugNew.h"

namespace Urho3D
{

/// %Object property info for scripting API dump.
struct PropertyInfo
{
    /// Construct.
    PropertyInfo() :
        read_(false),
        write_(false),
        indexed_(false)
    {
    }
    
    /// Property name.
    String name_;
    /// Property data type.
    String type_;
    /// Reading supported flag.
    bool read_;
    /// Writing supported flag.
    bool write_;
    /// Indexed flag.
    bool indexed_;
};

void ExtractPropertyInfo(const String& functionName, const String& declaration, Vector<PropertyInfo>& propertyInfos)
{
    String propertyName = functionName.Substring(4);
    PropertyInfo* info = 0;
    for (unsigned k = 0; k < propertyInfos.Size(); ++k)
    {
        if (propertyInfos[k].name_ == propertyName)
            info = &propertyInfos[k];
    }
    if (!info)
    {
        propertyInfos.Resize(propertyInfos.Size() + 1);
        info = &propertyInfos.Back();
        info->name_ = propertyName;
    }
    if (functionName.Find("get_") != String::NPOS)
    {
        info->read_ = true;
        // Extract type from the return value
        Vector<String> parts = declaration.Split(' ');
        if (parts.Size())
        {
            if (parts[0] != "const")
                info->type_ = parts[0];
            else if (parts.Size() > 1)
                info->type_ = parts[1];
        }
        // If get method has parameters, it is indexed
        if (declaration.Find("()") == String::NPOS)
        {
            info->indexed_ = true;
            info->type_ += "[]";
        }
        
        // Sanitate the reference operator away
        info->type_.Replace("&", "");
    }
    if (functionName.Find("set_") != String::NPOS)
    {
        info->write_ = true;
        if (info->type_.Empty())
        {
            // Extract type from parameters
            unsigned begin = declaration.Find(',');
            if (begin == String::NPOS)
                begin = declaration.Find('(');
            else
                info->indexed_ = true;
            
            if (begin != String::NPOS)
            {
                ++begin;
                unsigned end = declaration.Find(')');
                if (end != String::NPOS)
                {
                    info->type_ = declaration.Substring(begin, end - begin);
                    // Sanitate const & reference operator away
                    info->type_.Replace("const ", "");
                    info->type_.Replace("&in", "");
                    info->type_.Replace("&", "");
                }
            }
        }
    }
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
    
    for (unsigned i = 0 ; i < scriptFileContexts_.Size(); ++i)
        scriptFileContexts_[i]->Release();
    scriptFileContexts_.Clear();
    
    if (scriptEngine_)
    {
        scriptEngine_->Release();
        scriptEngine_ = 0;
    }
}

bool Script::Execute(const String& line)
{
    // Note: compiling code each time is slow. Not to be used for performance-critical or repeating activity
    PROFILE(ExecuteImmediate);
    
    ClearObjectTypeCache();
    
    String wrappedLine = "void f(){\n" + line + ";\n}";
    
    // If no immediate mode script file set, create a dummy module for compiling the line
    asIScriptModule* module = 0;
    if (defaultScriptFile_)
        module = defaultScriptFile_->GetScriptModule();
    if (!module)
        module = scriptEngine_->GetModule("ExecuteImmediate", asGM_CREATE_IF_NOT_EXISTS);
    if (!module)
        return false;
    
    asIScriptFunction *function = 0;
    if (module->CompileFunction("", wrappedLine.CString(), -1, 0, &function) < 0)
        return false;
    
    if (immediateContext_->Prepare(function) < 0)
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
    logMessages_.Clear();
}

void Script::DumpAPI()
{
    LOGRAW("namespace Urho3D\n{\n\n/**\n\\page ScriptAPI Scripting API\n\n");
    
    Vector<PropertyInfo> globalPropertyInfos;
    Vector<String> globalFunctions;
    
    unsigned functions = scriptEngine_->GetGlobalFunctionCount();
    for (unsigned i = 0; i < functions; ++i)
    {
        asIScriptFunction* function = scriptEngine_->GetGlobalFunctionByIndex(i);
        String functionName(function->GetName());
        String declaration(function->GetDeclaration());
        
        if (functionName.Find("set_") != String::NPOS || functionName.Find("get_") != String::NPOS)
            ExtractPropertyInfo(functionName, declaration, globalPropertyInfos);
        else
            globalFunctions.Push(declaration);
    }
    
    LOGRAW("\\section ScriptAPI_GlobalFunctions Global functions\n");
    
    for (unsigned i = 0; i < globalFunctions.Size(); ++i)
        OutputAPIRow(globalFunctions[i]);
    
    LOGRAW("\\section ScriptAPI_GlobalProperties Global properties\n");
    
    for (unsigned i = 0; i < globalPropertyInfos.Size(); ++i)
        OutputAPIRow(globalPropertyInfos[i].type_ + " " + globalPropertyInfos[i].name_, true);
    
    LOGRAW("\\section ScriptAPI_GlobalConstants Global constants\n");
    
    unsigned properties = scriptEngine_->GetGlobalPropertyCount();
    for (unsigned i = 0; i < properties; ++i)
    {
        const char* propertyName;
        const char* propertyDeclaration;
        int typeId;
        scriptEngine_->GetGlobalPropertyByIndex(i, &propertyName, 0, &typeId);
        propertyDeclaration = scriptEngine_->GetTypeDeclaration(typeId);
        
        String type(propertyDeclaration);
        OutputAPIRow(type + " " + String(propertyName), true);
    }
    
    LOGRAW("\\section ScriptAPI_Classes Classes\n");
    
    unsigned types = scriptEngine_->GetObjectTypeCount();
    for (unsigned i = 0; i < types; ++i)
    {
        asIObjectType* type = scriptEngine_->GetObjectTypeByIndex(i);
        if (type)
        {
            String typeName(type->GetName());
            Vector<String> methodDeclarations;
            Vector<PropertyInfo> propertyInfos;
            
            LOGRAW("\n" + typeName + "\n");
            
            unsigned methods = type->GetMethodCount();
            for (unsigned j = 0; j < methods; ++j)
            {
                asIScriptFunction* method = type->GetMethodByIndex(j);
                String methodName(method->GetName());
                String declaration(method->GetDeclaration());
                if (methodName.Find("get_") == String::NPOS && methodName.Find("set_") == String::NPOS)
                {
                    // Sanitate the method name. For now, skip the operators
                    if (declaration.Find("::op") == String::NPOS)
                    {
                        String prefix(typeName + "::");
                        declaration.Replace(prefix, "");
                        methodDeclarations.Push(declaration);
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
                newInfo.name_ = String(propertyName);
                newInfo.type_ = String(propertyDeclaration);
                newInfo.read_ = newInfo.write_ = true;
                propertyInfos.Push(newInfo);
            }
            
            if (!methodDeclarations.Empty())
            {
                LOGRAW("\nMethods:<br>\n");
                for (unsigned j = 0; j < methodDeclarations.Size(); ++j)
                    OutputAPIRow(methodDeclarations[j]);
            }
            
            if (!propertyInfos.Empty())
            {
                LOGRAW("\nProperties:<br>\n");
                for (unsigned j = 0; j < propertyInfos.Size(); ++j)
                {
                    String remark;
                    if (!propertyInfos[j].write_)
                        remark = " (readonly)";
                    else if (!propertyInfos[j].read_)
                        remark = " (writeonly)";
                    
                    OutputAPIRow(propertyInfos[j].type_ + " " + propertyInfos[j].name_ + remark);
                }
            }
            
            LOGRAW("\n");
        }
    }
    
    LOGRAW("*/\n\n}\n");
}

void Script::MessageCallback(const asSMessageInfo* msg)
{
    String message = String(msg->section) + " (" + String(msg->row) + "," + String(msg->col) + ") " +
        String(msg->message);
    
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
        if (msg->type == asMSGTYPE_ERROR || msg->type == asMSGTYPE_WARNING)
            logMessages_ += message + "\n";
    }
}

void Script::ExceptionCallback(asIScriptContext* context)
{
    asIScriptFunction *function = context->GetExceptionFunction();
    String message = "Exception '" + String(context->GetExceptionString()) + "' in '" +
        String(function->GetDeclaration()) + "'";
    
    asSMessageInfo msg;
    msg.row = context->GetExceptionLineNumber(&msg.col, &msg.section);
    msg.type = asMSGTYPE_ERROR;
    msg.message = message.CString();
    
    MessageCallback(&msg);
}

ScriptFile* Script::GetDefaultScriptFile() const
{
    return defaultScriptFile_;
}

Scene* Script::GetDefaultScene() const
{
    return defaultScene_;
}

void Script::ClearObjectTypeCache()
{
    objectTypes_.Clear();
}

asIObjectType* Script::GetObjectType(const char* declaration)
{
    HashMap<const char*, asIObjectType*>::ConstIterator i = objectTypes_.Find(declaration);
    if (i != objectTypes_.End())
        return i->second_;
    
    asIObjectType* type = scriptEngine_->GetObjectTypeById(scriptEngine_->GetTypeIdByDecl(declaration));
    objectTypes_[declaration] = type;
    return type;
}

asIScriptContext* Script::GetScriptFileContext()
{
    while (scriptNestingLevel_ >= scriptFileContexts_.Size())
    {
        asIScriptContext* newContext = scriptEngine_->CreateContext();
        newContext->SetExceptionCallback(asMETHOD(Script, ExceptionCallback), this, asCALL_THISCALL);
        scriptFileContexts_.Push(newContext);
    }
    
    return scriptFileContexts_[scriptNestingLevel_];
}

void Script::OutputAPIRow(const String& row, bool removeReference)
{
    String out = row;
    out.Replace("double", "float");
    out.Replace("&in", "&");
    out.Replace("&out", "&");
    if (removeReference)
        out.Replace("&", "");
    
    LOGRAW("- " + out + "\n");
}

void RegisterScriptLibrary(Context* context)
{
    ScriptFile::RegisterObject(context);
    ScriptInstance::RegisterObject(context);
}

}
