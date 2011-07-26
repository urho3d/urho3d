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

/** @file SerializationStructCompiler.cpp
	@brief */

// Modified by Lasse Öörni for Urho3D

#include <fstream>
#include <cassert>
#include <cstring>

#include "kNet/NetException.h"
#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/SerializationStructCompiler.h"

using namespace std;

namespace kNet
{

String SerializationStructCompiler::ParseToValidCSymbolName(const char *str)
{
	String outStr;
	size_t len = strlen(str);
	for(size_t i = 0; i < len; ++i)
		if ((isalpha(str[i]) || (outStr.Length() > 0 && isdigit(str[i]))) && str[i] != ' ')
			outStr += str[i];

	return outStr;
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
	String type;

	if (elem.type == SerialInvalid)
		throw kNet::NetException("Invalid element type for SerializationStructCompiler::WriteMemberDefinition!");

	String name = ParseToValidCSymbolName(elem.name.CString());

	if (elem.type == SerialStruct || elem.type == SerialOther)
		type = elem.typeString;
	else
		type = SerialTypeToCTypeString(elem.type);

	if (type == "string")
		type = "String";

	if (elem.varyingCount == true)
		out << Indent(level).CString() << "Vector<" << type.CString() << "> " << name.CString() << ";" << endl;
	else if (elem.count > 1)
		out << Indent(level).CString() << type.CString() << " " << name.CString() << "[" << elem.count << "];" << endl;
	else
		out << Indent(level).CString() << type.CString() << " " << name.CString() << ";" << endl;
}

void SerializationStructCompiler::WriteStructMembers(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	int childStructIndex = 1;

	for(size_t i = 0; i < elem.elements.Size(); ++i)
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

	for(size_t i = 0; i < elem.elements.Size(); ++i)
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

	out << Indent(level).CString() << "inline size_t Size() const" << endl
		<< Indent(level).CString() << "{" << endl
		<< Indent(level+1).CString() << "return ";

	for(size_t i = 0; i < elem.elements.Size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		if (i > 0)
			out << " + ";

		String memberName = ParseToValidCSymbolName(e.name.CString());

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
				out << "kNet::SumArray(" << memberName.CString() << ", " << memberName.CString() << ".size())";
			else if (e.count > 1)
				out << "kNet::SumArray(" << memberName.CString() << ", " << e.count << ")";
			else
				out << memberName.CString() << ".Size()";
		}
		else*/ if (e.type == SerialStruct || e.type == SerialOther || e.type == SerialString)
		{
			String typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";
			if (e.varyingCount)
				out << "kNet::ArraySize<" << typeSerializer.CString() << " >(" << memberName.CString() << ", " << memberName.CString() << ".Size())";
			else if (e.count > 1)
				out << "kNet::ArraySize(" << typeSerializer.CString() << " >(" << memberName.CString() << ", " << e.count << ")";
			else
				out << typeSerializer.CString() << "::Size(" << memberName.CString() << ")";
		}
		else
		{
			if (e.varyingCount)
				out << memberName.CString() << ".Size()" << "*" << SerialTypeSize(e.type);
			else if (e.count > 1)
				out << e.count << "*" << SerialTypeSize(e.type);
			else
				out << SerialTypeSize(e.type);
		}
	}

	if (elem.elements.Size() == 0)
		out << "0";

	out << ";" << endl
		<< Indent(level).CString() << "}" << endl << endl;
}

