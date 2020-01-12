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
    engine->RegisterEnum("MouseButton");
    engine->RegisterEnumValue("MouseButton", "MOUSEB_LEFT", MOUSEB_LEFT);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_MIDDLE", MOUSEB_MIDDLE);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_RIGHT", MOUSEB_RIGHT);

    engine->RegisterEnum("Qualifier");
    engine->RegisterEnumValue("Qualifier", "QUAL_SHIFT", QUAL_SHIFT);
    engine->RegisterEnumValue("Qualifier", "QUAL_CTRL", QUAL_CTRL);
    engine->RegisterEnumValue("Qualifier", "QUAL_ALT", QUAL_ALT);
    engine->RegisterEnumValue("Qualifier", "QUAL_ANY", QUAL_ANY);

    engine->RegisterEnum("Key");
    engine->RegisterEnumValue("Key", "KEY_UNKNOWN", KEY_UNKNOWN);
    engine->RegisterEnumValue("Key", "KEY_A", KEY_A);
    engine->RegisterEnumValue("Key", "KEY_B", KEY_B);
    engine->RegisterEnumValue("Key", "KEY_C", KEY_C);
    engine->RegisterEnumValue("Key", "KEY_D", KEY_D);
    engine->RegisterEnumValue("Key", "KEY_E", KEY_E);
    engine->RegisterEnumValue("Key", "KEY_F", KEY_F);
    engine->RegisterEnumValue("Key", "KEY_G", KEY_G);
    engine->RegisterEnumValue("Key", "KEY_H", KEY_H);
    engine->RegisterEnumValue("Key", "KEY_I", KEY_I);
    engine->RegisterEnumValue("Key", "KEY_J", KEY_J);
    engine->RegisterEnumValue("Key", "KEY_K", KEY_K);
    engine->RegisterEnumValue("Key", "KEY_L", KEY_L);
    engine->RegisterEnumValue("Key", "KEY_M", KEY_M);
    engine->RegisterEnumValue("Key", "KEY_N", KEY_N);
    engine->RegisterEnumValue("Key", "KEY_O", KEY_O);
    engine->RegisterEnumValue("Key", "KEY_P", KEY_P);
    engine->RegisterEnumValue("Key", "KEY_Q", KEY_Q);
    engine->RegisterEnumValue("Key", "KEY_R", KEY_R);
    engine->RegisterEnumValue("Key", "KEY_S", KEY_S);
    engine->RegisterEnumValue("Key", "KEY_T", KEY_T);
    engine->RegisterEnumValue("Key", "KEY_U", KEY_U);
    engine->RegisterEnumValue("Key", "KEY_V", KEY_V);
    engine->RegisterEnumValue("Key", "KEY_W", KEY_W);
    engine->RegisterEnumValue("Key", "KEY_X", KEY_X);
    engine->RegisterEnumValue("Key", "KEY_Y", KEY_Y);
    engine->RegisterEnumValue("Key", "KEY_Z", KEY_Z);
    engine->RegisterEnumValue("Key", "KEY_0", KEY_0);
    engine->RegisterEnumValue("Key", "KEY_1", KEY_1);
    engine->RegisterEnumValue("Key", "KEY_2", KEY_2);
    engine->RegisterEnumValue("Key", "KEY_3", KEY_3);
    engine->RegisterEnumValue("Key", "KEY_4", KEY_4);
    engine->RegisterEnumValue("Key", "KEY_5", KEY_5);
    engine->RegisterEnumValue("Key", "KEY_6", KEY_6);
    engine->RegisterEnumValue("Key", "KEY_7", KEY_7);
    engine->RegisterEnumValue("Key", "KEY_8", KEY_8);
    engine->RegisterEnumValue("Key", "KEY_9", KEY_9);
    engine->RegisterEnumValue("Key", "KEY_BACKSPACE", KEY_BACKSPACE);
    engine->RegisterEnumValue("Key", "KEY_TAB", KEY_TAB);
    engine->RegisterEnumValue("Key", "KEY_RETURN", KEY_RETURN);
    engine->RegisterEnumValue("Key", "KEY_RETURN2", KEY_RETURN2);
    engine->RegisterEnumValue("Key", "KEY_KP_ENTER", KEY_KP_ENTER);
    engine->RegisterEnumValue("Key", "KEY_SHIFT", KEY_SHIFT);
    engine->RegisterEnumValue("Key", "KEY_CTRL", KEY_CTRL);
    engine->RegisterEnumValue("Key", "KEY_ALT", KEY_ALT);
    engine->RegisterEnumValue("Key", "KEY_GUI", KEY_GUI);
    engine->RegisterEnumValue("Key", "KEY_PAUSE", KEY_PAUSE);
    engine->RegisterEnumValue("Key", "KEY_CAPSLOCK", KEY_CAPSLOCK);
    engine->RegisterEnumValue("Key", "KEY_ESCAPE", KEY_ESCAPE);
    engine->RegisterEnumValue("Key", "KEY_SPACE", KEY_SPACE);
    engine->RegisterEnumValue("Key", "KEY_PAGEUP", KEY_PAGEUP);
    engine->RegisterEnumValue("Key", "KEY_PAGEDOWN", KEY_PAGEDOWN);
    engine->RegisterEnumValue("Key", "KEY_END", KEY_END);
    engine->RegisterEnumValue("Key", "KEY_HOME", KEY_HOME);
    engine->RegisterEnumValue("Key", "KEY_LEFT", KEY_LEFT);
    engine->RegisterEnumValue("Key", "KEY_UP", KEY_UP);
    engine->RegisterEnumValue("Key", "KEY_RIGHT", KEY_RIGHT);
    engine->RegisterEnumValue("Key", "KEY_DOWN", KEY_DOWN);
    engine->RegisterEnumValue("Key", "KEY_SELECT", KEY_SELECT);
    engine->RegisterEnumValue("Key", "KEY_PRINTSCREEN", KEY_PRINTSCREEN);
    engine->RegisterEnumValue("Key", "KEY_INSERT", KEY_INSERT);
    engine->RegisterEnumValue("Key", "KEY_DELETE", KEY_DELETE);
    engine->RegisterEnumValue("Key", "KEY_LGUI", KEY_LGUI);
    engine->RegisterEnumValue("Key", "KEY_RGUI", KEY_RGUI);
    engine->RegisterEnumValue("Key", "KEY_APPLICATION", KEY_APPLICATION);
    engine->RegisterEnumValue("Key", "KEY_KP_0", KEY_KP_0);
    engine->RegisterEnumValue("Key", "KEY_KP_1", KEY_KP_1);
    engine->RegisterEnumValue("Key", "KEY_KP_2", KEY_KP_2);
    engine->RegisterEnumValue("Key", "KEY_KP_3", KEY_KP_3);
    engine->RegisterEnumValue("Key", "KEY_KP_4", KEY_KP_4);
    engine->RegisterEnumValue("Key", "KEY_KP_5", KEY_KP_5);
    engine->RegisterEnumValue("Key", "KEY_KP_6", KEY_KP_6);
    engine->RegisterEnumValue("Key", "KEY_KP_7", KEY_KP_7);
    engine->RegisterEnumValue("Key", "KEY_KP_8", KEY_KP_8);
    engine->RegisterEnumValue("Key", "KEY_KP_9", KEY_KP_9);
    engine->RegisterEnumValue("Key", "KEY_KP_MULTIPLY", KEY_KP_MULTIPLY);
    engine->RegisterEnumValue("Key", "KEY_KP_PLUS", KEY_KP_PLUS);
    engine->RegisterEnumValue("Key", "KEY_KP_MINUS", KEY_KP_MINUS);
    engine->RegisterEnumValue("Key", "KEY_KP_PERIOD", KEY_KP_PERIOD);
    engine->RegisterEnumValue("Key", "KEY_KP_DIVIDE", KEY_KP_DIVIDE);
    engine->RegisterEnumValue("Key", "KEY_F1", KEY_F1);
    engine->RegisterEnumValue("Key", "KEY_F2", KEY_F2);
    engine->RegisterEnumValue("Key", "KEY_F3", KEY_F3);
    engine->RegisterEnumValue("Key", "KEY_F4", KEY_F4);
    engine->RegisterEnumValue("Key", "KEY_F5", KEY_F5);
    engine->RegisterEnumValue("Key", "KEY_F6", KEY_F6);
    engine->RegisterEnumValue("Key", "KEY_F7", KEY_F7);
    engine->RegisterEnumValue("Key", "KEY_F8", KEY_F8);
    engine->RegisterEnumValue("Key", "KEY_F9", KEY_F9);
    engine->RegisterEnumValue("Key", "KEY_F10", KEY_F10);
    engine->RegisterEnumValue("Key", "KEY_F11", KEY_F11);
    engine->RegisterEnumValue("Key", "KEY_F12", KEY_F12);
    engine->RegisterEnumValue("Key", "KEY_F13", KEY_F13);
    engine->RegisterEnumValue("Key", "KEY_F14", KEY_F14);
    engine->RegisterEnumValue("Key", "KEY_F15", KEY_F15);
    engine->RegisterEnumValue("Key", "KEY_F16", KEY_F16);
    engine->RegisterEnumValue("Key", "KEY_F17", KEY_F17);
    engine->RegisterEnumValue("Key", "KEY_F18", KEY_F18);
    engine->RegisterEnumValue("Key", "KEY_F19", KEY_F19);
    engine->RegisterEnumValue("Key", "KEY_F20", KEY_F20);
    engine->RegisterEnumValue("Key", "KEY_F21", KEY_F21);
    engine->RegisterEnumValue("Key", "KEY_F22", KEY_F22);
    engine->RegisterEnumValue("Key", "KEY_F23", KEY_F23);
    engine->RegisterEnumValue("Key", "KEY_F24", KEY_F24);
    engine->RegisterEnumValue("Key", "KEY_NUMLOCKCLEAR", KEY_NUMLOCKCLEAR);
    engine->RegisterEnumValue("Key", "KEY_SCROLLLOCK", KEY_SCROLLLOCK);
    engine->RegisterEnumValue("Key", "KEY_LSHIFT", KEY_LSHIFT);
    engine->RegisterEnumValue("Key", "KEY_RSHIFT", KEY_RSHIFT);
    engine->RegisterEnumValue("Key", "KEY_LCTRL", KEY_LCTRL);
    engine->RegisterEnumValue("Key", "KEY_RCTRL", KEY_RCTRL);
    engine->RegisterEnumValue("Key", "KEY_LALT", KEY_LALT);
    engine->RegisterEnumValue("Key", "KEY_RALT", KEY_RALT);
    engine->RegisterEnumValue("Key", "KEY_AC_BACK", KEY_AC_BACK);
    engine->RegisterEnumValue("Key", "KEY_AC_BOOKMARKS", KEY_AC_BOOKMARKS);
    engine->RegisterEnumValue("Key", "KEY_AC_FORWARD", KEY_AC_FORWARD);
    engine->RegisterEnumValue("Key", "KEY_AC_HOME", KEY_AC_HOME);
    engine->RegisterEnumValue("Key", "KEY_AC_REFRESH", KEY_AC_REFRESH);
    engine->RegisterEnumValue("Key", "KEY_AC_SEARCH", KEY_AC_SEARCH);
    engine->RegisterEnumValue("Key", "KEY_AC_STOP", KEY_AC_STOP);
    engine->RegisterEnumValue("Key", "KEY_AGAIN", KEY_AGAIN);
    engine->RegisterEnumValue("Key", "KEY_ALTERASE", KEY_ALTERASE);
    engine->RegisterEnumValue("Key", "KEY_AMPERSAND", KEY_AMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_ASTERISK", KEY_ASTERISK);
    engine->RegisterEnumValue("Key", "KEY_AT", KEY_AT);
    engine->RegisterEnumValue("Key", "KEY_AUDIOMUTE", KEY_AUDIOMUTE);
    engine->RegisterEnumValue("Key", "KEY_AUDIONEXT", KEY_AUDIONEXT);
    engine->RegisterEnumValue("Key", "KEY_AUDIOPLAY", KEY_AUDIOPLAY);
    engine->RegisterEnumValue("Key", "KEY_AUDIOPREV", KEY_AUDIOPREV);
    engine->RegisterEnumValue("Key", "KEY_AUDIOSTOP", KEY_AUDIOSTOP);
    engine->RegisterEnumValue("Key", "KEY_BACKQUOTE", KEY_BACKQUOTE);
    engine->RegisterEnumValue("Key", "KEY_BACKSLASH", KEY_BACKSLASH);
    engine->RegisterEnumValue("Key", "KEY_BRIGHTNESSDOWN", KEY_BRIGHTNESSDOWN);
    engine->RegisterEnumValue("Key", "KEY_BRIGHTNESSUP", KEY_BRIGHTNESSUP);
    engine->RegisterEnumValue("Key", "KEY_CALCULATOR", KEY_CALCULATOR);
    engine->RegisterEnumValue("Key", "KEY_CANCEL", KEY_CANCEL);
    engine->RegisterEnumValue("Key", "KEY_CARET", KEY_CARET);
    engine->RegisterEnumValue("Key", "KEY_CLEAR", KEY_CLEAR);
    engine->RegisterEnumValue("Key", "KEY_CLEARAGAIN", KEY_CLEARAGAIN);
    engine->RegisterEnumValue("Key", "KEY_COLON", KEY_COLON);
    engine->RegisterEnumValue("Key", "KEY_COMMA", KEY_COMMA);
    engine->RegisterEnumValue("Key", "KEY_COMPUTER", KEY_COMPUTER);
    engine->RegisterEnumValue("Key", "KEY_COPY", KEY_COPY);
    engine->RegisterEnumValue("Key", "KEY_CRSEL", KEY_CRSEL);
    engine->RegisterEnumValue("Key", "KEY_CURRENCYSUBUNIT", KEY_CURRENCYSUBUNIT);
    engine->RegisterEnumValue("Key", "KEY_CURRENCYUNIT", KEY_CURRENCYUNIT);
    engine->RegisterEnumValue("Key", "KEY_CUT", KEY_CUT);
    engine->RegisterEnumValue("Key", "KEY_DECIMALSEPARATOR", KEY_DECIMALSEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_DISPLAYSWITCH", KEY_DISPLAYSWITCH);
    engine->RegisterEnumValue("Key", "KEY_DOLLAR", KEY_DOLLAR);
    engine->RegisterEnumValue("Key", "KEY_EJECT", KEY_EJECT);
    engine->RegisterEnumValue("Key", "KEY_EQUALS", KEY_EQUALS);
    engine->RegisterEnumValue("Key", "KEY_EXCLAIM", KEY_EXCLAIM);
    engine->RegisterEnumValue("Key", "KEY_EXSEL", KEY_EXSEL);
    engine->RegisterEnumValue("Key", "KEY_FIND", KEY_FIND);
    engine->RegisterEnumValue("Key", "KEY_GREATER", KEY_GREATER);
    engine->RegisterEnumValue("Key", "KEY_HASH", KEY_HASH);
    engine->RegisterEnumValue("Key", "KEY_HELP", KEY_HELP);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMDOWN", KEY_KBDILLUMDOWN);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMTOGGLE", KEY_KBDILLUMTOGGLE);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMUP", KEY_KBDILLUMUP);
    engine->RegisterEnumValue("Key", "KEY_KP_00", KEY_KP_00);
    engine->RegisterEnumValue("Key", "KEY_KP_000", KEY_KP_000);
    engine->RegisterEnumValue("Key", "KEY_KP_A", KEY_KP_A);
    engine->RegisterEnumValue("Key", "KEY_KP_AMPERSAND", KEY_KP_AMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_KP_AT", KEY_KP_AT);
    engine->RegisterEnumValue("Key", "KEY_KP_B", KEY_KP_B);
    engine->RegisterEnumValue("Key", "KEY_KP_BACKSPACE", KEY_KP_BACKSPACE);
    engine->RegisterEnumValue("Key", "KEY_KP_BINARY", KEY_KP_BINARY);
    engine->RegisterEnumValue("Key", "KEY_KP_C", KEY_KP_C);
    engine->RegisterEnumValue("Key", "KEY_KP_CLEAR", KEY_KP_CLEAR);
    engine->RegisterEnumValue("Key", "KEY_KP_CLEARENTRY", KEY_KP_CLEARENTRY);
    engine->RegisterEnumValue("Key", "KEY_KP_COLON", KEY_KP_COLON);
    engine->RegisterEnumValue("Key", "KEY_KP_COMMA", KEY_KP_COMMA);
    engine->RegisterEnumValue("Key", "KEY_KP_D", KEY_KP_D);
    engine->RegisterEnumValue("Key", "KEY_KP_DBLAMPERSAND", KEY_KP_DBLAMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_KP_DBLVERTICALBAR", KEY_KP_DBLVERTICALBAR);
    engine->RegisterEnumValue("Key", "KEY_KP_DECIMAL", KEY_KP_DECIMAL);
    engine->RegisterEnumValue("Key", "KEY_KP_E", KEY_KP_E);
    engine->RegisterEnumValue("Key", "KEY_KP_EQUALS", KEY_KP_EQUALS);
    engine->RegisterEnumValue("Key", "KEY_KP_EQUALSAS400", KEY_KP_EQUALSAS400);
    engine->RegisterEnumValue("Key", "KEY_KP_EXCLAM", KEY_KP_EXCLAM);
    engine->RegisterEnumValue("Key", "KEY_KP_F", KEY_KP_F);
    engine->RegisterEnumValue("Key", "KEY_KP_GREATER", KEY_KP_GREATER);
    engine->RegisterEnumValue("Key", "KEY_KP_HASH", KEY_KP_HASH);
    engine->RegisterEnumValue("Key", "KEY_KP_HEXADECIMAL", KEY_KP_HEXADECIMAL);
    engine->RegisterEnumValue("Key", "KEY_KP_LEFTBRACE", KEY_KP_LEFTBRACE);
    engine->RegisterEnumValue("Key", "KEY_KP_LEFTPAREN", KEY_KP_LEFTPAREN);
    engine->RegisterEnumValue("Key", "KEY_KP_LESS", KEY_KP_LESS);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMADD", KEY_KP_MEMADD);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMCLEAR", KEY_KP_MEMCLEAR);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMDIVIDE", KEY_KP_MEMDIVIDE);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMMULTIPLY", KEY_KP_MEMMULTIPLY);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMRECALL", KEY_KP_MEMRECALL);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMSTORE", KEY_KP_MEMSTORE);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMSUBTRACT", KEY_KP_MEMSUBTRACT);
    engine->RegisterEnumValue("Key", "KEY_KP_OCTAL", KEY_KP_OCTAL);
    engine->RegisterEnumValue("Key", "KEY_KP_PERCENT", KEY_KP_PERCENT);
    engine->RegisterEnumValue("Key", "KEY_KP_PLUSMINUS", KEY_KP_PLUSMINUS);
    engine->RegisterEnumValue("Key", "KEY_KP_POWER", KEY_KP_POWER);
    engine->RegisterEnumValue("Key", "KEY_KP_RIGHTBRACE", KEY_KP_RIGHTBRACE);
    engine->RegisterEnumValue("Key", "KEY_KP_RIGHTPAREN", KEY_KP_RIGHTPAREN);
    engine->RegisterEnumValue("Key", "KEY_KP_SPACE", KEY_KP_SPACE);
    engine->RegisterEnumValue("Key", "KEY_KP_TAB", KEY_KP_TAB);
    engine->RegisterEnumValue("Key", "KEY_KP_VERTICALBAR", KEY_KP_VERTICALBAR);
    engine->RegisterEnumValue("Key", "KEY_KP_XOR", KEY_KP_XOR);
    engine->RegisterEnumValue("Key", "KEY_LEFTBRACKET", KEY_LEFTBRACKET);
    engine->RegisterEnumValue("Key", "KEY_LEFTPAREN", KEY_LEFTPAREN);
    engine->RegisterEnumValue("Key", "KEY_LESS", KEY_LESS);
    engine->RegisterEnumValue("Key", "KEY_MAIL", KEY_MAIL);
    engine->RegisterEnumValue("Key", "KEY_MEDIASELECT", KEY_MEDIASELECT);
    engine->RegisterEnumValue("Key", "KEY_MENU", KEY_MENU);
    engine->RegisterEnumValue("Key", "KEY_MINUS", KEY_MINUS);
    engine->RegisterEnumValue("Key", "KEY_MODE", KEY_MODE);
    engine->RegisterEnumValue("Key", "KEY_MUTE", KEY_MUTE);
    engine->RegisterEnumValue("Key", "KEY_OPER", KEY_OPER);
    engine->RegisterEnumValue("Key", "KEY_OUT", KEY_OUT);
    engine->RegisterEnumValue("Key", "KEY_PASTE", KEY_PASTE);
    engine->RegisterEnumValue("Key", "KEY_PERCENT", KEY_PERCENT);
    engine->RegisterEnumValue("Key", "KEY_PERIOD", KEY_PERIOD);
    engine->RegisterEnumValue("Key", "KEY_PLUS", KEY_PLUS);
    engine->RegisterEnumValue("Key", "KEY_POWER", KEY_POWER);
    engine->RegisterEnumValue("Key", "KEY_PRIOR", KEY_PRIOR);
    engine->RegisterEnumValue("Key", "KEY_QUESTION", KEY_QUESTION);
    engine->RegisterEnumValue("Key", "KEY_QUOTE", KEY_QUOTE);
    engine->RegisterEnumValue("Key", "KEY_QUOTEDBL", KEY_QUOTEDBL);
    engine->RegisterEnumValue("Key", "KEY_RIGHTBRACKET", KEY_RIGHTBRACKET);
    engine->RegisterEnumValue("Key", "KEY_RIGHTPAREN", KEY_RIGHTPAREN);
    engine->RegisterEnumValue("Key", "KEY_SEMICOLON", KEY_SEMICOLON);
    engine->RegisterEnumValue("Key", "KEY_SEPARATOR", KEY_SEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_SLASH", KEY_SLASH);
    engine->RegisterEnumValue("Key", "KEY_SLEEP", KEY_SLEEP);
    engine->RegisterEnumValue("Key", "KEY_STOP", KEY_STOP);
    engine->RegisterEnumValue("Key", "KEY_SYSREQ", KEY_SYSREQ);
    engine->RegisterEnumValue("Key", "KEY_THOUSANDSSEPARATOR", KEY_THOUSANDSSEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_UNDERSCORE", KEY_UNDERSCORE);
    engine->RegisterEnumValue("Key", "KEY_UNDO", KEY_UNDO);
    engine->RegisterEnumValue("Key", "KEY_VOLUMEDOWN", KEY_VOLUMEDOWN);
    engine->RegisterEnumValue("Key", "KEY_VOLUMEUP", KEY_VOLUMEUP);
    engine->RegisterEnumValue("Key", "KEY_WWW", KEY_WWW);

    engine->RegisterEnum("Scancode");
    engine->RegisterEnumValue("Scancode", "SCANCODE_UNKNOWN", SCANCODE_UNKNOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CTRL", SCANCODE_CTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SHIFT", SCANCODE_SHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ALT", SCANCODE_ALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_GUI", SCANCODE_GUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_A", SCANCODE_A);
    engine->RegisterEnumValue("Scancode", "SCANCODE_B", SCANCODE_B);
    engine->RegisterEnumValue("Scancode", "SCANCODE_C", SCANCODE_C);
    engine->RegisterEnumValue("Scancode", "SCANCODE_D", SCANCODE_D);
    engine->RegisterEnumValue("Scancode", "SCANCODE_E", SCANCODE_E);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F", SCANCODE_F);
    engine->RegisterEnumValue("Scancode", "SCANCODE_G", SCANCODE_G);
    engine->RegisterEnumValue("Scancode", "SCANCODE_H", SCANCODE_H);
    engine->RegisterEnumValue("Scancode", "SCANCODE_I", SCANCODE_I);
    engine->RegisterEnumValue("Scancode", "SCANCODE_J", SCANCODE_J);
    engine->RegisterEnumValue("Scancode", "SCANCODE_K", SCANCODE_K);
    engine->RegisterEnumValue("Scancode", "SCANCODE_L", SCANCODE_L);
    engine->RegisterEnumValue("Scancode", "SCANCODE_M", SCANCODE_M);
    engine->RegisterEnumValue("Scancode", "SCANCODE_N", SCANCODE_N);
    engine->RegisterEnumValue("Scancode", "SCANCODE_O", SCANCODE_O);
    engine->RegisterEnumValue("Scancode", "SCANCODE_P", SCANCODE_P);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Q", SCANCODE_Q);
    engine->RegisterEnumValue("Scancode", "SCANCODE_R", SCANCODE_R);
    engine->RegisterEnumValue("Scancode", "SCANCODE_S", SCANCODE_S);
    engine->RegisterEnumValue("Scancode", "SCANCODE_T", SCANCODE_T);
    engine->RegisterEnumValue("Scancode", "SCANCODE_U", SCANCODE_U);
    engine->RegisterEnumValue("Scancode", "SCANCODE_V", SCANCODE_V);
    engine->RegisterEnumValue("Scancode", "SCANCODE_W", SCANCODE_W);
    engine->RegisterEnumValue("Scancode", "SCANCODE_X", SCANCODE_X);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Y", SCANCODE_Y);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Z", SCANCODE_Z);
    engine->RegisterEnumValue("Scancode", "SCANCODE_1", SCANCODE_1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_2", SCANCODE_2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_3", SCANCODE_3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_4", SCANCODE_4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_5", SCANCODE_5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_6", SCANCODE_6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_7", SCANCODE_7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_8", SCANCODE_8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_9", SCANCODE_9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_0", SCANCODE_0);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RETURN", SCANCODE_RETURN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ESCAPE", SCANCODE_ESCAPE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BACKSPACE", SCANCODE_BACKSPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_TAB", SCANCODE_TAB);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SPACE", SCANCODE_SPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MINUS", SCANCODE_MINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EQUALS", SCANCODE_EQUALS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LEFTBRACKET", SCANCODE_LEFTBRACKET);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RIGHTBRACKET", SCANCODE_RIGHTBRACKET);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BACKSLASH", SCANCODE_BACKSLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NONUSHASH", SCANCODE_NONUSHASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SEMICOLON", SCANCODE_SEMICOLON);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APOSTROPHE", SCANCODE_APOSTROPHE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_GRAVE", SCANCODE_GRAVE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COMMA", SCANCODE_COMMA);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PERIOD", SCANCODE_PERIOD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SLASH", SCANCODE_SLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CAPSLOCK", SCANCODE_CAPSLOCK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F1", SCANCODE_F1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F2", SCANCODE_F2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F3", SCANCODE_F3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F4", SCANCODE_F4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F5", SCANCODE_F5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F6", SCANCODE_F6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F7", SCANCODE_F7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F8", SCANCODE_F8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F9", SCANCODE_F9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F10", SCANCODE_F10);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F11", SCANCODE_F11);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F12", SCANCODE_F12);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PRINTSCREEN", SCANCODE_PRINTSCREEN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SCROLLLOCK", SCANCODE_SCROLLLOCK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAUSE", SCANCODE_PAUSE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INSERT", SCANCODE_INSERT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_HOME", SCANCODE_HOME);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAGEUP", SCANCODE_PAGEUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DELETE", SCANCODE_DELETE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_END", SCANCODE_END);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAGEDOWN", SCANCODE_PAGEDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RIGHT", SCANCODE_RIGHT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LEFT", SCANCODE_LEFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DOWN", SCANCODE_DOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_UP", SCANCODE_UP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NUMLOCKCLEAR", SCANCODE_NUMLOCKCLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DIVIDE", SCANCODE_KP_DIVIDE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MULTIPLY", SCANCODE_KP_MULTIPLY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MINUS", SCANCODE_KP_MINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PLUS", SCANCODE_KP_PLUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_ENTER", SCANCODE_KP_ENTER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_1", SCANCODE_KP_1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_2", SCANCODE_KP_2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_3", SCANCODE_KP_3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_4", SCANCODE_KP_4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_5", SCANCODE_KP_5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_6", SCANCODE_KP_6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_7", SCANCODE_KP_7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_8", SCANCODE_KP_8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_9", SCANCODE_KP_9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_0", SCANCODE_KP_0);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PERIOD", SCANCODE_KP_PERIOD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NONUSBACKSLASH", SCANCODE_NONUSBACKSLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APPLICATION", SCANCODE_APPLICATION);
    engine->RegisterEnumValue("Scancode", "SCANCODE_POWER", SCANCODE_POWER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EQUALS", SCANCODE_KP_EQUALS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F13", SCANCODE_F13);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F14", SCANCODE_F14);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F15", SCANCODE_F15);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F16", SCANCODE_F16);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F17", SCANCODE_F17);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F18", SCANCODE_F18);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F19", SCANCODE_F19);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F20", SCANCODE_F20);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F21", SCANCODE_F21);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F22", SCANCODE_F22);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F23", SCANCODE_F23);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F24", SCANCODE_F24);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EXECUTE", SCANCODE_EXECUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_HELP", SCANCODE_HELP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MENU", SCANCODE_MENU);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SELECT", SCANCODE_SELECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_STOP", SCANCODE_STOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AGAIN", SCANCODE_AGAIN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_UNDO", SCANCODE_UNDO);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CUT", SCANCODE_CUT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COPY", SCANCODE_COPY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PASTE", SCANCODE_PASTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_FIND", SCANCODE_FIND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MUTE", SCANCODE_MUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_VOLUMEUP", SCANCODE_VOLUMEUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_VOLUMEDOWN", SCANCODE_VOLUMEDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_COMMA", SCANCODE_KP_COMMA);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EQUALSAS400", SCANCODE_KP_EQUALSAS400);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL1", SCANCODE_INTERNATIONAL1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL2", SCANCODE_INTERNATIONAL2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL3", SCANCODE_INTERNATIONAL3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL4", SCANCODE_INTERNATIONAL4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL5", SCANCODE_INTERNATIONAL5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL6", SCANCODE_INTERNATIONAL6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL7", SCANCODE_INTERNATIONAL7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL8", SCANCODE_INTERNATIONAL8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL9", SCANCODE_INTERNATIONAL9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG1", SCANCODE_LANG1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG2", SCANCODE_LANG2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG3", SCANCODE_LANG3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG4", SCANCODE_LANG4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG5", SCANCODE_LANG5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG6", SCANCODE_LANG6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG7", SCANCODE_LANG7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG8", SCANCODE_LANG8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG9", SCANCODE_LANG9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ALTERASE", SCANCODE_ALTERASE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SYSREQ", SCANCODE_SYSREQ);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CANCEL", SCANCODE_CANCEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CLEAR", SCANCODE_CLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PRIOR", SCANCODE_PRIOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RETURN2", SCANCODE_RETURN2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SEPARATOR", SCANCODE_SEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_OUT", SCANCODE_OUT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_OPER", SCANCODE_OPER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CLEARAGAIN", SCANCODE_CLEARAGAIN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CRSEL", SCANCODE_CRSEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EXSEL", SCANCODE_EXSEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_00", SCANCODE_KP_00);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_000", SCANCODE_KP_000);
    engine->RegisterEnumValue("Scancode", "SCANCODE_THOUSANDSSEPARATOR", SCANCODE_THOUSANDSSEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DECIMALSEPARATOR", SCANCODE_DECIMALSEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CURRENCYUNIT", SCANCODE_CURRENCYUNIT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CURRENCYSUBUNIT", SCANCODE_CURRENCYSUBUNIT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LEFTPAREN", SCANCODE_KP_LEFTPAREN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_RIGHTPAREN", SCANCODE_KP_RIGHTPAREN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LEFTBRACE", SCANCODE_KP_LEFTBRACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_RIGHTBRACE", SCANCODE_KP_RIGHTBRACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_TAB", SCANCODE_KP_TAB);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_BACKSPACE", SCANCODE_KP_BACKSPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_A", SCANCODE_KP_A);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_B", SCANCODE_KP_B);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_C", SCANCODE_KP_C);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_D", SCANCODE_KP_D);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_E", SCANCODE_KP_E);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_F", SCANCODE_KP_F);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_XOR", SCANCODE_KP_XOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_POWER", SCANCODE_KP_POWER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PERCENT", SCANCODE_KP_PERCENT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LESS", SCANCODE_KP_LESS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_GREATER", SCANCODE_KP_GREATER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_AMPERSAND", SCANCODE_KP_AMPERSAND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DBLAMPERSAND", SCANCODE_KP_DBLAMPERSAND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_VERTICALBAR", SCANCODE_KP_VERTICALBAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DBLVERTICALBAR", SCANCODE_KP_DBLVERTICALBAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_COLON", SCANCODE_KP_COLON);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_HASH", SCANCODE_KP_HASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_SPACE", SCANCODE_KP_SPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_AT", SCANCODE_KP_AT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EXCLAM", SCANCODE_KP_EXCLAM);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMSTORE", SCANCODE_KP_MEMSTORE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMRECALL", SCANCODE_KP_MEMRECALL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMCLEAR", SCANCODE_KP_MEMCLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMADD", SCANCODE_KP_MEMADD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMSUBTRACT", SCANCODE_KP_MEMSUBTRACT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMMULTIPLY", SCANCODE_KP_MEMMULTIPLY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMDIVIDE", SCANCODE_KP_MEMDIVIDE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PLUSMINUS", SCANCODE_KP_PLUSMINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_CLEAR", SCANCODE_KP_CLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_CLEARENTRY", SCANCODE_KP_CLEARENTRY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_BINARY", SCANCODE_KP_BINARY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_OCTAL", SCANCODE_KP_OCTAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DECIMAL", SCANCODE_KP_DECIMAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_HEXADECIMAL", SCANCODE_KP_HEXADECIMAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LCTRL", SCANCODE_LCTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LSHIFT", SCANCODE_LSHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LALT", SCANCODE_LALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LGUI", SCANCODE_LGUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RCTRL", SCANCODE_RCTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RSHIFT", SCANCODE_RSHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RALT", SCANCODE_RALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RGUI", SCANCODE_RGUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MODE", SCANCODE_MODE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIONEXT", SCANCODE_AUDIONEXT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOPREV", SCANCODE_AUDIOPREV);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOSTOP", SCANCODE_AUDIOSTOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOPLAY", SCANCODE_AUDIOPLAY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOMUTE", SCANCODE_AUDIOMUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MEDIASELECT", SCANCODE_MEDIASELECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_WWW", SCANCODE_WWW);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MAIL", SCANCODE_MAIL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CALCULATOR", SCANCODE_CALCULATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COMPUTER", SCANCODE_COMPUTER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_SEARCH", SCANCODE_AC_SEARCH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_HOME", SCANCODE_AC_HOME);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_BACK", SCANCODE_AC_BACK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_FORWARD", SCANCODE_AC_FORWARD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_STOP", SCANCODE_AC_STOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_REFRESH", SCANCODE_AC_REFRESH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_BOOKMARKS", SCANCODE_AC_BOOKMARKS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BRIGHTNESSDOWN", SCANCODE_BRIGHTNESSDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BRIGHTNESSUP", SCANCODE_BRIGHTNESSUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DISPLAYSWITCH", SCANCODE_DISPLAYSWITCH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMTOGGLE", SCANCODE_KBDILLUMTOGGLE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMDOWN", SCANCODE_KBDILLUMDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMUP", SCANCODE_KBDILLUMUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EJECT", SCANCODE_EJECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SLEEP", SCANCODE_SLEEP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APP1", SCANCODE_APP1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APP2", SCANCODE_APP2);

    engine->RegisterEnum("HatPosition");
    engine->RegisterEnumValue("HatPosition", "HAT_CENTER", HAT_CENTER);
    engine->RegisterEnumValue("HatPosition", "HAT_UP", HAT_UP);
    engine->RegisterEnumValue("HatPosition", "HAT_RIGHT", HAT_RIGHT);
    engine->RegisterEnumValue("HatPosition", "HAT_DOWN", HAT_DOWN);
    engine->RegisterEnumValue("HatPosition", "HAT_LEFT", HAT_LEFT);

    engine->RegisterEnum("ControllerButton");
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_A", CONTROLLER_BUTTON_A);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_B", CONTROLLER_BUTTON_B);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_X", CONTROLLER_BUTTON_X);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_Y", CONTROLLER_BUTTON_Y);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_BACK", CONTROLLER_BUTTON_BACK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_GUIDE", CONTROLLER_BUTTON_GUIDE);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_START", CONTROLLER_BUTTON_START);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_LEFTSTICK", CONTROLLER_BUTTON_LEFTSTICK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_RIGHTSTICK", CONTROLLER_BUTTON_RIGHTSTICK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_LEFTSHOULDER", CONTROLLER_BUTTON_LEFTSHOULDER);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_RIGHTSHOULDER", CONTROLLER_BUTTON_RIGHTSHOULDER);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_UP", CONTROLLER_BUTTON_DPAD_UP);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_DOWN", CONTROLLER_BUTTON_DPAD_DOWN);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_LEFT", CONTROLLER_BUTTON_DPAD_LEFT);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_RIGHT", CONTROLLER_BUTTON_DPAD_RIGHT);

    engine->RegisterEnum("ControllerAxis");
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_LEFTX", CONTROLLER_AXIS_LEFTX);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_LEFTY", CONTROLLER_AXIS_LEFTY);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_RIGHTX", CONTROLLER_AXIS_RIGHTX);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_RIGHTY", CONTROLLER_AXIS_RIGHTY);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_TRIGGERLEFT", CONTROLLER_AXIS_TRIGGERLEFT);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_TRIGGERRIGHT", CONTROLLER_AXIS_TRIGGERRIGHT);
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
