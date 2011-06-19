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

XMLElement XMLElement::CreateChildElement(const String& name)
{
    if ((!file_) || (!element_))
        return XMLElement();
    
    TiXmlElement newElement(name.CString());
    element_->InsertEndChild(newElement);
    return XMLElement(file_, static_cast<TiXmlElement*>(element_->LastChild()));
}

bool XMLElement::RemoveChildElement(const String& name, bool last)
{
    if ((!file_) || (!element_))
        return false;
    
    TiXmlNode* element;
    if (name.Empty())
    {
        if (last)
            element = element_->LastChild();
        else
            element = element_->FirstChild();
    }
    else
    {
        if (last)
            element = element_->LastChild(name.CString());
        else
            element = element_->FirstChild(name.CString());
    }
    
    if (element)
    {
        element_->RemoveChild(element);
        return true;
    }
    
    return false;
}

bool XMLElement::RemoveChildElements(const String& name)
{
    if ((!file_) || (!element_))
        return false;
    
    TiXmlNode* element;
    if (name.Empty())
    {
        while (element = element_->LastChild())
            element_->RemoveChild(element);
    }
    else
    {
        while (element = element_->LastChild(name.CString()))
            element_->RemoveChild(element);
    }
    
    return true;
}

bool XMLElement::SetAttribute(const String& name, const String& value)
{
    if ((!file_) || (!element_))
        return false;
    
    element_->SetAttribute(name.CString(), value.CString());
    return true;
}

bool XMLElement::SetBool(const String& name, bool value)
{
    return SetAttribute(name, String(value));
}

bool XMLElement::SetBoundingBox(const BoundingBox& value)
{
    if (!SetVector3("min", value.min_))
        return false;
    return SetVector3("max", value.max_);
}

bool XMLElement::SetBuffer(const String& name, const void* data, unsigned size)
{
    String dataStr;
    const unsigned char* bytes = (const unsigned char*)data;
    
    for (unsigned i = 0; i < size; ++i)
        dataStr += String((unsigned)bytes[i]) + " ";
    
    return SetAttribute(name, dataStr);
}

bool XMLElement::SetBuffer(const String& name, const PODVector<unsigned char>& value)
{
    if (!value.Size())
        return SetAttribute(name, String());
    else
        return SetBuffer(name, &value[0], value.Size());
}

