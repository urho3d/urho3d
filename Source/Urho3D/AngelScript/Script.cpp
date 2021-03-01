//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../AngelScript/Addons.h"
#include "../AngelScript/Script.h"
#include "../AngelScript/ScriptAPI.h"
#include "../AngelScript/ScriptFile.h"
#include "../AngelScript/ScriptInstance.h"
#include "../AngelScript/RegistrationMacros.h"
#include "../Core/Profiler.h"
#include "../Engine/EngineEvents.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

class ScriptResourceRouter : public ResourceRouter
{
    URHO3D_OBJECT(ScriptResourceRouter, ResourceRouter);

    /// Construct.
    explicit ScriptResourceRouter(Context* context) :
        ResourceRouter(context)
    {
    }

    /// Check if request is for an AngelScript file and reroute to compiled version if necessary (.as file not available).
    void Route(String& name, ResourceRequest requestType) override
    {
        String extension = GetExtension(name);
        if (extension == ".as")
        {
            String replaced = ReplaceExtension(name, ".asc");
            // Note: ResourceCache prevents recursive calls to the resource routers so this is OK, the nested Exists()
            // check does not go through the router again
            auto* cache = GetSubsystem<ResourceCache>();
            if (!cache->Exists(name) && cache->Exists(replaced))
                name = replaced;
        }
    }
};

void ASRegisterManualFirst(asIScriptEngine* engine);
void ASRegisterGeneratedEnums(asIScriptEngine* engine);
void ASRegisterGeneratedObjectTypes(asIScriptEngine* engine);
void ASRegisterGeneratedDefaultConstructors(asIScriptEngine* engine);
void ASRegisterGeneratedClasses(asIScriptEngine* engine);

/*
void ASRegisterGenerated_Members_A(asIScriptEngine* engine);
void ASRegisterGenerated_Members_B(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Ca_Cm(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Cn_Cz(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Constraint(asIScriptEngine* engine);
void ASRegisterGenerated_Members_D(asIScriptEngine* engine);
void ASRegisterGenerated_Members_E(asIScriptEngine* engine);
void ASRegisterGenerated_Members_F(asIScriptEngine* engine);
void ASRegisterGenerated_Members_G(asIScriptEngine* engine);
void ASRegisterGenerated_Members_H(asIScriptEngine* engine);
void ASRegisterGenerated_Members_I(asIScriptEngine* engine);
void ASRegisterGenerated_Members_J(asIScriptEngine* engine);
void ASRegisterGenerated_Members_K(asIScriptEngine* engine);
void ASRegisterGenerated_Members_L(asIScriptEngine* engine);
void ASRegisterGenerated_Members_M(asIScriptEngine* engine);
void ASRegisterGenerated_Members_N(asIScriptEngine* engine);
void ASRegisterGenerated_Members_O(asIScriptEngine* engine);
void ASRegisterGenerated_Members_P(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Q(asIScriptEngine* engine);
void ASRegisterGenerated_Members_R(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Sa_Sm(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Sn_Sz(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Ta_Tm(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Tn_Tz(asIScriptEngine* engine);
void ASRegisterGenerated_Members_U(asIScriptEngine* engine);
void ASRegisterGenerated_Members_V(asIScriptEngine* engine);
void ASRegisterGenerated_Members_W(asIScriptEngine* engine);
void ASRegisterGenerated_Members_X(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Y(asIScriptEngine* engine);
void ASRegisterGenerated_Members_Z(asIScriptEngine* engine);

void ASRegisterGenerated_Members_Other(asIScriptEngine* engine);
*/

void ASRegisterGeneratedGlobalVariables(asIScriptEngine* engine);
void ASRegisterGeneratedGlobalFunctions(asIScriptEngine* engine);

void ASRegisterManualLast(asIScriptEngine* engine);