void SerializationStructCompiler::WriteSerializeMemberFunction(/*const String &className, */const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	out << Indent(level).CString() << "inline void SerializeTo(kNet::DataSerializer &dst) const" << endl
		<< Indent(level).CString() << "{" << endl;

	++level;

	for(size_t i = 0; i < elem.elements.Size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		String memberName = ParseToValidCSymbolName(e.name.CString());

		if (e.varyingCount == true)
		{
			// What type of variable will hold the varyingCount field?
			if (e.count != 8 && e.count != 16 && e.count != 32) ///\todo Support arbitrary bit-length varyingCounts.
				out << Indent(level).CString() << "// TODO: Unsupported varyingCount field length of " << e.count << " bits used!" << endl;

			out << Indent(level).CString() << "dst.Add<u" << e.count << ">(" << memberName.CString() << ".Size());" << endl;
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
			String typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";

			if (e.varyingCount == true)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << memberName.CString() << ".Size(); ++i)" << endl;
				out << Indent(level+1).CString() << typeSerializer.CString() << "::SerializeTo(dst, " << memberName.CString() << "[i]);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1).CString() << typeSerializer.CString() << "::SerializeTo(dst, " << memberName.CString() << "[i]);" << endl;
			}
			else
				out << Indent(level).CString() << typeSerializer.CString() << "::SerializeTo(dst, " << memberName.CString() << ");" << endl;
		}
		else
		{
			if (e.varyingCount == true)
			{
				out << Indent(level).CString() << "if (" << memberName.CString() << ".size() > 0)" << endl;
				out << Indent(level+1).CString() << "dst.AddArray<" << SerialTypeToCTypeString(e.type) << ">(&" << memberName.CString()
					<< "[0], " << memberName.CString() << ".size());" << endl;
			}
			else if (e.count > 1)
				out << Indent(level).CString() << "dst.AddArray<" << SerialTypeToCTypeString(e.type) << ">(" << memberName.CString()
					<< ", " << e.count << ");" << endl;
			else 
				out << Indent(level).CString() << "dst.Add<" << SerialTypeToCTypeString(e.type) << ">(" << memberName.CString()
					<< ");" << endl;
		}
	}
	--level;
	out << Indent(level).CString() << "}" << endl;
//	out << Indent(level).CString() << "inline static void SerializeTo(knet::DataSerializer &dst, const " << className.CString() << " &src) { src.SerializeTo(dst); }"<< endl;
	out << endl;
}

void SerializationStructCompiler::WriteDeserializeMemberFunction(/*const String &className, */const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	out << Indent(level).CString() << "inline void DeserializeFrom(kNet::DataDeserializer &src)" << endl
		<< Indent(level).CString() << "{" << endl;

	++level;

	for(size_t i = 0; i < elem.elements.Size(); ++i)
	{
		SerializedElementDesc &e = *elem.elements[i];
		assert(&e);

		String memberName = ParseToValidCSymbolName(e.name.CString());

		if (e.varyingCount == true)
		{
			// What type of variable will hold the varyingCount field?
			if (e.count != 8 && e.count != 16 && e.count != 32) ///\todo Support arbitrary bit-length varyingCounts.
				out << Indent(level).CString() << "// TODO: Unsupported varyingCount field length of " << e.count << " bits used!" << endl;

			out << Indent(level).CString() << memberName.CString() << ".Resize(src.Read<u" << e.count << ">());" << endl;
		}

/*		if (e.type == SerialStruct)
		{
			if (e.varyingCount == true)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << memberName << ".Size(); ++i)" << endl;
				out << Indent(level+1).CString() << memberName.CString() << "[i].DeserializeFrom(src);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1).CString() << memberName.CString() << "[i].DeserializeFrom(src);" << endl;
			}
			else
				out << Indent(level).CString() << memberName.CString() << ".DeserializeFrom(src);" << endl;
		} */
		if (e.type == SerialStruct || e.type == SerialOther)
		{
			String typeSerializer = "kNet::TypeSerializer<" + e.typeString + ">";

			if (e.varyingCount == true)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << memberName.CString() << ".Size(); ++i)" << endl;
				out << Indent(level+1).CString() << typeSerializer.CString() << "::DeserializeFrom(src, " << memberName.CString() << "[i]);" << endl;
			}
			else if (e.count > 1)
			{
				out << Indent(level).CString() << "for(size_t i = 0; i < " << e.count << "; ++i)" << endl;
				out << Indent(level+1).CString() << typeSerializer.CString() << "::DeserializeFrom(src, " << memberName.CString() << "[i]);" << endl;
			}
			else
				out << Indent(level).CString() << typeSerializer.CString() << "::DeserializeFrom(src, " << memberName.CString() << ");" << endl;
		}
		else 
		{
			if (e.varyingCount == true)
			{
				out << Indent(level).CString() << "if (" << memberName.CString() << ".Size() > 0)" << endl;
				out << Indent(level+1).CString() << "src.ReadArray<" << SerialTypeToCTypeString(e.type) << ">(&" << memberName.CString()
					<< "[0], " << memberName.CString() << ".size());" << endl;
			}
			else if (e.count > 1)
				out << Indent(level).CString() << "src.ReadArray<" << SerialTypeToCTypeString(e.type) << ">(" << memberName.CString()
					<< ", " << e.count << ");" << endl;
			else 
				out << Indent(level).CString() << memberName.CString() << " = src.Read<" << SerialTypeToCTypeString(e.type) << ">();" << endl;
		}
	}
	--level;
	out << Indent(level).CString() << "}" << endl;
