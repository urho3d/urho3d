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

#ifndef ENGINE_REGISTERTEMPLATES_H
#define ENGINE_REGISTERTEMPLATES_H

#include "BorderImage.h"
#include "Channel.h"
#include "Deserializer.h"
#include "GeometryNode.h"
#include "RegisterArray.h"
#include "Resource.h"
#include "ResourceCache.h"
#include "Serializer.h"
#include "Texture.h"

#include <angelscript.h>

//! Template function for dynamic cast between two script classes
template <class T, class U> U* refCast(T* t)
{
    if (!t)
        return 0;
    
    return dynamic_cast<U*>(t);
}

//! Template function for returning a Variant pointer type cast to specific class
template <class T> T* getVariantPtr(Variant* ptr)
{
    // An attempt at type safety. Probably can not guarantee that this could not be made to invoke UDB
    T* ptrA = static_cast<T*>(ptr->getPtr());
    RefCounted* ptrB = static_cast<RefCounted*>(ptrA);
    if (dynamic_cast<T*>(ptrB) == ptrA)
        return ptrA;
    else
        return 0;
}

//! Template function for std::vector to array conversion
template <class T> CScriptArray* vectorToArray(const std::vector<T>& vector, const char* arrayName)
{
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIScriptEngine* engine = context->GetEngine();
        asIObjectType* type = engine->GetObjectTypeById(engine->GetTypeIdByDecl(arrayName));
        CScriptArray* arr = new CScriptArray(vector.size(), type);
        
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];
        
        return arr;
    }
    else
        return 0;
}

//! Template function for std::vector to handle array conversion
template <class T> CScriptArray* vectorToHandleArray(const std::vector<T>& vector, const char* arrayName)
{
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIScriptEngine* engine = context->GetEngine();
        asIObjectType* type = engine->GetObjectTypeById(engine->GetTypeIdByDecl(arrayName));
        CScriptArray* arr = new CScriptArray(vector.size(), type);
        
        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            if (vector[i])
                vector[i]->addRef();
            *(static_cast<T*>(arr->At(i))) = vector[i];
        }
        
        return arr;
    }
    else
        return 0;
}

