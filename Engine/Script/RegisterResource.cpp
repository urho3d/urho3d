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
#include "Log.h"
#include "RegisterTemplates.h"
#include "ScriptInstance.h"
#include "Scene.h"

void registerResource(asIScriptEngine* engine)
{
    registerResource<Resource>(engine, "Resource");
}

static Resource* ResourceCacheGetResource(const std::string& type, const std::string& name, ResourceCache* ptr)
{
    try
    {
        return ptr->getResource(ShortStringHash(type), name);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static File* ResourceCacheGetFile(const std::string& name, ResourceCache* ptr)
{
    try
    {
        SharedPtr<File> file = ptr->getFile(name);
        // The shared pointer will go out of scope, so have to increment the reference count
        // (here an auto handle can not be used)
        if (file)
            file->addRef();
        return file.getPtr();
    }
    catch (Exception& e)
    {
        SAFE_RETHROW_RET(e, 0);
    }
}

static void ResourceCacheReleaseResource(const std::string& type, const std::string& name, bool force, ResourceCache* ptr)
{
    ptr->releaseResource(ShortStringHash(type), name, force);
}

static void ResourceCacheReleaseResources(const std::string& type, bool force, ResourceCache* ptr)
{
    ptr->releaseResources(ShortStringHash(type), force);
}

static void ResourceCacheReleaseResourcesPartial(const std::string& type, const std::string& partialName, bool force, ResourceCache* ptr)
{
    ptr->releaseResources(ShortStringHash(type), partialName, force);
}

static void ResourceCacheReloadResource(Resource* resource, ResourceCache* ptr)
{
    try
    {
        return ptr->reloadResource(resource);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void ResourceCacheSetMemoryBudget(const std::string& type, unsigned budget, ResourceCache* ptr)
{
    ptr->setMemoryBudget(ShortStringHash(type), budget);
}

static unsigned ResourceCacheGetMemoryBudget(const std::string& type, ResourceCache* ptr)
{
    return ptr->getMemoryBudget(ShortStringHash(type));
}

static unsigned ResourceCacheGetMemoryUse(const std::string& type, ResourceCache* ptr)
{
    return ptr->getMemoryUse(ShortStringHash(type));
}

static void registerResourceCache(asIScriptEngine* engine)
{
    engine->RegisterObjectType("ResourceCache", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_ADDREF, "void f()", asMETHOD(ResourceCache, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_RELEASE, "void f()", asMETHOD(ResourceCache, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void addResourcePath(const string& in)", asMETHOD(ResourceCache, addResourcePath), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void addPackageFile(PackageFile@+)", asMETHOD(ResourceCache, addPackageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void removeResourcePath(const string& in)", asMETHOD(ResourceCache, removeResourcePath), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void removePackageFile(PackageFile@+, bool, bool)", asMETHODPR(ResourceCache, removePackageFile, (PackageFile*, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void removePackageFile(const string& in, bool, bool)", asMETHODPR(ResourceCache, removePackageFile, (const std::string&, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void releaseResource(const string& in, const string& in, bool)", asFUNCTION(ResourceCacheReleaseResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void releaseResources(const string& in, bool)", asFUNCTION(ResourceCacheReleaseResources), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void releaseResources(const string& in, const string& in, bool)", asFUNCTION(ResourceCacheReleaseResourcesPartial), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void reloadResource(Resource@+)", asFUNCTION(ResourceCacheReloadResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void setMemoryBudget(const string& in, uint)", asFUNCTION(ResourceCacheSetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "bool exists(const string& in) const", asMETHODPR(ResourceCache, exists, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "File@ getFile(const string& in)", asFUNCTION(ResourceCacheGetFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ getResource(const string& in, const string& in)", asFUNCTION(ResourceCacheGetResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint getMemoryBudget(const string& in) const", asFUNCTION(ResourceCacheGetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint getMemoryUse(const string& in) const", asFUNCTION(ResourceCacheGetMemoryUse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint getTotalMemoryUse() const", asMETHOD(ResourceCache, getTotalMemoryUse), asCALL_THISCALL);
    engine->RegisterGlobalFunction("ResourceCache@+ getResourceCache()", asFUNCTION(getResourceCache), asCALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", asFUNCTION(getResourceCache), asCALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", asFUNCTION(getResourceCache), asCALL_CDECL);
}

static Image* ConstructImage(const std::string& name)
{
    return new Image(name);
}

static void registerImage(asIScriptEngine* engine)
{
    registerResource<Image>(engine, "Image");
    engine->RegisterObjectMethod("Image", "void saveBMP(const string& in)", asMETHOD(Image, saveBMP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void saveTGA(const string& in)", asMETHOD(Image, saveTGA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int getWidth() const", asMETHOD(Image, getWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int getHeight() const", asMETHOD(Image, getHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint getComponents() const", asMETHOD(Image, getComponents), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool isCompressed() const", asMETHOD(Image, isCompressed), asCALL_THISCALL);
    registerRefCasts<Resource, Image>(engine, "Resource", "Image");
}

static void ConstructXMLElement(XMLElement* ptr)
{
    new(ptr) XMLElement();
}

static void ConstructXMLElementCopy(const XMLElement& element, XMLElement* ptr)
{
    new(ptr) XMLElement(element);
}

static void registerXMLElement(asIScriptEngine* engine)
{
    engine->RegisterObjectType("XMLElement", sizeof(XMLElement), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXMLElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("XMLElement", asBEHAVE_CONSTRUCT, "void f(const XMLElement& in)", asFUNCTION(ConstructXMLElementCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLElement", "bool isNull() const", asMETHODPR(XMLElement, isNull, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool notNull() const", asMETHODPR(XMLElement, notNull, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement createChildElement(const string& in)", asMETHODPR(XMLElement, createChildElement, (const std::string&), XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getAttribute(const string& in, bool) const", asMETHODPR(XMLElement, getAttribute, (const std::string&, bool) const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool getBool(const string& in, bool) const", asMETHODPR(XMLElement, getBool, (const std::string&, bool) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "BoundingBox getBoundingBox(bool) const", asMETHODPR(XMLElement, getBoundingBox, (bool) const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement getChildElement(const string& in, bool) const", asMETHODPR(XMLElement, getChildElement, (const std::string&, bool) const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Color getColor(const string& in, bool) const", asMETHODPR(XMLElement, getColor, (const std::string&, bool) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "float getFloat(const string& in, bool) const", asMETHODPR(XMLElement, getFloat, (const std::string&, bool) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "int getInt(const string& in, bool) const", asMETHODPR(XMLElement, getInt, (const std::string&, bool) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getName() const", asMETHODPR(XMLElement, getName, () const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "XMLElement getNextElement(const string& in) const", asMETHODPR(XMLElement, getNextElement, (const std::string&) const, XMLElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Quaternion getQuaternion(const string& in, bool) const", asMETHODPR(XMLElement, getQuaternion, (const std::string&, bool) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getString(const string& in, bool) const", asMETHODPR(XMLElement, getString, (const std::string&, bool) const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getStringLower(const string& in, bool) const", asMETHODPR(XMLElement, getStringLower, (const std::string&, bool) const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getStringUpper(const string& in, bool) const", asMETHODPR(XMLElement, getStringUpper, (const std::string&, bool) const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "string getText() const", asMETHODPR(XMLElement, getText, () const, std::string), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Variant getVariant(bool) const", asMETHODPR(XMLElement, getVariant, (bool) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "VariantMap getVariantMap(bool) const", asMETHODPR(XMLElement, getVariantMap, (bool) const, VariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Vector2 getVector2(const string& in, bool) const", asMETHODPR(XMLElement, getVector2, (const std::string&, bool) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Vector3 getVector3(const string& in, bool) const", asMETHODPR(XMLElement, getVector3, (const std::string&, bool) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool hasAttribute(const string& in) const", asMETHODPR(XMLElement, hasAttribute, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool hasChildElement(const string& in) const", asMETHODPR(XMLElement, hasChildElement, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void removeChildElement(const string& in, bool)", asMETHODPR(XMLElement,removeChildElement, (const std::string&, bool), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setAttribute(const string& in, const string& in)", asMETHODPR(XMLElement,setAttribute, (const std::string&, const std::string&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setBool(const string& in, bool)", asMETHODPR(XMLElement,setBool, (const std::string&, bool), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setBoundingBox(const BoundingBox& in)", asMETHODPR(XMLElement,setBoundingBox, (const BoundingBox&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setColor(const string& in, const Color& in)", asMETHODPR(XMLElement,setColor, (const std::string&, const Color&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setFloat(const string& in, float)", asMETHODPR(XMLElement,setFloat, (const std::string&, float), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setInt(const string& in, int)", asMETHODPR(XMLElement,setInt, (const std::string&, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setQuaternion(const string& in, const Quaternion& in)", asMETHODPR(XMLElement,setQuaternion, (const std::string&, const Quaternion&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setString(const string& in, const string& in)", asMETHODPR(XMLElement,setString, (const std::string&, const std::string&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setVariant(const Variant& in)", asMETHODPR(XMLElement,setVariant, (const Variant&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setVariantMap(const VariantMap& in)", asMETHODPR(XMLElement,setVariantMap, (const VariantMap&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setVector2(const string& in, const Vector2& in)", asMETHODPR(XMLElement,setVector2, (const std::string&, const Vector2&), void ), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "void setVector3(const string& in, const Vector3& in)", asMETHODPR(XMLElement,setVector3, (const std::string&, const Vector3&), void ), asCALL_THISCALL);
}

static XMLFile* ConstructXMLFile(const std::string& name)
{
    return new XMLFile(name);
}

static void XMLFileLoad(File* file, XMLFile* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null file");
    try
    {
        ptr->load(*file);
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void registerXMLFile(asIScriptEngine* engine)
{
    registerResource<XMLFile>(engine, "XMLFile");
    engine->RegisterObjectMethod("XMLFile", "void save(const string& in)", asMETHOD(XMLFile, save), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void load(File@+)", asFUNCTION(XMLFileLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLFile", "XMLElement createRootElement(const string& in)", asMETHOD(XMLFile, createRootElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement getRootElement(const string& in, bool)", asMETHOD(XMLFile, getRootElement), asCALL_THISCALL);
    registerRefCasts<Resource, XMLFile>(engine, "Resource", "XMLFile");
}

void registerResourceLibrary(asIScriptEngine* engine)
{
    registerResource(engine);
    registerResourceCache(engine);
    registerImage(engine);
    registerXMLElement(engine);
    registerXMLFile(engine);
}