//	out << Indent(level).CString() << "inline static void DeserializeFrom(knet::DataDeserializer &src, " << className.CString() << " &dst) { dst.DeserializeFrom(src); }"<< endl;
	out << endl;
}

void SerializationStructCompiler::WriteStruct(const SerializedElementDesc &elem, int level, std::ofstream &out)
{
	assert(&elem && elem.type == SerialStruct);

	String className = String("struct S_") + ParseToValidCSymbolName(elem.name.CString());
	if (level == 0)
		className = String("struct ") + ParseToValidCSymbolName(elem.name.CString());

	out << Indent(level).CString() << className.CString() << endl
	    << Indent(level).CString() << "{" << endl;

	WriteNestedStructs(elem, level+1, out);
	WriteStructMembers(elem, level+1, out);
	WriteStructSizeMemberFunction(elem, level+1, out);
	WriteSerializeMemberFunction(/*className, */elem, level+1, out);
	WriteDeserializeMemberFunction(/*className, */elem, level+1, out);
	out << Indent(level).CString() << "};" << endl << endl;
}

void SerializationStructCompiler::CompileStruct(const SerializedElementDesc &structure, const char *outfile)
{
	ofstream out(outfile);

	WriteFilePreamble(out);
	WriteStruct(structure, 0, out);
}

void SerializationStructCompiler::WriteMessage(const SerializedMessageDesc &message, std::ofstream &out)
{
	String structName = "Msg" + message.name;
	out << "struct " << structName.CString() << endl
		<< "{" << endl;

	out << Indent(1).CString() << structName.CString() << "()" << endl 
		<< Indent(1).CString() << "{" << endl
		<< Indent(2).CString() << "InitToDefault();" << endl
		<< Indent(1).CString() << "}" << endl << endl;

	out << Indent(1).CString() << structName.CString() << "(const char *data, size_t numBytes)" << endl 
		<< Indent(1).CString() << "{" << endl
		<< Indent(2).CString() << "InitToDefault();" << endl
		<< Indent(2).CString() << "kNet::DataDeserializer dd(data, numBytes);" << endl
		<< Indent(2).CString() << "DeserializeFrom(dd);" << endl
		<< Indent(1).CString() << "}" << endl << endl;

	out << Indent(1).CString() << "void InitToDefault()" << endl
		<< Indent(1).CString() << "{" << endl
		<< Indent(2).CString() << "reliable = defaultReliable;" << endl
		<< Indent(2).CString() << "inOrder = defaultInOrder;" << endl
		<< Indent(2).CString() << "priority = defaultPriority;" << endl
		<< Indent(1).CString() << "}" << endl << endl;

	out << Indent(1).CString() << "enum { messageID = "<< message.id << " };" << endl;
	out << Indent(1).CString() << "static inline const char * const Name() { return \"" << message.name.CString() << "\"; }" << endl << endl;

	out << Indent(1).CString() << "static const bool defaultReliable = " << (message.reliable ? "true" : "false") << ";" << endl;
	out << Indent(1).CString() << "static const bool defaultInOrder = " << (message.inOrder ? "true" : "false") << ";" << endl;
	out << Indent(1).CString() << "static const u32 defaultPriority = " << message.priority << ";" << endl << endl;

	out << Indent(1).CString() << "bool reliable;" << endl;
	out << Indent(1).CString() << "bool inOrder;" << endl;
	out << Indent(1).CString() << "u32 priority;" << endl << endl;

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

String SerializationStructCompiler::Indent(int level)
{
	String str;
	for(int i = 0; i < level; ++i)
		str += "\t";
	return str;
}

} // ~kNet
