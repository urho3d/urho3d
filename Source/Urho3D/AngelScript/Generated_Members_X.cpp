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
    engine->RegisterObjectMethod("XMLElement", "bool AppendChild(XMLElement, bool = false)", AS_METHODPR(XMLElement, AppendChild, (XMLElement, bool), bool), AS_CALL_THISCALL);
    // XMLElement XMLElement::CreateChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement CreateChild(const String&in)", AS_METHODPR(XMLElement, CreateChild, (const String&), XMLElement), AS_CALL_THISCALL);
    // XMLElement XMLElement::CreateChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttribute(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttribute(const String&in = String::EMPTY) const", AS_METHODPR(XMLElement, GetAttribute, (const String&) const, String), AS_CALL_THISCALL);
    // String XMLElement::GetAttribute(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // const char* XMLElement::GetAttributeCString(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // String XMLElement::GetAttributeLower(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeLower(const String&in) const", AS_METHODPR(XMLElement, GetAttributeLower, (const String&) const, String), AS_CALL_THISCALL);
    // String XMLElement::GetAttributeLower(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // Vector<String> XMLElement::GetAttributeNames() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Array<String>@ GetAttributeNames() const", AS_FUNCTION_OBJFIRST(XMLElement_GetAttributeNames_void), AS_CALL_CDECL_OBJFIRST);
    // String XMLElement::GetAttributeUpper(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeUpper(const String&in) const", AS_METHODPR(XMLElement, GetAttributeUpper, (const String&) const, String), AS_CALL_THISCALL);
    // String XMLElement::GetAttributeUpper(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::GetBool(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool GetBool(const String&in) const", AS_METHODPR(XMLElement, GetBool, (const String&) const, bool), AS_CALL_THISCALL);
    // BoundingBox XMLElement::GetBoundingBox() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "BoundingBox GetBoundingBox() const", AS_METHODPR(XMLElement, GetBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> XMLElement::GetBuffer(const String& name) const | File: ../Resource/XMLElement.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // bool XMLElement::GetBuffer(const String& name, void* dest, unsigned size) const | File: ../Resource/XMLElement.h
    // Error: type "void*" can not automatically bind
    // XMLElement XMLElement::GetChild(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetChild(const String&in = String::EMPTY) const", AS_METHODPR(XMLElement, GetChild, (const String&) const, XMLElement), AS_CALL_THISCALL);
    // XMLElement XMLElement::GetChild(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // Color XMLElement::GetColor(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Color GetColor(const String&in) const", AS_METHODPR(XMLElement, GetColor, (const String&) const, Color), AS_CALL_THISCALL);
    // double XMLElement::GetDouble(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "double GetDouble(const String&in) const", AS_METHODPR(XMLElement, GetDouble, (const String&) const, double), AS_CALL_THISCALL);
    // XMLFile* XMLElement::GetFile() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ GetFile() const", AS_METHODPR(XMLElement, GetFile, () const, XMLFile*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ get_file() const", AS_METHODPR(XMLElement, GetFile, () const, XMLFile*), AS_CALL_THISCALL);
    // float XMLElement::GetFloat(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "float GetFloat(const String&in) const", AS_METHODPR(XMLElement, GetFloat, (const String&) const, float), AS_CALL_THISCALL);
    // int XMLElement::GetInt(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "int GetInt(const String&in) const", AS_METHODPR(XMLElement, GetInt, (const String&) const, int), AS_CALL_THISCALL);
    // long long XMLElement::GetInt64(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "int64 GetInt64(const String&in) const", AS_METHODPR(XMLElement, GetInt64, (const String&) const, long long), AS_CALL_THISCALL);
    // IntRect XMLElement::GetIntRect(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntRect GetIntRect(const String&in) const", AS_METHODPR(XMLElement, GetIntRect, (const String&) const, IntRect), AS_CALL_THISCALL);
    // IntVector2 XMLElement::GetIntVector2(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntVector2 GetIntVector2(const String&in) const", AS_METHODPR(XMLElement, GetIntVector2, (const String&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector3 XMLElement::GetIntVector3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "IntVector3 GetIntVector3(const String&in) const", AS_METHODPR(XMLElement, GetIntVector3, (const String&) const, IntVector3), AS_CALL_THISCALL);
    // Matrix3 XMLElement::GetMatrix3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix3 GetMatrix3(const String&in) const", AS_METHODPR(XMLElement, GetMatrix3, (const String&) const, Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 XMLElement::GetMatrix3x4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix3x4 GetMatrix3x4(const String&in) const", AS_METHODPR(XMLElement, GetMatrix3x4, (const String&) const, Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 XMLElement::GetMatrix4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Matrix4 GetMatrix4(const String&in) const", AS_METHODPR(XMLElement, GetMatrix4, (const String&) const, Matrix4), AS_CALL_THISCALL);
    // String XMLElement::GetName() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetName() const", AS_METHODPR(XMLElement, GetName, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_name() const", AS_METHODPR(XMLElement, GetName, () const, String), AS_CALL_THISCALL);
    // XMLElement XMLElement::GetNext(const String& name=String::EMPTY) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetNext(const String&in = String::EMPTY) const", AS_METHODPR(XMLElement, GetNext, (const String&) const, XMLElement), AS_CALL_THISCALL);
    // XMLElement XMLElement::GetNext(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // pugi::xml_node_struct* XMLElement::GetNode() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xml_node_struct*" can not automatically bind
    // unsigned XMLElement::GetNumAttributes() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetNumAttributes() const", AS_METHODPR(XMLElement, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint get_numAttributes() const", AS_METHODPR(XMLElement, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // XMLElement XMLElement::GetOrCreateChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetOrCreateChild(const String&in)", AS_METHODPR(XMLElement, GetOrCreateChild, (const String&), XMLElement), AS_CALL_THISCALL);
    // XMLElement XMLElement::GetOrCreateChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // XMLElement XMLElement::GetParent() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetParent() const", AS_METHODPR(XMLElement, GetParent, () const, XMLElement), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_parent() const", AS_METHODPR(XMLElement, GetParent, () const, XMLElement), AS_CALL_THISCALL);
    // Quaternion XMLElement::GetQuaternion(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Quaternion GetQuaternion(const String&in) const", AS_METHODPR(XMLElement, GetQuaternion, (const String&) const, Quaternion), AS_CALL_THISCALL);
    // Rect XMLElement::GetRect(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Rect GetRect(const String&in) const", AS_METHODPR(XMLElement, GetRect, (const String&) const, Rect), AS_CALL_THISCALL);
    // ResourceRef XMLElement::GetResourceRef() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "ResourceRef GetResourceRef() const", AS_METHODPR(XMLElement, GetResourceRef, () const, ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList XMLElement::GetResourceRefList() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "ResourceRefList GetResourceRefList() const", AS_METHODPR(XMLElement, GetResourceRefList, () const, ResourceRefList), AS_CALL_THISCALL);
    // StringVector XMLElement::GetStringVector() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Array<String>@ GetStringVector() const", AS_FUNCTION_OBJFIRST(XMLElement_GetStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned XMLElement::GetUInt(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetUInt(const String&in) const", AS_METHODPR(XMLElement, GetUInt, (const String&) const, unsigned), AS_CALL_THISCALL);
    // unsigned long long XMLElement::GetUInt64(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint64 GetUInt64(const String&in) const", AS_METHODPR(XMLElement, GetUInt64, (const String&) const, unsigned long long), AS_CALL_THISCALL);
    // String XMLElement::GetValue() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "String GetValue() const", AS_METHODPR(XMLElement, GetValue, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_value() const", AS_METHODPR(XMLElement, GetValue, () const, String), AS_CALL_THISCALL);
    // Variant XMLElement::GetVariant() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVariant() const", AS_METHODPR(XMLElement, GetVariant, () const, Variant), AS_CALL_THISCALL);
    // VariantMap XMLElement::GetVariantMap() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "VariantMap GetVariantMap() const", AS_METHODPR(XMLElement, GetVariantMap, () const, VariantMap), AS_CALL_THISCALL);
    // Variant XMLElement::GetVariantValue(VariantType type) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVariantValue(VariantType) const", AS_METHODPR(XMLElement, GetVariantValue, (VariantType) const, Variant), AS_CALL_THISCALL);
    // VariantVector XMLElement::GetVariantVector() const | File: ../Resource/XMLElement.h
    // Error: type "VariantVector" can not automatically bind
    // Vector4 XMLElement::GetVector(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector4 GetVector(const String&in) const", AS_METHODPR(XMLElement, GetVector, (const String&) const, Vector4), AS_CALL_THISCALL);
    // Vector2 XMLElement::GetVector2(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector2 GetVector2(const String&in) const", AS_METHODPR(XMLElement, GetVector2, (const String&) const, Vector2), AS_CALL_THISCALL);
    // Vector3 XMLElement::GetVector3(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector3 GetVector3(const String&in) const", AS_METHODPR(XMLElement, GetVector3, (const String&) const, Vector3), AS_CALL_THISCALL);
    // Vector4 XMLElement::GetVector4(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Vector4 GetVector4(const String&in) const", AS_METHODPR(XMLElement, GetVector4, (const String&) const, Vector4), AS_CALL_THISCALL);
    // Variant XMLElement::GetVectorVariant(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "Variant GetVectorVariant(const String&in) const", AS_METHODPR(XMLElement, GetVectorVariant, (const String&) const, Variant), AS_CALL_THISCALL);
    // const pugi::xpath_node* XMLElement::GetXPathNode() const | File: ../Resource/XMLElement.h
    // Error: type "const pugi::xpath_node*" can not automatically bind
    // unsigned XMLElement::GetXPathResultIndex() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "uint GetXPathResultIndex() const", AS_METHODPR(XMLElement, GetXPathResultIndex, () const, unsigned), AS_CALL_THISCALL);
    // const XPathResultSet* XMLElement::GetXPathResultSet() const | File: ../Resource/XMLElement.h
    // Error: type "const XPathResultSet*" can not automatically bind
    // bool XMLElement::HasAttribute(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool HasAttribute(const String&in) const", AS_METHODPR(XMLElement, HasAttribute, (const String&) const, bool), AS_CALL_THISCALL);
    // bool XMLElement::HasAttribute(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::HasChild(const String& name) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool HasChild(const String&in) const", AS_METHODPR(XMLElement, HasChild, (const String&) const, bool), AS_CALL_THISCALL);
    // bool XMLElement::HasChild(const char* name) const | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::IsNull() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool IsNull() const", AS_METHODPR(XMLElement, IsNull, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_isNull() const", AS_METHODPR(XMLElement, IsNull, () const, bool), AS_CALL_THISCALL);
    // XMLElement XMLElement::NextResult() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement NextResult() const", AS_METHODPR(XMLElement, NextResult, () const, XMLElement), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_nextResult() const", AS_METHODPR(XMLElement, NextResult, () const, XMLElement), AS_CALL_THISCALL);
    // bool XMLElement::NotNull() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool NotNull() const", AS_METHODPR(XMLElement, NotNull, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_notNull() const", AS_METHODPR(XMLElement, NotNull, () const, bool), AS_CALL_THISCALL);
    // explicit XMLElement::operator bool() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool opConv() const", AS_METHODPR(XMLElement, operator bool, () const, bool), AS_CALL_THISCALL);
    // XMLElement& XMLElement::operator=(const XMLElement& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement& opAssign(const XMLElement&in)", AS_METHODPR(XMLElement, operator=, (const XMLElement&), XMLElement&), AS_CALL_THISCALL);
    // bool XMLElement::Remove() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool Remove()", AS_METHODPR(XMLElement, Remove, (), bool), AS_CALL_THISCALL);
    // bool XMLElement::RemoveAttribute(const String& name=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveAttribute(const String&in = String::EMPTY)", AS_METHODPR(XMLElement, RemoveAttribute, (const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::RemoveAttribute(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChild(const XMLElement& element) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const XMLElement&in)", AS_METHODPR(XMLElement, RemoveChild, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool XMLElement::RemoveChild(const String& name) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const String&in)", AS_METHODPR(XMLElement, RemoveChild, (const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::RemoveChild(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::RemoveChildren(const String& name=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChildren(const String&in = String::EMPTY)", AS_METHODPR(XMLElement, RemoveChildren, (const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::RemoveChildren(const char* name) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // XPathResultSet XMLElement::Select(const String& query, pugi::xpath_variable_set* variables=nullptr) const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // XPathResultSet XMLElement::SelectPrepared(const XPathQuery& query) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XPathResultSet SelectPrepared(const XPathQuery&in) const", AS_METHODPR(XMLElement, SelectPrepared, (const XPathQuery&) const, XPathResultSet), AS_CALL_THISCALL);
    // XMLElement XMLElement::SelectSingle(const String& query, pugi::xpath_variable_set* variables=nullptr) const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // XMLElement XMLElement::SelectSinglePrepared(const XPathQuery& query) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "XMLElement SelectSinglePrepared(const XPathQuery&in) const", AS_METHODPR(XMLElement, SelectSinglePrepared, (const XPathQuery&) const, XMLElement), AS_CALL_THISCALL);
    // bool XMLElement::SetAttribute(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in, const String&in)", AS_METHODPR(XMLElement, SetAttribute, (const String&, const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetAttribute(const char* name, const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetAttribute(const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in)", AS_METHODPR(XMLElement, SetAttribute, (const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetAttribute(const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetBool(const String& name, bool value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetBool(const String&in, bool)", AS_METHODPR(XMLElement, SetBool, (const String&, bool), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetBoundingBox(const BoundingBox& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetBoundingBox(const BoundingBox&in)", AS_METHODPR(XMLElement, SetBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetBuffer(const String& name, const void* data, unsigned size) | File: ../Resource/XMLElement.h
    // Error: type "const void*" can not automatically bind
    // bool XMLElement::SetBuffer(const String& name, const PODVector<unsigned char>& value) | File: ../Resource/XMLElement.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool XMLElement::SetColor(const String& name, const Color& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetColor(const String&in, const Color&in)", AS_METHODPR(XMLElement, SetColor, (const String&, const Color&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetDouble(const String& name, double value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetDouble(const String&in, double)", AS_METHODPR(XMLElement, SetDouble, (const String&, double), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetFloat(const String& name, float value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetFloat(const String&in, float)", AS_METHODPR(XMLElement, SetFloat, (const String&, float), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetInt(const String& name, int value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetInt(const String&in, int)", AS_METHODPR(XMLElement, SetInt, (const String&, int), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetInt64(const String& name, long long value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetInt64(const String&in, int64)", AS_METHODPR(XMLElement, SetInt64, (const String&, long long), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetIntRect(const String& name, const IntRect& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntRect(const String&in, const IntRect&in)", AS_METHODPR(XMLElement, SetIntRect, (const String&, const IntRect&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetIntVector2(const String& name, const IntVector2& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntVector2(const String&in, const IntVector2&in)", AS_METHODPR(XMLElement, SetIntVector2, (const String&, const IntVector2&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetIntVector3(const String& name, const IntVector3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetIntVector3(const String&in, const IntVector3&in)", AS_METHODPR(XMLElement, SetIntVector3, (const String&, const IntVector3&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetMatrix3(const String& name, const Matrix3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3(const String&in, const Matrix3&in)", AS_METHODPR(XMLElement, SetMatrix3, (const String&, const Matrix3&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetMatrix3x4(const String& name, const Matrix3x4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3x4(const String&in, const Matrix3x4&in)", AS_METHODPR(XMLElement, SetMatrix3x4, (const String&, const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetMatrix4(const String& name, const Matrix4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix4(const String&in, const Matrix4&in)", AS_METHODPR(XMLElement, SetMatrix4, (const String&, const Matrix4&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetQuaternion(const String& name, const Quaternion& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetQuaternion(const String&in, const Quaternion&in)", AS_METHODPR(XMLElement, SetQuaternion, (const String&, const Quaternion&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetRect(const String& name, const Rect& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetRect(const String&in, const Rect&in)", AS_METHODPR(XMLElement, SetRect, (const String&, const Rect&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetResourceRef(const ResourceRef& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRef(const ResourceRef&in)", AS_METHODPR(XMLElement, SetResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetResourceRefList(const ResourceRefList& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRefList(const ResourceRefList&in)", AS_METHODPR(XMLElement, SetResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetString(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetString(const String&in, const String&in)", AS_METHODPR(XMLElement, SetString, (const String&, const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetStringVector(const StringVector& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(XMLElement_SetStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool XMLElement::SetUInt(const String& name, unsigned value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt(const String&in, uint)", AS_METHODPR(XMLElement, SetUInt, (const String&, unsigned), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetUInt64(const String& name, unsigned long long value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt64(const String&in, uint64)", AS_METHODPR(XMLElement, SetUInt64, (const String&, unsigned long long), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetValue(const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetValue(const String&in)", AS_METHODPR(XMLElement, SetValue, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool set_value(const String&in)", AS_METHODPR(XMLElement, SetValue, (const String&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetValue(const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XMLElement::SetVariant(const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariant(const Variant&in)", AS_METHODPR(XMLElement, SetVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVariantMap(const VariantMap& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantMap(const VariantMap&in)", AS_METHODPR(XMLElement, SetVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVariantValue(const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantValue(const Variant&in)", AS_METHODPR(XMLElement, SetVariantValue, (const Variant&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVariantVector(const VariantVector& value) | File: ../Resource/XMLElement.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool XMLElement::SetVector2(const String& name, const Vector2& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector2(const String&in, const Vector2&in)", AS_METHODPR(XMLElement, SetVector2, (const String&, const Vector2&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVector3(const String& name, const Vector3& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector3(const String&in, const Vector3&in)", AS_METHODPR(XMLElement, SetVector3, (const String&, const Vector3&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVector4(const String& name, const Vector4& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVector4(const String&in, const Vector4&in)", AS_METHODPR(XMLElement, SetVector4, (const String&, const Vector4&), bool), AS_CALL_THISCALL);
    // bool XMLElement::SetVectorVariant(const String& name, const Variant& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XMLElement", "bool SetVectorVariant(const String&in, const Variant&in)", AS_METHODPR(XMLElement, SetVectorVariant, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // XMLElement::XMLElement(XMLFile* file, pugi::xml_node_struct* node) | File: ../Resource/XMLElement.h
    // Error: type "pugi::xml_node_struct*" can not automatically bind
    // XMLElement::XMLElement(XMLFile* file, const XPathResultSet* resultSet, const pugi::xpath_node* xpathNode, unsigned xpathResultIndex) | File: ../Resource/XMLElement.h
    // Error: type "const XPathResultSet*" can not automatically bind
    // XMLElement::XMLElement(const XMLElement& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement&in)", AS_FUNCTION_OBJFIRST(XMLElement_XMLElement_XMLElement), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_XMLElement
    REGISTER_MANUAL_PART_XMLElement(XMLElement, "XMLElement")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_ADDREF, "void f()", AS_METHODPR(XMLFile, AddRef, (), void), AS_CALL_THISCALL);
    // bool XMLFile::BeginLoad(Deserializer& source) override | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool BeginLoad(Deserializer&)", AS_METHODPR(XMLFile, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // XMLElement XMLFile::CreateRoot(const String& name) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement CreateRoot(const String&in)", AS_METHODPR(XMLFile, CreateRoot, (const String&), XMLElement), AS_CALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool EndLoad()", AS_METHODPR(XMLFile, EndLoad, (), bool), AS_CALL_THISCALL);
    // bool XMLFile::FromString(const String& source) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool FromString(const String&in)", AS_METHODPR(XMLFile, FromString, (const String&), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(XMLFile, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool GetBlockEvents() const", AS_METHODPR(XMLFile, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetCategory() const", AS_METHODPR(XMLFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_category() const", AS_METHODPR(XMLFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // pugi::xml_document* XMLFile::GetDocument() const | File: ../Resource/XMLFile.h
    // Error: type "pugi::xml_document*" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "VariantMap& GetEventDataMap() const", AS_METHODPR(XMLFile, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "Object@+ GetEventSender() const", AS_METHODPR(XMLFile, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(XMLFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(XMLFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const VariantMap& GetGlobalVars() const", AS_METHODPR(XMLFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const VariantMap& get_globalVars() const", AS_METHODPR(XMLFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "uint GetMemoryUse() const", AS_METHODPR(XMLFile, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "uint get_memoryUse() const", AS_METHODPR(XMLFile, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetName() const", AS_METHODPR(XMLFile, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_name() const", AS_METHODPR(XMLFile, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "StringHash GetNameHash() const", AS_METHODPR(XMLFile, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // XMLElement XMLFile::GetOrCreateRoot(const String& name) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetOrCreateRoot(const String&in)", AS_METHODPR(XMLFile, GetOrCreateRoot, (const String&), XMLElement), AS_CALL_THISCALL);
    // XMLElement XMLFile::GetRoot(const String& name=String::EMPTY) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetRoot(const String&in = String::EMPTY)", AS_METHODPR(XMLFile, GetRoot, (const String&), XMLElement), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(XMLFile, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "StringHash GetType() const", AS_METHODPR(XMLFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "StringHash get_type() const", AS_METHODPR(XMLFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "const String& GetTypeName() const", AS_METHODPR(XMLFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "const String& get_typeName() const", AS_METHODPR(XMLFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "uint GetUseTimer()", AS_METHODPR(XMLFile, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "uint get_useTimer()", AS_METHODPR(XMLFile, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasEventHandlers() const", AS_METHODPR(XMLFile, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(XMLFile, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(XMLFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "bool IsInstanceOf(StringHash) const", AS_METHODPR(XMLFile, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool Load(Deserializer&)", AS_METHODPR(XMLFile, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool LoadFile(const String&in)", AS_METHODPR(XMLFile, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "bool Load(const String&in)", AS_METHODPR(XMLFile, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(XMLFile, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void XMLFile::Patch(XMLFile* patchFile) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLFile@+)", AS_METHODPR(XMLFile, Patch, (XMLFile*), void), AS_CALL_THISCALL);
    // void XMLFile::Patch(const XMLElement& patchElement) | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "void Patch(const XMLElement&in)", AS_METHODPR(XMLFile, Patch, (const XMLElement&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("XMLFile", "int Refs() const", AS_METHODPR(XMLFile, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "int get_refs() const", AS_METHODPR(XMLFile, Refs, () const, int), AS_CALL_THISCALL);
    // static void XMLFile::RegisterObject(Context* context) | File: ../Resource/XMLFile.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_RELEASE, "void f()", AS_METHODPR(XMLFile, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void ResetUseTimer()", AS_METHODPR(XMLFile, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool XMLFile::Save(Serializer& dest) const override | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool Save(Serializer&) const", AS_METHODPR(XMLFile, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool XMLFile::Save(Serializer& dest, const String& indentation) const | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "bool Save(Serializer&, const String&in) const", AS_METHODPR(XMLFile, Save, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "bool SaveFile(const String&in) const", AS_METHODPR(XMLFile, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "bool Save(const String&in) const", AS_METHODPR(XMLFile, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SendEvent(StringHash)", AS_METHODPR(XMLFile, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(XMLFile, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(XMLFile, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SetBlockEvents(bool)", AS_METHODPR(XMLFile, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(XMLFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(XMLFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetMemoryUse(uint)", AS_METHODPR(XMLFile, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("XMLFile", "void SetName(const String&in)", AS_METHODPR(XMLFile, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void set_name(const String&in)", AS_METHODPR(XMLFile, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String XMLFile::ToString(const String& indentation="\t") const | File: ../Resource/XMLFile.h
    engine->RegisterObjectMethod("XMLFile", "String ToString(const String&in = \"\t\") const", AS_METHODPR(XMLFile, ToString, (const String&) const, String), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromAllEvents()", AS_METHODPR(XMLFile, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(XMLFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(XMLFile, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(XMLFile, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("XMLFile", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(XMLFile, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("XMLFile", "int WeakRefs() const", AS_METHODPR(XMLFile, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "int get_weakRefs() const", AS_METHODPR(XMLFile, WeakRefs, () const, int), AS_CALL_THISCALL);
    // explicit XMLFile::XMLFile(Context* context) | File: ../Resource/XMLFile.h
    engine->RegisterObjectBehaviour("XMLFile", asBEHAVE_FACTORY, "XMLFile@+ f()", AS_FUNCTION(XMLFile_XMLFile_Context), AS_CALL_CDECL);
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
    engine->RegisterObjectMethod("XPathQuery", "void Bind()", AS_METHODPR(XPathQuery, Bind, (), void), AS_CALL_THISCALL);
    // void XPathQuery::Clear() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "void Clear()", AS_METHODPR(XPathQuery, Clear, (), void), AS_CALL_THISCALL);
    // XPathResultSet XPathQuery::Evaluate(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "XPathResultSet Evaluate(const XMLElement&in) const", AS_METHODPR(XPathQuery, Evaluate, (const XMLElement&) const, XPathResultSet), AS_CALL_THISCALL);
    // bool XPathQuery::EvaluateToBool(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool EvaluateToBool(const XMLElement&in) const", AS_METHODPR(XPathQuery, EvaluateToBool, (const XMLElement&) const, bool), AS_CALL_THISCALL);
    // float XPathQuery::EvaluateToFloat(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "float EvaluateToFloat(const XMLElement&in) const", AS_METHODPR(XPathQuery, EvaluateToFloat, (const XMLElement&) const, float), AS_CALL_THISCALL);
    // String XPathQuery::EvaluateToString(const XMLElement& element) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "String EvaluateToString(const XMLElement&in) const", AS_METHODPR(XPathQuery, EvaluateToString, (const XMLElement&) const, String), AS_CALL_THISCALL);
    // String XPathQuery::GetQuery() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "String GetQuery() const", AS_METHODPR(XPathQuery, GetQuery, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "String get_query() const", AS_METHODPR(XPathQuery, GetQuery, () const, String), AS_CALL_THISCALL);
    // pugi::xpath_query* XPathQuery::GetXPathQuery() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_query*" can not automatically bind
    // pugi::xpath_variable_set* XPathQuery::GetXPathVariableSet() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_variable_set*" can not automatically bind
    // bool XPathQuery::SetQuery(const String& queryString, const String& variableString=String::EMPTY, bool bind=true) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetQuery(const String&in, const String&in = String::EMPTY, bool = true)", AS_METHODPR(XPathQuery, SetQuery, (const String&, const String&, bool), bool), AS_CALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, bool value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, bool)", AS_METHODPR(XPathQuery, SetVariable, (const String&, bool), bool), AS_CALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, float value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, float)", AS_METHODPR(XPathQuery, SetVariable, (const String&, float), bool), AS_CALL_THISCALL);
    // bool XPathQuery::SetVariable(const String& name, const String& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const String&in)", AS_METHODPR(XPathQuery, SetVariable, (const String&, const String&), bool), AS_CALL_THISCALL);
    // bool XPathQuery::SetVariable(const char* name, const char* value) | File: ../Resource/XMLElement.h
    // Error: type "const char*" can not automatically bind
    // bool XPathQuery::SetVariable(const String& name, const XPathResultSet& value) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const XPathResultSet&in)", AS_METHODPR(XPathQuery, SetVariable, (const String&, const XPathResultSet&), bool), AS_CALL_THISCALL);
    // explicit XPathQuery::XPathQuery(const String& queryString, const String& variableString=String::EMPTY) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in = String::EMPTY)", AS_FUNCTION_OBJFIRST(XPathQuery_XPathQuery_String_String), AS_CALL_CDECL_OBJFIRST);
    // XPathQuery& XPathQuery::operator=(const XPathQuery&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<XPathQuery>(engine, "XPathQuery");
#ifdef REGISTER_MANUAL_PART_XPathQuery
    REGISTER_MANUAL_PART_XPathQuery(XPathQuery, "XPathQuery")
#endif

    // bool XPathResultSet::Empty() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "bool Empty() const", AS_METHODPR(XPathResultSet, Empty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "bool get_empty() const", AS_METHODPR(XPathResultSet, Empty, () const, bool), AS_CALL_THISCALL);
    // XMLElement XPathResultSet::FirstResult() | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement FirstResult()", AS_METHODPR(XPathResultSet, FirstResult, (), XMLElement), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement get_firstResult()", AS_METHODPR(XPathResultSet, FirstResult, (), XMLElement), AS_CALL_THISCALL);
    // pugi::xpath_node_set* XPathResultSet::GetXPathNodeSet() const | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_node_set*" can not automatically bind
    // XPathResultSet& XPathResultSet::operator=(const XPathResultSet& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XPathResultSet& opAssign(const XPathResultSet&in)", AS_METHODPR(XPathResultSet, operator=, (const XPathResultSet&), XPathResultSet&), AS_CALL_THISCALL);
    // XMLElement XPathResultSet::operator[](unsigned index) const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement opIndex(uint) const", AS_METHODPR(XPathResultSet, operator[], (unsigned) const, XMLElement), AS_CALL_THISCALL);
    // unsigned XPathResultSet::Size() const | File: ../Resource/XMLElement.h
    engine->RegisterObjectMethod("XPathResultSet", "uint Size() const", AS_METHODPR(XPathResultSet, Size, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "uint get_size() const", AS_METHODPR(XPathResultSet, Size, () const, unsigned), AS_CALL_THISCALL);
    // XPathResultSet::XPathResultSet(XMLFile* file, pugi::xpath_node_set* resultSet) | File: ../Resource/XMLElement.h
    // Error: type "pugi::xpath_node_set*" can not automatically bind
    // XPathResultSet::XPathResultSet(const XPathResultSet& rhs) | File: ../Resource/XMLElement.h
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f(const XPathResultSet&in)", AS_FUNCTION_OBJFIRST(XPathResultSet_XPathResultSet_XPathResultSet), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_XPathResultSet
    REGISTER_MANUAL_PART_XPathResultSet(XPathResultSet, "XPathResultSet")
#endif

}

}
