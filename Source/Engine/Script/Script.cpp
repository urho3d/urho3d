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

#include "Precompiled.h"
#include "Addons.h"
#include "Context.h"
#include "EngineEvents.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"
#include "Profiler.h"
#include "Scene.h"
#include "Script.h"
#include "ScriptAPI.h"
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
        {
            info = &propertyInfos[k];
            break;
        }
    }
    if (!info)
    {
        propertyInfos.Resize(propertyInfos.Size() + 1);
        info = &propertyInfos.Back();
        info->name_ = propertyName;
    }
    if (functionName.Contains("get_"))
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
        if (!declaration.Contains("()"))
        {
            info->indexed_ = true;
            info->type_ += "[]";
        }

        // Sanitate the reference operator away
        info->type_.Replace("&", "");
    }
    if (functionName.Contains("set_"))
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

bool ComparePropertyStrings(const String& lhs, const String& rhs)
{
    int spaceLhs = lhs.Find(' ');
    int spaceRhs = rhs.Find(' ');
    if (spaceLhs != String::NPOS && spaceRhs != String::NPOS)
        return String::Compare(lhs.CString() + spaceLhs, rhs.CString() + spaceRhs, true) < 0;
    else
        return String::Compare(lhs.CString(), rhs.CString(), true) < 0;
}

bool ComparePropertyInfos(const PropertyInfo& lhs, const PropertyInfo& rhs)
{
    return String::Compare(lhs.name_.CString(), rhs.name_.CString(), true) < 0;
}

Script::Script(Context* context) :
    Object(context),
    scriptEngine_(0),
    immediateContext_(0),
    scriptNestingLevel_(0),
    executeConsoleCommands_(true)
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

    // Register Script library object factories
    RegisterScriptLibrary(context_);

    // Register the Array, String & Dictionary API
    RegisterArray(scriptEngine_);
    RegisterString(scriptEngine_);
    RegisterDictionary(scriptEngine_);

    // Register the rest of the script API
    RegisterMathAPI(scriptEngine_);
    RegisterCoreAPI(scriptEngine_);
    RegisterIOAPI(scriptEngine_);
    RegisterResourceAPI(scriptEngine_);
    RegisterSceneAPI(scriptEngine_);
    RegisterGraphicsAPI(scriptEngine_);
    RegisterInputAPI(scriptEngine_);
    RegisterAudioAPI(scriptEngine_);
    RegisterUIAPI(scriptEngine_);
    RegisterNetworkAPI(scriptEngine_);
    RegisterPhysicsAPI(scriptEngine_);
    RegisterNavigationAPI(scriptEngine_);
    RegisterUrho2DAPI(scriptEngine_);
    RegisterScriptAPI(scriptEngine_);
    RegisterEngineAPI(scriptEngine_);

    // Subscribe to console commands
    SubscribeToEvent(E_CONSOLECOMMAND, HANDLER(Script, HandleConsoleCommand));
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
    executeConsoleCommands_ = enable;
}

