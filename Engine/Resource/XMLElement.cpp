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

#include "Precompiled.h"
#include "Exception.h"
#include "StringUtils.h"
#include "XMLElement.h"

#include <tinyxml.h>

XMLElement::XMLElement() :
    mElement(0)
{
}

XMLElement::XMLElement(TiXmlElement* element) :
    mElement(element)
{
}

XMLElement::XMLElement(const XMLElement& rhs) :
    mElement(rhs.mElement)
{
}

XMLElement::~XMLElement()
{
}

XMLElement XMLElement::createChildElement(const std::string& name)
{
    if (!mElement)
        SAFE_EXCEPTION_RET("Null XML element, can not create child element " + name, XMLElement());
    
    TiXmlElement newElement(name.c_str());
    mElement->InsertEndChild(newElement);
    return XMLElement(static_cast<TiXmlElement*>(mElement->LastChild()));
}

void XMLElement::removeChildElement(const std::string& name, bool last)
{
    if (!mElement)
        return;
    
    TiXmlNode* element;
    if (name.empty())
    {
        if (last)
            element = mElement->LastChild();
        else
            element = mElement->FirstChild();
    }
    else
    {
        if (last)
            element = mElement->LastChild(name.c_str());
        else
            element = mElement->FirstChild(name.c_str());
    }

    mElement->RemoveChild(element);
}

void XMLElement::setAttribute(const std::string& name, const std::string& value)
{
    if (!mElement)
        SAFE_EXCEPTION("Null XML element, can not set attribute " + name);

    mElement->SetAttribute(name.c_str(), value.c_str());
}

