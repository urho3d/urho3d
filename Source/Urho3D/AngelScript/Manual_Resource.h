//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Resource/ResourceCache.h"
#include "../IO/PackageFile.h"

namespace Urho3D
{

// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
bool ResourceLoad(File* file, Resource* ptr);
// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
bool ResourceLoadVectorBuffer(VectorBuffer& buffer, Resource* ptr);
// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
bool ResourceSave(File* file, Resource* ptr);
// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
bool ResourceSaveVectorBuffer(VectorBuffer& buffer, Resource* ptr);

// TODO bool Load(File@+), bool Load(VectorBuffer&) наверно не нужны, когда есть Lead(Deserializer) - зарегать как дочерний класс если вомзожно

#define REGISTER_MANUAL_PART_Resource(T, className) \
    /* bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Load(File@+)", asFUNCTION(ResourceLoad), asCALL_CDECL_OBJLAST); \
    /* bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Load(VectorBuffer&)", asFUNCTION(ResourceLoadVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Save(File@+) const", asFUNCTION(ResourceSave), asCALL_CDECL_OBJLAST); \
    /* virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Save(VectorBuffer&) const", asFUNCTION(ResourceSaveVectorBuffer), asCALL_CDECL_OBJLAST);

// ========================================================================================

// bool XPathQuery::SetQuery(const String &queryString, const String &variableString=String::EMPTY, bool bind=true) | File: ../Resource/XMLElement.h
bool XPathQuery_SetQuery(const String& queryString, XPathQuery* ptr);

#define REGISTER_MANUAL_PART_XPathQuery(T, className) \
    /* bool XPathQuery::SetQuery(const String &queryString, const String &variableString=String::EMPTY, bool bind=true) | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "void set_query(const String&)", asFUNCTION(XPathQuery_SetQuery), asCALL_CDECL_OBJLAST);

// ========================================================================================

// XMLElement XMLFile::GetRoot(const String &name=String::EMPTY) | File: ../Resource/XMLFile.h
XMLElement XMLFileGetRootDefault(XMLFile* ptr);

#define REGISTER_MANUAL_PART_XMLFile(T, className) \
    /* XMLElement XMLFile::GetRoot(const String &name=String::EMPTY) | File: ../Resource/XMLFile.h */ \
    engine->RegisterObjectMethod(className, "XMLElement get_root()", asFUNCTION(XMLFileGetRootDefault), asCALL_CDECL_OBJLAST);

// ========================================================================================

// XMLElement XMLElement::SelectSingle(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h
XMLElement XMLElement_SelectSingle(const String& query, XMLElement* ptr);
// XPathResultSet XMLElement::Select(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h
XPathResultSet XMLElement_Select(const String& query, XMLElement* ptr);
// bool XMLElement::SetVariantVector(const VariantVector &value) | File: ../Resource/XMLElement.h
bool XMLElementSetVariantVector(CScriptArray* value, XMLElement* ptr);
// VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h
CScriptArray* XMLElementGetVariantVector(XMLElement* ptr);

#define REGISTER_MANUAL_PART_XMLElement(T, className) \
    /* XMLElement XMLElement::SelectSingle(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "XMLElement SelectSingle(const String&in)", asFUNCTION(XMLElement_SelectSingle), asCALL_CDECL_OBJLAST); \
    /* XPathResultSet XMLElement::Select(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "XPathResultSet Select(const String&in)", asFUNCTION(XMLElement_Select), asCALL_CDECL_OBJLAST); \
    /* bool XMLElement::SetVariantVector(const VariantVector &value) | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "bool SetVariantVector(Array<Variant>@+)", asFUNCTION(XMLElementSetVariantVector), asCALL_CDECL_OBJLAST); \
    /* VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "Array<Variant>@ GetVariantVector() const", asFUNCTION(XMLElementGetVariantVector), asCALL_CDECL_OBJLAST);

// ========================================================================================

// void ResourceCache::GetResources(PODVector< Resource * > &result, StringHash type) const | File: ../Resource/ResourceCache.h
CScriptArray* ResourceCacheGetResources(StringHash type, ResourceCache* ptr);

#define REGISTER_MANUAL_PART_ResourceCache(T, className) \
    /* void ResourceCache::GetResources(PODVector< Resource * > &result, StringHash type) const | File: ../Resource/ResourceCache.h */ \
    engine->RegisterObjectMethod(className, "Array<Resource@>@ GetResources(StringHash)", asFUNCTION(ResourceCacheGetResources), asCALL_CDECL_OBJLAST);

// ========================================================================================

CScriptArray* JSONValueGetKeys(const JSONValue& jsonValue);
CScriptArray* JSONValueGetValues(const JSONValue& jsonValue);

#define REGISTER_MANUAL_PART_JSONValue(T, className) \
    engine->RegisterObjectMethod(className, "Array<String>@ get_keys() const", asFUNCTION(JSONValueGetKeys), asCALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<JSONValue>@ get_values() const", asFUNCTION(JSONValueGetValues), asCALL_CDECL_OBJLAST);

}
