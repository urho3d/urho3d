// DO NOT EDIT. This file is generated

#pragma once

#include "../AngelScript/APITemplates.h"
#include "../AngelScript/Manual.h"

#include "../Core/ProcessUtils.h"
#include "../Graphics/Drawable.h"

namespace Urho3D
{

// const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument=true) | File: ../Core/ProcessUtils.h
CScriptArray* ParseArguments_String_bool(const String& cmdLine, bool skipFirstArgument);
// const Vector<String>& GetArguments() | File: ../Core/ProcessUtils.h
CScriptArray* GetArguments_void();
// bool WriteDrawablesToOBJ(const PODVector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV=false) | File: ../Graphics/Drawable.h
bool WriteDrawablesToOBJ_PODVectorDrawable_File_bool_bool_bool(CScriptArray* drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV);
}
