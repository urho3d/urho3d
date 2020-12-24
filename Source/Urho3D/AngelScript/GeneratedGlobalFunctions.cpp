// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"

namespace Urho3D
{

// const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
static CScriptArray* GetArguments_void()
{
    const Vector<String>& result = GetArguments();
    return VectorToArray<String>(result, "Array<String>");
}

// const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument=true) | File: ../Core/ProcessUtils.h
static CScriptArray* ParseArguments_String_bool(const String& cmdLine, bool skipFirstArgument)
{
    const Vector<String>& result = ParseArguments(cmdLine, skipFirstArgument);
    return VectorToArray<String>(result, "Array<String>");
}

// bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV=false) | File: ../Graphics/Drawable.h
static bool WriteDrawablesToOBJ_PODVectorDrawable_File_bool_bool_bool(CScriptArray* drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV)
{
    PODVector<Drawable*> param0 = ArrayToPODVector<Drawable*>(drawables);
    bool result = WriteDrawablesToOBJ(param0, outputFile, asZUp, asRightHanded, writeLightmapUV);
    return result;
}

void ASRegisterGeneratedGlobalFunctions(asIScriptEngine* engine)
{
    // template<class T> T Abs(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Abs(float)", asFUNCTIONPR(Abs, (float), float), asCALL_CDECL);

    // template<class T> T Acos(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Acos(float)", asFUNCTIONPR(Acos, (float), float), asCALL_CDECL);

    // String AddTrailingSlash(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String AddTrailingSlash(const String&in)", asFUNCTIONPR(AddTrailingSlash, (const String&), String), asCALL_CDECL);

    // void AllocatorFree(AllocatorBlock* allocator, void* ptr) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity=1) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // void* AllocatorReserve(AllocatorBlock* allocator) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // void AllocatorUninitialize(AllocatorBlock* allocator) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // template<class T> T Asin(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Asin(float)", asFUNCTIONPR(Asin, (float), float), asCALL_CDECL);

    // template<class T> T Atan(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Atan(float)", asFUNCTIONPR(Atan, (float), float), asCALL_CDECL);

    // template<class T> T Atan2(T y, T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Atan2(float, float)", asFUNCTIONPR(Atan2, (float, float), float), asCALL_CDECL);

    // void BufferToString(String& dest, const void* data, unsigned size) | File: ../Core/StringUtils.h
    // Error: type "void*" can not automatically bind

    // template<class T> T Ceil(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Ceil(float)", asFUNCTIONPR(Ceil, (float), float), asCALL_CDECL);

    // template<class T> int CeilToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int CeilToInt(float)", asFUNCTIONPR(CeilToInt, (float), int), asCALL_CDECL);

    // template<class T> T Clamp(T value, T min, T max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Clamp(float, float, float)", asFUNCTIONPR(Clamp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Clamp(int, int, int)", asFUNCTIONPR(Clamp, (int, int, int), int), asCALL_CDECL);

    // unsigned ClosestPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint ClosestPowerOfTwo(uint)", asFUNCTIONPR(ClosestPowerOfTwo, (unsigned), unsigned), asCALL_CDECL);

    // void CombineHash(unsigned& result, unsigned hash) | File: ../Container/Hash.h
    engine->RegisterGlobalFunction("void CombineHash(uint&, uint)", asFUNCTIONPR(CombineHash, (unsigned&, unsigned), void), asCALL_CDECL);

    // bool CompareDrawables(Drawable* lhs, Drawable* rhs) | File: ../Graphics/Drawable.h
    engine->RegisterGlobalFunction("bool CompareDrawables(Drawable@+, Drawable@+)", asFUNCTIONPR(CompareDrawables, (Drawable*, Drawable*), bool), asCALL_CDECL);

    // bool CompareLights(Light* lhs, Light* rhs) | File: ../Graphics/Light.h
    engine->RegisterGlobalFunction("bool CompareLights(Light@+, Light@+)", asFUNCTIONPR(CompareLights, (Light*, Light*), bool), asCALL_CDECL);

    // unsigned CompressData(void* dest, const void* src, unsigned srcSize) | File: ../IO/Compression.h
    // Error: type "void*" can not automatically bind

    // bool CompressStream(Serializer& dest, Deserializer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("bool CompressStream(Serializer&, Deserializer&)", asFUNCTIONPR(CompressStream, (Serializer&, Deserializer&), bool), asCALL_CDECL);

    // VectorBuffer CompressVectorBuffer(VectorBuffer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("VectorBuffer CompressVectorBuffer(VectorBuffer&)", asFUNCTIONPR(CompressVectorBuffer, (VectorBuffer&), VectorBuffer), asCALL_CDECL);

    // template<class T> T Cos(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Cos(float)", asFUNCTIONPR(Cos, (float), float), asCALL_CDECL);

    // unsigned CountSetBits(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint CountSetBits(uint)", asFUNCTIONPR(CountSetBits, (unsigned), unsigned), asCALL_CDECL);

    // PODVector<unsigned char> DecodeBase64(String encodedString) | File: ../Core/StringUtils.h
    // Error: type "PODVector<unsigned char>" can not automatically bind

    // unsigned DecompressData(void* dest, const void* src, unsigned destSize) | File: ../IO/Compression.h
    // Error: type "void*" can not automatically bind

    // void DecompressImageDXT(unsigned char* rgba, const void* blocks, int width, int height, int depth, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // void DecompressImageETC(unsigned char* dstImage, const void* blocks, int width, int height, bool hasAlpha) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // void DecompressImagePVRTC(unsigned char* rgba, const void* blocks, int width, int height, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // bool DecompressStream(Serializer& dest, Deserializer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("bool DecompressStream(Serializer&, Deserializer&)", asFUNCTIONPR(DecompressStream, (Serializer&, Deserializer&), bool), asCALL_CDECL);

    // VectorBuffer DecompressVectorBuffer(VectorBuffer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("VectorBuffer DecompressVectorBuffer(VectorBuffer&)", asFUNCTIONPR(DecompressVectorBuffer, (VectorBuffer&), VectorBuffer), asCALL_CDECL);

    // template<class T> bool Equals(T lhs, T rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool Equals(float, float)", asFUNCTIONPR(Equals, (float, float), bool), asCALL_CDECL);

    // void ErrorDialog(const String& title, const String& message) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void ErrorDialog(const String&in, const String&in)", asFUNCTIONPR(ErrorDialog, (const String&, const String&), void), asCALL_CDECL);

    // void ErrorExit(const String& message=String::EMPTY, int exitCode=EXIT_FAILURE) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void ErrorExit(const String&in = String::EMPTY, int = EXIT_FAILURE)", asFUNCTIONPR(ErrorExit, (const String&, int), void), asCALL_CDECL);

    // unsigned EstimateCompressBound(unsigned srcSize) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("uint EstimateCompressBound(uint)", asFUNCTIONPR(EstimateCompressBound, (unsigned), unsigned), asCALL_CDECL);

    // void FlipBlockHorizontal(unsigned char* dest, const unsigned char* src, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // void FlipBlockVertical(unsigned char* dest, const unsigned char* src, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // unsigned short FloatToHalf(float value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint16 FloatToHalf(float)", asFUNCTIONPR(FloatToHalf, (float), unsigned short), asCALL_CDECL);

    // unsigned FloatToRawIntBits(float value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint FloatToRawIntBits(float)", asFUNCTIONPR(FloatToRawIntBits, (float), unsigned), asCALL_CDECL);

    // template<class T> T Floor(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Floor(float)", asFUNCTIONPR(Floor, (float), float), asCALL_CDECL);

    // template<class T> int FloorToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int FloorToInt(float)", asFUNCTIONPR(FloorToInt, (float), int), asCALL_CDECL);

    // template<class T> T Fract(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Fract(float)", asFUNCTIONPR(Fract, (float), float), asCALL_CDECL);

    // void GenerateTangents(void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, unsigned normalOffset, unsigned texCoordOffset, unsigned tangentOffset) | File: ../Graphics/Tangent.h
    // Error: type "void*" can not automatically bind

    // const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("Array<String>@ GetArguments()", asFUNCTION(GetArguments_void), asCALL_CDECL);

    // const char* GetCompilerDefines() | File: ../LibraryInfo.h
    // Error: type "const char*" can not automatically bind

    // String GetConsoleInput() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetConsoleInput()", asFUNCTIONPR(GetConsoleInput, (), String), asCALL_CDECL);

    // StringHashRegister& GetEventNameRegister() | File: ../Core/Object.h
    engine->RegisterGlobalFunction("StringHashRegister& GetEventNameRegister()", asFUNCTIONPR(GetEventNameRegister, (), StringHashRegister&), asCALL_CDECL);

    // String GetExtension(const String& fullPath, bool lowercaseExtension=true) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetExtension(const String&in, bool = true)", asFUNCTIONPR(GetExtension, (const String&, bool), String), asCALL_CDECL);

    // String GetFileName(const String& fullPath) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetFileName(const String&in)", asFUNCTIONPR(GetFileName, (const String&), String), asCALL_CDECL);

    // String GetFileNameAndExtension(const String& fileName, bool lowercaseExtension=false) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetFileNameAndExtension(const String&in, bool = false)", asFUNCTIONPR(GetFileNameAndExtension, (const String&, bool), String), asCALL_CDECL);

    // String GetFileSizeString(unsigned long long memorySize) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("String GetFileSizeString(uint64)", asFUNCTIONPR(GetFileSizeString, (unsigned long long), String), asCALL_CDECL);

    // String GetHostName() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetHostName()", asFUNCTIONPR(GetHostName, (), String), asCALL_CDECL);

    // String GetInternalPath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetInternalPath(const String&in)", asFUNCTIONPR(GetInternalPath, (const String&), String), asCALL_CDECL);

    // String GetLoginName() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetLoginName()", asFUNCTIONPR(GetLoginName, (), String), asCALL_CDECL);

    // String GetMiniDumpDir() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetMiniDumpDir()", asFUNCTIONPR(GetMiniDumpDir, (), String), asCALL_CDECL);

    // String GetNativePath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetNativePath(const String&in)", asFUNCTIONPR(GetNativePath, (const String&), String), asCALL_CDECL);

    // unsigned GetNumLogicalCPUs() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint GetNumLogicalCPUs()", asFUNCTIONPR(GetNumLogicalCPUs, (), unsigned), asCALL_CDECL);

    // unsigned GetNumPhysicalCPUs() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint GetNumPhysicalCPUs()", asFUNCTIONPR(GetNumPhysicalCPUs, (), unsigned), asCALL_CDECL);

    // String GetOSVersion() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetOSVersion()", asFUNCTIONPR(GetOSVersion, (), String), asCALL_CDECL);

    // String GetParentPath(const String& path) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetParentPath(const String&in)", asFUNCTIONPR(GetParentPath, (const String&), String), asCALL_CDECL);

    // String GetPath(const String& fullPath) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetPath(const String&in)", asFUNCTIONPR(GetPath, (const String&), String), asCALL_CDECL);

    // String GetPlatform() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetPlatform()", asFUNCTIONPR(GetPlatform, (), String), asCALL_CDECL);

    // unsigned GetRandomSeed() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("uint GetRandomSeed()", asFUNCTIONPR(GetRandomSeed, (), unsigned), asCALL_CDECL);

    // const String& GetResourceName(Resource* resource) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("const String& GetResourceName(Resource@+)", asFUNCTIONPR(GetResourceName, (Resource*), const String&), asCALL_CDECL);

    // ResourceRef GetResourceRef(Resource* resource, StringHash defaultType) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("ResourceRef GetResourceRef(Resource@+, StringHash)", asFUNCTIONPR(GetResourceRef, (Resource*, StringHash), ResourceRef), asCALL_CDECL);

    // StringHash GetResourceType(Resource* resource, StringHash defaultType) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("StringHash GetResourceType(Resource@+, StringHash)", asFUNCTIONPR(GetResourceType, (Resource*, StringHash), StringHash), asCALL_CDECL);

    // const char* GetRevision() | File: ../LibraryInfo.h
    // Error: type "const char*" can not automatically bind

    // unsigned GetStringListIndex(const String& value, const String* strings, unsigned defaultIndex, bool caseSensitive=false) | File: ../Core/StringUtils.h
    // Error: type "const String*" can not automatically bind

    // unsigned GetStringListIndex(const char* value, const String* strings, unsigned defaultIndex, bool caseSensitive=false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned GetStringListIndex(const char* value, const char** strings, unsigned defaultIndex, bool caseSensitive=false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned long long GetTotalMemory() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint64 GetTotalMemory()", asFUNCTIONPR(GetTotalMemory, (), unsigned long long), asCALL_CDECL);

    // WString GetWideNativePath(const String& pathName) | File: ../IO/FileSystem.h
    // Error: type "WString" can not automatically bind bacause have @nobind mark

    // float HalfToFloat(unsigned short value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float HalfToFloat(uint16)", asFUNCTIONPR(HalfToFloat, (unsigned short), float), asCALL_CDECL);

    // void InitFPU() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void InitFPU()", asFUNCTIONPR(InitFPU, (), void), asCALL_CDECL);

    // template<class T> T InverseLerp(T lhs, T rhs, T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float InverseLerp(float, float, float)", asFUNCTIONPR(InverseLerp, (float, float, float), float), asCALL_CDECL);

    // bool IsAbsolutePath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("bool IsAbsolutePath(const String&in)", asFUNCTIONPR(IsAbsolutePath, (const String&), bool), asCALL_CDECL);

    // bool IsAlpha(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool IsAlpha(uint)", asFUNCTIONPR(IsAlpha, (unsigned), bool), asCALL_CDECL);

    // bool IsDigit(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool IsDigit(uint)", asFUNCTIONPR(IsDigit, (unsigned), bool), asCALL_CDECL);

    // template<class T> bool IsNaN(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool IsNaN(double)", asFUNCTIONPR(IsNaN, (double), bool), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsNaN(float)", asFUNCTIONPR(IsNaN, (float), bool), asCALL_CDECL);

    // bool IsPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool IsPowerOfTwo(uint)", asFUNCTIONPR(IsPowerOfTwo, (unsigned), bool), asCALL_CDECL);

    // template<class T, class U> T Lerp(T lhs, T rhs, U t) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Lerp(float, float, float)", asFUNCTIONPR(Lerp, (float, float, float), float), asCALL_CDECL);

    // template<class T> T Ln(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Ln(float)", asFUNCTIONPR(Ln, (float), float), asCALL_CDECL);

    // unsigned LogBaseTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint LogBaseTwo(uint)", asFUNCTIONPR(LogBaseTwo, (unsigned), unsigned), asCALL_CDECL);

    // template<class T, class U> T Max(T lhs, U rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Max(float, float)", asFUNCTIONPR(Max, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Max(int, int)", asFUNCTIONPR(Max, (int, int), int), asCALL_CDECL);

    // template<class T, class U> T Min(T lhs, U rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Min(float, float)", asFUNCTIONPR(Min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Min(int, int)", asFUNCTIONPR(Min, (int, int), int), asCALL_CDECL);

    // unsigned NextPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint NextPowerOfTwo(uint)", asFUNCTIONPR(NextPowerOfTwo, (unsigned), unsigned), asCALL_CDECL);

    // void OpenConsoleWindow() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void OpenConsoleWindow()", asFUNCTIONPR(OpenConsoleWindow, (), void), asCALL_CDECL);

    // const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument=true) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("Array<String>@ ParseArguments(const String&in, bool = true)", asFUNCTION(ParseArguments_String_bool), asCALL_CDECL);

    // const Vector<String>& ParseArguments(const WString& cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "WString" can not automatically bind bacause have @nobind mark

    // const Vector<String>& ParseArguments(const char* cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "const char*" can not automatically bind

    // const Vector<String>& ParseArguments(const wchar_t* cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "const wchar_t*" can not automatically bind

    // const Vector<String>& ParseArguments(int argc, char** argv) | File: ../Core/ProcessUtils.h
    // Error: type "char**" can not automatically bind

    // template<class T> T Pow(T x, T y) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Pow(float, float)", asFUNCTIONPR(Pow, (float, float), float), asCALL_CDECL);

    // void PrintLine(const String& str, bool error=false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintLine(const String&in, bool = false)", asFUNCTIONPR(PrintLine, (const String&, bool), void), asCALL_CDECL);

    // void PrintLine(const char* str, bool error=false) | File: ../Core/ProcessUtils.h
    // Error: type "const char*" can not automatically bind

    // void PrintUnicode(const String& str, bool error=false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintUnicode(const String&in, bool = false)", asFUNCTIONPR(PrintUnicode, (const String&, bool), void), asCALL_CDECL);

    // void PrintUnicodeLine(const String& str, bool error=false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintUnicodeLine(const String&in, bool = false)", asFUNCTIONPR(PrintUnicodeLine, (const String&, bool), void), asCALL_CDECL);

    // int Rand() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("int Rand()", asFUNCTIONPR(Rand, (), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt()", asFUNCTIONPR(Rand, (), int), asCALL_CDECL);

    // float RandStandardNormal() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("float RandStandardNormal()", asFUNCTIONPR(RandStandardNormal, (), float), asCALL_CDECL);

    // float Random() | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random()", asFUNCTIONPR(Random, (), float), asCALL_CDECL);

    // float Random(float min, float max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random(float, float)", asFUNCTIONPR(Random, (float, float), float), asCALL_CDECL);

    // float Random(float range) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random(float)", asFUNCTIONPR(Random, (float), float), asCALL_CDECL);

    // int Random(int min, int max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int Random(int, int)", asFUNCTIONPR(Random, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int, int)", asFUNCTIONPR(Random, (int, int), int), asCALL_CDECL);

    // int Random(int range) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int Random(int)", asFUNCTIONPR(Random, (int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int)", asFUNCTIONPR(Random, (int), int), asCALL_CDECL);

    // float RandomNormal(float meanValue, float variance) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float RandomNormal(float, float)", asFUNCTIONPR(RandomNormal, (float, float), float), asCALL_CDECL);

    // void RegisterAudioLibrary(Context* context) | File: ../Audio/Audio.h
    // Context can be used as firs parameter of constructors only

    // void RegisterGraphicsLibrary(Context* context) | File: ../Graphics/Graphics.h
    // Context can be used as firs parameter of constructors only

    // void RegisterResourceLibrary(Context* context) | File: ../Resource/ResourceCache.h
    // Context can be used as firs parameter of constructors only

    // void RegisterSceneLibrary(Context* context) | File: ../Scene/Scene.h
    // Context can be used as firs parameter of constructors only

    // void RegisterUILibrary(Context* context) | File: ../UI/UI.h
    // Context can be used as firs parameter of constructors only

    // String RemoveTrailingSlash(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String RemoveTrailingSlash(const String&in)", asFUNCTIONPR(RemoveTrailingSlash, (const String&), String), asCALL_CDECL);

    // String ReplaceExtension(const String& fullPath, const String& newExtension) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String ReplaceExtension(const String&in, const String&in)", asFUNCTIONPR(ReplaceExtension, (const String&, const String&), String), asCALL_CDECL);

    // template<class T> T Round(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Round(float)", asFUNCTIONPR(Round, (float), float), asCALL_CDECL);

    // template<class T> int RoundToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int RoundToInt(float)", asFUNCTIONPR(RoundToInt, (float), int), asCALL_CDECL);

    // constexpr unsigned SDBMHash(unsigned hash, unsigned char c) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint SDBMHash(uint, uint8)", asFUNCTIONPR(SDBMHash, (unsigned, unsigned char), unsigned), asCALL_CDECL);

    // void SetMiniDumpDir(const String& pathName) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void SetMiniDumpDir(const String&in)", asFUNCTIONPR(SetMiniDumpDir, (const String&), void), asCALL_CDECL);

    // void SetRandomSeed(unsigned seed) | File: ../Math/Random.h
    engine->RegisterGlobalFunction("void SetRandomSeed(uint)", asFUNCTIONPR(SetRandomSeed, (unsigned), void), asCALL_CDECL);

    // template<class T> T Sign(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sign(float)", asFUNCTIONPR(Sign, (float), float), asCALL_CDECL);

    // template<class T> T Sin(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sin(float)", asFUNCTIONPR(Sin, (float), float), asCALL_CDECL);

    // void SinCos(float angle, float& sin, float& cos) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("void SinCos(float, float&, float&)", asFUNCTIONPR(SinCos, (float, float&, float&), void), asCALL_CDECL);

    // template<class T> T SmoothStep(T lhs, T rhs, T t) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float SmoothStep(float, float, float)", asFUNCTIONPR(SmoothStep, (float, float, float), float), asCALL_CDECL);

    // void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension=true) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("void SplitPath(const String&in, String&, String&, String&, bool = true)", asFUNCTIONPR(SplitPath, (const String&, String&, String&, String&, bool), void), asCALL_CDECL);

    // template<class T> T Sqrt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sqrt(float)", asFUNCTIONPR(Sqrt, (float), float), asCALL_CDECL);

    // float StableRandom(const Vector2& seed) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("float StableRandom(const Vector2&in)", asFUNCTIONPR(StableRandom, (const Vector2&), float), asCALL_CDECL);

    // float StableRandom(const Vector3& seed) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("float StableRandom(const Vector3&in)", asFUNCTIONPR(StableRandom, (const Vector3&), float), asCALL_CDECL);

    // float StableRandom(float seed) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("float StableRandom(float)", asFUNCTIONPR(StableRandom, (float), float), asCALL_CDECL);

    // void StringToBuffer(PODVector<unsigned char>& dest, const String& source) | File: ../Core/StringUtils.h
    // Error: type "PODVector<unsigned char>&" can not automatically bind

    // void StringToBuffer(PODVector<unsigned char>& dest, const char* source) | File: ../Core/StringUtils.h
    // Error: type "PODVector<unsigned char>&" can not automatically bind

    // template<class T> T Tan(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Tan(float)", asFUNCTIONPR(Tan, (float), float), asCALL_CDECL);

    // bool ToBool(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool ToBool(const String&in)", asFUNCTIONPR(ToBool, (const String&), bool), asCALL_CDECL);

    // bool ToBool(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Color ToColor(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Color ToColor(const String&in)", asFUNCTIONPR(ToColor, (const String&), Color), asCALL_CDECL);

    // Color ToColor(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // double ToDouble(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("double ToDouble(const String&in)", asFUNCTIONPR(ToDouble, (const String&), double), asCALL_CDECL);

    // double ToDouble(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // float ToFloat(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("float ToFloat(const String&in)", asFUNCTIONPR(ToFloat, (const String&), float), asCALL_CDECL);

    // float ToFloat(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // int ToInt(const String& source, int base=10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("int ToInt(const String&in, int = 10)", asFUNCTIONPR(ToInt, (const String&, int), int), asCALL_CDECL);

    // int ToInt(const char* source, int base=10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // long long ToInt64(const String& source, int base=10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("int64 ToInt64(const String&in, int = 10)", asFUNCTIONPR(ToInt64, (const String&, int), long long), asCALL_CDECL);

    // long long ToInt64(const char* source, int base=10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntRect ToIntRect(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntRect ToIntRect(const String&in)", asFUNCTIONPR(ToIntRect, (const String&), IntRect), asCALL_CDECL);

    // IntRect ToIntRect(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector2 ToIntVector2(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntVector2 ToIntVector2(const String&in)", asFUNCTIONPR(ToIntVector2, (const String&), IntVector2), asCALL_CDECL);

    // IntVector2 ToIntVector2(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector3 ToIntVector3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntVector3 ToIntVector3(const String&in)", asFUNCTIONPR(ToIntVector3, (const String&), IntVector3), asCALL_CDECL);

    // IntVector3 ToIntVector3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned ToLower(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToLower(uint)", asFUNCTIONPR(ToLower, (unsigned), unsigned), asCALL_CDECL);

    // Matrix3 ToMatrix3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix3 ToMatrix3(const String&in)", asFUNCTIONPR(ToMatrix3, (const String&), Matrix3), asCALL_CDECL);

    // Matrix3 ToMatrix3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Matrix3x4 ToMatrix3x4(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix3x4 ToMatrix3x4(const String&in)", asFUNCTIONPR(ToMatrix3x4, (const String&), Matrix3x4), asCALL_CDECL);

    // Matrix3x4 ToMatrix3x4(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Matrix4 ToMatrix4(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix4 ToMatrix4(const String&in)", asFUNCTIONPR(ToMatrix4, (const String&), Matrix4), asCALL_CDECL);

    // Matrix4 ToMatrix4(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Quaternion ToQuaternion(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Quaternion ToQuaternion(const String&in)", asFUNCTIONPR(ToQuaternion, (const String&), Quaternion), asCALL_CDECL);

    // Quaternion ToQuaternion(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Rect ToRect(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Rect ToRect(const String&in)", asFUNCTIONPR(ToRect, (const String&), Rect), asCALL_CDECL);

    // Rect ToRect(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // String ToString(const char* formatString,...) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // String ToString(void* value) | File: ../Core/StringUtils.h
    // Error: type "void*" can not automatically bind

    // String ToStringHex(unsigned value) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("String ToStringHex(uint)", asFUNCTIONPR(ToStringHex, (unsigned), String), asCALL_CDECL);

    // unsigned ToUInt(const String& source, int base=10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToUInt(const String&in, int = 10)", asFUNCTIONPR(ToUInt, (const String&, int), unsigned), asCALL_CDECL);

    // unsigned ToUInt(const char* source, int base=10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned long long ToUInt64(const String& source, int base=10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint64 ToUInt64(const String&in, int = 10)", asFUNCTIONPR(ToUInt64, (const String&, int), unsigned long long), asCALL_CDECL);

    // unsigned long long ToUInt64(const char* source, int base=10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned ToUpper(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToUpper(uint)", asFUNCTIONPR(ToUpper, (unsigned), unsigned), asCALL_CDECL);

    // Vector2 ToVector2(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector2 ToVector2(const String&in)", asFUNCTIONPR(ToVector2, (const String&), Vector2), asCALL_CDECL);

    // Vector2 ToVector2(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Vector3 ToVector3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector3 ToVector3(const String&in)", asFUNCTIONPR(ToVector3, (const String&), Vector3), asCALL_CDECL);

    // Vector3 ToVector3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Vector4 ToVector4(const String& source, bool allowMissingCoords=false) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector4 ToVector4(const String&in, bool = false)", asFUNCTIONPR(ToVector4, (const String&, bool), Vector4), asCALL_CDECL);

    // Vector4 ToVector4(const char* source, bool allowMissingCoords=false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Variant ToVectorVariant(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Variant ToVectorVariant(const String&in)", asFUNCTIONPR(ToVectorVariant, (const String&), Variant), asCALL_CDECL);

    // Variant ToVectorVariant(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector2 VectorAbs(const IntVector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorAbs(const IntVector2&in)", asFUNCTIONPR(VectorAbs, (const IntVector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorAbs(const IntVector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorAbs(const IntVector3&in)", asFUNCTIONPR(VectorAbs, (const IntVector3&), IntVector3), asCALL_CDECL);

    // Vector2 VectorAbs(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorAbs(const Vector2&in)", asFUNCTIONPR(VectorAbs, (const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorAbs(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorAbs(const Vector3&in)", asFUNCTIONPR(VectorAbs, (const Vector3&), Vector3), asCALL_CDECL);

    // Vector2 VectorCeil(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorCeil(const Vector2&in)", asFUNCTIONPR(VectorCeil, (const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorCeil(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorCeil(const Vector3&in)", asFUNCTIONPR(VectorCeil, (const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorCeil(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorCeil(const Vector4&in)", asFUNCTIONPR(VectorCeil, (const Vector4&), Vector4), asCALL_CDECL);

    // IntVector2 VectorCeilToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorCeilToInt(const Vector2&in)", asFUNCTIONPR(VectorCeilToInt, (const Vector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorCeilToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorCeilToInt(const Vector3&in)", asFUNCTIONPR(VectorCeilToInt, (const Vector3&), IntVector3), asCALL_CDECL);

    // Vector2 VectorFloor(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorFloor(const Vector2&in)", asFUNCTIONPR(VectorFloor, (const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorFloor(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorFloor(const Vector3&in)", asFUNCTIONPR(VectorFloor, (const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorFloor(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorFloor(const Vector4&in)", asFUNCTIONPR(VectorFloor, (const Vector4&), Vector4), asCALL_CDECL);

    // IntVector2 VectorFloorToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorFloorToInt(const Vector2&in)", asFUNCTIONPR(VectorFloorToInt, (const Vector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorFloorToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorFloorToInt(const Vector3&in)", asFUNCTIONPR(VectorFloorToInt, (const Vector3&), IntVector3), asCALL_CDECL);

    // Vector2 VectorLerp(const Vector2& lhs, const Vector2& rhs, const Vector2& t) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorLerp(const Vector2&in, const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorLerp, (const Vector2&, const Vector2&, const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorLerp(const Vector3& lhs, const Vector3& rhs, const Vector3& t) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorLerp(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorLerp, (const Vector3&, const Vector3&, const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorLerp(const Vector4& lhs, const Vector4& rhs, const Vector4& t) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorLerp(const Vector4&in, const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorLerp, (const Vector4&, const Vector4&, const Vector4&), Vector4), asCALL_CDECL);

    // IntVector2 VectorMax(const IntVector2& lhs, const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorMax(const IntVector2&in, const IntVector2&in)", asFUNCTIONPR(VectorMax, (const IntVector2&, const IntVector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorMax(const IntVector3& lhs, const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorMax(const IntVector3&in, const IntVector3&in)", asFUNCTIONPR(VectorMax, (const IntVector3&, const IntVector3&), IntVector3), asCALL_CDECL);

    // Vector2 VectorMax(const Vector2& lhs, const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorMax(const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorMax, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorMax(const Vector3& lhs, const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorMax(const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorMax, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorMax(const Vector4& lhs, const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorMax(const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorMax, (const Vector4&, const Vector4&), Vector4), asCALL_CDECL);

    // IntVector2 VectorMin(const IntVector2& lhs, const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorMin(const IntVector2&in, const IntVector2&in)", asFUNCTIONPR(VectorMin, (const IntVector2&, const IntVector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorMin(const IntVector3& lhs, const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorMin(const IntVector3&in, const IntVector3&in)", asFUNCTIONPR(VectorMin, (const IntVector3&, const IntVector3&), IntVector3), asCALL_CDECL);

    // Vector2 VectorMin(const Vector2& lhs, const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorMin(const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorMin, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorMin(const Vector3& lhs, const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorMin(const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorMin, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorMin(const Vector4& lhs, const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorMin(const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorMin, (const Vector4&, const Vector4&), Vector4), asCALL_CDECL);

    // Vector2 VectorRound(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorRound(const Vector2&in)", asFUNCTIONPR(VectorRound, (const Vector2&), Vector2), asCALL_CDECL);

    // Vector3 VectorRound(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorRound(const Vector3&in)", asFUNCTIONPR(VectorRound, (const Vector3&), Vector3), asCALL_CDECL);

    // Vector4 VectorRound(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorRound(const Vector4&in)", asFUNCTIONPR(VectorRound, (const Vector4&), Vector4), asCALL_CDECL);

    // IntVector2 VectorRoundToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorRoundToInt(const Vector2&in)", asFUNCTIONPR(VectorRoundToInt, (const Vector2&), IntVector2), asCALL_CDECL);

    // IntVector3 VectorRoundToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorRoundToInt(const Vector3&in)", asFUNCTIONPR(VectorRoundToInt, (const Vector3&), IntVector3), asCALL_CDECL);

    // bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV=false) | File: ../Graphics/Drawable.h
    engine->RegisterGlobalFunction("bool WriteDrawablesToOBJ(Array<Drawable@>@, File@+, bool, bool, bool = false)", asFUNCTION(WriteDrawablesToOBJ_PODVectorDrawable_File_bool_bool_bool), asCALL_CDECL);

#ifdef URHO3D_IK
    // void RegisterIKLibrary(Context* context) | File: ../IK/IK.h
    // Context can be used as firs parameter of constructors only
#endif

#ifdef URHO3D_NAVIGATION
    // void RegisterNavigationLibrary(Context* context) | File: ../Navigation/NavigationMesh.h
    // Context can be used as firs parameter of constructors only
#endif

#ifdef URHO3D_NETWORK
    // void RegisterNetworkLibrary(Context* context) | File: ../Network/Network.h
    // Context can be used as firs parameter of constructors only
#endif

#ifdef URHO3D_PHYSICS
    // void RegisterPhysicsLibrary(Context* context) | File: ../Physics/PhysicsWorld.h
    // Context can be used as firs parameter of constructors only
#endif

#ifdef URHO3D_URHO2D
    // void RegisterUrho2DLibrary(Context* context) | File: ../Urho2D/Urho2D.h
    // Context can be used as firs parameter of constructors only
#endif
}

}
