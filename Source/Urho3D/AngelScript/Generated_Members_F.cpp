// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit File::File(Context* context) | File: ../IO/File.h
static File* File_File_Context()
{
    return new File(GetScriptContext());
}

// File::File(Context* context, const String& fileName, FileMode mode=FILE_READ) | File: ../IO/File.h
static File* File_File_Context_String_FileMode(const String &fileName, FileMode mode=FILE_READ)
{
    return new File(GetScriptContext(), fileName, mode);
}

// File::File(Context* context, PackageFile* package, const String& fileName) | File: ../IO/File.h
static File* File_File_Context_PackageFile_String(PackageFile *package, const String &fileName)
{
    return new File(GetScriptContext(), package, fileName);
}

// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* File_ReadStringVector_void(File* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void File_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(File* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
static bool File_WriteStringVector_StringVector(File* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->WriteStringVector(value);
    return result;
}

// explicit FileSelector::FileSelector(Context* context) | File: ../UI/FileSelector.h
static FileSelector* FileSelector_FileSelector_Context()
{
    return new FileSelector(GetScriptContext());
}

// void FileSelector::SetFilters(const Vector<String>& filters, unsigned defaultIndex) | File: ../UI/FileSelector.h
static void FileSelector_SetFilters_VectorString_unsigned(FileSelector* ptr, CScriptArray* filters_conv, unsigned defaultIndex)
{
    Vector<String> filters = ArrayToVector<String>(filters_conv);
    ptr->SetFilters(filters, defaultIndex);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void FileSelector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(FileSelector* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit FileSystem::FileSystem(Context* context) | File: ../IO/FileSystem.h
static FileSystem* FileSystem_FileSystem_Context()
{
    return new FileSystem(GetScriptContext());
}

// int FileSystem::SystemRun(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
static int FileSystem_SystemRun_String_VectorString(FileSystem* ptr, const String& fileName, CScriptArray* arguments_conv)
{
    Vector<String> arguments = ArrayToVector<String>(arguments_conv);
    int result = ptr->SystemRun(fileName, arguments);
    return result;
}

// unsigned FileSystem::SystemRunAsync(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
static unsigned FileSystem_SystemRunAsync_String_VectorString(FileSystem* ptr, const String& fileName, CScriptArray* arguments_conv)
{
    Vector<String> arguments = ArrayToVector<String>(arguments_conv);
    unsigned result = ptr->SystemRunAsync(fileName, arguments);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void FileSystem_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(FileSystem* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit FileWatcher::FileWatcher(Context* context) | File: ../IO/FileWatcher.h
static FileWatcher* FileWatcher_FileWatcher_Context()
{
    return new FileWatcher(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void FileWatcher_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(FileWatcher* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Font::Font(Context* context) | File: ../UI/Font.h
static Font* Font_Font_Context()
{
    return new Font(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Font_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Font* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
static CScriptArray* FontFace_GetTextures_void(FontFace* ptr)
{
    const Vector<SharedPtr<Texture2D>>& result = ptr->GetTextures();
    return VectorToHandleArray(result, "Array<Texture2D@>");
}

// explicit FontFaceBitmap::FontFaceBitmap(Font* font) | File: ../UI/FontFaceBitmap.h
static FontFaceBitmap* FontFaceBitmap_FontFaceBitmap_Font(Font *font)
{
    return new FontFaceBitmap(font);
}

// const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
static CScriptArray* FontFaceBitmap_GetTextures_void(FontFaceBitmap* ptr)
{
    const Vector<SharedPtr<Texture2D>>& result = ptr->GetTextures();
    return VectorToHandleArray(result, "Array<Texture2D@>");
}

// explicit FontFaceFreeType::FontFaceFreeType(Font* font) | File: ../UI/FontFaceFreeType.h
static FontFaceFreeType* FontFaceFreeType_FontFaceFreeType_Font(Font *font)
{
    return new FontFaceFreeType(font);
}

// const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
static CScriptArray* FontFaceFreeType_GetTextures_void(FontFaceFreeType* ptr)
{
    const Vector<SharedPtr<Texture2D>>& result = ptr->GetTextures();
    return VectorToHandleArray(result, "Array<Texture2D@>");
}

// Frustum::Frustum(const Frustum& frustum) noexcept | File: ../Math/Frustum.h
static void Frustum_Frustum_Frustum(Frustum* ptr, const Frustum &frustum)
{
    new(ptr) Frustum(frustum);
}

// FocusParameters::FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView) | File: ../Graphics/Light.h
static void FocusParameters_FocusParameters_bool_bool_bool_float_float(FocusParameters* ptr, bool focus, bool nonUniform, bool autoSize, float quantize, float minView)
{
    new(ptr) FocusParameters(focus, nonUniform, autoSize, quantize, minView);
}

void ASRegisterGenerated_Members_F(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", asMETHODPR(File, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void File::Close() | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "void Close()", asMETHODPR(File, Close, (), void), asCALL_THISCALL);
    // explicit File::File(Context* context) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f()", asFUNCTION(File_File_Context), asCALL_CDECL);
    // File::File(Context* context, const String& fileName, FileMode mode=FILE_READ) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(const String&in, FileMode = FILE_READ)", asFUNCTION(File_File_Context_String_FileMode), asCALL_CDECL);
    // File::File(Context* context, PackageFile* package, const String& fileName) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(PackageFile@+, const String&in)", asFUNCTION(File_File_Context_PackageFile_String), asCALL_CDECL);
    // void File::Flush() | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "void Flush()", asMETHODPR(File, Flush, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool GetBlockEvents() const", asMETHODPR(File, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const String& GetCategory() const", asMETHODPR(File, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_category() const", asMETHODPR(File, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned File::GetChecksum() override | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "uint GetChecksum()", asMETHODPR(File, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_checksum()", asMETHODPR(File, GetChecksum, (), unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "VariantMap& GetEventDataMap() const", asMETHODPR(File, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "Object@+ GetEventSender() const", asMETHODPR(File, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(File, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "const Variant& get_globalVar(StringHash) const", asMETHODPR(File, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const VariantMap& GetGlobalVars() const", asMETHODPR(File, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "const VariantMap& get_globalVars() const", asMETHODPR(File, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* File::GetHandle() const | File: ../IO/File.h
    // Error: type "void*" can not automatically bind
    // FileMode File::GetMode() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "FileMode GetMode() const", asMETHODPR(File, GetMode, () const, FileMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "FileMode get_mode() const", asMETHODPR(File, GetMode, () const, FileMode), asCALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("File", "const String& GetName() const", asMETHODPR(File, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_name() const", asMETHODPR(File, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint GetPosition() const", asMETHODPR(File, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_position() const", asMETHODPR(File, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint GetSize() const", asMETHODPR(File, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_size() const", asMETHODPR(File, GetSize, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(File, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "StringHash GetType() const", asMETHODPR(File, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "StringHash get_type() const", asMETHODPR(File, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const String& GetTypeName() const", asMETHODPR(File, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_typeName() const", asMETHODPR(File, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasEventHandlers() const", asMETHODPR(File, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(File, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(File, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "bool IsEof() const", asMETHODPR(File, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_eof() const", asMETHODPR(File, IsEof, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool IsInstanceOf(StringHash) const", asMETHODPR(File, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool File::IsOpen() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool IsOpen() const", asMETHODPR(File, IsOpen, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_open() const", asMETHODPR(File, IsOpen, () const, bool), asCALL_THISCALL);
    // bool File::IsPackaged() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool IsPackaged() const", asMETHODPR(File, IsPackaged, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_packaged() const", asMETHODPR(File, IsPackaged, () const, bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(File, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // bool File::Open(const String& fileName, FileMode mode=FILE_READ) | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool Open(const String&in, FileMode = FILE_READ)", asMETHODPR(File, Open, (const String&, FileMode), bool), asCALL_THISCALL);
    // bool File::Open(PackageFile* package, const String& fileName) | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool Open(PackageFile@+, const String&in)", asMETHODPR(File, Open, (PackageFile*, const String&), bool), asCALL_THISCALL);
    // unsigned File::Read(void* dest, unsigned size) override | File: ../IO/File.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "bool ReadBool()", asMETHODPR(File, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "BoundingBox ReadBoundingBox()", asMETHODPR(File, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int8 ReadByte()", asMETHODPR(File, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Color ReadColor()", asMETHODPR(File, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "double ReadDouble()", asMETHODPR(File, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadFileID()", asMETHODPR(File, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "float ReadFloat()", asMETHODPR(File, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int ReadInt()", asMETHODPR(File, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int64 ReadInt64()", asMETHODPR(File, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntRect ReadIntRect()", asMETHODPR(File, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntVector2 ReadIntVector2()", asMETHODPR(File, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntVector3 ReadIntVector3()", asMETHODPR(File, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadLine()", asMETHODPR(File, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix3 ReadMatrix3()", asMETHODPR(File, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(File, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix4 ReadMatrix4()", asMETHODPR(File, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadNetID()", asMETHODPR(File, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Quaternion ReadPackedQuaternion()", asMETHODPR(File, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector3 ReadPackedVector3(float)", asMETHODPR(File, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Quaternion ReadQuaternion()", asMETHODPR(File, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Rect ReadRect()", asMETHODPR(File, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "ResourceRef ReadResourceRef()", asMETHODPR(File, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "ResourceRefList ReadResourceRefList()", asMETHODPR(File, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int16 ReadShort()", asMETHODPR(File, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadString()", asMETHODPR(File, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "StringHash ReadStringHash()", asMETHODPR(File, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Array<String>@ ReadStringVector()", asFUNCTION(File_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint8 ReadUByte()", asMETHODPR(File, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadUInt()", asMETHODPR(File, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint64 ReadUInt64()", asMETHODPR(File, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint16 ReadUShort()", asMETHODPR(File, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Variant ReadVariant()", asMETHODPR(File, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Variant ReadVariant(VariantType)", asMETHODPR(File, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "VariantMap ReadVariantMap()", asMETHODPR(File, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector2 ReadVector2()", asMETHODPR(File, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector3 ReadVector3()", asMETHODPR(File, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector4 ReadVector4()", asMETHODPR(File, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadVLE()", asMETHODPR(File, ReadVLE, (), unsigned), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("File", "int Refs() const", asMETHODPR(File, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "int get_refs() const", asMETHODPR(File, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", asMETHODPR(File, ReleaseRef, (), void), asCALL_THISCALL);
    // unsigned File::Seek(unsigned position) override | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "uint Seek(uint)", asMETHODPR(File, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint SeekRelative(int)", asMETHODPR(File, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SendEvent(StringHash)", asMETHODPR(File, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(File, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SetBlockEvents(bool)", asMETHODPR(File, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(File, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(File, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("File", "void SetName(const String&in)", asMETHODPR(File, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "void set_name(const String&in)", asMETHODPR(File, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint Tell() const", asMETHODPR(File, Tell, () const, unsigned), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromAllEvents()", asMETHODPR(File, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(File_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(File, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(File, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(File, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("File", "int WeakRefs() const", asMETHODPR(File, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "int get_weakRefs() const", asMETHODPR(File, WeakRefs, () const, int), asCALL_THISCALL);
    // unsigned File::Write(const void* data, unsigned size) override | File: ../IO/File.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteBool(bool)", asMETHODPR(File, WriteBool, (bool), bool), asCALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(File, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteByte(int8)", asMETHODPR(File, WriteByte, (signed char), bool), asCALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteColor(const Color&in)", asMETHODPR(File, WriteColor, (const Color&), bool), asCALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteDouble(double)", asMETHODPR(File, WriteDouble, (double), bool), asCALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteFileID(const String&in)", asMETHODPR(File, WriteFileID, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteFloat(float)", asMETHODPR(File, WriteFloat, (float), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteInt(int)", asMETHODPR(File, WriteInt, (int), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteInt64(int64)", asMETHODPR(File, WriteInt64, (long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntRect(const IntRect&in)", asMETHODPR(File, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(File, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntVector3(const IntVector3&in)", asMETHODPR(File, WriteIntVector3, (const IntVector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteLine(const String&in)", asMETHODPR(File, WriteLine, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(File, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(File, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(File, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteNetID(uint)", asMETHODPR(File, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(File, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(File, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(File, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteRect(const Rect&in)", asMETHODPR(File, WriteRect, (const Rect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteResourceRef(const ResourceRef&in)", asMETHODPR(File, WriteResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteResourceRefList(const ResourceRefList&in)", asMETHODPR(File, WriteResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteShort(int16)", asMETHODPR(File, WriteShort, (short), bool), asCALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteString(const String&in)", asMETHODPR(File, WriteString, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteStringHash(const StringHash&in)", asMETHODPR(File, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteStringVector(Array<String>@+)", asFUNCTION(File_WriteStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUByte(uint8)", asMETHODPR(File, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUInt(uint)", asMETHODPR(File, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUInt64(uint64)", asMETHODPR(File, WriteUInt64, (unsigned long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUShort(uint16)", asMETHODPR(File, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariant(const Variant&in)", asMETHODPR(File, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariantData(const Variant&in)", asMETHODPR(File, WriteVariantData, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(File, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector2(const Vector2&in)", asMETHODPR(File, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector3(const Vector3&in)", asMETHODPR(File, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector4(const Vector4&in)", asMETHODPR(File, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVLE(uint)", asMETHODPR(File, WriteVLE, (unsigned), bool), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(File, "File")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(File, "File")
#endif
#ifdef REGISTER_MANUAL_PART_AbstractFile
    REGISTER_MANUAL_PART_AbstractFile(File, "File")
#endif
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(File, "File")
#endif
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(File, "File")
#endif
#ifdef REGISTER_MANUAL_PART_File
    REGISTER_MANUAL_PART_File(File, "File")
#endif
    RegisterSubclass<Object, File>(engine, "Object", "File");
    RegisterSubclass<RefCounted, File>(engine, "RefCounted", "File");
    RegisterSubclass<AbstractFile, File>(engine, "AbstractFile", "File");
    RegisterSubclass<Deserializer, File>(engine, "Deserializer", "File");
    RegisterSubclass<Serializer, File>(engine, "Serializer", "File");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_ADDREF, "void f()", asMETHODPR(FileSelector, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit FileSelector::FileSelector(Context* context) | File: ../UI/FileSelector.h
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_FACTORY, "FileSelector@+ f()", asFUNCTION(FileSelector_FileSelector_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool GetBlockEvents() const", asMETHODPR(FileSelector, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // Button* FileSelector::GetCancelButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetCancelButton() const", asMETHODPR(FileSelector, GetCancelButton, () const, Button*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_cancelButton() const", asMETHODPR(FileSelector, GetCancelButton, () const, Button*), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetCategory() const", asMETHODPR(FileSelector, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_category() const", asMETHODPR(FileSelector, GetCategory, () const, const String&), asCALL_THISCALL);
    // Button* FileSelector::GetCloseButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetCloseButton() const", asMETHODPR(FileSelector, GetCloseButton, () const, Button*), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* FileSelector::GetDefaultStyle() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ GetDefaultStyle() const", asMETHODPR(FileSelector, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ get_defaultStyle() const", asMETHODPR(FileSelector, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    // bool FileSelector::GetDirectoryMode() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "bool GetDirectoryMode() const", asMETHODPR(FileSelector, GetDirectoryMode, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "bool get_directoryMode() const", asMETHODPR(FileSelector, GetDirectoryMode, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "VariantMap& GetEventDataMap() const", asMETHODPR(FileSelector, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "Object@+ GetEventSender() const", asMETHODPR(FileSelector, GetEventSender, () const, Object*), asCALL_THISCALL);
    // ListView* FileSelector::GetFileList() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "ListView@+ GetFileList() const", asMETHODPR(FileSelector, GetFileList, () const, ListView*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "ListView@+ get_fileList() const", asMETHODPR(FileSelector, GetFileList, () const, ListView*), asCALL_THISCALL);
    // const String& FileSelector::GetFileName() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetFileName() const", asMETHODPR(FileSelector, GetFileName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_fileName() const", asMETHODPR(FileSelector, GetFileName, () const, const String&), asCALL_THISCALL);
    // LineEdit* FileSelector::GetFileNameEdit() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ GetFileNameEdit() const", asMETHODPR(FileSelector, GetFileNameEdit, () const, LineEdit*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_fileNameEdit() const", asMETHODPR(FileSelector, GetFileNameEdit, () const, LineEdit*), asCALL_THISCALL);
    // const String& FileSelector::GetFilter() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetFilter() const", asMETHODPR(FileSelector, GetFilter, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_filter() const", asMETHODPR(FileSelector, GetFilter, () const, const String&), asCALL_THISCALL);
    // unsigned FileSelector::GetFilterIndex() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "uint GetFilterIndex() const", asMETHODPR(FileSelector, GetFilterIndex, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "uint get_filterIndex() const", asMETHODPR(FileSelector, GetFilterIndex, () const, unsigned), asCALL_THISCALL);
    // DropDownList* FileSelector::GetFilterList() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ GetFilterList() const", asMETHODPR(FileSelector, GetFilterList, () const, DropDownList*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ get_filterList() const", asMETHODPR(FileSelector, GetFilterList, () const, DropDownList*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(FileSelector, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const Variant& get_globalVar(StringHash) const", asMETHODPR(FileSelector, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const VariantMap& GetGlobalVars() const", asMETHODPR(FileSelector, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const VariantMap& get_globalVars() const", asMETHODPR(FileSelector, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Button* FileSelector::GetOKButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetOKButton() const", asMETHODPR(FileSelector, GetOKButton, () const, Button*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_okButton() const", asMETHODPR(FileSelector, GetOKButton, () const, Button*), asCALL_THISCALL);
    // const String& FileSelector::GetPath() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetPath() const", asMETHODPR(FileSelector, GetPath, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_path() const", asMETHODPR(FileSelector, GetPath, () const, const String&), asCALL_THISCALL);
    // LineEdit* FileSelector::GetPathEdit() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ GetPathEdit() const", asMETHODPR(FileSelector, GetPathEdit, () const, LineEdit*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_pathEdit() const", asMETHODPR(FileSelector, GetPathEdit, () const, LineEdit*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(FileSelector, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& FileSelector::GetTitle() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetTitle() const", asMETHODPR(FileSelector, GetTitle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_title() const", asMETHODPR(FileSelector, GetTitle, () const, const String&), asCALL_THISCALL);
    // Text* FileSelector::GetTitleText() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Text@+ GetTitleText() const", asMETHODPR(FileSelector, GetTitleText, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Text@+ get_titleText() const", asMETHODPR(FileSelector, GetTitleText, () const, Text*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "StringHash GetType() const", asMETHODPR(FileSelector, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "StringHash get_type() const", asMETHODPR(FileSelector, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetTypeName() const", asMETHODPR(FileSelector, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_typeName() const", asMETHODPR(FileSelector, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Window* FileSelector::GetWindow() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Window@+ GetWindow() const", asMETHODPR(FileSelector, GetWindow, () const, Window*), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Window@+ get_window() const", asMETHODPR(FileSelector, GetWindow, () const, Window*), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasEventHandlers() const", asMETHODPR(FileSelector, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(FileSelector, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(FileSelector, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool IsInstanceOf(StringHash) const", asMETHODPR(FileSelector, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(FileSelector, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSelector", "int Refs() const", asMETHODPR(FileSelector, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "int get_refs() const", asMETHODPR(FileSelector, Refs, () const, int), asCALL_THISCALL);
    // static void FileSelector::RegisterObject(Context* context) | File: ../UI/FileSelector.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_RELEASE, "void f()", asMETHODPR(FileSelector, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SendEvent(StringHash)", asMETHODPR(FileSelector, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(FileSelector, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SetBlockEvents(bool)", asMETHODPR(FileSelector, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void FileSelector::SetButtonTexts(const String& okText, const String& cancelText) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetButtonTexts(const String&in, const String&in)", asMETHODPR(FileSelector, SetButtonTexts, (const String&, const String&), void), asCALL_THISCALL);
    // void FileSelector::SetDefaultStyle(XMLFile* style) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(FileSelector, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_defaultStyle(XMLFile@+)", asMETHODPR(FileSelector, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void FileSelector::SetDirectoryMode(bool enable) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetDirectoryMode(bool)", asMETHODPR(FileSelector, SetDirectoryMode, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_directoryMode(bool)", asMETHODPR(FileSelector, SetDirectoryMode, (bool), void), asCALL_THISCALL);
    // void FileSelector::SetFileName(const String& fileName) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetFileName(const String&in)", asMETHODPR(FileSelector, SetFileName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_fileName(const String&in)", asMETHODPR(FileSelector, SetFileName, (const String&), void), asCALL_THISCALL);
    // void FileSelector::SetFilters(const Vector<String>& filters, unsigned defaultIndex) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetFilters(Array<String>@+, uint)", asFUNCTION(FileSelector_SetFilters_VectorString_unsigned), asCALL_CDECL_OBJFIRST);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(FileSelector, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(FileSelector, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void FileSelector::SetPath(const String& path) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetPath(const String&in)", asMETHODPR(FileSelector, SetPath, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_path(const String&in)", asMETHODPR(FileSelector, SetPath, (const String&), void), asCALL_THISCALL);
    // void FileSelector::SetTitle(const String& text) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetTitle(const String&in)", asMETHODPR(FileSelector, SetTitle, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_title(const String&in)", asMETHODPR(FileSelector, SetTitle, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromAllEvents()", asMETHODPR(FileSelector, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(FileSelector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(FileSelector, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(FileSelector, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(FileSelector, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void FileSelector::UpdateElements() | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void UpdateElements()", asMETHODPR(FileSelector, UpdateElements, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSelector", "int WeakRefs() const", asMETHODPR(FileSelector, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "int get_weakRefs() const", asMETHODPR(FileSelector, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(FileSelector, "FileSelector")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FileSelector, "FileSelector")
#endif
#ifdef REGISTER_MANUAL_PART_FileSelector
    REGISTER_MANUAL_PART_FileSelector(FileSelector, "FileSelector")
#endif
    RegisterSubclass<Object, FileSelector>(engine, "Object", "FileSelector");
    RegisterSubclass<RefCounted, FileSelector>(engine, "RefCounted", "FileSelector");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_ADDREF, "void f()", asMETHODPR(FileSystem, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool FileSystem::CheckAccess(const String& pathName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool CheckAccess(const String&in) const", asMETHODPR(FileSystem, CheckAccess, (const String&) const, bool), asCALL_THISCALL);
    // bool FileSystem::Copy(const String& srcFileName, const String& destFileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Copy(const String&in, const String&in)", asMETHODPR(FileSystem, Copy, (const String&, const String&), bool), asCALL_THISCALL);
    // bool FileSystem::CreateDir(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool CreateDir(const String&in)", asMETHODPR(FileSystem, CreateDir, (const String&), bool), asCALL_THISCALL);
    // bool FileSystem::Delete(const String& fileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Delete(const String&in)", asMETHODPR(FileSystem, Delete, (const String&), bool), asCALL_THISCALL);
    // bool FileSystem::DirExists(const String& pathName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool DirExists(const String&in) const", asMETHODPR(FileSystem, DirExists, (const String&) const, bool), asCALL_THISCALL);
    // bool FileSystem::FileExists(const String& fileName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool FileExists(const String&in) const", asMETHODPR(FileSystem, FileExists, (const String&) const, bool), asCALL_THISCALL);
    // explicit FileSystem::FileSystem(Context* context) | File: ../IO/FileSystem.h
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_FACTORY, "FileSystem@+ f()", asFUNCTION(FileSystem_FileSystem_Context), asCALL_CDECL);
    // String FileSystem::GetAppPreferencesDir(const String& org, const String& app) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetAppPreferencesDir(const String&in, const String&in) const", asMETHODPR(FileSystem, GetAppPreferencesDir, (const String&, const String&) const, String), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool GetBlockEvents() const", asMETHODPR(FileSystem, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const String& GetCategory() const", asMETHODPR(FileSystem, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const String& get_category() const", asMETHODPR(FileSystem, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // String FileSystem::GetCurrentDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetCurrentDir() const", asMETHODPR(FileSystem, GetCurrentDir, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_currentDir() const", asMETHODPR(FileSystem, GetCurrentDir, () const, String), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "VariantMap& GetEventDataMap() const", asMETHODPR(FileSystem, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "Object@+ GetEventSender() const", asMETHODPR(FileSystem, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool FileSystem::GetExecuteConsoleCommands() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool GetExecuteConsoleCommands() const", asMETHODPR(FileSystem, GetExecuteConsoleCommands, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool get_executeConsoleCommands() const", asMETHODPR(FileSystem, GetExecuteConsoleCommands, () const, bool), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(FileSystem, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const Variant& get_globalVar(StringHash) const", asMETHODPR(FileSystem, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const VariantMap& GetGlobalVars() const", asMETHODPR(FileSystem, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const VariantMap& get_globalVars() const", asMETHODPR(FileSystem, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned FileSystem::GetLastModifiedTime(const String& fileName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint GetLastModifiedTime(const String&in) const", asMETHODPR(FileSystem, GetLastModifiedTime, (const String&) const, unsigned), asCALL_THISCALL);
    // String FileSystem::GetProgramDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetProgramDir() const", asMETHODPR(FileSystem, GetProgramDir, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_programDir() const", asMETHODPR(FileSystem, GetProgramDir, () const, String), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(FileSystem, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // String FileSystem::GetTemporaryDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetTemporaryDir() const", asMETHODPR(FileSystem, GetTemporaryDir, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_temporaryDir() const", asMETHODPR(FileSystem, GetTemporaryDir, () const, String), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "StringHash GetType() const", asMETHODPR(FileSystem, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "StringHash get_type() const", asMETHODPR(FileSystem, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const String& GetTypeName() const", asMETHODPR(FileSystem, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const String& get_typeName() const", asMETHODPR(FileSystem, GetTypeName, () const, const String&), asCALL_THISCALL);
    // String FileSystem::GetUserDocumentsDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetUserDocumentsDir() const", asMETHODPR(FileSystem, GetUserDocumentsDir, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_userDocumentsDir() const", asMETHODPR(FileSystem, GetUserDocumentsDir, () const, String), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasEventHandlers() const", asMETHODPR(FileSystem, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool FileSystem::HasRegisteredPaths() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool HasRegisteredPaths() const", asMETHODPR(FileSystem, HasRegisteredPaths, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(FileSystem, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(FileSystem, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool IsInstanceOf(StringHash) const", asMETHODPR(FileSystem, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(FileSystem, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSystem", "int Refs() const", asMETHODPR(FileSystem, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int get_refs() const", asMETHODPR(FileSystem, Refs, () const, int), asCALL_THISCALL);
    // void FileSystem::RegisterPath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "void RegisterPath(const String&in)", asMETHODPR(FileSystem, RegisterPath, (const String&), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_RELEASE, "void f()", asMETHODPR(FileSystem, ReleaseRef, (), void), asCALL_THISCALL);
    // bool FileSystem::Rename(const String& srcFileName, const String& destFileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Rename(const String&in, const String&in)", asMETHODPR(FileSystem, Rename, (const String&, const String&), bool), asCALL_THISCALL);
    // void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h
    // Error: type "Vector<String>&" can not automatically bind
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SendEvent(StringHash)", asMETHODPR(FileSystem, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(FileSystem, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SetBlockEvents(bool)", asMETHODPR(FileSystem, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // bool FileSystem::SetCurrentDir(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SetCurrentDir(const String&in)", asMETHODPR(FileSystem, SetCurrentDir, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool set_currentDir(const String&in)", asMETHODPR(FileSystem, SetCurrentDir, (const String&), bool), asCALL_THISCALL);
    // void FileSystem::SetExecuteConsoleCommands(bool enable) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "void SetExecuteConsoleCommands(bool)", asMETHODPR(FileSystem, SetExecuteConsoleCommands, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_executeConsoleCommands(bool)", asMETHODPR(FileSystem, SetExecuteConsoleCommands, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(FileSystem, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(FileSystem, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // bool FileSystem::SetLastModifiedTime(const String& fileName, unsigned newTime) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SetLastModifiedTime(const String&in, uint)", asMETHODPR(FileSystem, SetLastModifiedTime, (const String&, unsigned), bool), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // int FileSystem::SystemCommand(const String& commandLine, bool redirectStdOutToLog=false) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "int SystemCommand(const String&in, bool = false)", asMETHODPR(FileSystem, SystemCommand, (const String&, bool), int), asCALL_THISCALL);
    // unsigned FileSystem::SystemCommandAsync(const String& commandLine) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint SystemCommandAsync(const String&in)", asMETHODPR(FileSystem, SystemCommandAsync, (const String&), unsigned), asCALL_THISCALL);
    // bool FileSystem::SystemOpen(const String& fileName, const String& mode=String::EMPTY) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SystemOpen(const String&in, const String&in = String::EMPTY)", asMETHODPR(FileSystem, SystemOpen, (const String&, const String&), bool), asCALL_THISCALL);
    // int FileSystem::SystemRun(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "int SystemRun(const String&in, Array<String>@+)", asFUNCTION(FileSystem_SystemRun_String_VectorString), asCALL_CDECL_OBJFIRST);
    // unsigned FileSystem::SystemRunAsync(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint SystemRunAsync(const String&in, Array<String>@+)", asFUNCTION(FileSystem_SystemRunAsync_String_VectorString), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromAllEvents()", asMETHODPR(FileSystem, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(FileSystem_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(FileSystem, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(FileSystem, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(FileSystem, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSystem", "int WeakRefs() const", asMETHODPR(FileSystem, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int get_weakRefs() const", asMETHODPR(FileSystem, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(FileSystem, "FileSystem")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FileSystem, "FileSystem")
#endif
#ifdef REGISTER_MANUAL_PART_FileSystem
    REGISTER_MANUAL_PART_FileSystem(FileSystem, "FileSystem")
#endif
    RegisterSubclass<Object, FileSystem>(engine, "Object", "FileSystem");
    RegisterSubclass<RefCounted, FileSystem>(engine, "RefCounted", "FileSystem");

    // void FileWatcher::AddChange(const String& fileName) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void AddChange(const String&in)", asMETHODPR(FileWatcher, AddChange, (const String&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_ADDREF, "void f()", asMETHODPR(FileWatcher, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit FileWatcher::FileWatcher(Context* context) | File: ../IO/FileWatcher.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_FACTORY, "FileWatcher@+ f()", asFUNCTION(FileWatcher_FileWatcher_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool GetBlockEvents() const", asMETHODPR(FileWatcher, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetCategory() const", asMETHODPR(FileWatcher, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const String& get_category() const", asMETHODPR(FileWatcher, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // static ThreadID Thread::GetCurrentThreadID() | File: ../Core/Thread.h
    // Not registered because have @nobind mark
    // float FileWatcher::GetDelay() const | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "float GetDelay() const", asMETHODPR(FileWatcher, GetDelay, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "VariantMap& GetEventDataMap() const", asMETHODPR(FileWatcher, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "Object@+ GetEventSender() const", asMETHODPR(FileWatcher, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(FileWatcher, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const Variant& get_globalVar(StringHash) const", asMETHODPR(FileWatcher, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const VariantMap& GetGlobalVars() const", asMETHODPR(FileWatcher, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const VariantMap& get_globalVars() const", asMETHODPR(FileWatcher, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool FileWatcher::GetNextChange(String& dest) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "bool GetNextChange(String&)", asMETHODPR(FileWatcher, GetNextChange, (String&), bool), asCALL_THISCALL);
    // const String& FileWatcher::GetPath() const | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetPath() const", asMETHODPR(FileWatcher, GetPath, () const, const String&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(FileWatcher, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "StringHash GetType() const", asMETHODPR(FileWatcher, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "StringHash get_type() const", asMETHODPR(FileWatcher, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetTypeName() const", asMETHODPR(FileWatcher, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const String& get_typeName() const", asMETHODPR(FileWatcher, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasEventHandlers() const", asMETHODPR(FileWatcher, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(FileWatcher, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(FileWatcher, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool IsInstanceOf(StringHash) const", asMETHODPR(FileWatcher, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // static bool Thread::IsMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("FileWatcher");
    engine->RegisterGlobalFunction("bool IsMainThread()", asFUNCTIONPR(FileWatcher::IsMainThread, (), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Thread::IsStarted() const | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "bool IsStarted() const", asMETHODPR(FileWatcher, IsStarted, () const, bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(FileWatcher, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileWatcher", "int Refs() const", asMETHODPR(FileWatcher, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "int get_refs() const", asMETHODPR(FileWatcher, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_RELEASE, "void f()", asMETHODPR(FileWatcher, ReleaseRef, (), void), asCALL_THISCALL);
    // bool Thread::Run() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "bool Run()", asMETHODPR(FileWatcher, Run, (), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SendEvent(StringHash)", asMETHODPR(FileWatcher, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(FileWatcher, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SetBlockEvents(bool)", asMETHODPR(FileWatcher, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void FileWatcher::SetDelay(float interval) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void SetDelay(float)", asMETHODPR(FileWatcher, SetDelay, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(FileWatcher, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(FileWatcher, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // static void Thread::SetMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("FileWatcher");
    engine->RegisterGlobalFunction("void SetMainThread()", asFUNCTIONPR(FileWatcher::SetMainThread, (), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Thread::SetPriority(int priority) | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "void SetPriority(int)", asMETHODPR(FileWatcher, SetPriority, (int), void), asCALL_THISCALL);
    // bool FileWatcher::StartWatching(const String& pathName, bool watchSubDirs) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "bool StartWatching(const String&in, bool)", asMETHODPR(FileWatcher, StartWatching, (const String&, bool), bool), asCALL_THISCALL);
    // void Thread::Stop() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "void Stop()", asMETHODPR(FileWatcher, Stop, (), void), asCALL_THISCALL);
    // void FileWatcher::StopWatching() | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void StopWatching()", asMETHODPR(FileWatcher, StopWatching, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void FileWatcher::ThreadFunction() override | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void ThreadFunction()", asMETHODPR(FileWatcher, ThreadFunction, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromAllEvents()", asMETHODPR(FileWatcher, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(FileWatcher_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(FileWatcher, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(FileWatcher, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(FileWatcher, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileWatcher", "int WeakRefs() const", asMETHODPR(FileWatcher, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "int get_weakRefs() const", asMETHODPR(FileWatcher, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(FileWatcher, "FileWatcher")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FileWatcher, "FileWatcher")
#endif
#ifdef REGISTER_MANUAL_PART_Thread
    REGISTER_MANUAL_PART_Thread(FileWatcher, "FileWatcher")
#endif
#ifdef REGISTER_MANUAL_PART_FileWatcher
    REGISTER_MANUAL_PART_FileWatcher(FileWatcher, "FileWatcher")
#endif
    RegisterSubclass<Object, FileWatcher>(engine, "Object", "FileWatcher");
    RegisterSubclass<RefCounted, FileWatcher>(engine, "RefCounted", "FileWatcher");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Font", asBEHAVE_ADDREF, "void f()", asMETHODPR(Font, AddRef, (), void), asCALL_THISCALL);
    // bool Font::BeginLoad(Deserializer& source) override | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool BeginLoad(Deserializer&)", asMETHODPR(Font, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool EndLoad()", asMETHODPR(Font, EndLoad, (), bool), asCALL_THISCALL);
    // explicit Font::Font(Context* context) | File: ../UI/Font.h
    engine->RegisterObjectBehaviour("Font", asBEHAVE_FACTORY, "Font@+ f()", asFUNCTION(Font_Font_Context), asCALL_CDECL);
    // const IntVector2& Font::GetAbsoluteGlyphOffset() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "const IntVector2& GetAbsoluteGlyphOffset() const", asMETHODPR(Font, GetAbsoluteGlyphOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const IntVector2& get_absoluteGlyphOffset() const", asMETHODPR(Font, GetAbsoluteGlyphOffset, () const, const IntVector2&), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Font, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool GetBlockEvents() const", asMETHODPR(Font, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const String& GetCategory() const", asMETHODPR(Font, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_category() const", asMETHODPR(Font, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "VariantMap& GetEventDataMap() const", asMETHODPR(Font, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "Object@+ GetEventSender() const", asMETHODPR(Font, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FontFace* Font::GetFace(float pointSize) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "FontFace@+ GetFace(float)", asMETHODPR(Font, GetFace, (float), FontFace*), asCALL_THISCALL);
    // FontType Font::GetFontType() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "FontType GetFontType() const", asMETHODPR(Font, GetFontType, () const, FontType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "FontType get_fontType() const", asMETHODPR(Font, GetFontType, () const, FontType), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Font, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Font, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const VariantMap& GetGlobalVars() const", asMETHODPR(Font, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const VariantMap& get_globalVars() const", asMETHODPR(Font, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "uint GetMemoryUse() const", asMETHODPR(Font, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "uint get_memoryUse() const", asMETHODPR(Font, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "const String& GetName() const", asMETHODPR(Font, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_name() const", asMETHODPR(Font, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "StringHash GetNameHash() const", asMETHODPR(Font, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // const Vector2& Font::GetScaledGlyphOffset() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "const Vector2& GetScaledGlyphOffset() const", asMETHODPR(Font, GetScaledGlyphOffset, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const Vector2& get_scaledGlyphOffset() const", asMETHODPR(Font, GetScaledGlyphOffset, () const, const Vector2&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Font, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // IntVector2 Font::GetTotalGlyphOffset(float pointSize) const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "IntVector2 GetTotalGlyphOffset(float) const", asMETHODPR(Font, GetTotalGlyphOffset, (float) const, IntVector2), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "StringHash GetType() const", asMETHODPR(Font, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "StringHash get_type() const", asMETHODPR(Font, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const String& GetTypeName() const", asMETHODPR(Font, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_typeName() const", asMETHODPR(Font, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "uint GetUseTimer()", asMETHODPR(Font, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "uint get_useTimer()", asMETHODPR(Font, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasEventHandlers() const", asMETHODPR(Font, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Font, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Font, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool IsInstanceOf(StringHash) const", asMETHODPR(Font, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Font::IsSDFFont() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool IsSDFFont() const", asMETHODPR(Font, IsSDFFont, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool Load(Deserializer&)", asMETHODPR(Font, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool LoadFile(const String&in)", asMETHODPR(Font, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "bool Load(const String&in)", asMETHODPR(Font, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Font, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Font", "int Refs() const", asMETHODPR(Font, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "int get_refs() const", asMETHODPR(Font, Refs, () const, int), asCALL_THISCALL);
    // static void Font::RegisterObject(Context* context) | File: ../UI/Font.h
    // Not registered because have @nobind mark
    // void Font::ReleaseFaces() | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void ReleaseFaces()", asMETHODPR(Font, ReleaseFaces, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Font", asBEHAVE_RELEASE, "void f()", asMETHODPR(Font, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void ResetUseTimer()", asMETHODPR(Font, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool Save(Serializer&) const", asMETHODPR(Font, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool SaveFile(const String&in) const", asMETHODPR(Font, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "bool Save(const String&in) const", asMETHODPR(Font, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs=false, const String& indentation="\t") | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool SaveXML(Serializer&, int, bool = false, const String&in = \"\t\")", asMETHODPR(Font, SaveXML, (Serializer&, int, bool, const String&), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SendEvent(StringHash)", asMETHODPR(Font, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Font, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Font::SetAbsoluteGlyphOffset(const IntVector2& offset) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void SetAbsoluteGlyphOffset(const IntVector2&in)", asMETHODPR(Font, SetAbsoluteGlyphOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_absoluteGlyphOffset(const IntVector2&in)", asMETHODPR(Font, SetAbsoluteGlyphOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Font, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SetBlockEvents(bool)", asMETHODPR(Font, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Font, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Font, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetMemoryUse(uint)", asMETHODPR(Font, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetName(const String&in)", asMETHODPR(Font, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_name(const String&in)", asMETHODPR(Font, SetName, (const String&), void), asCALL_THISCALL);
    // void Font::SetScaledGlyphOffset(const Vector2& offset) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void SetScaledGlyphOffset(const Vector2&in)", asMETHODPR(Font, SetScaledGlyphOffset, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_scaledGlyphOffset(const Vector2&in)", asMETHODPR(Font, SetScaledGlyphOffset, (const Vector2&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromAllEvents()", asMETHODPR(Font, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Font_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Font, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Font, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Font, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Font", "int WeakRefs() const", asMETHODPR(Font, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "int get_weakRefs() const", asMETHODPR(Font, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Font, "Font")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Font, "Font")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Font, "Font")
#endif
#ifdef REGISTER_MANUAL_PART_Font
    REGISTER_MANUAL_PART_Font(Font, "Font")
#endif
    RegisterSubclass<Resource, Font>(engine, "Resource", "Font");
    RegisterSubclass<Object, Font>(engine, "Object", "Font");
    RegisterSubclass<RefCounted, Font>(engine, "RefCounted", "Font");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFace", asBEHAVE_ADDREF, "void f()", asMETHODPR(FontFace, AddRef, (), void), asCALL_THISCALL);
    // virtual const FontGlyph* FontFace::GetGlyph(unsigned c) | File: ../UI/FontFace.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetKerning(uint, uint) const", asMETHODPR(FontFace, GetKerning, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetPointSize() const", asMETHODPR(FontFace, GetPointSize, () const, float), asCALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetRowHeight() const", asMETHODPR(FontFace, GetRowHeight, () const, float), asCALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "Array<Texture2D@>@ GetTextures() const", asFUNCTION(FontFace_GetTextures_void), asCALL_CDECL_OBJFIRST);
    // virtual bool FontFace::HasMutableGlyphs() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "bool HasMutableGlyphs() const", asMETHODPR(FontFace, HasMutableGlyphs, () const, bool), asCALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "bool IsDataLost() const", asMETHODPR(FontFace, IsDataLost, () const, bool), asCALL_THISCALL);
    // virtual bool FontFace::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize)=0 | File: ../UI/FontFace.h
    // Error: type "const unsigned char*" can not automatically bind
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFace", "int Refs() const", asMETHODPR(FontFace, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFace", "int get_refs() const", asMETHODPR(FontFace, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFace", asBEHAVE_RELEASE, "void f()", asMETHODPR(FontFace, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFace", "int WeakRefs() const", asMETHODPR(FontFace, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFace", "int get_weakRefs() const", asMETHODPR(FontFace, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FontFace, "FontFace")
#endif
#ifdef REGISTER_MANUAL_PART_FontFace
    REGISTER_MANUAL_PART_FontFace(FontFace, "FontFace")
#endif
    RegisterSubclass<RefCounted, FontFace>(engine, "RefCounted", "FontFace");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_ADDREF, "void f()", asMETHODPR(FontFaceBitmap, AddRef, (), void), asCALL_THISCALL);
    // explicit FontFaceBitmap::FontFaceBitmap(Font* font) | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_FACTORY, "FontFaceBitmap@+ f(Font@+)", asFUNCTION(FontFaceBitmap_FontFaceBitmap_Font), asCALL_CDECL);
    // virtual const FontGlyph* FontFace::GetGlyph(unsigned c) | File: ../UI/FontFace.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetKerning(uint, uint) const", asMETHODPR(FontFaceBitmap, GetKerning, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetPointSize() const", asMETHODPR(FontFaceBitmap, GetPointSize, () const, float), asCALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetRowHeight() const", asMETHODPR(FontFaceBitmap, GetRowHeight, () const, float), asCALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "Array<Texture2D@>@ GetTextures() const", asFUNCTION(FontFaceBitmap_GetTextures_void), asCALL_CDECL_OBJFIRST);
    // virtual bool FontFace::HasMutableGlyphs() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool HasMutableGlyphs() const", asMETHODPR(FontFaceBitmap, HasMutableGlyphs, () const, bool), asCALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool IsDataLost() const", asMETHODPR(FontFaceBitmap, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool FontFaceBitmap::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override | File: ../UI/FontFaceBitmap.h
    // Error: type "const unsigned char*" can not automatically bind
    // bool FontFaceBitmap::Load(FontFace* fontFace, bool usedGlyphs) | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool Load(FontFace@+, bool)", asMETHODPR(FontFaceBitmap, Load, (FontFace*, bool), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceBitmap", "int Refs() const", asMETHODPR(FontFaceBitmap, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceBitmap", "int get_refs() const", asMETHODPR(FontFaceBitmap, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_RELEASE, "void f()", asMETHODPR(FontFaceBitmap, ReleaseRef, (), void), asCALL_THISCALL);
    // bool FontFaceBitmap::Save(Serializer& dest, int pointSize, const String& indentation="\t") | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool Save(Serializer&, int, const String&in = \"\t\")", asMETHODPR(FontFaceBitmap, Save, (Serializer&, int, const String&), bool), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceBitmap", "int WeakRefs() const", asMETHODPR(FontFaceBitmap, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceBitmap", "int get_weakRefs() const", asMETHODPR(FontFaceBitmap, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_FontFace
    REGISTER_MANUAL_PART_FontFace(FontFaceBitmap, "FontFaceBitmap")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FontFaceBitmap, "FontFaceBitmap")
#endif
#ifdef REGISTER_MANUAL_PART_FontFaceBitmap
    REGISTER_MANUAL_PART_FontFaceBitmap(FontFaceBitmap, "FontFaceBitmap")
#endif
    RegisterSubclass<FontFace, FontFaceBitmap>(engine, "FontFace", "FontFaceBitmap");
    RegisterSubclass<RefCounted, FontFaceBitmap>(engine, "RefCounted", "FontFaceBitmap");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_ADDREF, "void f()", asMETHODPR(FontFaceFreeType, AddRef, (), void), asCALL_THISCALL);
    // explicit FontFaceFreeType::FontFaceFreeType(Font* font) | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_FACTORY, "FontFaceFreeType@+ f(Font@+)", asFUNCTION(FontFaceFreeType_FontFaceFreeType_Font), asCALL_CDECL);
    // const FontGlyph* FontFaceFreeType::GetGlyph(unsigned c) override | File: ../UI/FontFaceFreeType.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetKerning(uint, uint) const", asMETHODPR(FontFaceFreeType, GetKerning, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetPointSize() const", asMETHODPR(FontFaceFreeType, GetPointSize, () const, float), asCALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetRowHeight() const", asMETHODPR(FontFaceFreeType, GetRowHeight, () const, float), asCALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "Array<Texture2D@>@ GetTextures() const", asFUNCTION(FontFaceFreeType_GetTextures_void), asCALL_CDECL_OBJFIRST);
    // bool FontFaceFreeType::HasMutableGlyphs() const override | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectMethod("FontFaceFreeType", "bool HasMutableGlyphs() const", asMETHODPR(FontFaceFreeType, HasMutableGlyphs, () const, bool), asCALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "bool IsDataLost() const", asMETHODPR(FontFaceFreeType, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool FontFaceFreeType::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override | File: ../UI/FontFaceFreeType.h
    // Error: type "const unsigned char*" can not automatically bind
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceFreeType", "int Refs() const", asMETHODPR(FontFaceFreeType, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceFreeType", "int get_refs() const", asMETHODPR(FontFaceFreeType, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_RELEASE, "void f()", asMETHODPR(FontFaceFreeType, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceFreeType", "int WeakRefs() const", asMETHODPR(FontFaceFreeType, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceFreeType", "int get_weakRefs() const", asMETHODPR(FontFaceFreeType, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_FontFace
    REGISTER_MANUAL_PART_FontFace(FontFaceFreeType, "FontFaceFreeType")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FontFaceFreeType, "FontFaceFreeType")
#endif
#ifdef REGISTER_MANUAL_PART_FontFaceFreeType
    REGISTER_MANUAL_PART_FontFaceFreeType(FontFaceFreeType, "FontFaceFreeType")
#endif
    RegisterSubclass<FontFace, FontFaceFreeType>(engine, "FontFace", "FontFaceFreeType");
    RegisterSubclass<RefCounted, FontFaceFreeType>(engine, "RefCounted", "FontFaceFreeType");

    // Plane Frustum::planes_[NUM_FRUSTUM_PLANES] | File: ../Math/Frustum.h
    // Not registered because array
    // Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h
    // Not registered because array
    // void Frustum::Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(float, float, float, float, float, const Matrix3x4&in = Matrix3x4::IDENTITY)", asMETHODPR(Frustum, Define, (float, float, float, float, float, const Matrix3x4&), void), asCALL_THISCALL);
    // void Frustum::Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const Vector3&in, const Vector3&in, const Matrix3x4&in = Matrix3x4::IDENTITY)", asMETHODPR(Frustum, Define, (const Vector3&, const Vector3&, const Matrix3x4&), void), asCALL_THISCALL);
    // void Frustum::Define(const BoundingBox& box, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const BoundingBox&in, const Matrix3x4&in = Matrix3x4::IDENTITY)", asMETHODPR(Frustum, Define, (const BoundingBox&, const Matrix3x4&), void), asCALL_THISCALL);
    // void Frustum::Define(const Matrix4& projection) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const Matrix4&in)", asMETHODPR(Frustum, Define, (const Matrix4&), void), asCALL_THISCALL);
    // void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void DefineOrtho(float, float, float, float, float, const Matrix3x4&in = Matrix3x4::IDENTITY)", asMETHODPR(Frustum, DefineOrtho, (float, float, float, float, float, const Matrix3x4&), void), asCALL_THISCALL);
    // void Frustum::DefineSplit(const Matrix4& projection, float near, float far) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void DefineSplit(const Matrix4&in, float, float)", asMETHODPR(Frustum, DefineSplit, (const Matrix4&, float, float), void), asCALL_THISCALL);
    // float Frustum::Distance(const Vector3& point) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "float Distance(const Vector3&in) const", asMETHODPR(Frustum, Distance, (const Vector3&) const, float), asCALL_THISCALL);
    // Frustum::Frustum(const Frustum& frustum) noexcept | File: ../Math/Frustum.h
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Frustum_Frustum_Frustum), asCALL_CDECL_OBJFIRST);
    // Intersection Frustum::IsInside(const Vector3& point) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Frustum, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInside(const Sphere& sphere) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Frustum, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInside(const BoundingBox& box) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Frustum, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const Sphere& sphere) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Frustum, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const BoundingBox& box) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Frustum, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // Frustum& Frustum::operator=(const Frustum& rhs) noexcept | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum& opAssign(const Frustum&in)", asMETHODPR(Frustum, operator=, (const Frustum&), Frustum&), asCALL_THISCALL);
    // Rect Frustum::Projected(const Matrix4& projection) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Rect Projected(const Matrix4&in) const", asMETHODPR(Frustum, Projected, (const Matrix4&) const, Rect), asCALL_THISCALL);
    // void Frustum::Transform(const Matrix3& transform) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3&in)", asMETHODPR(Frustum, Transform, (const Matrix3&), void), asCALL_THISCALL);
    // void Frustum::Transform(const Matrix3x4& transform) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3x4&in)", asMETHODPR(Frustum, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3& transform) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3&) const, Frustum), asCALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3x4& transform) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3x4&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3x4&) const, Frustum), asCALL_THISCALL);
    // void Frustum::UpdatePlanes() | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void UpdatePlanes()", asMETHODPR(Frustum, UpdatePlanes, (), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Frustum
    REGISTER_MANUAL_PART_Frustum(Frustum, "Frustum")
#endif

    // bool FileSelectorEntry::directory_ | File: ../UI/FileSelector.h
    engine->RegisterObjectProperty("FileSelectorEntry", "bool directory", offsetof(FileSelectorEntry, directory_));
    // String FileSelectorEntry::name_ | File: ../UI/FileSelector.h
    engine->RegisterObjectProperty("FileSelectorEntry", "String name", offsetof(FileSelectorEntry, name_));
    // FileSelectorEntry& FileSelectorEntry::operator=(const FileSelectorEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FileSelectorEntry>(engine, "FileSelectorEntry");
#ifdef REGISTER_MANUAL_PART_FileSelectorEntry
    REGISTER_MANUAL_PART_FileSelectorEntry(FileSelectorEntry, "FileSelectorEntry")
#endif

    // bool FocusParameters::autoSize_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("FocusParameters", "bool autoSize", offsetof(FocusParameters, autoSize_));
    // bool FocusParameters::focus_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("FocusParameters", "bool focus", offsetof(FocusParameters, focus_));
    // float FocusParameters::minView_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("FocusParameters", "float minView", offsetof(FocusParameters, minView_));
    // bool FocusParameters::nonUniform_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("FocusParameters", "bool nonUniform", offsetof(FocusParameters, nonUniform_));
    // float FocusParameters::quantize_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("FocusParameters", "float quantize", offsetof(FocusParameters, quantize_));
    // FocusParameters::FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView) | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", asFUNCTION(FocusParameters_FocusParameters_bool_bool_bool_float_float), asCALL_CDECL_OBJFIRST);
    // void FocusParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("FocusParameters", "void Validate()", asMETHODPR(FocusParameters, Validate, (), void), asCALL_THISCALL);
    // FocusParameters& FocusParameters::operator=(const FocusParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FocusParameters>(engine, "FocusParameters");
#ifdef REGISTER_MANUAL_PART_FocusParameters
    REGISTER_MANUAL_PART_FocusParameters(FocusParameters, "FocusParameters")
#endif

    // float FontGlyph::advanceX_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "float advanceX", offsetof(FontGlyph, advanceX_));
    // float FontGlyph::height_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "float height", offsetof(FontGlyph, height_));
    // float FontGlyph::offsetX_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "float offsetX", offsetof(FontGlyph, offsetX_));
    // float FontGlyph::offsetY_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "float offsetY", offsetof(FontGlyph, offsetY_));
    // unsigned FontGlyph::page_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "uint page", offsetof(FontGlyph, page_));
    // short FontGlyph::texHeight_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "int16 texHeight", offsetof(FontGlyph, texHeight_));
    // short FontGlyph::texWidth_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "int16 texWidth", offsetof(FontGlyph, texWidth_));
    // bool FontGlyph::used_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "bool used", offsetof(FontGlyph, used_));
    // float FontGlyph::width_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "float width", offsetof(FontGlyph, width_));
    // short FontGlyph::x_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "int16 x", offsetof(FontGlyph, x_));
    // short FontGlyph::y_ | File: ../UI/FontFace.h
    engine->RegisterObjectProperty("FontGlyph", "int16 y", offsetof(FontGlyph, y_));
    // FontGlyph& FontGlyph::operator=(const FontGlyph&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FontGlyph>(engine, "FontGlyph");
#ifdef REGISTER_MANUAL_PART_FontGlyph
    REGISTER_MANUAL_PART_FontGlyph(FontGlyph, "FontGlyph")
#endif

    // Camera* FrameInfo::camera_ | File: ../Graphics/Drawable.h
    // Camera* can not be registered
    // unsigned FrameInfo::frameNumber_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("FrameInfo", "uint frameNumber", offsetof(FrameInfo, frameNumber_));
    // float FrameInfo::timeStep_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("FrameInfo", "float timeStep", offsetof(FrameInfo, timeStep_));
    // IntVector2 FrameInfo::viewSize_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("FrameInfo", "IntVector2 viewSize", offsetof(FrameInfo, viewSize_));
    // FrameInfo& FrameInfo::operator=(const FrameInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<FrameInfo>(engine, "FrameInfo");
#ifdef REGISTER_MANUAL_PART_FrameInfo
    REGISTER_MANUAL_PART_FrameInfo(FrameInfo, "FrameInfo")
#endif

}

}
