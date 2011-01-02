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

#ifndef SCENE_REPLICATIONUTILS_H
#define SCENE_REPLICATIONUTILS_H

#include "Component.h"
#include "VectorBuffer.h"

// Functions for comparing a value against a base revision (either with a default value or not) for writing a delta update
void checkBool(bool value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkBool(bool value, bool defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkInt(int value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkInt(int value, int defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUByte(unsigned char value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUByte(unsigned char value, unsigned char defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUShort(unsigned short value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUShort(unsigned short value, unsigned short defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUInt(unsigned value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkUInt(unsigned value, unsigned defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkFloat(float value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkFloat(float value, float defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkVector3(const Vector3& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkVector3(const Vector3& value, const Vector3& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkQuaternion(const Quaternion& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkQuaternion(const Quaternion& value, const Quaternion& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkColor(const Color& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkColor(const Color& value, const Color& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkString(const std::string& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkString(const std::string& value, const std::string& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkStringHash(StringHash value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkStringHash(StringHash value, StringHash defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkShortStringHash(ShortStringHash value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkShortStringHash(ShortStringHash value, ShortStringHash defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkComponentRef(const ComponentRef& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkComponentRef(const ComponentRef& value, const ComponentRef& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkVLE(unsigned value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkVLE(unsigned value, unsigned defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);
void checkBuffer(const VectorBuffer& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit);

// Functions for writing a value based on a binary condition
void writeBoolDelta(bool value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeIntDelta(int value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeUByteDelta(unsigned char value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeUShortDelta(unsigned short value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeUIntDelta(unsigned value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeFloatDelta(float value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeVector3Delta(const Vector3& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writePackedVector3Delta(const Vector3& value, float maxAbsCoord, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeQuaternionDelta(const Quaternion& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writePackedQuaternionDelta(const Quaternion& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeColorDelta(const Color& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeStringDelta(const std::string& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeStringHashDelta(StringHash value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeShortStringHashDelta(ShortStringHash value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeComponentRefDelta(const ComponentRef& value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeVLEDelta(unsigned value, Serializer& dest, Serializer& destRevision, unsigned char condition);
void writeBufferDelta(const VectorBuffer& value, Serializer& dest, Serializer& destRevision, unsigned char condition);

// Functions for reading a value based on a binary condition
bool readBoolDelta(bool& value, Deserializer& source, unsigned char condition);
bool readIntDelta(int& value, Deserializer& source, unsigned char condition);
bool readUByteDelta(unsigned char& value, Deserializer& source, unsigned char condition);
bool readUShortDelta(unsigned short& value, Deserializer& source, unsigned char condition);
bool readUIntDelta(unsigned& value, Deserializer& source, unsigned char condition);
bool readFloatDelta(float& value, Deserializer& source, unsigned char condition);
bool readVector3Delta(Vector3& value, Deserializer& source, unsigned char condition);
bool readPackedVector3Delta(Vector3& value, float maxAbsCoord, Deserializer& source, unsigned char condition);
bool readQuaternionDelta(Quaternion& value, Deserializer& source, unsigned char condition);
bool readPackedQuaternionDelta(Quaternion& value, Deserializer& source, unsigned char condition);
bool readColorDelta(Color& value, Deserializer& source, unsigned char condition);
bool readStringDelta(std::string& value, Deserializer& source, unsigned char condition);
bool readStringHashDelta(StringHash& value, Deserializer& source, unsigned char condition);
bool readShortStringHashDelta(ShortStringHash& value, Deserializer& source, unsigned char condition);
bool readComponentRefDelta(ComponentRef& value, Deserializer& source, unsigned char condition);
bool readVLEDelta(unsigned& value, Deserializer& source, unsigned char condition);
bool readBufferDelta(VectorBuffer& value, Deserializer& source, unsigned char condition);

//! Compare network frame numbers, taking wrapping into account
inline bool checkFrameNumber(unsigned short lhs, unsigned short rhs, bool sameFrameOk = true)
{
    // Frame number 0 means "frame never received", so in that case lhs is always considered "newer"
    if ((lhs) && (!rhs))
        return true;
    
    if ((!sameFrameOk) && (lhs == rhs))
        return false;
    
    return ((lhs - rhs) & 0xffff) < 0x8000;
}

#endif // SCENE_REPLICATIONUTILS_H
