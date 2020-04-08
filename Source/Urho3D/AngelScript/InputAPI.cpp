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
#include "../Input/Controls.h"
#include "../Input/Input.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

static void ConstructControls(Controls* ptr)
{
    new(ptr)Controls();
}

static void ConstructControlsCopy(const Controls& controls, Controls* ptr)
{
    new(ptr)Controls(controls);
}

static void DestructControls(Controls* ptr)
{
    ptr->~Controls();
}

static void RegisterControls(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asOBJ_APP_CLASS_CDK);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f(const Controls&in)", asFUNCTION(ConstructControlsCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Controls", "Controls& opAssign(const Controls&in)", asMETHOD(Controls, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Reset()", asMETHOD(Controls, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void Set(uint, bool)", asMETHOD(Controls, Set), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsDown(uint) const", asMETHOD(Controls, IsDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool IsPressed(uint, const Controls&in) const", asMETHOD(Controls, IsPressed), asCALL_THISCALL);
    engine->RegisterObjectProperty("Controls", "uint buttons", offsetof(Controls, buttons_));
    engine->RegisterObjectProperty("Controls", "float yaw", offsetof(Controls, yaw_));
    engine->RegisterObjectProperty("Controls", "float pitch", offsetof(Controls, pitch_));
    engine->RegisterObjectProperty("Controls", "VariantMap extraData", offsetof(Controls, extraData_));
}

static void RegisterInputConstants(asIScriptEngine* engine)
{
}

static Input* GetInput()
{
    return GetScriptContext()->GetSubsystem<Input>();
}

static bool InputSaveGestures(File* file, Input* ptr)
{
    return file && ptr->SaveGestures(*file);
}

static bool InputSaveGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr)
{
    return ptr->SaveGestures(buffer);
}

static bool InputSaveGesture(File* file, unsigned gestureID, Input* ptr)
{
    return file && ptr->SaveGesture(*file, gestureID);
}

static bool InputSaveGestureVectorBuffer(VectorBuffer& buffer, unsigned gestureID, Input* ptr)
{
    return ptr->SaveGesture(buffer, gestureID);
}

static unsigned InputLoadGestures(File* file, Input* ptr)
{
    return file ? ptr->LoadGestures(*file) : 0;
}

static unsigned InputLoadGesturesVectorBuffer(VectorBuffer& buffer, Input* ptr)
{
    return ptr->LoadGestures(buffer);
}

static void InputSetMouseVisible(bool enable, Input* ptr)
{
    ptr->SetMouseVisible(enable, false);
}

static void InputSetMouseMode(MouseMode mode, Input* ptr)
{
    ptr->SetMouseMode(mode, false);
}

static void InputSetMouseGrabbed(bool enable, Input* ptr)
{
    ptr->SetMouseGrabbed(enable, false);
}

