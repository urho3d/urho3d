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

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Resource.h"

#include "../Resource/ResourceCache.h"
#include "../Resource/Localization.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Resource(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static ResourceCache* GetResourceCache()
{
    return GetScriptContext()->GetSubsystem<ResourceCache>();
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Localization* GetLocalization()
{
    return GetScriptContext()->GetSubsystem<Localization>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Resource(asIScriptEngine* engine)
{
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Localization@+ get_localization()", asFUNCTION(GetLocalization), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
}

// ========================================================================================

// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
bool ResourceLoad(File* file, Resource* ptr)
{
    return file && ptr->Load(*file);
}

// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
bool ResourceLoadVectorBuffer(VectorBuffer& buffer, Resource* ptr)
{
    return ptr->Load(buffer);
}

// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
bool ResourceSave(File* file, Resource* ptr)
{
    return file && ptr->Save(*file);
}

// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
bool ResourceSaveVectorBuffer(VectorBuffer& buffer, Resource* ptr)
{
    return ptr->Save(buffer);
}

// ========================================================================================

// bool XPathQuery::SetQuery(const String &queryString, const String &variableString=String::EMPTY, bool bind=true) | File: ../Resource/XMLElement.h
bool XPathQuery_SetQuery(const String& queryString, XPathQuery* ptr)
{
    return ptr->SetQuery(queryString);
}

// ========================================================================================

// XMLElement XMLFile::GetRoot(const String &name=String::EMPTY) | File: ../Resource/XMLFile.h
XMLElement XMLFileGetRootDefault(XMLFile* ptr)
{
    return ptr->GetRoot();
}

// ========================================================================================

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);

// XMLElement XMLElement::SelectSingle(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h
XMLElement XMLElement_SelectSingle(const String& query, XMLElement* ptr)
{
    return ptr->SelectSingle(query);
}

// XPathResultSet XMLElement::Select(const String &query, pugi::xpath_variable_set *variables=nullptr) const | File: ../Resource/XMLElement.h
XPathResultSet XMLElement_Select(const String& query, XMLElement* ptr)
{
    return ptr->Select(query);
}

// bool XMLElement::SetVariantVector(const VariantVector &value) | File: ../Resource/XMLElement.h
bool XMLElementSetVariantVector(CScriptArray* value, XMLElement* ptr)
{
    VariantVector src;
    ArrayToVariantVector(value, src);
    return ptr->SetVariantVector(src);
}

// VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h
CScriptArray* XMLElementGetVariantVector(XMLElement* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

// ========================================================================================

// void ResourceCache::GetResources(PODVector< Resource * > &result, StringHash type) const | File: ../Resource/ResourceCache.h
CScriptArray* ResourceCacheGetResources(StringHash type, ResourceCache* ptr)
{
    PODVector<Resource*> resources;
    ptr->GetResources(resources, type);
    return VectorToHandleArray(resources, "Array<Resource@>");
}

// ========================================================================================

// void JSONValue::SetVariant(const Variant &variant, Context *context=nullptr) | File: ../Resource/JSONValue.h
void JSONValueSetVariant(const Variant& variant, JSONValue& jsonValue)
{
    jsonValue.SetVariant(variant, GetScriptContext());
}

// void JSONValue::SetVariantMap(const VariantMap &variantMap, Context *context=nullptr) | File: ../Resource/JSONValue.h
void JSONValueSetVariantMap(const VariantMap& variantMap, JSONValue& jsonValue)
{
    jsonValue.SetVariantMap(variantMap, GetScriptContext());
}

CScriptArray* JSONValueGetKeys(const JSONValue& jsonValue)
{
    Vector<String> keys;
    if (jsonValue.IsObject())
    {
        for (ConstJSONObjectIterator i = jsonValue.Begin(); i != jsonValue.End(); ++i)
            keys.Push(i->first_);
    }

    return VectorToArray<String>(keys, "Array<String>");
}

CScriptArray* JSONValueGetValues(const JSONValue& jsonValue)
{
    if (jsonValue.IsArray())
        return VectorToArray<JSONValue>(jsonValue.GetArray(), "Array<JSONValue>");
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

}