bool XMLElement::SetColor(const String& name, const Color& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetFloat(const String& name, float value)
{
    return SetAttribute(name, String(value));
}

bool XMLElement::SetInt(const String& name, int value)
{
    return SetAttribute(name, String(value));
}

bool XMLElement::SetIntRect(const String& name, const IntRect& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetIntVector2(const String& name, const IntVector2& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetRect(const String& name, const Rect& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetQuaternion(const String& name, const Quaternion& value)
{
    return XMLElement::SetAttribute(name, value.ToString());
}

bool XMLElement::SetString(const String& name, const String& value)
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
    
    SetAttribute("value", String(context->GetTypeName(value.type_)) + ";" + cache->GetResourceName(value.id_));
    return true;
}

bool XMLElement::SetResourceRefList(const ResourceRefList& value)
{
    if ((!file_) || (!element_))
        return false;
    
    // Need the context & resource cache to query for reverse hash mappings
    Context* context = file_->GetContext();
    ResourceCache* cache = file_->GetSubsystem<ResourceCache>();
    
    String str(context->GetTypeName(value.type_));
    for (unsigned i = 0; i < value.ids_.Size(); ++i)
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
    
    for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
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
    
    for (VariantMap::ConstIterator i = value.Begin(); i != value.End(); ++i)
    {
        XMLElement variantElem = CreateChildElement("variant");
        if (!variantElem)
            return false;
        variantElem.SetInt("hash", i->first_.GetValue());
        variantElem.SetVariant(i->second_);
    }
    
    return true;
}

bool XMLElement::SetVector2(const String& name, const Vector2& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetVector3(const String& name, const Vector3& value)
{
    return SetAttribute(name, value.ToString());
}

bool XMLElement::SetVector4(const String& name, const Vector4& value)
{
    return SetAttribute(name, value.ToString());
}

String XMLElement::GetName() const
{
    if ((!file_) || (!element_))
        return String();
    
    return String(element_->Value());
}

String XMLElement::GetText() const
{
    if ((!file_) || (!element_))
        return String();
    
    TiXmlNode* node = element_->FirstChild();
    if (node)
        return String(node->Value());
    else
        return String();
}

bool XMLElement::HasChildElement(const String& name) const
{
    if ((!file_) || (!element_))
        return false;
    
    if (element_->FirstChildElement(name.CString()) != 0)
        return true;
    else
        return false;
}

XMLElement XMLElement::GetChildElement(const String& name) const
{
    if ((!file_) || (!element_))
        return XMLElement();
    else
    {
        if (name.Empty())
            return XMLElement(file_, element_->FirstChildElement());
        else
            return XMLElement(file_, element_->FirstChildElement(name.CString()));
    }
}

XMLElement XMLElement::GetNextElement(const String& name) const
{
    if ((!file_) || (!element_))
        return XMLElement();
    
    if (name.Empty())
        return XMLElement(file_, element_->NextSiblingElement());
    else
        return XMLElement(file_, element_->NextSiblingElement(name.CString()));
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

bool XMLElement::HasAttribute(const String& name) const
{
    if ((!file_) || (!element_))
        return false;
    
    if (element_->Attribute(name.CString()) != 0)
        return true;
    else
        return false;
}

String XMLElement::GetAttribute(const String& name) const
{
    if ((!file_) || (!element_))
        return String();
    else
    {
        const char* data = element_->Attribute(name.CString());
        
        if (!data)
            return String();
        else
            return String(data);
    }
}

Vector<String> XMLElement::GetAttributeNames() const
{
    Vector<String> ret;
    
    if ((file_) && (element_))
    {
        const TiXmlAttribute* attribute = element_->FirstAttribute();
        while (attribute)
        {
            ret.Push(String(attribute->Name()));
            attribute = attribute->Next();
        }
    }
    
    return ret;
}

bool XMLElement::GetBool(const String& name) const
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

PODVector<unsigned char> XMLElement::GetBuffer(const String& name) const
{
    PODVector<unsigned char> ret;
    Vector<String> bytes = GetAttribute(name).Split(' ');
    
    ret.Resize(bytes.Size());
    for (unsigned i = 0; i < bytes.Size(); ++i)
        ret[i] = ToInt(bytes[i]);
    return ret;
}

bool XMLElement::GetBuffer(const String& name, void* dest, unsigned size) const
{
    PODVector<unsigned char> ret;
    Vector<String> bytes = GetAttribute(name).Split(' ');
    unsigned char* destBytes = (unsigned char*)dest;
    if (size < bytes.Size())
        return false;
    
    for (unsigned i = 0; i < bytes.Size(); ++i)
        destBytes[i] = ToInt(bytes[i]);
    return true;
}

Color XMLElement::GetColor(const String& name) const
{
    return ToColor(GetAttribute(name));
}

float XMLElement::GetFloat(const String& name) const
{
    return ToFloat(GetAttribute(name));
}

int XMLElement::GetInt(const String& name) const
{
    return ToInt(GetAttribute(name));
}

IntRect XMLElement::GetIntRect(const String& name) const
{
    return ToIntRect(GetAttribute(name));
}

IntVector2 XMLElement::GetIntVector2(const String& name) const
{
    return ToIntVector2(GetAttribute(name));
}

Quaternion XMLElement::GetQuaternion(const String& name) const
{
    return ToQuaternion(GetAttribute(name));
}

Rect XMLElement::GetRect(const String& name) const
{
    return ToRect(GetAttribute(name));
}

String XMLElement::GetString(const String& name) const
{
    return GetAttribute(name);
}

String XMLElement::GetStringLower(const String& name) const
{
    return GetAttribute(name).ToLower();
}

String XMLElement::GetStringUpper(const String& name) const
{
    return GetAttribute(name).ToUpper();
}

Variant XMLElement::GetVariant() const
{
    Variant ret;
    
    String type = GetAttribute("type").ToLower();
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
    
    Vector<String> values = GetAttribute("value").Split(';');
    if (values.Size() == 2)
    {
        ret.type_ = ShortStringHash(values[0]);
        ret.id_ = StringHash(values[1]);
    }
    
    return ret;
}

ResourceRefList XMLElement::GetResourceRefList() const
{
    ResourceRefList ret;
    
    Vector<String> values = GetAttribute("value").Split(';');
    if (values.Size() >= 1)
    {
        ret.type_ = ShortStringHash(values[0]);
        ret.ids_.Resize(values.Size() - 1);
        for (unsigned i = 1; i < values.Size(); ++i)
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
        ret.Push(variantElem.GetVariant());
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

Vector2 XMLElement::GetVector2(const String& name) const
{
    return ToVector2(GetAttribute(name));
}

Vector3 XMLElement::GetVector3(const String& name) const
{
    return ToVector3(GetAttribute(name));
}

Vector4 XMLElement::GetVector4(const String& name) const
{
    return ToVector4(GetAttribute(name));
}

Vector4 XMLElement::GetVector(const String& name) const
{
    return ToVector4(GetAttribute(name), true);
}

XMLFile* XMLElement::GetFile() const
{
    return file_;
}
