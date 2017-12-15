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

#ifndef H_SPK_IO_SPKSAVER
#define H_SPK_IO_SPKSAVER

namespace SPK
{
namespace IO
{
	/** @brief A class to serialize a System in a spk format stream */
	class SPK_PREFIX SPKSaver : public Saver
	{
	private :

		static const char MAGIC_NUMBER[3];
		static const char VERSION;

		static const size_t DATA_LENGTH_OFFSET;
		static const size_t HEADER_LENGTH;

        virtual bool innerSave(std::ostream& os,Graph& graph,const std::string &filepath=0) const override;

		bool writeObject(IOBuffer& buffer,const Descriptor& desc,Graph& graph) const;
		bool writeAttribute(IOBuffer& buffer,const Attribute& attrib,Graph& graph) const;
	};	
}}

#endif
