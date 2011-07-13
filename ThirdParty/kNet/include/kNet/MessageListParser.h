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

/** @file MessageListParser.h
	@brief The SerializedMessageList class. */

#include <vector>

#include "BasicSerializedDataTypes.h"

// TinyXML fwd
class TiXmlElement;

namespace kNet
{

/** Represents a single element of data in the stream. Can be a single value (one u32, or 
	one float), an array of data (nine bits, 12 u64's), a struct (see the elements 
	member), or even an array of structs. An array can be fixed-size (the protocol 
	file specifies the number of elements in the array), or of dynamic size (the 
	stream stores the element count just before the first actual element). */
struct SerializedElementDesc
{
	/// The data type of this element.
	BasicSerializedDataType type;

	/// A string version of this type is stored here. This field is used if the type of this element is something 
	/// else than a basic type.
	std::string typeString;

	/// If true, the number of times this element is instanced is specified in the stream.
	bool varyingCount;

	/// If varyingCount=false, denotes the number of times this element is present in the stream. If varyingCount=true,
	/// specifies how many *bits* of storage is used in the stream to store the number of times this element is stored.
	int count;

	/// The name of this element.
	std::string name;

	/// If this element denotes a structure (type == SerialStruct), then this vector contains all the child nodes.
	std::vector<SerializedElementDesc*> elements;

	/// The parent element, or 0 if this is the root element.
	SerializedElementDesc *parent;
};

/// Describes a whole serialized message.
struct SerializedMessageDesc
{
	/// This is a weak pointer to the root element of this message description. The memory is owned by the SerializedMessageList
	/// where this SerializedMessageDesc belongs to.
	SerializedElementDesc *data;
	std::string name;
	u32 id;
	bool reliable;
	bool inOrder;
	u32 priority;
};

/// Stores a whole list of message templates. 
class SerializedMessageList
{
public:
	/// Loads a set of message templates from a protocol .xml file.
	void LoadMessagesFromFile(const char *filename);

	/// Returns a message template associated with the given id, or 0 if no such message exists.
	const SerializedMessageDesc *FindMessageByID(u32 id);
	/// Returns a message template associated with the given name, or 0 if no such message exists.
	const SerializedMessageDesc *FindMessageByName(const char *name);

	/// Returns the whole list of messages.
	const std::list<SerializedMessageDesc> &GetMessages() const { return messages; }

	/// Returns a flat list of all the message elements.
	const std::list<SerializedElementDesc> &GetElements() const { return elements; }

private:
	std::list<SerializedElementDesc> elements;
	std::list<SerializedMessageDesc> messages;

	SerializedElementDesc *ParseNode(TiXmlElement *node, SerializedElementDesc *parentNode);

	void ParseMessages(TiXmlElement *root);
	void ParseStructs(TiXmlElement *root);
};

} // ~kNet
