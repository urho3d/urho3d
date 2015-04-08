/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file SerializationStructCompiler.cpp
	@brief */

#include <fstream>
#include <sstream>
#include <cassert>
#include <cstring>

#include "kNet/NetException.h"
#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/SerializationStructCompiler.h"

using namespace std;

namespace kNet
{

std::string SerializationStructCompiler::ParseToValidCSymbolName(const char *str)
{
	stringstream ss;
	size_t len = strlen(str);
	for(size_t i = 0; i < len; ++i)
		if ((isalpha(str[i]) || (ss.str().length() > 0 && isdigit(str[i]))) && str[i] != ' ')
			ss << str[i];

	return ss.str();
}

void SerializationStructCompiler::WriteFilePreamble(std::ofstream &out)
{
	// Write the preamble of the file.
	out << "#pragma once" << endl
	    << endl
	    << "#include \"kNet/DataDeserializer.h\"" << endl
	    << "#include \"kNet/DataSerializer.h\"" << endl
	    << endl;
}

void SerializationStructCompiler::WriteMemberDefinition(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	string type;

	if (elem.type == SerialInvalid)
		throw kNet::NetException("Invalid element type for SerializationStructCompiler::WriteMemberDefinition!");

	string name = ParseToValidCSymbolName(elem.name.c_str());

	if (elem.type == SerialStruct || elem.type == SerialOther)
		type = elem.typeString;
	else
		type = SerialTypeToCTypeString(elem.type);

	if (type == "string")
		type = "std::string"; // Make a hardcoded fix for std::string so that the user doesn't have to specify 'std::string' into the XML, which would be clumsy.

	if (elem.varyingCount == true)
		out << Indent(level) << "std::vector<" << type << "> " << name << ";" << endl;
	else if (elem.count > 1)
		out << Indent(level) << type << " " << name << "[" << elem.count << "];" << endl;
	else
		out << Indent(level) << type << " " << name << ";" << endl;
}

void SerializationStructCompiler::WriteStructMembers(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	for(size_t i = 0; i < elem.elements.size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		WriteMemberDefinition(e, level, out);
	}
	out << endl;
}

void SerializationStructCompiler::WriteNestedStructs(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	for(size_t i = 0; i < elem.elements.size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		if (e.type == SerialStruct)
			WriteStruct(e, level, out);
	}
}

/// The 'size_t Size() const' member function for a struct returns the size of the generated structure, in bytes.
void SerializationStructCompiler::WriteStructSizeMemberFunction(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	out << Indent(level) << "inline size_t Size() const" << endl
		<< Indent(level) << "{" << endl
		<< Indent(level+1) << "return ";

	for(size_t i = 0; i < elem.elements.size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		if (i > 0)
			out << " + ";

		string memberName = ParseToValidCSymbolName(e.name.c_str());

		if (e.varyingCount)
		{
			if (e.count % 8 != 0) // DynamicCount must be full bytes! In case of error, round up to full byte. ///\todo Support dynamicCounts at bit-level.
				out << (e.count + 7) / 8 << "/* Warning: DynamicCount was " << e.count << " bits, but only full bytes are supported for now.*/ + ";
			else
				out << e.count / 8 << " + ";
		}

/*
		if (e.type == SerialStruct)
		{
			if (e.varyingCount)
				out << "kNet::SumArray(" << memberName << ", " << memberName << ".size())";
			else if (e.count > 1)
				out << "kNet::SumArray(" << memberName << ", " << e.count << ")";
			else
				out << memberName << ".Size()";
		}
		else*/ if (e.type == SerialStruct || e.type == SerialOther || e.type == SerialString)
		{
			std::string typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";
			if (e.varyingCount)
				out << "kNet::ArraySize<" << typeSerializer << " >(" << memberName << ", " << memberName << ".size())";
			else if (e.count > 1)
				out << "kNet::ArraySize(" << typeSerializer << " >(" << memberName << ", " << e.count << ")";
			else
				out << typeSerializer << "::Size(" << memberName << ")";
		}
		else
		{
			if (e.varyingCount)
				out << memberName << ".size()" << "*" << SerialTypeSize(e.type);
			else if (e.count > 1)
				out << e.count << "*" << SerialTypeSize(e.type);
			else
				out << SerialTypeSize(e.type);
		}
	}

	if (elem.elements.empty())
		out << "0";

	out << ";" << endl
		<< Indent(level) << "}" << endl << endl;
}

void SerializationStructCompiler::WriteSerializeMemberFunction(/*const std::string &className, */const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	out << Indent(level) << "inline void SerializeTo(kNet::DataSerializer &dst) const" << endl
		<< Indent(level) << "{" << endl;

	++level;

	for(size_t i = 0; i < elem.elements.size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		string memberName = ParseToValidCSymbolName(e.name.c_str());

		if (e.varyingCount == true)
		{
			// What type of variable will hold the varyingCount field?
			if (e.count != 8 && e.count != 16 && e.count != 32) ///\todo Support arbitrary bit-length varyingCounts.
				out << Indent(level) << "// TODO: Unsupported varyingCount field length of " << e.count << " bits used!" << endl;

			out << Indent(level) << "dst.Add<u" << e.count << ">(" << memberName << ".size());" << endl;
		}
/*
		if (e.type == SerialStruct)
		{
			if (e.varyingCount == true)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << memberName << ".size(); ++i)" << endl;
				out << Indent(level+1) << memberName << "[i].SerializeTo(dst);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1) << memberName << "[i].SerializeTo(dst);" << endl;
			}
			else
				out << Indent(level) << memberName << ".SerializeTo(dst);" << endl;
		}
		else*/ if (e.type == SerialStruct || e.type == SerialOther)
		{
			std::string typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";

			if (e.varyingCount == true)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << memberName << ".size(); ++i)" << endl;
				out << Indent(level+1) << typeSerializer << "::SerializeTo(dst, " << memberName << "[i]);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1) << typeSerializer << "::SerializeTo(dst, " << memberName << "[i]);" << endl;
			}
			else
				out << Indent(level) << typeSerializer << "::SerializeTo(dst, " << memberName << ");" << endl;
		}
		else
		{
			if (e.varyingCount == true)
			{
				out << Indent(level) << "if (" << memberName << ".size() > 0)" << endl;
				out << Indent(level+1) << "dst.AddArray<" << SerialTypeToCTypeString(e.type) << ">(&" << memberName
					<< "[0], " << memberName << ".size());" << endl;
			}
			else if (e.count > 1)
				out << Indent(level) << "dst.AddArray<" << SerialTypeToCTypeString(e.type) << ">(" << memberName
					<< ", " << e.count << ");" << endl;
			else 
				out << Indent(level) << "dst.Add<" << SerialTypeToCTypeString(e.type) << ">(" << memberName
					<< ");" << endl;
		}
	}
	--level;
	out << Indent(level) << "}" << endl;
//	out << Indent(level) << "inline static void SerializeTo(knet::DataSerializer &dst, const " << className << " &src) { src.SerializeTo(dst); }"<< endl;
	out << endl;
}

