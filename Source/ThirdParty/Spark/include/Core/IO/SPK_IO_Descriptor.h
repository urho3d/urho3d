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

#ifndef H_SPK_DESCRIPTOR
#define H_SPK_DESCRIPTOR

#include <vector>
#include <string>

namespace SPK
{
	class SPKObject;

namespace IO
{
	class Attribute;

	/** 
	* @brief A description of a SPKObject for serialization/deserialization 
	* 
	* A descriptor is basically a set of attributes with a name, a type and possibly a value.<br>
	* <br>
	* A descriptor cannot be created directly but is gotten via a serializable SPKObject with the method SPKObject::exportAttributes().<br>
	* A descriptor can be used to set a serializable object with the method SPKObject::importAttributes(const IO::Descriptor&).<br>
	* <br>
	* Descriptors are used by loaders and savers but can also be used to set objects within an application or to retrieve object structure. (in an editor for instance)
	*/
	class SPK_PREFIX Descriptor
	{
	friend class Attribute;
	friend class SPK::SPKObject;

	public :

		/////////////////
		// Constructor //
		/////////////////

		Descriptor(const Descriptor& descriptor);

		////////////////
		// Attributes //
		////////////////

		/**
		* @brief Gets the attribute with the given name
		* @param name : the name of the attribute
		* @return the attribute or NULL if no attribute with this name is found
		*/
		Attribute* getAttribute(const std::string& name);

		/**
		* @brief Gets the attribute with its value set with the given name
		* @param name : the name of the attribute
		* @return the attribute or NULL if no attribute with this name is found or if the attribute with this name is not set
		*/
		Attribute* getAttributeWithValue(const std::string& name);

		/**
		* @brief Gets the attribute at the given index
		* @param name : the index of the attribute
		* @return the attribute at the given index
		*/
		Attribute& getAttribute(size_t index);

		/**
		* @brief Gets the attribute with the given name (const version)
		* @param name : the name of the attribute
		* @return the attribute or NULL if no attribute with this name is found
		*/
		const Attribute* getAttribute(const std::string& name) const;

		/**
		* @brief Gets the attribute with its value set with the given name (const version)
		* @param name : the name of the attribute
		* @return the attribute or NULL if no attribute with this name is found or if the attribute with this name is not set
		*/
		const Attribute* getAttributeWithValue(const std::string& name) const;

		/**
		* @brief Gets the attribute at the given index (const version)
		* @param name : the index of the attribute
		* @return the attribute at the given index
		*/
		const Attribute& getAttribute(size_t index) const;

		/**
		* @brief Gets the number of attributes
		* @return the number of attributes
		*/
		size_t getNbAttributes() const;

		//////////
		// Misc //
		//////////

		/**
		* @brief Gets the signature
		*
		* The signature of a descriptor is a hash build with the concatenation of all its attribute names and types.<br>
		* It allows to handle different versions of serializable objects and ensure a descriptor is valid for a given type.
		*
		* @return the signature
		*/
		uint32 getSignature() const;

		/**
		* @brief Gets the name of this descriptor
		* The name of a descriptor is the name of the class which is described.
		* @return the name
		*/
		const std::string& getName() const;

	private :

		Descriptor(const std::vector<Attribute>& attributes); // Constructor only accessible by SPKObject

        std::vector<Attribute> attributes;
        std::vector<std::vector<std::string> > buffer;      // Internal buffer of stringifyed attributes values
        std::vector<Ref<SPKObject> > refBuffer;             // An internal buffer of reference to keep strong reference


		uint32 signature;

		std::string name;

		void computeSignature();
		void markAttributes();

		void setName(const std::string& name);
	};

	inline const Attribute* Descriptor::getAttribute(const std::string& name) const
	{
		return const_cast<Descriptor*>(this)->getAttribute(name);
	}

	inline const Attribute* Descriptor::getAttributeWithValue(const std::string& name) const
	{
		return const_cast<Descriptor*>(this)->getAttributeWithValue(name);
	}

	inline const Attribute& Descriptor::getAttribute(size_t index) const
	{
		return const_cast<Descriptor*>(this)->getAttribute(index);
	}

	inline size_t Descriptor::getNbAttributes() const
	{
		return attributes.size();
	}

	inline uint32 Descriptor::getSignature() const
	{
		return signature;
	}

	inline const std::string& Descriptor::getName() const
	{
		return name;
	}

	inline void Descriptor::setName(const std::string& name)
	{
		this->name = name;
	}
}}

#endif
