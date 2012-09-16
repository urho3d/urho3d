//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

#include <pugixml.hpp>

#include "DebugNew.h"

namespace Urho3D
{

XMLElement::XMLElement() :
    node_(0)
{
}

XMLElement::XMLElement(XMLFile* file, pugi::xml_node_struct* node) :
    file_(file),
    node_(node)
{
}

XMLElement::XMLElement(const XMLElement& rhs) :
    file_(rhs.file_),
    node_(rhs.file_ ? rhs.node_ : 0)
{
}

XMLElement::~XMLElement()
{
}

XMLElement XMLElement::CreateChild(const String& name)
{
    return CreateChild(name.CString());
}

XMLElement XMLElement::CreateChild(const char* name)
{
    if (!file_ || !node_)
        return XMLElement();
    
    pugi::xml_node node(node_);
    pugi::xml_node child = node.append_child(name);
    return XMLElement(file_, child.internal_object());
}

bool XMLElement::RemoveChild(const XMLElement& element)
{
    if (!file_ || !node_ || element.node_)
        return false;
    
    pugi::xml_node node(node_);
    pugi::xml_node child(element.node_);
    return node.remove_child(child);
}

bool XMLElement::RemoveChild(const String& name)
{
    return RemoveChild(name.CString());
}

bool XMLElement::RemoveChild(const char* name)
{
    if (!file_ || !node_)
        return false;
    
    pugi::xml_node node(node_);
    return node.remove_child(name);
}

bool XMLElement::RemoveChildren(const String& name)
{
    return RemoveChildren(name.CString());
}

bool XMLElement::RemoveChildren(const char* name)
{
    if (!file_ || !node_)
        return false;
    
    pugi::xml_node node(node_);
    if (!String::CStringLength(name))
    {
        for (;;)
        {
            pugi::xml_node child = node.last_child();
            if (child.empty())
                break;
            node.remove_child(child);
        }
    }
    else
    {
        for (;;)
        {
            pugi::xml_node child = node.child(name);
            if (child.empty())
                break;
            node.remove_child(child);
        }
    }
    
    return true;
}

bool XMLElement::SetAttribute(const String& name, const String& value)
{
    return SetAttribute(name.CString(), value.CString());
}

bool XMLElement::SetAttribute(const char* name, const char* value)
{
    if (!file_ || !node_)
        return false;
    
    pugi::xml_node node(node_);
    pugi::xml_attribute attr = node.attribute(name);
    if (attr.empty())
        attr = node.append_attribute(name);
    attr.set_value(value);
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
    
    return SetVariantValue(value);
}

bool XMLElement::SetVariantValue(const Variant& value)
{
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
        return SetAttribute("value", value.ToString().CString());
    }
}

bool XMLElement::SetResourceRef(const ResourceRef& value)
{
    if (!file_ || !node_)
        return false;
    
    // Need the context & resource cache to query for reverse hash mappings
    Context* context = file_->GetContext();
    ResourceCache* cache = file_->GetSubsystem<ResourceCache>();
    
    SetAttribute("value", String(context->GetTypeName(value.type_)) + ";" + cache->GetResourceName(value.id_));
    return true;
}

bool XMLElement::SetResourceRefList(const ResourceRefList& value)
{
    if (!file_ || !node_)
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
    
    SetAttribute("value", str.CString());
    return true;
}

bool XMLElement::SetVariantVector(const VariantVector& value)
{
    // Must remove all existing variant child elements (if they exist) to not cause confusion
    if (!RemoveChildren("variant"))
        return false;
    
    for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
    {
        XMLElement variantElem = CreateChild("variant");
        if (!variantElem)
            return false;
        variantElem.SetVariant(*i);
    }
    
    return true;
}

