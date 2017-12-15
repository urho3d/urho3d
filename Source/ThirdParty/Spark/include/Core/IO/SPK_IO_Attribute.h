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
#ifndef H_SPK_ATTRIBUTE
#define H_SPK_ATTRIBUTE

#include <string>
#include <vector>
#include <sstream>

namespace SPK
{
	class SPKObject;

namespace IO
{
	class Descriptor;

	/** @brief Constants defining attribute's types */
	enum AttributeType
	{
		ATTRIBUTE_TYPE_CHAR,		/**< @brief the value is a char */
		ATTRIBUTE_TYPE_BOOL,		/**< @brief the value is a boolean */
		ATTRIBUTE_TYPE_INT32,		/**< @brief the value is an int 32 bits */
		ATTRIBUTE_TYPE_UINT32,		/**< @brief the value is an unsigned int 32 bits */
		ATTRIBUTE_TYPE_FLOAT,		/**< @brief the value is a float */
		ATTRIBUTE_TYPE_VECTOR,		/**< @brief the value is a Vector3D */
		ATTRIBUTE_TYPE_COLOR,		/**< @brief the value is a Color */
		ATTRIBUTE_TYPE_STRING,		/**< @brief the value is a std::string */
		ATTRIBUTE_TYPE_REF,			/**< @brief the value is a Ref<SPKObject> */
		ATTRIBUTE_TYPE_CHARS,		/**< @brief the value is an array of char */
		ATTRIBUTE_TYPE_BOOLS,		/**< @brief the value is an array of boolean */
		ATTRIBUTE_TYPE_INT32S,		/**< @brief the value is an array of int 32 bits */
		ATTRIBUTE_TYPE_UINT32S,		/**< @brief the value is an array of unsigned int 32 bits */
		ATTRIBUTE_TYPE_FLOATS,		/**< @brief the value is an array of float */
		ATTRIBUTE_TYPE_VECTORS,		/**< @brief the value is an array of Vector3D */
		ATTRIBUTE_TYPE_COLORS,		/**< @brief the value is an array of Color */
		ATTRIBUTE_TYPE_STRINGS,		/**< @brief the value is an array of std::string */
		ATTRIBUTE_TYPE_REFS,		/**< @brief the value is an array of Ref<SPKObject> */
	};

	/**
	* @brief A single field of a serializable object
	*
	* An attribute is defined by :
	* <ul>
	* <li>a name</li>
	* <li>a type</li>
	* <li>a value (which can be set or not</li>
	* </ul>
	*/
	class Attribute
	{
	friend class Descriptor;

	public :

		Attribute(const std::string& name,AttributeType type);

		/**
		* @brief Gets the name of this attribute
		* @return the name
		*/
		const std::string& getName() const;

		/**
		* @brief Gets the type of the attribute
		* @return the type
		*/
		AttributeType getType() const;

		/**
		* @brief Tells whether the value of this attribute is set
		* @return true if the value is set, false if not
		*/
		bool hasValue() const;

		/**
		* @brief Tells whether the value of this attribute is optional
		*
		* An optional value will not necessarily be exported when serializing because it is not needed to deserialize the object
		* (Typically it is the default value of the attribute).
		* Optional value are useful when serializing in human readable format (xml for instance) to keep the information clear.
		*
		* @return true if the value is optinal, false otherwise
		*/
		bool isValueOptional() const;

		template<typename T> static AttributeType getAttributeType();
		template<typename T> static AttributeType getAttributeTypeArray();

		template<typename T> void setValue(const T& value,bool optional = false);
		template<typename T> void setValues(const T* values,size_t nb,bool optional = false);
		template<typename T> T getValue() const;
		template<typename T> std::vector<T> getValues() const;

		template<typename T> void setValueRef(const Ref<T>& value,bool optional = false);
		template<typename T> void setValuesRef(const Ref<T>* values,size_t nb,bool optional = false);
		template<typename T> Ref<T> getValueRef() const;
		template<typename T> std::vector<Ref<T> > getValuesRef() const;

