//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../AngelScript/APITemplates.h"
#include "../IO/Compression.h"
#include "../IO/FileSystem.h"
#include "../IO/NamedPipe.h"
#include "../IO/PackageFile.h"

namespace Urho3D
{

void FakeAddRef(void* ptr)
{
}

void FakeReleaseRef(void* ptr)
{
}

static Log* GetLog()
{
    return GetScriptContext()->GetSubsystem<Log>();
}

#ifdef URHO3D_LOGGING

static void Print(const String& value, bool error)
{
    Log::WriteRaw(value + "\n", error);
}

static void Print(int value, bool error)
{
    Log::WriteRaw(String(value) + "\n", error);
}

static void Print(unsigned value, bool error)
{
    Log::WriteRaw(String(value) + "\n", error);
}

static void Print(float value, bool error)
{
    Log::WriteRaw(String(value) + "\n", error);
}

static void Print(bool value, bool error)
{
    Log::WriteRaw(String(value) + "\n", error);
}

static void Print(const Variant& value, bool error)
{
    Log::WriteRaw(value.ToString() + "\n", error);
}

static void PrintCallStack(bool error)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
        Log::WriteRaw(Script::GetCallStack(context), error);
}

static void LogWrite(const String& str, bool error, Log* ptr)
{
    Log::WriteRaw(str + "\n", error);
}

static void LogDebug(const String& str, Log* ptr)
{
    Log::Write(LOG_DEBUG, str);
}

static void LogInfo(const String& str, Log* ptr)
{
    Log::Write(LOG_INFO, str);
}

static void LogWarning(const String& str, Log* ptr)
{
    Log::Write(LOG_WARNING, str);
}

static void LogError(const String& str, Log* ptr)
{
    Log::Write(LOG_ERROR, str);
}

#else

static void Print(const String& value, bool error) { }
static void Print(int value, bool error) { }
static void Print(unsigned value, bool error) { }
static void Print(float value, bool error) { }
static void Print(bool value, bool error) { }
static void Print(const Variant& value, bool error) { }
static void PrintCallStack(bool error) { }
static void LogWrite(const String& str, bool error, Log* ptr) { }
static void LogDebug(const String& str, Log* ptr) { }
static void LogInfo(const String& str, Log* ptr) { }
static void LogWarning(const String& str, Log* ptr) { }
static void LogError(const String& str, Log* ptr) { }

#endif

