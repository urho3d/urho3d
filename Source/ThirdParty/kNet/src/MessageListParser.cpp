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

/** @file MessageListParser.cpp
	@brief */

#ifdef KNET_USE_TINYXML
#include <tinyxml.h>
#endif

#include <cassert>
#include <cstring>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/NetworkLogging.h"
#include "kNet/MessageListParser.h"
#include "kNet/NetException.h"
#include "kNet/Socket.h"

#define NUMELEMS(x) (sizeof(x)/sizeof(x[0]))

namespace
{
	///\note See BasicSerializedDataTypes.h:31: The order of these elements matches that of the BasicSerializedDataType enum.
	const char *data[] = { "", "bit", "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "float", "double", "string", "struct" };
	const size_t typeSizes[] = { 0xFFFFFFFF, 0xFFFFFFFF, 1, 1, 2, 2, 4, 4, 8, 8, 4, 8, 0xFFFFFFFF, 0xFFFFFFFF }; // 0xFFFFFFFF here denotes 'does not apply'.
}

namespace kNet
{

BasicSerializedDataType StringToSerialType(const char *type)
{
	if (!strcmp(type, "string") || !strcmp(type, "std::string"))
		return SerialString;
	assert(NumSerialTypes-2 == NUMELEMS(data));
	for(size_t i = 0; i < NUMELEMS(data); ++i)
		if (!strcmp(type, data[i]))
			return (BasicSerializedDataType)i;

	return SerialInvalid;
}

const char *SerialTypeToReadableString(BasicSerializedDataType type)
{
	assert(NumSerialTypes-2 == NUMELEMS(data));
	assert(type >= SerialInvalid);
	assert(type < NumSerialTypes); 
	return data[type];
}

const char *SerialTypeToCTypeString(BasicSerializedDataType type)
{
	if (type == SerialString)
		return "std::string";
	assert(NumSerialTypes-2 == NUMELEMS(data));
	assert(type >= SerialInvalid);
	assert(type < NumSerialTypes); 
	return data[type];
}

size_t SerialTypeSize(BasicSerializedDataType type)
{
	assert(NumSerialTypes-2 == NUMELEMS(data));
	assert(type >= SerialInvalid);
	assert(type < NumSerialTypes); 
	return typeSizes[type];	
}

SerializedElementDesc *SerializedMessageList::ParseNode(TiXmlElement *node, SerializedElementDesc *parentNode)
{
#ifdef KNET_USE_TINYXML
	elements.push_back(SerializedElementDesc());
	SerializedElementDesc *elem = &elements.back();
	elem->parent = parentNode;
	elem->name = node->Attribute("name") ? node->Attribute("name") : "";

	if (!strcmp(node->Value(), "message"))
	{
		elem->count = 1;
		elem->varyingCount = false;
		elem->type = SerialStruct;
	}
	else
	{
		// Cannot have both static count and dynamic count!
		if (node->Attribute("count") && node->Attribute("varyingCount"))
			KNET_LOG(LogError, "Warning: An XML node contains both 'count' and 'varyingCount' attributes! 'varyingCount' takes precedence.");

		if (node->Attribute("dynamicCount"))
		{
			node->QueryIntAttribute("dynamicCount", &elem->count);
			elem->varyingCount = true;
		}
		else if (node->Attribute("count"))
		{
			node->QueryIntAttribute("count", &elem->count);
			elem->varyingCount = false;
		}
		else
		{
			elem->count = 1;
			elem->varyingCount = false;
		}

		elem->typeString = node->Value();
		if (elem->typeString == "string")
			elem->typeString = "std::string";
		elem->type = StringToSerialType(node->Value());
		if (elem->type == SerialInvalid && !elem->typeString.empty())
			elem->type = SerialOther;
		if (elem->type == SerialStruct)
			elem->typeString = "S_" + elem->name; ///\todo Add a ClassName parameter for better control over naming here?
	}

	// If this node is a structure, parse all its members.
	if (elem->type == SerialStruct)
	{
		TiXmlElement *child = node->FirstChildElement();
		while(child)
		{
			SerializedElementDesc *childElem = ParseNode(child, elem);
			elem->elements.push_back(childElem);

			child = child->NextSiblingElement();
		}
	}

	return elem;
#else
	throw NetException("kNet was built without TinyXml support! SerializedMessageList is not available!");
#endif
}

bool ParseBool(const char *str)
{
	if (!str)
		return false;

	if (!_stricmp(str, "true") || !_stricmp(str, "1"))
		return true;
	else
		return false;
}

void SerializedMessageList::ParseMessages(TiXmlElement *root)
{
#ifdef KNET_USE_TINYXML
	TiXmlElement *node = root->FirstChildElement("message");
	while(node)
	{
		SerializedMessageDesc desc;
		int success = node->QueryIntAttribute("id", (int*)&desc.id);
		if (success == TIXML_NO_ATTRIBUTE)
		{
			KNET_LOG(LogError, "Error parsing message attribute 'id' as int!");
			node = node->NextSiblingElement("message");
			continue; 
		}
		success = node->QueryIntAttribute("priority", (int*)&desc.priority);
		if (success == TIXML_NO_ATTRIBUTE)
			desc.priority = 0; // If priority not specified, use the default priority of zero - the lowest priority possible.
		if (node->Attribute("name"))
			desc.name = node->Attribute("name");
		desc.reliable = ParseBool(node->Attribute("reliable"));
		desc.inOrder = ParseBool(node->Attribute("inOrder"));
		desc.data = ParseNode(node, 0);

		// Work a slight convenience - if there is a single struct inside a single struct inside a single struct - jump straight through to the data.

		messages.push_back(desc);

		node = node->NextSiblingElement("message");
	}
#else
	throw NetException("kNet was built without TinyXml support! SerializedMessageList is not available!");
#endif
}

void SerializedMessageList::ParseStructs(TiXmlElement *root)
{
#ifdef KNET_USE_TINYXML
	TiXmlElement *node = root->FirstChildElement("struct");
	while(node)
	{
		ParseNode(node, 0);

		node = node->NextSiblingElement("struct");
	}
#else
	throw NetException("kNet was built without TinyXml support! SerializedMessageList is not available!");
#endif
}

void SerializedMessageList::LoadMessagesFromFile(const char *filename)
{
#ifdef KNET_USE_TINYXML
	TiXmlDocument doc(filename);
	bool success = doc.LoadFile();
	if (!success)
	{
		KNET_LOG(LogError, "TiXmlDocument open failed on filename %s!", filename);
		return;
	}

	TiXmlElement *xmlRoot = doc.FirstChildElement();

	ParseStructs(xmlRoot);
	ParseMessages(xmlRoot);
#else
	throw NetException("kNet was built without TinyXml support! SerializedMessageList is not available!");
#endif
}


const SerializedMessageDesc *SerializedMessageList::FindMessageByID(u32 id)
{
	for(std::list<SerializedMessageDesc>::iterator iter = messages.begin();
		iter != messages.end(); ++iter)
		if (iter->id == id)
			return &*iter;

	return 0;
}

const SerializedMessageDesc *SerializedMessageList::FindMessageByName(const char *name)
{
	for(std::list<SerializedMessageDesc>::iterator iter = messages.begin();
		iter != messages.end(); ++iter)
		if (iter->name == name)
			return &*iter;

	return 0;
}

} // ~kNet
