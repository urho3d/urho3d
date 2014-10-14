#include "Precompiled.h"

#include "asPEEK.h"
#include "Context.h"
#include "Script.h"
#include "ScriptFile.h"
#include "FileSystem.h"
#include "StringUtils.h"
#include <iostream>
#include <fstream>

namespace Urho3D {

	class asPEEK::Variable 
	{
	public:
		Variable() : 
			tid(0), address(0x0) 
		{
		}
		Variable(void* addr, int typeID) : 
			tid(typeID), address(addr) 
		{
		}

		bool isValid() const 
		{
			return address != 0x0;
		}

		bool isCPPObject() const 
		{
			return (tid & asTYPEID_APPOBJECT) != 0;
		}

		int tid;
		void* address;
	};

	class asPEEK::Handler 
	{
	public:
		Handler(asPEEK* peek, const String& name) : 
			peek(peek), name(name) 
		{
		}

		asPEEK* peek;
		String name;
	};

	asPEEK::asPEEK(Context* ctx, int port) : 
		engine_(0x0) 
	{
		ctx_ = ctx;

		struct mg_callbacks callbacks;
		memset(&callbacks, 0, sizeof(callbacks)); //seriously ugly
		callbacks.websocket_connect = websocket_connect_handler;
		callbacks.websocket_ready = websocket_ready_handler;
		callbacks.websocket_data = websocket_data_handler;
		callbacks.connection_close = websocket_close_handler;

		const char *options[] = {
			"listening_ports", "9002",
			"document_root", "docroot",//??
			NULL
		};

		debuggingLine_ = 0;
		debuggingSection_ = 0;
		debuggingContext_ = 0x0;
		debuggingStartedFunction_ = 0x0;
		debuggingEndedFunction_ = 0x0;
		loadSectionFunction_ = (asPEEK::DefaultLoadSectionFunction);
		restartFunction_ = 0x0; //TODO: implement as restart? probably not
		saveSectionFunction_ = (asPEEK::DefaultSaveSectionFunction);//0x0; //TODO: implement section saving

		sectionCount_ = 1;

		this->context_ = mg_start(&callbacks, this, options);

		debugInterrupt_ = false;
		nextDebugCommand_ = CONTINUE;
	}

	asPEEK::~asPEEK() 
	{
		::mg_stop(context_);
	}

	void asPEEK::SetDebuggerEnabled(bool enabled) 
	{
		debugInterrupt_ = enabled;
	}

	int asPEEK::websocket_connect_handler(const mg_connection *conn) 
	{
		mg_request_info* info = mg_get_request_info(const_cast<mg_connection*>(conn));
		asPEEK* inst = (asPEEK*)info->user_data;
		if (inst->tracked_context_.Size() > 0) 
		{
			for (HashMap<int,asIScriptContext*>::Iterator it = inst->tracked_context_.Begin(); it != inst->tracked_context_.End(); ++it)
				it->second_->SetLineCallback(asMETHOD(asPEEK, LineCallback), inst, asCALL_THISCALL);
		}
		return 0; //??err just assume everything's okeydokey?
	}

	void asPEEK::websocket_ready_handler(mg_connection *conn) 
	{
		mg_request_info* info = mg_get_request_info(conn);
		asPEEK* inst = (asPEEK*)info->user_data;

		inst->connectionList_.Push(conn);
		if (inst->engine_ == 0x0) 
		{
			const FileSystem* fs = inst->ctx_->GetSubsystem<FileSystem>();
			Script* scripting = inst->ctx_->GetSubsystem<Script>();
			inst->currentDir_ = fs->GetCurrentDir().CString();
			inst->engine_ = scripting->GetScriptEngine();
			inst->AddContext(scripting->GetScriptFileContext());
			inst->AddContext(scripting->GetImmediateContext());
			asIScriptEngine* engine = inst->engine_;
			String modName;
			
			for (unsigned int i = 0; i < engine->GetModuleCount(); ++i) 
			{
				asIScriptModule* mod = engine->GetModuleByIndex(i);
				inst->AddModule(mod);
				inst->AddScriptSection(mod->GetName(), mod->GetName());
				modName = mod->GetName();
			}
			
			ScriptFile* file = scripting->GetDefaultScriptFile();
			if (file != 0x0) 
			{
				HashSet<String>& includes = file->includeFiles_;
				for (HashSet<String>::Iterator it = includes.Begin(); it != includes.End(); ++it)
					inst->AddScriptSection((*it), modName);
			}
		} 
		else 
		{
			for (HashMap<int,asIScriptContext*>::ConstIterator it = inst->tracked_context_.Begin(); it != inst->tracked_context_.End(); ++it) 
			{
				it->second_->SetLineCallback(asMETHOD(asPEEK, LineCallback), inst, asCALL_THISCALL);
				inst->SendContexts(conn);
			}
		}
		inst->NewClient(conn);
	}

	void asPEEK::websocket_close_handler(mg_connection *conn) 
	{
		mg_request_info* info = mg_get_request_info(conn);
		asPEEK* instance = (asPEEK*)info->user_data;

		instance->connectionList_.Remove(conn);
		if (instance->connectionList_.Size() == 0) 
		{
			for (HashMap<int,SectionData>::Iterator it = instance->sections_.Begin(); it != instance->sections_.End(); ++it)
				it->second_.breakpoints.Clear();
		}
		if (instance->debuggingContext_ != 0x0 && instance->connectionList_.Size() == 0) {
			instance->debugInterrupt_ = true;
			instance->EndDebugging();
		}
		if (instance->connectionList_.Size() == 0) 
		{
			for (HashMap<int,asIScriptContext*>::ConstIterator it = instance->tracked_context_.Begin(); it != instance->tracked_context_.End(); ++it)
				it->second_->SetLineCallback(asMETHOD(asPEEK, VoidLineCallback), instance, asCALL_THISCALL);
		}
	}

