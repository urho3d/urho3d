// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct BackgroundLoadItem | File: ../Resource/BackgroundLoader.h
void CollectMembers_BackgroundLoadItem(MemberCollection& members)
{
    // SharedPtr<Resource> BackgroundLoadItem::resource_
    // Error: type "SharedPtr<Resource>" can not automatically bind
    // HashSet<Pair<StringHash, StringHash>> BackgroundLoadItem::dependencies_
    // Error: type "HashSet<Pair<StringHash, StringHash>>" can not automatically bind
    // HashSet<Pair<StringHash, StringHash>> BackgroundLoadItem::dependents_
    // Error: type "HashSet<Pair<StringHash, StringHash>>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("bool BackgroundLoadItem::sendEventOnFailure_", "bool sendEventOnFailure", offsetof(BackgroundLoadItem, sendEventOnFailure_)));

}

// struct CompressedLevel | File: ../Resource/Image.h
void CollectMembers_CompressedLevel(MemberCollection& members)
{
    // bool CompressedLevel::Decompress(unsigned char* dest) const
    // Error: type "unsigned char*" can not automatically bind

    // unsigned char* CompressedLevel::data_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("CompressedFormat CompressedLevel::format_", "CompressedFormat format", offsetof(CompressedLevel, format_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int CompressedLevel::width_", "int width", offsetof(CompressedLevel, width_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int CompressedLevel::height_", "int height", offsetof(CompressedLevel, height_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int CompressedLevel::depth_", "int depth", offsetof(CompressedLevel, depth_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned CompressedLevel::blockSize_", "uint blockSize", offsetof(CompressedLevel, blockSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned CompressedLevel::dataSize_", "uint dataSize", offsetof(CompressedLevel, dataSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned CompressedLevel::rowSize_", "uint rowSize", offsetof(CompressedLevel, rowSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned CompressedLevel::rows_", "uint rows", offsetof(CompressedLevel, rows_)));

}

// class JSONValue | File: ../Resource/JSONValue.h
void CollectMembers_JSONValue(MemberCollection& members)
{
    // ConstJSONObjectIterator JSONValue::Begin() const
    // Error: type "ConstJSONObjectIterator" can not automatically bind
    // JSONObjectIterator JSONValue::Begin()
    // Error: type "JSONObjectIterator" can not automatically bind
    // ConstJSONObjectIterator JSONValue::End() const
    // Error: type "ConstJSONObjectIterator" can not automatically bind
    // JSONObjectIterator JSONValue::End()
    // Error: type "JSONObjectIterator" can not automatically bind
    // const JSONArray& JSONValue::GetArray() const
    // Error: type "const JSONArray&" can not automatically bind
    // const char* JSONValue::GetCString(const char* defaultValue = "") const
    // Error: type "const char*" can not automatically bind
    // const JSONObject& JSONValue::GetObject() const
    // Error: type "const JSONObject&" can not automatically bind
    // VariantVector JSONValue::GetVariantVector() const
    // Error: type "VariantVector" can not automatically bind
    // void JSONValue::SetVariantVector(const VariantVector& variantVector, Context* context = nullptr)
    // Error: type "const VariantVector&" can not automatically bind
    // JSONValue& JSONValue::operator =(const JSONArray& rhs)
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue& JSONValue::operator =(const JSONObject& rhs)
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue& JSONValue::operator =(const char* rhs)
    // Error: type "const char*" can not automatically bind

    // static JSONValueType JSONValue::GetValueTypeFromName(const char* typeName)
    // Error: type "const char*" can not automatically bind
    // static JSONNumberType JSONValue::GetNumberTypeFromName(const char* typeName)
    // Error: type "const char*" can not automatically bind

    // bool JSONValue::boolValue_
    // Not registered because have @nobind mark
    // double JSONValue::numberValue_
    // Not registered because have @nobind mark
    // String* JSONValue::stringValue_
    // Not registered because have @nobind mark
    // JSONArray* JSONValue::arrayValue_
    // Not registered because have @nobind mark
    // JSONObject* JSONValue::objectValue_
    // Not registered because have @nobind mark

    // static const JSONArray JSONValue::emptyArray
    // Error: type "const JSONArray" can not automatically bind
    // static const JSONObject JSONValue::emptyObject
    // Error: type "const JSONObject" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const JSONValue JSONValue::EMPTY", "const JSONValue EMPTY", (void*)&JSONValue::EMPTY));

}

// struct ResourceGroup | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceGroup(MemberCollection& members)
{
    // HashMap<StringHash, SharedPtr<Resource>> ResourceGroup::resources_
    // Error: type "HashMap<StringHash, SharedPtr<Resource>>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned long long ResourceGroup::memoryBudget_", "uint64 memoryBudget", offsetof(ResourceGroup, memoryBudget_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned long long ResourceGroup::memoryUse_", "uint64 memoryUse", offsetof(ResourceGroup, memoryUse_)));

}

