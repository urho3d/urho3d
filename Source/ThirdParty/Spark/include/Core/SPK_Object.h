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

#ifndef H_SPK_OBJECT
#define H_SPK_OBJECT

#include <string>
#include <map>

#define SPK_START_DESCRIPTION \
\
protected : \
virtual void fillAttributeList(std::vector<IO::Attribute>& attributes) const override \
{

#define SPK_PARENT_ATTRIBUTES(ParentName)	ParentName::fillAttributeList(attributes);
#define SPK_ATTRIBUTE(Name,Type)			attributes.push_back(SPK::IO::Attribute(Name,SPK::IO::Type));
#define SPK_ATTRIBUTE_GENERIC(Name,T)		attributes.push_back(SPK::IO::Attribute(Name,SPK::IO::Attribute::getAttributeType<T>()));
#define SPK_ATTRIBUTE_ARRAY_GENERIC(Name,T)	attributes.push_back(SPK::IO::Attribute(Name,SPK::IO::Attribute::getAttributeTypeArray<T>()));


#define SPK_END_DESCRIPTION }

#define SPK_IMPLEMENT_OBJECT(ClassName) \
private : \
friend class SPK::IO::IOManager; \
template<typename T> friend class SPK::Ref; \
static std::string asName()								{ return #ClassName; } \
static SPK::Ref<SPK::SPKObject> createSerializable()	{ return SPK_NEW(ClassName); } \
virtual SPK::Ref<SPK::SPKObject> clone() const override	{ return SPK_NEW(ClassName,*this); } \
public : \
virtual std::string getClassName() const override		{ return ClassName::asName(); }

// For templates
#define SPK_DEFINE_DESCRIPTION_TEMPLATE	protected : void fillAttributeList(std::vector<SPK::IO::Attribute>& attributes) const override;
#define SPK_START_DESCRIPTION_TEMPLATE(ClassName) \
template<typename T> inline void ClassName::fillAttributeList(std::vector<SPK::IO::Attribute>& attributes) const \
{

#define SPK_DEFINE_OBJECT_TEMPLATE(ClassName) \
private : \
friend class SPK::IO::IOManager; \
template<typename U> friend class SPK::Ref; \
static std::string asName(); \
static SPK::Ref<SPK::SPKObject> createSerializable()		{ return SPK_NEW(ClassName); } \
virtual SPK::Ref<SPK::SPKObject> clone() const override		{ return SPK_NEW(ClassName,*this); } \
public : \
virtual std::string getClassName() const override			{ return ClassName::asName(); }

#define SPK_IMPLEMENT_OBJECT_TEMPLATE(ClassName) \
template<> inline std::string ClassName::asName() { return #ClassName; }

namespace SPK
{
	/** @brief Defines the share policy for a SPKObject */
	enum SharePolicy
	{
		SHARE_POLICY_CUSTOM,	/**< The SPKObject is shared at the user's discretion */
		SHARE_POLICY_TRUE,		/**< The SPKObject is forced to be shared */		
		SHARE_POLICY_FALSE		/**< The SPKObject is forced to be unshared */
	};

	namespace IO { class IOManager; }


    class SPK_PREFIX SPKObjectMeta
    {
    public:
        virtual void fillAttributeList(std::vector<IO::Attribute>& attributes) const = 0;
    };

	/** @brief The base class of all SPARK objects */
    class SPK_PREFIX SPKObject : public SPKObjectMeta
	{
	template<typename T> friend class Ref;

	SPK_START_DESCRIPTION
	SPK_ATTRIBUTE("name",ATTRIBUTE_TYPE_STRING)
	SPK_ATTRIBUTE("shared",ATTRIBUTE_TYPE_BOOL)
	SPK_END_DESCRIPTION

	public :

		/**
		* @brief Copies a SPK Object
		* @param : ref : The SPK object to copy
		* @return a SPK object which is a copy of ref
		*/
		template<typename T>
		static Ref<T> copy(const Ref<T>& ref);

		virtual ~SPKObject();

		///////////////
		// Reference //
		///////////////

		/**
		* @brief Gets the number of references of this object
		* When the number of references reaches 0, the object is destroyed.
		* @return the number of references
		*/
		unsigned int getNbReferences() const;

		/**
		* Tells whether this object is shared or not
		* During a deep copy, a referenced shared object will not be copied but only its reference will.
		* @return true if the object is shared, false otherwise
		*/
		bool isShared() const;

		/**
		* Sets whether this object is shareable or not
		* Note that some type of objects are not shareable
		* @param shared : true to make this obkect shared, false not to
		*/
		void setShared(bool shared);

		//////////
		// Name //
		//////////

		/**
		* @brief Sets the name of this object
		* @param name : the name
		*/
		void setName(const std::string& name);

		/**
		* @brief Gets the name of this object
		* @return the name
		*/
		const std::string& getName() const;

		/**
		* @brief Traverses this object to find an object with the given name
		*
		* The first object found with the given name is returned.<br>
		* This object is always checked first.<br>
		* If no object with the given name is found, NULL is returned.<br>
		*
		* @param name : the name of the object to find
		* @return : the object with the given name or null
		*/
        virtual Ref<SPKObject> findByName(const std::string& name);

		///////////////////
		// Serialization //
		///////////////////

		/**
		* @brief Create a descriptor for this object
		* The descriptor created has no attribute values set.<br>
		* Use exportAttributes, if you need a descriptor with set attributes.
		* @return a descriptor with empty attributes of this type of object
		*/
		IO::Descriptor createDescriptor() const;

		/**
		* @brief Imports the attributes of a descriptor and use it to set up this object
		* @param descriptor : The descriptor used to set up this object
		*/
		void importAttributes(const IO::Descriptor& descriptor);

		/**
		* @brief Exports the attribute of this object in a descriptor
		* @return A descriptor representing the object
		*/
		IO::Descriptor exportAttributes() const;

		/**
		* @brief Gets the class name of this object
		* @return the class name
		*/
		virtual std::string getClassName() const = 0;

	protected :

		// abstract class
		SPKObject(SharePolicy SHARE_POLICY = SHARE_POLICY_CUSTOM);
		SPKObject(const SPKObject& obj);

        virtual void innerImport(const IO::Descriptor& descriptor);
        virtual void innerExport(IO::Descriptor& descriptor) const;

		template<typename T>
		Ref<T> copyChild(const Ref<T>& ref) const;

	private :

		std::string name;

		unsigned int nbReferences;

		const SharePolicy SHARE_POLICY;
		bool shared;

		// The copy buffer is used to be able to correctly perform a deep copy of objects. If an object is present more than once is the hierarchy it will be copied only once
		// The choice to have a field that is used only for the copy was made because the memory overhead is neglictible and the other possible choices were not satisfying :
		// * Having a static copyBuffer made the copy not thread safe (As concurrent copy of object would make concurrent read/write on the buffer)
		// * Passing the copyBuffer to methods was too dirty and messed up the interface (Impossible to use the copy constructor anymore)
		// Note that with this method the copy of the same object remains not thread safe but the copy of different object is
		mutable std::map<SPKObject*,SPKObject*>* copyBuffer;

		virtual Ref<SPKObject> clone() const = 0;
	};

	inline unsigned int SPKObject::getNbReferences() const
	{
		return nbReferences;
	}

	inline bool SPKObject::isShared() const
	{
		return shared;
	}

	inline void SPKObject::setName(const std::string& name)
	{
		this->name = name;
	}

	inline const std::string& SPKObject::getName() const
	{
		return name;
	}

	inline Ref<SPKObject> SPKObject::findByName(const std::string& name)
	{
		return getName().compare(name) == 0 ? this : NULL;
	}

	template<typename T>
	Ref<T> SPKObject::copy(const Ref<T>& ref)
	{
		if (!ref)
			return ref;

		if (ref->copyBuffer != NULL)
		{
			SPK_LOG_FATAL("The object is already being copied and cannot be copied more than once at the same time");
			return SPK_NULL_REF;
		}

		ref->copyBuffer = new std::map<SPKObject*,SPKObject*>(); // Creates the copy buffer to allow correct copy of underlying SPARK objects
        Ref<T> clone = staticCast<T>(staticCast<SPKObject>(ref)->clone());
		delete ref->copyBuffer; // Deletes the copy buffer used for the copy
		ref->copyBuffer = NULL;
		return clone;
	}

	template<typename T>
	Ref<T> SPKObject::copyChild(const Ref<T>& ref) const
	{
		if (!ref)
			return SPK_NULL_REF;

		if (ref->isShared())
			return ref;

		if (copyBuffer == NULL)
		{
			SPK_LOG_FATAL("The copy buffer of the object is NULL while copying the object");
			return SPK_NULL_REF;
		}

		std::map<SPKObject*,SPKObject*>::const_iterator it = copyBuffer->find(ref.get());
		if (it != copyBuffer->end())
			return dynamic_cast<T*>(it->second);

		ref->copyBuffer = copyBuffer; // Sets the copyBuffer of the child to the copyBuffer of the parent
        Ref<SPKObject> clone = staticCast<SPKObject>(ref)->clone();
		ref->copyBuffer = NULL; // Removes the reference to the copy buffer (the copy buffer is deleted by the top level copied object)

		copyBuffer->insert(std::make_pair(ref.get(),clone.get()));
        return staticCast<T>(clone);
	}
}

#endif