		void setValueOptionalOnFalse(bool value);
		void setValueOptionalOnTrue(bool value);
		void setValueOptionalOnNull(const Ref<SPKObject>& value);
		void setValueOptionalOnEmpty(const std::string& value);

	private :

		std::string name;
		AttributeType type;
		size_t offset;

		Descriptor* descriptor;

		bool valueSet;
		bool optional;
    };

    //-----------------------------------------------------------
    // Helper funtions to convert string / numeric
    //-----------------------------------------------------------

    template<typename T>
    inline std::string ToString(const T& v)
    {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    }

    template<typename T>
    inline T FromString(const std::string& str)
    {
        std::istringstream ss(str);
        T ret;
        ss >> ret;
        return ret;
    }

    // Vector3D specialization
    template<>
    inline std::string ToString(const Vector3D& v)
    {
        std::ostringstream ss;
        ss << v.x << " " << v.y << " " << v.z;
        return ss.str();
    }

    // Vector3D specialization
    template<>
    inline Vector3D FromString(const std::string& str)
    {
        std::istringstream ss(str);
        Vector3D ret;
        ss >> ret.x >> ret.y >> ret.z;
        return ret;
    }

    // Color specialization
    template<>
    inline std::string ToString(const Color& v)
    {
        std::ostringstream ss;
        ss << v.getRGBA();
        return ss.str();
    }

    // Color specialization
    template<>
    inline Color FromString(const std::string& str)
    {
        std::istringstream ss(str);
        uint32 rgba;
        ss >> rgba;
        return Color(rgba);
    }

    //-----------------------------------------------------------

	inline Attribute::Attribute(const std::string& name,AttributeType type) :
		name(name),
		type(type),
		offset(0),
		descriptor(NULL),
		valueSet(false)
	{}

	inline const std::string& Attribute::getName() const
	{
		return name;
	}

	inline AttributeType Attribute::getType() const
	{
		return type;
	}

	inline bool Attribute::hasValue() const
	{
		return valueSet;
	}

	inline bool Attribute::isValueOptional() const
	{
		return optional;
	}

	template<typename T>
	void Attribute::setValue(const T& value,bool optional)
	{
		SPK_ASSERT(getAttributeType<T>() == type,"Attribute::setValue<T>(AttributeType,const T&,bool) - The value is not of the right type");

        offset = descriptor->buffer.size();
        valueSet = true;
        this->optional = optional;

        std::vector<std::string> strList;
        strList.push_back(ToString(value));
        descriptor->buffer.push_back(strList);

		SPK_LOG_DEBUG("Set value for attribute \"" << name << "\" : " << value);
	}

	template<typename T>
	void Attribute::setValues(const T* values,size_t nb,bool optional)
	{
		SPK_ASSERT(getAttributeTypeArray<T>() == type,"Attribute::setValues<T>(AttributeType,const T&,size_t,bool) - The array of values is not of the right type");
		if (nb == 0) return; // the value is not set if the array is empty

        offset = descriptor->buffer.size();
        valueSet = true;
        this->optional = optional;

        std::vector<std::string> strList;
        for (size_t i = 0; i < nb; ++i)
            strList.push_back(ToString(values[i]));
        descriptor->buffer.push_back(strList);

#if !defined(SPK_NO_LOG) && defined(SPK_DEBUG)
		Logger::Stream os = SPK::Logger::get().getStream(SPK::LOG_PRIORITY_DEBUG);
		os << "Set " << nb << " values for attribute \"" << name << "\" : ";
		for (size_t i = 0; i < nb; ++i)
			os << " " << values[i];
		os << '\n';
		SPK::Logger::get().flush();
#endif
	}

	template<typename T>
	T Attribute::getValue() const
	{
		SPK_ASSERT(getAttributeType<T>() == type,"Attribute::getValue<T>(AttributeType) - The desired value is not of the right type");
		SPK_ASSERT(valueSet,"Attribute::getValue<T>(AttributeType) - The value is not set and therefore cannot be read");

        std::vector<std::string> strList = descriptor->buffer[offset];
        T value = FromString<T>(strList[0]);
        SPK_LOG_DEBUG("Get value for attribute \"" << name << "\" : " << value);
        return value;
	}

