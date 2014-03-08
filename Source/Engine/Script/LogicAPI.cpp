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
#include "SplinePath.h"

namespace Urho3D
{

static void RegisterSplinePath(asIScriptEngine* engine)
{
    RegisterComponent<SplinePath>(engine, "SplinePath");
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", asMETHOD(SplinePath, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", asMETHOD(SplinePath, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", asMETHOD(SplinePath, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", asMETHOD(SplinePath, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_position(float)", asMETHOD(SplinePath, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 get_position() const", asMETHOD(SplinePath, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", asMETHOD(SplinePath, GetPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", asMETHOD(SplinePath, Move), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Reset()", asMETHOD(SplinePath, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_finished() const", asMETHOD(SplinePath, IsFinished), asCALL_THISCALL);
}


void RegisterLogicAPI(asIScriptEngine* engine)
{
    RegisterSplinePath(engine);
}
}