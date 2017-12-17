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

#ifndef H_SPK_IO_SPKLOADER
#define H_SPK_IO_SPKLOADER

namespace SPK
{
namespace IO
{
	/** @brief A class to deserialize a System from a spk format stream */
	class SPK_PREFIX SPKLoader : public Loader
	{
	private :

		static const char MAGIC_NUMBER[3];
		static const char VERSION;

		static const size_t DATA_LENGTH_OFFSET;
		static const size_t HEADER_LENGTH;

        virtual bool innerLoad(std::istream& is,Graph& graph,const std::string& path=0) const override;
        virtual bool innerLoadFromBuffer(Graph& graph, const char * data, unsigned int datasize) override;

		bool readObject(Node& node,const Graph& graph,const IOBuffer& data) const;
		bool readAttribute(Attribute& attrib,const Graph& graph,const IOBuffer& data) const;
		Ref<SPKObject> readReference(const Graph& graph,const IOBuffer& data) const;

		template<class T>
		void setAttributeValues(Attribute& attrib,const IOBuffer& data) const;
	};

	template<class T>
	void SPKLoader::setAttributeValues(Attribute& attrib,const IOBuffer& data) const
	{
		size_t nbValues = data.get<uint32>();
		T* buffer = SPK_NEW_ARRAY(T,nbValues);
		for (size_t i = 0; i < nbValues; ++i)
			buffer[i] = data.get<T>();
		attrib.setValues(buffer,nbValues);
		SPK_DELETE_ARRAY(buffer);
	}
}}

#endif