void XMLElement::setBool(const std::string& name, bool value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setBoundingBox(const BoundingBox& value)
{
    setVector3("min", value.mMin);
    setVector3("max", value.mMax);
}

void XMLElement::setBuffer(const std::string& name, const void* data, unsigned size)
{
    std::string dataStr;
    const unsigned char* bytes = (const unsigned char*)data;
    
    for (unsigned i = 0; i < size; ++i)
        dataStr += toString(bytes[i]) + " ";
    
    setAttribute(name, dataStr);
}

void XMLElement::setBuffer(const std::string& name, const std::vector<unsigned char>& value)
{
    if (!value.size())
        setAttribute(name, std::string());
    else
        setBuffer(name, &value[0], value.size());
}

void XMLElement::setColor(const std::string& name, const Color& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setFloat(const std::string& name, float value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setInt(const std::string& name, int value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setIntRect(const std::string& name, const IntRect& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setIntVector2(const std::string& name, const IntVector2& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setRect(const std::string& name, const Rect& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setQuaternion(const std::string& name, const Quaternion& value)
{
    XMLElement::setAttribute(name, toString(value));
}

void XMLElement::setString(const std::string& name, const std::string& value)
{
    setAttribute(name, value);
}

void XMLElement::setVariant(const Variant& value)
{
    setAttribute("type", value.getTypeName());
    setAttribute("value", value.toString());
}

void XMLElement::setVariantMap(const VariantMap& value)
{
    for (VariantMap::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        XMLElement variantElem = createChildElement("variant");
        std::string name = shortHashToString(i->first);
        if (name.empty())
            variantElem.setInt("hash", i->first.mData);
        else
            variantElem.setString("name", name);
        variantElem.setVariant(i->second);
    }
}

void XMLElement::setVector2(const std::string& name, const Vector2& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setVector3(const std::string& name, const Vector3& value)
{
    setAttribute(name, toString(value));
}

void XMLElement::setVector4(const std::string& name, const Vector4& value)
{
    setAttribute(name, toString(value));
}

std::string XMLElement::getName() const
{
    if (!mElement)
        return std::string();

    return std::string(mElement->Value());
}

std::string XMLElement::getText() const
{
    if (!mElement)
        return std::string();
    
    TiXmlNode* node = mElement->FirstChild();
    if (node)
        return std::string(node->Value());
    else
        return std::string();
}

bool XMLElement::hasChildElement(const std::string& name) const
{
    if (!mElement)
        return false;
    
    if (mElement->FirstChildElement(name.c_str()) != 0)
        return true;
    else
        return false;
}

XMLElement XMLElement::getChildElement(const std::string& name, bool throwIfMissing) const
{
    if (throwIfMissing)
    {
        if (!mElement)
            SAFE_EXCEPTION_RET("Null XML element, can not get child element " + name, XMLElement());
        
        TiXmlElement* child;
        if (name.empty())
            child = mElement->FirstChildElement();
        else
            child = mElement->FirstChildElement(name.c_str());
        
        if (!child)
            SAFE_EXCEPTION_RET("XML element " + std::string(mElement->Value()) + " has no child element " + name, XMLElement());
        
        return XMLElement(child);
    }
    else
    {
        if (!mElement)
            return XMLElement();
        else
        {
            if (name.empty())
                return XMLElement(mElement->FirstChildElement());
            else
                return XMLElement(mElement->FirstChildElement(name.c_str()));
        }
    }
}

XMLElement XMLElement::getNextElement(const std::string& name) const
{
    if (!mElement)
        return XMLElement();
    
    if (name.empty())
        return XMLElement(mElement->NextSiblingElement());
    else
        return XMLElement(mElement->NextSiblingElement(name.c_str()));
}

bool XMLElement::hasAttribute(const std::string& name) const
{
    if (!mElement)
        return false;
    
    if (mElement->Attribute(name.c_str()) != 0)
        return true;
    else
        return false;
}


std::string XMLElement::getAttribute(const std::string& name, bool throwIfMissing) const
{
    if (throwIfMissing)
    {
        if (!mElement)
            SAFE_EXCEPTION_RET("Null XML element, can not get attribute " + name, std::string());
        
        const char* data = mElement->Attribute(name.c_str());
        
        if (!data)
            SAFE_EXCEPTION_RET("XML element " + std::string(mElement->Value()) + " has no attribute " + name, std::string())
        else
            return std::string(data);
    }
    else
    {
        if (!mElement)
            return std::string();
        else
        {
            const char* data = mElement->Attribute(name.c_str());
            
            if (!data)
                return std::string();
            else
                return std::string(data);
        }
    }
}

bool XMLElement::getBool(const std::string& name, bool throwIfMissing) const
{
    return toBool(getAttribute(name, throwIfMissing));
}

BoundingBox XMLElement::getBoundingBox(bool throwIfMissing) const
{
    BoundingBox ret;
    
    ret.mMin = getVector3("min", throwIfMissing);
    ret.mMax = getVector3("max", throwIfMissing);
    ret.mDefined = true;
    return ret;
}

std::vector<unsigned char> XMLElement::getBuffer(const std::string& name, bool throwIfMissing) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = split(getAttribute(name, throwIfMissing), ' ');
    
    ret.resize(bytes.size());
    for (unsigned i = 0; i < bytes.size(); ++i)
        ret[i] = toInt(bytes[i]);
    return ret;
}

void XMLElement::getBuffer(const std::string& name, void* dest, unsigned size, bool throwIfMissing) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = split(getAttribute(name, throwIfMissing), ' ');
    unsigned char* destBytes = (unsigned char*)dest;
    if (size < bytes.size())
        SAFE_EXCEPTION("Destination buffer not big enough");
    
    for (unsigned i = 0; i < bytes.size(); ++i)
        destBytes[i] = toInt(bytes[i]);
}

Color XMLElement::getColor(const std::string& name, bool throwIfMissing) const
{
    return toColor(getAttribute(name, throwIfMissing));
}

float XMLElement::getFloat(const std::string& name, bool throwIfMissing) const
{
    return toFloat(getAttribute(name, throwIfMissing));
}

int XMLElement::getInt(const std::string& name, bool throwIfMissing) const
{
    return toInt(getAttribute(name, throwIfMissing));
}

IntRect XMLElement::getIntRect(const std::string& name, bool throwIfMissing) const
{
    return toIntRect(getAttribute(name, throwIfMissing));
}

IntVector2 XMLElement::getIntVector2(const std::string& name, bool throwIfMissing) const
{
    return toIntVector2(getAttribute(name, throwIfMissing));
}

Quaternion XMLElement::getQuaternion(const std::string& name, bool throwIfMissing) const
{
    return toQuaternion(getAttribute(name, throwIfMissing));
}

Rect XMLElement::getRect(const std::string& name, bool throwIfMissing) const
{
    return toRect(getAttribute(name, throwIfMissing));
}

std::string XMLElement::getString(const std::string& name, bool throwIfMissing) const
{
    return getAttribute(name, throwIfMissing);
}

std::string XMLElement::getStringLower(const std::string& name, bool throwIfMissing) const
{
    return toLower(getAttribute(name, throwIfMissing));
}

std::string XMLElement::getStringUpper(const std::string& name, bool throwIfMissing) const
{
    return toUpper(getAttribute(name, throwIfMissing));
}

Variant XMLElement::getVariant(bool throwIfMissing) const
{
    Variant ret;
    std::string type = getAttribute("type", throwIfMissing);
    std::string value = getAttribute("value", throwIfMissing);
    
    ret.fromString(type, value);
    return ret;
}

VariantMap XMLElement::getVariantMap(bool throwIfMissing) const
{
    VariantMap ret;
    
    XMLElement variantElem = getChildElement("variant", false);
    while (variantElem.notNull())
    {
        ShortStringHash key;
        if (variantElem.hasAttribute("hash"))
            key.mData = variantElem.getInt("hash");
        else
            key = ShortStringHash(variantElem.getString("name"));
        ret[key] =variantElem.getVariant(throwIfMissing);
        variantElem = variantElem.getNextElement("variant");
    }
    
    return ret;
}

Vector2 XMLElement::getVector2(const std::string& name, bool throwIfMissing) const
{
    return toVector2(getAttribute(name, throwIfMissing));
}

Vector3 XMLElement::getVector3(const std::string& name, bool throwIfMissing) const
{
    return toVector3(getAttribute(name, throwIfMissing));
}

Vector4 XMLElement::getVector4(const std::string& name, bool throwIfMissing) const
{
    return toVector4(getAttribute(name, throwIfMissing));
}

Vector4 XMLElement::getVector(const std::string& name, bool throwIfMissing) const
{
    return toVector4(getAttribute(name, throwIfMissing), true);
}