void SerializationStructCompiler::WriteDeserializeMemberFunction(/*const std::string &className, */const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	out << Indent(level) << "inline void DeserializeFrom(kNet::DataDeserializer &src)" << endl
		<< Indent(level) << "{" << endl;

	++level;

	for(size_t i = 0; i < elem.elements.size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		string memberName = ParseToValidCSymbolName(e.name.c_str());

		if (e.varyingCount == true)
		{
			// What type of variable will hold the varyingCount field?
			if (e.count != 8 && e.count != 16 && e.count != 32) ///\todo Support arbitrary bit-length varyingCounts.
				out << Indent(level) << "// TODO: Unsupported varyingCount field length of " << e.count << " bits used!" << endl;

			out << Indent(level) << memberName << ".resize(src.Read<u" << e.count << ">());" << endl;
		}

/*		if (e.type == SerialStruct)
		{
			if (e.varyingCount == true)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << memberName << ".size(); ++i)" << endl;
				out << Indent(level+1) << memberName << "[i].DeserializeFrom(src);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1) << memberName << "[i].DeserializeFrom(src);" << endl;
			}
			else
				out << Indent(level) << memberName << ".DeserializeFrom(src);" << endl;
		} */
		if (e.type == SerialStruct || e.type == SerialOther)
		{
			std::string typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";

			if (e.varyingCount == true)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << memberName << ".size(); ++i)" << endl;
				out << Indent(level+1) << typeSerializer << "::DeserializeFrom(src, " << memberName << "[i]);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level) << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1) << typeSerializer << "::DeserializeFrom(src, " << memberName << "[i]);" << endl;
			}
			else
				out << Indent(level) << typeSerializer << "::DeserializeFrom(src, " << memberName << ");" << endl;
		}
		else 
		{
			if (e.varyingCount == true)
			{
				out << Indent(level) << "if (" << memberName << ".size() > 0)" << endl;
				out << Indent(level+1) << "src.ReadArray<" << SerialTypeToCTypeString(e.type) << ">(&" << memberName
					<< "[0], " << memberName << ".size());" << endl;
			}
			else if (e.count > 1)
				out << Indent(level) << "src.ReadArray<" << SerialTypeToCTypeString(e.type) << ">(" << memberName
					<< ", " << e.count << ");" << endl;
			else 
				out << Indent(level) << memberName << " = src.Read<" << SerialTypeToCTypeString(e.type) << ">();" << endl;
		}
	}
	--level;
	out << Indent(level) << "}" << endl;