	int asPEEK::websocket_data_handler(mg_connection *conn, int flags, char *data, size_t data_len) 
	{
		//if (flags & 0x80) {
		mg_request_info* info = mg_get_request_info(conn);
		asPEEK* instance = (asPEEK*)info->user_data;

		flags &= 0x7f;
		switch (flags) 
		{
		case WEBSOCKET_OPCODE_CONTINUATION: //shouldn't need
			fprintf(stderr, "CONTINUATION...\n");
			break;
		case WEBSOCKET_OPCODE_TEXT: 
			{
				Message msg(conn, String(data,data_len));
				instance->ProcessMessage(msg);
			}
			break;
		case WEBSOCKET_OPCODE_BINARY: //shouldn't need
			break;
		case WEBSOCKET_OPCODE_CONNECTION_CLOSE:
			/* If client initiated close, respond with close message in acknowlegement */
			///if (!ws_conn[wsd].closing) {
			// mg_websocket_write(conn, WEBSOCKET_OPCODE_CONNECTION_CLOSE, data, data_len);
			//ws_conn[wsd].closing = 1; /* we should not send addional messages when close requested/acknowledged */
			//}
			return 0; /* time to close the connection */
			break;
		case WEBSOCKET_OPCODE_PING:
			mg_websocket_write(conn, WEBSOCKET_OPCODE_PONG, data, data_len);
			break;
		case WEBSOCKET_OPCODE_PONG:
			{ //we'll get pong'ed if we take too long, which is a little weird
				Message msg(conn, String(data,data_len));
				instance->ProcessMessage(msg);
			}
			break;
		default:
			fprintf(stderr, "Unknown flags: %02x\n", flags);
			break;
		}
		//}

		return 1;   /* keep connection open */
	}

	void asPEEK::VoidLineCallback(asIScriptContext* ctx) 
	{
		return;
	}

	bool asPEEK::CheckBreakpoint(int line, SectionData* sectionData) 
	{
		if (!sectionData || sectionData->breakpoints.Size() == 0)
			return false;
		return sectionData->breakpoints.Contains(line);
	}

	void asPEEK::LineCallback(asIScriptContext* ctx) 
	{
		if (ctx->GetState() != asEXECUTION_ACTIVE)
			return;

		if (debuggingContext_ != 0x0 && debuggingContext_->GetState() != asEXECUTION_ACTIVE) 
		{
			EndDebugging();
			return;
		}

		const char* section = 0x0;
		int line = ctx->GetLineNumber(0, 0, &section);
		if (line <= 0)
			return;
		if (!section)
			return;
		SectionData *d = GetSectionData(section);
		if (!d)
			return;

		// if command is continue (default) check breakpoint 
		if (nextDebugCommand_ == CONTINUE) 
		{
			if (d->breakpoints.Size() > 0 && CheckBreakpoint(line, d)) 
			{ // hit a breakpoint
				if (debuggingStartedFunction_)
					debuggingStartedFunction_();

				//boost::mutex::scoped_lock lock(debugging_mutex);
				debuggingLine_ = line;
				debuggingSection_ = d->id;
				// this thread is now being debugged
				debuggingContext_ = ctx;
				//lock.unlock();

				Debug(ctx, line, d);
			} 
			else if (ctx == debuggingContext_) 
			{
					EndDebugging();
			}

		} 
		else 
		{ 
			int ssize = ctx->GetCallstackSize();
			
			switch (nextDebugCommand_) 
			{
			case asPEEK::STEPOUT:
				if (ctx->GetCallstackSize() < debuggingStackLevel_) 
				{
					//The stack has gotten smaller, that should mean that we've stepped out
					debuggingLine_ = line;
					debuggingSection_ = d->id;
					debuggingContext_ = ctx;
					Debug(ctx, line, d);
				} 
				else 
				{
					if (d->breakpoints.Size() > 0 && CheckBreakpoint(line,d)) 
					{ // hit a breakpoint
						debuggingLine_ = line;
						debuggingSection_ = d->id;
						debuggingContext_ = ctx;
						Debug(ctx, line, d);
					}
				}
				break;
			case asPEEK::STEPIN:
				{
					//We we step in we allow the next bit of code to execute, and then report back
					debuggingLine_ = line;
					debuggingSection_ = d->id;
					debuggingContext_ = ctx;
					Debug(ctx, line, d);
				}
				break;
			case asPEEK::STEPOVER:
				if (ctx->GetCallstackSize() <= debuggingStackLevel_) 
				{
					debuggingLine_ = line;
					debuggingSection_ = d->id;
					debuggingContext_ = ctx;
					Debug(ctx, line, d);
				} 
				else if (d->breakpoints.Size() > 0 && CheckBreakpoint(line,d)) // hit a breakpoint
				{
					debuggingLine_ = line;
					debuggingSection_ = d->id;
					debuggingContext_ = ctx;
					Debug(ctx, line, d);
				}
				break;
			default:
				break;
			}
		}
	}

	void asPEEK::SendModuleNames(mg_connection* conn) 
	{
		String ss;
		ss += "MODL [";
		for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End();) 
		{
			ss += "\"";
			ss += (*it)->GetName();
			ss += "\"";
			++it;
			if (it != tracked_modules_.End())
				ss += ",";
		}
		ss += "]";

		//con->send(modules);

