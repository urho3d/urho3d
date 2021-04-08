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

// bool Input::SaveGestures(Serializer& dest) | File: ../Input/Input.h
template <class T> bool Input_SaveGestures_File(File* file, T* ptr)
{
    return file && ptr->SaveGestures(*file);
}

// bool Input::SaveGestures(Serializer& dest) | File: ../Input/Input.h
template <class T> bool Input_SaveGestures_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->SaveGestures(buffer);
}

// bool Input::SaveGesture(Serializer& dest, unsigned gestureID) | File: ../Input/Input.h
template <class T> bool Input_SaveGesture_File_uint(File* file, unsigned gestureID, T* ptr)
{
    return file && ptr->SaveGesture(*file, gestureID);
}

// bool Input::SaveGesture(Serializer& dest, unsigned gestureID) | File: ../Input/Input.h
template <class T> bool Input_SaveGesture_VectorBuffer_uint(VectorBuffer& buffer, unsigned gestureID, T* ptr)
{
    return ptr->SaveGesture(buffer, gestureID);
}

// unsigned Input::LoadGestures(Deserializer& source) | File: ../Input/Input.h
template <class T> unsigned Input_LoadGestures_File(File* file, T* ptr)
{
    return file ? ptr->LoadGestures(*file) : 0;
}

// unsigned Input::LoadGestures(Deserializer& source) | File: ../Input/Input.h
template <class T> unsigned Input_LoadGestures_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->LoadGestures(buffer);
}

// void Input::SetMouseGrabbed(bool grab, bool suppressEvent = false) | File: ../Input/Input.h
template <class T> void Input_SetMouseGrabbed(bool enable, T* ptr)
{
    ptr->SetMouseGrabbed(enable, false);
}

// void Input::SetMouseMode(MouseMode mode, bool suppressEvent = false) | File: ../Input/Input.h
template <class T> void Input_SetMouseMode(MouseMode mode, T* ptr)
{
    ptr->SetMouseMode(mode, false);
}

// void Input::SetMouseVisible(bool enable, bool suppressEvent = false) | File: ../Input/Input.h
template <class T> void Input_SetMouseVisible(bool enable, T* ptr)
{
    ptr->SetMouseVisible(enable, false);
}

#define REGISTER_MEMBERS_MANUAL_PART_Input() \
    /* bool Input::SaveGestures(Serializer& dest) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGestures(File@+)", AS_FUNCTION_OBJLAST(Input_SaveGestures_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveGestures(VectorBuffer&)", AS_FUNCTION_OBJLAST(Input_SaveGestures_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool Input::SaveGesture(Serializer& dest, unsigned gestureID) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "bool SaveGesture(File@+, uint)", AS_FUNCTION_OBJLAST(Input_SaveGesture_File_uint<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveGesture(VectorBuffer&, uint)", AS_FUNCTION_OBJLAST(Input_SaveGesture_VectorBuffer_uint<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* unsigned Input::LoadGestures(Deserializer& source) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "uint LoadGestures(File@+)", AS_FUNCTION_OBJLAST(Input_LoadGestures_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "uint LoadGestures(VectorBuffer&)", AS_FUNCTION_OBJLAST(Input_LoadGestures_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Input::SetMouseGrabbed(bool grab, bool suppressEvent = false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseGrabbed(bool)", AS_FUNCTION_OBJLAST(Input_SetMouseGrabbed<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Input::SetMouseMode(MouseMode mode, bool suppressEvent = false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseMode(MouseMode)", AS_FUNCTION_OBJLAST(Input_SetMouseMode<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Input::SetMouseVisible(bool enable, bool suppressEvent = false) | File: ../Input/Input.h */ \
    engine->RegisterObjectMethod(className, "void set_mouseVisible(bool)", AS_FUNCTION_OBJLAST(Input_SetMouseVisible<T>), AS_CALL_CDECL_OBJLAST);

}
