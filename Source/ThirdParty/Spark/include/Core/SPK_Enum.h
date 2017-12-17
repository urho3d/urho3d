//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frederic Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef H_SPK_ENUM
#define H_SPK_ENUM

#include "SPK_Logger.h"

// macros for enum declarations
// This allows to get a string representation of an enum value
// See this post for more info : http://stackoverflow.com/questions/147267#2025117
#define SPK_ENUM_VALUE(name,value)	name value,
#define SPK_ENUM_CASE(name,value)	case name : return #name;
#define SPK_ENUM_CMP(name,value)	if (str == #name) return name;

#define SPK_DECLARE_ENUM(EnumType,ENUM_DEF) \
enum EnumType { \
	ENUM_DEF(SPK_ENUM_VALUE) \
}; \
template<> SPK_PREFIX std::string getEnumName(EnumType value); \
template<> SPK_PREFIX EnumType getEnumValue(const std::string& name); \

#define SPK_DEFINE_ENUM(EnumType,ENUM_DEF) \
template<> \
std::string getEnumName(EnumType value) { \
	switch(value) { \
		ENUM_DEF(SPK_ENUM_CASE) \
		default : \
		SPK_LOG_ERROR("Cannot find a name in " << #EnumType << " for " << value); \
			return ""; \
	} \
} \
template<> \
EnumType getEnumValue(const std::string& str) { \
	ENUM_DEF(SPK_ENUM_CMP) \
	SPK_LOG_ERROR("Cannot find a value in " << #EnumType << " for " << str); \
	return static_cast<EnumType>(0); \
} \

namespace SPK 
{
	/**
	* @brief Gets the string representation of an enumerated value
	* @param value : the value of the enumerated
	* @return the name of an enumerated 
	*/
	template<typename T>
	std::string getEnumName(T value);	

	/** 
	* @brief Gets the value of an enumerated from its string representation
	* @param str : the name of the enumerated
	* @return the value of an enumerated
	*/
	template<typename T>
	T getEnumValue(const std::string& str);	

	/** 
	* @brief Returns an integer representation of an ORed enum string
	* The enumeration values must be power of two for the result to be consistent.
	* @param enums : A string of the form "ENUM1 | ENUM2 | ..."
	* @return the integer representation of this flag
	*/
    //template<typename T>
    //size_t getORedEnumValue(const std::string& enums) // TODO Needs testing...
    //{
    //	size_t pos = 0;
    //	size_t flag = 0;
    //	while (pos < enums.length)
    //	{
    //		size_t startPos = pos;
    //		pos = enums.find_first_of(" |",startPos);
    //		if (pos == std::npos)
    //			pos = enums.length;
    //		if (pos > startPos)
    //		{
    //			T value = getEnumValue(enums.substr(startPos,pos - startPos)); // to call the right function
    //			flag |= value;
    //		}
    //		++pos;
    //	}
    //	return flag;
    //}

	/**
	* @brief Returns a string representation of an Ored enum flag
	* The enumeration values must be power of two for the result to be consistent. 
	* @param flag : A flag representing an ORed enum
	* @return the string representation of this flag of the form "ENUM1 | ENUM2 | ..."
	*/
    //template<typename T>
    //std::string getORedEnumString(int flag) // TODO Needs testing...
    //{
    //	std::stringbuf buf;
    //	bool hasOneORedEnum = false;
    //	for (size_t i = 1; i < 32; ++i)
    //		if ((flag & (1 << i)) != 0)
    //		{
    //			std::string name = getEnumName(static_cast<T>(1 << i));
    //			if (!name.empty())
    //			{
    //				if (hasOneORedEnum)
    //					buf << '|';
    //				buf << name
    //				hasOneORedEnum = true
    //			}
    //		}
    //	if (!hasOneORedEnum)
    //		buf << getName(static_cast<T>(0));
    //	return buf.str();
    //}
}

#endif