static void RegisterLog(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const int LOG_DEBUG", (void*)&LOG_DEBUG);
    engine->RegisterGlobalProperty("const int LOG_INFO", (void*)&LOG_INFO);
    engine->RegisterGlobalProperty("const int LOG_WARNING", (void*)&LOG_WARNING);
    engine->RegisterGlobalProperty("const int LOG_ERROR", (void*)&LOG_ERROR);
    engine->RegisterGlobalProperty("const int LOG_NONE", (void*)&LOG_NONE);

    RegisterObject<Log>(engine, "Log");
    engine->RegisterObjectMethod("Log", "void Open(const String&in)", asMETHOD(Log, Open), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void Close()", asMETHOD(Log, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void Write(const String&in, bool error = false)", asFUNCTION(LogWrite), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Debug(const String&in)", asFUNCTION(LogDebug), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Info(const String&in)", asFUNCTION(LogInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Warning(const String&in)", asFUNCTION(LogWarning), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Error(const String&in)", asFUNCTION(LogError), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void set_level(int)", asMETHOD(Log, SetLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_level() const", asMETHOD(Log, GetLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_timeStamp(bool)", asMETHOD(Log, SetTimeStamp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_timeStamp() const", asMETHOD(Log, GetTimeStamp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "String get_lastMessage()", asMETHOD(Log, GetLastMessage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_quiet(bool)", asMETHOD(Log, SetQuiet), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_quiet() const", asMETHOD(Log, IsQuiet), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Log@+ get_log()", asFUNCTION(GetLog), asCALL_CDECL);

    // Register also Print() functions for convenience
    engine->RegisterGlobalFunction("void Print(const String&in, bool error = false)", asFUNCTIONPR(Print, (const String&, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(int, bool error = false)", asFUNCTIONPR(Print, (int, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(uint, bool error = false)", asFUNCTIONPR(Print, (unsigned, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(float, bool error = false)", asFUNCTIONPR(Print, (float, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(bool, bool error = false)", asFUNCTIONPR(Print, (bool, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(const Variant&in, bool error = false)", asFUNCTIONPR(Print, (const Variant&, bool), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void PrintCallStack(bool error = false)", asFUNCTION(PrintCallStack), asCALL_CDECL);
}

static File* ConstructFile()
{
    return new File(GetScriptContext());
}

static File* ConstructFileAndOpen(const String& fileName, FileMode mode)
{
    return new File(GetScriptContext(), fileName, mode);
}

static NamedPipe* ConstructNamedPipe()
{
    return new NamedPipe(GetScriptContext());
}

static NamedPipe* ConstructNamedPipeAndOpen(const String& fileName, bool isServer)
{
    return new NamedPipe(GetScriptContext(), fileName, isServer);
}

static void ConstructVectorBuffer(VectorBuffer* ptr)
{
    new(ptr) VectorBuffer();
}

static void ConstructVectorBufferCopy(const VectorBuffer& buffer, VectorBuffer* ptr)
{
    new(ptr) VectorBuffer(buffer);
}

static void ConstructVectorBufferFromStream(Deserializer* src, unsigned size, VectorBuffer* ptr)
{
    if (src)
        new(ptr) VectorBuffer(*src, size);
    else
        new(ptr) VectorBuffer();
}

static void DestructVectorBuffer(VectorBuffer* ptr)
{
    ptr->~VectorBuffer();
}

static void VectorBufferSetData(Deserializer* src, unsigned size, VectorBuffer* ptr)
{
    if (src)
        ptr->SetData(*src, size);
}

static unsigned char* VectorBufferAt(unsigned index, VectorBuffer* ptr)
{
    if (index >= ptr->GetSize())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return 0;
    }

    return ptr->GetModifiableData() + index;
}

static void ConstructVariantVectorBuffer(const VectorBuffer& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static VectorBuffer VariantGetBuffer(Variant* ptr)
{
    VectorBuffer ret(ptr->GetBuffer());
    return ret;
}

static FileSystem* GetFileSystem()
{
    return GetScriptContext()->GetSubsystem<FileSystem>();
}

static CScriptArray* FileSystemScanDir(const String& pathName, const String& filter, unsigned flags, bool recursive, FileSystem* ptr)
{
    Vector<String> result;
    ptr->ScanDir(result, pathName, filter, flags, recursive);
    return VectorToArray<String>(result, "Array<String>");
}

static int FileSystemSystemRun(const String& fileName, CScriptArray* srcArguments, FileSystem* ptr)
{
    if (!srcArguments)
        return -1;

    unsigned numArguments = srcArguments->GetSize();
    Vector<String> destArguments(numArguments);
    for (unsigned i = 0; i < numArguments; ++i)
        destArguments[i] = *(static_cast<String*>(srcArguments->At(i)));

    return ptr->SystemRun(fileName, destArguments);
}

static unsigned FileSystemSystemRunAsync(const String& fileName, CScriptArray* srcArguments, FileSystem* ptr)
{
    if (!srcArguments)
        return M_MAX_UNSIGNED;

    unsigned numArguments = srcArguments->GetSize();
    Vector<String> destArguments(numArguments);
    for (unsigned i = 0; i < numArguments; ++i)
        destArguments[i] = *(static_cast<String*>(srcArguments->At(i)));

    return ptr->SystemRunAsync(fileName, destArguments);
}

static void RegisterSerialization(asIScriptEngine* engine)
{
    engine->RegisterEnum("FileMode");
    engine->RegisterEnumValue("FileMode", "FILE_READ", FILE_READ);
    engine->RegisterEnumValue("FileMode", "FILE_WRITE", FILE_WRITE);
    engine->RegisterEnumValue("FileMode", "FILE_READWRITE", FILE_READWRITE);

    engine->RegisterGlobalProperty("const uint SCAN_FILES", (void*)&SCAN_FILES);
    engine->RegisterGlobalProperty("const uint SCAN_DIRS", (void*)&SCAN_DIRS);
    engine->RegisterGlobalProperty("const uint SCAN_HIDDEN", (void*)&SCAN_HIDDEN);

    engine->RegisterObjectType("VectorBuffer", sizeof(VectorBuffer), asOBJ_VALUE | asOBJ_APP_CLASS_CDK);
    engine->RegisterObjectType("Serializer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    RegisterSerializer<Serializer>(engine, "Serializer");

    engine->RegisterObjectType("Deserializer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    RegisterDeserializer<Deserializer>(engine, "Deserializer");

    RegisterObject<File>(engine, "File");
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f()", asFUNCTION(ConstructFile), asCALL_CDECL);
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(const String&in, FileMode mode = FILE_READ)", asFUNCTION(ConstructFileAndOpen), asCALL_CDECL);
    engine->RegisterObjectMethod("File", "bool Open(const String&in, FileMode mode = FILE_READ)", asMETHODPR(File, Open, (const String&, FileMode), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "void Close()", asMETHOD(File, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "FileMode get_mode() const", asMETHOD(File, GetMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_open()", asMETHOD(File, IsOpen), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_packaged()", asMETHOD(File, IsPackaged), asCALL_THISCALL);
    RegisterSerializer<File>(engine, "File");
    RegisterDeserializer<File>(engine, "File");

    RegisterObject<NamedPipe>(engine, "NamedPipe");
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f()", asFUNCTION(ConstructNamedPipe), asCALL_CDECL);
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f(const String&in, bool)", asFUNCTION(ConstructNamedPipeAndOpen), asCALL_CDECL);
    engine->RegisterObjectMethod("NamedPipe", "bool Open(const String&in, bool)", asMETHODPR(NamedPipe, Open, (const String&, bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "void Close()", asMETHOD(NamedPipe, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_server() const", asMETHOD(NamedPipe, IsServer), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_open() const", asMETHOD(NamedPipe, IsOpen), asCALL_THISCALL);
    RegisterSerializer<File>(engine, "NamedPipe");
    RegisterDeserializer<File>(engine, "NamedPipe");

    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", asFUNCTION(ConstructVectorBufferCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer@+, uint)", asFUNCTION(ConstructVectorBufferFromStream), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "VectorBuffer& opAssign(const VectorBuffer&in)", asMETHODPR(VectorBuffer, operator =, (const VectorBuffer&), VectorBuffer&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void SetData(Deserializer@+, uint)", asFUNCTION(VectorBufferSetData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "void Clear()", asMETHOD(VectorBuffer, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void Resize(uint)", asMETHOD(VectorBuffer, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint8 &opIndex(uint)", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "const uint8 &opIndex(uint) const", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    RegisterSerializer<VectorBuffer>(engine, "VectorBuffer");
    RegisterDeserializer<VectorBuffer>(engine, "VectorBuffer");

    // Register VectorBuffer conversions to Variant
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", asFUNCTION(ConstructVariantVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VectorBuffer&in)", asMETHODPR(Variant, operator =, (const VectorBuffer&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VectorBuffer&in) const", asMETHODPR(Variant, operator ==, (const VectorBuffer&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetBuffer() const", asMETHOD(Variant, GetVectorBuffer), asCALL_THISCALL);

    // Register VectorBuffer compression functions
    engine->RegisterGlobalFunction("VectorBuffer CompressVectorBuffer(VectorBuffer&in)", asFUNCTION(CompressVectorBuffer), asCALL_CDECL);
    engine->RegisterGlobalFunction("VectorBuffer DecompressVectorBuffer(VectorBuffer&in)", asFUNCTION(DecompressVectorBuffer), asCALL_CDECL);
}

void RegisterFileSystem(asIScriptEngine* engine)
{
    RegisterObject<FileSystem>(engine, "FileSystem");
    engine->RegisterObjectMethod("FileSystem", "bool FileExists(const String&in) const", asMETHOD(FileSystem, FileExists), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool DirExists(const String&in) const", asMETHOD(FileSystem, DirExists), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool SetLastModifiedTime(const String&in, uint)", asMETHOD(FileSystem, SetLastModifiedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "uint GetLastModifiedTime(const String&in) const", asMETHOD(FileSystem, GetLastModifiedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "Array<String>@ ScanDir(const String&in, const String&in, uint, bool) const", asFUNCTION(FileSystemScanDir), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSystem", "bool CreateDir(const String&in)", asMETHOD(FileSystem, CreateDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int SystemCommand(const String&in, bool redirectStdOutToLog = false)", asMETHOD(FileSystem, SystemCommand), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int SystemRun(const String&in, Array<String>@+)", asFUNCTION(FileSystemSystemRun), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSystem", "uint SystemCommandAsync(const String&in)", asMETHOD(FileSystem, SystemCommandAsync), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "uint SystemRunAsync(const String&in, Array<String>@+)", asFUNCTION(FileSystemSystemRunAsync), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSystem", "bool SystemOpen(const String&in, const String&in)", asMETHOD(FileSystem, SystemOpen), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Copy(const String&in, const String&in)", asMETHOD(FileSystem, Copy), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Rename(const String&in, const String&in)", asMETHOD(FileSystem, Rename), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Delete(const String&in)", asMETHOD(FileSystem, Delete), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String GetAppPreferencesDir(const String&in org, const String&in app) const", asMETHOD(FileSystem, GetAppPreferencesDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_currentDir() const", asMETHOD(FileSystem, GetCurrentDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_currentDir(const String&in)", asMETHOD(FileSystem, SetCurrentDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_executeConsoleCommands(bool)", asMETHOD(FileSystem, SetExecuteConsoleCommands), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool get_executeConsoleCommands() const", asMETHOD(FileSystem, GetExecuteConsoleCommands), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_programDir() const", asMETHOD(FileSystem, GetProgramDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_userDocumentsDir() const", asMETHOD(FileSystem, GetUserDocumentsDir), asCALL_THISCALL);
    engine->RegisterGlobalFunction("FileSystem@+ get_fileSystem()", asFUNCTION(GetFileSystem), asCALL_CDECL);

    engine->RegisterGlobalFunction("String GetPath(const String&in)", asFUNCTION(GetPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetFileName(const String&in)", asFUNCTION(GetFileName), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetExtension(const String&in, bool lowercaseExtension = true)", asFUNCTION(GetExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetFileNameAndExtension(const String&in, bool lowercaseExtension = false)", asFUNCTION(GetFileNameAndExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("String ReplaceExtension(const String&in, const String&in)", asFUNCTION(ReplaceExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("String AddTrailingSlash(const String&in)", asFUNCTION(AddTrailingSlash), asCALL_CDECL);
    engine->RegisterGlobalFunction("String RemoveTrailingSlash(const String&in)", asFUNCTION(RemoveTrailingSlash), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetParentPath(const String&in)", asFUNCTION(GetParentPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetInternalPath(const String&in)", asFUNCTION(GetInternalPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsAbsolutePath(const String&in)", asFUNCTION(IsAbsolutePath), asCALL_CDECL);
}

static PackageFile* ConstructPackageFile()
{
    return new PackageFile(GetScriptContext());
}

static PackageFile* ConstructAndOpenPackageFile(const String& fileName, unsigned startOffset)
{
    return new PackageFile(GetScriptContext(), fileName, startOffset);
}

static const CScriptArray* PackageFileGetEntryNames(PackageFile* packageFile)
{
    return VectorToArray<String>(packageFile->GetEntryNames(), "Array<String>");
}

static void RegisterPackageFile(asIScriptEngine* engine)
{
    RegisterObject<PackageFile>(engine, "PackageFile");
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f()", asFUNCTION(ConstructPackageFile), asCALL_CDECL);
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const String&in, uint startOffset = 0)", asFUNCTION(ConstructAndOpenPackageFile), asCALL_CDECL);
    engine->RegisterObjectMethod("PackageFile", "bool Open(const String&in, uint startOffset = 0) const", asMETHOD(PackageFile, Open), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool Exists(const String&in) const", asMETHOD(PackageFile, Exists), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_name() const", asMETHOD(PackageFile, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_numFiles() const", asMETHOD(PackageFile, GetNumFiles), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalSize() const", asMETHOD(PackageFile, GetTotalSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalDataSize() const", asMETHOD(PackageFile, GetTotalDataSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_checksum() const", asMETHOD(PackageFile, GetChecksum), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool compressed() const", asMETHOD(PackageFile, IsCompressed), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "Array<String>@ GetEntryNames() const", asFUNCTION(PackageFileGetEntryNames), asCALL_CDECL_OBJLAST);
}

void RegisterIOAPI(asIScriptEngine* engine)
{
    RegisterLog(engine);
    RegisterSerialization(engine);
    RegisterFileSystem(engine);
    RegisterPackageFile(engine);
}

}