//	out << Indent(level) << "inline static void DeserializeFrom(knet::DataDeserializer &src, " << className << " &dst) { dst.DeserializeFrom(src); }"<< endl;
	out << endl;
}

void SerializationStructCompiler::WriteStruct(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	string className = string("struct S_") + ParseToValidCSymbolName(elem.name.c_str());
	if (level == 0)
		className = string("struct ") + ParseToValidCSymbolName(elem.name.c_str());

	out << Indent(level) << className << endl
	    << Indent(level) << "{" << endl;

	WriteNestedStructs(elem, level+1, out);
	WriteStructMembers(elem, level+1, out);
	WriteStructSizeMemberFunction(elem, level+1, out);
	WriteSerializeMemberFunction(/*className, */elem, level+1, out);
	WriteDeserializeMemberFunction(/*className, */elem, level+1, out);
	out << Indent(level) << "};" << endl << endl;
}

void SerializationStructCompiler::CompileStruct(const SerializedElementDesc &structure, const char *outfile)
{
	ofstream out(outfile);

	WriteFilePreamble(out);
	WriteStruct(structure, 0, out);
}

void SerializationStructCompiler::WriteMessage(const SerializedMessageDesc &message, std::ofstream &out)
{
	string structName = string("Msg") + message.name;
	out << "struct " << structName << endl
		<< "{" << endl;

	out << Indent(1) << structName << "()" << endl 
		<< Indent(1) << "{" << endl
		<< Indent(2) << "InitToDefault();" << endl
		<< Indent(1) << "}" << endl << endl;

	out << Indent(1) << structName << "(const char *data, size_t numBytes)" << endl 
		<< Indent(1) << "{" << endl
		<< Indent(2) << "InitToDefault();" << endl
		<< Indent(2) << "kNet::DataDeserializer dd(data, numBytes);" << endl
		<< Indent(2) << "DeserializeFrom(dd);" << endl
		<< Indent(1) << "}" << endl << endl;

	out << Indent(1) << "void InitToDefault()" << endl
		<< Indent(1) << "{" << endl
		<< Indent(2) << "reliable = defaultReliable;" << endl
		<< Indent(2) << "inOrder = defaultInOrder;" << endl
		<< Indent(2) << "priority = defaultPriority;" << endl
		<< Indent(1) << "}" << endl << endl;

	out << Indent(1) << "enum { messageID = "<< message.id << " };" << endl;
	out << Indent(1) << "static inline const char * const Name() { return \"" << message.name << "\"; }" << endl << endl;

	out << Indent(1) << "static const bool defaultReliable = " << (message.reliable ? "true" : "false") << ";" << endl;
	out << Indent(1) << "static const bool defaultInOrder = " << (message.inOrder ? "true" : "false") << ";" << endl;
	out << Indent(1) << "static const u32 defaultPriority = " << message.priority << ";" << endl << endl;

	out << Indent(1) << "bool reliable;" << endl;
	out << Indent(1) << "bool inOrder;" << endl;
	out << Indent(1) << "u32 priority;" << endl << endl;

	WriteNestedStructs(*message.data, 1, out);
	WriteStructMembers(*message.data, 1, out);
	WriteStructSizeMemberFunction(*message.data, 1, out);
	WriteSerializeMemberFunction(/*structName, */*message.data, 1, out);
	WriteDeserializeMemberFunction(/*structName, */*message.data, 1, out);

	out << "};" << endl << endl;

}

void SerializationStructCompiler::CompileMessage(const SerializedMessageDesc &message, const char *outfile)
{
	ofstream out(outfile);

	WriteFilePreamble(out);
	WriteMessage(message, out);
}

std::string SerializationStructCompiler::Indent(int level)
{
	stringstream ss;
	for(int i = 0; i < level; ++i)
		ss << "\t";
	return ss.str();
}

} // ~kNet
