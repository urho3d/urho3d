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

// virtual unsigned Deserializer::Read(void *dest, unsigned size)=0 | File: ../IO/Deserializer.h
CScriptArray* DeserializerRead(unsigned size, Deserializer* ptr);
// VectorBuffer(Deserializer& source, unsigned size) | File: .. / IO / VectorBuffer.h
VectorBuffer DeserializerReadVectorBuffer(unsigned size, Deserializer* ptr);

#define REGISTER_MANUAL_PART_Deserializer(T, className) \
    /* virtual unsigned Deserializer::Read(void *dest, unsigned size)=0 | File: ../IO/Deserializer.h */ \
    engine->RegisterObjectMethod(className, "Array<uint8>@ Read(uint)", asFUNCTION(DeserializerRead), asCALL_CDECL_OBJLAST); \
    /* VectorBuffer(Deserializer& source, unsigned size) | File: ../IO/VectorBuffer.h */ \
    engine->RegisterObjectMethod(className, "VectorBuffer ReadVectorBuffer(uint)", asFUNCTION(DeserializerReadVectorBuffer), asCALL_CDECL_OBJLAST);

// ================================================================================

// virtual unsigned Serializer::Write(const void *data, unsigned size)=0 | File: ../IO/Serializer.h
unsigned SerializerWrite(CScriptArray* arr, Serializer* ptr);
// virtual unsigned Serializer::Write(const void *data, unsigned size)=0 | File: ../IO/Serializer.h
bool SerializerWriteVectorBuffer(VectorBuffer* src, Serializer* ptr);

#define REGISTER_MANUAL_PART_Serializer(T, className) \
    /* virtual unsigned Serializer::Write(const void *data, unsigned size)=0 | File: ../IO/Serializer.h */ \
    engine->RegisterObjectMethod(className, "uint Write(Array<uint8>@+)", asFUNCTION(SerializerWrite), asCALL_CDECL_OBJLAST); \
    /* virtual unsigned Serializer::Write(const void *data, unsigned size)=0 | File: ../IO/Serializer.h */ \
    engine->RegisterObjectMethod(className, "bool WriteVectorBuffer(const VectorBuffer&in)", asFUNCTION(SerializerWriteVectorBuffer), asCALL_CDECL_OBJLAST);

// ================================================================================

// void FileSystem::ScanDir(Vector< String > &result, const String &pathName, const String &filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h
CScriptArray* FileSystemScanDir(const String& pathName, const String& filter, unsigned flags, bool recursive, FileSystem* ptr);

#define REGISTER_MANUAL_PART_FileSystem(T, className) \
    /* void FileSystem::ScanDir(Vector< String > &result, const String &pathName, const String &filter, unsigned flags, bool recursive) const | File: ../IO/FileSystem.h */ \
    engine->RegisterObjectMethod(className, "Array<String>@ ScanDir(const String&in, const String&in, uint, bool) const", asFUNCTION(FileSystemScanDir), asCALL_CDECL_OBJLAST);

}
