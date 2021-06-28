//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../AngelScript/Manual_Graphics.h"
#include "../Scene/Scene.h"
#include "../Graphics/DebugRenderer.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Graphics(asIScriptEngine* engine)
{
    // enum TextureUnit | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_ALBEDOBUFFER", TU_ALBEDOBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMALBUFFER", TU_NORMALBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTRAMP", TU_LIGHTRAMP);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTSHAPE", TU_LIGHTSHAPE);
    engine->RegisterEnumValue("TextureUnit", "TU_SHADOWMAP", TU_SHADOWMAP);
#ifdef DESKTOP_GRAPHICS
    engine->RegisterEnumValue("TextureUnit", "TU_VOLUMEMAP", TU_VOLUMEMAP);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM1", TU_CUSTOM1);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM2", TU_CUSTOM2);
    engine->RegisterEnumValue("TextureUnit", "TU_FACESELECT", TU_FACESELECT);
    engine->RegisterEnumValue("TextureUnit", "TU_INDIRECTION", TU_INDIRECTION);
    engine->RegisterEnumValue("TextureUnit", "TU_DEPTHBUFFER", TU_DEPTHBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTBUFFER", TU_LIGHTBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_ZONE", TU_ZONE);
#endif
    engine->RegisterEnumValue("TextureUnit", "MAX_MATERIAL_TEXTURE_UNITS", MAX_MATERIAL_TEXTURE_UNITS);
    engine->RegisterEnumValue("TextureUnit", "MAX_TEXTURE_UNITS", MAX_TEXTURE_UNITS);
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Graphics* GetGraphics()
{
    return GetScriptContext()->GetSubsystem<Graphics>();
}

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Renderer* GetRenderer()
{
    return GetScriptContext()->GetSubsystem<Renderer>();
}

// template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Scene.h
static DebugRenderer* GetDebugRenderer()
{
    Scene* scene = GetScriptContextScene();
    if (scene)
        return scene->GetComponent<DebugRenderer>();
    else
        return nullptr;
}

// template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Scene.h
static Octree* GetOctree()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<Octree>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Graphics(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Graphics@+ get_graphics()", AS_FUNCTION(GetGraphics), AS_CALL_CDECL);

    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Renderer@+ get_renderer()", AS_FUNCTION(GetRenderer), AS_CALL_CDECL);

    // template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Scene.h
    engine->RegisterGlobalFunction("DebugRenderer@+ get_debugRenderer()", AS_FUNCTION(GetDebugRenderer), AS_CALL_CDECL);

    // template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Scene.h
    engine->RegisterGlobalFunction("Octree@+ get_octree()", AS_FUNCTION(GetOctree), AS_CALL_CDECL);
}

// ========================================================================================

TechniqueEntry noTechniqueEntry;

}
