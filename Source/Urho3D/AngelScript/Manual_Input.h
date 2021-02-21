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

#pragma once

#include "../Input/Input.h"

namespace Urho3D
{

// bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h
bool InputSaveGestures(File* file, Input* ptr);
// bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h
bool InputSaveGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr);
// bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h
bool InputSaveGesture(File* file, unsigned gestureID, Input* ptr);
// bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h
bool InputSaveGestureVectorBuffer(VectorBuffer& buffer, unsigned gestureID, Input* ptr);
// unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h
unsigned InputLoadGestures(File* file, Input* ptr);
// unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h
unsigned InputLoadGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr);
// void Input::SetMouseGrabbed(bool grab, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseGrabbed(bool enable, Input* ptr);
// void Input::SetMouseMode(MouseMode mode, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseMode(MouseMode mode, Input* ptr);
// void Input::SetMouseVisible(bool enable, bool suppressEvent=false) | File: ../Input/Input.h
void InputSetMouseVisible(bool enable, Input* ptr);

#define REGISTER_MANUAL_PART_Input(T, className) \
    /* bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGestures(File@+)", AS_FUNCTION_OBJLAST(InputSaveGestures), AS_CALL_CDECL_OBJLAST); \
    /* bool Input::SaveGestures(Serializer &dest) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGestures(VectorBuffer&)", AS_FUNCTION_OBJLAST(InputSaveGesturesVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGesture(File@+, uint)", AS_FUNCTION_OBJLAST(InputSaveGesture), AS_CALL_CDECL_OBJLAST); \
    /* bool Input::SaveGesture(Serializer &dest, unsigned gestureID) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGesture(VectorBuffer&, uint)", AS_FUNCTION_OBJLAST(InputSaveGestureVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "uint LoadGestures(File@+)", AS_FUNCTION_OBJLAST(InputLoadGestures), AS_CALL_CDECL_OBJLAST); \
    /* unsigned Input::LoadGestures(Deserializer &source) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "uint LoadGestures(VectorBuffer&)", AS_FUNCTION_OBJLAST(InputLoadGesturesVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* void Input::SetMouseGrabbed(bool grab, bool suppressEvent=false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseGrabbed(bool)", AS_FUNCTION_OBJLAST(InputSetMouseGrabbed), AS_CALL_CDECL_OBJLAST); \
    /* void Input::SetMouseMode(MouseMode mode, bool suppressEvent=false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseMode(MouseMode)", AS_FUNCTION_OBJLAST(InputSetMouseMode), AS_CALL_CDECL_OBJLAST); \
    /* void Input::SetMouseVisible(bool enable, bool suppressEvent=false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseVisible(bool)", AS_FUNCTION_OBJLAST(InputSetMouseVisible), AS_CALL_CDECL_OBJLAST);

}
