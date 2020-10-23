// DO NOT EDIT. This file is generated

#include "../Precompiled.h"

#include "../AngelScript/GeneratedGlue.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument=true) | File: ../Core/ProcessUtils.h
CScriptArray* ParseArguments_String_bool(const String& cmdLine, bool skipFirstArgument)
{
    const Vector<String>& result = ParseArguments(cmdLine, skipFirstArgument);
    return VectorToArray<String>(result, "Array<String>");
}

// const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
CScriptArray* GetArguments_void()
{
    const Vector<String>& result = GetArguments();
    return VectorToArray<String>(result, "Array<String>");
}

// bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV=false) | File: ../Graphics/Drawable.h
bool WriteDrawablesToOBJ_PODVectorDrawable_File_bool_bool_bool(CScriptArray* drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV)
{
    PODVector<Drawable*> param0 = ArrayToPODVector<Drawable*>(drawables);
    bool result = WriteDrawablesToOBJ(param0, outputFile, asZUp, asRightHanded, writeLightmapUV);
    return result;
}

}
