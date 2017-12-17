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

#ifndef H_SPK_IO_XMLSAVER
#define H_SPK_IO_XMLSAVER

#ifndef SPK_NO_XML

#include <sstream>

namespace pugi
{
	class xml_node;
	class xml_attribute;
}

namespace SPK
{
namespace IO
{
	/** @brief Constants defining the rule to layout values when saving in XML */
	enum XMLValueLayout
	{
		XML_VALUE_LAYOUT_AS_ATTRIBUTE,	/**< @brief <attrib id="..." value="..."> */
		XML_VALUE_LAYOUT_AS_TEXT,		/**< @brief <attrib id="...">...</attrib> */
	};

	/** @brief Constants defining the rule to layout references when saving in XML */
	enum XMLReferenceRule
	{
		XML_REFERENCE_RULE_WHEN_NEEDED,			/**< References are only used when the SPKObject is referenced more than once. If so the SPKObject is written at the root of the XML document */
		XML_REFERENCE_RULE_FORCED,				/**< References are always used. The SPKObject is always written at the root of the XML document */
		XML_REFERENCE_RULE_DESCRIBED_AT_FIRST,	/**< The SPKObject is written the first time it is referenced and then references are used */
	};


	/** @brief A struct that defines the layout of a XML document to save */
	struct XMLLayout
	{
		std::string indent;					/**< @brief the string used for an indent ("\t" by default) */
		bool lineBreak;						/**< @brief true to include line breaks in the output */
		XMLValueLayout valueLayout;			/**< @brief defines how to layout values (XML_VALUE_LAYOUT_AS_ATTRIBUTE by default)*/
		XMLReferenceRule referenceRule;		/**< @brief defines how to layout references (XML_REFERENCE_RULE_WHEN_NEEDED by default)*/

		/** @brief Default constructor */
		XMLLayout() :
			indent("\t"),
			lineBreak("\n"),
			valueLayout(XML_VALUE_LAYOUT_AS_ATTRIBUTE),
			referenceRule(XML_REFERENCE_RULE_WHEN_NEEDED)
		{}
	};

	/** @brief A class to serialize a System in an XML format */
	class SPK_PREFIX XMLSaver : public Saver
	{
	public :

		/**
		* @brief Sets the author of the systems to save
		* The author will be written at the beginning of the XML document as a comment.
		* @param author : The author of the systems to save
		*/
		void setAuthor(const std::string& author)	{ this->author = author; }

		/**
		* @brief Sets the layout of the saver
		* The layout will be used each time a document is written.
		* @param layout : the layout rules
		*/
		void setLayout(const XMLLayout& layout)		{ this->layout = layout; }

		/**
		* @brief Gets the layout of the saver
		* @return the layout rules
		*/
		XMLLayout& getLayout()						{ return layout; }

		/**
		* @brief Gets the layout of the saver
		* Const version of getLayout()
		* @return the layout rules
		*/
		const XMLLayout& getLayout() const			{ return layout; }

	private :

		XMLLayout layout;
		std::string author;

        virtual bool innerSave(std::ostream& os, Graph& graph, const std::string &filepath=0) const override;

		bool writeNode(pugi::xml_node& parent,const Node& node,Graph& graph) const;
		bool writeObject(pugi::xml_node& parent,const Ref<SPKObject>& object,Graph& graph,bool refInTag) const;
		void writeValue(pugi::xml_node& attrib,const std::string& value) const;
		void writeRef(pugi::xml_node& attrib,const Node& node) const;

		static pugi::xml_attribute getAttribute(pugi::xml_node& n, const std::string& name);
		template<typename T> static std::string format(const T& value);
		template<typename T> static std::string formatArray(const std::vector<T>& value);
	};

	template<typename T>
	std::string XMLSaver::format(const T& value)
	{
		std::ostringstream os;
		os << std::boolalpha;
		os << value;
		return os.str();
	}

	template<typename T>
	std::string XMLSaver::formatArray(const std::vector<T>& values)
	{
		std::ostringstream os;
		os << std::boolalpha;
		for (size_t i = 0; i < values.size(); ++i)
		{
			os << values[i];
			if (i != values.size() - 1)
				os << ';';
		}
		return os.str();
	}
}}

#endif
#endif
