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

#include "../AngelScript/Manual_Input.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Input(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Input* GetInput()
{
    return GetScriptContext()->GetSubsystem<Input>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Input(asIScriptEngine* engine)
{
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Input@+ get_input()", asFUNCTION(GetInput), asCALL_CDECL);
}

// ========================================================================================

// bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h
bool InputSaveGestures(File* file, Input* ptr)
{
    return file && ptr->SaveGestures(*file);
}

// bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h
bool InputSaveGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr)
{
    return ptr->SaveGestures(buffer);
}

// bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h
bool InputSaveGesture(File* file, unsigned gestureID, Input* ptr)
{
    return file && ptr->SaveGesture(*file, gestureID);
}

// bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h
bool InputSaveGestureVectorBuffer(VectorBuffer& buffer, unsigned gestureID, Input* ptr)
{
    return ptr->SaveGesture(buffer, gestureID);
}

// unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h
unsigned InputLoadGestures(File* file, Input* ptr)
{
    return file ? ptr->LoadGestures(*file) : 0;
}

// unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h
unsigned InputLoadGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr)
{
    return ptr->LoadGestures(buffer);
}

// void Input::SetMouseGrabbed(bool grab, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseGrabbed(bool enable, Input* ptr)
{
    ptr->SetMouseGrabbed(enable, false);
}

// void Input::SetMouseMode(MouseMode mode, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseMode(MouseMode mode, Input* ptr)
{
    ptr->SetMouseMode(mode, false);
}

// void Input::SetMouseVisible(bool enable, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseVisible(bool enable, Input* ptr)
{
    ptr->SetMouseVisible(enable, false);
}

}