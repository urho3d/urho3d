// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../AngelScript/APITemplates.h"
#include "../IO/PackageFile.h"
#include "../Resource/Image.h"
#include "../Resource/ResourceCache.h"

namespace Urho3D
{

// bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
template <class T> bool Resource_Load_File(File* file, T* ptr)
{
    return file && ptr->Load(*file);
}

// bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
template <class T> bool Resource_Load_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->Load(buffer);
}

// virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
template <class T> bool Resource_Save_File(File* file, T* ptr)
{
    return file && ptr->Save(*file);
}

// virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
template <class T> bool Resource_Save_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->Save(buffer);
}

#define REGISTER_MEMBERS_MANUAL_PART_Resource() \
    /* bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Load(File@+)", AS_FUNCTION_OBJLAST(Resource_Load_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool Load(VectorBuffer&)", AS_FUNCTION_OBJLAST(Resource_Load_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h */ \
    engine->RegisterObjectMethod(className, "bool Save(File@+) const", AS_FUNCTION_OBJLAST(Resource_Save_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool Save(VectorBuffer&) const", AS_FUNCTION_OBJLAST(Resource_Save_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// bool XPathQuery::SetQuery(const String& queryString, const String& variableString = String::EMPTY, bool bind = true) | File: ../Resource/XMLElement.h
template <class T> bool XPathQuery_SetQuery(const String& queryString, T* ptr)
{
    return ptr->SetQuery(queryString);
}

#define REGISTER_MEMBERS_MANUAL_PART_XPathQuery() \
    /* bool XPathQuery::SetQuery(const String& queryString, const String& variableString = String::EMPTY, bool bind = true) | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "void set_query(const String&)", AS_FUNCTION_OBJLAST(XPathQuery_SetQuery<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// XMLElement XMLFile::GetRoot(const String& name = String::EMPTY) | File: ../Resource/XMLFile.h
template <class T> XMLElement XMLFile_GetRoot_Default(T* ptr)
{
    return ptr->GetRoot();
}

#define REGISTER_MEMBERS_MANUAL_PART_XMLFile() \
    /* XMLElement XMLFile::GetRoot(const String& name = String::EMPTY) | File: ../Resource/XMLFile.h */ \
    engine->RegisterObjectMethod(className, "XMLElement get_root()", AS_FUNCTION_OBJLAST(XMLFile_GetRoot_Default<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);

// XMLElement XMLElement::SelectSingle(const String& query, pugi::xpath_variable_set* variables = nullptr) const | File: ../Resource/XMLElement.h
template <class T> XMLElement XMLElement_SelectSingle(const String& query, T* ptr)
{
    return ptr->SelectSingle(query);
}

// XPathResultSet XMLElement::Select(const String& query, pugi::xpath_variable_set* variables = nullptr) const | File: ../Resource/XMLElement.h
template <class T> XPathResultSet XMLElement_Select(const String& query, T* ptr)
{
    return ptr->Select(query);
}

// bool XMLElement::SetVariantVector(const VariantVector& value) | File: ../Resource/XMLElement.h
template <class T> bool XMLElement_SetVariantVector(CScriptArray* value, T* ptr)
{
    VariantVector src;
    ArrayToVariantVector(value, src);
    return ptr->SetVariantVector(src);
}

// VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h
template <class T> CScriptArray* XMLElement_GetVariantVector(T* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

#define REGISTER_MEMBERS_MANUAL_PART_XMLElement() \
    /* XMLElement XMLElement::SelectSingle(const String& query, pugi::xpath_variable_set* variables = nullptr) const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "XMLElement SelectSingle(const String&in)", AS_FUNCTION_OBJLAST(XMLElement_SelectSingle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* XPathResultSet XMLElement::Select(const String& query, pugi::xpath_variable_set* variables = nullptr) const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "XPathResultSet Select(const String&in)", AS_FUNCTION_OBJLAST(XMLElement_Select<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool XMLElement::SetVariantVector(const VariantVector& value) | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "bool SetVariantVector(Array<Variant>@+)", AS_FUNCTION_OBJLAST(XMLElement_SetVariantVector<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h */ \
    engine->RegisterObjectMethod(className, "Array<Variant>@ GetVariantVector() const", AS_FUNCTION_OBJLAST(XMLElement_GetVariantVector<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const | File: ../Resource/ResourceCache.h
template <class T> CScriptArray* ResourceCache_GetResources(StringHash type, T* ptr)
{
    PODVector<Resource*> resources;
    ptr->GetResources(resources, type);
    return VectorToHandleArray(resources, "Array<Resource@>");
}

#define REGISTER_MEMBERS_MANUAL_PART_ResourceCache() \
    /* void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const | File: ../Resource/ResourceCache.h */ \
    engine->RegisterObjectMethod(className, "Array<Resource@>@ GetResources(StringHash)", AS_FUNCTION_OBJLAST(ResourceCache_GetResources<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

template <class T> CScriptArray* JSONValue_GetKeys(const T& jsonValue)
{
    Vector<String> keys;
    if (jsonValue.IsObject())
    {
        for (ConstJSONObjectIterator i = jsonValue.Begin(); i != jsonValue.End(); ++i)
            keys.Push(i->first_);
    }

    return VectorToArray<String>(keys, "Array<String>");
}

template <class T> CScriptArray* JSONValue_GetValues(const T& jsonValue)
{
    if (jsonValue.IsArray())
    {
        return VectorToArray<JSONValue>(jsonValue.GetArray(), "Array<JSONValue>");
    }
    else
    {
        Vector<JSONValue> values;
        if (jsonValue.IsObject())
        {
            for (ConstJSONObjectIterator i = jsonValue.Begin(); i != jsonValue.End(); ++i)
                values.Push(i->second_);
        }

        return VectorToArray<JSONValue>(values, "Array<JSONValue>");
    }
}

#define REGISTER_MEMBERS_MANUAL_PART_JSONValue() \
    engine->RegisterObjectMethod(className, "Array<String>@ get_keys() const", AS_FUNCTION_OBJLAST(JSONValue_GetKeys<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<JSONValue>@ get_values() const", AS_FUNCTION_OBJLAST(JSONValue_GetValues<T>), AS_CALL_CDECL_OBJLAST);

}
