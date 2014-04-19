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

#pragma once

#include "BoundingBox.h"
#include "Rect.h"
#include "Ptr.h"
#include "Variant.h"

namespace rapidjson
{
    template<typename CharType> struct UTF8;
    class CrtAllocator;
    template <typename BaseAllocator> class MemoryPoolAllocator;
    template <typename Encoding, typename Allocator> class GenericValue;
    typedef GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator> > Value;
}

namespace Urho3D
{

class JSONFile;

/// JSON value type.
enum JSONValueType
{
    /// Object type (Hash Map).
    JVT_OBJECT = 0,
    /// Array type.
    JVT_ARRAY,
    /// Unknown type.
    JVT_UNKNOWN,
};

/// JSON value class.
class URHO3D_API JSONValue
{
public:
    /// Construct null value.
    JSONValue();
    /// Construct with document and JSON value pointers.
    JSONValue(JSONFile* file, rapidjson::Value* value);
    /// Copy-construct from another value.
    JSONValue(const JSONValue& rhs);
    /// Destruct.
    ~JSONValue();

    /// Assignment operator.
    JSONValue& operator = (const JSONValue& rhs);

    /// Return whether does not refer to JSON value.
    bool IsNull() const;
    /// Return whether refers to JSON value.
    bool NotNull() const;
    /// Return true if refers to JSON value.
    operator bool () const;

    // JSON object value functions
    /// Create a child value.
    JSONValue CreateChild(const String& name, JSONValueType valueType = JVT_OBJECT);
    /// Return a child value by name. Return null if not exist.
    JSONValue GetChild(const String& name, JSONValueType valueType = JVT_UNKNOWN) const;
    /// Set int.
    void SetInt(const String& name, int value);
    /// Set bool.
    void SetBool(const String& name, bool value);
    /// Set float.
    void SetFloat(const String& name, float value);
    /// Set vector2.
    void SetVector2(const String& name, const Vector2& value);
    /// Set vector3.
    void SetVector3(const String& name, const Vector3& value);
    /// Set vector4.
    void SetVector4(const String& name, const Vector4& value);
    /// Set vector variant.
    void SetVectorVariant(const String& name, const Variant& value);
    /// Set quaternion.
    void SetQuaternion(const String& name, const Quaternion& value);
    /// Set color.
    void SetColor(const String& name, const Color& value);
    /// Set string.
    void SetString(const String& name, const String& value);
    /// Set buffer.
    void SetBuffer(const String& name, const void* data, unsigned size);
    /// Set buffer.
    void SetBuffer(const String& name, const PODVector<unsigned char>& value);
    /// Set resource ref.
    void SetResourceRef(const String& name, const ResourceRef& value);
    /// Set resource ref list.
    void SetResourceRefList(const String& name, const ResourceRefList& value);
    /// Set int rect.
    void SetIntRect(const String& name, const IntRect& value);
    /// Set int vector2.
    void SetIntVector2(const String& name, const IntVector2& value);
    /// Set matrix3.
    void SetMatrix3(const String& name, const Matrix3& value);
    /// Set matrix3x4.
    void SetMatrix3x4(const String& name, const Matrix3x4& value);
    /// Set matrix4.
    void SetMatrix4(const String& name, const Matrix4& value);
    /// Set variant (include type).
    void SetVariant(const String& name, const Variant& value);
    /// Set variant value.
    void SetVariantValue(const String& name, const Variant& value);

    /// Is object type.
    bool IsObject() const;
    /// Return int.
    int GetInt(const String& name) const;
    /// Return bool.
    bool GetBool(const String& name) const;
    /// Return float.
    float GetFloat(const String& name) const;
    /// Return vector2.
    Vector2 GetVector2(const String& name) const;
    /// Return vector3.
    Vector3 GetVector3(const String& name) const;
    /// Return vector4.
    Vector4 GetVector4(const String& name) const;
    /// Return vector variant.
    Variant GetVectorVariant(const String& name) const;
    /// Return quaternion.
    Quaternion GetQuaternion(const String& name) const;
    /// Return color.
    Color GetColor(const String& name) const;
    /// Return string.
    String GetString(const String& name) const;
    /// Return C string.
    const char* GetCString(const String& name) const;
    /// Return buffer.
    PODVector<unsigned char> GetBuffer(const String& name) const;
    /// Return buffer.
    bool GetBuffer(const String& name, void* dest, unsigned size) const;
    /// Return resource ref.
    ResourceRef GetResourceRef(const String& name) const;
    /// Return resource ref list.
    ResourceRefList GetResourceRefList(const String& name) const;
    /// Return int rect.
    IntRect GetIntRect(const String& name) const;
    /// Return int vector2.
    IntVector2 GetIntVector2(const String& name) const;
    /// Return matrix3.
    Matrix3 GetMatrix3(const String& name) const;
    /// Return matrix3x4.
    Matrix3x4 GetMatrix3x4(const String& name) const;
    /// Return matrix4.
    Matrix4 GetMatrix4(const String& name) const;
    /// Return variant.
    Variant GetVariant(const String& name) const;
    /// Return variant value.
    Variant GetVariantValue(const String& name, VariantType type) const;

