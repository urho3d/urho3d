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
#include "Exception.h"
#include "Log.h"
#include "Profiler.h"
#include "RegisterAudio.h"
#include "RegisterArray.h"
#include "RegisterCommon.h"
#include "RegisterEvent.h"
#include "RegisterInput.h"
#include "RegisterMath.h"
#include "RegisterPhysics.h"
#include "RegisterRenderer.h"
#include "RegisterResource.h"
#include "RegisterScene.h"
#include "RegisterScript.h"
#include "RegisterStdString.h"
#include "RegisterUI.h"
#include "ScriptEngine.h"
#include "StringUtils.h"

#include <angelscript.h>

#include "DebugNew.h"

static ScriptEngine* instance;

void messageCallback(const asSMessageInfo *msg, void *param)
{
    std::string message = std::string(msg->section) + " (" + toString(msg->row) + "," + toString(msg->col) + ") " + std::string(msg->message);
    
    switch (msg->type)
    {
    case asMSGTYPE_ERROR:
        LOGERROR(message);
        break;
        
    case asMSGTYPE_WARNING:
        LOGWARNING(message);
        break;
        
    default:
        LOGINFO(message);
        break;
    }
}

ScriptEngine::ScriptEngine() :
    mAngelScriptEngine(0),
    mImmediateContext(0)
{
    if (instance)
        EXCEPTION("Script engine already exists");
    
    mAngelScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    if (!mAngelScriptEngine)
        EXCEPTION("Could not create AngelScript engine");
    
    LOGINFO("Script engine created");
    
    mAngelScriptEngine->SetUserData(this);
    mAngelScriptEngine->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, true);
    mAngelScriptEngine->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, true);
    mAngelScriptEngine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);
    
    // Register the script API
    registerAPI();
    
    // Create the context for immediate execution
    mImmediateContext = createScriptContext();
    
    instance = this;
}

ScriptEngine::~ScriptEngine()
{
    LOGINFO("Script engine shut down");
    
    if (mImmediateContext)
    {
        mImmediateContext->Release();
        mImmediateContext = 0;
    }
    
    if (mAngelScriptEngine)
    {
        mAngelScriptEngine->Release();
        mAngelScriptEngine = 0;
    }
    
    if (instance == this)
        instance = 0;
}

asIScriptContext* ScriptEngine::createScriptContext()
{
    return mAngelScriptEngine->CreateContext();
}

bool ScriptEngine::execute(const std::string& line)
{
    // Note: compiling code each time is slow. Not to be used for performance-critical or repeating activity
    PROFILE(Script_ExecuteImmediate);
    
    std::string wrappedLine = "void temp(){\n" + line + ";\n}";
    
    // Create a dummy module for compiling the line
    asIScriptModule* module = mAngelScriptEngine->GetModule("temp", asGM_ALWAYS_CREATE);
    if (!module)
        return false;
    
    // Use the line as the function name to get an easy to understand error message in case of failure
    asIScriptFunction *function = 0;
    if (module->CompileFunction(line.c_str(), wrappedLine.c_str(), -1, 0, &function) < 0)
        return false;
    
    if (mImmediateContext->Prepare(function->GetId()) < 0)
    {
        function->Release();
        return false;
    }
    
    bool success = false;
    
    success = mImmediateContext->Execute() >= 0;
    function->Release();
    
    return success;
}

void ScriptEngine::garbageCollect()
{
    PROFILE(Script_GarbageCollect);
    
    mAngelScriptEngine->GarbageCollect();
}

void ScriptEngine::registerAPI()
{
    PROFILE(ScriptEngine_RegisterAPI);
    
    // Array and string types
    LOGDEBUG("Registering array and string types");
    registerArray(mAngelScriptEngine);
    registerStdString(mAngelScriptEngine);
    
    // Libraries
    LOGDEBUG("Registering Math library");
    registerMathLibrary(mAngelScriptEngine);
    // Common library
    LOGDEBUG("Registering Common library");
    registerCommonLibrary(mAngelScriptEngine);
    // Event library
    LOGDEBUG("Registering Event library");
    registerEventLibrary(mAngelScriptEngine);
    // Resource library
    LOGDEBUG("Registering Resource library");
    registerResourceLibrary(mAngelScriptEngine);
    // Scene library
    LOGDEBUG("Registering Scene library");
    registerSceneLibrary(mAngelScriptEngine);
    // Audio library
    LOGDEBUG("Registering Audio library");
    registerAudioLibrary(mAngelScriptEngine);
    // Renderer library
    LOGDEBUG("Registering Renderer library");
    registerRendererLibrary(mAngelScriptEngine);
    // Input library
    LOGDEBUG("Registering Input library");
    registerInputLibrary(mAngelScriptEngine);
    // UI library
    LOGDEBUG("Registering UI library");
    registerUILibrary(mAngelScriptEngine);
    // Physics library
    LOGDEBUG("Registering Physics library");
    registerPhysicsLibrary(mAngelScriptEngine);
    // Script library
    LOGDEBUG("Registering Script library");
    registerScriptLibrary(mAngelScriptEngine);
}

ScriptEngine* getScriptEngine()
{
    return instance;
}