bool XMLElement::SetVariantMap(const VariantMap& value)
{
    if (!RemoveChildren("variant"))
        return false;
    
    for (VariantMap::ConstIterator i = value.Begin(); i != value.End(); ++i)
    {
        XMLElement variantElem = CreateChild("variant");
        if (!variantElem)
            return false;
        variantElem.SetInt("hash", i->first_.Value());
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
    if (!file_ || !node_)
        return String();
    
    pugi::xml_node node(node_);
    return String(node.name());
}

bool XMLElement::HasChild(const String& name) const
{
    return HasChild(name.CString());
}

bool XMLElement::HasChild(const char* name) const
{
    if (!file_ || !node_)
        return false;
    
    pugi::xml_node node(node_);
    return !node.child(name).empty();
}

XMLElement XMLElement::GetChild(const String& name) const
{
    return GetChild(name.CString());
}

XMLElement XMLElement::GetChild(const char* name) const
{
    if (!file_ || !node_)
        return XMLElement();
    
    pugi::xml_node node(node_);
    if (!String::CStringLength(name))
        return XMLElement(file_, node.first_child().internal_object());
    else
        return XMLElement(file_, node.child(name).internal_object());
}

XMLElement XMLElement::GetNext(const String& name) const
{
    return GetNext(name.CString());
}

XMLElement XMLElement::GetNext(const char* name) const
{
    if (!file_ || !node_)
        return XMLElement();
    
    pugi::xml_node node(node_);
    if (!String::CStringLength(name))
        return XMLElement(file_, node.next_sibling().internal_object());
    else
        return XMLElement(file_, node.next_sibling(name).internal_object());
}

XMLElement XMLElement::GetParent() const
{
    if (!file_ || !node_)
        return XMLElement();
    
    pugi::xml_node node(node_);
    return XMLElement(file_, node.parent().internal_object());
}

unsigned XMLElement::GetNumAttributes() const
{
    if (!file_ || !node_)
        return 0;
    
    pugi::xml_node node(node_);
    unsigned ret = 0;
    
    pugi::xml_attribute attr = node.first_attribute();
    while (!attr.empty())
    {
        ++ret;
        attr = attr.next_attribute();
    }
    
    return ret;
}

bool XMLElement::HasAttribute(const String& name) const
{
    return HasAttribute(name.CString());
}

bool XMLElement::HasAttribute(const char* name) const
{
    if (!file_ || !node_)
        return false;
    
    pugi::xml_node node(node_);
    return !node.attribute(name).empty();
}

String XMLElement::GetAttribute(const String& name) const
{
    if (!file_ || !node_)
        return String();
    
    pugi::xml_node node(node_);
    return String(node.attribute(name.CString()).value());
}

const char* XMLElement::GetAttribute(const char* name) const
{
    if (!file_ || !node_)
        return 0;
    
    pugi::xml_node node(node_);
    return node.attribute(name).value();
}

String XMLElement::GetAttributeLower(const String& name) const
{
    return GetAttribute(name).ToLower();
}

String XMLElement::GetAttributeLower(const char* name) const
{
    return String(GetAttribute(name)).ToLower();
}

String XMLElement::GetAttributeUpper(const String& name) const
{
    return GetAttribute(name).ToUpper();
}

String XMLElement::GetAttributeUpper(const char* name) const
{
    return String(GetAttribute(name)).ToUpper();
}

Vector<String> XMLElement::GetAttributeNames() const
{
    if (!file_ || !node_)
        return Vector<String>();
    
    pugi::xml_node node(node_);
    Vector<String> ret;
    
    pugi::xml_attribute attr = node.first_attribute();
    while (!attr.empty())
    {
        ret.Push(String(attr.name()));
        attr = attr.next_attribute();
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

Variant XMLElement::GetVariant() const
{
    VariantType type = Variant::GetTypeFromName(GetAttribute("type"));
    return GetVariantValue(type);
}

Variant XMLElement::GetVariantValue(VariantType type) const
{
    Variant ret;
    
    if (type == VAR_RESOURCEREF)
        ret = GetResourceRef();
    else if (type == VAR_RESOURCEREFLIST)
        ret = GetResourceRefList();
    else if (type == VAR_VARIANTVECTOR)
        ret = GetVariantVector();
    else if (type == VAR_VARIANTMAP)
        ret = GetVariantMap();
    else
        ret.FromString(type, GetAttribute("value"));
    
    return ret;
}

ResourceRef XMLElement::GetResourceRef() const
{
    ResourceRef ret;
    
    Vector<String> values = String::Split(GetAttribute("value"), ';');
    if (values.Size() == 2)
    {
        ret.type_ = ShortStringHash(values[0]);
        ret.id_ = StringHash(values[1]);
        
        // Whenever we encounter a resource name read from a ResourceRef XML element, store the reverse mapping to
        // ResourceCache if possible. We will probably use the hash to request a resource shortly afterward
        if (file_)
            file_->GetSubsystem<ResourceCache>()->StoreNameHash(values[1]);
    }
    
    return ret;
}

ResourceRefList XMLElement::GetResourceRefList() const
{
    ResourceRefList ret;
    
    Vector<String> values = String::Split(GetAttribute("value"), ';');
    if (values.Size() >= 1)
    {
        // Whenever we encounter resource names read from a ResourceRefList XML element, store the reverse mapping to
        // ResourceCache if possible. We will probably use the hashes to request resources shortly afterward
        ResourceCache* cache = file_ ? file_->GetSubsystem<ResourceCache>() : 0;
        
        ret.type_ = ShortStringHash(values[0]);
        ret.ids_.Resize(values.Size() - 1);
        for (unsigned i = 1; i < values.Size(); ++i)
        {
            ret.ids_[i - 1] = StringHash(values[i]);
            if (cache)
                cache->StoreNameHash(values[i]);
        }
    }
    
    return ret;
}

VariantVector XMLElement::GetVariantVector() const
{
    VariantVector ret;
    
    XMLElement variantElem = GetChild("variant");
    while (variantElem)
    {
        ret.Push(variantElem.GetVariant());
        variantElem = variantElem.GetNext("variant");
    }
    
    return ret;
}

VariantMap XMLElement::GetVariantMap() const
{
    VariantMap ret;
    
    XMLElement variantElem = GetChild("variant");
    while (variantElem)
    {
        ShortStringHash key(variantElem.GetInt("hash"));
        ret[key] = variantElem.GetVariant();
        variantElem = variantElem.GetNext("variant");
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

}
