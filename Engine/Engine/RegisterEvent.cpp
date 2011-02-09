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
#include "ScriptFile.h"
#include "ScriptInstance.h"

#include <angelscript.h>

#include "DebugNew.h"

void SendEvent(const std::string& eventType, VariantMap& parameters)
{
    sendEvent(StringHash(eventType), parameters);
}

void SubscribeToEvent(const std::string& eventType, const std::string& handlerName)
{
    // Try to subscribe to an instance event first, then to a script file event if not found
    ScriptInstance* instance = getScriptContextInstance();
    if (instance)
        instance->addEventHandler(StringHash(eventType), handlerName);
    else
    {
        ScriptFile* file = getScriptContextFile();
        if (file)
            file->addEventHandler(StringHash(eventType), handlerName);
    }
}

void UnsubscribeFromEvent(const std::string& eventType)
{
    // Try to unsubscribe from an instance event first, then from a script file event if not found
    ScriptInstance* instance = getScriptContextInstance();
    if (instance)
        instance->removeEventHandler(StringHash(eventType));
    else
    {
        ScriptFile* file = getScriptContextFile();
        if (file)
            file->removeEventHandler(StringHash(eventType));
    }
}

void UnsubscribeFromAllEvents()
{
    // Try to unsubscribe from instance events first, then from script file events if not found
    ScriptInstance* instance = getScriptContextInstance();
    if (instance)
        instance->removeAllEventHandlers();
    else
    {
        ScriptFile* file = getScriptContextFile();
        if (file)
            file->removeAllEventHandlers();
    }
}

void registerEventLibrary(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("void sendEvent(const string& in, VariantMap&)", asFUNCTION(SendEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void subscribeToEvent(const string& in, const string& in)", asFUNCTION(SubscribeToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromEvent(const string& in)", asFUNCTION(UnsubscribeFromEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromAllEvents()", asFUNCTION(UnsubscribeFromAllEvents), asCALL_CDECL);
}
