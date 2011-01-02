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

#ifndef RESOURCE_XMLELEMENT_H
#define RESOURCE_XMLELEMENT_H

#include "BoundingBox.h"
#include "Color.h"
#include "Rect.h"
#include "Quaternion.h"
#include "Variant.h"
#include "Vector4.h"

#include <string>

class TiXmlElement;

//! An element in an XML file
class XMLElement
{
public:
    //! Construct null element
    XMLElement();
    //! Construct with element pointer
    XMLElement(TiXmlElement* element);
    //! Copy-construct from another element
    XMLElement(const XMLElement& rhs);
    //! Destruct
    ~XMLElement();
    
    //! Create a child element
    XMLElement createChildElement(const std::string& name);
    //! Remove a child element, either first or last of them if several exist
    void removeChildElement(const std::string& name, bool last = true);
    //! Set an attribute
    void setAttribute(const std::string& name, const std::string& value);
    //! Set a bool attribute
    void setBool(const std::string& name, bool value);
    //! Set a BoundingBox attribute
    void setBoundingBox(const BoundingBox& value);
    //! Set a buffer attribute
    void setBuffer(const std::string& name, const void* data, unsigned size);
    //! Set a buffer attribute
    void setBuffer(const std::string& name, const std::vector<unsigned char>& value);
    //! Set a Color attribute
    void setColor(const std::string& name, const Color& value);
    //! Set a float attribute
    void setFloat(const std::string& name, float value);
    //! Set an integer attribute
    void setInt(const std::string& name, int value);
    //! Set an IntRect attribute
    void setIntRect(const std::string& name, const IntRect& value);
    //! Set an IntVector2 attribute
    void setIntVector2(const std::string& name, const IntVector2& value);
    //! Set a Rect attribute
    void setRect(const std::string& name, const Rect& value);
    //! Set a Quaternion attribute
    void setQuaternion(const std::string& name, const Quaternion& value);
    //! Set a string attribute
    void setString(const std::string& name, const std::string& value);
    //! Set a Variant attribute
    void setVariant(const Variant& value);
    //! Set a VariantMap attribute
    void setVariantMap(const VariantMap& value);
    //! Set a Vector2 attribute
    void setVector2(const std::string& name, const Vector2& value);
    //! Set a Vector3 attribute
    void setVector3(const std::string& name, const Vector3& value);
    //! Set a Vector4 attribute
    void setVector4(const std::string& name, const Vector4& value);
    
    //! Return whether does not refer to an element
    bool isNull() const { return mElement == 0; }
    //! Return whether refers to an element
    bool notNull() const { return mElement != 0; }
    //! Return true if refers to an element
    operator bool () const { return mElement != 0; }
    //! Return element name
    std::string getName() const;
    //! Return element contents
    std::string getText() const;
    //! Return whether has a child element
    bool hasChildElement(const std::string& name) const;
    //! Return child element. Optionally throw an exception if missing
    XMLElement getChildElement(const std::string& name = std::string(), bool throwIfMissing = true) const;
    //! Return next sibling element
    XMLElement getNextElement(const std::string& name = std::string()) const;
    //! Return whether has an attribute
    bool hasAttribute(const std::string& name) const;
    //! Return attribute. Optionally throw an exception if missing
    std::string getAttribute(const std::string& name, bool throwIfMissing = true) const;
    //! Return bool attribute. Optionally throw an exception if missing
    bool getBool(const std::string& name, bool throwIfMissing = true) const;
    //! Return buffer attribute. Optionally throw an exception if missing
    std::vector<unsigned char> getBuffer(const std::string& name, bool throwIfMissing = true) const;
    //! Copy buffer attribute into a supplied buffer. Throw exception if not big enough. Optionally throw an exception if missing
    void getBuffer(const std::string& name, void* dest, unsigned size, bool throwIfMissing = true) const;
    //! Return bounding box attribute. Optionally throw an exception if missing
    BoundingBox getBoundingBox(bool throwIfMissing = true) const;
    //! Return a Color attribute. Optionally throw an exception if missing
    Color getColor(const std::string& name, bool throwIfMissing = true) const;
    //! Return a float attribute. Optionally throw an exception if missing
    float getFloat(const std::string& name, bool throwIfMissing = true) const;
    //! Return an integer attribute. Optionally throw an exception if missing
    int getInt(const std::string& name, bool throwIfMissing = true) const;
    //! Return an IntRect attribute. Optionally throw an exception if missing
    IntRect getIntRect(const std::string& name, bool throwIfMissing = true) const;
    //! Return an IntVector2 attribute. Optionally throw an exception if missing
    IntVector2 getIntVector2(const std::string& name, bool throwIfMissing = true) const;
    //! Return a Rect attribute. Optionally throw an exception if missing
    Rect getRect(const std::string& name, bool throwIfMissing = true) const;
    //! Return a Quaternion attribute. Optionally throw an exception if missing
    Quaternion getQuaternion(const std::string& name, bool throwIfMissing = true) const;
    //! Return a string attribute. Optionally throw an exception if missing
    std::string getString(const std::string& name, bool throwIfMissing = true) const;
    //! Return a string attribute in lowercase. Optionally throw an exception if missing
    std::string getStringLower(const std::string& name, bool throwIfMissing = true) const;
    //! Return a string attribute in uppercase. Optionally throw an exception if missing
    std::string getStringUpper(const std::string& name, bool throwIfMissing = true) const;
    //! Return a Variant attribute. Optionally throw an exception if missing
    Variant getVariant(bool throwIfMissing = true) const;
    //! Return a VariantMap attribute. Optionally throw an exception if missing
    VariantMap getVariantMap(bool throwIfMissing = true) const;
    //! Return a Vector2 attribute. Optionally throw an exception if missing
    Vector2 getVector2(const std::string& name, bool throwIfMissing = true) const;
    //! Return a Vector3 attribute. Optionally throw an exception if missing
    Vector3 getVector3(const std::string& name, bool throwIfMissing = true) const;
    //! Return a Vector4 attribute. Optionally throw an exception if missing
    Vector4 getVector4(const std::string& name, bool throwIfMissing = true) const;
    //! Return any Vector attribute as Vector4. Missing coordinates will be zero. Optionally throw an exception if missing
    Vector4 getVector(const std::string& name, bool throwIfMissing = true) const;
    
    //! Return TinyXML element
    TiXmlElement* getElement() const { return mElement; }
    
private:
    //! TinyXML element
    TiXmlElement* mElement;
};

#endif // RESOURCE_XMLELEMENT_H
