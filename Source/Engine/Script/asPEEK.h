/*
Copyright (c) 2012 Muhammed Ikbal Akpaca

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

* Alterations in 2014 by Jonathan Sandusky:
	- Removal of Boost dependency
	- Replace websocketpp with civetweb
*/

#pragma once

#include <angelscript.h>
#include <civetweb.h>
#include <sstream>
#include "Vector.h"
#include "Str.h"


namespace Urho3D {
	
class Context;

class asPEEK 
{
	class Variable;
	class Connection;

	struct Message 
	{
		mg_connection* conn;
		String messageContents;

		Message(mg_connection* c, const String& text) 
		{
			conn = c;
			messageContents = text;
		}
	};

	class SectionData 
	{
	public:
		int id;
		String mod;
		String name;
		HashSet<int> breakpoints;
	};
	class Handler;

	enum Command {
		CONTINUE,
		STEPIN,
		STEPOUT,
		STEPOVER,
	};
		
public:
	/// construct the debugger daemon on the specified port
	asPEEK(Context* engine, int port);
	~asPEEK();

	/// function signature called when debugging first has a debugger attach
	typedef void (*DEBUGGINGSTARTEDFUNCTION)();
	/// function signature called when all debuggers have detached
	typedef void (*DEBUGGINGENDEDFUNCTION)();
	/// function signature called when a debugger sends a 'restart' command
	typedef void (*RESTARTFUNCTION)();
	/// function called to load code from a file to send to a debugger
	typedef void (*LOADSECTIONFUNCTION)(const String&, String&);
	/// function called to save code received from a debugger to a file
	typedef void (*SAVESECTIONFUNCTION)(const String&, String&);

	/// turns on/off the debugger, by default the debugger is on
	void SetDebuggerEnabled(bool enabled);

	/// adds a script context to the list of tracked contexts
	void AddContext(asIScriptContext* ctx);
	/// checks if a script context is inactive
	void ContextIsInactive(asIScriptContext* ctx);
	/// removes a script context from the list of tracked contexts
	void RemoveContext(asIScriptContext* ctx);

	/// adds a script module to the list of tracked modules
	void AddModule(asIScriptModule* mod);
	/// removes a script module from the list of tracked modules
	void RemoveModule(asIScriptModule* mod);
		
	/// adds a script section to the tracked list
	void AddScriptSection(const String& name, const String& mod);
	/// removes a script section from the tracked list
	void RemoveScriptSection(const String &name); // UNTESTED

	/// sends a message (usually a command) to a specific connection
	void SendMessage(mg_connection* conn, String& msg);
	/// sends a log message to all attached debuggers
	void SendLogMessageToAll(const String &msg);
	/// sends a general message (usually a command) to all attached debuggers
	void SendMessageToAll(const String &msg);

	/// adds a breakpoint to a script section
	bool AddBreakpoint(const String& section, int line);
	/// removes a breakpoint from a script section
	bool RemoveBreakpoint(const String& section, int line);

	void SetDebuggingStartedFunction(DEBUGGINGSTARTEDFUNCTION func) {debuggingStartedFunction_ = func;}
	void SetDebuggingEndedFunction(DEBUGGINGENDEDFUNCTION func) {debuggingEndedFunction_ = func;}
	void SetLoadSectionFunction(LOADSECTIONFUNCTION func) {loadSectionFunction_ = func;}
	void SetSaveSectionFunction(SAVESECTIONFUNCTION func) {saveSectionFunction_ = func;}
	void SetRestartFunction(RESTARTFUNCTION func) {restartFunction_ = func;}

private:
	String currentDir_;
	asIScriptEngine* engine_;
	Context* ctx_;
	asIScriptContext* debuggingContext_;
	struct mg_context *context_;
	Vector<Connection*> connections_;

	bool debugInterrupt_;
	unsigned int nextDebugCommand_;
	unsigned int debuggingStackLevel_;
	unsigned int debuggingLine_;
	unsigned int debuggingSection_;
	HashMap<int,SectionData> sections_;
	HashMap<String,int> sectionIds_;
	HashMap<int, asIScriptContext*> tracked_context_;
	HashSet<asIScriptModule*> tracked_modules_;
	Vector<String> debugCommands_;
	Vector<mg_connection*> connectionList_;

