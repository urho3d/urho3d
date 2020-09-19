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

#include "../Engine/Console.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Engine(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Console* GetConsole()
{
    return GetScriptContext()->GetSubsystem<Console>();
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static DebugHud* GetDebugHud()
{
    return GetScriptContext()->GetSubsystem<DebugHud>();
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Engine* GetEngine()
{
    return GetScriptContext()->GetSubsystem<Engine>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Engine(asIScriptEngine* engine)
{
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Console@+ get_console()", asFUNCTION(GetConsole), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("DebugHud@+ get_debugHud()", asFUNCTION(GetDebugHud), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Engine@+ get_engine()", asFUNCTION(GetEngine), asCALL_CDECL);
}

}
