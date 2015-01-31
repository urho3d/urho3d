//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/BoundingBox.h"
#include "../Math/Rect.h"
#include "../Container/Ptr.h"
#include "../Core/Variant.h"

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
    /// Any type (use type in JSON value).
    JSON_ANY = 0,
    /// Object type (Hash Map).
    JSON_OBJECT,
    /// Array type.
    JSON_ARRAY
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
    JSONValue CreateChild(const String& name, JSONValueType valueType = JSON_OBJECT);
    /// Return a child value by name. Return null if not exist.
    JSONValue GetChild(const String& name, JSONValueType valueType = JSON_ANY) const;
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
    /// Return child names (only object and array child name).
    Vector<String> GetChildNames() const;
    /// Return member value names.
    Vector<String> GetValueNames() const;
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
    JSONValue CreateChild(JSONValueType valueType = JSON_OBJECT);
    /// Remove a child value in array. Return null if not exist.
    JSONValue GetChild(unsigned index, JSONValueType valueType = JSON_ANY) const;
    /// Add int.
    void AddInt(int value);
    /// Add bool.
    void AddBool(bool value);
    /// Add float.
    void AddFloat(float value);
    /// Add vector2.
    void AddVector2(const Vector2& value);
    /// Add vector3.
    void AddVector3(const Vector3& value);
    /// Add vector4.
    void AddVector4(const Vector4& value);
    /// Add vector variant.
    void AddVectorVariant(const Variant& value);
    /// Add quaternion.
    void AddQuaternion(const Quaternion& value);
    /// Add color.
    void AddColor(const Color& value);
    /// Add string.
    void AddString(const String& value);
    /// Add buffer.
    void AddBuffer(const PODVector<unsigned char>& value);
    /// Add buffer.
    void AddBuffer(const void* data, unsigned size);
    /// Add resource ref.
    void AddResourceRef(const ResourceRef& value);
    /// Add resource ref list.
    void AddResourceRefList(const ResourceRefList& value);
    /// Add int rect.
    void AddIntRect(const IntRect& value);
    /// Add int vector2.
    void AddIntVector2(const IntVector2& value);
    /// Add matrix3.
    void AddMatrix3(const Matrix3& value);
    /// Add matrix3x4.
    void AddMatrix3x4(const Matrix3x4& value);
    /// Add matrix4.
    void AddMatrix4(const Matrix4& value);
    /// Add variant.
    void AddVariant(const Variant& value);
    /// Add variant value.
    void AddVariantValue(const Variant& value);
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
    /// Add JSON value to array type.
    void AddMember(rapidjson::Value& jsonValue);
    /// Return JSON value by index for array type.
    rapidjson::Value&  GetMember(unsigned index) const;

    /// JSON file.
    WeakPtr<JSONFile> file_;
    /// Rapid JSON value.
    rapidjson::Value* value_;
};

}