    // JSON array value functions
    /// Create a child value in array.
    JSONValue CreateChild(JSONValueType valueType = JVT_OBJECT);
    /// Remove a child value in array. Return null if not exist.
    JSONValue GetChild(unsigned index, JSONValueType valueType = JVT_UNKNOWN) const;
    /// Push int.
    void PushInt(int value);
    /// Push bool.
    void PushBool(bool value);
    /// Push float.
    void PushFloat(float value);
    /// Push vector2.
    void PushVector2(const Vector2& value);
    /// Push vector3.
    void PushVector3(const Vector3& value);
    /// Push vector4.
    void PushVector4(const Vector4& value);
    /// Push vector variant.
    void PushVectorVariant(const Variant& value);
    /// Push quaternion.
    void PushQuaternion(const Quaternion& value);
    /// Push color.
    void PushColor(const Color& value);
    /// Push string.
    void PushString(const String& value);
    /// Push buffer.
    void PushBuffer(const PODVector<unsigned char>& value);
    /// Push buffer.
    void PushBuffer(const void* data, unsigned size);
    /// Push resource ref.
    void PushResourceRef(const ResourceRef& value);
    /// Push resource ref list.
    void PushResourceRefList(const ResourceRefList& value);
    /// Push int rect.
    void PushIntRect(const IntRect& value);
    /// Push int vector2.
    void PushIntVector2(const IntVector2& value);
    /// Push matrix3.
    void PushMatrix3(const Matrix3& value);
    /// Push matrix3x4.
    void PushMatrix3x4(const Matrix3x4& value);
    /// Push matrix4.
    void PushMatrix4(const Matrix4& value);
    /// Push variant.
    void PushVariant(const Variant& value);
    /// Push variant value.
    void PushVariantValue(const Variant& value);
    /// Is array type.
    bool IsArray() const;
    /// Return array size.
    unsigned GetSize() const;
    /// Return int.
    int GetInt(unsigned index) const;
    /// Return bool.
    bool GetBool(unsigned index) const;
    /// Return float.
    float GetFloat(unsigned index) const;
    /// Return vector2.
    Vector2 GetVector2(unsigned index) const;
    /// Return vector3.
    Vector3 GetVector3(unsigned index) const;
    /// Return vector4.
    Vector4 GetVector4(unsigned index) const;
    /// Return vector variant.
    Variant GetVectorVariant(unsigned index) const;
    /// Return quaternion.
    Quaternion GetQuaternion(unsigned index) const;
    /// Return color.
    Color GetColor(unsigned index) const;
    /// Return string.
    String GetString(unsigned index) const;
    /// Return C string.
    const char* GetCString(unsigned index) const;
    /// Return buffer.
    PODVector<unsigned char> GetBuffer(unsigned index) const;
    /// Return buffer.
    bool GetBuffer(unsigned index, void* dest, unsigned size) const;
    /// Return resource ref.
    ResourceRef GetResourceRef(unsigned index) const;
    /// Return resource ref list.
    ResourceRefList GetResourceRefList(unsigned index) const;
    /// Return int rect.
    IntRect GetIntRect(unsigned index) const;
    /// Return int vector2.
    IntVector2 GetIntVector2(unsigned index) const;
    /// Return matrix3.
    Matrix3 GetMatrix3(unsigned index) const;
    /// Return matrix3x4.
    Matrix3x4 GetMatrix3x4(unsigned index) const;
    /// Return matrix4.
    Matrix4 GetMatrix4(unsigned index) const;
    /// Return variant.
    Variant GetVariant(unsigned index) const;
    /// Return variant.
    Variant GetVariantValue(unsigned index, VariantType type) const;
    
    /// Empty JSONValue.
    static const JSONValue EMPTY;

private:
    /// Set JSON value for object type.
    void AddMember(const String& name, rapidjson::Value& jsonValue);
    /// Return JSON value by name for object type.
    rapidjson::Value& GetMember(const String& name) const;
    /// Push JSON value to array type.
    void PushMember(rapidjson::Value& jsonValue);
    /// Return JSON value by index for array type.
    rapidjson::Value&  GetMember(unsigned index) const;

    /// JSON file.
    WeakPtr<JSONFile> file_;
    /// Rapid JSON value.
    rapidjson::Value* value_;
};

}
