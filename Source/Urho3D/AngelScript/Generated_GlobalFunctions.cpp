// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Generated_Includes.h"

namespace Urho3D
{

// const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
static CScriptArray* constspVectorlesStringgreamp_GetArguments_void()
{
    const Vector<String>& result = GetArguments();
    return VectorToArray<String>(result, "Array<String>");
}

// const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument = true) | File: ../Core/ProcessUtils.h
static CScriptArray* constspVectorlesStringgreamp_ParseArguments_constspStringamp_bool(const String& cmdLine, bool skipFirstArgument)
{
    const Vector<String>& result = ParseArguments(cmdLine, skipFirstArgument);
    return VectorToArray<String>(result, "Array<String>");
}

// bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV = false) | File: ../Graphics/Drawable.h
static bool bool_WriteDrawablesToOBJ_constspPODVectorlesDrawablestargreamp_Filestar_bool_bool_bool(CScriptArray* drawables_conv, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV)
{
    PODVector<Drawable*> drawables = ArrayToPODVector<Drawable*>(drawables_conv);
    bool result = WriteDrawablesToOBJ(drawables, outputFile, asZUp, asRightHanded, writeLightmapUV);
    return result;
}

void ASRegisterGeneratedGlobalFunctions(asIScriptEngine* engine)
{
    // template <class T> T Abs(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Abs(float)", AS_FUNCTIONPR(Abs, (float), float), AS_CALL_CDECL);

    // template <class T> T Acos(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Acos(float)", AS_FUNCTIONPR(Acos, (float), float), AS_CALL_CDECL);

    // String AddTrailingSlash(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String AddTrailingSlash(const String&in)", AS_FUNCTIONPR(AddTrailingSlash, (const String&), String), AS_CALL_CDECL);

    // void AllocatorFree(AllocatorBlock* allocator, void* ptr) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity = 1) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // void* AllocatorReserve(AllocatorBlock* allocator) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // void AllocatorUninitialize(AllocatorBlock* allocator) | File: ../Container/Allocator.h
    // Error: type "AllocatorBlock*" can not automatically bind

    // template <class T> T Asin(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Asin(float)", AS_FUNCTIONPR(Asin, (float), float), AS_CALL_CDECL);

    // template <class T> T Atan(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Atan(float)", AS_FUNCTIONPR(Atan, (float), float), AS_CALL_CDECL);

    // template <class T> T Atan2(T y, T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Atan2(float, float)", AS_FUNCTIONPR(Atan2, (float, float), float), AS_CALL_CDECL);

    // void BufferToString(String& dest, const void* data, unsigned size) | File: ../Core/StringUtils.h
    // Error: type "const void*" can not automatically bind

    // template <class T> T Ceil(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Ceil(float)", AS_FUNCTIONPR(Ceil, (float), float), AS_CALL_CDECL);

    // template <class T> int CeilToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int CeilToInt(float)", AS_FUNCTIONPR(CeilToInt, (float), int), AS_CALL_CDECL);

    // template <class T> T Clamp(T value, T min, T max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Clamp(float, float, float)", AS_FUNCTIONPR(Clamp, (float, float, float), float), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int Clamp(int, int, int)", AS_FUNCTIONPR(Clamp, (int, int, int), int), AS_CALL_CDECL);

    // unsigned ClosestPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint ClosestPowerOfTwo(uint)", AS_FUNCTIONPR(ClosestPowerOfTwo, (unsigned), unsigned), AS_CALL_CDECL);

    // void CombineHash(unsigned& result, unsigned hash) | File: ../Container/Hash.h
    engine->RegisterGlobalFunction("void CombineHash(uint&, uint)", AS_FUNCTIONPR(CombineHash, (unsigned&, unsigned), void), AS_CALL_CDECL);

    // bool CompareDrawables(Drawable* lhs, Drawable* rhs) | File: ../Graphics/Drawable.h
    engine->RegisterGlobalFunction("bool CompareDrawables(Drawable@+, Drawable@+)", AS_FUNCTIONPR(CompareDrawables, (Drawable*, Drawable*), bool), AS_CALL_CDECL);

    // bool CompareLights(Light* lhs, Light* rhs) | File: ../Graphics/Light.h
    engine->RegisterGlobalFunction("bool CompareLights(Light@+, Light@+)", AS_FUNCTIONPR(CompareLights, (Light*, Light*), bool), AS_CALL_CDECL);

    // unsigned CompressData(void* dest, const void* src, unsigned srcSize) | File: ../IO/Compression.h
    // Error: type "void*" can not automatically bind

    // bool CompressStream(Serializer& dest, Deserializer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("bool CompressStream(Serializer&, Deserializer&)", AS_FUNCTIONPR(CompressStream, (Serializer&, Deserializer&), bool), AS_CALL_CDECL);

    // VectorBuffer CompressVectorBuffer(VectorBuffer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("VectorBuffer CompressVectorBuffer(VectorBuffer&)", AS_FUNCTIONPR(CompressVectorBuffer, (VectorBuffer&), VectorBuffer), AS_CALL_CDECL);

    // template <class T> T Cos(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Cos(float)", AS_FUNCTIONPR(Cos, (float), float), AS_CALL_CDECL);

    // unsigned CountSetBits(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint CountSetBits(uint)", AS_FUNCTIONPR(CountSetBits, (unsigned), unsigned), AS_CALL_CDECL);

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
    engine->RegisterGlobalFunction("bool DecompressStream(Serializer&, Deserializer&)", AS_FUNCTIONPR(DecompressStream, (Serializer&, Deserializer&), bool), AS_CALL_CDECL);

    // VectorBuffer DecompressVectorBuffer(VectorBuffer& src) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("VectorBuffer DecompressVectorBuffer(VectorBuffer&)", AS_FUNCTIONPR(DecompressVectorBuffer, (VectorBuffer&), VectorBuffer), AS_CALL_CDECL);

    // template <class T> bool Equals(T lhs, T rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool Equals(float, float)", AS_FUNCTIONPR(Equals, (float, float), bool), AS_CALL_CDECL);

    // void ErrorDialog(const String& title, const String& message) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void ErrorDialog(const String&in, const String&in)", AS_FUNCTIONPR(ErrorDialog, (const String&, const String&), void), AS_CALL_CDECL);

    // void ErrorExit(const String& message = String::EMPTY, int exitCode = EXIT_FAILURE) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void ErrorExit(const String&in = String::EMPTY, int = EXIT_FAILURE)", AS_FUNCTIONPR(ErrorExit, (const String&, int), void), AS_CALL_CDECL);

    // unsigned EstimateCompressBound(unsigned srcSize) | File: ../IO/Compression.h
    engine->RegisterGlobalFunction("uint EstimateCompressBound(uint)", AS_FUNCTIONPR(EstimateCompressBound, (unsigned), unsigned), AS_CALL_CDECL);

    // void FlipBlockHorizontal(unsigned char* dest, const unsigned char* src, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // void FlipBlockVertical(unsigned char* dest, const unsigned char* src, CompressedFormat format) | File: ../Resource/Decompress.h
    // Error: type "unsigned char*" can not automatically bind

    // unsigned short FloatToHalf(float value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint16 FloatToHalf(float)", AS_FUNCTIONPR(FloatToHalf, (float), unsigned short), AS_CALL_CDECL);

    // unsigned FloatToRawIntBits(float value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint FloatToRawIntBits(float)", AS_FUNCTIONPR(FloatToRawIntBits, (float), unsigned), AS_CALL_CDECL);

    // template <class T> T Floor(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Floor(float)", AS_FUNCTIONPR(Floor, (float), float), AS_CALL_CDECL);

    // template <class T> int FloorToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int FloorToInt(float)", AS_FUNCTIONPR(FloorToInt, (float), int), AS_CALL_CDECL);

    // template <class T> T Fract(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Fract(float)", AS_FUNCTIONPR(Fract, (float), float), AS_CALL_CDECL);

    // void GenerateTangents(void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, unsigned normalOffset, unsigned texCoordOffset, unsigned tangentOffset) | File: ../Graphics/Tangent.h
    // Error: type "void*" can not automatically bind

    // const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("Array<String>@ GetArguments()", AS_FUNCTION(constspVectorlesStringgreamp_GetArguments_void), AS_CALL_CDECL);

    // const char* GetCompilerDefines() | File: ../LibraryInfo.h
    // Error: type "const char*" can not automatically bind

    // String GetConsoleInput() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetConsoleInput()", AS_FUNCTIONPR(GetConsoleInput, (), String), AS_CALL_CDECL);

    // StringHashRegister& GetEventNameRegister() | File: ../Core/Object.h
    engine->RegisterGlobalFunction("StringHashRegister& GetEventNameRegister()", AS_FUNCTIONPR(GetEventNameRegister, (), StringHashRegister&), AS_CALL_CDECL);

    // String GetExtension(const String& fullPath, bool lowercaseExtension = true) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetExtension(const String&in, bool = true)", AS_FUNCTIONPR(GetExtension, (const String&, bool), String), AS_CALL_CDECL);

    // String GetFileName(const String& fullPath) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetFileName(const String&in)", AS_FUNCTIONPR(GetFileName, (const String&), String), AS_CALL_CDECL);

    // String GetFileNameAndExtension(const String& fileName, bool lowercaseExtension = false) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetFileNameAndExtension(const String&in, bool = false)", AS_FUNCTIONPR(GetFileNameAndExtension, (const String&, bool), String), AS_CALL_CDECL);

    // String GetFileSizeString(unsigned long long memorySize) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("String GetFileSizeString(uint64)", AS_FUNCTIONPR(GetFileSizeString, (unsigned long long), String), AS_CALL_CDECL);

    // String GetHostName() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetHostName()", AS_FUNCTIONPR(GetHostName, (), String), AS_CALL_CDECL);

    // String GetInternalPath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetInternalPath(const String&in)", AS_FUNCTIONPR(GetInternalPath, (const String&), String), AS_CALL_CDECL);

    // String GetLoginName() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetLoginName()", AS_FUNCTIONPR(GetLoginName, (), String), AS_CALL_CDECL);

    // String GetMiniDumpDir() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetMiniDumpDir()", AS_FUNCTIONPR(GetMiniDumpDir, (), String), AS_CALL_CDECL);

    // String GetNativePath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetNativePath(const String&in)", AS_FUNCTIONPR(GetNativePath, (const String&), String), AS_CALL_CDECL);

    // unsigned GetNumLogicalCPUs() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint GetNumLogicalCPUs()", AS_FUNCTIONPR(GetNumLogicalCPUs, (), unsigned), AS_CALL_CDECL);

    // unsigned GetNumPhysicalCPUs() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint GetNumPhysicalCPUs()", AS_FUNCTIONPR(GetNumPhysicalCPUs, (), unsigned), AS_CALL_CDECL);

    // String GetOSVersion() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetOSVersion()", AS_FUNCTIONPR(GetOSVersion, (), String), AS_CALL_CDECL);

    // String GetParentPath(const String& path) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetParentPath(const String&in)", AS_FUNCTIONPR(GetParentPath, (const String&), String), AS_CALL_CDECL);

    // String GetPath(const String& fullPath) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String GetPath(const String&in)", AS_FUNCTIONPR(GetPath, (const String&), String), AS_CALL_CDECL);

    // String GetPlatform() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("String GetPlatform()", AS_FUNCTIONPR(GetPlatform, (), String), AS_CALL_CDECL);

    // unsigned GetRandomSeed() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("uint GetRandomSeed()", AS_FUNCTIONPR(GetRandomSeed, (), unsigned), AS_CALL_CDECL);

    // const String& GetResourceName(Resource* resource) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("const String& GetResourceName(Resource@+)", AS_FUNCTIONPR(GetResourceName, (Resource*), const String&), AS_CALL_CDECL);

    // ResourceRef GetResourceRef(Resource* resource, StringHash defaultType) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("ResourceRef GetResourceRef(Resource@+, StringHash)", AS_FUNCTIONPR(GetResourceRef, (Resource*, StringHash), ResourceRef), AS_CALL_CDECL);

    // StringHash GetResourceType(Resource* resource, StringHash defaultType) | File: ../Resource/Resource.h
    engine->RegisterGlobalFunction("StringHash GetResourceType(Resource@+, StringHash)", AS_FUNCTIONPR(GetResourceType, (Resource*, StringHash), StringHash), AS_CALL_CDECL);

    // const char* GetRevision() | File: ../LibraryInfo.h
    // Error: type "const char*" can not automatically bind

    // unsigned GetStringListIndex(const String& value, const String* strings, unsigned defaultIndex, bool caseSensitive = false) | File: ../Core/StringUtils.h
    // Error: type "const String*" can not automatically bind

    // unsigned GetStringListIndex(const char* value, const String* strings, unsigned defaultIndex, bool caseSensitive = false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned GetStringListIndex(const char* value, const char** strings, unsigned defaultIndex, bool caseSensitive = false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned long long GetTotalMemory() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("uint64 GetTotalMemory()", AS_FUNCTIONPR(GetTotalMemory, (), unsigned long long), AS_CALL_CDECL);

    // WString GetWideNativePath(const String& pathName) | File: ../IO/FileSystem.h
    // Error: type "WString" can not automatically bind bacause have @nobind mark

    // float HalfToFloat(unsigned short value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float HalfToFloat(uint16)", AS_FUNCTIONPR(HalfToFloat, (unsigned short), float), AS_CALL_CDECL);

    // void InitFPU() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void InitFPU()", AS_FUNCTIONPR(InitFPU, (), void), AS_CALL_CDECL);

    // template <class T> T InverseLerp(T lhs, T rhs, T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float InverseLerp(float, float, float)", AS_FUNCTIONPR(InverseLerp, (float, float, float), float), AS_CALL_CDECL);

    // bool IsAbsolutePath(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("bool IsAbsolutePath(const String&in)", AS_FUNCTIONPR(IsAbsolutePath, (const String&), bool), AS_CALL_CDECL);

    // bool IsAlpha(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool IsAlpha(uint)", AS_FUNCTIONPR(IsAlpha, (unsigned), bool), AS_CALL_CDECL);

    // bool IsDigit(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool IsDigit(uint)", AS_FUNCTIONPR(IsDigit, (unsigned), bool), AS_CALL_CDECL);

    // template <class T> bool IsNaN(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool IsNaN(double)", AS_FUNCTIONPR(IsNaN, (double), bool), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("bool IsNaN(float)", AS_FUNCTIONPR(IsNaN, (float), bool), AS_CALL_CDECL);

    // bool IsPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("bool IsPowerOfTwo(uint)", AS_FUNCTIONPR(IsPowerOfTwo, (unsigned), bool), AS_CALL_CDECL);

    // template <class T, class U> T Lerp(T lhs, T rhs, U t) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Lerp(float, float, float)", AS_FUNCTIONPR(Lerp, (float, float, float), float), AS_CALL_CDECL);

    // template <class T> T Ln(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Ln(float)", AS_FUNCTIONPR(Ln, (float), float), AS_CALL_CDECL);

    // unsigned LogBaseTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint LogBaseTwo(uint)", AS_FUNCTIONPR(LogBaseTwo, (unsigned), unsigned), AS_CALL_CDECL);

    // template <class T, class U> T Max(T lhs, U rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Max(float, float)", AS_FUNCTIONPR(Max, (float, float), float), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int Max(int, int)", AS_FUNCTIONPR(Max, (int, int), int), AS_CALL_CDECL);

    // template <class T, class U> T Min(T lhs, U rhs) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Min(float, float)", AS_FUNCTIONPR(Min, (float, float), float), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int Min(int, int)", AS_FUNCTIONPR(Min, (int, int), int), AS_CALL_CDECL);

    // unsigned NextPowerOfTwo(unsigned value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint NextPowerOfTwo(uint)", AS_FUNCTIONPR(NextPowerOfTwo, (unsigned), unsigned), AS_CALL_CDECL);

    // void OpenConsoleWindow() | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void OpenConsoleWindow()", AS_FUNCTIONPR(OpenConsoleWindow, (), void), AS_CALL_CDECL);

    // const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument = true) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("Array<String>@ ParseArguments(const String&in, bool = true)", AS_FUNCTION(constspVectorlesStringgreamp_ParseArguments_constspStringamp_bool), AS_CALL_CDECL);

    // const Vector<String>& ParseArguments(const WString& cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "WString" can not automatically bind bacause have @nobind mark

    // const Vector<String>& ParseArguments(const char* cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "const char*" can not automatically bind

    // const Vector<String>& ParseArguments(const wchar_t* cmdLine) | File: ../Core/ProcessUtils.h
    // Error: type "const wchar_t*" can not automatically bind

    // const Vector<String>& ParseArguments(int argc, char** argv) | File: ../Core/ProcessUtils.h
    // Error: type "char**" can not automatically bind

    // template <class T> T Pow(T x, T y) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Pow(float, float)", AS_FUNCTIONPR(Pow, (float, float), float), AS_CALL_CDECL);

    // void PrintLine(const String& str, bool error = false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintLine(const String&in, bool = false)", AS_FUNCTIONPR(PrintLine, (const String&, bool), void), AS_CALL_CDECL);

    // void PrintLine(const char* str, bool error = false) | File: ../Core/ProcessUtils.h
    // Error: type "const char*" can not automatically bind

    // void PrintUnicode(const String& str, bool error = false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintUnicode(const String&in, bool = false)", AS_FUNCTIONPR(PrintUnicode, (const String&, bool), void), AS_CALL_CDECL);

    // void PrintUnicodeLine(const String& str, bool error = false) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void PrintUnicodeLine(const String&in, bool = false)", AS_FUNCTIONPR(PrintUnicodeLine, (const String&, bool), void), AS_CALL_CDECL);

    // int Rand() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("int Rand()", AS_FUNCTIONPR(Rand, (), int), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt()", AS_FUNCTIONPR(Rand, (), int), AS_CALL_CDECL);

    // float RandStandardNormal() | File: ../Math/Random.h
    engine->RegisterGlobalFunction("float RandStandardNormal()", AS_FUNCTIONPR(RandStandardNormal, (), float), AS_CALL_CDECL);

    // float Random() | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random()", AS_FUNCTIONPR(Random, (), float), AS_CALL_CDECL);

    // float Random(float min, float max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random(float, float)", AS_FUNCTIONPR(Random, (float, float), float), AS_CALL_CDECL);

    // float Random(float range) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Random(float)", AS_FUNCTIONPR(Random, (float), float), AS_CALL_CDECL);

    // int Random(int min, int max) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int Random(int, int)", AS_FUNCTIONPR(Random, (int, int), int), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int, int)", AS_FUNCTIONPR(Random, (int, int), int), AS_CALL_CDECL);

    // int Random(int range) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int Random(int)", AS_FUNCTIONPR(Random, (int), int), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int)", AS_FUNCTIONPR(Random, (int), int), AS_CALL_CDECL);

    // float RandomNormal(float meanValue, float variance) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float RandomNormal(float, float)", AS_FUNCTIONPR(RandomNormal, (float, float), float), AS_CALL_CDECL);

    // void RegisterAudioLibrary(Context* context) | File: ../Audio/Audio.h
    // Not registered because have @nobind mark

    // void RegisterGraphicsLibrary(Context* context) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark

    // void RegisterResourceLibrary(Context* context) | File: ../Resource/ResourceCache.h
    // Not registered because have @nobind mark

    // void RegisterSceneLibrary(Context* context) | File: ../Scene/Scene.h
    // Not registered because have @nobind mark

    // void RegisterUILibrary(Context* context) | File: ../UI/UI.h
    // Not registered because have @nobind mark

    // String RemoveTrailingSlash(const String& pathName) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String RemoveTrailingSlash(const String&in)", AS_FUNCTIONPR(RemoveTrailingSlash, (const String&), String), AS_CALL_CDECL);

    // String ReplaceExtension(const String& fullPath, const String& newExtension) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("String ReplaceExtension(const String&in, const String&in)", AS_FUNCTIONPR(ReplaceExtension, (const String&, const String&), String), AS_CALL_CDECL);

    // template <class T> T Round(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Round(float)", AS_FUNCTIONPR(Round, (float), float), AS_CALL_CDECL);

    // template <class T> int RoundToInt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("int RoundToInt(float)", AS_FUNCTIONPR(RoundToInt, (float), int), AS_CALL_CDECL);

    // constexpr unsigned SDBMHash(unsigned hash, unsigned char c) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("uint SDBMHash(uint, uint8)", AS_FUNCTIONPR(SDBMHash, (unsigned, unsigned char), unsigned), AS_CALL_CDECL);

    // void SetMiniDumpDir(const String& pathName) | File: ../Core/ProcessUtils.h
    engine->RegisterGlobalFunction("void SetMiniDumpDir(const String&in)", AS_FUNCTIONPR(SetMiniDumpDir, (const String&), void), AS_CALL_CDECL);

    // void SetRandomSeed(unsigned seed) | File: ../Math/Random.h
    engine->RegisterGlobalFunction("void SetRandomSeed(uint)", AS_FUNCTIONPR(SetRandomSeed, (unsigned), void), AS_CALL_CDECL);

    // template <class T> T Sign(T value) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sign(float)", AS_FUNCTIONPR(Sign, (float), float), AS_CALL_CDECL);

    // template <class T> T Sin(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sin(float)", AS_FUNCTIONPR(Sin, (float), float), AS_CALL_CDECL);

    // void SinCos(float angle, float& sin, float& cos) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("void SinCos(float, float&, float&)", AS_FUNCTIONPR(SinCos, (float, float&, float&), void), AS_CALL_CDECL);

    // template <class T> T SmoothStep(T lhs, T rhs, T t) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float SmoothStep(float, float, float)", AS_FUNCTIONPR(SmoothStep, (float, float, float), float), AS_CALL_CDECL);

    // void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension = true) | File: ../IO/FileSystem.h
    engine->RegisterGlobalFunction("void SplitPath(const String&in, String&, String&, String&, bool = true)", AS_FUNCTIONPR(SplitPath, (const String&, String&, String&, String&, bool), void), AS_CALL_CDECL);

    // template <class T> T Sqrt(T x) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Sqrt(float)", AS_FUNCTIONPR(Sqrt, (float), float), AS_CALL_CDECL);

    // float StableRandom(const Vector2& seed) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("float StableRandom(const Vector2&in)", AS_FUNCTIONPR(StableRandom, (const Vector2&), float), AS_CALL_CDECL);

    // float StableRandom(const Vector3& seed) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("float StableRandom(const Vector3&in)", AS_FUNCTIONPR(StableRandom, (const Vector3&), float), AS_CALL_CDECL);

    // float StableRandom(float seed) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("float StableRandom(float)", AS_FUNCTIONPR(StableRandom, (float), float), AS_CALL_CDECL);

    // void StringToBuffer(PODVector<unsigned char>& dest, const String& source) | File: ../Core/StringUtils.h
    // Error: type "PODVector<unsigned char>&" can not automatically bind

    // void StringToBuffer(PODVector<unsigned char>& dest, const char* source) | File: ../Core/StringUtils.h
    // Error: type "PODVector<unsigned char>&" can not automatically bind

    // template <class T> T Tan(T angle) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Tan(float)", AS_FUNCTIONPR(Tan, (float), float), AS_CALL_CDECL);

    // bool ToBool(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("bool ToBool(const String&in)", AS_FUNCTIONPR(ToBool, (const String&), bool), AS_CALL_CDECL);

    // bool ToBool(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Color ToColor(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Color ToColor(const String&in)", AS_FUNCTIONPR(ToColor, (const String&), Color), AS_CALL_CDECL);

    // Color ToColor(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // double ToDouble(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("double ToDouble(const String&in)", AS_FUNCTIONPR(ToDouble, (const String&), double), AS_CALL_CDECL);

    // double ToDouble(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // float ToFloat(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("float ToFloat(const String&in)", AS_FUNCTIONPR(ToFloat, (const String&), float), AS_CALL_CDECL);

    // float ToFloat(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // int ToInt(const String& source, int base = 10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("int ToInt(const String&in, int = 10)", AS_FUNCTIONPR(ToInt, (const String&, int), int), AS_CALL_CDECL);

    // int ToInt(const char* source, int base = 10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // long long ToInt64(const String& source, int base = 10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("int64 ToInt64(const String&in, int = 10)", AS_FUNCTIONPR(ToInt64, (const String&, int), long long), AS_CALL_CDECL);

    // long long ToInt64(const char* source, int base = 10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntRect ToIntRect(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntRect ToIntRect(const String&in)", AS_FUNCTIONPR(ToIntRect, (const String&), IntRect), AS_CALL_CDECL);

    // IntRect ToIntRect(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector2 ToIntVector2(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntVector2 ToIntVector2(const String&in)", AS_FUNCTIONPR(ToIntVector2, (const String&), IntVector2), AS_CALL_CDECL);

    // IntVector2 ToIntVector2(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector3 ToIntVector3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("IntVector3 ToIntVector3(const String&in)", AS_FUNCTIONPR(ToIntVector3, (const String&), IntVector3), AS_CALL_CDECL);

    // IntVector3 ToIntVector3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned ToLower(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToLower(uint)", AS_FUNCTIONPR(ToLower, (unsigned), unsigned), AS_CALL_CDECL);

    // Matrix3 ToMatrix3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix3 ToMatrix3(const String&in)", AS_FUNCTIONPR(ToMatrix3, (const String&), Matrix3), AS_CALL_CDECL);

    // Matrix3 ToMatrix3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Matrix3x4 ToMatrix3x4(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix3x4 ToMatrix3x4(const String&in)", AS_FUNCTIONPR(ToMatrix3x4, (const String&), Matrix3x4), AS_CALL_CDECL);

    // Matrix3x4 ToMatrix3x4(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Matrix4 ToMatrix4(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Matrix4 ToMatrix4(const String&in)", AS_FUNCTIONPR(ToMatrix4, (const String&), Matrix4), AS_CALL_CDECL);

    // Matrix4 ToMatrix4(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Quaternion ToQuaternion(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Quaternion ToQuaternion(const String&in)", AS_FUNCTIONPR(ToQuaternion, (const String&), Quaternion), AS_CALL_CDECL);

    // Quaternion ToQuaternion(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Rect ToRect(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Rect ToRect(const String&in)", AS_FUNCTIONPR(ToRect, (const String&), Rect), AS_CALL_CDECL);

    // Rect ToRect(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // String ToString(const char* formatString,...) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // String ToString(void* value) | File: ../Core/StringUtils.h
    // Error: type "void*" can not automatically bind

    // String ToStringHex(unsigned value) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("String ToStringHex(uint)", AS_FUNCTIONPR(ToStringHex, (unsigned), String), AS_CALL_CDECL);

    // unsigned ToUInt(const String& source, int base = 10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToUInt(const String&in, int = 10)", AS_FUNCTIONPR(ToUInt, (const String&, int), unsigned), AS_CALL_CDECL);

    // unsigned ToUInt(const char* source, int base = 10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned long long ToUInt64(const String& source, int base = 10) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint64 ToUInt64(const String&in, int = 10)", AS_FUNCTIONPR(ToUInt64, (const String&, int), unsigned long long), AS_CALL_CDECL);

    // unsigned long long ToUInt64(const char* source, int base = 10) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // unsigned ToUpper(unsigned ch) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("uint ToUpper(uint)", AS_FUNCTIONPR(ToUpper, (unsigned), unsigned), AS_CALL_CDECL);

    // Vector2 ToVector2(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector2 ToVector2(const String&in)", AS_FUNCTIONPR(ToVector2, (const String&), Vector2), AS_CALL_CDECL);

    // Vector2 ToVector2(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Vector3 ToVector3(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector3 ToVector3(const String&in)", AS_FUNCTIONPR(ToVector3, (const String&), Vector3), AS_CALL_CDECL);

    // Vector3 ToVector3(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Vector4 ToVector4(const String& source, bool allowMissingCoords = false) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Vector4 ToVector4(const String&in, bool = false)", AS_FUNCTIONPR(ToVector4, (const String&, bool), Vector4), AS_CALL_CDECL);

    // Vector4 ToVector4(const char* source, bool allowMissingCoords = false) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // Variant ToVectorVariant(const String& source) | File: ../Core/StringUtils.h
    engine->RegisterGlobalFunction("Variant ToVectorVariant(const String&in)", AS_FUNCTIONPR(ToVectorVariant, (const String&), Variant), AS_CALL_CDECL);

    // Variant ToVectorVariant(const char* source) | File: ../Core/StringUtils.h
    // Error: type "const char*" can not automatically bind

    // IntVector2 VectorAbs(const IntVector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorAbs(const IntVector2&in)", AS_FUNCTIONPR(VectorAbs, (const IntVector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorAbs(const IntVector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorAbs(const IntVector3&in)", AS_FUNCTIONPR(VectorAbs, (const IntVector3&), IntVector3), AS_CALL_CDECL);

    // Vector2 VectorAbs(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorAbs(const Vector2&in)", AS_FUNCTIONPR(VectorAbs, (const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorAbs(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorAbs(const Vector3&in)", AS_FUNCTIONPR(VectorAbs, (const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector2 VectorCeil(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorCeil(const Vector2&in)", AS_FUNCTIONPR(VectorCeil, (const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorCeil(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorCeil(const Vector3&in)", AS_FUNCTIONPR(VectorCeil, (const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorCeil(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorCeil(const Vector4&in)", AS_FUNCTIONPR(VectorCeil, (const Vector4&), Vector4), AS_CALL_CDECL);

    // IntVector2 VectorCeilToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorCeilToInt(const Vector2&in)", AS_FUNCTIONPR(VectorCeilToInt, (const Vector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorCeilToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorCeilToInt(const Vector3&in)", AS_FUNCTIONPR(VectorCeilToInt, (const Vector3&), IntVector3), AS_CALL_CDECL);

    // Vector2 VectorFloor(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorFloor(const Vector2&in)", AS_FUNCTIONPR(VectorFloor, (const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorFloor(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorFloor(const Vector3&in)", AS_FUNCTIONPR(VectorFloor, (const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorFloor(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorFloor(const Vector4&in)", AS_FUNCTIONPR(VectorFloor, (const Vector4&), Vector4), AS_CALL_CDECL);

    // IntVector2 VectorFloorToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorFloorToInt(const Vector2&in)", AS_FUNCTIONPR(VectorFloorToInt, (const Vector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorFloorToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorFloorToInt(const Vector3&in)", AS_FUNCTIONPR(VectorFloorToInt, (const Vector3&), IntVector3), AS_CALL_CDECL);

    // Vector2 VectorLerp(const Vector2& lhs, const Vector2& rhs, const Vector2& t) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorLerp(const Vector2&in, const Vector2&in, const Vector2&in)", AS_FUNCTIONPR(VectorLerp, (const Vector2&, const Vector2&, const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorLerp(const Vector3& lhs, const Vector3& rhs, const Vector3& t) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorLerp(const Vector3&in, const Vector3&in, const Vector3&in)", AS_FUNCTIONPR(VectorLerp, (const Vector3&, const Vector3&, const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorLerp(const Vector4& lhs, const Vector4& rhs, const Vector4& t) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorLerp(const Vector4&in, const Vector4&in, const Vector4&in)", AS_FUNCTIONPR(VectorLerp, (const Vector4&, const Vector4&, const Vector4&), Vector4), AS_CALL_CDECL);

    // IntVector2 VectorMax(const IntVector2& lhs, const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorMax(const IntVector2&in, const IntVector2&in)", AS_FUNCTIONPR(VectorMax, (const IntVector2&, const IntVector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorMax(const IntVector3& lhs, const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorMax(const IntVector3&in, const IntVector3&in)", AS_FUNCTIONPR(VectorMax, (const IntVector3&, const IntVector3&), IntVector3), AS_CALL_CDECL);

    // Vector2 VectorMax(const Vector2& lhs, const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorMax(const Vector2&in, const Vector2&in)", AS_FUNCTIONPR(VectorMax, (const Vector2&, const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorMax(const Vector3& lhs, const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorMax(const Vector3&in, const Vector3&in)", AS_FUNCTIONPR(VectorMax, (const Vector3&, const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorMax(const Vector4& lhs, const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorMax(const Vector4&in, const Vector4&in)", AS_FUNCTIONPR(VectorMax, (const Vector4&, const Vector4&), Vector4), AS_CALL_CDECL);

    // IntVector2 VectorMin(const IntVector2& lhs, const IntVector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorMin(const IntVector2&in, const IntVector2&in)", AS_FUNCTIONPR(VectorMin, (const IntVector2&, const IntVector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorMin(const IntVector3& lhs, const IntVector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorMin(const IntVector3&in, const IntVector3&in)", AS_FUNCTIONPR(VectorMin, (const IntVector3&, const IntVector3&), IntVector3), AS_CALL_CDECL);

    // Vector2 VectorMin(const Vector2& lhs, const Vector2& rhs) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorMin(const Vector2&in, const Vector2&in)", AS_FUNCTIONPR(VectorMin, (const Vector2&, const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorMin(const Vector3& lhs, const Vector3& rhs) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorMin(const Vector3&in, const Vector3&in)", AS_FUNCTIONPR(VectorMin, (const Vector3&, const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorMin(const Vector4& lhs, const Vector4& rhs) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorMin(const Vector4&in, const Vector4&in)", AS_FUNCTIONPR(VectorMin, (const Vector4&, const Vector4&), Vector4), AS_CALL_CDECL);

    // Vector2 VectorRound(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("Vector2 VectorRound(const Vector2&in)", AS_FUNCTIONPR(VectorRound, (const Vector2&), Vector2), AS_CALL_CDECL);

    // Vector3 VectorRound(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("Vector3 VectorRound(const Vector3&in)", AS_FUNCTIONPR(VectorRound, (const Vector3&), Vector3), AS_CALL_CDECL);

    // Vector4 VectorRound(const Vector4& vec) | File: ../Math/Vector4.h
    engine->RegisterGlobalFunction("Vector4 VectorRound(const Vector4&in)", AS_FUNCTIONPR(VectorRound, (const Vector4&), Vector4), AS_CALL_CDECL);

    // IntVector2 VectorRoundToInt(const Vector2& vec) | File: ../Math/Vector2.h
    engine->RegisterGlobalFunction("IntVector2 VectorRoundToInt(const Vector2&in)", AS_FUNCTIONPR(VectorRoundToInt, (const Vector2&), IntVector2), AS_CALL_CDECL);

    // IntVector3 VectorRoundToInt(const Vector3& vec) | File: ../Math/Vector3.h
    engine->RegisterGlobalFunction("IntVector3 VectorRoundToInt(const Vector3&in)", AS_FUNCTIONPR(VectorRoundToInt, (const Vector3&), IntVector3), AS_CALL_CDECL);

    // bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV = false) | File: ../Graphics/Drawable.h
    engine->RegisterGlobalFunction("bool WriteDrawablesToOBJ(Array<Drawable@>@, File@+, bool, bool, bool = false)", AS_FUNCTION(bool_WriteDrawablesToOBJ_constspPODVectorlesDrawablestargreamp_Filestar_bool_bool_bool), AS_CALL_CDECL);

#ifdef URHO3D_IK
    // void RegisterIKLibrary(Context* context) | File: ../IK/IK.h
    // Not registered because have @nobind mark
#endif

#ifdef URHO3D_NAVIGATION
    // void RegisterNavigationLibrary(Context* context) | File: ../Navigation/NavigationMesh.h
    // Not registered because have @nobind mark
#endif

#ifdef URHO3D_NETWORK
    // void RegisterNetworkLibrary(Context* context) | File: ../Network/Network.h
    // Not registered because have @nobind mark
#endif

#ifdef URHO3D_PHYSICS
    // void RegisterPhysicsLibrary(Context* context) | File: ../Physics/PhysicsWorld.h
    // Not registered because have @nobind mark
#endif

#ifdef URHO3D_URHO2D
    // void RegisterUrho2DLibrary(Context* context) | File: ../Urho2D/Urho2D.h
    // Not registered because have @nobind mark
#endif
}

}
