//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "PackageFile.h"
#include "ResourceCache.h"

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
    ptr->ReleaseResource(ShortStringHash(type), name, force);
}

static void ResourceCacheReleaseResources(const String& type, bool force, ResourceCache* ptr)
{
    ptr->ReleaseResources(ShortStringHash(type), force);
}

static void ResourceCacheReleaseResourcesPartial(const String& type, const String& partialName, bool force, ResourceCache* ptr)
{
    ptr->ReleaseResources(ShortStringHash(type), partialName, force);
}

static void ResourceCacheSetMemoryBudget(const String& type, unsigned budget, ResourceCache* ptr)
{
    ptr->SetMemoryBudget(ShortStringHash(type), budget);
}

static unsigned ResourceCacheGetMemoryBudget(const String& type, ResourceCache* ptr)
{
    return ptr->GetMemoryBudget(ShortStringHash(type));
}

static unsigned ResourceCacheGetMemoryUse(const String& type, ResourceCache* ptr)
{
    return ptr->GetMemoryUse(ShortStringHash(type));
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
    engine->RegisterObjectMethod("ResourceCache", "bool AddResourceDir(const String&in)", asMETHOD(ResourceCache, AddResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void AddPackageFile(PackageFile@+, bool addAsFirst = false)", asMETHOD(ResourceCache, AddPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool AddManualResource(Resource@+)", asMETHOD(ResourceCache, AddManualResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemoveResourceDir(const String&in)", asMETHOD(ResourceCache, RemoveResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(PackageFile@+, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (PackageFile*, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(const String&in, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (const String&, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResource(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResources), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResourcesPartial), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseAllResources(bool force = false)", asMETHOD(ResourceCache, ReleaseAllResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool ReloadResource(Resource@+)", asMETHOD(ResourceCache, ReloadResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool Exists(const String&in) const", asMETHODPR(ResourceCache, Exists, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "File@ GetFile(const String&in)", asFUNCTION(ResourceCacheGetFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "String GetPreferredResourceDir(const String&in)", asMETHOD(ResourceCache, GetPreferredResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceName(const String&in)", asMETHOD(ResourceCache, SanitateResourceName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const String& GetResourceName(StringHash)", asMETHOD(ResourceCache, GetResourceName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(const String&in, const String&in)", asFUNCTION(ResourceCacheGetResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(ShortStringHash, StringHash)", asMETHODPR(ResourceCache, GetResource, (ShortStringHash, StringHash), Resource*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_memoryBudget(const String&in, uint)", asFUNCTION(ResourceCacheSetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_memoryBudget(const String&in) const", asFUNCTION(ResourceCacheGetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_memoryUse(const String&in) const", asFUNCTION(ResourceCacheGetMemoryUse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint get_totalMemoryUse() const", asMETHOD(ResourceCache, GetTotalMemoryUse), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ get_resourceDirs() const", asFUNCTION(ResourceCacheGetResourceDirs), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ get_packageFiles() const", asFUNCTION(ResourceCacheGetPackageFiles), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
}

static void RegisterImage(asIScriptEngine* engine)
{
    RegisterResource<Image>(engine, "Image");
    engine->RegisterObjectMethod("Image", "void SaveBMP(const String&in)", asMETHOD(Image, SaveBMP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SaveTGA(const String&in)", asMETHOD(Image, SaveTGA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_width() const", asMETHOD(Image, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_height() const", asMETHOD(Image, GetHeight), asCALL_THISCALL);
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

static void RegisterXMLElement(asIScriptEngine* engine)
{
    RegisterResource<XMLFile>(engine, "XMLFile");
    engine->RegisterObjectType("XMLElement", sizeof(XMLElement), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXMLElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement&in)", asFUNCTION(ConstructXMLElementCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructXMLElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "XMLElement& opAssign(const XMLElement&in)", asMETHOD(XMLElement, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement CreateChild(const String&in)", asMETHODPR(XMLElement, CreateChild, (const String&), XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const XMLElement&in)", asMETHODPR(XMLElement, RemoveChild, (const XMLElement&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChild(const String&in)", asMETHODPR(XMLElement, RemoveChild, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool RemoveChildren(const String&in name = String())", asMETHODPR(XMLElement, RemoveChildren, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetAttribute(const String&in, const String&in)", asMETHODPR(XMLElement, SetAttribute, (const String&, const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetBool(const String&in, bool)", asMETHOD(XMLElement, SetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetBoundingBox(const BoundingBox&in)", asMETHOD(XMLElement, SetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetColor(const String&in, const Color&in)", asMETHOD(XMLElement, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetFloat(const String&in, float)", asMETHOD(XMLElement, SetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetInt(const String&in, int)", asMETHOD(XMLElement, SetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetQuaternion(const String&in, const Quaternion&in)", asMETHOD(XMLElement, SetQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariant(const Variant&in)", asMETHOD(XMLElement, SetVariant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRef(const String&in, const ResourceRef&in)", asMETHOD(XMLElement, SetResourceRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetResourceRefList(const String&in, const ResourceRefList&in)", asMETHOD(XMLElement, SetResourceRefList), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantVector(Array<Variant>@+)", asFUNCTION(XMLElementSetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "bool SetVariantMap(const VariantMap&in)", asMETHOD(XMLElement, SetVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector2(const String&in, const Vector2&in)", asMETHOD(XMLElement, SetVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector3(const String&in, const Vector3&in)", asMETHOD(XMLElement, SetVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetVector4(const String&in, const Vector3&in)", asMETHOD(XMLElement, SetVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint GetNumAttributes() const", asMETHOD(XMLElement, GetNumAttributes), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool HasAttribute(const String&in) const", asMETHODPR(XMLElement, HasAttribute, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "String GetAttribute(const String&in) const", asMETHODPR(XMLElement, GetAttribute, (const String&) const, String), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("XMLElement", "String get_name() const", asMETHOD(XMLElement, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_isNull() const", asMETHOD(XMLElement, IsNull), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool get_notNull() const", asMETHOD(XMLElement, NotNull), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement get_parent() const", asMETHOD(XMLElement, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLFile@+ get_file() const", asMETHOD(XMLElement, GetFile), asCALL_THISCALL);
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
}

void RegisterResourceAPI(asIScriptEngine* engine)
{
    RegisterResource(engine);
    RegisterResourceCache(engine);
    RegisterImage(engine);
    RegisterXMLElement(engine);
    RegisterXMLFile(engine);
}