Script::Script(Context* context) :
    Object(context),
    scriptEngine_(nullptr),
    immediateContext_(nullptr),
    scriptNestingLevel_(0),
    executeConsoleCommands_(false)
{
    scriptEngine_ = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    if (!scriptEngine_)
    {
        URHO3D_LOGERROR("Could not create AngelScript engine");
        return;
    }

    scriptEngine_->SetUserData(this);
    scriptEngine_->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, (asPWORD)true);
    scriptEngine_->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, (asPWORD)true);
    scriptEngine_->SetEngineProperty(asEP_ALLOW_IMPLICIT_HANDLE_TYPES, (asPWORD)true);
    scriptEngine_->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, (asPWORD)true);
    scriptEngine_->SetEngineProperty(asEP_PROPERTY_ACCESSOR_MODE, 1);
    scriptEngine_->SetMessageCallback(asMETHOD(Script, MessageCallback), this, asCALL_THISCALL);

    // Create the context for immediate execution
    immediateContext_ = scriptEngine_->CreateContext();
    immediateContext_->SetExceptionCallback(asMETHOD(Script, ExceptionCallback), this, asCALL_THISCALL);

    // Register Script library object factories
    RegisterScriptLibrary(context_);

    // Register the Array, String & Dictionary API
    RegisterScriptInterfaceAPI(scriptEngine_);

    ASRegisterManualFirst(scriptEngine_);
    ASRegisterGeneratedEnums(scriptEngine_);
    ASRegisterGeneratedObjectTypes(scriptEngine_);
    ASRegisterGeneratedDefaultConstructors(scriptEngine_);
    ASRegisterGeneratedClasses(scriptEngine_);

    /*
    ASRegisterGenerated_Members_A(scriptEngine_);
    ASRegisterGenerated_Members_B(scriptEngine_);
    ASRegisterGenerated_Members_Ca_Cm(scriptEngine_);
    ASRegisterGenerated_Members_Cn_Cz(scriptEngine_);
    ASRegisterGenerated_Members_Constraint(scriptEngine_);
    ASRegisterGenerated_Members_D(scriptEngine_);
    ASRegisterGenerated_Members_E(scriptEngine_);
    ASRegisterGenerated_Members_F(scriptEngine_);
    ASRegisterGenerated_Members_G(scriptEngine_);
    ASRegisterGenerated_Members_H(scriptEngine_);
    ASRegisterGenerated_Members_I(scriptEngine_);
    ASRegisterGenerated_Members_J(scriptEngine_);
    ASRegisterGenerated_Members_K(scriptEngine_);
    ASRegisterGenerated_Members_L(scriptEngine_);
    ASRegisterGenerated_Members_M(scriptEngine_);
    ASRegisterGenerated_Members_N(scriptEngine_);
    ASRegisterGenerated_Members_O(scriptEngine_);
    ASRegisterGenerated_Members_P(scriptEngine_);
    ASRegisterGenerated_Members_Q(scriptEngine_);
    ASRegisterGenerated_Members_R(scriptEngine_);
    ASRegisterGenerated_Members_Sa_Sm(scriptEngine_);
    ASRegisterGenerated_Members_Sn_Sz(scriptEngine_);
    ASRegisterGenerated_Members_Ta_Tm(scriptEngine_);
    ASRegisterGenerated_Members_Tn_Tz(scriptEngine_);
    ASRegisterGenerated_Members_U(scriptEngine_);
    ASRegisterGenerated_Members_V(scriptEngine_);
    ASRegisterGenerated_Members_W(scriptEngine_);
    ASRegisterGenerated_Members_X(scriptEngine_);
    ASRegisterGenerated_Members_Y(scriptEngine_);
    ASRegisterGenerated_Members_Z(scriptEngine_);

    ASRegisterGenerated_Members_Other(scriptEngine_);
    */

    ASRegisterGeneratedGlobalVariables(scriptEngine_);
    ASRegisterGeneratedGlobalFunctions(scriptEngine_);

    ASRegisterManualLast(scriptEngine_);

    // Register the rest of the script API
    RegisterCoreAPI(scriptEngine_);
    RegisterSceneAPI(scriptEngine_);

    RegisterScriptAPI(scriptEngine_);

    // Subscribe to console commands
    SetExecuteConsoleCommands(true);

    // Create and register resource router for checking for compiled AngelScript files
    auto* cache = GetSubsystem<ResourceCache>();
    if (cache)
    {
        router_ = new ScriptResourceRouter(context_);
        cache->AddResourceRouter(router_);
    }
}

Script::~Script()
{
    if (immediateContext_)
    {
        immediateContext_->Release();
        immediateContext_ = nullptr;
    }

    for (unsigned i = 0; i < scriptFileContexts_.Size(); ++i)
        scriptFileContexts_[i]->Release();

    if (scriptEngine_)
    {
        scriptEngine_->Release();
        scriptEngine_ = nullptr;
    }

    auto* cache = GetSubsystem<ResourceCache>();
    if (cache)
        cache->RemoveResourceRouter(router_);
}

