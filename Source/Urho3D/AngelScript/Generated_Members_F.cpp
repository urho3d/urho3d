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
    engine->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", AS_METHODPR(File, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void File::Close() | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "void Close()", AS_METHODPR(File, Close, (), void), AS_CALL_THISCALL);
    // explicit File::File(Context* context) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f()", AS_FUNCTION(File_File_Context), AS_CALL_CDECL);
    // File::File(Context* context, const String& fileName, FileMode mode=FILE_READ) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(const String&in, FileMode = FILE_READ)", AS_FUNCTION(File_File_Context_String_FileMode), AS_CALL_CDECL);
    // File::File(Context* context, PackageFile* package, const String& fileName) | File: ../IO/File.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(PackageFile@+, const String&in)", AS_FUNCTION(File_File_Context_PackageFile_String), AS_CALL_CDECL);
    // void File::Flush() | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "void Flush()", AS_METHODPR(File, Flush, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool GetBlockEvents() const", AS_METHODPR(File, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const String& GetCategory() const", AS_METHODPR(File, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_category() const", AS_METHODPR(File, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned File::GetChecksum() override | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "uint GetChecksum()", AS_METHODPR(File, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_checksum()", AS_METHODPR(File, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "VariantMap& GetEventDataMap() const", AS_METHODPR(File, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "Object@+ GetEventSender() const", AS_METHODPR(File, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(File, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(File, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const VariantMap& GetGlobalVars() const", AS_METHODPR(File, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "const VariantMap& get_globalVars() const", AS_METHODPR(File, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* File::GetHandle() const | File: ../IO/File.h
    // Error: type "void*" can not automatically bind
    // FileMode File::GetMode() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "FileMode GetMode() const", AS_METHODPR(File, GetMode, () const, FileMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "FileMode get_mode() const", AS_METHODPR(File, GetMode, () const, FileMode), AS_CALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("File", "const String& GetName() const", AS_METHODPR(File, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_name() const", AS_METHODPR(File, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint GetPosition() const", AS_METHODPR(File, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_position() const", AS_METHODPR(File, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint GetSize() const", AS_METHODPR(File, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint get_size() const", AS_METHODPR(File, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(File, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "StringHash GetType() const", AS_METHODPR(File, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "StringHash get_type() const", AS_METHODPR(File, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "const String& GetTypeName() const", AS_METHODPR(File, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "const String& get_typeName() const", AS_METHODPR(File, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasEventHandlers() const", AS_METHODPR(File, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(File, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(File, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "bool IsEof() const", AS_METHODPR(File, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_eof() const", AS_METHODPR(File, IsEof, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "bool IsInstanceOf(StringHash) const", AS_METHODPR(File, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool File::IsOpen() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool IsOpen() const", AS_METHODPR(File, IsOpen, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_open() const", AS_METHODPR(File, IsOpen, () const, bool), AS_CALL_THISCALL);
    // bool File::IsPackaged() const | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool IsPackaged() const", AS_METHODPR(File, IsPackaged, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "bool get_packaged() const", AS_METHODPR(File, IsPackaged, () const, bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(File, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // bool File::Open(const String& fileName, FileMode mode=FILE_READ) | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool Open(const String&in, FileMode = FILE_READ)", AS_METHODPR(File, Open, (const String&, FileMode), bool), AS_CALL_THISCALL);
    // bool File::Open(PackageFile* package, const String& fileName) | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "bool Open(PackageFile@+, const String&in)", AS_METHODPR(File, Open, (PackageFile*, const String&), bool), AS_CALL_THISCALL);
    // unsigned File::Read(void* dest, unsigned size) override | File: ../IO/File.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "bool ReadBool()", AS_METHODPR(File, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "BoundingBox ReadBoundingBox()", AS_METHODPR(File, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int8 ReadByte()", AS_METHODPR(File, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Color ReadColor()", AS_METHODPR(File, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "double ReadDouble()", AS_METHODPR(File, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadFileID()", AS_METHODPR(File, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "float ReadFloat()", AS_METHODPR(File, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int ReadInt()", AS_METHODPR(File, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int64 ReadInt64()", AS_METHODPR(File, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntRect ReadIntRect()", AS_METHODPR(File, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntVector2 ReadIntVector2()", AS_METHODPR(File, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "IntVector3 ReadIntVector3()", AS_METHODPR(File, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadLine()", AS_METHODPR(File, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix3 ReadMatrix3()", AS_METHODPR(File, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(File, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Matrix4 ReadMatrix4()", AS_METHODPR(File, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadNetID()", AS_METHODPR(File, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Quaternion ReadPackedQuaternion()", AS_METHODPR(File, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector3 ReadPackedVector3(float)", AS_METHODPR(File, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Quaternion ReadQuaternion()", AS_METHODPR(File, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Rect ReadRect()", AS_METHODPR(File, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "ResourceRef ReadResourceRef()", AS_METHODPR(File, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "ResourceRefList ReadResourceRefList()", AS_METHODPR(File, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "int16 ReadShort()", AS_METHODPR(File, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "String ReadString()", AS_METHODPR(File, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "StringHash ReadStringHash()", AS_METHODPR(File, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(File_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint8 ReadUByte()", AS_METHODPR(File, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadUInt()", AS_METHODPR(File, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint64 ReadUInt64()", AS_METHODPR(File, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint16 ReadUShort()", AS_METHODPR(File, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Variant ReadVariant()", AS_METHODPR(File, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Variant ReadVariant(VariantType)", AS_METHODPR(File, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "VariantMap ReadVariantMap()", AS_METHODPR(File, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector2 ReadVector2()", AS_METHODPR(File, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector3 ReadVector3()", AS_METHODPR(File, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "Vector4 ReadVector4()", AS_METHODPR(File, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint ReadVLE()", AS_METHODPR(File, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("File", "int Refs() const", AS_METHODPR(File, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "int get_refs() const", AS_METHODPR(File, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", AS_METHODPR(File, ReleaseRef, (), void), AS_CALL_THISCALL);
    // unsigned File::Seek(unsigned position) override | File: ../IO/File.h
    engine->RegisterObjectMethod("File", "uint Seek(uint)", AS_METHODPR(File, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint SeekRelative(int)", AS_METHODPR(File, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SendEvent(StringHash)", AS_METHODPR(File, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(File, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SetBlockEvents(bool)", AS_METHODPR(File, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(File, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(File, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("File", "void SetName(const String&in)", AS_METHODPR(File, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "void set_name(const String&in)", AS_METHODPR(File, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("File", "uint Tell() const", AS_METHODPR(File, Tell, () const, unsigned), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromAllEvents()", AS_METHODPR(File, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(File_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(File, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(File, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("File", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(File, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("File", "int WeakRefs() const", AS_METHODPR(File, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("File", "int get_weakRefs() const", AS_METHODPR(File, WeakRefs, () const, int), AS_CALL_THISCALL);
    // unsigned File::Write(const void* data, unsigned size) override | File: ../IO/File.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteBool(bool)", AS_METHODPR(File, WriteBool, (bool), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteBoundingBox(const BoundingBox&in)", AS_METHODPR(File, WriteBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteByte(int8)", AS_METHODPR(File, WriteByte, (signed char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteColor(const Color&in)", AS_METHODPR(File, WriteColor, (const Color&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteDouble(double)", AS_METHODPR(File, WriteDouble, (double), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteFileID(const String&in)", AS_METHODPR(File, WriteFileID, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteFloat(float)", AS_METHODPR(File, WriteFloat, (float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteInt(int)", AS_METHODPR(File, WriteInt, (int), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteInt64(int64)", AS_METHODPR(File, WriteInt64, (long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntRect(const IntRect&in)", AS_METHODPR(File, WriteIntRect, (const IntRect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntVector2(const IntVector2&in)", AS_METHODPR(File, WriteIntVector2, (const IntVector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteIntVector3(const IntVector3&in)", AS_METHODPR(File, WriteIntVector3, (const IntVector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteLine(const String&in)", AS_METHODPR(File, WriteLine, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix3(const Matrix3&in)", AS_METHODPR(File, WriteMatrix3, (const Matrix3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix3x4(const Matrix3x4&in)", AS_METHODPR(File, WriteMatrix3x4, (const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteMatrix4(const Matrix4&in)", AS_METHODPR(File, WriteMatrix4, (const Matrix4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteNetID(uint)", AS_METHODPR(File, WriteNetID, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WritePackedQuaternion(const Quaternion&in)", AS_METHODPR(File, WritePackedQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WritePackedVector3(const Vector3&in, float)", AS_METHODPR(File, WritePackedVector3, (const Vector3&, float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteQuaternion(const Quaternion&in)", AS_METHODPR(File, WriteQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteRect(const Rect&in)", AS_METHODPR(File, WriteRect, (const Rect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteResourceRef(const ResourceRef&in)", AS_METHODPR(File, WriteResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteResourceRefList(const ResourceRefList&in)", AS_METHODPR(File, WriteResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteShort(int16)", AS_METHODPR(File, WriteShort, (short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteString(const String&in)", AS_METHODPR(File, WriteString, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteStringHash(const StringHash&in)", AS_METHODPR(File, WriteStringHash, (const StringHash&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(File_WriteStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUByte(uint8)", AS_METHODPR(File, WriteUByte, (unsigned char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUInt(uint)", AS_METHODPR(File, WriteUInt, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUInt64(uint64)", AS_METHODPR(File, WriteUInt64, (unsigned long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteUShort(uint16)", AS_METHODPR(File, WriteUShort, (unsigned short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariant(const Variant&in)", AS_METHODPR(File, WriteVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariantData(const Variant&in)", AS_METHODPR(File, WriteVariantData, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVariantMap(const VariantMap&in)", AS_METHODPR(File, WriteVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector2(const Vector2&in)", AS_METHODPR(File, WriteVector2, (const Vector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector3(const Vector3&in)", AS_METHODPR(File, WriteVector3, (const Vector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVector4(const Vector4&in)", AS_METHODPR(File, WriteVector4, (const Vector4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("File", "bool WriteVLE(uint)", AS_METHODPR(File, WriteVLE, (unsigned), bool), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FileSelector, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit FileSelector::FileSelector(Context* context) | File: ../UI/FileSelector.h
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_FACTORY, "FileSelector@+ f()", AS_FUNCTION(FileSelector_FileSelector_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool GetBlockEvents() const", AS_METHODPR(FileSelector, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // Button* FileSelector::GetCancelButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetCancelButton() const", AS_METHODPR(FileSelector, GetCancelButton, () const, Button*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_cancelButton() const", AS_METHODPR(FileSelector, GetCancelButton, () const, Button*), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetCategory() const", AS_METHODPR(FileSelector, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_category() const", AS_METHODPR(FileSelector, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Button* FileSelector::GetCloseButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetCloseButton() const", AS_METHODPR(FileSelector, GetCloseButton, () const, Button*), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* FileSelector::GetDefaultStyle() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ GetDefaultStyle() const", AS_METHODPR(FileSelector, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ get_defaultStyle() const", AS_METHODPR(FileSelector, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    // bool FileSelector::GetDirectoryMode() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "bool GetDirectoryMode() const", AS_METHODPR(FileSelector, GetDirectoryMode, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "bool get_directoryMode() const", AS_METHODPR(FileSelector, GetDirectoryMode, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "VariantMap& GetEventDataMap() const", AS_METHODPR(FileSelector, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "Object@+ GetEventSender() const", AS_METHODPR(FileSelector, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // ListView* FileSelector::GetFileList() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "ListView@+ GetFileList() const", AS_METHODPR(FileSelector, GetFileList, () const, ListView*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "ListView@+ get_fileList() const", AS_METHODPR(FileSelector, GetFileList, () const, ListView*), AS_CALL_THISCALL);
    // const String& FileSelector::GetFileName() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetFileName() const", AS_METHODPR(FileSelector, GetFileName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_fileName() const", AS_METHODPR(FileSelector, GetFileName, () const, const String&), AS_CALL_THISCALL);
    // LineEdit* FileSelector::GetFileNameEdit() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ GetFileNameEdit() const", AS_METHODPR(FileSelector, GetFileNameEdit, () const, LineEdit*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_fileNameEdit() const", AS_METHODPR(FileSelector, GetFileNameEdit, () const, LineEdit*), AS_CALL_THISCALL);
    // const String& FileSelector::GetFilter() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetFilter() const", AS_METHODPR(FileSelector, GetFilter, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_filter() const", AS_METHODPR(FileSelector, GetFilter, () const, const String&), AS_CALL_THISCALL);
    // unsigned FileSelector::GetFilterIndex() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "uint GetFilterIndex() const", AS_METHODPR(FileSelector, GetFilterIndex, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "uint get_filterIndex() const", AS_METHODPR(FileSelector, GetFilterIndex, () const, unsigned), AS_CALL_THISCALL);
    // DropDownList* FileSelector::GetFilterList() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ GetFilterList() const", AS_METHODPR(FileSelector, GetFilterList, () const, DropDownList*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ get_filterList() const", AS_METHODPR(FileSelector, GetFilterList, () const, DropDownList*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(FileSelector, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(FileSelector, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const VariantMap& GetGlobalVars() const", AS_METHODPR(FileSelector, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const VariantMap& get_globalVars() const", AS_METHODPR(FileSelector, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Button* FileSelector::GetOKButton() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Button@+ GetOKButton() const", AS_METHODPR(FileSelector, GetOKButton, () const, Button*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_okButton() const", AS_METHODPR(FileSelector, GetOKButton, () const, Button*), AS_CALL_THISCALL);
    // const String& FileSelector::GetPath() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetPath() const", AS_METHODPR(FileSelector, GetPath, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_path() const", AS_METHODPR(FileSelector, GetPath, () const, const String&), AS_CALL_THISCALL);
    // LineEdit* FileSelector::GetPathEdit() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ GetPathEdit() const", AS_METHODPR(FileSelector, GetPathEdit, () const, LineEdit*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_pathEdit() const", AS_METHODPR(FileSelector, GetPathEdit, () const, LineEdit*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(FileSelector, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& FileSelector::GetTitle() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetTitle() const", AS_METHODPR(FileSelector, GetTitle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_title() const", AS_METHODPR(FileSelector, GetTitle, () const, const String&), AS_CALL_THISCALL);
    // Text* FileSelector::GetTitleText() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Text@+ GetTitleText() const", AS_METHODPR(FileSelector, GetTitleText, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Text@+ get_titleText() const", AS_METHODPR(FileSelector, GetTitleText, () const, Text*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "StringHash GetType() const", AS_METHODPR(FileSelector, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "StringHash get_type() const", AS_METHODPR(FileSelector, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "const String& GetTypeName() const", AS_METHODPR(FileSelector, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_typeName() const", AS_METHODPR(FileSelector, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Window* FileSelector::GetWindow() const | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "Window@+ GetWindow() const", AS_METHODPR(FileSelector, GetWindow, () const, Window*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Window@+ get_window() const", AS_METHODPR(FileSelector, GetWindow, () const, Window*), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasEventHandlers() const", AS_METHODPR(FileSelector, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(FileSelector, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(FileSelector, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "bool IsInstanceOf(StringHash) const", AS_METHODPR(FileSelector, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(FileSelector, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSelector", "int Refs() const", AS_METHODPR(FileSelector, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "int get_refs() const", AS_METHODPR(FileSelector, Refs, () const, int), AS_CALL_THISCALL);
    // static void FileSelector::RegisterObject(Context* context) | File: ../UI/FileSelector.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSelector", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FileSelector, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SendEvent(StringHash)", AS_METHODPR(FileSelector, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(FileSelector, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SetBlockEvents(bool)", AS_METHODPR(FileSelector, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void FileSelector::SetButtonTexts(const String& okText, const String& cancelText) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetButtonTexts(const String&in, const String&in)", AS_METHODPR(FileSelector, SetButtonTexts, (const String&, const String&), void), AS_CALL_THISCALL);
    // void FileSelector::SetDefaultStyle(XMLFile* style) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(FileSelector, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(FileSelector, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void FileSelector::SetDirectoryMode(bool enable) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetDirectoryMode(bool)", AS_METHODPR(FileSelector, SetDirectoryMode, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_directoryMode(bool)", AS_METHODPR(FileSelector, SetDirectoryMode, (bool), void), AS_CALL_THISCALL);
    // void FileSelector::SetFileName(const String& fileName) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetFileName(const String&in)", AS_METHODPR(FileSelector, SetFileName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_fileName(const String&in)", AS_METHODPR(FileSelector, SetFileName, (const String&), void), AS_CALL_THISCALL);
    // void FileSelector::SetFilters(const Vector<String>& filters, unsigned defaultIndex) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetFilters(Array<String>@+, uint)", AS_FUNCTION_OBJFIRST(FileSelector_SetFilters_VectorString_unsigned), AS_CALL_CDECL_OBJFIRST);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(FileSelector, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(FileSelector, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void FileSelector::SetPath(const String& path) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetPath(const String&in)", AS_METHODPR(FileSelector, SetPath, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_path(const String&in)", AS_METHODPR(FileSelector, SetPath, (const String&), void), AS_CALL_THISCALL);
    // void FileSelector::SetTitle(const String& text) | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void SetTitle(const String&in)", AS_METHODPR(FileSelector, SetTitle, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_title(const String&in)", AS_METHODPR(FileSelector, SetTitle, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromAllEvents()", AS_METHODPR(FileSelector, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(FileSelector_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(FileSelector, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(FileSelector, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSelector", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(FileSelector, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void FileSelector::UpdateElements() | File: ../UI/FileSelector.h
    engine->RegisterObjectMethod("FileSelector", "void UpdateElements()", AS_METHODPR(FileSelector, UpdateElements, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSelector", "int WeakRefs() const", AS_METHODPR(FileSelector, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "int get_weakRefs() const", AS_METHODPR(FileSelector, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FileSystem, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool FileSystem::CheckAccess(const String& pathName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool CheckAccess(const String&in) const", AS_METHODPR(FileSystem, CheckAccess, (const String&) const, bool), AS_CALL_THISCALL);
    // bool FileSystem::Copy(const String& srcFileName, const String& destFileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Copy(const String&in, const String&in)", AS_METHODPR(FileSystem, Copy, (const String&, const String&), bool), AS_CALL_THISCALL);
    // bool FileSystem::CreateDir(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool CreateDir(const String&in)", AS_METHODPR(FileSystem, CreateDir, (const String&), bool), AS_CALL_THISCALL);
    // bool FileSystem::Delete(const String& fileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Delete(const String&in)", AS_METHODPR(FileSystem, Delete, (const String&), bool), AS_CALL_THISCALL);
    // bool FileSystem::DirExists(const String& pathName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool DirExists(const String&in) const", AS_METHODPR(FileSystem, DirExists, (const String&) const, bool), AS_CALL_THISCALL);
    // bool FileSystem::FileExists(const String& fileName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool FileExists(const String&in) const", AS_METHODPR(FileSystem, FileExists, (const String&) const, bool), AS_CALL_THISCALL);
    // explicit FileSystem::FileSystem(Context* context) | File: ../IO/FileSystem.h
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_FACTORY, "FileSystem@+ f()", AS_FUNCTION(FileSystem_FileSystem_Context), AS_CALL_CDECL);
    // String FileSystem::GetAppPreferencesDir(const String& org, const String& app) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetAppPreferencesDir(const String&in, const String&in) const", AS_METHODPR(FileSystem, GetAppPreferencesDir, (const String&, const String&) const, String), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool GetBlockEvents() const", AS_METHODPR(FileSystem, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const String& GetCategory() const", AS_METHODPR(FileSystem, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const String& get_category() const", AS_METHODPR(FileSystem, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // String FileSystem::GetCurrentDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetCurrentDir() const", AS_METHODPR(FileSystem, GetCurrentDir, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_currentDir() const", AS_METHODPR(FileSystem, GetCurrentDir, () const, String), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "VariantMap& GetEventDataMap() const", AS_METHODPR(FileSystem, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "Object@+ GetEventSender() const", AS_METHODPR(FileSystem, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool FileSystem::GetExecuteConsoleCommands() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool GetExecuteConsoleCommands() const", AS_METHODPR(FileSystem, GetExecuteConsoleCommands, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool get_executeConsoleCommands() const", AS_METHODPR(FileSystem, GetExecuteConsoleCommands, () const, bool), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(FileSystem, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(FileSystem, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const VariantMap& GetGlobalVars() const", AS_METHODPR(FileSystem, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const VariantMap& get_globalVars() const", AS_METHODPR(FileSystem, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned FileSystem::GetLastModifiedTime(const String& fileName) const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint GetLastModifiedTime(const String&in) const", AS_METHODPR(FileSystem, GetLastModifiedTime, (const String&) const, unsigned), AS_CALL_THISCALL);
    // String FileSystem::GetProgramDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetProgramDir() const", AS_METHODPR(FileSystem, GetProgramDir, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_programDir() const", AS_METHODPR(FileSystem, GetProgramDir, () const, String), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(FileSystem, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // String FileSystem::GetTemporaryDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetTemporaryDir() const", AS_METHODPR(FileSystem, GetTemporaryDir, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_temporaryDir() const", AS_METHODPR(FileSystem, GetTemporaryDir, () const, String), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "StringHash GetType() const", AS_METHODPR(FileSystem, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "StringHash get_type() const", AS_METHODPR(FileSystem, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "const String& GetTypeName() const", AS_METHODPR(FileSystem, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "const String& get_typeName() const", AS_METHODPR(FileSystem, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // String FileSystem::GetUserDocumentsDir() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "String GetUserDocumentsDir() const", AS_METHODPR(FileSystem, GetUserDocumentsDir, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "String get_userDocumentsDir() const", AS_METHODPR(FileSystem, GetUserDocumentsDir, () const, String), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasEventHandlers() const", AS_METHODPR(FileSystem, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool FileSystem::HasRegisteredPaths() const | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool HasRegisteredPaths() const", AS_METHODPR(FileSystem, HasRegisteredPaths, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(FileSystem, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(FileSystem, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "bool IsInstanceOf(StringHash) const", AS_METHODPR(FileSystem, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(FileSystem, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSystem", "int Refs() const", AS_METHODPR(FileSystem, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int get_refs() const", AS_METHODPR(FileSystem, Refs, () const, int), AS_CALL_THISCALL);
    // void FileSystem::RegisterPath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "void RegisterPath(const String&in)", AS_METHODPR(FileSystem, RegisterPath, (const String&), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileSystem", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FileSystem, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool FileSystem::Rename(const String& srcFileName, const String& destFileName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool Rename(const String&in, const String&in)", AS_METHODPR(FileSystem, Rename, (const String&, const String&), bool), AS_CALL_THISCALL);
    // void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h
    // Error: type "Vector<String>&" can not automatically bind
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SendEvent(StringHash)", AS_METHODPR(FileSystem, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(FileSystem, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SetBlockEvents(bool)", AS_METHODPR(FileSystem, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // bool FileSystem::SetCurrentDir(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SetCurrentDir(const String&in)", AS_METHODPR(FileSystem, SetCurrentDir, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "bool set_currentDir(const String&in)", AS_METHODPR(FileSystem, SetCurrentDir, (const String&), bool), AS_CALL_THISCALL);
    // void FileSystem::SetExecuteConsoleCommands(bool enable) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "void SetExecuteConsoleCommands(bool)", AS_METHODPR(FileSystem, SetExecuteConsoleCommands, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_executeConsoleCommands(bool)", AS_METHODPR(FileSystem, SetExecuteConsoleCommands, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(FileSystem, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(FileSystem, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // bool FileSystem::SetLastModifiedTime(const String& fileName, unsigned newTime) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SetLastModifiedTime(const String&in, uint)", AS_METHODPR(FileSystem, SetLastModifiedTime, (const String&, unsigned), bool), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // int FileSystem::SystemCommand(const String& commandLine, bool redirectStdOutToLog=false) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "int SystemCommand(const String&in, bool = false)", AS_METHODPR(FileSystem, SystemCommand, (const String&, bool), int), AS_CALL_THISCALL);
    // unsigned FileSystem::SystemCommandAsync(const String& commandLine) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint SystemCommandAsync(const String&in)", AS_METHODPR(FileSystem, SystemCommandAsync, (const String&), unsigned), AS_CALL_THISCALL);
    // bool FileSystem::SystemOpen(const String& fileName, const String& mode=String::EMPTY) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "bool SystemOpen(const String&in, const String&in = String::EMPTY)", AS_METHODPR(FileSystem, SystemOpen, (const String&, const String&), bool), AS_CALL_THISCALL);
    // int FileSystem::SystemRun(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "int SystemRun(const String&in, Array<String>@+)", AS_FUNCTION_OBJFIRST(FileSystem_SystemRun_String_VectorString), AS_CALL_CDECL_OBJFIRST);
    // unsigned FileSystem::SystemRunAsync(const String& fileName, const Vector<String>& arguments) | File: ../IO/FileSystem.h
    engine->RegisterObjectMethod("FileSystem", "uint SystemRunAsync(const String&in, Array<String>@+)", AS_FUNCTION_OBJFIRST(FileSystem_SystemRunAsync_String_VectorString), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromAllEvents()", AS_METHODPR(FileSystem, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(FileSystem_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(FileSystem, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(FileSystem, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileSystem", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(FileSystem, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileSystem", "int WeakRefs() const", AS_METHODPR(FileSystem, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileSystem", "int get_weakRefs() const", AS_METHODPR(FileSystem, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("FileWatcher", "void AddChange(const String&in)", AS_METHODPR(FileWatcher, AddChange, (const String&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FileWatcher, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit FileWatcher::FileWatcher(Context* context) | File: ../IO/FileWatcher.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_FACTORY, "FileWatcher@+ f()", AS_FUNCTION(FileWatcher_FileWatcher_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool GetBlockEvents() const", AS_METHODPR(FileWatcher, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetCategory() const", AS_METHODPR(FileWatcher, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const String& get_category() const", AS_METHODPR(FileWatcher, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // static ThreadID Thread::GetCurrentThreadID() | File: ../Core/Thread.h
    // Not registered because have @nobind mark
    // float FileWatcher::GetDelay() const | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "float GetDelay() const", AS_METHODPR(FileWatcher, GetDelay, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "VariantMap& GetEventDataMap() const", AS_METHODPR(FileWatcher, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "Object@+ GetEventSender() const", AS_METHODPR(FileWatcher, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(FileWatcher, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(FileWatcher, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const VariantMap& GetGlobalVars() const", AS_METHODPR(FileWatcher, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const VariantMap& get_globalVars() const", AS_METHODPR(FileWatcher, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool FileWatcher::GetNextChange(String& dest) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "bool GetNextChange(String&)", AS_METHODPR(FileWatcher, GetNextChange, (String&), bool), AS_CALL_THISCALL);
    // const String& FileWatcher::GetPath() const | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetPath() const", AS_METHODPR(FileWatcher, GetPath, () const, const String&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(FileWatcher, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "StringHash GetType() const", AS_METHODPR(FileWatcher, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "StringHash get_type() const", AS_METHODPR(FileWatcher, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "const String& GetTypeName() const", AS_METHODPR(FileWatcher, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "const String& get_typeName() const", AS_METHODPR(FileWatcher, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasEventHandlers() const", AS_METHODPR(FileWatcher, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(FileWatcher, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(FileWatcher, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "bool IsInstanceOf(StringHash) const", AS_METHODPR(FileWatcher, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // static bool Thread::IsMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("FileWatcher");
    engine->RegisterGlobalFunction("bool IsMainThread()", AS_FUNCTIONPR(FileWatcher::IsMainThread, (), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Thread::IsStarted() const | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "bool IsStarted() const", AS_METHODPR(FileWatcher, IsStarted, () const, bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(FileWatcher, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileWatcher", "int Refs() const", AS_METHODPR(FileWatcher, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "int get_refs() const", AS_METHODPR(FileWatcher, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FileWatcher", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FileWatcher, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool Thread::Run() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "bool Run()", AS_METHODPR(FileWatcher, Run, (), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SendEvent(StringHash)", AS_METHODPR(FileWatcher, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(FileWatcher, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SetBlockEvents(bool)", AS_METHODPR(FileWatcher, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void FileWatcher::SetDelay(float interval) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void SetDelay(float)", AS_METHODPR(FileWatcher, SetDelay, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(FileWatcher, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(FileWatcher, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // static void Thread::SetMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("FileWatcher");
    engine->RegisterGlobalFunction("void SetMainThread()", AS_FUNCTIONPR(FileWatcher::SetMainThread, (), void), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Thread::SetPriority(int priority) | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "void SetPriority(int)", AS_METHODPR(FileWatcher, SetPriority, (int), void), AS_CALL_THISCALL);
    // bool FileWatcher::StartWatching(const String& pathName, bool watchSubDirs) | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "bool StartWatching(const String&in, bool)", AS_METHODPR(FileWatcher, StartWatching, (const String&, bool), bool), AS_CALL_THISCALL);
    // void Thread::Stop() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("FileWatcher", "void Stop()", AS_METHODPR(FileWatcher, Stop, (), void), AS_CALL_THISCALL);
    // void FileWatcher::StopWatching() | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void StopWatching()", AS_METHODPR(FileWatcher, StopWatching, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void FileWatcher::ThreadFunction() override | File: ../IO/FileWatcher.h
    engine->RegisterObjectMethod("FileWatcher", "void ThreadFunction()", AS_METHODPR(FileWatcher, ThreadFunction, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromAllEvents()", AS_METHODPR(FileWatcher, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(FileWatcher_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(FileWatcher, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(FileWatcher, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("FileWatcher", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(FileWatcher, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FileWatcher", "int WeakRefs() const", AS_METHODPR(FileWatcher, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FileWatcher", "int get_weakRefs() const", AS_METHODPR(FileWatcher, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Font", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Font, AddRef, (), void), AS_CALL_THISCALL);
    // bool Font::BeginLoad(Deserializer& source) override | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool BeginLoad(Deserializer&)", AS_METHODPR(Font, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool EndLoad()", AS_METHODPR(Font, EndLoad, (), bool), AS_CALL_THISCALL);
    // explicit Font::Font(Context* context) | File: ../UI/Font.h
    engine->RegisterObjectBehaviour("Font", asBEHAVE_FACTORY, "Font@+ f()", AS_FUNCTION(Font_Font_Context), AS_CALL_CDECL);
    // const IntVector2& Font::GetAbsoluteGlyphOffset() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "const IntVector2& GetAbsoluteGlyphOffset() const", AS_METHODPR(Font, GetAbsoluteGlyphOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const IntVector2& get_absoluteGlyphOffset() const", AS_METHODPR(Font, GetAbsoluteGlyphOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Font, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool GetBlockEvents() const", AS_METHODPR(Font, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const String& GetCategory() const", AS_METHODPR(Font, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_category() const", AS_METHODPR(Font, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "VariantMap& GetEventDataMap() const", AS_METHODPR(Font, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "Object@+ GetEventSender() const", AS_METHODPR(Font, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FontFace* Font::GetFace(float pointSize) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "FontFace@+ GetFace(float)", AS_METHODPR(Font, GetFace, (float), FontFace*), AS_CALL_THISCALL);
    // FontType Font::GetFontType() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "FontType GetFontType() const", AS_METHODPR(Font, GetFontType, () const, FontType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "FontType get_fontType() const", AS_METHODPR(Font, GetFontType, () const, FontType), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Font, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Font, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Font, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const VariantMap& get_globalVars() const", AS_METHODPR(Font, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "uint GetMemoryUse() const", AS_METHODPR(Font, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "uint get_memoryUse() const", AS_METHODPR(Font, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "const String& GetName() const", AS_METHODPR(Font, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_name() const", AS_METHODPR(Font, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "StringHash GetNameHash() const", AS_METHODPR(Font, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // const Vector2& Font::GetScaledGlyphOffset() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "const Vector2& GetScaledGlyphOffset() const", AS_METHODPR(Font, GetScaledGlyphOffset, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const Vector2& get_scaledGlyphOffset() const", AS_METHODPR(Font, GetScaledGlyphOffset, () const, const Vector2&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Font, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // IntVector2 Font::GetTotalGlyphOffset(float pointSize) const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "IntVector2 GetTotalGlyphOffset(float) const", AS_METHODPR(Font, GetTotalGlyphOffset, (float) const, IntVector2), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "StringHash GetType() const", AS_METHODPR(Font, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "StringHash get_type() const", AS_METHODPR(Font, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "const String& GetTypeName() const", AS_METHODPR(Font, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const String& get_typeName() const", AS_METHODPR(Font, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "uint GetUseTimer()", AS_METHODPR(Font, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "uint get_useTimer()", AS_METHODPR(Font, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasEventHandlers() const", AS_METHODPR(Font, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Font, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Font, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Font, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Font::IsSDFFont() const | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool IsSDFFont() const", AS_METHODPR(Font, IsSDFFont, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool Load(Deserializer&)", AS_METHODPR(Font, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool LoadFile(const String&in)", AS_METHODPR(Font, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "bool Load(const String&in)", AS_METHODPR(Font, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Font, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Font", "int Refs() const", AS_METHODPR(Font, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "int get_refs() const", AS_METHODPR(Font, Refs, () const, int), AS_CALL_THISCALL);
    // static void Font::RegisterObject(Context* context) | File: ../UI/Font.h
    // Not registered because have @nobind mark
    // void Font::ReleaseFaces() | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void ReleaseFaces()", AS_METHODPR(Font, ReleaseFaces, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Font", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Font, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void ResetUseTimer()", AS_METHODPR(Font, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool Save(Serializer&) const", AS_METHODPR(Font, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "bool SaveFile(const String&in) const", AS_METHODPR(Font, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "bool Save(const String&in) const", AS_METHODPR(Font, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs=false, const String& indentation="\t") | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "bool SaveXML(Serializer&, int, bool = false, const String&in = \"\t\")", AS_METHODPR(Font, SaveXML, (Serializer&, int, bool, const String&), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SendEvent(StringHash)", AS_METHODPR(Font, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Font, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Font::SetAbsoluteGlyphOffset(const IntVector2& offset) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void SetAbsoluteGlyphOffset(const IntVector2&in)", AS_METHODPR(Font, SetAbsoluteGlyphOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_absoluteGlyphOffset(const IntVector2&in)", AS_METHODPR(Font, SetAbsoluteGlyphOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Font, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SetBlockEvents(bool)", AS_METHODPR(Font, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Font, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Font, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetMemoryUse(uint)", AS_METHODPR(Font, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Font", "void SetName(const String&in)", AS_METHODPR(Font, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_name(const String&in)", AS_METHODPR(Font, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Font::SetScaledGlyphOffset(const Vector2& offset) | File: ../UI/Font.h
    engine->RegisterObjectMethod("Font", "void SetScaledGlyphOffset(const Vector2&in)", AS_METHODPR(Font, SetScaledGlyphOffset, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_scaledGlyphOffset(const Vector2&in)", AS_METHODPR(Font, SetScaledGlyphOffset, (const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromAllEvents()", AS_METHODPR(Font, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Font_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Font, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Font, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Font", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Font, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Font", "int WeakRefs() const", AS_METHODPR(Font, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Font", "int get_weakRefs() const", AS_METHODPR(Font, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("FontFace", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FontFace, AddRef, (), void), AS_CALL_THISCALL);
    // virtual const FontGlyph* FontFace::GetGlyph(unsigned c) | File: ../UI/FontFace.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetKerning(uint, uint) const", AS_METHODPR(FontFace, GetKerning, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetPointSize() const", AS_METHODPR(FontFace, GetPointSize, () const, float), AS_CALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "float GetRowHeight() const", AS_METHODPR(FontFace, GetRowHeight, () const, float), AS_CALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "Array<Texture2D@>@ GetTextures() const", AS_FUNCTION_OBJFIRST(FontFace_GetTextures_void), AS_CALL_CDECL_OBJFIRST);
    // virtual bool FontFace::HasMutableGlyphs() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "bool HasMutableGlyphs() const", AS_METHODPR(FontFace, HasMutableGlyphs, () const, bool), AS_CALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFace", "bool IsDataLost() const", AS_METHODPR(FontFace, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // virtual bool FontFace::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize)=0 | File: ../UI/FontFace.h
    // Error: type "const unsigned char*" can not automatically bind
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFace", "int Refs() const", AS_METHODPR(FontFace, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFace", "int get_refs() const", AS_METHODPR(FontFace, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFace", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FontFace, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFace", "int WeakRefs() const", AS_METHODPR(FontFace, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFace", "int get_weakRefs() const", AS_METHODPR(FontFace, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(FontFace, "FontFace")
#endif
#ifdef REGISTER_MANUAL_PART_FontFace
    REGISTER_MANUAL_PART_FontFace(FontFace, "FontFace")
#endif
    RegisterSubclass<RefCounted, FontFace>(engine, "RefCounted", "FontFace");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FontFaceBitmap, AddRef, (), void), AS_CALL_THISCALL);
    // explicit FontFaceBitmap::FontFaceBitmap(Font* font) | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_FACTORY, "FontFaceBitmap@+ f(Font@+)", AS_FUNCTION(FontFaceBitmap_FontFaceBitmap_Font), AS_CALL_CDECL);
    // virtual const FontGlyph* FontFace::GetGlyph(unsigned c) | File: ../UI/FontFace.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetKerning(uint, uint) const", AS_METHODPR(FontFaceBitmap, GetKerning, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetPointSize() const", AS_METHODPR(FontFaceBitmap, GetPointSize, () const, float), AS_CALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "float GetRowHeight() const", AS_METHODPR(FontFaceBitmap, GetRowHeight, () const, float), AS_CALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "Array<Texture2D@>@ GetTextures() const", AS_FUNCTION_OBJFIRST(FontFaceBitmap_GetTextures_void), AS_CALL_CDECL_OBJFIRST);
    // virtual bool FontFace::HasMutableGlyphs() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool HasMutableGlyphs() const", AS_METHODPR(FontFaceBitmap, HasMutableGlyphs, () const, bool), AS_CALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool IsDataLost() const", AS_METHODPR(FontFaceBitmap, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool FontFaceBitmap::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override | File: ../UI/FontFaceBitmap.h
    // Error: type "const unsigned char*" can not automatically bind
    // bool FontFaceBitmap::Load(FontFace* fontFace, bool usedGlyphs) | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool Load(FontFace@+, bool)", AS_METHODPR(FontFaceBitmap, Load, (FontFace*, bool), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceBitmap", "int Refs() const", AS_METHODPR(FontFaceBitmap, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceBitmap", "int get_refs() const", AS_METHODPR(FontFaceBitmap, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceBitmap", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FontFaceBitmap, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool FontFaceBitmap::Save(Serializer& dest, int pointSize, const String& indentation="\t") | File: ../UI/FontFaceBitmap.h
    engine->RegisterObjectMethod("FontFaceBitmap", "bool Save(Serializer&, int, const String&in = \"\t\")", AS_METHODPR(FontFaceBitmap, Save, (Serializer&, int, const String&), bool), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceBitmap", "int WeakRefs() const", AS_METHODPR(FontFaceBitmap, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceBitmap", "int get_weakRefs() const", AS_METHODPR(FontFaceBitmap, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_ADDREF, "void f()", AS_METHODPR(FontFaceFreeType, AddRef, (), void), AS_CALL_THISCALL);
    // explicit FontFaceFreeType::FontFaceFreeType(Font* font) | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_FACTORY, "FontFaceFreeType@+ f(Font@+)", AS_FUNCTION(FontFaceFreeType_FontFaceFreeType_Font), AS_CALL_CDECL);
    // const FontGlyph* FontFaceFreeType::GetGlyph(unsigned c) override | File: ../UI/FontFaceFreeType.h
    // Error: type "const FontGlyph*" can not automatically bind
    // float FontFace::GetKerning(unsigned c, unsigned d) const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetKerning(uint, uint) const", AS_METHODPR(FontFaceFreeType, GetKerning, (unsigned, unsigned) const, float), AS_CALL_THISCALL);
    // float FontFace::GetPointSize() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetPointSize() const", AS_METHODPR(FontFaceFreeType, GetPointSize, () const, float), AS_CALL_THISCALL);
    // float FontFace::GetRowHeight() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "float GetRowHeight() const", AS_METHODPR(FontFaceFreeType, GetRowHeight, () const, float), AS_CALL_THISCALL);
    // const Vector<SharedPtr<Texture2D>>& FontFace::GetTextures() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "Array<Texture2D@>@ GetTextures() const", AS_FUNCTION_OBJFIRST(FontFaceFreeType_GetTextures_void), AS_CALL_CDECL_OBJFIRST);
    // bool FontFaceFreeType::HasMutableGlyphs() const override | File: ../UI/FontFaceFreeType.h
    engine->RegisterObjectMethod("FontFaceFreeType", "bool HasMutableGlyphs() const", AS_METHODPR(FontFaceFreeType, HasMutableGlyphs, () const, bool), AS_CALL_THISCALL);
    // bool FontFace::IsDataLost() const | File: ../UI/FontFace.h
    engine->RegisterObjectMethod("FontFaceFreeType", "bool IsDataLost() const", AS_METHODPR(FontFaceFreeType, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool FontFaceFreeType::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override | File: ../UI/FontFaceFreeType.h
    // Error: type "const unsigned char*" can not automatically bind
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceFreeType", "int Refs() const", AS_METHODPR(FontFaceFreeType, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceFreeType", "int get_refs() const", AS_METHODPR(FontFaceFreeType, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("FontFaceFreeType", asBEHAVE_RELEASE, "void f()", AS_METHODPR(FontFaceFreeType, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("FontFaceFreeType", "int WeakRefs() const", AS_METHODPR(FontFaceFreeType, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("FontFaceFreeType", "int get_weakRefs() const", AS_METHODPR(FontFaceFreeType, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Frustum", "void Define(float, float, float, float, float, const Matrix3x4&in = Matrix3x4::IDENTITY)", AS_METHODPR(Frustum, Define, (float, float, float, float, float, const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Frustum::Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const Vector3&in, const Vector3&in, const Matrix3x4&in = Matrix3x4::IDENTITY)", AS_METHODPR(Frustum, Define, (const Vector3&, const Vector3&, const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Frustum::Define(const BoundingBox& box, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const BoundingBox&in, const Matrix3x4&in = Matrix3x4::IDENTITY)", AS_METHODPR(Frustum, Define, (const BoundingBox&, const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Frustum::Define(const Matrix4& projection) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Define(const Matrix4&in)", AS_METHODPR(Frustum, Define, (const Matrix4&), void), AS_CALL_THISCALL);
    // void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void DefineOrtho(float, float, float, float, float, const Matrix3x4&in = Matrix3x4::IDENTITY)", AS_METHODPR(Frustum, DefineOrtho, (float, float, float, float, float, const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Frustum::DefineSplit(const Matrix4& projection, float near, float far) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void DefineSplit(const Matrix4&in, float, float)", AS_METHODPR(Frustum, DefineSplit, (const Matrix4&, float, float), void), AS_CALL_THISCALL);
    // float Frustum::Distance(const Vector3& point) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "float Distance(const Vector3&in) const", AS_METHODPR(Frustum, Distance, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Frustum::Frustum(const Frustum& frustum) noexcept | File: ../Math/Frustum.h
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Frustum_Frustum_Frustum), AS_CALL_CDECL_OBJFIRST);
    // Intersection Frustum::IsInside(const Vector3& point) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Vector3&in) const", AS_METHODPR(Frustum, IsInside, (const Vector3&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Frustum::IsInside(const Sphere& sphere) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Sphere&in) const", AS_METHODPR(Frustum, IsInside, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Frustum::IsInside(const BoundingBox& box) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const BoundingBox&in) const", AS_METHODPR(Frustum, IsInside, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const Sphere& sphere) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const Sphere&in) const", AS_METHODPR(Frustum, IsInsideFast, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const BoundingBox& box) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const BoundingBox&in) const", AS_METHODPR(Frustum, IsInsideFast, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // Frustum& Frustum::operator=(const Frustum& rhs) noexcept | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum& opAssign(const Frustum&in)", AS_METHODPR(Frustum, operator=, (const Frustum&), Frustum&), AS_CALL_THISCALL);
    // Rect Frustum::Projected(const Matrix4& projection) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Rect Projected(const Matrix4&in) const", AS_METHODPR(Frustum, Projected, (const Matrix4&) const, Rect), AS_CALL_THISCALL);
    // void Frustum::Transform(const Matrix3& transform) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3&in)", AS_METHODPR(Frustum, Transform, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Frustum::Transform(const Matrix3x4& transform) | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3x4&in)", AS_METHODPR(Frustum, Transform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3& transform) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3&in) const", AS_METHODPR(Frustum, Transformed, (const Matrix3&) const, Frustum), AS_CALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3x4& transform) const | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3x4&in) const", AS_METHODPR(Frustum, Transformed, (const Matrix3x4&) const, Frustum), AS_CALL_THISCALL);
    // void Frustum::UpdatePlanes() | File: ../Math/Frustum.h
    engine->RegisterObjectMethod("Frustum", "void UpdatePlanes()", AS_METHODPR(Frustum, UpdatePlanes, (), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", AS_FUNCTION_OBJFIRST(FocusParameters_FocusParameters_bool_bool_bool_float_float), AS_CALL_CDECL_OBJFIRST);
    // void FocusParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("FocusParameters", "void Validate()", AS_METHODPR(FocusParameters, Validate, (), void), AS_CALL_THISCALL);
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
