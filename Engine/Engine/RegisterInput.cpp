//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "Controls.h"
#include "Engine.h"
#include "Input.h"

#include <angelscript.h>

static void registerKeyCodes(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const int MOUSEB_LEFT", (void*)&MOUSEB_LEFT);
    engine->RegisterGlobalProperty("const int MOUSEB_RIGHT", (void*)&MOUSEB_RIGHT);
    engine->RegisterGlobalProperty("const int MOUSEB_MIDDLE", (void*)&MOUSEB_MIDDLE);
    engine->RegisterGlobalProperty("const int KEY_BACK", (void*)&KEY_BACK);
    engine->RegisterGlobalProperty("const int KEY_TAB", (void*)&KEY_TAB);
    engine->RegisterGlobalProperty("const int KEY_CLEAR", (void*)&KEY_CLEAR);
    engine->RegisterGlobalProperty("const int KEY_RETURN", (void*)&KEY_RETURN);
    engine->RegisterGlobalProperty("const int KEY_SHIFT", (void*)&KEY_SHIFT);
    engine->RegisterGlobalProperty("const int KEY_CONTROL", (void*)&KEY_CONTROL);
    engine->RegisterGlobalProperty("const int KEY_MENU", (void*)&KEY_MENU);
    engine->RegisterGlobalProperty("const int KEY_PAUSE", (void*)&KEY_PAUSE);
    engine->RegisterGlobalProperty("const int KEY_CAPITAL", (void*)&KEY_CAPITAL);
    engine->RegisterGlobalProperty("const int KEY_ESCAPE", (void*)&KEY_ESCAPE);
    engine->RegisterGlobalProperty("const int KEY_CONVERT", (void*)&KEY_CONVERT);
    engine->RegisterGlobalProperty("const int KEY_NONCONVERT", (void*)&KEY_NONCONVERT);
    engine->RegisterGlobalProperty("const int KEY_ACCEPT", (void*)&KEY_ACCEPT);
    engine->RegisterGlobalProperty("const int KEY_MODECHANGE", (void*)&KEY_MODECHANGE);
    engine->RegisterGlobalProperty("const int KEY_SPACE", (void*)&KEY_SPACE);
    engine->RegisterGlobalProperty("const int KEY_PRIOR", (void*)&KEY_PRIOR);
    engine->RegisterGlobalProperty("const int KEY_NEXT", (void*)&KEY_NEXT);
    engine->RegisterGlobalProperty("const int KEY_END", (void*)&KEY_END);
    engine->RegisterGlobalProperty("const int KEY_HOME", (void*)&KEY_HOME);
    engine->RegisterGlobalProperty("const int KEY_LEFT", (void*)&KEY_LEFT);
    engine->RegisterGlobalProperty("const int KEY_UP", (void*)&KEY_UP);
    engine->RegisterGlobalProperty("const int KEY_RIGHT", (void*)&KEY_RIGHT);
    engine->RegisterGlobalProperty("const int KEY_DOWN", (void*)&KEY_DOWN);
    engine->RegisterGlobalProperty("const int KEY_SELECT", (void*)&KEY_SELECT);
    engine->RegisterGlobalProperty("const int KEY_PRINT", (void*)&KEY_PRINT);
    engine->RegisterGlobalProperty("const int KEY_EXECUTE", (void*)&KEY_EXECUTE);
    engine->RegisterGlobalProperty("const int KEY_SNAPSHOT", (void*)&KEY_SNAPSHOT);
    engine->RegisterGlobalProperty("const int KEY_INSERT", (void*)&KEY_INSERT);
    engine->RegisterGlobalProperty("const int KEY_DELETE", (void*)&KEY_DELETE);
    engine->RegisterGlobalProperty("const int KEY_HELP", (void*)&KEY_HELP);
    engine->RegisterGlobalProperty("const int KEY_LWIN", (void*)&KEY_LWIN);
    engine->RegisterGlobalProperty("const int KEY_RWIN", (void*)&KEY_RWIN);
    engine->RegisterGlobalProperty("const int KEY_APPS", (void*)&KEY_APPS);
    engine->RegisterGlobalProperty("const int KEY_SLEEP", (void*)&KEY_SLEEP);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD0", (void*)&KEY_NUMPAD0);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD1", (void*)&KEY_NUMPAD1);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD2", (void*)&KEY_NUMPAD2);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD3", (void*)&KEY_NUMPAD3);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD4", (void*)&KEY_NUMPAD4);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD5", (void*)&KEY_NUMPAD5);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD6", (void*)&KEY_NUMPAD6);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD7", (void*)&KEY_NUMPAD7);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD8", (void*)&KEY_NUMPAD8);
    engine->RegisterGlobalProperty("const int KEY_NUMPAD9", (void*)&KEY_NUMPAD9);
    engine->RegisterGlobalProperty("const int KEY_MULTIPLY", (void*)&KEY_MULTIPLY);
    engine->RegisterGlobalProperty("const int KEY_ADD", (void*)&KEY_ADD);
    engine->RegisterGlobalProperty("const int KEY_SEPARATOR", (void*)&KEY_SEPARATOR);
    engine->RegisterGlobalProperty("const int KEY_SUBTRACT", (void*)&KEY_SUBTRACT);
    engine->RegisterGlobalProperty("const int KEY_DECIMAL", (void*)&KEY_DECIMAL);
    engine->RegisterGlobalProperty("const int KEY_DIVIDE", (void*)&KEY_DIVIDE);
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
    engine->RegisterGlobalProperty("const int KEY_NUMLOCK", (void*)&KEY_NUMLOCK);
    engine->RegisterGlobalProperty("const int KEY_SCROLL", (void*)&KEY_SCROLL);
    engine->RegisterGlobalProperty("const int KEY_LSHIFT", (void*)&KEY_LSHIFT);
    engine->RegisterGlobalProperty("const int KEY_RSHIFT", (void*)&KEY_RSHIFT);
    engine->RegisterGlobalProperty("const int KEY_LCONTROL", (void*)&KEY_LCONTROL);
    engine->RegisterGlobalProperty("const int KEY_RCONTROL", (void*)&KEY_RCONTROL);
    engine->RegisterGlobalProperty("const int KEY_LMENU", (void*)&KEY_LMENU);
    engine->RegisterGlobalProperty("const int KEY_RMENU", (void*)&KEY_RMENU);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_BACK", (void*)&KEY_BROWSER_BACK);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_FORWARD", (void*)&KEY_BROWSER_FORWARD);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_REFRESH", (void*)&KEY_BROWSER_REFRESH);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_STOP", (void*)&KEY_BROWSER_STOP);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_SEARCH", (void*)&KEY_BROWSER_SEARCH);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_FAVORITES", (void*)&KEY_BROWSER_FAVORITES);
    engine->RegisterGlobalProperty("const int KEY_BROWSER_HOME", (void*)&KEY_BROWSER_HOME);
    engine->RegisterGlobalProperty("const int KEY_VOLUME_MUTE", (void*)&KEY_VOLUME_MUTE);
    engine->RegisterGlobalProperty("const int KEY_VOLUME_DOWN", (void*)&KEY_VOLUME_DOWN);
    engine->RegisterGlobalProperty("const int KEY_VOLUME_UP", (void*)&KEY_VOLUME_UP);
    engine->RegisterGlobalProperty("const int KEY_MEDIA_NEXT_TRACK", (void*)&KEY_MEDIA_NEXT_TRACK);
    engine->RegisterGlobalProperty("const int KEY_MEDIA_PREV_TRACK", (void*)&KEY_MEDIA_PREV_TRACK);
    engine->RegisterGlobalProperty("const int KEY_MEDIA_STOP", (void*)&KEY_MEDIA_STOP);
    engine->RegisterGlobalProperty("const int KEY_MEDIA_PLAY_PAUSE", (void*)&KEY_MEDIA_PLAY_PAUSE);
    engine->RegisterGlobalProperty("const int KEY_LAUNCH_MAIL", (void*)&KEY_LAUNCH_MAIL);
    engine->RegisterGlobalProperty("const int KEY_LAUNCH_MEDIA_SELECT", (void*)&KEY_LAUNCH_MEDIA_SELECT);
    engine->RegisterGlobalProperty("const int KEY_LAUNCH_APP1", (void*)&KEY_LAUNCH_APP1);
    engine->RegisterGlobalProperty("const int KEY_LAUNCH_APP2", (void*)&KEY_LAUNCH_APP2);
    engine->RegisterGlobalProperty("const int KEY_OEM_1", (void*)&KEY_OEM_1);
    engine->RegisterGlobalProperty("const int KEY_OEM_PLUS", (void*)&KEY_OEM_PLUS);
    engine->RegisterGlobalProperty("const int KEY_OEM_COMMA", (void*)&KEY_OEM_COMMA);
    engine->RegisterGlobalProperty("const int KEY_OEM_MINUS", (void*)&KEY_OEM_MINUS);
    engine->RegisterGlobalProperty("const int KEY_OEM_PERIOD", (void*)&KEY_OEM_PERIOD);
    engine->RegisterGlobalProperty("const int KEY_OEM_2", (void*)&KEY_OEM_2);
    engine->RegisterGlobalProperty("const int KEY_OEM_3", (void*)&KEY_OEM_3);
    engine->RegisterGlobalProperty("const int KEY_OEM_4", (void*)&KEY_OEM_4);
    engine->RegisterGlobalProperty("const int KEY_OEM_5", (void*)&KEY_OEM_5);
    engine->RegisterGlobalProperty("const int KEY_OEM_6", (void*)&KEY_OEM_6);
    engine->RegisterGlobalProperty("const int KEY_OEM_7", (void*)&KEY_OEM_7);
    engine->RegisterGlobalProperty("const int KEY_OEM_8", (void*)&KEY_OEM_8);
}