// class XMLElement | File: ../Resource/XMLElement.h
void CollectMembers_XMLElement(MemberCollection& members)
{
    // XMLElement XMLElement::CreateChild(const char* name)
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttribute(const char* name) const
    // Error: type "const char*" can not automatically bind
    // const char* XMLElement::GetAttributeCString(const char* name) const
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttributeLower(const char* name) const
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttributeUpper(const char* name) const
    // Error: type "const char*" can not automatically bind
    // PODVector<unsigned char> XMLElement::GetBuffer(const String& name) const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool XMLElement::GetBuffer(const String& name, void* dest, unsigned size) const
    // Error: type "void*" can not automatically bind
    // XMLElement XMLElement::GetChild(const char* name) const
    // Error: type "const char*" can not automatically bind
    // XMLElement XMLElement::GetNext(const char* name) const
    // Error: type "const char*" can not automatically bind
    // pugi::xml_node_struct* XMLElement::GetNode() const
    // Error: type "pugi::xml_node_struct*" can not automatically bind
    // XMLElement XMLElement::GetOrCreateChild(const char* name)
    // Error: type "const char*" can not automatically bind
    // VariantVector XMLElement::GetVariantVector() const
    // Error: type "VariantVector" can not automatically bind
    // const pugi::xpath_node* XMLElement::GetXPathNode() const
    // Error: type "const pugi::xpath_node*" can not automatically bind
    // const XPathResultSet* XMLElement::GetXPathResultSet() const
    // Error: type "const XPathResultSet*" can not automatically bind
    // bool XMLElement::HasAttribute(const char* name) const
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::HasChild(const char* name) const
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveAttribute(const char* name)
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChild(const char* name)
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChildren(const char* name)
    // Error: type "const char*" can not automatically bind
    // XPathResultSet XMLElement::Select(const String& query, pugi::xpath_variable_set* variables = nullptr) const
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // XMLElement XMLElement::SelectSingle(const String& query, pugi::xpath_variable_set* variables = nullptr) const
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // bool XMLElement::SetAttribute(const char* name, const char* value)
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetAttribute(const char* value)
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetBuffer(const String& name, const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool XMLElement::SetBuffer(const String& name, const void* data, unsigned size)
    // Error: type "const void*" can not automatically bind
    // bool XMLElement::SetValue(const char* value)
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetVariantVector(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const XMLElement XMLElement::EMPTY", "const XMLElement EMPTY", (void*)&XMLElement::EMPTY));

}

// class XPathQuery | File: ../Resource/XMLElement.h
void CollectMembers_XPathQuery(MemberCollection& members)
{
    // pugi::xpath_query* XPathQuery::GetXPathQuery() const
    // Error: type "pugi::xpath_query*" can not automatically bind
    // pugi::xpath_variable_set* XPathQuery::GetXPathVariableSet() const
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // bool XPathQuery::SetVariable(const char* name, const char* value)
    // Error: type "const char*" can not automatically bind

}

// class XPathResultSet | File: ../Resource/XMLElement.h
void CollectMembers_XPathResultSet(MemberCollection& members)
{
    // pugi::xpath_node_set* XPathResultSet::GetXPathNodeSet() const
    // Error: type "pugi::xpath_node_set*" can not automatically bind

}

// class BackgroundLoader | File: ../Resource/BackgroundLoader.h
void CollectMembers_BackgroundLoader(MemberCollection& members)
{
    CollectMembers_RefCounted(members);
    CollectMembers_Thread(members);

    Remove(members.methods_, "virtual void Thread::ThreadFunction() = 0");

}

// class Localization | File: ../Resource/Localization.h
void CollectMembers_Localization(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class Resource | File: ../Resource/Resource.h
void CollectMembers_Resource(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class ResourceCache | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceCache(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void ResourceCache::AddResourceRouter(ResourceRouter* router, bool addAsFirst = false)
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // const HashMap<StringHash, ResourceGroup>& ResourceCache::GetAllResources() const
    // Error: type "const HashMap<StringHash, ResourceGroup>&" can not automatically bind
    // ResourceRouter* ResourceCache::GetResourceRouter(unsigned index) const
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const
    // Error: type "PODVector<Resource*>&" can not automatically bind
    // void ResourceCache::RemoveResourceRouter(ResourceRouter* router)
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark

    // template <class T> bool ResourceCache::BackgroundLoadResource(const String& name, bool sendEventOnFailure = true, Resource* caller = nullptr)
    // Not registered because template
    // template <class T> T* ResourceCache::GetExistingResource(const String& name)
    // Not registered because template
    // template <class T> T* ResourceCache::GetResource(const String& name, bool sendEventOnFailure = true)
    // Not registered because template
    // template <class T> void ResourceCache::GetResources(PODVector<T*>& result) const
    // Not registered because template
    // template <class T> SharedPtr<T> ResourceCache::GetTempResource(const String& name, bool sendEventOnFailure = true)
    // Not registered because template
    // template <class T> void ResourceCache::ReleaseResource(const String& name, bool force = false)
    // Not registered because template

}

// class ResourceRouter | File: ../Resource/ResourceCache.h
void CollectMembers_ResourceRouter(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class Image | File: ../Resource/Image.h
void CollectMembers_Image(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");
    Remove(members.methods_, "virtual bool Resource::SaveFile(const String& fileName) const");

    // unsigned char* Image::GetData() const
    // Error: type "unsigned char*" can not automatically bind
    // void Image::GetLevels(PODVector<Image*>& levels)
    // Error: type "PODVector<Image*>&" can not automatically bind
    // void Image::GetLevels(PODVector<const Image*>& levels) const
    // Error: type "PODVector<const Image*>&" can not automatically bind
    // SDL_Surface* Image::GetSDLSurface(const IntRect& rect = IntRect::ZERO) const
    // Error: type "SDL_Surface*" can not automatically bind
    // void Image::SetData(const unsigned char* pixelData)
    // Error: type "const unsigned char*" can not automatically bind

    // static void Image::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class JSONFile | File: ../Resource/JSONFile.h
void CollectMembers_JSONFile(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // static void JSONFile::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class ResourceWithMetadata | File: ../Resource/Resource.h
void CollectMembers_ResourceWithMetadata(MemberCollection& members)
{
    CollectMembers_Resource(members);

}

// class XMLFile | File: ../Resource/XMLFile.h
void CollectMembers_XMLFile(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // pugi::xml_document* XMLFile::GetDocument() const
    // Error: type "pugi::xml_document*" can not automatically bind

    // static void XMLFile::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

} // namespace Urho3D
