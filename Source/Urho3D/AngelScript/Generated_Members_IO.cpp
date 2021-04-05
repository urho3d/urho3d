// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// class Deserializer | File: ../IO/Deserializer.h
void CollectMembers_Deserializer(MemberCollection& members)
{
    // virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0
    // Error: type "void*" can not automatically bind
    // PODVector<unsigned char> Deserializer::ReadBuffer()
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // VariantVector Deserializer::ReadVariantVector()
    // Error: type "VariantVector" can not automatically bind

}

// struct PackageEntry | File: ../IO/PackageFile.h
void CollectMembers_PackageEntry(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageEntry::offset_", "uint offset", offsetof(PackageEntry, offset_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageEntry::size_", "uint size", offsetof(PackageEntry, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned PackageEntry::checksum_", "uint checksum", offsetof(PackageEntry, checksum_)));

}

// class Serializer | File: ../IO/Serializer.h
void CollectMembers_Serializer(MemberCollection& members)
{
    // virtual unsigned Serializer::Write(const void* data, unsigned size) = 0
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteVariantVector(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// struct StoredLogMessage | File: ../IO/Log.h
void CollectMembers_StoredLogMessage(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("String StoredLogMessage::message_", "String message", offsetof(StoredLogMessage, message_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int StoredLogMessage::level_", "int level", offsetof(StoredLogMessage, level_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool StoredLogMessage::error_", "bool error", offsetof(StoredLogMessage, error_)));

}

// class AbstractFile | File: ../IO/AbstractFile.h
void CollectMembers_AbstractFile(MemberCollection& members)
{
    CollectMembers_Deserializer(members);
    CollectMembers_Serializer(members);

    Remove(members.methods_, "virtual const String& Deserializer::GetName() const");

}

// class File | File: ../IO/File.h
void CollectMembers_File(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_AbstractFile(members);

    Remove(members.methods_, "virtual unsigned Deserializer::GetChecksum()");
    Remove(members.methods_, "virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0");
    Remove(members.methods_, "virtual unsigned Deserializer::Seek(unsigned position) = 0");
    Remove(members.methods_, "virtual unsigned Serializer::Write(const void* data, unsigned size) = 0");

    // void* File::GetHandle() const
    // Error: type "void*" can not automatically bind

}

// class FileSystem | File: ../IO/FileSystem.h
void CollectMembers_FileSystem(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const
    // Error: type "Vector<String>&" can not automatically bind

}

// class FileWatcher | File: ../IO/FileWatcher.h
void CollectMembers_FileWatcher(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_Thread(members);

    Remove(members.methods_, "virtual void Thread::ThreadFunction() = 0");

}

// class Log | File: ../IO/Log.h
void CollectMembers_Log(MemberCollection& members)
{
    CollectMembers_Object(members);

    // static void Log::Write(int level, const String& message)
    // Not registered because have @nobind mark
    // static void Log::WriteFormat(int level, const char* format,...)
    // Error: type "const char*" can not automatically bind

}

// class MemoryBuffer | File: ../IO/MemoryBuffer.h
void CollectMembers_MemoryBuffer(MemberCollection& members)
{
    CollectMembers_AbstractFile(members);

    Remove(members.methods_, "virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0");
    Remove(members.methods_, "virtual unsigned Deserializer::Seek(unsigned position) = 0");
    Remove(members.methods_, "virtual unsigned Serializer::Write(const void* data, unsigned size) = 0");

    // unsigned char* MemoryBuffer::GetData()
    // Error: type "unsigned char*" can not automatically bind

}

// class NamedPipe | File: ../IO/NamedPipe.h
void CollectMembers_NamedPipe(MemberCollection& members)
{
    CollectMembers_Object(members);
    CollectMembers_AbstractFile(members);

    Remove(members.methods_, "virtual bool Deserializer::IsEof() const");
    Remove(members.methods_, "virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0");
    Remove(members.methods_, "virtual unsigned Deserializer::Seek(unsigned position) = 0");
    Remove(members.methods_, "virtual unsigned Serializer::Write(const void* data, unsigned size) = 0");
    Remove(members.methods_, "virtual void AbstractFile::SetName(const String& name)");

}

// class PackageFile | File: ../IO/PackageFile.h
void CollectMembers_PackageFile(MemberCollection& members)
{
    CollectMembers_Object(members);

    // const HashMap<String, PackageEntry>& PackageFile::GetEntries() const
    // Error: type "const HashMap<String, PackageEntry>&" can not automatically bind
    // const PackageEntry* PackageFile::GetEntry(const String& fileName) const
    // Error: type "const PackageEntry*" can not automatically bind

}

// class VectorBuffer | File: ../IO/VectorBuffer.h
void CollectMembers_VectorBuffer(MemberCollection& members)
{
    CollectMembers_AbstractFile(members);

    Remove(members.methods_, "virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0");
    Remove(members.methods_, "virtual unsigned Deserializer::Seek(unsigned position) = 0");
    Remove(members.methods_, "virtual unsigned Serializer::Write(const void* data, unsigned size) = 0");

    // const PODVector<unsigned char>& VectorBuffer::GetBuffer() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const unsigned char* VectorBuffer::GetData() const
    // Error: type "const unsigned char*" can not automatically bind
    // unsigned char* VectorBuffer::GetModifiableData()
    // Error: type "unsigned char*" can not automatically bind
    // void VectorBuffer::SetData(const PODVector<unsigned char>& data)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void VectorBuffer::SetData(const void* data, unsigned size)
    // Error: type "const void*" can not automatically bind

}

} // namespace Urho3D