	int contextCount_;
	int sectionCount_;

	DEBUGGINGSTARTEDFUNCTION debuggingStartedFunction_;
	DEBUGGINGENDEDFUNCTION debuggingEndedFunction_;
	LOADSECTIONFUNCTION loadSectionFunction_;
	SAVESECTIONFUNCTION saveSectionFunction_;
	RESTARTFUNCTION restartFunction_;

	/// sends everything a debugger needs when it first attaches
	void NewClient(mg_connection* conn);
	/// sends the global variables in the script vm
	void SendGlobalVariables(mg_connection* conn, asIScriptContext* ctx);
	/// sends the local variables of a script context
	void SendLocalVariables(mg_connection* conn, asIScriptContext* ctx);
	/// sends the 'this' at the current point in script execution
	void SendThisObject(mg_connection* conn, asIScriptContext* ctx);
	/// sends the callstack
	void SendStack(mg_connection* conn, asIScriptContext* ctx);
	/// sends module info to a connection
	void SendModuleNames(mg_connection* conn);
	/// sends a list of the section names to a connection
	void SendSectionNames(mg_connection* conn);
	/// sends script context information to a connection
	void SendContexts(mg_connection* conn);
	/// sends the line of execution to a connection
	void SendCurrentLine(mg_connection* conn);
	/// sends the contents of a script file to a connection
	void SendFile(const Vector<String>& words, mg_connection* conn);
	/// sends a specific variable value that the client has queried for
	void SendVariable(const String& varName, asIScriptModule* mod, mg_connection* conn);
	/// uses the Script subsystem to execute some code on the immediate context, does not work while debugging is active
	void ExecuteScript(mg_connection* conn, asIScriptModule* mod, const String& script);

	String ToString(const Variable& var, HashSet<void*> *previous = 0);

	SectionData* GetSectionData(const String& section);
	void ProcessMessage(Message& msg);
	void ProcessVariableRequest(Vector<String>* msg);
	void ProcessVariableAssignment(Vector<String>* msg);
	Variable GetGlobalVariable(Vector<String>& msg);
	Variable GetGlobalVariable(const String& msg, String& modName, const String& ns);
	Variable GetMemberVariable(const Variable& parent, const String& name);
	Variable GetMemberVariable(const String& name, asIScriptObject* object);
	String PrimitiveToString(const Variable& var);
	void ScriptObjectToString(asIScriptObject* obj, String& ss, HashSet<void*> *previous = 0);
	Variable GetVariableAtLocalStack(const String& varname);
	Variable GetVariableByName(const Vector<String>& name, asIScriptModule* mod);
	Variable GetChildOfObject(Vector<String>& name, asIScriptObject* obj);

	/// sends stack,this,locals,line,etc to all connected debuggers
	void SendDebugData(asIScriptContext* ctx, int line, SectionData* section);
	/// the main "sit and spin" loop while waiting for the next debug command
	void Debug(asIScriptContext* ctx, int line, SectionData* section);
	/// clears out context specific vars when script debugging ceases (continue,detach,etc)
	void EndDebugging();

	static int websocket_connect_handler(const mg_connection *conn);
	static void websocket_ready_handler(mg_connection *conn);
	static void websocket_close_handler(mg_connection *conn);
	static int websocket_data_handler(mg_connection *conn, int flags, char *data, size_t data_len);

	static int getline(int offset, const String& input, String& ouput, char delimitter);

	static void DefaultLoadSectionFunction(const String &filename, String &script);
	static void DefaultSaveSectionFunction(const String& filename, String& code);

	/// this line callback for AngelScript does nothing
	void VoidLineCallback(asIScriptContext* ctx);
	/// this line callback for AngelScript does the main work
	void LineCallback(asIScriptContext* ctx);

	/// utility function used to test breakpoint conditions on a specific line
	bool CheckBreakpoint(int line, SectionData* sectionData);
	/// sets a breakpoint from a list of command words received by a debugger
	void SetBreakpoint(const Vector<String>& words);
	/// removes a breakpoint from a list of command words received by a debugger
	void RemoveBreakpoint(const Vector<String>& words);
};

}