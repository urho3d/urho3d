// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// Vector<String> XMLElement::GetAttributeNames() const | File: ../Resource/XMLElement.h
static CScriptArray* XMLElement_GetAttributeNames_void(XMLElement* ptr)
{
    Vector<String> result = ptr->GetAttributeNames();
    return VectorToArray<String>(result, "Array<String>");
}

// StringVector XMLElement::GetStringVector() const | File: ../Resource/XMLElement.h
static CScriptArray* XMLElement_GetStringVector_void(XMLElement* ptr)
{
    StringVector result = ptr->GetStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// bool XMLElement::SetStringVector(const StringVector& value) | File: ../Resource/XMLElement.h
static bool XMLElement_SetStringVector_StringVector(XMLElement* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->SetStringVector(value);
    return result;
}

// XMLElement::XMLElement(const XMLElement& rhs) | File: ../Resource/XMLElement.h
static void XMLElement_XMLElement_XMLElement(XMLElement* ptr, const XMLElement &rhs)
{
    new(ptr) XMLElement(rhs);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void XMLFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(XMLFile* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit XMLFile::XMLFile(Context* context) | File: ../Resource/XMLFile.h
static XMLFile* XMLFile_XMLFile_Context()
{
    return new XMLFile(GetScriptContext());
}

// explicit XPathQuery::XPathQuery(const String& queryString, const String& variableString=String::EMPTY) | File: ../Resource/XMLElement.h
static void XPathQuery_XPathQuery_String_String(XPathQuery* ptr, const String &queryString, const String &variableString=String::EMPTY)
{
    new(ptr) XPathQuery(queryString, variableString);
}

// XPathResultSet::XPathResultSet(const XPathResultSet& rhs) | File: ../Resource/XMLElement.h
static void XPathResultSet_XPathResultSet_XPathResultSet(XPathResultSet* ptr, const XPathResultSet &rhs)
{
    new(ptr) XPathResultSet(rhs);
}

void ASRegisterGenerated_Members_X(asIScriptEngine* engine)
{
    // const XMLElement XMLElement::EMPTY | File: ../Resource/XMLElement.h
    engine->SetDefaultNamespace("XMLElement");
    engine->RegisterGlobalProperty("const XMLElement EMPTY", (void*)&XMLElement::EMPTY);
    engine->SetDefaultNamespace("");
    // bool XMLElement::AppendChild(XMLElement element, bool asCopy=false) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool AppendChild(XMLElement, bool = false)", asMETHODPR(XMLElement, AppendChild, (XMLElement, bool), bool), asCALL_THISCALL);
    // XMLElement XMLElement::CreateChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement CreateChild(const String&in)", asMETHODPR(XMLElement, CreateChild, (const String&), XMLElement), asCALL_THISCALL);
    // XMLElement XMLElement::CreateChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttribute(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttribute(const String&in = String::EMPTY) const", asMETHODPR(XMLElement, GetAttribute, (const String&) const, String), asCALL_THISCALL);
    // String XMLElement::GetAttribute(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // const char* XMLElement::GetAttributeCString(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttributeLower(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeLower(const String&in) const", asMETHODPR(XMLElement, GetAttributeLower, (const String&) const, String), asCALL_THISCALL);
    // String XMLElement::GetAttributeLower(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // Vector<String> XMLElement::GetAttributeNames() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Array<String>@ GetAttributeNames() const", asFUNCTION(XMLElement_GetAttributeNames_void), asCALL_CDECL_OBJFIRST);
    // String XMLElement::GetAttributeUpper(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeUpper(const String&in) const", asMETHODPR(XMLElement, GetAttributeUpper, (const String&) const, String), asCALL_THISCALL);
    // String XMLElement::GetAttributeUpper(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::GetBool(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool GetBool(const String&in) const", asMETHODPR(XMLElement, GetBool, (const String&) const, bool), asCALL_THISCALL);
    // BoundingBox XMLElement::GetBoundingBox() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "BoundingBox GetBoundingBox() const", asMETHODPR(XMLElement, GetBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> XMLElement::GetBuffer(const String& name) const | File: ../Resource/XMLElement.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool XMLElement::GetBuffer(const String& name, void* dest, unsigned size) const | File: ../Resource/XMLElement.h
    // Error: type "void*" can not automatically bind
    // XMLElement XMLElement::GetChild(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetChild(const String&in = String::EMPTY) const", asMETHODPR(XMLElement, GetChild, (const String&) const, XMLElement), asCALL_THISCALL);
    // XMLElement XMLElement::GetChild(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // Color XMLElement::GetColor(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Color GetColor(const String&in) const", asMETHODPR(XMLElement, GetColor, (const String&) const, Color), asCALL_THISCALL);
    // double XMLElement::GetDouble(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "double GetDouble(const String&in) const", asMETHODPR(XMLElement, GetDouble, (const String&) const, double), asCALL_THISCALL);
    // XMLFile* XMLElement::GetFile() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ GetFile() const", asMETHODPR(XMLElement, GetFile, () const, XMLFile*), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ get_file() const", asMETHODPR(XMLElement, GetFile, () const, XMLFile*), asCALL_THISCALL);
    // float XMLElement::GetFloat(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "float GetFloat(const String&in) const", asMETHODPR(XMLElement, GetFloat, (const String&) const, float), asCALL_THISCALL);
    // int XMLElement::GetInt(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "int GetInt(const String&in) const", asMETHODPR(XMLElement, GetInt, (const String&) const, int), asCALL_THISCALL);
    // long long XMLElement::GetInt64(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "int64 GetInt64(const String&in) const", asMETHODPR(XMLElement, GetInt64, (const String&) const, long long), asCALL_THISCALL);
    // IntRect XMLElement::GetIntRect(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntRect GetIntRect(const String&in) const", asMETHODPR(XMLElement, GetIntRect, (const String&) const, IntRect), asCALL_THISCALL);
    // IntVector2 XMLElement::GetIntVector2(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntVector2 GetIntVector2(const String&in) const", asMETHODPR(XMLElement, GetIntVector2, (const String&) const, IntVector2), asCALL_THISCALL);
    // IntVector3 XMLElement::GetIntVector3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntVector3 GetIntVector3(const String&in) const", asMETHODPR(XMLElement, GetIntVector3, (const String&) const, IntVector3), asCALL_THISCALL);
    // Matrix3 XMLElement::GetMatrix3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix3 GetMatrix3(const String&in) const", asMETHODPR(XMLElement, GetMatrix3, (const String&) const, Matrix3), asCALL_THISCALL);
    // Matrix3x4 XMLElement::GetMatrix3x4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix3x4 GetMatrix3x4(const String&in) const", asMETHODPR(XMLElement, GetMatrix3x4, (const String&) const, Matrix3x4), asCALL_THISCALL);
    // Matrix4 XMLElement::GetMatrix4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix4 GetMatrix4(const String&in) const", asMETHODPR(XMLElement, GetMatrix4, (const String&) const, Matrix4), asCALL_THISCALL);
    // String XMLElement::GetName() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetName() const", asMETHODPR(XMLElement, GetName, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_name() const", asMETHODPR(XMLElement, GetName, () const, String), asCALL_THISCALL);
    // XMLElement XMLElement::GetNext(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetNext(const String&in = String::EMPTY) const", asMETHODPR(XMLElement, GetNext, (const String&) const, XMLElement), asCALL_THISCALL);
    // XMLElement XMLElement::GetNext(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // pugi::xml_node_struct* XMLElement::GetNode() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xml_node_struct*" can not automatically bind
    // unsigned XMLElement::GetNumAttributes() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetNumAttributes() const", asMETHODPR(XMLElement, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint get_numAttributes() const", asMETHODPR(XMLElement, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // XMLElement XMLElement::GetOrCreateChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetOrCreateChild(const String&in)", asMETHODPR(XMLElement, GetOrCreateChild, (const String&), XMLElement), asCALL_THISCALL);
    // XMLElement XMLElement::GetOrCreateChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // XMLElement XMLElement::GetParent() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetParent() const", asMETHODPR(XMLElement, GetParent, () const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_parent() const", asMETHODPR(XMLElement, GetParent, () const, XMLElement), asCALL_THISCALL);
    // Quaternion XMLElement::GetQuaternion(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Quaternion GetQuaternion(const String&in) const", asMETHODPR(XMLElement, GetQuaternion, (const String&) const, Quaternion), asCALL_THISCALL);
    // Rect XMLElement::GetRect(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Rect GetRect(const String&in) const", asMETHODPR(XMLElement, GetRect, (const String&) const, Rect), asCALL_THISCALL);
    // ResourceRef XMLElement::GetResourceRef() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "ResourceRef GetResourceRef() const", asMETHODPR(XMLElement, GetResourceRef, () const, ResourceRef), asCALL_THISCALL);
    // ResourceRefList XMLElement::GetResourceRefList() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "ResourceRefList GetResourceRefList() const", asMETHODPR(XMLElement, GetResourceRefList, () const, ResourceRefList), asCALL_THISCALL);
    // StringVector XMLElement::GetStringVector() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Array<String>@ GetStringVector() const", asFUNCTION(XMLElement_GetStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned XMLElement::GetUInt(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetUInt(const String&in) const", asMETHODPR(XMLElement, GetUInt, (const String&) const, unsigned), asCALL_THISCALL);
    // unsigned long long XMLElement::GetUInt64(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint64 GetUInt64(const String&in) const", asMETHODPR(XMLElement, GetUInt64, (const String&) const, unsigned long long), asCALL_THISCALL);
    // String XMLElement::GetValue() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetValue() const", asMETHODPR(XMLElement, GetValue, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_value() const", asMETHODPR(XMLElement, GetValue, () const, String), asCALL_THISCALL);
    // Variant XMLElement::GetVariant() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVariant() const", asMETHODPR(XMLElement, GetVariant, () const, Variant), asCALL_THISCALL);
    // VariantMap XMLElement::GetVariantMap() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "VariantMap GetVariantMap() const", asMETHODPR(XMLElement, GetVariantMap, () const, VariantMap), asCALL_THISCALL);
    // Variant XMLElement::GetVariantValue(VariantType type) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVariantValue(VariantType) const", asMETHODPR(XMLElement, GetVariantValue, (VariantType) const, Variant), asCALL_THISCALL);
    // VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h
    // Error: type "VariantVector" can not automatically bind
    // Vector4 XMLElement::GetVector(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector4 GetVector(const String&in) const", asMETHODPR(XMLElement, GetVector, (const String&) const, Vector4), asCALL_THISCALL);
    // Vector2 XMLElement::GetVector2(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector2 GetVector2(const String&in) const", asMETHODPR(XMLElement, GetVector2, (const String&) const, Vector2), asCALL_THISCALL);
    // Vector3 XMLElement::GetVector3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector3 GetVector3(const String&in) const", asMETHODPR(XMLElement, GetVector3, (const String&) const, Vector3), asCALL_THISCALL);
    // Vector4 XMLElement::GetVector4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector4 GetVector4(const String&in) const", asMETHODPR(XMLElement, GetVector4, (const String&) const, Vector4), asCALL_THISCALL);
    // Variant XMLElement::GetVectorVariant(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVectorVariant(const String&in) const", asMETHODPR(XMLElement, GetVectorVariant, (const String&) const, Variant), asCALL_THISCALL);
    // const pugi::xpath_node* XMLElement::GetXPathNode() const | File: ../Resource/XMLElement.h
    // Error: type "const pugi::xpath_node*" can not automatically bind
    // unsigned XMLElement::GetXPathResultIndex() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetXPathResultIndex() const", asMETHODPR(XMLElement, GetXPathResultIndex, () const, unsigned), asCALL_THISCALL);
    // const XPathResultSet* XMLElement::GetXPathResultSet() const | File: ../Resource/XMLElement.h
    // Error: type "const XPathResultSet*" can not automatically bind
    // bool XMLElement::HasAttribute(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool HasAttribute(const String&in) const", asMETHODPR(XMLElement, HasAttribute, (const String&) const, bool), asCALL_THISCALL);
    // bool XMLElement::HasAttribute(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::HasChild(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool HasChild(const String&in) const", asMETHODPR(XMLElement, HasChild, (const String&) const, bool), asCALL_THISCALL);
    // bool XMLElement::HasChild(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::IsNull() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool IsNull() const", asMETHODPR(XMLElement, IsNull, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_isNull() const", asMETHODPR(XMLElement, IsNull, () const, bool), asCALL_THISCALL);
    // XMLElement XMLElement::NextResult() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement NextResult() const", asMETHODPR(XMLElement, NextResult, () const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_nextResult() const", asMETHODPR(XMLElement, NextResult, () const, XMLElement), asCALL_THISCALL);
    // bool XMLElement::NotNull() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool NotNull() const", asMETHODPR(XMLElement, NotNull, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_notNull() const", asMETHODPR(XMLElement, NotNull, () const, bool), asCALL_THISCALL);
    // explicit XMLElement::operator bool() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool opConv() const", asMETHODPR(XMLElement, operator bool, () const, bool), asCALL_THISCALL);
    // XMLElement& XMLElement::operator=(const XMLElement& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement& opAssign(const XMLElement&in)", asMETHODPR(XMLElement, operator=, (const XMLElement&), XMLElement&), asCALL_THISCALL);
    // bool XMLElement::Remove() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool Remove()", asMETHODPR(XMLElement, Remove, (), bool), asCALL_THISCALL);
    // bool XMLElement::RemoveAttribute(const String& name=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveAttribute(const String&in = String::EMPTY)", asMETHODPR(XMLElement, RemoveAttribute, (const String&), bool), asCALL_THISCALL);
    // bool XMLElement::RemoveAttribute(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChild(const XMLElement& element) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const XMLElement&in)", asMETHODPR(XMLElement, RemoveChild, (const XMLElement&), bool), asCALL_THISCALL);
    // bool XMLElement::RemoveChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const String&in)", asMETHODPR(XMLElement, RemoveChild, (const String&), bool), asCALL_THISCALL);
    // bool XMLElement::RemoveChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChildren(const String& name=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChildren(const String&in = String::EMPTY)", asMETHODPR(XMLElement, RemoveChildren, (const String&), bool), asCALL_THISCALL);
    // bool XMLElement::RemoveChildren(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // XPathResultSet XMLElement::Select(const String& query, pugi::xpath_variable_set* variables=nullptr) const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // XPathResultSet XMLElement::SelectPrepared(const XPathQuery& query) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XPathResultSet SelectPrepared(const XPathQuery&in) const", asMETHODPR(XMLElement, SelectPrepared, (const XPathQuery&) const, XPathResultSet), asCALL_THISCALL);
    // XMLElement XMLElement::SelectSingle(const String& query, pugi::xpath_variable_set* variables=nullptr) const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // XMLElement XMLElement::SelectSinglePrepared(const XPathQuery& query) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement SelectSinglePrepared(const XPathQuery&in) const", asMETHODPR(XMLElement, SelectSinglePrepared, (const XPathQuery&) const, XMLElement), asCALL_THISCALL);
    // bool XMLElement::SetAttribute(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in, const String&in)", asMETHODPR(XMLElement, SetAttribute, (const String&, const String&), bool), asCALL_THISCALL);
    // bool XMLElement::SetAttribute(const char* name, const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetAttribute(const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in)", asMETHODPR(XMLElement, SetAttribute, (const String&), bool), asCALL_THISCALL);
    // bool XMLElement::SetAttribute(const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetBool(const String& name, bool value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetBool(const String&in, bool)", asMETHODPR(XMLElement, SetBool, (const String&, bool), bool), asCALL_THISCALL);
    // bool XMLElement::SetBoundingBox(const BoundingBox& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetBoundingBox(const BoundingBox&in)", asMETHODPR(XMLElement, SetBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool XMLElement::SetBuffer(const String& name, const void* data, unsigned size) | File: ../Resource/XMLElement.h
    // Error: type "const void*" can not automatically bind
    // bool XMLElement::SetBuffer(const String& name, const PODVector<unsigned char>& value) | File: ../Resource/XMLElement.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool XMLElement::SetColor(const String& name, const Color& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetColor(const String&in, const Color&in)", asMETHODPR(XMLElement, SetColor, (const String&, const Color&), bool), asCALL_THISCALL);
    // bool XMLElement::SetDouble(const String& name, double value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetDouble(const String&in, double)", asMETHODPR(XMLElement, SetDouble, (const String&, double), bool), asCALL_THISCALL);
    // bool XMLElement::SetFloat(const String& name, float value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetFloat(const String&in, float)", asMETHODPR(XMLElement, SetFloat, (const String&, float), bool), asCALL_THISCALL);
    // bool XMLElement::SetInt(const String& name, int value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetInt(const String&in, int)", asMETHODPR(XMLElement, SetInt, (const String&, int), bool), asCALL_THISCALL);
    // bool XMLElement::SetInt64(const String& name, long long value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetInt64(const String&in, int64)", asMETHODPR(XMLElement, SetInt64, (const String&, long long), bool), asCALL_THISCALL);
    // bool XMLElement::SetIntRect(const String& name, const IntRect& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntRect(const String&in, const IntRect&in)", asMETHODPR(XMLElement, SetIntRect, (const String&, const IntRect&), bool), asCALL_THISCALL);
    // bool XMLElement::SetIntVector2(const String& name, const IntVector2& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntVector2(const String&in, const IntVector2&in)", asMETHODPR(XMLElement, SetIntVector2, (const String&, const IntVector2&), bool), asCALL_THISCALL);
    // bool XMLElement::SetIntVector3(const String& name, const IntVector3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntVector3(const String&in, const IntVector3&in)", asMETHODPR(XMLElement, SetIntVector3, (const String&, const IntVector3&), bool), asCALL_THISCALL);
    // bool XMLElement::SetMatrix3(const String& name, const Matrix3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3(const String&in, const Matrix3&in)", asMETHODPR(XMLElement, SetMatrix3, (const String&, const Matrix3&), bool), asCALL_THISCALL);
    // bool XMLElement::SetMatrix3x4(const String& name, const Matrix3x4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3x4(const String&in, const Matrix3x4&in)", asMETHODPR(XMLElement, SetMatrix3x4, (const String&, const Matrix3x4&), bool), asCALL_THISCALL);
    // bool XMLElement::SetMatrix4(const String& name, const Matrix4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix4(const String&in, const Matrix4&in)", asMETHODPR(XMLElement, SetMatrix4, (const String&, const Matrix4&), bool), asCALL_THISCALL);
    // bool XMLElement::SetQuaternion(const String& name, const Quaternion& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetQuaternion(const String&in, const Quaternion&in)", asMETHODPR(XMLElement, SetQuaternion, (const String&, const Quaternion&), bool), asCALL_THISCALL);
    // bool XMLElement::SetRect(const String& name, const Rect& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetRect(const String&in, const Rect&in)", asMETHODPR(XMLElement, SetRect, (const String&, const Rect&), bool), asCALL_THISCALL);
    // bool XMLElement::SetResourceRef(const ResourceRef& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRef(const ResourceRef&in)", asMETHODPR(XMLElement, SetResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool XMLElement::SetResourceRefList(const ResourceRefList& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRefList(const ResourceRefList&in)", asMETHODPR(XMLElement, SetResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool XMLElement::SetString(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetString(const String&in, const String&in)", asMETHODPR(XMLElement, SetString, (const String&, const String&), bool), asCALL_THISCALL);
    // bool XMLElement::SetStringVector(const StringVector& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetStringVector(Array<String>@+)", asFUNCTION(XMLElement_SetStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool XMLElement::SetUInt(const String& name, unsigned value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt(const String&in, uint)", asMETHODPR(XMLElement, SetUInt, (const String&, unsigned), bool), asCALL_THISCALL);
    // bool XMLElement::SetUInt64(const String& name, unsigned long long value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt64(const String&in, uint64)", asMETHODPR(XMLElement, SetUInt64, (const String&, unsigned long long), bool), asCALL_THISCALL);
    // bool XMLElement::SetValue(const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetValue(const String&in)", asMETHODPR(XMLElement, SetValue, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool set_value(const String&in)", asMETHODPR(XMLElement, SetValue, (const String&), bool), asCALL_THISCALL);
    // bool XMLElement::SetValue(const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetVariant(const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariant(const Variant&in)", asMETHODPR(XMLElement, SetVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVariantMap(const VariantMap& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantMap(const VariantMap&in)", asMETHODPR(XMLElement, SetVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVariantValue(const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantValue(const Variant&in)", asMETHODPR(XMLElement, SetVariantValue, (const Variant&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVariantVector(const VariantVector& value) | File: ../Resource/XMLElement.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool XMLElement::SetVector2(const String& name, const Vector2& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector2(const String&in, const Vector2&in)", asMETHODPR(XMLElement, SetVector2, (const String&, const Vector2&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVector3(const String& name, const Vector3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector3(const String&in, const Vector3&in)", asMETHODPR(XMLElement, SetVector3, (const String&, const Vector3&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVector4(const String& name, const Vector4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector4(const String&in, const Vector4&in)", asMETHODPR(XMLElement, SetVector4, (const String&, const Vector4&), bool), asCALL_THISCALL);
    // bool XMLElement::SetVectorVariant(const String& name, const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVectorVariant(const String&in, const Variant&in)", asMETHODPR(XMLElement, SetVectorVariant, (const String&, const Variant&), bool), asCALL_THISCALL);
    // XMLElement::XMLElement(XMLFile* file, pugi::xml_node_struct* node) | File: ../Resource/XMLElement.h
    // Error: type "pugi::xml_node_struct*" can not automatically bind
    // XMLElement::XMLElement(XMLFile* file, const XPathResultSet* resultSet, const pugi::xpath_node* xpathNode, unsigned xpathResultIndex) | File: ../Resource/XMLElement.h
    // Error: type "const XPathResultSet*" can not automatically bind
    // XMLElement::XMLElement(const XMLElement& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement&in)", asFUNCTION(XMLElement_XMLElement_XMLElement), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_XMLElement
    REGISTER_MANUAL_PART_XMLElement(XMLElement, "XMLElement")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_ADDREF, "void f()", asMETHODPR(XMLFile, AddRef, (), void), asCALL_THISCALL);
    // bool XMLFile::BeginLoad(Deserializer& source) override | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool BeginLoad(Deserializer&)", asMETHODPR(XMLFile, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // XMLElement XMLFile::CreateRoot(const String& name) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement CreateRoot(const String&in)", asMETHODPR(XMLFile, CreateRoot, (const String&), XMLElement), asCALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool EndLoad()", asMETHODPR(XMLFile, EndLoad, (), bool), asCALL_THISCALL);
    // bool XMLFile::FromString(const String& source) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool FromString(const String&in)", asMETHODPR(XMLFile, FromString, (const String&), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(XMLFile, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool GetBlockEvents() const", asMETHODPR(XMLFile, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetCategory() const", asMETHODPR(XMLFile, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_category() const", asMETHODPR(XMLFile, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // pugi::xml_document* XMLFile::GetDocument() const | File: ../Resource/XMLFile.h
    // Error: type "pugi::xml_document*" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "VariantMap& GetEventDataMap() const", asMETHODPR(XMLFile, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "Object@+ GetEventSender() const", asMETHODPR(XMLFile, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(XMLFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const Variant& get_globalVar(StringHash) const", asMETHODPR(XMLFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const VariantMap& GetGlobalVars() const", asMETHODPR(XMLFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const VariantMap& get_globalVars() const", asMETHODPR(XMLFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "uint GetMemoryUse() const", asMETHODPR(XMLFile, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "uint get_memoryUse() const", asMETHODPR(XMLFile, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetName() const", asMETHODPR(XMLFile, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_name() const", asMETHODPR(XMLFile, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "StringHash GetNameHash() const", asMETHODPR(XMLFile, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // XMLElement XMLFile::GetOrCreateRoot(const String& name) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetOrCreateRoot(const String&in)", asMETHODPR(XMLFile, GetOrCreateRoot, (const String&), XMLElement), asCALL_THISCALL);
    // XMLElement XMLFile::GetRoot(const String& name=String::EMPTY) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetRoot(const String&in = String::EMPTY)", asMETHODPR(XMLFile, GetRoot, (const String&), XMLElement), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(XMLFile, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "StringHash GetType() const", asMETHODPR(XMLFile, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "StringHash get_type() const", asMETHODPR(XMLFile, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetTypeName() const", asMETHODPR(XMLFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_typeName() const", asMETHODPR(XMLFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "uint GetUseTimer()", asMETHODPR(XMLFile, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "uint get_useTimer()", asMETHODPR(XMLFile, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasEventHandlers() const", asMETHODPR(XMLFile, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(XMLFile, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(XMLFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool IsInstanceOf(StringHash) const", asMETHODPR(XMLFile, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool Load(Deserializer&)", asMETHODPR(XMLFile, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool LoadFile(const String&in)", asMETHODPR(XMLFile, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "bool Load(const String&in)", asMETHODPR(XMLFile, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(XMLFile, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void XMLFile::Patch(XMLFile* patchFile) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLFile@+)", asMETHODPR(XMLFile, Patch, (XMLFile*), void), asCALL_THISCALL);
    // void XMLFile::Patch(const XMLElement& patchElement) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "void Patch(const XMLElement&in)", asMETHODPR(XMLFile, Patch, (const XMLElement&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("XMLFile", "int Refs() const", asMETHODPR(XMLFile, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "int get_refs() const", asMETHODPR(XMLFile, Refs, () const, int), asCALL_THISCALL);
    // static void XMLFile::RegisterObject(Context* context) | File: ../Resource/XMLFile.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_RELEASE, "void f()", asMETHODPR(XMLFile, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void ResetUseTimer()", asMETHODPR(XMLFile, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool XMLFile::Save(Serializer& dest) const override | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool Save(Serializer&) const", asMETHODPR(XMLFile, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool XMLFile::Save(Serializer& dest, const String& indentation) const | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool Save(Serializer&, const String&in) const", asMETHODPR(XMLFile, Save, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool SaveFile(const String&in) const", asMETHODPR(XMLFile, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "bool Save(const String&in) const", asMETHODPR(XMLFile, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SendEvent(StringHash)", asMETHODPR(XMLFile, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(XMLFile, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(XMLFile, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SetBlockEvents(bool)", asMETHODPR(XMLFile, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(XMLFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(XMLFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetMemoryUse(uint)", asMETHODPR(XMLFile, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetName(const String&in)", asMETHODPR(XMLFile, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void set_name(const String&in)", asMETHODPR(XMLFile, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String XMLFile::ToString(const String& indentation="\t") const | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "String ToString(const String&in = \"\t\") const", asMETHODPR(XMLFile, ToString, (const String&) const, String), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromAllEvents()", asMETHODPR(XMLFile, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(XMLFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(XMLFile, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(XMLFile, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(XMLFile, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("XMLFile", "int WeakRefs() const", asMETHODPR(XMLFile, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "int get_weakRefs() const", asMETHODPR(XMLFile, WeakRefs, () const, int), asCALL_THISCALL);
    // explicit XMLFile::XMLFile(Context* context) | File: ../Resource/XMLFile.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_FACTORY, "XMLFile@+ f()", asFUNCTION(XMLFile_XMLFile_Context), asCALL_CDECL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(XMLFile, "XMLFile")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(XMLFile, "XMLFile")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(XMLFile, "XMLFile")
#endif
#ifdef REGISTER_MANUAL_PART_XMLFile
    REGISTER_MANUAL_PART_XMLFile(XMLFile, "XMLFile")
#endif
    RegisterSubclass<Resource, XMLFile>(engine, "Resource", "XMLFile");
    RegisterSubclass<Object, XMLFile>(engine, "Object", "XMLFile");
    RegisterSubclass<RefCounted, XMLFile>(engine, "RefCounted", "XMLFile");

    // void XPathQuery::Bind() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "void Bind()", asMETHODPR(XPathQuery, Bind, (), void), asCALL_THISCALL);
    // void XPathQuery::Clear() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "void Clear()", asMETHODPR(XPathQuery, Clear, (), void), asCALL_THISCALL);
    // XPathResultSet XPathQuery::Evaluate(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "XPathResultSet Evaluate(const XMLElement&in) const", asMETHODPR(XPathQuery, Evaluate, (const XMLElement&) const, XPathResultSet), asCALL_THISCALL);
    // bool XPathQuery::EvaluateToBool(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool EvaluateToBool(const XMLElement&in) const", asMETHODPR(XPathQuery, EvaluateToBool, (const XMLElement&) const, bool), asCALL_THISCALL);
    // float XPathQuery::EvaluateToFloat(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "float EvaluateToFloat(const XMLElement&in) const", asMETHODPR(XPathQuery, EvaluateToFloat, (const XMLElement&) const, float), asCALL_THISCALL);
    // String XPathQuery::EvaluateToString(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "String EvaluateToString(const XMLElement&in) const", asMETHODPR(XPathQuery, EvaluateToString, (const XMLElement&) const, String), asCALL_THISCALL);
    // String XPathQuery::GetQuery() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "String GetQuery() const", asMETHODPR(XPathQuery, GetQuery, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "String get_query() const", asMETHODPR(XPathQuery, GetQuery, () const, String), asCALL_THISCALL);
    // pugi::xpath_query* XPathQuery::GetXPathQuery() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_query*" can not automatically bind
    // pugi::xpath_variable_set* XPathQuery::GetXPathVariableSet() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // bool XPathQuery::SetQuery(const String& queryString, const String& variableString=String::EMPTY, bool bind=true) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetQuery(const String&in, const String&in = String::EMPTY, bool = true)", asMETHODPR(XPathQuery, SetQuery, (const String&, const String&, bool), bool), asCALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, bool value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, bool)", asMETHODPR(XPathQuery, SetVariable, (const String&, bool), bool), asCALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, float value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, float)", asMETHODPR(XPathQuery, SetVariable, (const String&, float), bool), asCALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const String&in)", asMETHODPR(XPathQuery, SetVariable, (const String&, const String&), bool), asCALL_THISCALL);
    // bool XPathQuery::SetVariable(const char* name, const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XPathQuery::SetVariable(const String& name, const XPathResultSet& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const XPathResultSet&in)", asMETHODPR(XPathQuery, SetVariable, (const String&, const XPathResultSet&), bool), asCALL_THISCALL);
    // explicit XPathQuery::XPathQuery(const String& queryString, const String& variableString=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in = String::EMPTY)", asFUNCTION(XPathQuery_XPathQuery_String_String), asCALL_CDECL_OBJFIRST);
    // XPathQuery& XPathQuery::operator=(const XPathQuery&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<XPathQuery>(engine, "XPathQuery");
#ifdef REGISTER_MANUAL_PART_XPathQuery
    REGISTER_MANUAL_PART_XPathQuery(XPathQuery, "XPathQuery")
#endif

    // bool XPathResultSet::Empty() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "bool Empty() const", asMETHODPR(XPathResultSet, Empty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "bool get_empty() const", asMETHODPR(XPathResultSet, Empty, () const, bool), asCALL_THISCALL);
    // XMLElement XPathResultSet::FirstResult() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement FirstResult()", asMETHODPR(XPathResultSet, FirstResult, (), XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement get_firstResult()", asMETHODPR(XPathResultSet, FirstResult, (), XMLElement), asCALL_THISCALL);
    // pugi::xpath_node_set* XPathResultSet::GetXPathNodeSet() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_node_set*" can not automatically bind
    // XPathResultSet& XPathResultSet::operator=(const XPathResultSet& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XPathResultSet& opAssign(const XPathResultSet&in)", asMETHODPR(XPathResultSet, operator=, (const XPathResultSet&), XPathResultSet&), asCALL_THISCALL);
    // XMLElement XPathResultSet::operator[](unsigned index) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement opIndex(uint) const", asMETHODPR(XPathResultSet, operator[], (unsigned) const, XMLElement), asCALL_THISCALL);
    // unsigned XPathResultSet::Size() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "uint Size() const", asMETHODPR(XPathResultSet, Size, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "uint get_size() const", asMETHODPR(XPathResultSet, Size, () const, unsigned), asCALL_THISCALL);
    // XPathResultSet::XPathResultSet(XMLFile* file, pugi::xpath_node_set* resultSet) | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_node_set*" can not automatically bind
    // XPathResultSet::XPathResultSet(const XPathResultSet& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f(const XPathResultSet&in)", asFUNCTION(XPathResultSet_XPathResultSet_XPathResultSet), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_XPathResultSet
    REGISTER_MANUAL_PART_XPathResultSet(XPathResultSet, "XPathResultSet")
#endif

}

}