static void RegisterInput(asIScriptEngine* engine)
{
    engine->RegisterObjectType("TouchState", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("TouchState", "const int touchID", offsetof(TouchState, touchID_));
    engine->RegisterObjectProperty("TouchState", "const IntVector2 position", offsetof(TouchState, position_));
    engine->RegisterObjectProperty("TouchState", "const IntVector2 lastPosition", offsetof(TouchState, lastPosition_));
    engine->RegisterObjectProperty("TouchState", "const IntVector2 delta", offsetof(TouchState, delta_));
    engine->RegisterObjectProperty("TouchState", "const float pressure", offsetof(TouchState, pressure_));

    engine->RegisterObjectType("JoystickState", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("JoystickState", "const String name", offsetof(JoystickState, name_));
    engine->RegisterObjectProperty("JoystickState", "const int joystickID", offsetof(JoystickState, joystickID_));
    engine->RegisterObjectMethod("JoystickState", "bool get_controller() const", asMETHOD(JoystickState, IsController), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numButtons() const", asMETHOD(JoystickState, GetNumButtons), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numAxes() const", asMETHOD(JoystickState, GetNumAxes), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numHats() const", asMETHOD(JoystickState, GetNumHats), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonDown(uint) const", asMETHOD(JoystickState, GetButtonDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonPress(uint) const", asMETHOD(JoystickState, GetButtonPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "float get_axisPosition(uint) const", asMETHOD(JoystickState, GetAxisPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "int get_hatPosition(uint) const", asMETHOD(JoystickState, GetHatPosition), asCALL_THISCALL);

    RegisterObject<Input>(engine, "Input");
    engine->RegisterObjectMethod("Input", "int AddScreenJoystick(XMLFile@+ layoutFile = null, XMLFile@+ styleFile = null)", asMETHOD(Input, AddScreenJoystick), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool RemoveScreenJoystick(int)", asMETHOD(Input, RemoveScreenJoystick), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool RecordGesture()", asMETHOD(Input, RecordGesture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool SaveGestures(File@+)", asFUNCTION(InputSaveGestures), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "bool SaveGestures(VectorBuffer&)", asFUNCTION(InputSaveGesturesVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "bool SaveGesture(File@+, uint)", asFUNCTION(InputSaveGesture), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "bool SaveGesture(VectorBuffer&, uint)", asFUNCTION(InputSaveGestureVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "uint LoadGestures(File@+)", asFUNCTION(InputLoadGestures), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "uint LoadGestures(VectorBuffer&)", asFUNCTION(InputLoadGesturesVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "bool RemoveGesture(uint)", asMETHOD(Input, RemoveGesture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void RemoveAllGestures()", asMETHOD(Input, RemoveAllGestures), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void CenterMousePosition()", asMETHOD(Input, CenterMousePosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int GetKeyFromName(const String&in) const", asMETHOD(Input, GetKeyFromName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int GetKeyFromScancode(int) const", asMETHOD(Input, GetKeyFromScancode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "String GetKeyName(int) const", asMETHOD(Input, GetKeyName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int GetScancodeFromKey(int) const", asMETHOD(Input, GetScancodeFromKey), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int GetScancodeFromName(const String&in) const", asMETHOD(Input, GetScancodeFromName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "String GetScancodeName(int) const", asMETHOD(Input, GetScancodeName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void SetMouseVisible(bool enable, bool suppressEvent = false)", asMETHOD(Input, SetMouseVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mouseVisible(bool)", asFUNCTION(InputSetMouseVisible), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "void ResetMouseVisible()", asMETHOD(Input, ResetMouseVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseVisible() const", asMETHOD(Input, IsMouseVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void SetMouseGrabbed(bool, bool = false)", asMETHOD(Input, SetMouseGrabbed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mouseGrabbed(bool)", asFUNCTION(InputSetMouseGrabbed), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "bool get_mouseGrabbed() const", asMETHOD(Input, IsMouseGrabbed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void ResetMouseGrabbed()", asMETHOD(Input, ResetMouseGrabbed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void SetMouseMode(MouseMode, bool = false)", asMETHOD(Input, SetMouseMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mouseMode(MouseMode)", asFUNCTION(InputSetMouseMode), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Input", "void ResetMouseMode()", asMETHOD(Input, ResetMouseMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "MouseMode get_mouseMode() const", asMETHOD(Input, GetMouseMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseLocked() const", asMETHOD(Input, IsMouseLocked), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenJoystickVisible(int, bool)", asMETHOD(Input, SetScreenJoystickVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenJoystickVisible(int)", asMETHOD(Input, IsScreenJoystickVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_screenKeyboardVisible(bool)", asMETHOD(Input, SetScreenKeyboardVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardVisible() const", asMETHOD(Input, IsScreenKeyboardVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_screenKeyboardSupport() const", asMETHOD(Input, GetScreenKeyboardSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_touchEmulation(bool)", asMETHOD(Input, SetTouchEmulation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_touchEmulation() const", asMETHOD(Input, GetTouchEmulation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_toggleFullscreen(bool)", asMETHOD(Input, SetToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_toggleFullscreen() const", asMETHOD(Input, GetToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyDown(int) const", asMETHOD(Input, GetKeyDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_keyPress(int) const", asMETHOD(Input, GetKeyPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodeDown(int) const", asMETHOD(Input, GetScancodeDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_scancodePress(int) const", asMETHOD(Input, GetScancodePress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonDown(int) const", asMETHOD(Input, GetMouseButtonDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseButtonPress(int) const", asMETHOD(Input, GetMouseButtonPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierDown(int) const", asMETHOD(Input, GetQualifierDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_qualifierPress(int) const", asMETHOD(Input, GetQualifierPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_qualifiers() const", asMETHOD(Input, GetQualifiers), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mousePosition(const IntVector2&in)", asMETHOD(Input, SetMousePosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mousePosition() const", asMETHOD(Input, GetMousePosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "IntVector2 get_mouseMove() const", asMETHOD(Input, GetMouseMove), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveX() const", asMETHOD(Input, GetMouseMoveX), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveY() const", asMETHOD(Input, GetMouseMoveY), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveWheel() const", asMETHOD(Input, GetMouseMoveWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "Vector2 get_inputScale() const", asMETHOD(Input, GetInputScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numTouches() const", asMETHOD(Input, GetNumTouches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "TouchState@+ get_touches(uint) const", asMETHOD(Input, GetTouch), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numJoysticks() const", asMETHOD(Input, GetNumJoysticks), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticks(int)", asMETHOD(Input, GetJoystick), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByIndex(uint)", asMETHOD(Input, GetJoystickByIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByName(const String& in)", asMETHOD(Input, GetJoystickByName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_focus() const", asMETHOD(Input, HasFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_minimized() const", asMETHOD(Input, IsMinimized), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Input@+ get_input()", asFUNCTION(GetInput), asCALL_CDECL);
}

void RegisterInputAPI(asIScriptEngine* engine)
{
    RegisterControls(engine);
    RegisterInputConstants(engine);
    RegisterInput(engine);
}

}
