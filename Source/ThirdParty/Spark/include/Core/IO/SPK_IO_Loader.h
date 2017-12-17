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

#ifndef H_SPK_IO_LOADER
#define H_SPK_IO_LOADER

#include <list>

namespace SPK
{
	class System;

namespace IO
{
	/** @brief An abstract class to load an entire particle system from a resource */
	class SPK_PREFIX Loader
	{
	public :

		//////////////////////////////
		// Constructor / Destructor //
		//////////////////////////////

		virtual ~Loader() {}

		/////////////////////
		// Loading methods //
		/////////////////////

		/**
		* @brief Loads a system from an input stream
		* @param is : the input stream from which to load the system
		* @return the loaded system or NULL if loading failed
		*/
        Ref<System> load(std::istream& is, const std::string &path = 0) const;

		/**
		* @brief Loads a system from a file
		* @param path : the path from which to load the file
		* @return the loaded system or NULL if loading failed
		*/
		Ref<System> load(const std::string& path) const;

        /**
        * @brief Loads a system from a data buffer
        * @param data : the data buffer that contains data to parse
        * @param datasize : the data buffer size
        * @return the loaded system or NULL if loading failed
        */
        Ref<System> loadFromBuffer(const char * data, unsigned int datasize);

		////////////////////
		// nested classes //
		////////////////////

		class Graph; // Forward declaration for friendship

		class Node
		{
		friend class Graph;
		friend class Loader;

		public :

			const Ref<SPKObject>& getObject() const	{ return object; }
			Descriptor& getDescriptor()				{ return descriptor; }

		private :

			Node(const Ref<SPKObject>& object);

			Ref<SPKObject> object;
			Descriptor descriptor;
		};

		class Graph
		{
		friend class Loader;

		public :

			bool addNode(size_t key,const std::string& name);
			bool validateNodes();

			Node* getNode(size_t key) const { return getNode(key,true); }

		private :

			Graph();
			~Graph();

			std::map<size_t,Node*> key2Ptr;
			std::list<Node*> nodes;

			bool nodesValidated;
			Ref<System> system;

			Node* getNode(size_t key,bool withCheck) const; // inner getNode that allows to bypass validation check
			void destroyAllNodes();

			const Ref<System>& finalize();
		};

	private :

		/**
		* @brief The inner load method to be implemented in derived classes
		* @param is : the input stream from which to load the syste
		* @param graph : the graph that allows to build the system
		* @return true if the loading was successful, false if it failed
		*/
        virtual bool innerLoad(std::istream& is,Graph& graph,const std::string& path=0) const = 0;

        /**
        * @brief The inner load buffer method to be implemented in derived classes
        * @param graph : the graph that allows to build the system
        * @param data : the data buffer
        * @param datasize : the data buffer size
        * @return true if the loading was successful, false if it failed
        */
        virtual bool innerLoadFromBuffer(Graph& graph, const char * data, unsigned int datasize) = 0;
	};
}}

#endif
