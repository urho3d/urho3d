//
// Copyright (c) 2008-2015 the Urho3D project.
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
    engine->RegisterGlobalProperty("const int MOUSEB_LEFT", (void*)&MOUSEB_LEFT);
    engine->RegisterGlobalProperty("const int MOUSEB_MIDDLE", (void*)&MOUSEB_MIDDLE);
    engine->RegisterGlobalProperty("const int MOUSEB_RIGHT", (void*)&MOUSEB_RIGHT);
    engine->RegisterGlobalProperty("const int QUAL_SHIFT", (void*)&QUAL_SHIFT);
    engine->RegisterGlobalProperty("const int QUAL_CTRL", (void*)&QUAL_CTRL);
    engine->RegisterGlobalProperty("const int QUAL_ALT", (void*)&QUAL_ALT);
    engine->RegisterGlobalProperty("const int QUAL_ANY", (void*)&QUAL_ANY);
    engine->RegisterGlobalProperty("const int KEY_A", (void*)&KEY_A);
    engine->RegisterGlobalProperty("const int KEY_B", (void*)&KEY_B);
    engine->RegisterGlobalProperty("const int KEY_C", (void*)&KEY_C);
    engine->RegisterGlobalProperty("const int KEY_D", (void*)&KEY_D);
    engine->RegisterGlobalProperty("const int KEY_E", (void*)&KEY_E);
    engine->RegisterGlobalProperty("const int KEY_F", (void*)&KEY_F);
    engine->RegisterGlobalProperty("const int KEY_G", (void*)&KEY_G);
    engine->RegisterGlobalProperty("const int KEY_H", (void*)&KEY_H);
    engine->RegisterGlobalProperty("const int KEY_I", (void*)&KEY_I);
    engine->RegisterGlobalProperty("const int KEY_J", (void*)&KEY_J);
    engine->RegisterGlobalProperty("const int KEY_K", (void*)&KEY_K);
    engine->RegisterGlobalProperty("const int KEY_L", (void*)&KEY_L);
    engine->RegisterGlobalProperty("const int KEY_M", (void*)&KEY_M);
    engine->RegisterGlobalProperty("const int KEY_N", (void*)&KEY_N);
    engine->RegisterGlobalProperty("const int KEY_O", (void*)&KEY_O);
    engine->RegisterGlobalProperty("const int KEY_P", (void*)&KEY_P);
    engine->RegisterGlobalProperty("const int KEY_Q", (void*)&KEY_Q);
    engine->RegisterGlobalProperty("const int KEY_R", (void*)&KEY_R);
    engine->RegisterGlobalProperty("const int KEY_S", (void*)&KEY_S);
    engine->RegisterGlobalProperty("const int KEY_T", (void*)&KEY_T);
    engine->RegisterGlobalProperty("const int KEY_U", (void*)&KEY_U);
    engine->RegisterGlobalProperty("const int KEY_V", (void*)&KEY_V);
    engine->RegisterGlobalProperty("const int KEY_W", (void*)&KEY_W);
    engine->RegisterGlobalProperty("const int KEY_X", (void*)&KEY_X);
    engine->RegisterGlobalProperty("const int KEY_Y", (void*)&KEY_Y);
    engine->RegisterGlobalProperty("const int KEY_Z", (void*)&KEY_Z);
    engine->RegisterGlobalProperty("const int KEY_0", (void*)&KEY_0);
    engine->RegisterGlobalProperty("const int KEY_1", (void*)&KEY_1);
    engine->RegisterGlobalProperty("const int KEY_2", (void*)&KEY_2);
    engine->RegisterGlobalProperty("const int KEY_3", (void*)&KEY_3);
    engine->RegisterGlobalProperty("const int KEY_4", (void*)&KEY_4);
    engine->RegisterGlobalProperty("const int KEY_5", (void*)&KEY_5);
    engine->RegisterGlobalProperty("const int KEY_6", (void*)&KEY_6);
    engine->RegisterGlobalProperty("const int KEY_7", (void*)&KEY_7);
    engine->RegisterGlobalProperty("const int KEY_8", (void*)&KEY_8);
    engine->RegisterGlobalProperty("const int KEY_9", (void*)&KEY_9);
    engine->RegisterGlobalProperty("const int KEY_BACKSPACE", (void*)&KEY_BACKSPACE);
    engine->RegisterGlobalProperty("const int KEY_TAB", (void*)&KEY_TAB);
    engine->RegisterGlobalProperty("const int KEY_RETURN", (void*)&KEY_RETURN);
    engine->RegisterGlobalProperty("const int KEY_RETURN2", (void*)&KEY_RETURN2);
    engine->RegisterGlobalProperty("const int KEY_KP_ENTER", (void*)&KEY_KP_ENTER);
    engine->RegisterGlobalProperty("const int KEY_SHIFT", (void*)&KEY_SHIFT);
    engine->RegisterGlobalProperty("const int KEY_CTRL", (void*)&KEY_CTRL);
    engine->RegisterGlobalProperty("const int KEY_ALT", (void*)&KEY_ALT);
    engine->RegisterGlobalProperty("const int KEY_GUI", (void*)&KEY_GUI);
    engine->RegisterGlobalProperty("const int KEY_PAUSE", (void*)&KEY_PAUSE);
    engine->RegisterGlobalProperty("const int KEY_CAPSLOCK", (void*)&KEY_CAPSLOCK);
    engine->RegisterGlobalProperty("const int KEY_ESC", (void*)&KEY_ESC);
    engine->RegisterGlobalProperty("const int KEY_SPACE", (void*)&KEY_SPACE);
    engine->RegisterGlobalProperty("const int KEY_PAGEUP", (void*)&KEY_PAGEUP);
    engine->RegisterGlobalProperty("const int KEY_PAGEDOWN", (void*)&KEY_PAGEDOWN);
    engine->RegisterGlobalProperty("const int KEY_END", (void*)&KEY_END);
    engine->RegisterGlobalProperty("const int KEY_HOME", (void*)&KEY_HOME);
    engine->RegisterGlobalProperty("const int KEY_LEFT", (void*)&KEY_LEFT);
    engine->RegisterGlobalProperty("const int KEY_UP", (void*)&KEY_UP);
    engine->RegisterGlobalProperty("const int KEY_RIGHT", (void*)&KEY_RIGHT);
    engine->RegisterGlobalProperty("const int KEY_DOWN", (void*)&KEY_DOWN);
    engine->RegisterGlobalProperty("const int KEY_SELECT", (void*)&KEY_SELECT);
    engine->RegisterGlobalProperty("const int KEY_PRINTSCREEN", (void*)&KEY_PRINTSCREEN);
    engine->RegisterGlobalProperty("const int KEY_INSERT", (void*)&KEY_INSERT);
    engine->RegisterGlobalProperty("const int KEY_DELETE", (void*)&KEY_DELETE);
    engine->RegisterGlobalProperty("const int KEY_LGUI", (void*)&KEY_LGUI);
    engine->RegisterGlobalProperty("const int KEY_RGUI", (void*)&KEY_RGUI);
    engine->RegisterGlobalProperty("const int KEY_APPLICATION", (void*)&KEY_APPLICATION);
    engine->RegisterGlobalProperty("const int KEY_KP_0", (void*)&KEY_KP_0);
    engine->RegisterGlobalProperty("const int KEY_KP_1", (void*)&KEY_KP_1);
    engine->RegisterGlobalProperty("const int KEY_KP_2", (void*)&KEY_KP_2);
    engine->RegisterGlobalProperty("const int KEY_KP_3", (void*)&KEY_KP_3);
    engine->RegisterGlobalProperty("const int KEY_KP_4", (void*)&KEY_KP_4);
    engine->RegisterGlobalProperty("const int KEY_KP_5", (void*)&KEY_KP_5);
    engine->RegisterGlobalProperty("const int KEY_KP_6", (void*)&KEY_KP_6);
    engine->RegisterGlobalProperty("const int KEY_KP_7", (void*)&KEY_KP_7);
    engine->RegisterGlobalProperty("const int KEY_KP_8", (void*)&KEY_KP_8);
    engine->RegisterGlobalProperty("const int KEY_KP_9", (void*)&KEY_KP_9);
    engine->RegisterGlobalProperty("const int KEY_KP_MULTIPLY", (void*)&KEY_KP_MULTIPLY);
    engine->RegisterGlobalProperty("const int KEY_KP_PLUS", (void*)&KEY_KP_PLUS);
    engine->RegisterGlobalProperty("const int KEY_KP_MINUS", (void*)&KEY_KP_MINUS);
    engine->RegisterGlobalProperty("const int KEY_KP_PERIOD", (void*)&KEY_KP_PERIOD);
    engine->RegisterGlobalProperty("const int KEY_KP_DIVIDE", (void*)&KEY_KP_DIVIDE);
    engine->RegisterGlobalProperty("const int KEY_F1", (void*)&KEY_F1);
    engine->RegisterGlobalProperty("const int KEY_F2", (void*)&KEY_F2);
    engine->RegisterGlobalProperty("const int KEY_F3", (void*)&KEY_F3);
    engine->RegisterGlobalProperty("const int KEY_F4", (void*)&KEY_F4);
    engine->RegisterGlobalProperty("const int KEY_F5", (void*)&KEY_F5);
    engine->RegisterGlobalProperty("const int KEY_F6", (void*)&KEY_F6);
    engine->RegisterGlobalProperty("const int KEY_F7", (void*)&KEY_F7);
    engine->RegisterGlobalProperty("const int KEY_F8", (void*)&KEY_F8);
    engine->RegisterGlobalProperty("const int KEY_F9", (void*)&KEY_F9);
    engine->RegisterGlobalProperty("const int KEY_F10", (void*)&KEY_F10);
    engine->RegisterGlobalProperty("const int KEY_F11", (void*)&KEY_F11);
    engine->RegisterGlobalProperty("const int KEY_F12", (void*)&KEY_F12);
    engine->RegisterGlobalProperty("const int KEY_F13", (void*)&KEY_F13);
    engine->RegisterGlobalProperty("const int KEY_F14", (void*)&KEY_F14);
    engine->RegisterGlobalProperty("const int KEY_F15", (void*)&KEY_F15);
    engine->RegisterGlobalProperty("const int KEY_F16", (void*)&KEY_F16);
    engine->RegisterGlobalProperty("const int KEY_F17", (void*)&KEY_F17);
    engine->RegisterGlobalProperty("const int KEY_F18", (void*)&KEY_F18);
    engine->RegisterGlobalProperty("const int KEY_F19", (void*)&KEY_F19);
    engine->RegisterGlobalProperty("const int KEY_F20", (void*)&KEY_F20);
    engine->RegisterGlobalProperty("const int KEY_F21", (void*)&KEY_F21);
    engine->RegisterGlobalProperty("const int KEY_F22", (void*)&KEY_F22);
    engine->RegisterGlobalProperty("const int KEY_F23", (void*)&KEY_F23);
    engine->RegisterGlobalProperty("const int KEY_F24", (void*)&KEY_F24);
    engine->RegisterGlobalProperty("const int KEY_NUMLOCKCLEAR", (void*)&KEY_NUMLOCKCLEAR);
    engine->RegisterGlobalProperty("const int KEY_SCROLLLOCK", (void*)&KEY_SCROLLLOCK);
    engine->RegisterGlobalProperty("const int KEY_LSHIFT", (void*)&KEY_LSHIFT);
    engine->RegisterGlobalProperty("const int KEY_RSHIFT", (void*)&KEY_RSHIFT);
    engine->RegisterGlobalProperty("const int KEY_LCTRL", (void*)&KEY_LCTRL);
    engine->RegisterGlobalProperty("const int KEY_RCTRL", (void*)&KEY_RCTRL);
    engine->RegisterGlobalProperty("const int KEY_LALT", (void*)&KEY_LALT);
    engine->RegisterGlobalProperty("const int KEY_RALT", (void*)&KEY_RALT);
    engine->RegisterGlobalProperty("const int SCANCODE_UNKNOWN", (void*)&SCANCODE_UNKNOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_CTRL", (void*)&SCANCODE_CTRL);
    engine->RegisterGlobalProperty("const int SCANCODE_SHIFT", (void*)&SCANCODE_SHIFT);
    engine->RegisterGlobalProperty("const int SCANCODE_ALT", (void*)&SCANCODE_ALT);
    engine->RegisterGlobalProperty("const int SCANCODE_GUI", (void*)&SCANCODE_GUI);
    engine->RegisterGlobalProperty("const int SCANCODE_A", (void*)&SCANCODE_A);
    engine->RegisterGlobalProperty("const int SCANCODE_B", (void*)&SCANCODE_B);
    engine->RegisterGlobalProperty("const int SCANCODE_C", (void*)&SCANCODE_C);
    engine->RegisterGlobalProperty("const int SCANCODE_D", (void*)&SCANCODE_D);
    engine->RegisterGlobalProperty("const int SCANCODE_E", (void*)&SCANCODE_E);
    engine->RegisterGlobalProperty("const int SCANCODE_F", (void*)&SCANCODE_F);
    engine->RegisterGlobalProperty("const int SCANCODE_G", (void*)&SCANCODE_G);
    engine->RegisterGlobalProperty("const int SCANCODE_H", (void*)&SCANCODE_H);
    engine->RegisterGlobalProperty("const int SCANCODE_I", (void*)&SCANCODE_I);
    engine->RegisterGlobalProperty("const int SCANCODE_J", (void*)&SCANCODE_J);
    engine->RegisterGlobalProperty("const int SCANCODE_K", (void*)&SCANCODE_K);
    engine->RegisterGlobalProperty("const int SCANCODE_L", (void*)&SCANCODE_L);
    engine->RegisterGlobalProperty("const int SCANCODE_M", (void*)&SCANCODE_M);
    engine->RegisterGlobalProperty("const int SCANCODE_N", (void*)&SCANCODE_N);
    engine->RegisterGlobalProperty("const int SCANCODE_O", (void*)&SCANCODE_O);
    engine->RegisterGlobalProperty("const int SCANCODE_P", (void*)&SCANCODE_P);
    engine->RegisterGlobalProperty("const int SCANCODE_Q", (void*)&SCANCODE_Q);
    engine->RegisterGlobalProperty("const int SCANCODE_R", (void*)&SCANCODE_R);
    engine->RegisterGlobalProperty("const int SCANCODE_S", (void*)&SCANCODE_S);
    engine->RegisterGlobalProperty("const int SCANCODE_T", (void*)&SCANCODE_T);
    engine->RegisterGlobalProperty("const int SCANCODE_U", (void*)&SCANCODE_U);
    engine->RegisterGlobalProperty("const int SCANCODE_V", (void*)&SCANCODE_V);
    engine->RegisterGlobalProperty("const int SCANCODE_W", (void*)&SCANCODE_W);
    engine->RegisterGlobalProperty("const int SCANCODE_X", (void*)&SCANCODE_X);
    engine->RegisterGlobalProperty("const int SCANCODE_Y", (void*)&SCANCODE_Y);
    engine->RegisterGlobalProperty("const int SCANCODE_Z", (void*)&SCANCODE_Z);
    engine->RegisterGlobalProperty("const int SCANCODE_1", (void*)&SCANCODE_1);
    engine->RegisterGlobalProperty("const int SCANCODE_2", (void*)&SCANCODE_2);
    engine->RegisterGlobalProperty("const int SCANCODE_3", (void*)&SCANCODE_3);
    engine->RegisterGlobalProperty("const int SCANCODE_4", (void*)&SCANCODE_4);
    engine->RegisterGlobalProperty("const int SCANCODE_5", (void*)&SCANCODE_5);
    engine->RegisterGlobalProperty("const int SCANCODE_6", (void*)&SCANCODE_6);
    engine->RegisterGlobalProperty("const int SCANCODE_7", (void*)&SCANCODE_7);
    engine->RegisterGlobalProperty("const int SCANCODE_8", (void*)&SCANCODE_8);
    engine->RegisterGlobalProperty("const int SCANCODE_9", (void*)&SCANCODE_9);
    engine->RegisterGlobalProperty("const int SCANCODE_0", (void*)&SCANCODE_0);
    engine->RegisterGlobalProperty("const int SCANCODE_RETURN", (void*)&SCANCODE_RETURN);
    engine->RegisterGlobalProperty("const int SCANCODE_ESCAPE", (void*)&SCANCODE_ESCAPE);
    engine->RegisterGlobalProperty("const int SCANCODE_BACKSPACE", (void*)&SCANCODE_BACKSPACE);
    engine->RegisterGlobalProperty("const int SCANCODE_TAB", (void*)&SCANCODE_TAB);
    engine->RegisterGlobalProperty("const int SCANCODE_SPACE", (void*)&SCANCODE_SPACE);
    engine->RegisterGlobalProperty("const int SCANCODE_MINUS", (void*)&SCANCODE_MINUS);
    engine->RegisterGlobalProperty("const int SCANCODE_EQUALS", (void*)&SCANCODE_EQUALS);
    engine->RegisterGlobalProperty("const int SCANCODE_LEFTBRACKET", (void*)&SCANCODE_LEFTBRACKET);
    engine->RegisterGlobalProperty("const int SCANCODE_RIGHTBRACKET", (void*)&SCANCODE_RIGHTBRACKET);
    engine->RegisterGlobalProperty("const int SCANCODE_BACKSLASH", (void*)&SCANCODE_BACKSLASH);
    engine->RegisterGlobalProperty("const int SCANCODE_NONUSHASH", (void*)&SCANCODE_NONUSHASH);
    engine->RegisterGlobalProperty("const int SCANCODE_SEMICOLON", (void*)&SCANCODE_SEMICOLON);
    engine->RegisterGlobalProperty("const int SCANCODE_APOSTROPHE", (void*)&SCANCODE_APOSTROPHE);
    engine->RegisterGlobalProperty("const int SCANCODE_GRAVE", (void*)&SCANCODE_GRAVE);
    engine->RegisterGlobalProperty("const int SCANCODE_COMMA", (void*)&SCANCODE_COMMA);
    engine->RegisterGlobalProperty("const int SCANCODE_PERIOD", (void*)&SCANCODE_PERIOD);
    engine->RegisterGlobalProperty("const int SCANCODE_SLASH", (void*)&SCANCODE_SLASH);
    engine->RegisterGlobalProperty("const int SCANCODE_CAPSLOCK", (void*)&SCANCODE_CAPSLOCK);
    engine->RegisterGlobalProperty("const int SCANCODE_F1", (void*)&SCANCODE_F1);
    engine->RegisterGlobalProperty("const int SCANCODE_F2", (void*)&SCANCODE_F2);
    engine->RegisterGlobalProperty("const int SCANCODE_F3", (void*)&SCANCODE_F3);
    engine->RegisterGlobalProperty("const int SCANCODE_F4", (void*)&SCANCODE_F4);
    engine->RegisterGlobalProperty("const int SCANCODE_F5", (void*)&SCANCODE_F5);
    engine->RegisterGlobalProperty("const int SCANCODE_F6", (void*)&SCANCODE_F6);
    engine->RegisterGlobalProperty("const int SCANCODE_F7", (void*)&SCANCODE_F7);
    engine->RegisterGlobalProperty("const int SCANCODE_F8", (void*)&SCANCODE_F8);
    engine->RegisterGlobalProperty("const int SCANCODE_F9", (void*)&SCANCODE_F9);
    engine->RegisterGlobalProperty("const int SCANCODE_F10", (void*)&SCANCODE_F10);
    engine->RegisterGlobalProperty("const int SCANCODE_F11", (void*)&SCANCODE_F11);
    engine->RegisterGlobalProperty("const int SCANCODE_F12", (void*)&SCANCODE_F12);
    engine->RegisterGlobalProperty("const int SCANCODE_PRINTSCREEN", (void*)&SCANCODE_PRINTSCREEN);
    engine->RegisterGlobalProperty("const int SCANCODE_SCROLLLOCK", (void*)&SCANCODE_SCROLLLOCK);
    engine->RegisterGlobalProperty("const int SCANCODE_PAUSE", (void*)&SCANCODE_PAUSE);
    engine->RegisterGlobalProperty("const int SCANCODE_INSERT", (void*)&SCANCODE_INSERT);
    engine->RegisterGlobalProperty("const int SCANCODE_HOME", (void*)&SCANCODE_HOME);
    engine->RegisterGlobalProperty("const int SCANCODE_PAGEUP", (void*)&SCANCODE_PAGEUP);
    engine->RegisterGlobalProperty("const int SCANCODE_DELETE", (void*)&SCANCODE_DELETE);
    engine->RegisterGlobalProperty("const int SCANCODE_END", (void*)&SCANCODE_END);
    engine->RegisterGlobalProperty("const int SCANCODE_PAGEDOWN", (void*)&SCANCODE_PAGEDOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_RIGHT", (void*)&SCANCODE_RIGHT);
    engine->RegisterGlobalProperty("const int SCANCODE_LEFT", (void*)&SCANCODE_LEFT);
    engine->RegisterGlobalProperty("const int SCANCODE_DOWN", (void*)&SCANCODE_DOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_UP", (void*)&SCANCODE_UP);
    engine->RegisterGlobalProperty("const int SCANCODE_NUMLOCKCLEAR", (void*)&SCANCODE_NUMLOCKCLEAR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_DIVIDE", (void*)&SCANCODE_KP_DIVIDE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MULTIPLY", (void*)&SCANCODE_KP_MULTIPLY);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MINUS", (void*)&SCANCODE_KP_MINUS);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_PLUS", (void*)&SCANCODE_KP_PLUS);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_ENTER", (void*)&SCANCODE_KP_ENTER);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_1", (void*)&SCANCODE_KP_1);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_2", (void*)&SCANCODE_KP_2);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_3", (void*)&SCANCODE_KP_3);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_4", (void*)&SCANCODE_KP_4);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_5", (void*)&SCANCODE_KP_5);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_6", (void*)&SCANCODE_KP_6);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_7", (void*)&SCANCODE_KP_7);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_8", (void*)&SCANCODE_KP_8);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_9", (void*)&SCANCODE_KP_9);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_0", (void*)&SCANCODE_KP_0);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_PERIOD", (void*)&SCANCODE_KP_PERIOD);
    engine->RegisterGlobalProperty("const int SCANCODE_NONUSBACKSLASH", (void*)&SCANCODE_NONUSBACKSLASH);
    engine->RegisterGlobalProperty("const int SCANCODE_APPLICATION", (void*)&SCANCODE_APPLICATION);
    engine->RegisterGlobalProperty("const int SCANCODE_POWER", (void*)&SCANCODE_POWER);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_EQUALS", (void*)&SCANCODE_KP_EQUALS);
    engine->RegisterGlobalProperty("const int SCANCODE_F13", (void*)&SCANCODE_F13);
    engine->RegisterGlobalProperty("const int SCANCODE_F14", (void*)&SCANCODE_F14);
    engine->RegisterGlobalProperty("const int SCANCODE_F15", (void*)&SCANCODE_F15);
    engine->RegisterGlobalProperty("const int SCANCODE_F16", (void*)&SCANCODE_F16);
    engine->RegisterGlobalProperty("const int SCANCODE_F17", (void*)&SCANCODE_F17);
    engine->RegisterGlobalProperty("const int SCANCODE_F18", (void*)&SCANCODE_F18);
    engine->RegisterGlobalProperty("const int SCANCODE_F19", (void*)&SCANCODE_F19);
    engine->RegisterGlobalProperty("const int SCANCODE_F20", (void*)&SCANCODE_F20);
    engine->RegisterGlobalProperty("const int SCANCODE_F21", (void*)&SCANCODE_F21);
    engine->RegisterGlobalProperty("const int SCANCODE_F22", (void*)&SCANCODE_F22);
    engine->RegisterGlobalProperty("const int SCANCODE_F23", (void*)&SCANCODE_F23);
    engine->RegisterGlobalProperty("const int SCANCODE_F24", (void*)&SCANCODE_F24);
    engine->RegisterGlobalProperty("const int SCANCODE_EXECUTE", (void*)&SCANCODE_EXECUTE);
    engine->RegisterGlobalProperty("const int SCANCODE_HELP", (void*)&SCANCODE_HELP);
    engine->RegisterGlobalProperty("const int SCANCODE_MENU", (void*)&SCANCODE_MENU);
    engine->RegisterGlobalProperty("const int SCANCODE_SELECT", (void*)&SCANCODE_SELECT);
    engine->RegisterGlobalProperty("const int SCANCODE_STOP", (void*)&SCANCODE_STOP);
    engine->RegisterGlobalProperty("const int SCANCODE_AGAIN", (void*)&SCANCODE_AGAIN);
    engine->RegisterGlobalProperty("const int SCANCODE_UNDO", (void*)&SCANCODE_UNDO);
    engine->RegisterGlobalProperty("const int SCANCODE_CUT", (void*)&SCANCODE_CUT);
    engine->RegisterGlobalProperty("const int SCANCODE_COPY", (void*)&SCANCODE_COPY);
    engine->RegisterGlobalProperty("const int SCANCODE_PASTE", (void*)&SCANCODE_PASTE);
    engine->RegisterGlobalProperty("const int SCANCODE_FIND", (void*)&SCANCODE_FIND);
    engine->RegisterGlobalProperty("const int SCANCODE_MUTE", (void*)&SCANCODE_MUTE);
    engine->RegisterGlobalProperty("const int SCANCODE_VOLUMEUP", (void*)&SCANCODE_VOLUMEUP);
    engine->RegisterGlobalProperty("const int SCANCODE_VOLUMEDOWN", (void*)&SCANCODE_VOLUMEDOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_COMMA", (void*)&SCANCODE_KP_COMMA);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_EQUALSAS400", (void*)&SCANCODE_KP_EQUALSAS400);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL1", (void*)&SCANCODE_INTERNATIONAL1);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL2", (void*)&SCANCODE_INTERNATIONAL2);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL3", (void*)&SCANCODE_INTERNATIONAL3);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL4", (void*)&SCANCODE_INTERNATIONAL4);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL5", (void*)&SCANCODE_INTERNATIONAL5);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL6", (void*)&SCANCODE_INTERNATIONAL6);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL7", (void*)&SCANCODE_INTERNATIONAL7);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL8", (void*)&SCANCODE_INTERNATIONAL8);
    engine->RegisterGlobalProperty("const int SCANCODE_INTERNATIONAL9", (void*)&SCANCODE_INTERNATIONAL9);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG1", (void*)&SCANCODE_LANG1);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG2", (void*)&SCANCODE_LANG2);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG3", (void*)&SCANCODE_LANG3);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG4", (void*)&SCANCODE_LANG4);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG5", (void*)&SCANCODE_LANG5);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG6", (void*)&SCANCODE_LANG6);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG7", (void*)&SCANCODE_LANG7);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG8", (void*)&SCANCODE_LANG8);
    engine->RegisterGlobalProperty("const int SCANCODE_LANG9", (void*)&SCANCODE_LANG9);
    engine->RegisterGlobalProperty("const int SCANCODE_ALTERASE", (void*)&SCANCODE_ALTERASE);
    engine->RegisterGlobalProperty("const int SCANCODE_SYSREQ", (void*)&SCANCODE_SYSREQ);
    engine->RegisterGlobalProperty("const int SCANCODE_CANCEL", (void*)&SCANCODE_CANCEL);
    engine->RegisterGlobalProperty("const int SCANCODE_CLEAR", (void*)&SCANCODE_CLEAR);
    engine->RegisterGlobalProperty("const int SCANCODE_PRIOR", (void*)&SCANCODE_PRIOR);
    engine->RegisterGlobalProperty("const int SCANCODE_RETURN2", (void*)&SCANCODE_RETURN2);
    engine->RegisterGlobalProperty("const int SCANCODE_SEPARATOR", (void*)&SCANCODE_SEPARATOR);
    engine->RegisterGlobalProperty("const int SCANCODE_OUT", (void*)&SCANCODE_OUT);
    engine->RegisterGlobalProperty("const int SCANCODE_OPER", (void*)&SCANCODE_OPER);
    engine->RegisterGlobalProperty("const int SCANCODE_CLEARAGAIN", (void*)&SCANCODE_CLEARAGAIN);
    engine->RegisterGlobalProperty("const int SCANCODE_CRSEL", (void*)&SCANCODE_CRSEL);
    engine->RegisterGlobalProperty("const int SCANCODE_EXSEL", (void*)&SCANCODE_EXSEL);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_00", (void*)&SCANCODE_KP_00);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_000", (void*)&SCANCODE_KP_000);
    engine->RegisterGlobalProperty("const int SCANCODE_THOUSANDSSEPARATOR", (void*)&SCANCODE_THOUSANDSSEPARATOR);
    engine->RegisterGlobalProperty("const int SCANCODE_DECIMALSEPARATOR", (void*)&SCANCODE_DECIMALSEPARATOR);
    engine->RegisterGlobalProperty("const int SCANCODE_CURRENCYUNIT", (void*)&SCANCODE_CURRENCYUNIT);
    engine->RegisterGlobalProperty("const int SCANCODE_CURRENCYSUBUNIT", (void*)&SCANCODE_CURRENCYSUBUNIT);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_LEFTPAREN", (void*)&SCANCODE_KP_LEFTPAREN);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_RIGHTPAREN", (void*)&SCANCODE_KP_RIGHTPAREN);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_LEFTBRACE", (void*)&SCANCODE_KP_LEFTBRACE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_RIGHTBRACE", (void*)&SCANCODE_KP_RIGHTBRACE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_TAB", (void*)&SCANCODE_KP_TAB);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_BACKSPACE", (void*)&SCANCODE_KP_BACKSPACE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_A", (void*)&SCANCODE_KP_A);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_B", (void*)&SCANCODE_KP_B);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_C", (void*)&SCANCODE_KP_C);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_D", (void*)&SCANCODE_KP_D);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_E", (void*)&SCANCODE_KP_E);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_F", (void*)&SCANCODE_KP_F);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_XOR", (void*)&SCANCODE_KP_XOR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_POWER", (void*)&SCANCODE_KP_POWER);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_PERCENT", (void*)&SCANCODE_KP_PERCENT);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_LESS", (void*)&SCANCODE_KP_LESS);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_GREATER", (void*)&SCANCODE_KP_GREATER);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_AMPERSAND", (void*)&SCANCODE_KP_AMPERSAND);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_DBLAMPERSAND", (void*)&SCANCODE_KP_DBLAMPERSAND);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_VERTICALBAR", (void*)&SCANCODE_KP_VERTICALBAR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_DBLVERTICALBAR", (void*)&SCANCODE_KP_DBLVERTICALBAR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_COLON", (void*)&SCANCODE_KP_COLON);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_HASH", (void*)&SCANCODE_KP_HASH);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_SPACE", (void*)&SCANCODE_KP_SPACE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_AT", (void*)&SCANCODE_KP_AT);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_EXCLAM", (void*)&SCANCODE_KP_EXCLAM);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMSTORE", (void*)&SCANCODE_KP_MEMSTORE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMRECALL", (void*)&SCANCODE_KP_MEMRECALL);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMCLEAR", (void*)&SCANCODE_KP_MEMCLEAR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMADD", (void*)&SCANCODE_KP_MEMADD);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMSUBTRACT", (void*)&SCANCODE_KP_MEMSUBTRACT);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMMULTIPLY", (void*)&SCANCODE_KP_MEMMULTIPLY);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_MEMDIVIDE", (void*)&SCANCODE_KP_MEMDIVIDE);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_PLUSMINUS", (void*)&SCANCODE_KP_PLUSMINUS);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_CLEAR", (void*)&SCANCODE_KP_CLEAR);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_CLEARENTRY", (void*)&SCANCODE_KP_CLEARENTRY);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_BINARY", (void*)&SCANCODE_KP_BINARY);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_OCTAL", (void*)&SCANCODE_KP_OCTAL);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_DECIMAL", (void*)&SCANCODE_KP_DECIMAL);
    engine->RegisterGlobalProperty("const int SCANCODE_KP_HEXADECIMAL", (void*)&SCANCODE_KP_HEXADECIMAL);
    engine->RegisterGlobalProperty("const int SCANCODE_LCTRL", (void*)&SCANCODE_LCTRL);
    engine->RegisterGlobalProperty("const int SCANCODE_LSHIFT", (void*)&SCANCODE_LSHIFT);
    engine->RegisterGlobalProperty("const int SCANCODE_LALT", (void*)&SCANCODE_LALT);
    engine->RegisterGlobalProperty("const int SCANCODE_LGUI", (void*)&SCANCODE_LGUI);
    engine->RegisterGlobalProperty("const int SCANCODE_RCTRL", (void*)&SCANCODE_RCTRL);
    engine->RegisterGlobalProperty("const int SCANCODE_RSHIFT", (void*)&SCANCODE_RSHIFT);
    engine->RegisterGlobalProperty("const int SCANCODE_RALT", (void*)&SCANCODE_RALT);
    engine->RegisterGlobalProperty("const int SCANCODE_RGUI", (void*)&SCANCODE_RGUI);
    engine->RegisterGlobalProperty("const int SCANCODE_MODE", (void*)&SCANCODE_MODE);
    engine->RegisterGlobalProperty("const int SCANCODE_AUDIONEXT", (void*)&SCANCODE_AUDIONEXT);
    engine->RegisterGlobalProperty("const int SCANCODE_AUDIOPREV", (void*)&SCANCODE_AUDIOPREV);
    engine->RegisterGlobalProperty("const int SCANCODE_AUDIOSTOP", (void*)&SCANCODE_AUDIOSTOP);
    engine->RegisterGlobalProperty("const int SCANCODE_AUDIOPLAY", (void*)&SCANCODE_AUDIOPLAY);
    engine->RegisterGlobalProperty("const int SCANCODE_AUDIOMUTE", (void*)&SCANCODE_AUDIOMUTE);
    engine->RegisterGlobalProperty("const int SCANCODE_MEDIASELECT", (void*)&SCANCODE_MEDIASELECT);
    engine->RegisterGlobalProperty("const int SCANCODE_WWW", (void*)&SCANCODE_WWW);
    engine->RegisterGlobalProperty("const int SCANCODE_MAIL", (void*)&SCANCODE_MAIL);
    engine->RegisterGlobalProperty("const int SCANCODE_CALCULATOR", (void*)&SCANCODE_CALCULATOR);
    engine->RegisterGlobalProperty("const int SCANCODE_COMPUTER", (void*)&SCANCODE_COMPUTER);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_SEARCH", (void*)&SCANCODE_AC_SEARCH);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_HOME", (void*)&SCANCODE_AC_HOME);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_BACK", (void*)&SCANCODE_AC_BACK);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_FORWARD", (void*)&SCANCODE_AC_FORWARD);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_STOP", (void*)&SCANCODE_AC_STOP);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_REFRESH", (void*)&SCANCODE_AC_REFRESH);
    engine->RegisterGlobalProperty("const int SCANCODE_AC_BOOKMARKS", (void*)&SCANCODE_AC_BOOKMARKS);
    engine->RegisterGlobalProperty("const int SCANCODE_BRIGHTNESSDOWN", (void*)&SCANCODE_BRIGHTNESSDOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_BRIGHTNESSUP", (void*)&SCANCODE_BRIGHTNESSUP);
    engine->RegisterGlobalProperty("const int SCANCODE_DISPLAYSWITCH", (void*)&SCANCODE_DISPLAYSWITCH);
    engine->RegisterGlobalProperty("const int SCANCODE_KBDILLUMTOGGLE", (void*)&SCANCODE_KBDILLUMTOGGLE);
    engine->RegisterGlobalProperty("const int SCANCODE_KBDILLUMDOWN", (void*)&SCANCODE_KBDILLUMDOWN);
    engine->RegisterGlobalProperty("const int SCANCODE_KBDILLUMUP", (void*)&SCANCODE_KBDILLUMUP);
    engine->RegisterGlobalProperty("const int SCANCODE_EJECT", (void*)&SCANCODE_EJECT);
    engine->RegisterGlobalProperty("const int SCANCODE_SLEEP", (void*)&SCANCODE_SLEEP);
    engine->RegisterGlobalProperty("const int SCANCODE_APP1", (void*)&SCANCODE_APP1);
    engine->RegisterGlobalProperty("const int SCANCODE_APP2", (void*)&SCANCODE_APP2);
    engine->RegisterGlobalProperty("const int HAT_CENTER", (void*)&HAT_CENTER);
    engine->RegisterGlobalProperty("const int HAT_UP", (void*)&HAT_UP);
    engine->RegisterGlobalProperty("const int HAT_RIGHT", (void*)&HAT_RIGHT);
    engine->RegisterGlobalProperty("const int HAT_DOWN", (void*)&HAT_DOWN);
    engine->RegisterGlobalProperty("const int HAT_LEFT", (void*)&HAT_LEFT);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_A", (void*)&CONTROLLER_BUTTON_A);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_B", (void*)&CONTROLLER_BUTTON_B);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_X", (void*)&CONTROLLER_BUTTON_X);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_Y", (void*)&CONTROLLER_BUTTON_Y);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_BACK", (void*)&CONTROLLER_BUTTON_BACK);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_GUIDE", (void*)&CONTROLLER_BUTTON_GUIDE);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_START", (void*)&CONTROLLER_BUTTON_START);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_LEFTSTICK", (void*)&CONTROLLER_BUTTON_LEFTSTICK);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_RIGHTSTICK", (void*)&CONTROLLER_BUTTON_RIGHTSTICK);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_LEFTSHOULDER", (void*)&CONTROLLER_BUTTON_LEFTSHOULDER);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_RIGHTSHOULDER", (void*)&CONTROLLER_BUTTON_RIGHTSHOULDER);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_DPAD_UP", (void*)&CONTROLLER_BUTTON_DPAD_UP);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_DPAD_DOWN", (void*)&CONTROLLER_BUTTON_DPAD_DOWN);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_DPAD_LEFT", (void*)&CONTROLLER_BUTTON_DPAD_LEFT);
    engine->RegisterGlobalProperty("const int CONTROLLER_BUTTON_DPAD_RIGHT", (void*)&CONTROLLER_BUTTON_DPAD_RIGHT);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_LEFTX", (void*)&CONTROLLER_AXIS_LEFTX);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_LEFTY", (void*)&CONTROLLER_AXIS_LEFTY);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_RIGHTX", (void*)&CONTROLLER_AXIS_RIGHTX);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_RIGHTY", (void*)&CONTROLLER_AXIS_RIGHTY);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_TRIGGERLEFT", (void*)&CONTROLLER_AXIS_TRIGGERLEFT);
    engine->RegisterGlobalProperty("const int CONTROLLER_AXIS_TRIGGERRIGHT", (void*)&CONTROLLER_AXIS_TRIGGERRIGHT);
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

