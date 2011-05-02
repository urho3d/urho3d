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
#include "Context.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <tinyxml.h>

XMLElement::XMLElement() :
    element_(0)
{
}

XMLElement::XMLElement(XMLFile* file, TiXmlElement* element) :
    file_(file),
    element_(element)
{
}

XMLElement::XMLElement(const XMLElement& rhs) :
    file_(rhs.file_),
    element_(rhs.file_ ? rhs.element_ : 0)
{
}

XMLElement::~XMLElement()
{
}

XMLElement XMLElement::CreateChildElement(const std::string& name)
{
    if ((!file_) || (!element_))
        return XMLElement();
    
    TiXmlElement newElement(name.c_str());
    element_->InsertEndChild(newElement);
    return XMLElement(file_, static_cast<TiXmlElement*>(element_->LastChild()));
}

bool XMLElement::RemoveChildElement(const std::string& name, bool last)
{
    if ((!file_) || (!element_))
        return false;
    
    TiXmlNode* element;
    if (name.empty())
    {
        if (last)
            element = element_->LastChild();
        else
            element = element_->FirstChild();
    }
    else
    {
        if (last)
            element = element_->LastChild(name.c_str());
        else
            element = element_->FirstChild(name.c_str());
    }
    
    if (element)
    {
        element_->RemoveChild(element);
        return true;
    }
    
    return false;
}

bool XMLElement::RemoveChildElements(const std::string& name)
{
    if ((!file_) || (!element_))
        return false;
    
    TiXmlNode* element;
    if (name.empty())
    {
        while (element = element_->LastChild())
            element_->RemoveChild(element);
    }
    else
    {
        while (element = element_->LastChild(name.c_str()))
            element_->RemoveChild(element);
    }
    
    return true;
}

bool XMLElement::SetAttribute(const std::string& name, const std::string& value)
{
    if ((!file_) || (!element_))
        return false;
    
    element_->SetAttribute(name.c_str(), value.c_str());
    return true;
}

