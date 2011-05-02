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
#include "APITemplates.h"
#include "Console.h"
#include "DebugHud.h"
#include "Engine.h"

static Console* GetConsole()
{
    return GetScriptContext()->GetSubsystem<Console>();
}

static void RegisterConsole(asIScriptEngine* engine)
{
    RegisterObject<Console>(engine, "Console");
    engine->RegisterObjectMethod("Console", "void Toggle()", asMETHOD(Console, Toggle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void UpdateElements()", asMETHOD(Console, UpdateElements), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_style(XMLFile@+)", asMETHOD(Console, SetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "XMLFile@+ get_style() const", asMETHOD(Console, GetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_visible(bool)", asMETHOD(Console, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "bool get_visible() const", asMETHOD(Console, IsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numRows(uint)", asMETHOD(Console, SetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numRows() const", asMETHOD(Console, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "void set_numHistoryRows(uint)", asMETHOD(Console, SetNumHistoryRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_numHistoryRows() const", asMETHOD(Console, GetNumHistoryRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "uint get_historyPosition() const", asMETHOD(Console, GetHistoryPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "const String& get_historyRow(uint) const", asMETHOD(Console, GetHistoryRow), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "BorderImage@+ get_background() const", asMETHOD(Console, GetBackground), asCALL_THISCALL);
    engine->RegisterObjectMethod("Console", "LineEdit@+ get_lineEdit() const", asMETHOD(Console, GetLineEdit), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Console@+ get_console()", asFUNCTION(GetConsole), asCALL_CDECL);
}

static DebugHud* GetDebugHud()
{
    return GetScriptContext()->GetSubsystem<DebugHud>();
}

static void RegisterDebugHud(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_NONE", (void*)&DEBUGHUD_SHOW_NONE);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_STATS", (void*)&DEBUGHUD_SHOW_STATS);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_MODE", (void*)&DEBUGHUD_SHOW_MODE);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_PROFILER", (void*)&DEBUGHUD_SHOW_PROFILER);
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_ALL", (void*)&DEBUGHUD_SHOW_ALL);
    
    RegisterObject<Console>(engine, "DebugHud");
    engine->RegisterObjectMethod("DebugHud", "void Toggle(uint)", asMETHOD(DebugHud, Toggle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void ToggleAll()", asMETHOD(DebugHud, ToggleAll), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_style(XMLFile@+)", asMETHOD(DebugHud, SetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ get_style() const", asMETHOD(DebugHud, GetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_mode(uint)", asMETHOD(DebugHud, SetMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint get_mode() const", asMETHOD(DebugHud, GetMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_profilerInterval(float)", asMETHOD(DebugHud, SetProfilerInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "float get_profilerInterval() const", asMETHOD(DebugHud, GetProfilerInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_useRendererStats(bool)", asMETHOD(DebugHud, SetUseRendererStats), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "bool get_useRendererStats() const", asMETHOD(DebugHud, GetUseRendererStats), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_statsText() const", asMETHOD(DebugHud, GetStatsText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_modeText() const", asMETHOD(DebugHud, GetModeText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_profilerText() const", asMETHOD(DebugHud, GetProfilerText), asCALL_THISCALL);
    engine->RegisterGlobalFunction("DebugHud@+ get_debugHud()", asFUNCTION(GetDebugHud), asCALL_CDECL);
}

static Engine* GetEngine()
{
    return GetScriptContext()->GetSubsystem<Engine>();
}

static void RegisterEngine(asIScriptEngine* engine)
{
    RegisterObject<Engine>(engine, "Engine");
    engine->RegisterObjectMethod("Engine", "void RunFrame()", asMETHOD(Engine, RunFrame), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void Exit()", asMETHOD(Engine, Exit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void DumpProfilingData()", asMETHOD(Engine, DumpProfilingData), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void DumpResources()", asMETHOD(Engine, DumpResources), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "Console@+ CreateConsole()", asMETHOD(Engine, CreateConsole), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "DebugHud@+ CreateDebugHud()", asMETHOD(Engine, CreateDebugHud), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_minFps(int)", asMETHOD(Engine, SetMinFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_minFps() const", asMETHOD(Engine, GetMinFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxFps(int)", asMETHOD(Engine, SetMaxFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxFps() const", asMETHOD(Engine, GetMaxFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxInactiveFps(int)", asMETHOD(Engine, SetMaxInactiveFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxInactiveFps() const", asMETHOD(Engine, GetMaxInactiveFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_initialized() const", asMETHOD(Engine, IsInitialized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_exiting() const", asMETHOD(Engine, IsExiting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_headless() const", asMETHOD(Engine, IsHeadless), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Engine@+ get_engine()", asFUNCTION(GetEngine), asCALL_CDECL);
}

void RegisterEngineAPI(asIScriptEngine* engine)
{
    RegisterConsole(engine);
    RegisterDebugHud(engine);
    RegisterEngine(engine);
}