//! Template function for registering implicit ref casts between two classes
template <class T, class U> void registerRefCasts(asIScriptEngine* engine, const char* classNameT, const char* classNameU)
{
    static const std::string declReturnT(std::string(classNameT) + "@+ f()");
    static const std::string declReturnU(std::string(classNameU) + "@+ f()");
    
    engine->RegisterObjectBehaviour(classNameT, asBEHAVE_IMPLICIT_REF_CAST, declReturnU.c_str(), asFUNCTION((refCast<T, U>)), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour(classNameU, asBEHAVE_IMPLICIT_REF_CAST, declReturnT.c_str(), asFUNCTION((refCast<U, T>)), asCALL_CDECL_OBJLAST);
}

//! Template function for registering a class derived from Serializer
template <class T> void registerSerializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "void writeInt(int)", asMETHODPR(T, writeInt, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeShort(int16)", asMETHODPR(T, writeShort, (short), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeByte(int8)", asMETHODPR(T, writeByte, (signed char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeUInt(uint)", asMETHODPR(T, writeUInt, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeUShort(uint16)", asMETHODPR(T, writeUShort, (unsigned short), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeUByte(uint8)", asMETHODPR(T, writeUByte, (unsigned char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeBool(bool)", asMETHODPR(T, writeBool, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeFloat(float)", asMETHODPR(T, writeFloat, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeIntRect(const IntRect& in)", asMETHODPR(T, writeIntRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeIntVector2(const IntVector2& in)", asMETHODPR(T, writeIntVector2, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVector2(const Vector2& in)", asMETHODPR(T, writeVector2, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVector3(const Vector3& in)", asMETHODPR(T, writeVector3, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writePackedVector3(const Vector3& in, float)", asMETHODPR(T, writePackedVector3, (const Vector3&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVector4(const Vector4& in)", asMETHODPR(T, writeVector4, (const Vector4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeQuaternion(const Quaternion& in)", asMETHODPR(T, writeQuaternion, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writePackedQuaternion(const Quaternion& in)", asMETHODPR(T, writePackedQuaternion, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeColor(const Color& in)", asMETHODPR(T, writeColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeBoundingBox(const BoundingBox& in)", asMETHODPR(T, writeBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeString(const string& in)", asMETHODPR(T, writeString, (const std::string&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeStringHash(const StringHash& in)", asMETHODPR(T, writeStringHash, (const StringHash&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeShortStringHash(const ShortStringHash& in)", asMETHODPR(T, writeShortStringHash, (const ShortStringHash&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVariant(const Variant& in)", asMETHODPR(T, writeVariant, (const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVariantMap(const VariantMap& in)", asMETHODPR(T, writeVariantMap, (const VariantMap&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void writeVLE(uint)", asMETHODPR(T, writeVLE, (unsigned), void), asCALL_THISCALL);
}

//! Template function for registering a class derived from Deerializer
template <class T> void registerDeserializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "int readInt()", asMETHODPR(T, readInt, (), int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int16 readShort()", asMETHODPR(T, readShort, (), short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int8 readByte()", asMETHODPR(T, readByte, (), signed char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint readUInt()", asMETHODPR(T, readUInt, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint16 readUShort()", asMETHODPR(T, readUShort, (), unsigned short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint8 readUByte()", asMETHODPR(T, readUByte, (), unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool readBool()", asMETHODPR(T, readBool, (), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float readFloat()", asMETHODPR(T, readFloat, (), float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntRect readIntRect()", asMETHODPR(T, readIntRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 readIntVector2()", asMETHODPR(T, readIntVector2, (), IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 readVector2()", asMETHODPR(T, readVector2, (), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 readVector3()", asMETHODPR(T, readVector3, (), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 readPackedVector3(float)", asMETHODPR(T, readPackedVector3, (float), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector4 readVector4()", asMETHODPR(T, readVector4, (), Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion readQuaternion()", asMETHODPR(T, readQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion readPackedQuaternion()", asMETHODPR(T, readPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Color readColor()", asMETHODPR(T, readColor, (), Color), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BoundingBox readBoundingBox()", asMETHODPR(T, readBoundingBox, (), BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "string readString()", asMETHODPR(T, readString, (), std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash readStringHash()", asMETHODPR(T, readStringHash, (), StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ShortStringHash readShortStringHash()", asMETHODPR(T, readShortStringHash, (), ShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant readVariant()", asMETHODPR(T, readVariant, (), Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap readVariantMap()", asMETHODPR(T, readVariantMap, (), VariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint readVLE()", asMETHODPR(T, readVLE, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint seek(uint)", asMETHODPR(T, seek, (unsigned), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const string& getName() const", asMETHODPR(T, getName, () const, const std::string&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getPosition() const", asMETHODPR(T, getPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getSize() const", asMETHODPR(T, getSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isEof() const", asMETHODPR(T, isEof, () const, bool), asCALL_THISCALL);
}

//! Template function for registering a class derived from HashedType
template <class T> void registerHashedType(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, addRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, releaseRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ShortStringHash getType() const", asMETHODPR(T, getType, () const, ShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const string& getTypeName() const", asMETHODPR(T, getTypeName, () const, const std::string&), asCALL_THISCALL);
}

//! Template function for registering a class derived from Component
template <class T> void registerComponent(asIScriptEngine* engine, const char* className)
{
    registerHashedType<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setName(const string& in)", asMETHODPR(T, setName, (const std::string&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setNetFlags(uint8)", asMETHODPR(T, setNetFlags, (unsigned char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const string& getName() const", asMETHODPR(T, getName, () const, const std::string&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint8 getNetFlags() const", asMETHODPR(T, getNetFlags, () const, unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Entity@+ getEntity() const", asMETHODPR(T, getEntity, () const, Entity*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isAuthority() const", asMETHODPR(T, isAuthority, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isProxy() const", asMETHODPR(T, isProxy, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isOwnerPredicted() const", asMETHODPR(T, isOwnerPredicted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isTransientPredicted() const", asMETHODPR(T, isTransientPredicted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isPlayback() const", asMETHODPR(T, isPlayback, () const, bool), asCALL_THISCALL);
}

//! Template function for registering a class derived from Node
template <class T> void registerNode(asIScriptEngine* engine, const char* className)
{
    registerComponent<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setPosition(const Vector3& in)", asMETHODPR(T, setPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setRotation(const Quaternion& in)", asMETHODPR(T, setRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setScale(float)", asMETHODPR(T, setScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setScale(const Vector3& in)", asMETHODPR(T, setScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setTransform(const Vector3& in, const Quaternion& in)", asMETHODPR(T, setTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setTransform(const Vector3& in, const Quaternion& in, float)", asMETHODPR(T, setTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setTransform(const Vector3& in, const Quaternion& in, const Quaternion& in)", asMETHODPR(T, setTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void translate(const Vector3& in)", asMETHODPR(T, translate, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void translateRelative(const Vector3& in)", asMETHODPR(T, translateRelative, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void rotate(const Quaternion& in, bool)", asMETHODPR(T, rotate, (const Quaternion&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void pitch(float, bool)", asMETHODPR(T, pitch, (float, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void yaw(float, bool)", asMETHODPR(T, yaw, (float, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void roll(float, bool)", asMETHODPR(T, roll, (float, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void scale(float)", asMETHODPR(T, scale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void scale(const Vector3& in)", asMETHODPR(T, scale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void addChild(Node@+)", asMETHODPR(T, addChild, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void removeChild(Node@+, bool)", asMETHODPR(T, removeChild, (Node*, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void removeAllChildren(bool)", asMETHODPR(T, removeAllChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& getPosition() const", asMETHODPR(T, getPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Quaternion& getRotation() const", asMETHODPR(T, getRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& getScale() const", asMETHODPR(T, getScale, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& getWorldPosition()", asMETHODPR(T, getWorldPosition, (), const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Quaternion& getWorldRotation()", asMETHODPR(T, getWorldRotation, (), const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& getWorldScale()", asMETHODPR(T, getWorldScale, (), const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getNodeFlags() const", asMETHODPR(T, getNodeFlags, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ getParent() const", asMETHODPR(T, getParent, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isDirty() const", asMETHODPR(T, isDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getNumChildren(bool) const", asMETHODPR(T, getNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ getChild(uint) const", asMETHODPR(T, getChild, (unsigned) const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ getChild(const string& in, bool) const", asMETHODPR(T, getChild, (const std::string&, bool) const, Node*), asCALL_THISCALL);
}

//! Template function for registering a class derived from Channel. The base type (Component or Node) must have been registered first
template <class T> void registerChannel(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "void play(Sound@+)", asMETHODPR(T, play, (Sound*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void play(Sound@+, float)", asMETHODPR(T, play, (Sound*, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void play(Sound@+, float, float)", asMETHODPR(T, play, (Sound*, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void play(Sound@+, float, float, float)", asMETHODPR(T, play, (Sound*, float, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void stop()", asMETHOD(T, stop), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setChannelType(ChannelType)", asMETHODPR(T, setChannelType, (ChannelType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setFrequency(float)", asMETHODPR(T, setFrequency, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setGain(float)", asMETHODPR(T, setGain, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setPanning(float)", asMETHODPR(T, setPanning, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Sound@+ getSound() const", asMETHODPR(T, getSound, () const, Sound*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ChannelType getChannelType() const", asMETHODPR(T, getChannelType, () const, ChannelType), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getTimePosition() const", asMETHODPR(T, getTimePosition, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getFrequency() const", asMETHODPR(T, getFrequency, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getGain() const", asMETHODPR(T, getGain, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getAttenuation() const", asMETHODPR(T, getAttenuation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getPanning() const", asMETHODPR(T, getPanning, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isPlaying() const", asMETHODPR(T, isPlaying, () const, bool), asCALL_THISCALL);
}

//! Template function for registering a class derived from VolumeNode
template <class T> void registerVolumeNode(asIScriptEngine* engine, const char* className)
{
    registerNode<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setCastShadows(bool)", asMETHODPR(T, setCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setOccluder(bool)", asMETHODPR(T, setOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setVisible(bool)", asMETHODPR(T, setVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setDrawDistance(float)", asMETHODPR(T, setDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setShadowDistance(float)", asMETHODPR(T, setShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setViewMask(uint)", asMETHODPR(T, setViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setLightMask(uint)", asMETHODPR(T, setLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float calculateDrawDistance(Camera@+, float)", asMETHODPR(T, calculateDrawDistance, (const Camera&, float), float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool getCastShadows() const", asMETHODPR(T, getCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isOccluder() const", asMETHODPR(T, isOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isVisible() const", asMETHODPR(T, isVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getDrawDistance() const", asMETHODPR(T, getDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getShadowDistance() const", asMETHODPR(T, getShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getViewMask() const", asMETHODPR(T, getViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getLightMask() const", asMETHODPR(T, getLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isInView(uint) const", asMETHODPR(T, isInView, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const BoundingBox& getWorldBoundingBox()", asMETHODPR(T, getWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
}

//! Template function for registering a class derived from GeometryNode
template <class T> void registerGeometryNode(asIScriptEngine* engine, const char* className)
{
    registerVolumeNode<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setLodBias(float)", asMETHODPR(T, setLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getLodBias() const", asMETHODPR(T, getLodBias, () const, float), asCALL_THISCALL);
}

//! Template function for registering a class derived from Resource
template <class T> void registerResource(asIScriptEngine* engine, const char* className)
{
    registerHashedType<T>(engine, className);
    engine->RegisterObjectMethod(className, "const string& getName() const", asMETHODPR(T, getName, () const, const std::string&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getMemoryUse() const", asMETHODPR(T, getMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getUseTimer()" ,asMETHODPR(T, getUseTimer, (), unsigned), asCALL_THISCALL);
}

//! Template function for registering a class derived from Texture
template <class T> void registerTexture(asIScriptEngine* engine, const char* className)
{
    registerResource<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setNumLevels(uint)", asMETHOD(T, setNumLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setFilterMode(TextureFilterMode)", asMETHOD(T, setFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setAddressMode(TextureCoordinate, TextureAddressMode)", asMETHOD(T, setAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setBorderColor(const Color& in)", asMETHOD(T, setBorderColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setBackupTexture(Texture@+)", asMETHOD(T, setBackupTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void clearDataLost()", asMETHOD(T, clearDataLost), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureUsage getUsage() const", asMETHOD(T, getUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getFormat() const", asMETHOD(T, getFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getLevels() const", asMETHOD(T, getLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int getWidth() const", asMETHOD(T, getWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int getHeight() const", asMETHOD(T, getHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isDataLost() const", asMETHOD(T, isDataLost), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureFilterMode getFilterMode() const", asMETHOD(T, getFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureAddressMode getAddressMode(TextureCoordinate) const", asMETHOD(T, getAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& getBorderColor() const", asMETHOD(T, getBorderColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ getBackupTexture() const", asMETHOD(T, getBackupTexture), asCALL_THISCALL);
}

//! Template function for constructing an UI element
template <class T> T* ConstructUIElement()
{
    return new T();
}

//! Template function for constructing an UI element with name
template <class T> T* ConstructUIElementWithName(const std::string& name)
{
    return new T(name);
}

//! Template function for registering a class derived from UIElement
template <class T> void registerUIElement(asIScriptEngine* engine, const char* className)
{
    static const std::string declFactory(std::string(className) + "@+ f()");
    static const std::string declFactoryWithName(std::string(className) + "@+ f(const string& in)");
    
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.c_str(), asFUNCTION(ConstructUIElement<T>), asCALL_CDECL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactoryWithName.c_str(), asFUNCTION(ConstructUIElementWithName<T>), asCALL_CDECL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, addRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, releaseRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setName(const string& in)", asMETHOD(T, setName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setPosition(const IntVector2& in)", asMETHODPR(T, setPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setPosition(int, int)", asMETHODPR(T, setPosition, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setSize(const IntVector2& in)", asMETHODPR(T, setSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setSize(int, int)", asMETHODPR(T, setSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setWidth(int)", asMETHOD(T, setWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setHeight(int)", asMETHOD(T, setHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setAlignment(HorizontalAlignment, VerticalAlignment)", asMETHOD(T, setAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setHorizontalAlignment(HorizontalAlignment)", asMETHOD(T, setHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setVerticalAlignment(VerticalAlignment)", asMETHOD(T, setVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setColor(const Color& in)", asMETHODPR(T, setColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setColor(UIElementCorner, const Color& in)", asMETHODPR(T, setColor, (UIElementCorner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setHoverColor(const Color& in)", asMETHOD(T, setHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setPriority(int)", asMETHOD(T, setPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setOpacity(float)", asMETHOD(T, setOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setBringToFront(bool)", asMETHOD(T, setBringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setClipChildren(bool)", asMETHOD(T, setClipChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setEnabled(bool)", asMETHOD(T, setEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setFocusable(bool)", asMETHOD(T, setFocusable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setFocus(bool)", asMETHOD(T, setFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setVisible(bool)", asMETHOD(T, setVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void addChild(UIElement@+)", asMETHOD(T, addChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void removeChild(UIElement@+)", asMETHOD(T, removeChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void removeAllChildren()", asMETHOD(T, removeAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const string& getName() const", asMETHOD(T, getName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& getPosition() const", asMETHOD(T, getPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& getSize() const", asMETHOD(T, getSize), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int getWidth() const", asMETHOD(T, getWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int getHeight() const", asMETHOD(T, getHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "HorizontalAlignment getHorizontalAlignment() const", asMETHOD(T, getHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VerticalAlignment getVerticalAlignment() const", asMETHOD(T, getVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& getColor(UIElementCorner) const", asMETHOD(T, getColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& getHoverColor() const", asMETHOD(T, getHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int getPriority() const", asMETHOD(T, getPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float getOpacity() const", asMETHOD(T, getOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool getBringToFront() const", asMETHOD(T, getBringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool getClipChildren() const", asMETHOD(T, getClipChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isEnabled() const", asMETHOD(T, isEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isFocusable() const", asMETHOD(T, isFocusable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool hasFocus() const", asMETHOD(T, hasFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isVisible() const", asMETHOD(T, isVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool isHovering() const", asMETHOD(T, isHovering), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool hasColorGradient() const", asMETHOD(T, hasColorGradient), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint getNumChildren(bool) const", asMETHOD(T, getNumChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ getChild(uint) const", asMETHODPR(T, getChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ getChild(const string& in, bool) const", asMETHODPR(T, getChild, (const std::string&, bool) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ getParent() const", asMETHOD(T, getParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 screenToElement(const IntVector2& in)", asMETHOD(T, screenToElement), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 elementToScreen(const IntVector2& in)", asMETHOD(T, elementToScreen), asCALL_THISCALL);
}

//! Template function for registering a class derived from BorderImage
template <class T> void registerBorderImage(asIScriptEngine* engine, const char* className)
{
    registerUIElement<T>(engine, className);
    engine->RegisterObjectMethod(className, "void setTexture(Texture@+)", asMETHOD(T, setTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setImageRect(const IntRect& in)", asMETHODPR(T, setImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setImageRect(int, int, int, int)", asMETHODPR(T, setImageRect, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setFullImageRect()", asMETHOD(T, setFullImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setBorder(const IntRect& in)", asMETHODPR(T, setBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void setBorder(int, int, int, int)", asMETHODPR(T, setBorder, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ getTexture() const", asMETHOD(T, setTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& getImageRect() const", asMETHOD(T, getImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& getBorder() const", asMETHOD(T, getBorder), asCALL_THISCALL);
}

#endif // ENGINE_REGISTERTEMPLATES_H
