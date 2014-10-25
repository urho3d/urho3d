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

	enum Command {
		CONTINUE,
		STEPIN,
		STEPOUT,
		STEPOVER,
	};
		
public:
	/// return type for MEMBER_QUERY_METHOD implementations
	enum QueryResult
	{
		/// we can't find your variable
		FAILED = -1,
		/// we've found your variable
		FOUND = 0,
		/// we found it, and we went ahead and set the value - see QueryNode in asPEEK.cpp for an explanation
		FOUND_AND_SET = 1
	};

	/// function signature for converting a variable to string, the void* will never be null
	typedef String (*TYPE_CONVERTER)(void*);
	/// function signature for setting a variable value from a string, the void* will never be null
	typedef void (*ASSIGNMENT_METHOD)(void*,String value);
	/// signature used for query an instance for members of a specific type name, refer to examples in asPEEK.cpp
	typedef QueryResult (*MEMBER_QUERY_METHOD)(void** varAddress, int* typeID, String* typeName, const String& query, const String& value);

	/// construct the debugger daemon on the specified port
	asPEEK(Context* engine, int port);
	~asPEEK();

	/// register a convesion method for a specified typename
	void RegisterConversion(const String& typeName, TYPE_CONVERTER, ASSIGNMENT_METHOD, MEMBER_QUERY_METHOD);

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

	/// the assigned function will be called whenever debugging begins (ie. a debugger attaches)
	void SetDebuggingStartedFunction(DEBUGGINGSTARTEDFUNCTION func) {debuggingStartedFunction_ = func;}
	/// the assigned function will be called whenever debugging ends (ie. all clients detach)
	void SetDebuggingEndedFunction(DEBUGGINGENDEDFUNCTION func) {debuggingEndedFunction_ = func;}
	/// assigned function is called to read script files to send over the network
	void SetLoadSectionFunction(LOADSECTIONFUNCTION func) {loadSectionFunction_ = func;}
	/// assigned function is called to save script code to file that has been received from the client
	void SetSaveSectionFunction(SAVESECTIONFUNCTION func) {saveSectionFunction_ = func;}
	/// assigned function is called whenever the client sends a "RESTART" command
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
	
	HashMap<int,TYPE_CONVERTER> conversionMethods_;
	HashMap<String,TYPE_CONVERTER> tempConversionMap_;
	HashMap<String,ASSIGNMENT_METHOD> tempAssignmentsMap_;
	HashMap<int,ASSIGNMENT_METHOD> assignmentMethods_;
	HashMap<String,MEMBER_QUERY_METHOD> queryMethods_;

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

	/// sets the value of a variable from a string
	void FromString(const Variable& var, String value, HashSet<void*>* previous = 0);
	/// converts a variable to json string (or a hex address 0x______)
	String ToString(const Variable& var, HashSet<void*> *previous = 0);
	/// converts an angelscript (or C++) primitive to a string
	String PrimitiveToString(const Variable& var);
	/// sets the value of a primitive type from the input string
	void PrimitiveFromString(const Variable& var, const String& value);
	/// converts a script object to a JSON string, appending the input 'target' with the value
	void ScriptObjectToString(asIScriptObject* obj, String& target, HashSet<void*> *previous = 0);

	/// get the SectionData for a section with specified name
	SectionData* GetSectionData(const String& section);
	/// does most of the work involved in determining what to do in response to client commands
	void ProcessMessage(Message& msg);
	/// retrieves a global scope variable from the terms
	Variable GetGlobalVariable(Vector<String>& msg);
	/// retrieves a specific global variable within a specific namespace
	Variable GetGlobalVariable(const String& msg, String& modName, const String& ns);
	/// extract as a Variable a value from a script object
	Variable GetMemberVariable(const String& name, asIScriptObject* object);
	/// grab a variable from the local stack (typically a function arg, function scope variable)
	Variable GetVariableAtLocalStack(const String& varname);
	/// retrieve a specific variable along the path (object.child.otherChild) in the specified module
	Variable GetVariableByName(const Vector<String>& name, asIScriptModule* mod);
	/// seek out a specific child of a script object
	Variable GetChildOfObject(Vector<String>& name, asIScriptObject* obj);

	/// sends stack,this,locals,line,etc to all connected debuggers
	void SendDebugData(asIScriptContext* ctx, int line, SectionData* section);
	/// the main "sit and spin" loop while waiting for the next debug command
	void Debug(asIScriptContext* ctx, int line, SectionData* section);
	/// clears out context specific vars when script debugging ceases (continue,detach,etc)
	void EndDebugging();
	/// check against angelscript for items we need to track
	void UpdateAngelScriptBindings();
	/// check against type conversion table to build an updated mapping of TID to function call
	void UpdateTypeConversions();

	static int websocket_connect_handler(const mg_connection *conn);
	static void websocket_ready_handler(mg_connection *conn);
	static void websocket_close_handler(mg_connection *conn);
	static int websocket_data_handler(mg_connection *conn, int flags, char *data, size_t data_len);

	static void DefaultLoadSectionFunction(const String &filename, String &script);
	static void DefaultSaveSectionFunction(const String& filename, String& code);

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