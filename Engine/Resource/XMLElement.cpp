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
#include "Log.h"
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
    {
        LOGERROR("Null XML element, can not create child element " + name);
        return XMLElement();
    }
    TiXmlElement newElement(name.c_str());
    mElement->InsertEndChild(newElement);
    return XMLElement(static_cast<TiXmlElement*>(mElement->LastChild()));
}

bool XMLElement::removeChildElement(const std::string& name, bool last)
{
    if (!mElement)
        return false;
    
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
    
    if (element)
    {
        mElement->RemoveChild(element);
        return true;
    }
    
    return false;
}

bool XMLElement::removeChildElements(const std::string& name)
{
    if (!mElement)
        return false;
    
    TiXmlNode* element;
    if (name.empty())
    {
        while (element = mElement->LastChild())
            mElement->RemoveChild(element);
    }
    else
    {
        while (element = mElement->LastChild(name.c_str()))
            mElement->RemoveChild(element);
    }
    
    return true;
}

bool XMLElement::setAttribute(const std::string& name, const std::string& value)
{
    if (!mElement)
    {
        LOGERROR("Null XML element, can not set attribute " + name);
        return false;
    }
    
    mElement->SetAttribute(name.c_str(), value.c_str());
    return true;
}

bool XMLElement::setBool(const std::string& name, bool value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setBoundingBox(const BoundingBox& value)
{
    if (!setVector3("min", value.mMin))
        return false;
    return setVector3("max", value.mMax);
}

bool XMLElement::setBuffer(const std::string& name, const void* data, unsigned size)
{
    std::string dataStr;
    const unsigned char* bytes = (const unsigned char*)data;
    
    for (unsigned i = 0; i < size; ++i)
        dataStr += toString(bytes[i]) + " ";
    
    return setAttribute(name, dataStr);
}

bool XMLElement::setBuffer(const std::string& name, const std::vector<unsigned char>& value)
{
    if (!value.size())
        return setAttribute(name, std::string());
    else
        return setBuffer(name, &value[0], value.size());
}

bool XMLElement::setColor(const std::string& name, const Color& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setFloat(const std::string& name, float value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setInt(const std::string& name, int value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setIntRect(const std::string& name, const IntRect& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setIntVector2(const std::string& name, const IntVector2& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setRect(const std::string& name, const Rect& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setQuaternion(const std::string& name, const Quaternion& value)
{
    return XMLElement::setAttribute(name, toString(value));
}

bool XMLElement::setString(const std::string& name, const std::string& value)
{
    return setAttribute(name, value);
}

bool XMLElement::setVariant(const Variant& value)
{
    if (!setAttribute("type", value.getTypeName()))
        return false;
    
    switch (value.getType())
    {
    case VAR_VARIANTVECTOR:
        return setVariantVector(value.getVariantVector());
        
    case VAR_VARIANTMAP:
        return setVariantMap(value.getVariantMap());
        
    default:
        return setAttribute("value", value.toString());
    }
}

bool XMLElement::setVariantVector(const VariantVector& value)
{
    // Must remove all existing variant child elements (if they exist) to not cause confusion
    if (!removeChildElements("variant"))
        return false;
    
    for (VariantVector::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        XMLElement variantElem = createChildElement("variant");
        if (!variantElem)
            return false;
        variantElem.setVariant(*i);
    }
    
    return true;
}

bool XMLElement::setVariantMap(const VariantMap& value)
{
    if (!removeChildElements("variant"))
        return false;
    
    for (VariantMap::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        XMLElement variantElem = createChildElement("variant");
        if (!variantElem)
            return false;
        std::string name = shortHashToString(i->first);
        if (name.empty())
            variantElem.setInt("hash", i->first.mData);
        else
            variantElem.setString("name", name);
        variantElem.setVariant(i->second);
    }
    
    return true;
}

bool XMLElement::setVector2(const std::string& name, const Vector2& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setVector3(const std::string& name, const Vector3& value)
{
    return setAttribute(name, toString(value));
}

bool XMLElement::setVector4(const std::string& name, const Vector4& value)
{
    return setAttribute(name, toString(value));
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

XMLElement XMLElement::getChildElement(const std::string& name) const
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

XMLElement XMLElement::getNextElement(const std::string& name) const
{
    if (!mElement)
        return XMLElement();
    
    if (name.empty())
        return XMLElement(mElement->NextSiblingElement());
    else
        return XMLElement(mElement->NextSiblingElement(name.c_str()));
}

XMLElement XMLElement::getParentElement() const
{
    if (!mElement)
        return XMLElement();
    
    return XMLElement(dynamic_cast<TiXmlElement*>(mElement->Parent()));
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


std::string XMLElement::getAttribute(const std::string& name) const
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

bool XMLElement::getBool(const std::string& name) const
{
    return toBool(getAttribute(name));
}

BoundingBox XMLElement::getBoundingBox() const
{
    BoundingBox ret;
    
    ret.mMin = getVector3("min");
    ret.mMax = getVector3("max");
    ret.mDefined = true;
    return ret;
}

std::vector<unsigned char> XMLElement::getBuffer(const std::string& name) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = split(getAttribute(name), ' ');
    
    ret.resize(bytes.size());
    for (unsigned i = 0; i < bytes.size(); ++i)
        ret[i] = toInt(bytes[i]);
    return ret;
}

void XMLElement::getBuffer(const std::string& name, void* dest, unsigned size) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = split(getAttribute(name), ' ');
    unsigned char* destBytes = (unsigned char*)dest;
    if (size < bytes.size())
        SAFE_EXCEPTION("Destination buffer not big enough");
    
    for (unsigned i = 0; i < bytes.size(); ++i)
        destBytes[i] = toInt(bytes[i]);
}

Color XMLElement::getColor(const std::string& name) const
{
    return toColor(getAttribute(name));
}

float XMLElement::getFloat(const std::string& name) const
{
    return toFloat(getAttribute(name));
}

int XMLElement::getInt(const std::string& name) const
{
    return toInt(getAttribute(name));
}

IntRect XMLElement::getIntRect(const std::string& name) const
{
    return toIntRect(getAttribute(name));
}

IntVector2 XMLElement::getIntVector2(const std::string& name) const
{
    return toIntVector2(getAttribute(name));
}

Quaternion XMLElement::getQuaternion(const std::string& name) const
{
    return toQuaternion(getAttribute(name));
}

Rect XMLElement::getRect(const std::string& name) const
{
    return toRect(getAttribute(name));
}

std::string XMLElement::getString(const std::string& name) const
{
    return getAttribute(name);
}

std::string XMLElement::getStringLower(const std::string& name) const
{
    return toLower(getAttribute(name));
}

std::string XMLElement::getStringUpper(const std::string& name) const
{
    return toUpper(getAttribute(name));
}

Variant XMLElement::getVariant() const
{
    Variant ret;
    
    std::string type = toLower(getAttribute("type"));
    if (type == "variantvector")
        ret = getVariantVector();
    else if (type == "variantmap")
        ret = getVariantMap();
    else
        ret.fromString(type, getAttribute("value"));
    
    return ret;
}

VariantVector XMLElement::getVariantVector() const
{
    VariantVector ret;
    
    XMLElement variantElem = getChildElement("variant");
    while (variantElem)
    {
        ret.push_back(variantElem.getVariant());
        variantElem = variantElem.getNextElement("variant");
    }
    
    return ret;
}

VariantMap XMLElement::getVariantMap() const
{
    VariantMap ret;
    
    XMLElement variantElem = getChildElement("variant");
    while (variantElem)
    {
        ShortStringHash key;
        if (variantElem.hasAttribute("hash"))
            key.mData = variantElem.getInt("hash");
        else
            key = ShortStringHash(variantElem.getString("name"));
        ret[key] = variantElem.getVariant();
        variantElem = variantElem.getNextElement("variant");
    }
    
    return ret;
}

Vector2 XMLElement::getVector2(const std::string& name) const
{
    return toVector2(getAttribute(name));
}

Vector3 XMLElement::getVector3(const std::string& name) const
{
    return toVector3(getAttribute(name));
}

Vector4 XMLElement::getVector4(const std::string& name) const
{
    return toVector4(getAttribute(name));
}

Vector4 XMLElement::getVector(const std::string& name) const
{
    return toVector4(getAttribute(name), true);
}
