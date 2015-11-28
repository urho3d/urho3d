//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include "../IO/PackageFile.h"
#include "../Resource/Image.h"
#include "../Resource/JSONFile.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/Localization.h"

namespace Urho3D
{

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);

void RegisterResource(asIScriptEngine* engine)
{
    RegisterResource<Resource>(engine, "Resource");
}

static Resource* ResourceCacheGetResource(const String& type, const String& name, bool sendEventOnFailure, ResourceCache* ptr)
{
    return ptr->GetResource(StringHash(type), name, sendEventOnFailure);
}

static Resource* ResourceCacheGetExistingResource(const String& type, const String& name, ResourceCache* ptr)
{
    return ptr->GetResource(StringHash(type), name);
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

static void ResourceCacheSetMemoryBudget(const String& type, unsigned long long budget, ResourceCache* ptr)
{
    ptr->SetMemoryBudget(type, budget);
}

static unsigned long long ResourceCacheGetMemoryBudget(const String& type, ResourceCache* ptr)
{
    return ptr->GetMemoryBudget(type);
}

static unsigned long long ResourceCacheGetMemoryUse(const String& type, ResourceCache* ptr)
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

static bool ResourceCacheBackgroundLoadResource(const String& type, const String& name, bool sendEventOnFailure, ResourceCache* ptr)
{
    return ptr->BackgroundLoadResource(type, name, sendEventOnFailure);
}

static Localization* GetLocalization()
{
    return GetScriptContext()->GetSubsystem<Localization>();
}

static void RegisterLocalization(asIScriptEngine* engine)
{
    RegisterObject<Localization>(engine, "Localization");
    engine->RegisterObjectMethod("Localization", "int get_numLanguages() const", asMETHOD(Localization, GetNumLanguages), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_languageIndex() const", asMETHODPR(Localization, GetLanguageIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int GetLanguageIndex(const String&in)", asMETHODPR(Localization, GetLanguageIndex, (const String&), int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "String get_language()", asMETHODPR(Localization, GetLanguage, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "String GetLanguage(int)", asMETHODPR(Localization, GetLanguage, (int), String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void SetLanguage(int)", asMETHODPR(Localization, SetLanguage, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void SetLanguage(const String&in)", asMETHODPR(Localization, SetLanguage, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "String Get(const String&in)", asMETHOD(Localization, Get), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void Reset()", asMETHOD(Localization, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void LoadJSON(const JSONValue&in)", asMETHOD(Localization, LoadJSON), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void LoadJSONFile(const String&in)", asMETHOD(Localization, LoadJSONFile), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Localization@+ get_localization()", asFUNCTION(GetLocalization), asCALL_CDECL);
}

static void RegisterResourceCache(asIScriptEngine* engine)
{
    RegisterObject<ResourceCache>(engine, "ResourceCache");
    engine->RegisterObjectMethod("ResourceCache", "bool AddResourceDir(const String&in, uint priority = M_MAX_UNSIGNED)", asMETHOD(ResourceCache, AddResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(PackageFile@+, uint priority = M_MAX_UNSIGNED)", asMETHODPR(ResourceCache, AddPackageFile, (PackageFile*, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(const String&in, uint priority = M_MAX_UNSIGNED)", asMETHODPR(ResourceCache, AddPackageFile, (const String&, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool AddManualResource(Resource@+)", asMETHOD(ResourceCache, AddManualResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemoveResourceDir(const String&in)", asMETHOD(ResourceCache, RemoveResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(PackageFile@+, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (PackageFile*, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(const String&in, bool releaseResources = true, bool forceRelease = false)", asMETHODPR(ResourceCache, RemovePackageFile, (const String&, bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResource(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(StringHash, bool force = false)", asMETHODPR(ResourceCache, ReleaseResources, (StringHash, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, const String&in, bool force = false)", asFUNCTION(ResourceCacheReleaseResourcesPartial), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, bool force = false)", asMETHODPR(ResourceCache, ReleaseResources, (const String&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseAllResources(bool force = false)", asMETHOD(ResourceCache, ReleaseAllResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool ReloadResource(Resource@+)", asMETHOD(ResourceCache, ReloadResource), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void ReloadResourceWithDependencies(const String&in)", asMETHOD(ResourceCache, ReloadResourceWithDependencies), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool Exists(const String&in) const", asMETHODPR(ResourceCache, Exists, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "File@ GetFile(const String&in)", asFUNCTION(ResourceCacheGetFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "String GetPreferredResourceDir(const String&in) const", asMETHOD(ResourceCache, GetPreferredResourceDir), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceName(const String&in) const", asMETHOD(ResourceCache, SanitateResourceName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceDirName(const String&in) const", asMETHOD(ResourceCache, SanitateResourceDirName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "String GetResourceFileName(const String&in) const", asMETHOD(ResourceCache, GetResourceFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(const String&in, const String&in, bool sendEventOnFailure = true)", asFUNCTION(ResourceCacheGetResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(StringHash, const String&in, bool sendEventOnFailure = true)", asMETHODPR(ResourceCache, GetResource, (StringHash, const String&, bool), Resource*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetExistingResource(const String&in, const String&in)", asFUNCTION(ResourceCacheGetExistingResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetExistingResource(StringHash, const String&in)", asMETHODPR(ResourceCache, GetExistingResource, (StringHash, const String&), Resource*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool BackgroundLoadResource(const String&in, const String&in, bool sendEventOnFailure = true)", asFUNCTION(ResourceCacheBackgroundLoadResource), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void set_memoryBudget(const String&in, uint64)", asFUNCTION(ResourceCacheSetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryBudget(const String&in) const", asFUNCTION(ResourceCacheGetMemoryBudget), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryUse(const String&in) const", asFUNCTION(ResourceCacheGetMemoryUse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_totalMemoryUse() const", asMETHOD(ResourceCache, GetTotalMemoryUse), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ get_resourceDirs() const", asFUNCTION(ResourceCacheGetResourceDirs), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ get_packageFiles() const", asFUNCTION(ResourceCacheGetPackageFiles), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceCache", "void set_searchPackagesFirst(bool)", asMETHOD(ResourceCache, SetSearchPackagesFirst), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_seachPackagesFirst() const", asMETHOD(ResourceCache, GetSearchPackagesFirst), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_autoReloadResources(bool)", asMETHOD(ResourceCache, SetAutoReloadResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_autoReloadResources() const", asMETHOD(ResourceCache, GetAutoReloadResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_returnFailedResources(bool)", asMETHOD(ResourceCache, SetReturnFailedResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_returnFailedResources() const", asMETHOD(ResourceCache, GetReturnFailedResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_finishBackgroundResourcesMs(int)", asMETHOD(ResourceCache, SetFinishBackgroundResourcesMs), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_finishBackgroundResourcesMs() const", asMETHOD(ResourceCache, GetFinishBackgroundResourcesMs), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint get_numBackgroundLoadResources() const", asMETHOD(ResourceCache, GetNumBackgroundLoadResources), asCALL_THISCALL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", asFUNCTION(GetResourceCache), asCALL_CDECL);
}

static bool ImageLoadColorLUT(File* file, Image* ptr)
{
    return file && ptr->LoadColorLUT(*file);
}

static bool ImageLoadColorLUTVectorBuffer(VectorBuffer& buffer, Image* ptr)
{
    return ptr->LoadColorLUT(buffer);
}

static void RegisterImage(asIScriptEngine* engine)
{
    engine->RegisterEnum("CompressedFormat");
    engine->RegisterEnumValue("CompressedFormat", "CF_NONE", 0);
    engine->RegisterEnumValue("CompressedFormat", "CF_RGBA", 1);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT1", 2);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT3", 3);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT5", 4);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC1", 5);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_2BPP", 6);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_2BPP", 7);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_4BPP", 8);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_4BPP", 9);

    RegisterResource<Image>(engine, "Image");
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, uint)", asMETHODPR(Image, SetSize, (int, int, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SetSize(int, int, int, uint)", asMETHODPR(Image, SetSize, (int, int, unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixel(int, int, int, const Color&in)", asMETHODPR(Image, SetPixel, (int, int, int, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, uint)", asMETHODPR(Image, SetPixelInt, (int, int, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void SetPixelInt(int, int, int, uint)", asMETHODPR(Image, SetPixelInt, (int, int, int, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool LoadColorLUT(File@+)", asFUNCTION(ImageLoadColorLUT), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Image", "bool LoadColorLUT(VectorBuffer&)", asFUNCTION(ImageLoadColorLUTVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Image", "bool FlipHorizontal()", asMETHOD(Image, FlipHorizontal), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool FlipVertical()", asMETHOD(Image, FlipVertical), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool Resize(int, int)", asMETHOD(Image, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void Clear(const Color&in)", asMETHOD(Image, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "void ClearInt(uint)", asMETHOD(Image, ClearInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SaveBMP(const String&in) const", asMETHOD(Image, SaveBMP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SavePNG(const String&in) const", asMETHOD(Image, SavePNG), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SaveTGA(const String&in) const", asMETHOD(Image, SaveTGA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool SaveJPG(const String&in, int) const", asMETHOD(Image, SaveJPG), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int) const", asMETHODPR(Image, GetPixel, (int, int) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixel(int, int, int) const", asMETHODPR(Image, GetPixel, (int, int, int) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int) const", asMETHODPR(Image, GetPixelInt, (int, int) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint GetPixelInt(int, int, int) const", asMETHODPR(Image, GetPixelInt, (int, int, int) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixelBilinear(float, float) const", asMETHODPR(Image, GetPixelBilinear, (float, float) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Color GetPixelTrilinear(float, float, float) const", asMETHODPR(Image, GetPixelTrilinear, (float, float, float) const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_width() const", asMETHOD(Image, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_height() const", asMETHOD(Image, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "int get_depth() const", asMETHOD(Image, GetDepth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_components() const", asMETHOD(Image, GetComponents), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_compressed() const", asMETHOD(Image, IsCompressed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "CompressedFormat get_compressedFormat() const", asMETHOD(Image, GetCompressedFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "uint get_numCompressedLevels() const", asMETHOD(Image, GetNumCompressedLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "Image@+ GetSubimage(const IntRect&in) const", asMETHOD(Image, GetSubimage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_cubemap() const", asMETHOD(Image, IsCubemap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_array() const", asMETHOD(Image, IsArray), asCALL_THISCALL);
    engine->RegisterObjectMethod("Image", "bool get_sRGB() const", asMETHOD(Image, IsSRGB), asCALL_THISCALL);
}

static void ConstructJSONValue(JSONValue* ptr)
{
    new(ptr) JSONValue();
}

static void ConstructJSONValueBool(bool value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueInt(int value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueUnsigned(unsigned value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueFloat(float value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueDouble(double value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueString(const String& value, JSONValue* ptr)
{
    new (ptr) JSONValue(value);
}

static void ConstructJSONValueCopy(const JSONValue& value, JSONValue* ptr)
{
    new(ptr) JSONValue(value);
}

static void DestructJSONValue(JSONValue* ptr)
{
    ptr->~JSONValue();
}

static JSONValue& JSONValueAtPosition(unsigned position, JSONValue& jsonValue)
{
    return jsonValue[position];
}

static JSONValue& JSONValueAtKey(const String& key, JSONValue& jsonValue)
{
    return jsonValue[key];
}

static void RegisterJSONValue(asIScriptEngine* engine)
{
    engine->RegisterEnum("JSONValueType");
    engine->RegisterEnumValue("JSONValueType", "JSON_NULL", JSON_NULL);
    engine->RegisterEnumValue("JSONValueType", "JSON_BOOL", JSON_BOOL);
    engine->RegisterEnumValue("JSONValueType", "JSON_NUMBER", JSON_NUMBER);
    engine->RegisterEnumValue("JSONValueType", "JSON_STRING", JSON_STRING);
    engine->RegisterEnumValue("JSONValueType", "JSON_ARRAY", JSON_ARRAY);
    engine->RegisterEnumValue("JSONValueType", "JSON_OBJECT", JSON_OBJECT);

    engine->RegisterObjectType("JSONValue", sizeof(JSONValue), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructJSONValue), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructJSONValueBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructJSONValueInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructJSONValueUnsigned), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructJSONValueFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(ConstructJSONValueDouble), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructJSONValueString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const JSONValue&in)", asFUNCTION(ConstructJSONValueCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructJSONValue), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(bool)", asMETHODPR(JSONValue, operator =, (bool), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(int)", asMETHODPR(JSONValue, operator =, (int), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(uint)", asMETHODPR(JSONValue, operator =, (unsigned), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(float)", asMETHODPR(JSONValue, operator =, (float), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(double)", asMETHODPR(JSONValue, operator =, (double), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const String&in)", asMETHODPR(JSONValue, operator =, (const String&), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const JSONValue&in)", asMETHODPR(JSONValue, operator =, (const JSONValue&), JSONValue&), asCALL_THISCALL);

    engine->RegisterObjectMethod("JSONValue", "JSONValueType get_valueType() const", asMETHOD(JSONValue, GetValueType), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNull() const", asMETHOD(JSONValue, IsNull), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isBool() const", asMETHOD(JSONValue, IsBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNumber() const", asMETHOD(JSONValue, IsNumber), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isString() const", asMETHOD(JSONValue, IsString), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isArray() const", asMETHOD(JSONValue, IsArray), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isObject() const", asMETHOD(JSONValue, IsObject), asCALL_THISCALL);

    engine->RegisterObjectMethod("JSONValue", "bool GetBool() const", asMETHOD(JSONValue, GetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "int GetInt() const", asMETHOD(JSONValue, GetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "uint GetUInt() const", asMETHOD(JSONValue, GetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "float GetFloat() const", asMETHOD(JSONValue, GetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "double GetDouble() const", asMETHOD(JSONValue, GetDouble), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "const String& GetString() const", asMETHOD(JSONValue, GetString), asCALL_THISCALL);

    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(uint)", asFUNCTION(JSONValueAtPosition), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(uint) const", asFUNCTION(JSONValueAtPosition), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("JSONValue", "void Push(const JSONValue&in)", asMETHOD(JSONValue, Push), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "void Pop()", asMETHOD(JSONValue, Pop), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "void Insert(uint, const JSONValue&in)", asMETHODPR(JSONValue, Insert, (unsigned, const JSONValue&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "void Erase(uint, uint length = 1)", asMETHODPR(JSONValue, Erase, (unsigned, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "void Resize(uint)", asMETHOD(JSONValue, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "uint get_size()", asMETHOD(JSONValue, Size), asCALL_THISCALL);

    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(const String&in)", asFUNCTION(JSONValueAtKey), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(const String&in) const", asFUNCTION(JSONValueAtKey), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("JSONValue", "void Set(const String&in, const JSONValue&in)", asMETHOD(JSONValue, Set), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& Get(const String&in) const", asMETHOD(JSONValue, Get), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "void Erase(const String&in)", asMETHODPR(JSONValue, Erase, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool Contains(const String&in) const", asMETHOD(JSONValue, Contains), asCALL_THISCALL);

    engine->RegisterObjectMethod("JSONValue", "void Clear()", asMETHOD(JSONValue, Clear), asCALL_THISCALL);
}

static bool JSONFileSave(File* file, const String& indendation, JSONFile* ptr)
{
    return file && ptr->Save(*file, indendation);
}

static void RegisterJSONFile(asIScriptEngine* engine)
{
    RegisterResource<JSONFile>(engine, "JSONFile");
    engine->RegisterObjectMethod("JSONFile", "const JSONValue& GetRoot() const", asMETHODPR(JSONFile, GetRoot, () const, const JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "bool Save(File@+, const String&in) const", asFUNCTION(JSONFileSave), asCALL_CDECL_OBJLAST);
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

static bool XMLElementSetVariantVector(CScriptArray* value, XMLElement* ptr)
{
    VariantVector src;
    ArrayToVariantVector(value, src);
    return ptr->SetVariantVector(src);
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
    engine->RegisterObjectMethod("XMLElement", "bool SetDouble(const String&in, double)", asMETHOD(XMLElement, SetDouble), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetInt(const String&in, int)", asMETHOD(XMLElement, SetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetUInt(const String&in, uint)", asMETHOD(XMLElement, SetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetIntRect(const String&in, const IntRect&in)", asMETHOD(XMLElement, SetIntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetIntVector2(const String&in, const IntVector2&in)", asMETHOD(XMLElement, SetIntVector2), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3(const String&in, const Matrix3&in)", asMETHOD(XMLElement, SetMatrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix3x4(const String&in, const Matrix3x4&in)", asMETHOD(XMLElement, SetMatrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "bool SetMatrix4(const String&in, const Matrix4&in)", asMETHOD(XMLElement, SetMatrix4), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("XMLElement", "double GetDouble(const String&in) const", asMETHOD(XMLElement, GetDouble), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "uint GetUInt(const String&in) const", asMETHOD(XMLElement, GetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "int GetInt(const String&in) const", asMETHOD(XMLElement, GetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "IntRect GetIntRect(const String&in) const", asMETHOD(XMLElement, GetIntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "IntVector2 GetIntVector2(const String&in) const", asMETHOD(XMLElement, GetIntVector2), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("XMLElement", "Matrix3 GetMatrix3(const String&in) const", asMETHOD(XMLElement, GetMatrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Matrix3x4 GetMatrix3x4(const String&in) const", asMETHOD(XMLElement, GetMatrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLElement", "Matrix4 GetMatrix4(const String&in) const", asMETHOD(XMLElement, GetMatrix4), asCALL_THISCALL);
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

static bool XMLFileSave(File* file, const String& indendation, XMLFile* ptr)
{
    return file && ptr->Save(*file, indendation);
}

static void RegisterXMLFile(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("XMLFile", "bool FromString(const String&in)", asMETHOD(XMLFile, FromString), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement CreateRoot(const String&in)", asMETHOD(XMLFile, CreateRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement GetRoot(const String&in name = String())", asMETHOD(XMLFile, GetRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "bool Save(File@+, const String&in) const", asFUNCTION(XMLFileSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLFile", "String ToString(const String&in = String(\"\t\")) const", asMETHOD(XMLFile, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "XMLElement get_root()", asFUNCTION(XMLFileGetRootDefault), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLFile@+)", asMETHODPR(XMLFile, Patch, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("XMLFile", "void Patch(XMLElement)", asMETHODPR(XMLFile, Patch, (XMLElement), void), asCALL_THISCALL);
}

void RegisterResourceAPI(asIScriptEngine* engine)
{
    RegisterResource(engine);
    RegisterResourceCache(engine);
    RegisterImage(engine);
    RegisterJSONValue(engine);
    RegisterJSONFile(engine);
    RegisterXMLElement(engine);
    RegisterXMLFile(engine);
    RegisterLocalization(engine);
}

}
