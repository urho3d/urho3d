//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "APITemplates.h"
#include "Image.h"
#include "PackageFile.h"
#include "ResourceCache.h"

namespace Urho3D
{

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);

void RegisterResource(asIScriptEngine* engine)
{
    RegisterResource<Resource>(engine, "Resource");
}

static Resource* ResourceCacheGetResource(const String& type, const String& name, ResourceCache* ptr)
{
    return ptr->GetResource(ShortStringHash(type), name);
}

static File* ResourceCacheGetFile(const String& name, ResourceCache* ptr)
{
    SharedPtr<File> file = ptr->GetFile(name);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    if (file)
        file->AddRef();
    return file.Get();
}

static void ResourceCacheReleaseResource(const String& type, const String& name, bool force, ResourceCache* ptr)
{
    ptr->ReleaseResource(type, name, force);
}

static void ResourceCacheReleaseResourcesPartial(const String& type, const String& partialName, bool force, ResourceCache* ptr)
{
    ptr->ReleaseResources(type, partialName, force);
}

static void ResourceCacheSetMemoryBudget(const String& type, unsigned budget, ResourceCache* ptr)
{
    ptr->SetMemoryBudget(type, budget);
}

static unsigned ResourceCacheGetMemoryBudget(const String& type, ResourceCache* ptr)
{
    return ptr->GetMemoryBudget(type);
}

static unsigned ResourceCacheGetMemoryUse(const String& type, ResourceCache* ptr)
{
    return ptr->GetMemoryUse(type);
}

static ResourceCache* GetResourceCache()
{
    return GetScriptContext()->GetSubsystem<ResourceCache>();
}

static CScriptArray* ResourceCacheGetResourceDirs(ResourceCache* ptr)
{
    return VectorToArray<String>(ptr->GetResourceDirs(), "Array<String>");
}

static CScriptArray* ResourceCacheGetPackageFiles(ResourceCache* ptr)
{
    return VectorToHandleArray<PackageFile>(ptr->GetPackageFiles(), "Array<PackageFile@>");
}