static void ConstructControls(Controls* ptr)
{
    new(ptr) Controls();
}

static void ConstructControlsCopy(const Controls& controls, Controls* ptr)
{
    new(ptr) Controls(controls);
}

static void DestructControls(Controls* ptr)
{
    ptr->~Controls();
}

static void registerControls(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Controls", sizeof(Controls), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_CONSTRUCT, "void f(const Controls& in)", asFUNCTION(ConstructControlsCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Controls", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructControls), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Controls", "Controls &opAssign(const Controls& in)", asMETHOD(Controls, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void write(Serializer&)", asMETHOD(Controls, write), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void read(Deserializer&)", asMETHOD(Controls, read), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void writeXML(XMLElement&)", asMETHOD(Controls, writeXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void readXML(const XMLElement&)", asMETHOD(Controls, readXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void reset()", asMETHOD(Controls, reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "void set(uint, bool)", asMETHOD(Controls, set), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool isDown(uint)", asMETHOD(Controls, isDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Controls", "bool isPressed(uint, const Controls& in)", asMETHOD(Controls, isPressed), asCALL_THISCALL);
    engine->RegisterObjectProperty("Controls", "uint buttons", offsetof(Controls, mButtons));
    engine->RegisterObjectProperty("Controls", "float yaw", offsetof(Controls, mYaw));
    engine->RegisterObjectProperty("Controls", "float pitch", offsetof(Controls, mPitch));
    engine->RegisterObjectProperty("Controls", "VariantMap extraData", offsetof(Controls, mExtraData));
}

