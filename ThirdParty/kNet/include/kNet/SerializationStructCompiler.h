/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file SerializationStructCompiler.h
	@brief The SerializationStructCompiler class. */

#include <string>
#include <fstream>

#include "MessageListParser.h"

namespace kNet
{

/// Generates .h files out of XML description files for serializable structs and network messages.
class SerializationStructCompiler
{
public:
	void CompileStruct(const SerializedElementDesc &structure, const char *outfile);
	void CompileMessage(const SerializedMessageDesc &message, const char *outfile);

	static std::string ParseToValidCSymbolName(const char *str);

private:
	void WriteFilePreamble(std::ofstream &out);
	void WriteStruct(const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteMessage(const SerializedMessageDesc &message, std::ofstream &out);

	void WriteMemberDefinition(const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteStructMembers(const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteNestedStructs(const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteStructSizeMemberFunction(const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteSerializeMemberFunction(/*const std::string &className, */const SerializedElementDesc &elem, int level, std::ofstream &out);
	void WriteDeserializeMemberFunction(/*const std::string &className, */const SerializedElementDesc &elem, int level, std::ofstream &out);

	static std::string Indent(int level);
};

} // ~kNet