	template<typename T>
	std::vector<T> Attribute::getValues() const
	{
		SPK_ASSERT(getAttributeTypeArray<T>() == type,"Attribute::getValues<T>(AttributeType) - The desired array of values is not of the right type");
		SPK_ASSERT(valueSet,"Attribute::getValues<T>(AttributeType) - The value is not set and therefore cannot be read");

        std::vector<T> tmpBuffer;
        std::vector<std::string> strList = descriptor->buffer[offset];
        for (size_t i = 0; i < strList.size(); ++i)
            tmpBuffer.push_back(FromString<T>(strList[i]));

#if !defined(SPK_NO_LOG) && defined(SPK_DEBUG)
		Logger::Stream os = SPK::Logger::get().getStream(SPK::LOG_PRIORITY_DEBUG);
        os << "Get " << strList.size() << " values for attribute \"" << name << "\" : ";
        for (size_t i = 0; i < strList.size(); ++i)
			os << " " << tmpBuffer[i];
		os << '\n';
		SPK::Logger::get().flush();
#endif

		return tmpBuffer;
	}

	template<typename T>
	void Attribute::setValueRef(const Ref<T>& value,bool optional)
	{
		SPK_ASSERT(ATTRIBUTE_TYPE_REF == type,"Attribute::setValueRef(const Ref<SPKObject>&,bool) - The value is not a reference");

        offset = descriptor->buffer.size();
        valueSet = true;
        this->optional = optional;

        size_t refBufferSize = descriptor->refBuffer.size();
        std::vector<std::string> strList;
        strList.push_back(ToString(refBufferSize));
        descriptor->buffer.push_back(strList);
        descriptor->refBuffer.push_back(value);

		SPK_LOG_DEBUG("Set value for attribute \"" << name << "\" : " << value);
	}

	template<typename T>
	Ref<T> Attribute::getValueRef() const
	{
		SPK_ASSERT(ATTRIBUTE_TYPE_REF == type,"Attribute::getValueRef() - The desired value is not a reference");
		SPK_ASSERT(valueSet,"Attribute::getValueRef() - The value is not set and therefore cannot be read");

        std::vector<std::string> strList = descriptor->buffer[offset];
        size_t refIndex = FromString<size_t>(strList[0]);
        SPK_LOG_DEBUG("Get value for attribute \"" << name << "\" : " << descriptor->refBuffer[refIndex]);
        return staticCast<T>(descriptor->refBuffer[refIndex]);
	}

	template<typename T>
	void Attribute::setValuesRef(const Ref<T>* values,size_t nb,bool optional)
	{
		SPK_ASSERT(ATTRIBUTE_TYPE_REFS == type,"Attribute::setValuesRef<T>(const Ref<T>*,size_t,bool) - The array of values is not an array of references");
		if (nb == 0) return; // the value is not set if the array is empty

        offset = descriptor->buffer.size();
        valueSet = true;
        this->optional = optional;

        std::vector<std::string> strList;
        for (size_t i = 0; i < nb; ++i)
        {
            size_t refBufferSize = descriptor->refBuffer.size();
            strList.push_back(ToString(refBufferSize));
            descriptor->refBuffer.push_back(values[i]);
        }
        descriptor->buffer.push_back(strList);

#if !defined(SPK_NO_LOG) && defined(SPK_DEBUG)
		Logger::Stream os = SPK::Logger::get().getStream(SPK::LOG_PRIORITY_DEBUG);
		os << "Set " << nb << " values for attribute \"" << name << "\" : ";
		for (size_t i = 0; i < nb; ++i)
			os << " " << values[i];
		os << '\n';
		SPK::Logger::get().flush();
#endif
	}