		SendMessage(conn, ss);
	}

	void asPEEK::SendSectionNames(mg_connection* conn) 
	{
		String ss;
		ss += "SCLS [";

		for (HashMap<int, SectionData>::ConstIterator it = sections_.Begin(); it != sections_.End(); ) 
		{  
			ss += "{";
			ss += "\"id\":";
			ss += it->first_;
			ss += ",\"name\":\"";
			ss += it->second_.name.CString(); ss += "\",";
			ss += "\"mod\":\""; ss += it->second_.mod.CString(); ss += "\"";
			ss += "}";

			++it;
			if (it != sections_.End())
				ss += ",";
		}

		ss += "]";
		SendMessage(conn, ss);

		for (HashMap<int, SectionData>::ConstIterator it = sections_.Begin(); it != sections_.End(); ++it) 
		{
			for (HashSet<int>::ConstIterator it2 = it->second_.breakpoints.Begin(); it2 != it->second_.breakpoints.End(); ++it2) 
			{
				String ss2;
				ss2 += "BSET ";
				ss2 += it->first_;
				ss2 += " ";
				ss2 += *(it2);
				SendMessage(conn, ss2);
			}
		}
	}

	void asPEEK::SendContexts(mg_connection* conn) {
		String ss;
		ss += "CTXL";
		for (HashMap<int, asIScriptContext*>::ConstIterator it = tracked_context_.Begin(); it != tracked_context_.End(); ++it) 
		{
			ss += " ";
			ss += it->first_;
		}
		SendMessage(conn, ss);
	}

	void asPEEK::SendCurrentLine(mg_connection* conn) 
	{
		if (debuggingContext_ && debuggingSection_ && debuggingLine_) 
		{
			String ss;
			ss += "HITL ";
			ss += debuggingSection_;
			ss += " ";
			ss += debuggingLine_;

			SendMessage(conn, ss);
		}
	}

	void asPEEK::SendFile(const Vector<String>& words, mg_connection* conn) 
	{
		if (loadSectionFunction_) 
		{
			String fileContents;
			int secID = Urho3D::ToInt(words[1]);
			if (secID != 0) 
			{
				if (sections_.Contains(secID)) 
				{
					loadSectionFunction_(sections_[secID].name, fileContents);
					String msg = "FILE ";
					msg += words[1];
					msg += " ";
					msg += fileContents;
					SendMessage(conn, msg);
				}
			} 
			else 
			{
				SendMessage(conn, String("LOGE You did not define a load section function. Can not send section."));
			}
		}
	}

	String asPEEK::ToString(const Variable& var, HashSet<void*> *previous)
	{
		if (var.tid & asTYPEID_SCRIPTOBJECT) 
		{
			if (var.tid & asTYPEID_OBJHANDLE) 
			{
				String ss;
				ScriptObjectToString(*(asIScriptObject**)(var.address), ss, previous);
				return ss;
			} 
			else 
			{
				String ss;
				ScriptObjectToString((asIScriptObject*)(var.address), ss, previous);
				return ss;
			}
		} 
		else if (var.tid & asTYPEID_TEMPLATE) 
		{
			String ss;
			ss += "{\"addr\":\"0x";
			if (var.tid & asTYPEID_OBJHANDLE)
				ss += (int)(*(void**)var.address);
			else
				ss += (int)(var.address);
			ss += "\"}";
			return ss;
		} 
		else if (var.tid & asTYPEID_APPOBJECT) 
		{
			int tid = var.tid;
			bool isHandle = false;

			if (var.tid & asTYPEID_OBJHANDLE) 
			{
				tid |= asTYPEID_OBJHANDLE;
				isHandle = true;
			}

			/*if (specialTypesCount.count(tid)) {
			std::string s = "";
			if (isHandle) {
			s += conversionMethods[specialTypes[tid]](*(void**)var.address);
			} else {
			s += conversionMethods[specialTypes[tid]](var.address);
			}
			return s;
			} else {*/
			String ss;
			ss += "{\"addr\":\"0x";
			if (isHandle)
				ss += (int)(*(void**)(var.address));
			else
				ss += (int)var.address;
			ss += "\"}";
			return ss;
			//}
		} 
		else 
		{
			return PrimitiveToString(var);
		}
	}

	void asPEEK::ProcessMessage(Message& msg)
	{
		String command = msg.messageContents.Substring(0,4);
		if (command.Compare("ASGN") == 0) 
		{
			//??client doesn't support this yet
		} 
		else if (command.Compare("REQV") == 0) 
		{
			Vector<String> words;
			String ss(msg.messageContents);
			words = ss.Split(' ');

			if (words.Size() == 3) 
			{
				int id;
				id = Urho3D::ToInt(words[1]);
				if (id == 0)
					return;
				if (!sections_.Contains(id))
					return;

				String modName = sections_[id].mod;
				asIScriptModule* module = engine_->GetModule(modName.CString());

				if (module != 0x0 && tracked_modules_.Contains(module))
					SendVariable(words[2], module, msg.conn);
			}

		} 
		else if (command.Compare("GETV") == 0)
		{
			Vector<String> words;
			words = msg.messageContents.Split(' ');
			if (words.Size() < 3) 
			{
				SendMessage(msg.conn, String("ERRO Missing variable name"));
				return;
			}

			Variable v = GetGlobalVariable(words);
			if (v.isValid()) 
			{
				if (v.tid & asTYPEID_SCRIPTOBJECT) 
				{
					HashSet<void*> previous;

					if (v.tid & asTYPEID_OBJHANDLE)
						previous.Insert(*(void**)(v.address));
					else
						previous.Insert(v.address);

					String ss2;
					ss2 += "VARV {";
					ss2 += "\"mod\":\""; ss2 += words[1]; ss2 += "\",";
					ss2 += "\"name\":\""; ss2 += words[2]; ss2 += "\", \"val\":";
					SendMessage(msg.conn, ss2 + ToString(v, &previous) + "}");
				} 
				else 
				{
					String ss2;
					ss2 += "VARV {";
					ss2 += "\"mod\":\""; ss2 += words[1]; ss2 += "\",";
					ss2 += "\"name\":\""; ss2 += words[2]; ss2 += "\", \"val\":";
					SendMessage(msg.conn, ss2 + ToString(v) + "}");
				}
			} 
			else 
			{
				SendMessage(msg.conn, String("LOGW Could not find variable ") + words[2].CString());
			}

		} 
		else if (command == "GETF") 
		{
			Vector<String> words;
			String ss(msg.messageContents);
			words = ss.Split(' ');

			if (words.Size() == 2)
				SendFile(words, msg.conn);

		} 
		else if (command == "BRKS") 
		{

			Vector<String> words;
			String ss(msg.messageContents);
			words = ss.Split(' ');

			if (words.Size() == 3)
			{
				SetBreakpoint(words);
			}

		} 
		else if (command == "BRKR") 
		{

			Vector<String> words;
			String ss(msg.messageContents);
			words = ss.Split(' ');

			if (words.Size() == 3)
			{
				RemoveBreakpoint(words);
			}

		} 
		else if (command == "STOV" || command == "STIN" || command == "CONT" || command == "STOU") 
		{
			Vector<String> words;
			words = msg.messageContents.Split(' ');

			if (debuggingContext_)
				debugCommands_.Push(words[0]);
		} 
		else if (command == "SAVE") 
		{
			// strip command and script section
			int spaceCount = 0;
			unsigned int i = 0;
			unsigned size = msg.messageContents.Length();
			for (; i < size; ++i) 
			{
				if (msg.messageContents[i] == ' ')
					spaceCount++;

				if (spaceCount == 2)
					break;
			}

			int sectionId = Urho3D::ToInt(msg.messageContents.Substring(5,i-5));
			// get section id
			if (sectionId != 0) 
			{
				SendMessage(msg.conn, "LOGE Unable to parse section id: "+ msg.messageContents.Substring(5, i-5));
				return;
			}

			if (!sections_.Contains(sectionId)) 
			{
				SendMessage(msg.conn, String("LOGE Section does not exist id: " + sectionId));
				return;
			}

			msg.messageContents.Erase((size_t)0, (size_t)i+1);
			SectionData *d = &sections_[sectionId];
			
			if (saveSectionFunction_ != 0x0)
				saveSectionFunction_(d->name, msg.messageContents);
			else 
			{
				SendMessage(msg.conn, String("LOGE Save section function is not defined"));
				return;
			}

			String ss;
			ss += "SECM ";
			ss += sectionId;
			SendMessageToAll(ss);

		} 
		else if (command == "EXCT") 
		{

			if (tracked_modules_.Empty())
				return;

			// strip command and script section
			unsigned int moduleEnd = 0;
			unsigned int i = 0;
			unsigned size = msg.messageContents.Length();
			for (; i < size; ++i) 
			{
				if (msg.messageContents[i] == '?')
					moduleEnd = i;
			}

			if (moduleEnd == 0)
				return;

			String moduleName;
			// get module id
			moduleName  = msg.messageContents.Substring(5, moduleEnd-5);

			asIScriptModule *module = 0;
			if (moduleName == "Any") 
			{
				module = *tracked_modules_.Begin();
			} 
			else 
			{
				for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
				{
					if (moduleName == (*it)->GetName()) 
						module = *it;
				}
			}
			if (msg.messageContents.Length() > moduleEnd+1)
				ExecuteScript(msg.conn, module, msg.messageContents.Substring(moduleEnd+1, msg.messageContents.Length()));

		} 
		else if (command == "RSTR") 
		{
			if (restartFunction_) 
			{
				if (debuggingContext_)
					SendMessage(msg.conn, String("LOGE Currently debugging, can not restart."));
			} 
			else 
			{
				SendMessage(msg.conn, String("LOGE Restart function is not defined"));
			}
		}
	}

	void asPEEK::ProcessVariableRequest(Vector<String>* msg)
	{

	}

	void asPEEK::ProcessVariableAssignment(Vector<String>* msg)
	{
	}

	asPEEK::Variable asPEEK::GetGlobalVariable(Vector<String>& msg)
	{
		Vector<String> words;
		words = msg[2].Split(' ');
		String ns = "";
		
		int pos = words[0].Find(":");
		if (pos != String::NPOS) 
		{
			ns = words[0].Substring(0, pos);
			if (ns == " ") 
			{
				ns = "::";
			}
		}

		if (words.Empty()) 
		{
			return Variable();
		} 
		else if (words.Size() == 1) 
		{
			if (ns.Empty()) 
			{
				return GetGlobalVariable(words[0], msg[1], ns);
			} 
			else 
			{
				return GetGlobalVariable(words[0].Substring(pos+2, words[0].Length()), msg[1], ns);
			}
		} 
		else 
		{
			Variable parent;
			if (ns.Empty())
				parent = GetGlobalVariable(words[0], msg[1], ns);
			else
				parent = GetGlobalVariable(words[0].Substring(pos+2, words[0].Length()), msg[1], ns);
			
			if (parent.isValid()) 
			{
				if (!parent.isCPPObject()) 
				{
					for (unsigned int i = 1; i < words.Size(); ++i)
						parent = GetMemberVariable(parent, words[i]);
				} 
				else 
				{
					return Variable();
				}
			}
			return parent;
		}
	}

	asPEEK::Variable asPEEK::GetGlobalVariable(const String& msg, String& modName, const String& ns)
	{
		if (modName.Empty()) 
		{
			for (HashSet<asIScriptModule*>::ConstIterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
			{
				if (!ns.Empty())
					(*it)->SetDefaultNamespace(ns.CString());
				
				const int idx = (*it)->GetGlobalVarIndexByName(msg.CString());
				if (idx >= 0) 
				{
					Variable v;
					(*it)->GetGlobalVar(idx, 0, 0, &v.tid, 0);
					v.address = (*it)->GetAddressOfGlobalVar(idx);
					modName = (*it)->GetName();

					if (!ns.Empty())
						(*it)->SetDefaultNamespace("");
					return v;
				}
				if (!ns.Empty())
					(*it)->SetDefaultNamespace("");
			}
		} 
		else 
		{
			asIScriptModule* mod = engine_->GetModule(modName.CString());

			if (mod) 
			{
				if (!ns.Empty())
					mod->SetDefaultNamespace(ns.CString());

				const int idx = mod->GetGlobalVarIndexByName(msg.CString());
				Variable v;
				mod->GetGlobalVar(idx, 0, 0, &v.tid, 0);
				v.address = mod->GetAddressOfGlobalVar(idx);

				if (!ns.Empty())
					mod->SetDefaultNamespace("");

				return v;

			}
		}
		return Variable();
	}

	asPEEK::Variable asPEEK::GetMemberVariable(const String& varname, asIScriptObject* obj) {
		const unsigned int mcount = obj->GetPropertyCount();

		for (unsigned int i= 0; i < mcount; ++i) 
		{
			if (varname == obj->GetPropertyName(i)) 
				return Variable( obj->GetAddressOfProperty(i), obj->GetPropertyTypeId(i) ); 
		}

		return Variable();
	}

	asPEEK::Variable asPEEK::GetMemberVariable(const Variable& parent, const String& name){
		asIScriptObject* obj = (asIScriptObject*)parent.address;
		const unsigned int pcount = obj->GetPropertyCount();
		for (unsigned int i = 0; i < pcount; ++i) 
		{
			if (name == obj->GetPropertyName(i))
			{
				const int tid = obj->GetPropertyTypeId(i);
				if (tid & asTYPEID_OBJHANDLE)
					return Variable(*(void**)(obj->GetAddressOfProperty(i)), tid);
				else
					return Variable(obj->GetAddressOfProperty(i), tid);
			}
		}
		return Variable();
	}

	String asPEEK::PrimitiveToString(const Variable& var){
		if (var.tid > asTYPEID_DOUBLE) 
		{ // this is enumeration
			String ss;
			ss += "\"";
			ss += *(asUINT*) var.address;

			bool found = false;
			int ecount = engine_->GetEnumCount();
			for (int i = 0; i < ecount; ++i) 
			{
				int tid;
				engine_->GetEnumByIndex(i, &tid);
				if (var.tid == tid) 
				{
					found  = true;
					const char *c = engine_->GetEnumValueByIndex(tid, i, 0);
					if (c) 
					{
						ss += " ("; 
						ss += c;
						ss += ")";
					}
				}
			}

			//TODO, this part needs improvent, we are looping over all modules' enums to find a name.
			// would be good if we knew beforehand which module we look it in
			if (!found) 
			{
				for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
				{
					ecount = (*it)->GetEnumCount();

					for (int i = 0; i < ecount; ++i) 
					{
						int tid;
						(*it)->GetEnumByIndex(i, &tid);
						if (var.tid == tid) 
						{
							const char *c = (*it)->GetEnumValueByIndex(tid, i, 0);
							if (c) 
							{
								ss += " (";
								ss += c;
								ss += ")";
							}
						}
					}
				}
			}
			ss += "\"";
			return ss;
		} 
		else 
		{
			switch (var.tid) 
			{
			case asTYPEID_BOOL:
				if (*(bool*)var.address)
					return "true";
				else
					return "false";
			case asTYPEID_FLOAT:
				{
					String ss;
					ss += *(float*)var.address;
					return ss;
				}
			case asTYPEID_DOUBLE:
				{
					String ss;
					ss += (float)(*(double*)var.address);
					return ss;
				}
			case asTYPEID_INT8:
				{
					String ss;
					ss += *(char*)var.address;
					return ss;
				}
			case asTYPEID_INT16:
				{
					String ss;
					ss += *(short*)var.address;
					return ss;
				}
			case asTYPEID_INT32:
				{
					String ss;
					ss += *(int*)var.address;
					return ss;
				}
			case asTYPEID_INT64:
				{
					String ss;
					ss += (int)(*(long*)var.address);
					return ss;
				}
			case asTYPEID_UINT8:
				{
					String ss;
					ss += (unsigned short)(*(unsigned char*)var.address);
					return ss;
				}
			case asTYPEID_UINT16:
				{
					String ss;
					ss += *(unsigned short*)var.address;
					return ss;
				}
			case asTYPEID_UINT32:
				{
					String ss;
					ss += *(unsigned int*)var.address;
					return ss;
				}
			case asTYPEID_UINT64:
				{
					String ss;
					ss += (int)(*(unsigned long*)var.address);
					return ss;
				}
			default:
				return "\"Primitive?\"";
				break;
			}
		}
	}

	void asPEEK::ScriptObjectToString(asIScriptObject* obj, String& ss, HashSet<void*> *previous)
	{
		if (!obj) 
		{ 
			ss += "{\"addr\":\"null\"}";
			return;
		}
		ss += "{"; // every object starts with curly open
		ss += "\"_\":\"";
		ss += obj->GetObjectType()->GetName();
		ss += "\"";

		unsigned int pcount = obj->GetPropertyCount();

		if (pcount)
			ss += ",";

		for (unsigned int i = 0; i < pcount; ++i) 
		{
			ss += "\"";
			ss += obj->GetPropertyName(i);
			ss += "\":";
			int tid = obj->GetPropertyTypeId(i);

			if (tid & asTYPEID_SCRIPTOBJECT) 
			{
				if (previous) 
				{
					void *v = 0;
					void *t = obj->GetAddressOfProperty(i);
					if (tid & asTYPEID_OBJHANDLE)
						v = *(void**)obj->GetAddressOfProperty(i);
					else
						v = obj->GetAddressOfProperty(i);

					if (!v) 
					{
						ss += "{\"addr\":\"null\"}";

						if (i != (pcount - 1) )
							ss += ","; // comma between each member, but not to last one

						continue;
					} 
					else
					{
						if (previous->Contains(v)) 
						{		
							ss += "{\"[REPEAT]\":\"0x";
							ss += (int)v;
							ss += "\"}";

							if (i != (pcount - 1) )
								ss += ","; // comma between each member, but not to last one 

							continue;
						} 
						else 
						{
							previous->Insert(v);  
						}
					}
				}
			}

			Variable v(obj->GetAddressOfProperty(i), tid);

			ss += ToString(v, previous).CString();

			if (i != (pcount - 1) )
				ss += ","; // comma between each member, but not to last one 

		}

		ss += "}"; // every object ends with curly close
	}

	void asPEEK::SetBreakpoint(const Vector<String>& words)
	{
		int secId = Urho3D::ToInt(words[1]);
		int line = Urho3D::ToInt(words[2]);
		bool isSet = false;

		if (sections_.Contains(secId)) 
		{
			if (!sections_[secId].breakpoints.Contains(line)) 
			{
				sections_[secId].breakpoints.Insert(line);
				isSet = true;
			}
		}

		if (isSet) 
		{
			String ss;
			ss += "BSET ";
			ss += secId;
			ss += " ";
			ss += line;
			SendMessageToAll(ss);
		}
	}

	void asPEEK::RemoveBreakpoint(const Vector<String>& words)
	{
		int secId = Urho3D::ToInt(words[1]);
		int line = Urho3D::ToInt(words[2]);
		bool isRemoved = false;

		if (sections_.Contains(secId)) 
		{// section should exist
			if (sections_[secId].breakpoints.Contains(line)) 
			{
				sections_[secId].breakpoints.Erase(line);
				isRemoved = true;
			}
		}

		if (isRemoved) 
		{
			String ss;
			ss += "BREM ";
			ss += secId;
			ss += " ";
			ss += line;
			SendMessageToAll(ss);
		}
	}

	void asPEEK::SendDebugData(asIScriptContext* ctx, int line, SectionData* section) {
		for (unsigned int i = 0; i < connectionList_.Size(); ++i) {
			mg_connection* conn = connectionList_[i];
			SendThisObject(conn, ctx);
			SendGlobalVariables(conn,ctx);
			SendLocalVariables(conn, ctx);
			SendCurrentLine(conn);
			SendStack(conn, ctx);
		}
	}

	void asPEEK::Debug(asIScriptContext* ctx, int line, SectionData* section)
	{
		SendDebugData(ctx,line,section);

		while (!debugInterrupt_) 
		{// wait commands from client

			String command = "";
			if (!debugCommands_.Empty())
			{
				command = debugCommands_[0];
				debugCommands_.Erase(0);
			}

			if (command != "") 
			{
				if (command == "STOV") 
				{
					nextDebugCommand_ = STEPOVER;
					debuggingStackLevel_ = ctx->GetCallstackSize();
					break; // break out of wait cycle
				} 
				else if ( command == "CONT") 
				{
					nextDebugCommand_ = CONTINUE;
					break; // break out of wait cycle
				} 
				else if (command == "STIN") 
				{
					nextDebugCommand_ = STEPIN;
					debuggingStackLevel_ = ctx->GetCallstackSize();
					break; // break out of wait cycle
				} 
				else if (command == "STOU") 
				{
					nextDebugCommand_ = STEPOUT;
					debuggingStackLevel_ = ctx->GetCallstackSize();
					break; // break out of wait cycle
				}
			}
		}
		if (debugInterrupt_)
			debugInterrupt_ = !debugInterrupt_;
	}

	void asPEEK::SendGlobalVariables(mg_connection* conn, asIScriptContext* ctx) 
	{
		String ss;
		ss += "GLOV [";
		unsigned int ssize = engine_->GetGlobalPropertyCount();
		for (unsigned int i = 0; i < ssize; ++i) 
		{
			ss += "{";

			int tid = 0;
			const char* name = 0;
			void* addr = 0x0;
			engine_->GetGlobalPropertyByIndex(i, &name, 0, &tid, 0x0 /*isConst*/, 0x0 /*configGroup*/, &addr);
			ss += "\"";
			ss += name;
			ss += "\"";
			ss += ":";

			if (tid & asTYPEID_SCRIPTOBJECT) 
			{
				HashSet<void*> previous;
				if (tid & asTYPEID_OBJHANDLE)
					previous.Insert(*(void**)addr);
				else
					previous.Insert(addr);
				ss += ToString(Variable(addr, tid), &previous).CString();
			} else
				ss += ToString(Variable(addr, tid)).CString();

			ss += "}";
			if (i != ssize - 1)
				ss += ",";
		}
		ss += "]";
		SendMessage(conn, ss);
	}

	void asPEEK::SendLocalVariables(mg_connection* conn, asIScriptContext* ctx)
	{
		String ss;
		ss += "LOCV [";
		unsigned int ssize = ctx->GetCallstackSize();
		for (unsigned int i = 0; i < ssize; ++i) 
		{
			ss += "{";
			int varCount = ctx->GetVarCount(i);

			for (int i2 = 0; i2 < varCount; ++i2) 
			{
				void *addr = ctx->GetAddressOfVar(i2, i);

				int tid = ctx->GetVarTypeId(i2, i);
				ss += "\"";
				ss += ctx->GetVarName(i2, i);
				ss += "\"";
				ss += ":";

				if (!addr) 
				{
					ss += "\"undefined\"";
				} 
				else 
				{
					if (tid & asTYPEID_SCRIPTOBJECT) 
					{
						HashSet<void*> previous;
						if (tid & asTYPEID_OBJHANDLE)
							previous.Insert(*(void**)addr);
						else
							previous.Insert(addr);
						ss += ToString(Variable(addr, tid), &previous).CString();
					} 
					else
						ss += ToString(Variable(addr, tid)).CString();
				}
				if (i2 != (varCount - 1))
					ss += ",";
			}
			ss += "}";
			if (i != ssize - 1)
				ss += ",";
		}
		ss += "]";
		SendMessage(conn, ss);
	}

	void asPEEK::SendThisObject(mg_connection* conn, asIScriptContext* ctx)
	{
		asIScriptObject *obj = (asIScriptObject*) ctx->GetThisPointer();
		if (obj) 
		{
			String ss;
			ss += "THIS ";
			ss += ctx->GetCallstackSize();
			ss += " {";
			unsigned int pcount = obj->GetPropertyCount();
			for (unsigned int i = 0; i< pcount; ++i) 
			{
				int tid = obj->GetPropertyTypeId(i);
				ss += "\"";
				ss += obj->GetPropertyName(i);
				ss += "\"";
				ss += ":";

				void *v = obj->GetAddressOfProperty(i);
				if (!v) 
				{
					ss += "{\"addr\":\"null\"}";
				} 
				else 
				{
					if (tid & asTYPEID_SCRIPTOBJECT) 
					{
						HashSet<void*> previous;
						previous.Insert(obj);
						if (tid & asTYPEID_OBJHANDLE)
							previous.Insert(*(void**)v);
						else
							previous.Insert(v);

						ss += ToString(Variable(v, tid), &previous).CString();
					} 
					else 
					{
						ss += ToString(Variable(v, tid)).CString();
					}
				}

				if (i < (pcount-1))
					ss += ",";
			}
			ss += "}";
			SendMessage(conn, ss);
		}
	}

	void asPEEK::SendStack(mg_connection* conn, asIScriptContext* ctx)
	{
		const unsigned int ssize = ctx->GetCallstackSize();
		String ss;
		ss += "STCK [";
		for (unsigned int i = 0; i < ssize; ++i) 
		{
			const char *sectionName;
			int column;
			int lineNumber = ctx->GetLineNumber(i, &column, &sectionName);

			if (!sectionName)
				continue;
			String sectionLower = String(sectionName).ToLower();
			if (!sectionIds_.Contains(sectionLower))
				continue;

			ss += "{";
			ss += "\"l\":"; ss += lineNumber; ss += ",";
			ss += "\"c\":"; ss += column; ss += ",";
			ss += "\"s\":"; ss += sectionIds_[sectionLower]; ss += ",";
			ss += "\"f\":\""; ss += ctx->GetFunction(i)->GetDeclaration(); ss += "\"";
			ss += "}";

			if (i != ssize -1) {
				ss += ",";
			}
		}
		ss += "]";
		SendMessage(conn, ss);
	}

	void asPEEK::NewClient(mg_connection* conn)
	{
		SendModuleNames(conn);
		SendSectionNames(conn);
		SendContexts(conn);
		if (debuggingContext_) 
		{
			SendLocalVariables(conn, debuggingContext_);
			SendCurrentLine(conn);
			SendStack(conn, debuggingContext_);
		}
	}

	void asPEEK::SendVariable(const String& varname, asIScriptModule* mod, mg_connection* conn) 
	{
		Vector<String> words;
		words = varname.Split('.');

		if (words.Empty())
			return;

		// this gets the most parent object
		Variable var = GetVariableByName(words, mod);

		if (!var.address)
			return;

		if (words.Size() > 1) 
		{
			// should be an object type or else client sent a fucked up string
			if (var.tid & asTYPEID_SCRIPTOBJECT) {
				// remove most parent
				words.Erase(0);
				if (var.tid & asTYPEID_OBJHANDLE)
					var = GetChildOfObject(words, *(asIScriptObject**) var.address);
				else
					var = GetChildOfObject(words, (asIScriptObject*) var.address);

				// send value
			}
		}
		
		String ss;
		ss += "REQV ";
		ss += varname.CString();
		ss += " ";

		if (var.tid & asTYPEID_SCRIPTOBJECT) 
		{
			HashSet<void*> previous;

			if (var.tid & asTYPEID_OBJHANDLE)
				previous.Insert(*(void**)var.address);
			else
				previous.Insert(var.address);

			ss += ToString(var, &previous).CString();
		}
		else
			ss += ToString(var).CString();

		SendMessage(conn, ss);
	}

	asPEEK::Variable asPEEK::GetVariableAtLocalStack(const String& varname)
	{
		if (!debuggingContext_)
			return Variable();

		unsigned int ssize = debuggingContext_->GetCallstackSize();

		for (unsigned int i = 0; i < ssize; ++i)
		{
			int vcount = debuggingContext_->GetVarCount(i);

			for (int j = 0; j < vcount ; ++j)
			{
				if (varname == debuggingContext_->GetVarName(j, i))
				{
					return Variable(debuggingContext_->GetAddressOfVar(j, i), debuggingContext_->GetVarTypeId(j, i));
				}
			}
		}

		return Variable();
	}

	asPEEK::Variable asPEEK::GetVariableByName(const Vector<String>& name, asIScriptModule* mod)
	{
		// we should first determine if this object is local/global/member
		Variable var;
		String ns = ""; // namespace

		int pos = name[0].Find("::");

		if (pos != String::NPOS) 
		{
			ns = name[0].Substring(0, pos);

			if (ns == "") // user might want global scope ::Myint
				ns = "::";
		}

		// only if it doesn't have namespace. only global variables have namespaces
		if (ns == "") 
		{
			var = GetVariableAtLocalStack(name[0]);

			if (var.address)
				return var;


			//boost::mutex::scoped_lock lock(debugging_mutex);
			if (debuggingContext_) 
			{
				if (debuggingContext_->GetThisPointer()) 
				{
					asIScriptObject *t = (asIScriptObject*) debuggingContext_->GetThisPointer();
					//lock.unlock();
					var = GetMemberVariable(name[0].CString(), t);

					if (var.address)
						return var;
				}
			}
		}

		String modName = mod->GetName(); // look in all modules
		if (ns == "")
			var = GetGlobalVariable(name[0], modName, ns.CString()); // see if this is a global variable
		else
			var = GetGlobalVariable((name[0].Substring(pos+2, name[0].Length())).CString(), modName, ns.CString()); // see if this is a global variable

		if (var.address)
			return var;

		return Variable();
	}

	asPEEK::Variable asPEEK::GetChildOfObject(Vector<String>& member, asIScriptObject* obj)
	{
		Variable v;
		for (unsigned int i = 0; i < member.Size(); ++i) 
		{
			v = GetMemberVariable(member[i].CString(), obj);

			if (!v.address)
				return Variable(); // we failed sorry :(

			if (v.tid & asTYPEID_SCRIPTOBJECT)
			{
				if (v.tid & asTYPEID_OBJHANDLE)
					obj = *(asIScriptObject**)v.address;
				else
					obj = (asIScriptObject*)v.address;
			}
			else // only acceptable if loop is over
			{
				if (i == member.Size() -1)
					return v;
				else
					return Variable();
			}
		}

		return v;
	}

	void asPEEK::ExecuteScript(mg_connection* conn, asIScriptModule* mod, const String& script)
	{
		if (mod) 
		{
			String funcCode = "void asPEEK_Execute() {\n";
			funcCode += script;
			funcCode += "\n;}";

			// Compile the function that can be executed
			asIScriptFunction *func = 0;
			if (!ctx_->GetSubsystem<Script>()->Execute(script)) 
			{
				SendMessage(conn, String("EXCT Was not able to compile"));
				return;
			}

			SendMessage(conn, String("EXCT Execution Successful."));
		}
	}

	void asPEEK::EndDebugging()
	{
		debuggingLine_ = 0;
		debuggingSection_ = 0;
		nextDebugCommand_ = CONTINUE;
		debuggingContext_ = 0;

		if (debuggingEndedFunction_)
			debuggingEndedFunction_();

		SendMessageToAll("CONT");
	}

	void asPEEK::AddContext(asIScriptContext* ctx)
	{
		ctx->SetLineCallback(asMETHOD(asPEEK, LineCallback), this, asCALL_THISCALL);
		tracked_context_[contextCount_] = ctx;
		contextCount_++;
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			SendContexts(connectionList_[i]);
	}

	void asPEEK::ContextIsInactive(asIScriptContext* ctx){
		if (ctx == debuggingContext_)
			EndDebugging();
	}

	void asPEEK::RemoveContext(asIScriptContext* ctx)
	{
		for (HashMap<int, asIScriptContext*>::Iterator it = tracked_context_.Begin(); it != tracked_context_.End() ; ++it) 
		{
			if (it->second_ == ctx) 
			{
				ContextIsInactive(ctx);
				tracked_context_.Erase(it);
				break;
			}
		}
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			this->SendContexts(connectionList_[i]);
	}

	void asPEEK::AddModule(asIScriptModule* mod)
	{
		tracked_modules_.Insert(mod);
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			SendModuleNames(connectionList_[i]);
	}

	void asPEEK::RemoveModule(asIScriptModule* mod)
	{
		tracked_modules_.Erase(mod);
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			SendModuleNames(connectionList_[i]);
	}

	void asPEEK::AddScriptSection(const String& name, const String& mod)
	{
		SectionData d;
		d.id = sectionCount_;
		d.name = name;
		d.mod = mod;
		sectionIds_[name] = sectionCount_;
		sections_[d.id] = d;
		sectionCount_++;
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			SendSectionNames(connectionList_[i]);
	}

	void asPEEK::RemoveScriptSection(const String &name){ // UNTESTED
		if (sectionIds_.Contains(name)) 
		{
			const int id = sectionIds_[name];
			sectionIds_.Erase(name);
			sections_.Erase(id);
		}
		for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
			SendSectionNames(connectionList_[i]);
	}

	void asPEEK::SendLogMessageToAll(const String &msg)
	{
		SendMessageToAll("LOGI " + msg);
	}

	void asPEEK::SendMessageToAll(const String &msg)
	{
		for (unsigned int i = 0; i < connectionList_.Size(); ++i) 
		{
			if (connectionList_[i])
				::mg_websocket_write(connectionList_[i], WEBSOCKET_OPCODE_TEXT, msg.CString(), msg.Length());
		}
	}

	void asPEEK::SendMessage(mg_connection* conn, String& msg) 
	{
		::mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, msg.CString(), msg.Length());
	}

	bool asPEEK::AddBreakpoint(const String& section, int line)
	{
		if (!sectionIds_.Contains(section.ToLower()))
			return false;
		SectionData* d = &sections_[sectionIds_[section.ToLower()]];
		if (d->breakpoints.Contains(line))
			return false;
		d->breakpoints.Insert(line);
		return true;
	}

	bool asPEEK::RemoveBreakpoint(const String& section, int line) 
	{
		if (!sectionIds_.Contains(section))
			return false;
		SectionData* d = &sections_[sectionIds_[section.ToLower()]];
		if (d->breakpoints.Contains(line)) 
		{
			d->breakpoints.Erase(line);
			return true;
		}
		return false;
	}

	asPEEK::SectionData* asPEEK::GetSectionData(const String& section) 
	{
		asPEEK::SectionData *d = 0;
		// check if that section is added to asPEEK
		HashMap<String, int>::Iterator s = sectionIds_.Find(section.ToLower());
		if (s == sectionIds_.End())
			return 0;
		d = &sections_[s->second_];

		return d;

	}

	void asPEEK::DefaultLoadSectionFunction(const String &filename, String &script) 
	{
		std::ifstream ifs;
		String ss = "Data/";
		ss += filename;
		ifs.open(ss.CString(), std::ifstream::in);

		int ch = ifs.get();
		while (ifs.good()) 
		{
			script += (char) ch;
			ch = ifs.get();
		}

		ifs.close();

	}

	void asPEEK::DefaultSaveSectionFunction(const String& filename, String& code) 
	{
		std::ofstream ofs;
		String fl = "Data/";
		fl += filename;
		ofs.open(fl.CString(), std::ofstream::out);
		ofs.write(code.CString(),code.Length());
		ofs.close();
	}

	int asPEEK::getline(int offset, const String& input, String& output, char delimitter) 
	{
		output.Clear();
		char c;
		while ((c = input.At(offset)) != delimitter) 
		{
			++offset;
			output += c;
		}
		return offset;
	}
}