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
#include "APITemplates.h"
#include "FileSystem.h"
#include "Log.h"
#include "PackageFile.h"
#include "ProcessUtils.h"
#include "StringUtils.h"
#include "VectorBuffer.h"

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

static void Print(const String& value)
{
    GetLog()->WriteRaw(value + "\n");
}

static void Print(int value)
{
    GetLog()->WriteRaw(ToString(value) + "\n");
}

static void Print(float value)
{
    GetLog()->WriteRaw(ToString(value) + "\n");
}

static void Print(bool value)
{
    GetLog()->WriteRaw(ToString(value) + "\n");
}

static void LogWrite(const String& str, Log* ptr)
{
    ptr->WriteRaw(str + "\n");
}

static void LogDebug(const String& str, Log* ptr)
{
    ptr->Write(LOG_DEBUG, str);
}

static void LogInfo(const String& str, Log* ptr)
{
    ptr->Write(LOG_INFO, str);
}

static void LogWarning(const String& str, Log* ptr)
{
    ptr->Write(LOG_WARNING, str);
}

static void LogError(const String& str, Log* ptr)
{
    ptr->Write(LOG_ERROR, str);
}

static void RegisterLog(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const int LOG_DEBUG", (void*)&LOG_DEBUG);
    engine->RegisterGlobalProperty("const int LOG_INFO", (void*)&LOG_INFO);
    engine->RegisterGlobalProperty("const int LOG_WARNING", (void*)&LOG_WARNING);
    engine->RegisterGlobalProperty("const int LOG_ERROR", (void*)&LOG_ERROR);
    engine->RegisterGlobalProperty("const int LOG_NONE", (void*)&LOG_NONE);
    
    RegisterObject<Log>(engine, "Log");
    engine->RegisterObjectMethod("Log", "void Write(const String&in)", asFUNCTION(LogWrite), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Debug(const String&in)", asFUNCTION(LogDebug), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Info(const String&in)", asFUNCTION(LogInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Warning(const String&in)", asFUNCTION(LogWarning), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "void Error(const String&in)", asFUNCTION(LogError), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Log", "int get_level() const", asMETHOD(Log, GetLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_level(int)", asMETHOD(Log, SetLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const String& get_lastMessage()", asMETHOD(Log, GetLastMessage), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Log@+ get_log()", asFUNCTION(GetLog), asCALL_CDECL);
    
    // Register also Print() functions for convenience
    engine->RegisterGlobalFunction("void Print(const String&in)", asFUNCTIONPR(Print, (const String&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(int)", asFUNCTIONPR(Print, (int), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(float)", asFUNCTIONPR(Print, (float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void Print(bool)", asFUNCTIONPR(Print, (bool), void), asCALL_CDECL);
}

static File* ConstructFile()
{
    return new File(GetScriptContext());
}

static File* ConstructFileAndOpen(const String& fileName, FileMode mode)
{
    return new File(GetScriptContext(), fileName, mode);
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
    if (!src)
        size = 0;
    
    new(ptr) VectorBuffer(*src, size);
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

static void ConstructVariantBuffer(const VectorBuffer& buffer, Variant* ptr)
{
    new(ptr) Variant(buffer.GetBuffer());
}

static VectorBuffer VariantGetBuffer(Variant* ptr)
{
    VectorBuffer ret(ptr->GetBuffer());
    return ret;
}

static bool VariantEqualsBuffer(const VectorBuffer& buffer, Variant* ptr)
{
    return (*ptr) == buffer.GetBuffer();
}

static FileSystem* GetFileSystem()
{
    return GetScriptContext()->GetSubsystem<FileSystem>();
}

static CScriptArray* FileSystemScanDir(const String& pathName, const String& filter, unsigned flags, bool recursive, FileSystem* ptr)
{
    std::vector<String> result;
    ptr->ScanDir(result, pathName, filter, flags, recursive);
    return VectorToArray<String>(result, "Array<String>");
}

static int FileSystemSystemRun(const String& fileName, CScriptArray* srcArguments, FileSystem* ptr)
{
    if (!srcArguments)
        return -1;
    
    unsigned numArguments = srcArguments->GetSize();
    std::vector<String> destArguments(numArguments);
    for (unsigned i = 0; i < numArguments; ++i)
        destArguments[i] = *(static_cast<String*>(srcArguments->At(i)));
    
    return ptr->SystemRun(fileName, destArguments);
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
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(const String&in, FileMode)", asFUNCTION(ConstructFileAndOpen), asCALL_CDECL);
    engine->RegisterObjectMethod("File", "bool Open(const String&in, FileMode)", asMETHODPR(File, Open, (const String&, FileMode), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "void Close()", asMETHOD(File, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "FileMode get_mode() const", asMETHOD(File, GetMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_open()", asMETHOD(File, IsOpen), asCALL_THISCALL);
    RegisterSerializer<File>(engine, "File");
    RegisterDeserializer<File>(engine, "File");
    
    engine->RegisterObjectType("VectorBuffer", sizeof(VectorBuffer), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", asFUNCTION(ConstructVectorBufferCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer@+, uint)", asFUNCTION(ConstructVectorBufferFromStream), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "VectorBuffer &opAssign(const VectorBuffer&in)", asMETHOD(VectorBuffer, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void SetData(Deserializer@+, uint)", asFUNCTION(VectorBufferSetData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "void Clear()", asMETHOD(VectorBuffer, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void Resize(uint)", asMETHOD(VectorBuffer, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint8 &opIndex(uint)", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "const uint8 &opIndex(uint) const", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    RegisterSerializer<VectorBuffer>(engine, "VectorBuffer");
    RegisterDeserializer<VectorBuffer>(engine, "VectorBuffer");
    
    // Register VectorBuffer conversions to Variant
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer&in)", asFUNCTION(ConstructVariantBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetBuffer() const", asFUNCTION(VariantGetBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VectorBuffer&in) const", asFUNCTION(VariantEqualsBuffer), asCALL_CDECL_OBJLAST);
}

void RegisterFileSystem(asIScriptEngine* engine)
{
    RegisterObject<FileSystem>(engine, "FileSystem");
    engine->RegisterObjectMethod("FileSystem", "bool FileExists(const String&in)", asMETHOD(FileSystem, FileExists), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool DirExists(const String&in)", asMETHOD(FileSystem, DirExists), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "Array<String>@ ScanDir(const String&in, const String&in, uint, bool)", asFUNCTION(FileSystemScanDir), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSystem", "bool CreateDir(const String&in)", asMETHOD(FileSystem, CreateDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int SystemCommand(const String&in)", asMETHOD(FileSystem, SystemCommand), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int SystemRun(const String&in, Array<String>@+)", asFUNCTION(FileSystemSystemRun), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSystem", "bool SystemOpen(const String&in, const String&in)", asMETHOD(FileSystem, SystemOpen), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Copy(const String&in, const String&in)", asMETHOD(FileSystem, Copy), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Rename(const String&in, const String&in)", asMETHOD(FileSystem, Rename), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool Delete(const String&in)", asMETHOD(FileSystem, Delete), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_currentDir()", asMETHOD(FileSystem, GetCurrentDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_currentDir(const String&in)", asMETHOD(FileSystem, SetCurrentDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_programDir()", asMETHOD(FileSystem, GetProgramDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_userDocumentsDir()", asMETHOD(FileSystem, GetUserDocumentsDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_systemFontDir()", asMETHOD(FileSystem, GetSystemFontDir), asCALL_THISCALL);
    engine->RegisterGlobalFunction("FileSystem@+ get_fileSystem()", asFUNCTION(GetFileSystem), asCALL_CDECL);
    
    engine->RegisterGlobalFunction("String GetPath(const String&in)", asFUNCTION(GetPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetFileName(const String&in)", asFUNCTION(GetFileName), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetExtension(const String&in)", asFUNCTION(GetExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetFileNameAndExtension(const String&in)", asFUNCTION(GetFileNameAndExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("String AddTrailingSlash(const String&in)", asFUNCTION(AddTrailingSlash), asCALL_CDECL);
    engine->RegisterGlobalFunction("String RemoveTrailingSlash(const String&in)", asFUNCTION(RemoveTrailingSlash), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetParentPath(const String&in)", asFUNCTION(GetParentPath), asCALL_CDECL);
}

static PackageFile* ConstructPackageFile()
{
    return new PackageFile(GetScriptContext());
}

static PackageFile* ConstructAndOpenPackageFile(const String& fileName)
{
    return new PackageFile(GetScriptContext(), fileName);
}

static void RegisterPackageFile(asIScriptEngine* engine)
{
    RegisterObject<PackageFile>(engine, "PackageFile");
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f()", asFUNCTION(ConstructPackageFile), asCALL_CDECL);
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const String&in)", asFUNCTION(ConstructAndOpenPackageFile), asCALL_CDECL);
    engine->RegisterObjectMethod("PackageFile", "bool Open(const String&in) const", asMETHOD(PackageFile, Open), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool Exists(const String&in) const", asMETHOD(PackageFile, Exists), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_name() const", asMETHOD(PackageFile, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_numFiles() const", asMETHOD(PackageFile, GetNumFiles), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalSize() const", asMETHOD(PackageFile, GetTotalSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_checksum() const", asMETHOD(PackageFile, GetChecksum), asCALL_THISCALL);
}

void RegisterIOAPI(asIScriptEngine* engine)
{
    RegisterLog(engine);
    RegisterSerialization(engine);
    RegisterFileSystem(engine);
    RegisterPackageFile(engine);
}