	template<typename T>
	std::vector<Ref<T> > Attribute::getValuesRef() const
	{
		SPK_ASSERT(ATTRIBUTE_TYPE_REFS == type,"Attribute::getValuesRef<T>() - The desired array of values is an array of references");
		SPK_ASSERT(valueSet,"Attribute::getValuesRef<T>() - The value is not set and therefore cannot be read");

        std::vector<Ref<T> > tmpBuffer;
        std::vector<std::string> strList = descriptor->buffer[offset];
        for (size_t i = 0; i < strList.size(); ++i)
        {
            size_t refIndex = FromString<size_t>(strList[i]);
            tmpBuffer.push_back( staticCast<T>(descriptor->refBuffer[refIndex]) );
        }

#if !defined(SPK_NO_LOG) && defined(SPK_DEBUG)
		Logger::Stream os = SPK::Logger::get().getStream(SPK::LOG_PRIORITY_DEBUG);
        os << "Get " << strList.size() << " values for attribute \"" << name << "\" : ";
        for (size_t i = 0; i < strList.size(); ++i)
			os << " " << tmpBuffer[i];
		os << '\n';
		SPK::Logger::get().flush();
#endif

		return tmpBuffer;
	}


	// Specialization for refs
	template<> inline void Attribute::setValue(const Ref<SPKObject>& value,bool optional)					{ setValueRef(value,optional); }
	template<> inline void Attribute::setValues(const Ref<SPKObject>* values,size_t nb,bool optional)		{ setValuesRef(values,nb,optional); }
	template<> inline Ref<SPKObject> Attribute::getValue() const											{ return getValueRef<SPKObject>(); }
	template<> inline std::vector<Ref<SPKObject> > Attribute::getValues() const								{ return getValuesRef<SPKObject>(); }

	template<> inline AttributeType Attribute::getAttributeType<char>()						{ return ATTRIBUTE_TYPE_CHAR; }
	template<> inline AttributeType Attribute::getAttributeType<bool>()						{ return ATTRIBUTE_TYPE_BOOL; }
	template<> inline AttributeType Attribute::getAttributeType<int32>()					{ return ATTRIBUTE_TYPE_INT32; }
	template<> inline AttributeType Attribute::getAttributeType<uint32>()					{ return ATTRIBUTE_TYPE_UINT32; }
	template<> inline AttributeType Attribute::getAttributeType<float>()					{ return ATTRIBUTE_TYPE_FLOAT; }
	template<> inline AttributeType Attribute::getAttributeType<Vector3D>()					{ return ATTRIBUTE_TYPE_VECTOR; }
	template<> inline AttributeType Attribute::getAttributeType<Color>()					{ return ATTRIBUTE_TYPE_COLOR; }
	template<> inline AttributeType Attribute::getAttributeType<std::string>()				{ return ATTRIBUTE_TYPE_STRING; }
	template<> inline AttributeType Attribute::getAttributeType<Ref<SPKObject> >()			{ return ATTRIBUTE_TYPE_REF; }

	template<> inline AttributeType Attribute::getAttributeTypeArray<char>()				{ return ATTRIBUTE_TYPE_CHARS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<bool>()				{ return ATTRIBUTE_TYPE_BOOLS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<int32>()				{ return ATTRIBUTE_TYPE_INT32S; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<uint32>()				{ return ATTRIBUTE_TYPE_UINT32S; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<float>()				{ return ATTRIBUTE_TYPE_FLOATS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<Vector3D>()			{ return ATTRIBUTE_TYPE_VECTORS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<Color>()				{ return ATTRIBUTE_TYPE_COLORS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<std::string>()			{ return ATTRIBUTE_TYPE_STRINGS; }
	template<> inline AttributeType Attribute::getAttributeTypeArray<Ref<SPKObject> >()		{ return ATTRIBUTE_TYPE_REFS; }

	// Helper methods (after specilization as they instantiate some template methods)
	inline void Attribute::setValueOptionalOnFalse(bool value)							{ setValue<bool>(value,!value); }
	inline void Attribute::setValueOptionalOnTrue(bool value)							{ setValue<bool>(value,value); }
	inline void Attribute::setValueOptionalOnNull(const Ref<SPKObject>& value)			{ setValueRef(value,!value); }
	inline void Attribute::setValueOptionalOnEmpty(const std::string& value)			{ setValue<std::string>(value,value.empty()); }
}}

#endif