bool Script::Execute(const String& line)
{
    // Note: compiling code each time is slow. Not to be used for performance-critical or repeating activity
    URHO3D_PROFILE(ExecuteImmediate);

    ClearObjectTypeCache();

    String wrappedLine = "void f(){\n" + line + ";\n}";

    // If no immediate mode script file set, create a dummy module for compiling the line
    asIScriptModule* module = nullptr;
    if (defaultScriptFile_)
        module = defaultScriptFile_->GetScriptModule();
    if (!module)
        module = scriptEngine_->GetModule("ExecuteImmediate", asGM_CREATE_IF_NOT_EXISTS);
    if (!module)
        return false;

    asIScriptFunction* function = nullptr;
    if (module->CompileFunction("", wrappedLine.CString(), -1, 0, &function) < 0)
        return false;

    if (immediateContext_->Prepare(function) < 0)
    {
        function->Release();
        return false;
    }

    bool success = immediateContext_->Execute() >= 0;
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

void Script::SetExecuteConsoleCommands(bool enable)
{
    if (enable == executeConsoleCommands_)
        return;

    executeConsoleCommands_ = enable;
    if (enable)
        SubscribeToEvent(E_CONSOLECOMMAND, URHO3D_HANDLER(Script, HandleConsoleCommand));
    else
        UnsubscribeFromEvent(E_CONSOLECOMMAND);
}

void Script::MessageCallback(const asSMessageInfo* msg)
{
    String message;
    message.AppendWithFormat("%s:%d,%d %s", msg->section, msg->row, msg->col, msg->message);

    switch (msg->type)
    {
    case asMSGTYPE_ERROR:
        URHO3D_LOGERROR(message);
        break;

    case asMSGTYPE_WARNING:
        URHO3D_LOGWARNING(message);
        break;

    default:
        URHO3D_LOGINFO(message);
        break;
    }
}

void Script::ExceptionCallback(asIScriptContext* context)
{
    String message;
    message.AppendWithFormat("- Exception '%s' in '%s'\n%s", context->GetExceptionString(),
        context->GetExceptionFunction()->GetDeclaration(), GetCallStack(context).CString());

    asSMessageInfo msg{};
    msg.row = context->GetExceptionLineNumber(&msg.col, &msg.section);
    msg.type = asMSGTYPE_ERROR;
    msg.message = message.CString();

    MessageCallback(&msg);
}

String Script::GetCallStack(asIScriptContext* context)
{
    String str("AngelScript callstack:\n");

    // Append the call stack
    for (asUINT i = 0; i < context->GetCallstackSize(); i++)
    {
        asIScriptFunction* func;
        const char* scriptSection;
        int line, column;
        func = context->GetFunction(i);
        line = context->GetLineNumber(i, &column, &scriptSection);
        str.AppendWithFormat("\t%s:%s:%d,%d\n", scriptSection, func->GetDeclaration(), line, column);
    }

    return str;
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

asITypeInfo* Script::GetObjectType(const char* declaration)
{
    HashMap<const char*, asITypeInfo*>::ConstIterator i = objectTypes_.Find(declaration);
    if (i != objectTypes_.End())
        return i->second_;

    asITypeInfo* type = scriptEngine_->GetTypeInfoById(scriptEngine_->GetTypeIdByDecl(declaration));
    objectTypes_[declaration] = type;
    return type;
}

const char **Script::GetEnumValues(int asTypeID)
{
    // If we've already found it, do not try to update the values, as that may invalidate the buffer
    if (enumValues_.Contains(asTypeID))
        return enumValues_[asTypeID].Buffer();

    asITypeInfo* type = scriptEngine_->GetTypeInfoById(asTypeID);
    if (!type)
        return nullptr;

    if (!(type->GetFlags() & asOBJ_ENUM))
        return nullptr;

    unsigned count = type->GetEnumValueCount();
    enumValues_[asTypeID].Resize(count + 1);
    for (unsigned i = 0; i < count; ++i)
    {
        int val = -1;
        const char* name = type->GetEnumValueByIndex(i,&val);
        if ((unsigned)val >= count)// use unsigned for val so negative values will be flagged as invalid
        {
            URHO3D_LOGDEBUGF("Could not register enum attribute names for type %d."
                      "%s has value of %d, which is outside of the range [0,%d) for a 0-based enum.",
                      asTypeID,name,val,count);

            //fill with empty buffer
            enumValues_[asTypeID] = PODVector<const char*>();
            return nullptr;
        }
        else
        {
            enumValues_[asTypeID][i] = name;
        }
    }
    enumValues_[asTypeID][count] = nullptr;
    return enumValues_[asTypeID].Buffer();
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

void Script::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;
    if (eventData[P_ID].GetString() == GetTypeName())
        Execute(eventData[P_COMMAND].GetString());
}

void RegisterScriptLibrary(Context* context)
{
    ScriptFile::RegisterObject(context);
    ScriptInstance::RegisterObject(context);
}

}