static Input* GetInput()
{
    return getEngine()->getInput();
}

static void registerInput(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Input", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Input", asBEHAVE_ADDREF, "void f()", asMETHOD(Input, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Input", asBEHAVE_RELEASE, "void f()", asMETHOD(Input, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "void setToggleFullscreen(bool)", asMETHOD(Input, setToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool getKeyDown(int) const", asMETHOD(Input, getKeyDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool getKeyPress(int) const", asMETHOD(Input, getKeyPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool getMouseButtonDown(int) const", asMETHOD(Input, getMouseButtonDown), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool getMouseButtonPress(int) const", asMETHOD(Input, getMouseButtonPress), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int getMouseMoveX() const", asMETHOD(Input, getMouseMoveX), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int getMouseMoveY() const", asMETHOD(Input, getMouseMoveY), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "int getMouseMoveWheel() const", asMETHOD(Input, getMouseMoveWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool getToggleFullscreen() const", asMETHOD(Input, getToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool isActive() const", asMETHOD(Input, isActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("Input", "bool isMinimized() const", asMETHOD(Input, isMinimized), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Input@+ getInput()", asFUNCTION(GetInput), asCALL_CDECL);
    engine->RegisterGlobalFunction("Input@+ get_input()", asFUNCTION(GetInput), asCALL_CDECL);
}

void registerInputLibrary(asIScriptEngine* engine)
{
    registerKeyCodes(engine);
    registerControls(engine);
    registerInput(engine);
}