static void RegisterResourceCache(asIScriptEngine* engine)
{
    RegisterObject<ResourceCache>(engine, "ResourceCache");
    engine->RegisterObjectMethod("ResourceCache", "bool AddResourceDir(const String&in, uint priority = -1)", asMETHOD(ResourceCache, AddResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void AddPackageFile(PackageFile@+, uint priority = -1)", asMETHOD(ResourceCache, AddPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool AddManualResource(Resource@+)", asMETHOD(ResourceCache, AddManualResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemoveResourceDir(const String&in)", asMETHOD(ResourceCache, RemoveResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(PackageFile@+, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (PackageFile*, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(const String&in, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (const String&, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResource(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(ShortStringHash, bool force = false)", asMETHODPR(ResourceCache, ReleaseResources, (ShortStringHash, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResourcesPartial), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, bool force = false)", asMETHODPR(ResourceCache, ReleaseResources, (const String&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseAllResources(bool force = false)", asMETHOD(ResourceCache, ReleaseAllResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool ReloadResource(Resource@+)", asMETHOD(ResourceCache, ReloadResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool Exists(const String&in) const", asMETHODPR(ResourceCache, Exists, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "File@ GetFile(const String&in)", asFUNCTION(ResourceCacheGetFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "String GetPreferredResourceDir(const String&in) const", asMETHOD(ResourceCache, GetPreferredResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceName(const String&in) const", asMETHOD(ResourceCache, SanitateResourceName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceDirName(const String&in) const", asMETHOD(ResourceCache, SanitateResourceDirName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String GetResourceFileName(const String&in) const", asMETHOD(ResourceCache, GetResourceFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(const String&in, const String&in)", asFUNCTION(ResourceCacheGetResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(ShortStringHash, const String&in)", asMETHODPR(ResourceCache, GetResource, (ShortStringHash, const String&), Resource*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_memoryBudget(const String&in, uint)", asFUNCTION(ResourceCacheSetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_memoryBudget(const String&in) const", asFUNCTION(ResourceCacheGetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_memoryUse(const String&in) const", asFUNCTION(ResourceCacheGetMemoryUse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_totalMemoryUse() const", asMETHOD(ResourceCache, GetTotalMemoryUse), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ get_resourceDirs() const", asFUNCTION(ResourceCacheGetResourceDirs), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ get_packageFiles() const", asFUNCTION(ResourceCacheGetPackageFiles), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void set_searchPackagesFirst(bool)", asMETHOD(ResourceCache, SetSearchPackagesFirst), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_seachPackagesFirst() const", asMETHOD(ResourceCache, GetSearchPackagesFirst), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_autoReloadResources(bool)", asMETHOD(ResourceCache, SetAutoReloadResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_autoReloadResources() const", asMETHOD(ResourceCache, GetAutoReloadResources), asCALL_THISCALL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
}

static bool ImageLoadColorLUT(File* file, Serializable* ptr)
{
    if (file)
        return ptr->Load(*file);
    else
        return false;
}

static void RegisterImage(asIScriptEngine* engine)
{
    RegisterResource<Image>(engine, "Image");
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, uint)", asMETHODPR(Image, SetSize, (int, int, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, int, uint)", asMETHODPR(Image, SetSize, (int, int, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, int, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool LoadColorLUT(File@+)", asFUNCTION(ImageLoadColorLUT), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Image", "void FlipVertical()", asMETHOD(Image, FlipVertical), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void Resize(int, int)", asMETHOD(Image, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void Clear(const Color&in)", asMETHOD(Image, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SaveBMP(const String&in) const", asMETHOD(Image, SaveBMP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SavePNG(const String&in) const", asMETHOD(Image, SavePNG), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SaveTGA(const String&in) const", asMETHOD(Image, SaveTGA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SaveJPG(const String&in, int) const", asMETHOD(Image, SaveJPG), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int) const", asMETHODPR(Image, GetPixel, (int, int) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int, int) const", asMETHODPR(Image, GetPixel, (int, int, int) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixelBilinear(float, float) const", asMETHODPR(Image, GetPixelBilinear, (float, float) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixelTrilinear(float, float, float) const", asMETHODPR(Image, GetPixelTrilinear, (float, float, float) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_width() const", asMETHOD(Image, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_height() const", asMETHOD(Image, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_depth() const", asMETHOD(Image, GetDepth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_components() const", asMETHOD(Image, GetComponents), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_compressed() const", asMETHOD(Image, IsCompressed), asCALL_THISCALL);
}

static void ConstructXMLElement(XMLElement* ptr)
{
    new(ptr) XMLElement();
}

static void ConstructXMLElementCopy(const XMLElement& element, XMLElement* ptr)
{
    new(ptr) XMLElement(element);
}

static void DestructXMLElement(XMLElement* ptr)
{
    ptr->~XMLElement();
}

static void XMLElementSetVariantVector(CScriptArray* value, XMLElement* ptr)
{
    VariantVector src;
    ArrayToVariantVector(value, src);
    ptr->SetVariantVector(src);
}

static CScriptArray* XMLElementGetAttributeNames(XMLElement* ptr)
{
    return VectorToArray<String>(ptr->GetAttributeNames(), "Array<String>");
}

static CScriptArray* XMLElementGetVariantVector(XMLElement* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

static void ConstructXPathResultSet(XPathResultSet* ptr)
{
    new(ptr) XPathResultSet();
}

static void ConstructXPathResultSetCopy(const XPathResultSet& xpathResultSet, XPathResultSet* ptr)
{
    new(ptr) XPathResultSet(xpathResultSet);
}

static void DestructXPathResultSet(XPathResultSet* ptr)
{
    ptr->~XPathResultSet();
}

static XMLElement XPathResultSetAt(unsigned index, XPathResultSet* ptr)
{
    return ptr->operator [](index);
}

static void ConstructXPathQuery(XPathQuery* ptr)
{
    new(ptr) XPathQuery();
}

static void ConstructXPathQueryWithString(const String& queryString, const String& variableString, XPathQuery* ptr)
{
    new(ptr) XPathQuery(queryString, variableString);
}

static void DestructXPathQuery(XPathQuery* ptr)
{
    ptr->~XPathQuery();
}

static void RegisterXMLElement(asIScriptEngine* engine)
{
    RegisterResource<XMLFile>(engine, "XMLFile");
    engine->RegisterObjectType("XMLElement", sizeof(XMLElement), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectType("XPathResultSet", sizeof(XPathResultSet), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectType("XPathQuery", sizeof(XPathQuery), asOBJ_VALUE | asOBJ_APP_CLASS_CD);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXMLElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement&in)", asFUNCTION(ConstructXMLElementCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructXMLElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "XMLElement& opAssign(const XMLElement&in)", asMETHOD(XMLElement, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement CreateChild(const String&in)", asMETHODPR(XMLElement, CreateChild, (const String&), XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const XMLElement&in)", asMETHODPR(XMLElement, RemoveChild, (const XMLElement&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const String&in)", asMETHODPR(XMLElement, RemoveChild, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChildren(const String&in name = String())", asMETHODPR(XMLElement, RemoveChildren, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveAttribute(const String&in name = String())", asMETHODPR(XMLElement, RemoveAttribute, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement SelectSingle(const String&in)", asMETHOD(XMLElement, SelectSingle), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement SelectSinglePrepared(const XPathQuery&in)", asMETHOD(XMLElement, SelectSinglePrepared), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XPathResultSet Select(const String&in)", asMETHOD(XMLElement, Select), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XPathResultSet SelectPrepared(const XPathQuery&in)", asMETHOD(XMLElement, SelectPrepared), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetValue(const String&in)", asMETHODPR(XMLElement, SetValue, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in, const String&in)", asMETHODPR(XMLElement, SetAttribute, (const String&, const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in)", asMETHODPR(XMLElement, SetAttribute, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetBool(const String&in, bool)", asMETHOD(XMLElement, SetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetBoundingBox(const BoundingBox&in)", asMETHOD(XMLElement, SetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetColor(const String&in, const Color&in)", asMETHOD(XMLElement, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetFloat(const String&in, float)", asMETHOD(XMLElement, SetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetInt(const String&in, int)", asMETHOD(XMLElement, SetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt(const String&in, uint)", asMETHOD(XMLElement, SetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetQuaternion(const String&in, const Quaternion&in)", asMETHOD(XMLElement, SetQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariant(const Variant&in)", asMETHOD(XMLElement, SetVariant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRef(const String&in, const ResourceRef&in)", asMETHOD(XMLElement, SetResourceRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRefList(const String&in, const ResourceRefList&in)", asMETHOD(XMLElement, SetResourceRefList), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantVector(Array<Variant>@+)", asFUNCTION(XMLElementSetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantMap(const VariantMap&in)", asMETHOD(XMLElement, SetVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector2(const String&in, const Vector2&in)", asMETHOD(XMLElement, SetVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector3(const String&in, const Vector3&in)", asMETHOD(XMLElement, SetVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector4(const String&in, const Vector4&in)", asMETHOD(XMLElement, SetVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVectorVariant(const String&in, const Variant&in)", asMETHOD(XMLElement, SetVectorVariant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool HasAttribute(const String&in) const", asMETHODPR(XMLElement, HasAttribute, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String GetValue() const", asMETHOD(XMLElement, GetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String GetAttribute(const String&in arg0 = String()) const", asMETHODPR(XMLElement, GetAttribute, (const String&) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeLower(const String&in) const", asMETHODPR(XMLElement, GetAttributeLower, (const String&) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String GetAttributeUpper(const String&in) const", asMETHODPR(XMLElement, GetAttributeUpper, (const String&) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Array<String>@ GetAttributeNames() const", asFUNCTION(XMLElementGetAttributeNames), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "bool HasChild(const String&in) const", asMETHODPR(XMLElement, HasChild, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetChild(const String&in name = String()) const", asMETHODPR(XMLElement, GetChild, (const String&) const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement GetNext(const String&in name = String()) const", asMETHODPR(XMLElement, GetNext, (const String&) const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool GetBool(const String&in) const", asMETHOD(XMLElement, GetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "BoundingBox GetBoundingBox() const", asMETHOD(XMLElement, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Color GetColor(const String&in) const", asMETHOD(XMLElement, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "float GetFloat(const String&in) const", asMETHOD(XMLElement, GetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint GetUInt(const String&in) const", asMETHOD(XMLElement, GetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "int GetInt(const String&in) const", asMETHOD(XMLElement, GetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Quaternion GetQuaternion(const String&in) const", asMETHOD(XMLElement, GetQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Variant GetVariant() const", asMETHOD(XMLElement, GetVariant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "ResourceRef GetResourceRef() const", asMETHOD(XMLElement, GetResourceRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "ResourceRefList GetResourceRefList() const", asMETHOD(XMLElement, GetResourceRefList), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Array<Variant>@ GetVariantVector() const", asFUNCTION(XMLElementGetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "VariantMap GetVariantMap() const", asMETHOD(XMLElement, GetVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Vector2 GetVector2(const String&in) const", asMETHOD(XMLElement, GetVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Vector3 GetVector3(const String&in) const", asMETHOD(XMLElement, GetVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Vector4 GetVector4(const String&in) const", asMETHOD(XMLElement, GetVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Variant GetVectorVariant(const String&in) const", asMETHOD(XMLElement, GetVectorVariant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool set_value(const String&in)", asMETHODPR(XMLElement, SetValue, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_value() const", asMETHOD(XMLElement, GetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String get_name() const", asMETHOD(XMLElement, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint get_numAttributes() const", asMETHOD(XMLElement, GetNumAttributes), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_isNull() const", asMETHOD(XMLElement, IsNull), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_notNull() const", asMETHOD(XMLElement, NotNull), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_parent() const", asMETHOD(XMLElement, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ get_file() const", asMETHOD(XMLElement, GetFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_nextResult() const", asMETHOD(XMLElement, NextResult), asCALL_THISCALL);

    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXPathResultSet), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_CONSTRUCT, "void f(const XPathResultSet&in)", asFUNCTION(ConstructXPathResultSetCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XPathResultSet", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructXPathResultSet), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XPathResultSet", "XPathResultSet& opAssign(const XPathResultSet&in)", asMETHOD(XPathResultSet, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement opIndex(uint index)", asFUNCTION(XPathResultSetAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XPathResultSet", "XMLElement get_firstResult()", asMETHOD(XPathResultSet, FirstResult), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "uint get_size()", asMETHOD(XPathResultSet, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathResultSet", "bool get_empty()", asMETHOD(XPathResultSet, Empty), asCALL_THISCALL);

    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXPathQuery), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_CONSTRUCT, "void f(const String&in, const String& arg1 = String())", asFUNCTION(ConstructXPathQueryWithString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XPathQuery", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructXPathQuery), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XPathQuery", "void Bind()", asMETHOD(XPathQuery, Bind), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, bool)", asMETHODPR(XPathQuery, SetVariable, (const String&, bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, float)", asMETHODPR(XPathQuery, SetVariable, (const String&, float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const String&in)", asMETHODPR(XPathQuery, SetVariable, (const String&, const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool SetVariable(const String&in, const XPathResultSet&in)", asMETHODPR(XPathQuery, SetVariable, (const String&, const XPathResultSet&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool SetQuery(const String&, const String& arg1 = String(), bool arg2 = true)", asMETHOD(XPathQuery, SetQuery), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "void Clear()", asMETHOD(XPathQuery, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "bool EvaluateToBool(XMLElement)", asMETHOD(XPathQuery, EvaluateToBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "float EvaluateToFloat(XMLElement)", asMETHOD(XPathQuery, EvaluateToFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "String EvaluateToString(XMLElement)", asMETHOD(XPathQuery, EvaluateToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "XPathResultSet Evaluate(XMLElement)", asMETHOD(XPathQuery, Evaluate), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "void set_query(const String&)", asMETHOD(XPathQuery, SetQuery), asCALL_THISCALL);
    engine->RegisterObjectMethod("XPathQuery", "String get_query() const", asMETHOD(XPathQuery, GetQuery), asCALL_THISCALL);
}

static XMLElement XMLFileGetRootDefault(XMLFile* ptr)
{
    return ptr->GetRoot();
}

static void RegisterXMLFile(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("XMLFile", "XMLElement CreateRoot(const String&in)", asMETHOD(XMLFile, CreateRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetRoot(const String&in name = String())", asMETHOD(XMLFile, GetRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement get_root()", asFUNCTION(XMLFileGetRootDefault), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLFile@+)", asMETHODPR(XMLFile, Patch, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLElement)", asMETHODPR(XMLFile, Patch, (XMLElement), void), asCALL_THISCALL);
}

void RegisterResourceAPI(asIScriptEngine* engine)
{
    RegisterResource(engine);
    RegisterResourceCache(engine);
    RegisterImage(engine);
    RegisterXMLElement(engine);
    RegisterXMLFile(engine);
}

}
