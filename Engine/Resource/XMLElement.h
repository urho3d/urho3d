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

#pragma once

#include "BoundingBox.h"
#include "Rect.h"
#include "Ptr.h"
#include "Variant.h"

class TiXmlElement;
class XMLFile;

/// Element in an XML file
class XMLElement
{
public:
    /// Construct null element
    XMLElement();
    /// Construct with document and element pointers
    XMLElement(XMLFile* file, TiXmlElement* element);
    /// Copy-construct from another element
    XMLElement(const XMLElement& rhs);
    /// Destruct
    ~XMLElement();
    
    /// Create a child element
    XMLElement CreateChild(const String& name);
    /// Remove a child element, either first or last of them if several exist
    bool RemoveChild(const String& name = String(), bool last = true);
    /// Remove child elements of certain name, or all child elements if name is empty
    bool RemoveChildren(const String& name = String());
    /// Set an attribute
    bool SetAttribute(const String& name, const String& value);
    /// Set a bool attribute
    bool SetBool(const String& name, bool value);
    /// Set a BoundingBox attribute
    bool SetBoundingBox(const BoundingBox& value);
    /// Set a buffer attribute
    bool SetBuffer(const String& name, const void* data, unsigned size);
    /// Set a buffer attribute
    bool SetBuffer(const String& name, const PODVector<unsigned char>& value);
    /// Set a Color attribute
    bool SetColor(const String& name, const Color& value);
    /// Set a float attribute
    bool SetFloat(const String& name, float value);
    /// Set an integer attribute
    bool SetInt(const String& name, int value);
    /// Set an IntRect attribute
    bool SetIntRect(const String& name, const IntRect& value);
    /// Set an IntVector2 attribute
    bool SetIntVector2(const String& name, const IntVector2& value);
    /// Set a Rect attribute
    bool SetRect(const String& name, const Rect& value);
    /// Set a Quaternion attribute
    bool SetQuaternion(const String& name, const Quaternion& value);
    /// Set a string attribute
    bool SetString(const String& name, const String& value);
    /// Set a Variant attribute
    bool SetVariant(const Variant& value);
    /// Set a ResourceRef attribute
    bool SetResourceRef(const ResourceRef& value);
    /// Set a ResourceRefList attribute
    bool SetResourceRefList(const ResourceRefList& value);
    /// Set a VariantVector attribute. Creates child elements as necessary
    bool SetVariantVector(const VariantVector& value);
    /// Set a VariantMap attribute. Creates child elements as necessary
    bool SetVariantMap(const VariantMap& value);
    /// Set a Vector2 attribute
    bool SetVector2(const String& name, const Vector2& value);
    /// Set a Vector3 attribute
    bool SetVector3(const String& name, const Vector3& value);
    /// Set a Vector4 attribute
    bool SetVector4(const String& name, const Vector4& value);
    
    /// Return whether does not refer to an element
    bool IsNull() const { return element_ == 0; }
    /// Return whether refers to an element
    bool NotNull() const { return element_ != 0; }
    /// Return true if refers to an element
    operator bool () const { return element_ != 0; }
    /// Return element name
    String GetName() const;
    /// Return element contents
    String GetText() const;
    /// Return whether has a child element
    bool HasChild(const String& name) const;
    /// Return child element, or null if missing
    XMLElement GetChild(const String& name = String()) const;
    /// Return next sibling element
    XMLElement GetNext(const String& name = String()) const;
    /// Return parent element
    XMLElement GetParent() const;
    /// Return number of attributes
    unsigned GetNumAttributes() const;
    /// Return whether has an attribute
    bool HasAttribute(const String& name) const;
    /// Return attribute, or empty if missing
    String GetAttribute(const String& name) const;
    /// Return names of all attributes
    Vector<String> GetAttributeNames() const;
    /// Return bool attribute, or false if missing
    bool GetBool(const String& name) const;
    /// Return buffer attribute, or empty if missing
    PODVector<unsigned char> GetBuffer(const String& name) const;
    /// Copy buffer attribute into a supplied buffer. Return false if not big enough
    bool GetBuffer(const String& name, void* dest, unsigned size) const;
    /// Return bounding box attribute, or empty if missing
    BoundingBox GetBoundingBox() const;
    /// Return a Color attribute, or default if missing
    Color GetColor(const String& name) const;
    /// Return a float attribute, or zero if missing
    float GetFloat(const String& name) const;
    /// Return an integer attribute, or zero if missing
    int GetInt(const String& name) const;
    /// Return an IntRect attribute, or default if missing
    IntRect GetIntRect(const String& name) const;
    /// Return an IntVector2 attribute, or default if missing
    IntVector2 GetIntVector2(const String& name) const;
    /// Return a Rect attribute, or default if missing
    Rect GetRect(const String& name) const;
    /// Return a Quaternion attribute, or default if missing
    Quaternion GetQuaternion(const String& name) const;
    /// Return a string attribute, or empty if missing
    String GetString(const String& name) const;
    /// Return a string attribute in lowercase, or empty if missing
    String GetStringLower(const String& name) const;
    /// Return a string attribute in uppercase, or empty if missing
    String GetStringUpper(const String& name) const;
    /// Return a Variant attribute, or empty if missing
    Variant GetVariant() const;
    /// Return a ResourceRef attribute, or empty if missing
    ResourceRef GetResourceRef() const;
    /// Return a ResourceRefList attribute, or empty if missing
    ResourceRefList GetResourceRefList() const;
    /// Return a VariantVector attribute, or empty if missing
    VariantVector GetVariantVector() const;
    /// Return a VariantMap attribute, or empty if missing
    VariantMap GetVariantMap() const;
    /// Return a Vector2 attribute, or default if missing
    Vector2 GetVector2(const String& name) const;
    /// Return a Vector3 attribute, or default if missing
    Vector3 GetVector3(const String& name) const;
    /// Return a Vector4 attribute, or default if missing
    Vector4 GetVector4(const String& name) const;
    /// Return any Vector attribute as Vector4. Missing coordinates will be zero
    Vector4 GetVector(const String& name) const;
    /// Return XML file
    XMLFile* GetFile() const;
    /// Return TinyXML element
    TiXmlElement* GetElement() const { return element_; }
    
private:
    /// XML file
    WeakPtr<XMLFile> file_;
    /// TinyXML element
    TiXmlElement* element_;
};