void Script::DumpAPI(DumpMode mode)
{
    // Does not use LOGRAW macro here to ensure the messages are always dumped regardless of ENABLE_LOGGING compiler directive and of Log subsystem availability
    if (mode == DOXYGEN)
        Log::WriteRaw("namespace Urho3D\n{\n\n/**\n\\page ScriptAPI Scripting API\n\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("// Script API header intended to be 'force included' in IDE for AngelScript content assist / code completion\n\n"
            "#define int8 signed char\n"
            "#define int16 signed short\n"
            "#define int64 long\n"
            "#define uint8 unsigned char\n"
            "#define uint16 unsigned short\n"
            "#define uint64 unsigned long\n"
            "#define null 0\n");

    if (mode == DOXYGEN)
        Log::WriteRaw("\\section ScriptAPI_Classes Classes\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("\n// Classes\n");

    unsigned types = scriptEngine_->GetObjectTypeCount();
    Vector<Pair<String, unsigned> > sortedTypes;
    for (unsigned i = 0; i < types; ++i)
    {
        asIObjectType* type = scriptEngine_->GetObjectTypeByIndex(i);
        if (type)
        {
            String typeName(type->GetName());
            sortedTypes.Push(MakePair(typeName, i));
        }
    }
    Sort(sortedTypes.Begin(), sortedTypes.End());
    
    for (unsigned i = 0; i < sortedTypes.Size(); ++i)
    {
        asIObjectType* type = scriptEngine_->GetObjectTypeByIndex(sortedTypes[i].second_);
        if (type)
        {
            String typeName(type->GetName());
            Vector<String> methodDeclarations;
            Vector<PropertyInfo> propertyInfos;

            if (mode == DOXYGEN)
                Log::WriteRaw("\n### " + typeName + "\n");
            else if (mode == C_HEADER)
            {
                ///\todo Find a cleaner way to do this instead of hardcoding
                if (typeName == "Array")
                    Log::WriteRaw("\ntemplate <class T> class " + typeName + "\n{\n");
                else
                    Log::WriteRaw("\nclass " + typeName + "\n{\n");
            }

            unsigned methods = type->GetMethodCount();
            for (unsigned j = 0; j < methods; ++j)
            {
                asIScriptFunction* method = type->GetMethodByIndex(j);
                String methodName(method->GetName());
                String declaration(method->GetDeclaration());
                if (methodName.Contains("get_") || methodName.Contains("set_"))
                    ExtractPropertyInfo(methodName, declaration, propertyInfos);
                else
                {
                    // Sanitate the method name. \todo For now, skip the operators
                    if (!declaration.Contains("::op"))
                    {
                        String prefix(typeName + "::");
                        declaration.Replace(prefix, "");
                        ///\todo Is there a better way to mark deprecated API bindings for AngelScript?
                        unsigned posBegin = declaration.FindLast("const String&in = \"deprecated:");
                        if (posBegin != String::NPOS)
                        {
                            // Assume this 'mark' is added as the last parameter
                            unsigned posEnd = declaration.Find(')', posBegin);
                            if (posBegin != String::NPOS)
                            {
                                declaration.Replace(posBegin, posEnd - posBegin, "");
                                posBegin = declaration.Find(", ", posBegin - 2);
                                if (posBegin != String::NPOS)
                                    declaration.Replace(posBegin, 2, "");
                                if (mode == DOXYGEN)
                                    declaration += " // deprecated";
                                else if (mode == C_HEADER)
                                    declaration = "/* deprecated */\n" + declaration;
                            }
                        }
                        methodDeclarations.Push(declaration);
                    }
                }
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
            
            Sort(methodDeclarations.Begin(), methodDeclarations.End(), ComparePropertyStrings);
            Sort(propertyInfos.Begin(), propertyInfos.End(), ComparePropertyInfos);
            
            if (!methodDeclarations.Empty())
            {
                if (mode == DOXYGEN)
                    Log::WriteRaw("\nMethods:\n\n");
                else if (mode == C_HEADER)
                    Log::WriteRaw("// Methods:\n");
                for (unsigned j = 0; j < methodDeclarations.Size(); ++j)
                    OutputAPIRow(mode, methodDeclarations[j]);
            }

            if (!propertyInfos.Empty())
            {
                if (mode == DOXYGEN)
                    Log::WriteRaw("\nProperties:\n\n");
                else if (mode == C_HEADER)
                    Log::WriteRaw("\n// Properties:\n");
                for (unsigned j = 0; j < propertyInfos.Size(); ++j)
                {
                    String remark;
                    String cppdoc;
                    if (!propertyInfos[j].write_)
                        remark = "readonly";
                    else if (!propertyInfos[j].read_)
                        remark = "writeonly";
                    if (!remark.Empty())
                    {
                        if (mode == DOXYGEN)
                        {
                            remark = " // " + remark;
                        }
                        else if (mode == C_HEADER)
                        {
                            cppdoc = "/* " + remark + " */\n";
                            remark.Clear();
                        }
                    }

                    OutputAPIRow(mode, cppdoc + propertyInfos[j].type_ + " " + propertyInfos[j].name_ + remark);
                }
            }

            if (mode == DOXYGEN)
                Log::WriteRaw("\n");
            else if (mode == C_HEADER)
                Log::WriteRaw("};\n");
        }
    }

    Vector<PropertyInfo> globalPropertyInfos;
    Vector<String> globalFunctions;

    unsigned functions = scriptEngine_->GetGlobalFunctionCount();
    for (unsigned i = 0; i < functions; ++i)
    {
        asIScriptFunction* function = scriptEngine_->GetGlobalFunctionByIndex(i);
        String functionName(function->GetName());
        String declaration(function->GetDeclaration());

        if (functionName.Contains("set_") || functionName.Contains("get_"))
            ExtractPropertyInfo(functionName, declaration, globalPropertyInfos);
        else
            globalFunctions.Push(declaration);
    }

    Sort(globalFunctions.Begin(), globalFunctions.End(), ComparePropertyStrings);
    Sort(globalPropertyInfos.Begin(), globalPropertyInfos.End(), ComparePropertyInfos);

    if (mode == DOXYGEN)
        Log::WriteRaw("\\section ScriptAPI_Enums Enumerations\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("\n// Enumerations\n");

    unsigned enums = scriptEngine_->GetEnumCount();
    Vector<Pair<String, unsigned> > sortedEnums;
    for (unsigned i = 0; i < enums; ++i)
    {
        int typeId;
        sortedEnums.Push(MakePair(String(scriptEngine_->GetEnumByIndex(i, &typeId)), i));
    }
    Sort(sortedEnums.Begin(), sortedEnums.End());
    
    for (unsigned i = 0; i < sortedEnums.Size(); ++i)
    {
        int typeId;
        if (mode == DOXYGEN)
            Log::WriteRaw("\n### " + String(scriptEngine_->GetEnumByIndex(sortedEnums[i].second_, &typeId)) + "\n\n");
        else if (mode == C_HEADER)
            Log::WriteRaw("\nenum " + String(scriptEngine_->GetEnumByIndex(sortedEnums[i].second_, &typeId)) + "\n{\n");

        for (unsigned j = 0; j < (unsigned)scriptEngine_->GetEnumValueCount(typeId); ++j)
        {
            int value = 0;
            const char* name = scriptEngine_->GetEnumValueByIndex(typeId, j, &value);
            OutputAPIRow(mode, String(name), false, ",");
        }

        if (mode == DOXYGEN)
            Log::WriteRaw("\n");
        else if (mode == C_HEADER)
            Log::WriteRaw("};\n");
    }
    
    if (mode == DOXYGEN)
        Log::WriteRaw("\\section ScriptAPI_GlobalFunctions Global functions\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("\n// Global functions\n");

    for (unsigned i = 0; i < globalFunctions.Size(); ++i)
        OutputAPIRow(mode, globalFunctions[i]);

    if (mode == DOXYGEN)
        Log::WriteRaw("\\section ScriptAPI_GlobalProperties Global properties\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("\n// Global properties\n");

    for (unsigned i = 0; i < globalPropertyInfos.Size(); ++i)
        OutputAPIRow(mode, globalPropertyInfos[i].type_ + " " + globalPropertyInfos[i].name_, true);

    if (mode == DOXYGEN)
        Log::WriteRaw("\\section ScriptAPI_GlobalConstants Global constants\n");
    else if (mode == C_HEADER)
        Log::WriteRaw("\n// Global constants\n");

    Vector<String> globalConstants;
    unsigned properties = scriptEngine_->GetGlobalPropertyCount();
    for (unsigned i = 0; i < properties; ++i)
    {
        const char* propertyName;
        const char* propertyDeclaration;
        int typeId;
        scriptEngine_->GetGlobalPropertyByIndex(i, &propertyName, 0, &typeId);
        propertyDeclaration = scriptEngine_->GetTypeDeclaration(typeId);

        String type(propertyDeclaration);
        globalConstants.Push(type + " " + String(propertyName));
    }
    
    Sort(globalConstants.Begin(), globalConstants.End(), ComparePropertyStrings);
    
    for (unsigned i = 0; i < globalConstants.Size(); ++i)
        OutputAPIRow(mode, globalConstants[i], true);

    // Dump event descriptions in Doxygen mode. This means going through the header files, as the information is not
    // available otherwise
    if (mode == DOXYGEN)
    {
        FileSystem* fileSystem = GetSubsystem<FileSystem>();
        Vector<String> headerFiles;
        String path = fileSystem->GetProgramDir();
        path.Replace("/Bin", "/Source/Engine");
        
        fileSystem->ScanDir(headerFiles, path, "*.h", SCAN_FILES, true);
        if (!headerFiles.Empty())
        {
            Log::WriteRaw("\n\\page EventList Event list\n");
            Sort(headerFiles.Begin(), headerFiles.End());
        }
        
        for (unsigned i = 0; i < headerFiles.Size(); ++i)
        {
            if (headerFiles[i].EndsWith("Events.h"))
            {
                SharedPtr<File> file(new File(context_, path + headerFiles[i], FILE_READ));
                if (!file->IsOpen())
                    continue;
                
                unsigned start = headerFiles[i].Find('/') + 1;
                unsigned end = headerFiles[i].Find("Events.h");
                Log::WriteRaw("\n## %" + headerFiles[i].Substring(start, end - start) + " events\n");
                
                while (!file->IsEof())
                {
                    String line = file->ReadLine();
                    if (line.StartsWith("EVENT"))
                    {
                        Vector<String> parts = line.Split(',');
                        if (parts.Size() == 2)
                            Log::WriteRaw("\n### " + parts[1].Substring(0, parts[1].Length() - 1).Trimmed() + "\n");
                    }
                    if (line.Contains("PARAM"))
                    {
                        Vector<String> parts = line.Split(',');
                        if (parts.Size() == 2)
                        {
                            String paramName = parts[1].Substring(0, parts[1].Find(')')).Trimmed();
                            String paramType = parts[1].Substring(parts[1].Find("// ") + 3);
                            if (!paramName.Empty() && !paramType.Empty())
                                Log::WriteRaw("- %" + paramName + " : " + paramType + "\n");
                        }
                    }
                }
            }
        }
        
        if (!headerFiles.Empty())
            Log::WriteRaw("\n");
    }

    if (mode == DOXYGEN)
        Log::WriteRaw("*/\n\n}\n");
}

void Script::MessageCallback(const asSMessageInfo* msg)
{
    String message;
    message.AppendWithFormat("%s:%d,%d %s", msg->section, msg->row, msg->col, msg->message);

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

void Script::ExceptionCallback(asIScriptContext* context)
{
    String message;
    message.AppendWithFormat("- Exception '%s' in '%s'\n%s", context->GetExceptionString(), context->GetExceptionFunction()->GetDeclaration(), GetCallStack(context).CString());

    asSMessageInfo msg;
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

void Script::OutputAPIRow(DumpMode mode, const String& row, bool removeReference, String separator)
{
    String out(row);
    ///\todo We need C++11 <regex> in String class to handle REGEX whole-word replacement correctly. Can't do that since we still support VS2008.
    // Commenting out to temporary fix property name like 'doubleClickInterval' from being wrongly replaced.
    // Fortunately, there is no occurence of type 'double' in the API at the moment.
    //out.Replace("double", "float");   // s/\bdouble\b/float/g
    out.Replace("&in", "&");
    out.Replace("&out", "&");
    if (removeReference)
        out.Replace("&", "");

    if (mode == DOXYGEN)
        Log::WriteRaw("- " + out + "\n");
    else if (mode == C_HEADER)
    {
        out.Replace("@", "");
        out.Replace("?&", "void*");

        // s/(\w+)\[\]/Array<\1>/g
        unsigned posBegin = String::NPOS;
        while (1)   // Loop to cater for array of array of T
        {
            unsigned posEnd = out.Find("[]");
            if (posEnd == String::NPOS)
                break;
            if (posBegin > posEnd)
                posBegin = posEnd - 1;
            while (posBegin < posEnd && isalnum(out[posBegin]))
                --posBegin;
            ++posBegin;
            out.Replace(posBegin, posEnd - posBegin + 2, "Array<" + out.Substring(posBegin, posEnd - posBegin) + ">");
        }

        Log::WriteRaw(out + separator + "\n");
    }
}

void Script::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;

    if (executeConsoleCommands_)
        Execute(eventData[P_COMMAND].GetString());
}

void RegisterScriptLibrary(Context* context)
{
    ScriptFile::RegisterObject(context);
    ScriptInstance::RegisterObject(context);
}

}