bool XMLElement::SetBool(const std::string& name, bool value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetBoundingBox(const BoundingBox& value)
{
    if (!SetVector3("min", value.min_))
        return false;
    return SetVector3("max", value.max_);
}

bool XMLElement::SetBuffer(const std::string& name, const void* data, unsigned size)
{
    std::string dataStr;
    const unsigned char* bytes = (const unsigned char*)data;
    
    for (unsigned i = 0; i < size; ++i)
        dataStr += ToString(bytes[i]) + " ";
    
    return SetAttribute(name, dataStr);
}

bool XMLElement::SetBuffer(const std::string& name, const std::vector<unsigned char>& value)
{
    if (!value.size())
        return SetAttribute(name, std::string());
    else
        return SetBuffer(name, &value[0], value.size());
}

bool XMLElement::SetColor(const std::string& name, const Color& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetFloat(const std::string& name, float value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetInt(const std::string& name, int value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetIntRect(const std::string& name, const IntRect& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetIntVector2(const std::string& name, const IntVector2& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetRect(const std::string& name, const Rect& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetQuaternion(const std::string& name, const Quaternion& value)
{
    return XMLElement::SetAttribute(name, ToString(value));
}

bool XMLElement::SetString(const std::string& name, const std::string& value)
{
    return SetAttribute(name, value);
}

bool XMLElement::SetVariant(const Variant& value)
{
    if (!SetAttribute("type", value.GetTypeName()))
        return false;
    
    switch (value.GetType())
    {
    case VAR_RESOURCEREF:
        return SetResourceRef(value.GetResourceRef());
    
    case VAR_RESOURCEREFLIST:
        return SetResourceRefList(value.GetResourceRefList());
        
    case VAR_VARIANTVECTOR:
        return SetVariantVector(value.GetVariantVector());
        
    case VAR_VARIANTMAP:
        return SetVariantMap(value.GetVariantMap());
        
    default:
        return SetAttribute("value", value.ToString());
    }
}

bool XMLElement::SetResourceRef(const ResourceRef& value)
{
    if ((!file_) || (!element_))
        return false;
    
    // Need the context & resource cache to query for reverse hash mappings
    Context* context = file_->GetContext();
    ResourceCache* cache = file_->GetSubsystem<ResourceCache>();
    
    SetAttribute("value", std::string(context->GetTypeName(value.type_)) + ";" + cache->GetResourceName(value.id_));
    return true;
}

bool XMLElement::SetResourceRefList(const ResourceRefList& value)
{
    if ((!file_) || (!element_))
        return false;
    
    // Need the context & resource cache to query for reverse hash mappings
    Context* context = file_->GetContext();
    ResourceCache* cache = file_->GetSubsystem<ResourceCache>();
    
    std::string str(context->GetTypeName(value.type_));
    for (unsigned i = 0; i < value.ids_.size(); ++i)
    {
        str += ";";
        str += cache->GetResourceName(value.ids_[i]);
    }
    
    SetAttribute("value", str);
    return true;
}

bool XMLElement::SetVariantVector(const VariantVector& value)
{
    // Must remove all existing variant child elements (if they exist) to not cause confusion
    if (!RemoveChildElements("variant"))
        return false;
    
    for (VariantVector::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        XMLElement variantElem = CreateChildElement("variant");
        if (!variantElem)
            return false;
        variantElem.SetVariant(*i);
    }
    
    return true;
}

bool XMLElement::SetVariantMap(const VariantMap& value)
{
    if (!RemoveChildElements("variant"))
        return false;
    
    for (VariantMap::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        XMLElement variantElem = CreateChildElement("variant");
        if (!variantElem)
            return false;
        variantElem.SetInt("hash", i->first.GetValue());
        variantElem.SetVariant(i->second);
    }
    
    return true;
}

bool XMLElement::SetVector2(const std::string& name, const Vector2& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetVector3(const std::string& name, const Vector3& value)
{
    return SetAttribute(name, ToString(value));
}

bool XMLElement::SetVector4(const std::string& name, const Vector4& value)
{
    return SetAttribute(name, ToString(value));
}

std::string XMLElement::GetName() const
{
    if ((!file_) || (!element_))
        return std::string();
    
    return std::string(element_->Value());
}

std::string XMLElement::GetText() const
{
    if ((!file_) || (!element_))
        return std::string();
    
    TiXmlNode* node = element_->FirstChild();
    if (node)
        return std::string(node->Value());
    else
        return std::string();
}

bool XMLElement::HasChildElement(const std::string& name) const
{
    if ((!file_) || (!element_))
        return false;
    
    if (element_->FirstChildElement(name.c_str()) != 0)
        return true;
    else
        return false;
}

XMLElement XMLElement::GetChildElement(const std::string& name) const
{
    if ((!file_) || (!element_))
        return XMLElement();
    else
    {
        if (name.empty())
            return XMLElement(file_, element_->FirstChildElement());
        else
            return XMLElement(file_, element_->FirstChildElement(name.c_str()));
    }
}

XMLElement XMLElement::GetNextElement(const std::string& name) const
{
    if ((!file_) || (!element_))
        return XMLElement();
    
    if (name.empty())
        return XMLElement(file_, element_->NextSiblingElement());
    else
        return XMLElement(file_, element_->NextSiblingElement(name.c_str()));
}

XMLElement XMLElement::GetParentElement() const
{
    if ((!file_) || (!element_))
        return XMLElement();
    
    return XMLElement(file_, dynamic_cast<TiXmlElement*>(element_->Parent()));
}

unsigned XMLElement::GetNumAttributes() const
{
    unsigned ret = 0;
    
    if ((file_) && (element_))
    {
        const TiXmlAttribute* attribute = element_->FirstAttribute();
        while (attribute)
        {
            ++ret;
            attribute = attribute->Next();
        }
    }
    
    return ret;
}

bool XMLElement::HasAttribute(const std::string& name) const
{
    if ((!file_) || (!element_))
        return false;
    
    if (element_->Attribute(name.c_str()) != 0)
        return true;
    else
        return false;
}

std::string XMLElement::GetAttribute(const std::string& name) const
{
    if ((!file_) || (!element_))
        return std::string();
    else
    {
        const char* data = element_->Attribute(name.c_str());
        
        if (!data)
            return std::string();
        else
            return std::string(data);
    }
}

std::vector<std::string> XMLElement::GetAttributeNames() const
{
    std::vector<std::string> ret;
    
    if ((file_) && (element_))
    {
        const TiXmlAttribute* attribute = element_->FirstAttribute();
        while (attribute)
        {
            ret.push_back(std::string(attribute->Name()));
            attribute = attribute->Next();
        }
    }
    
    return ret;
}

bool XMLElement::GetBool(const std::string& name) const
{
    return ToBool(GetAttribute(name));
}

BoundingBox XMLElement::GetBoundingBox() const
{
    BoundingBox ret;
    
    ret.min_ = GetVector3("min");
    ret.max_ = GetVector3("max");
    ret.defined_ = true;
    return ret;
}

std::vector<unsigned char> XMLElement::GetBuffer(const std::string& name) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = Split(GetAttribute(name), ' ');
    
    ret.resize(bytes.size());
    for (unsigned i = 0; i < bytes.size(); ++i)
        ret[i] = ToInt(bytes[i]);
    return ret;
}

bool XMLElement::GetBuffer(const std::string& name, void* dest, unsigned size) const
{
    std::vector<unsigned char> ret;
    std::vector<std::string> bytes = Split(GetAttribute(name), ' ');
    unsigned char* destBytes = (unsigned char*)dest;
    if (size < bytes.size())
        return false;
    
    for (unsigned i = 0; i < bytes.size(); ++i)
        destBytes[i] = ToInt(bytes[i]);
    return true;
}

Color XMLElement::GetColor(const std::string& name) const
{
    return ToColor(GetAttribute(name));
}

float XMLElement::GetFloat(const std::string& name) const
{
    return ToFloat(GetAttribute(name));
}

int XMLElement::GetInt(const std::string& name) const
{
    return ToInt(GetAttribute(name));
}

IntRect XMLElement::GetIntRect(const std::string& name) const
{
    return ToIntRect(GetAttribute(name));
}

IntVector2 XMLElement::GetIntVector2(const std::string& name) const
{
    return ToIntVector2(GetAttribute(name));
}

Quaternion XMLElement::GetQuaternion(const std::string& name) const
{
    return ToQuaternion(GetAttribute(name));
}

Rect XMLElement::GetRect(const std::string& name) const
{
    return ToRect(GetAttribute(name));
}

std::string XMLElement::GetString(const std::string& name) const
{
    return GetAttribute(name);
}

std::string XMLElement::GetStringLower(const std::string& name) const
{
    return ToLower(GetAttribute(name));
}

std::string XMLElement::GetStringUpper(const std::string& name) const
{
    return ToUpper(GetAttribute(name));
}

Variant XMLElement::GetVariant() const
{
    Variant ret;
    
    std::string type = ToLower(GetAttribute("type"));
    if (type == "resourceref")
        ret = GetResourceRef();
    else if (type == "resourcereflist")
        ret = GetResourceRefList();
    else if (type == "variantvector")
        ret = GetVariantVector();
    else if (type == "variantmap")
        ret = GetVariantMap();
    else
        ret.FromString(type, GetAttribute("value"));
    
    return ret;
}

ResourceRef XMLElement::GetResourceRef() const
{
    ResourceRef ret;
    
    std::vector<std::string> values = Split(GetAttribute("value"), ';');
    if (values.size() == 2)
    {
        ret.type_ = ShortStringHash(values[0]);
        ret.id_ = StringHash(values[1]);
    }
    
    return ret;
}

ResourceRefList XMLElement::GetResourceRefList() const
{
    ResourceRefList ret;
    
    std::vector<std::string> values = Split(GetAttribute("value"), ';');
    if (values.size() >= 1)
    {
        ret.type_ = ShortStringHash(values[0]);
        ret.ids_.resize(values.size() - 1);
        for (unsigned i = 1; i < values.size(); ++i)
            ret.ids_[i - 1] = StringHash(values[i]);
    }
    
    return ret;
}

VariantVector XMLElement::GetVariantVector() const
{
    VariantVector ret;
    
    XMLElement variantElem = GetChildElement("variant");
    while (variantElem)
    {
        ret.push_back(variantElem.GetVariant());
        variantElem = variantElem.GetNextElement("variant");
    }
    
    return ret;
}

VariantMap XMLElement::GetVariantMap() const
{
    VariantMap ret;
    
    XMLElement variantElem = GetChildElement("variant");
    while (variantElem)
    {
        ShortStringHash key(variantElem.GetInt("hash"));
        ret[key] = variantElem.GetVariant();
        variantElem = variantElem.GetNextElement("variant");
    }
    
    return ret;
}

Vector2 XMLElement::GetVector2(const std::string& name) const
{
    return ToVector2(GetAttribute(name));
}

Vector3 XMLElement::GetVector3(const std::string& name) const
{
    return ToVector3(GetAttribute(name));
}

Vector4 XMLElement::GetVector4(const std::string& name) const
{
    return ToVector4(GetAttribute(name));
}

Vector4 XMLElement::GetVector(const std::string& name) const
{
    return ToVector4(GetAttribute(name), true);
}

XMLFile* XMLElement::GetFile() const
{
    return file_;
}
