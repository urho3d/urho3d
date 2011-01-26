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

#ifndef SCRIPT_SCRIPTENGINE_H
#define SCRIPT_SCRIPTENGINE_H

#include "RefCount.h"

class asIScriptEngine;
class asIScriptContext;
struct asSMessageInfo;

//! Script engine logging mode
enum ScriptLogMode
{
    LOGMODE_IMMEDIATE = 0,
    LOGMODE_RETAINED
};

//! Utilizes the AngelScript library for executing scripts
class ScriptEngine : public RefCounted
{
public:
    //! Construct. Create the AngelScript engine and register string & array classes
    ScriptEngine();
    //! Destruct. Release the AngelScript engine
    ~ScriptEngine();
    
    //! Create a script context
    asIScriptContext* createScriptContext();
    //! Compile and execute a line of script
    bool execute(const std::string& line);
    //! Perform garbage collection
    void garbageCollect();
    //! Set script engine logging mode, immediate is default
    void setLogMode(ScriptLogMode mode);
    //! Clear retained mode log messages
    void clearLogMessages();
    //! Log a message from the script engine
    void logMessage(const asSMessageInfo* msg);
    
    //! Return the AngelScript engine
    asIScriptEngine* getAngelScriptEngine() const { return mAngelScriptEngine; }
    //! Return immediate execution script context
    asIScriptContext* getImmediateContext() const { return mImmediateContext; }
    //! Return logging mode
    ScriptLogMode getLogMode() const;
    //! Return retained mode log messages
    const std::string& getLogMessages() const { return mLogMessages; }
    
private:
    //! AngelScript engine
    asIScriptEngine* mAngelScriptEngine;
    //! Immediate execution script context
    asIScriptContext* mImmediateContext;
    //! Script engine logging mode
    ScriptLogMode mLogMode;
    //! Retained mode log messages
    std::string mLogMessages;
};

#endif // SCRIPT_SCRIPTENGINE_H