static void RegisterInput(asIScriptEngine* engine)
{
    engine->RegisterEnum("MouseMode");
    engine->RegisterEnumValue("MouseMode", "MM_ABSOLUTE", MM_ABSOLUTE);
    engine->RegisterEnumValue("MouseMode", "MM_RELATIVE", MM_RELATIVE);
    engine->RegisterEnumValue("MouseMode", "MM_WRAP", MM_WRAP);
    engine->RegisterEnumValue("MouseMode", "MM_FREE", MM_FREE);

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
    engine->RegisterObjectMethod("Input", "void set_mouseGrabbed(bool)", asMETHOD(Input, SetMouseGrabbed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool get_mouseGrabbed() const", asMETHOD(Input, IsMouseGrabbed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void set_mouseMode(MouseMode) const", asMETHOD(Input, SetMouseMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "MouseMode get_mouseMode() const", asMETHOD(Input, GetMouseMode), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Input", "IntVector2 get_mousePosition() const", asMETHOD(Input, GetMousePosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "const IntVector2& get_mouseMove() const", asMETHOD(Input, GetMouseMove), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveX() const", asMETHOD(Input, GetMouseMoveX), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveY() const", asMETHOD(Input, GetMouseMoveY), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int get_mouseMoveWheel() const", asMETHOD(Input, GetMouseMoveWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numTouches() const", asMETHOD(Input, GetNumTouches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "TouchState@+ get_touches(uint) const", asMETHOD(Input, GetTouch), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "uint get_numJoysticks() const", asMETHOD(Input, GetNumJoysticks), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticks(int)", asMETHOD(Input, GetJoystick), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "JoystickState@+ get_joysticksByIndex(uint)", asMETHOD(Input, GetJoystickByIndex), asCALL_THISCALL);
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
