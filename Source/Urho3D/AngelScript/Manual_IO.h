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

#pragma once

#include "../IO/NamedPipe.h"
#include "../IO/PackageFile.h"
#include "../IO/FileSystem.h"

namespace Urho3D
{

// virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0 | File: ../IO/Deserializer.h
template <class T> CScriptArray* Deserializer_Read(unsigned size, Deserializer* ptr)
{
    PODVector<unsigned char> vector(size);
    unsigned bytesRead = size ? ptr->Read(&vector[0], size) : 0;
    vector.Resize(bytesRead);
    return VectorToArray(vector, "Array<uint8>");
}

// VectorBuffer::VectorBuffer(Deserializer& source, unsigned size) | File: .. / IO / VectorBuffer.h
template <class T> VectorBuffer Deserializer_ReadVectorBuffer(unsigned size, Deserializer* ptr)
{
    return VectorBuffer(*ptr, size);
}

#define REGISTER_MEMBERS_MANUAL_PART_Deserializer() \
    /* virtual unsigned Deserializer::Read(void* dest, unsigned size) = 0 | File: ../IO/Deserializer.h */ \
    engine->RegisterObjectMethod(className, "Array<uint8>@ Read(uint)", AS_FUNCTION_OBJLAST(Deserializer_Read<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* VectorBuffer::VectorBuffer(Deserializer& source, unsigned size) | File: .. / IO / VectorBuffer.h */ \
    engine->RegisterObjectMethod(className, "VectorBuffer ReadVectorBuffer(uint)", AS_FUNCTION_OBJLAST(Deserializer_ReadVectorBuffer<T>), AS_CALL_CDECL_OBJLAST);

// ================================================================================

// virtual unsigned Serializer::Write(const void* data, unsigned size) = 0 | File: ../IO/Serializer.h
template <class T> unsigned Serializer_Write(CScriptArray* arr, Serializer* ptr)
{
    unsigned bytesToWrite = arr->GetSize();
    return bytesToWrite ? ptr->Write(arr->At(0), bytesToWrite) : 0;
}

// virtual unsigned Serializer::Write(const void* data, unsigned size) = 0 | File: ../IO/Serializer.h
template <class T> bool Serializer_Write_VectorBuffer(VectorBuffer* src, Serializer* ptr)
{
    return ptr->Write(src->GetData(), src->GetSize()) == src->GetSize();
}

#define REGISTER_MEMBERS_MANUAL_PART_Serializer() \
    /* virtual unsigned Serializer::Write(const void* data, unsigned size) = 0 | File: ../IO/Serializer.h */ \
    engine->RegisterObjectMethod(className, "uint Write(Array<uint8>@+)", AS_FUNCTION_OBJLAST(Serializer_Write<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool WriteVectorBuffer(const VectorBuffer&in)", AS_FUNCTION_OBJLAST(Serializer_Write_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST);

// ================================================================================

// void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h
template <class T> CScriptArray* FileSystem_ScanDir(const String& pathName, const String& filter, unsigned flags, bool recursive, FileSystem* ptr)
{
    Vector<String> result;
    ptr->ScanDir(result, pathName, filter, flags, recursive);
    return VectorToArray<String>(result, "Array<String>");
}

#define REGISTER_MEMBERS_MANUAL_PART_FileSystem() \
    /* void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h */ \
    engine->RegisterObjectMethod(className, "Array<String>@ ScanDir(const String&in, const String&in, uint, bool) const", AS_FUNCTION_OBJLAST(FileSystem_ScanDir<T>), AS_CALL_CDECL_OBJLAST);

}
