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

#ifndef H_SPK_IO_SAVER
#define H_SPK_IO_SAVER

#include <list>

namespace SPK
{
namespace IO
{
	/** @brief An abstract class to save an entire particle system in a resource */
	class SPK_PREFIX Saver
	{
	public :

		//////////////////////////////
		// Constructor / Destructor //
		//////////////////////////////

		virtual ~Saver() {}

		////////////////////
		// Saving methods //
		////////////////////

		/**
		* @brief Saves a system to an output stream
		* @param os : the output stream to save the system to
		* @return true if the system has been successfully saved, false if not
		*/
        bool save(std::ostream& os, const Ref<System>& system, const std::string &filepath=0) const;

		/**
		* @brief Saves a system in a file
		* @param path : the path of the file to save the system in
		* @return true if the system has been successfully saved, false if not
		*/
        bool save(const std::string& path, const Ref<System>& system, const std::string &filepath=0) const;

		////////////////////
		// Nested classes //
		////////////////////

		class Graph; // Forward declaration for friendship

		class Node
		{
		friend class Graph;
		friend class Saver;
		friend bool compareNodePriority(const Node*,const Node*);

		public :

			size_t getReferenceID() const			{ return refID; }
			const Descriptor& getDescriptor() const	{ return descriptor; }
			size_t getNbReferences() const			{ return nbReferences; }
			void markAsProcessed() const			{ processed = true; }
			bool isProcessed() const				{ return processed; }

		private :

			Node(const Descriptor& descriptor);

			size_t refID;
			mutable bool processed;
			size_t nbReferences;
			Descriptor descriptor;
			size_t priority;
		};

		class Graph
		{
		friend class Saver;

		public :

			~Graph();

			Node* getNode(const Ref<SPKObject>& ptr);
			Node* getNextNode();
			size_t getNbNodes()	{ return nodes.size(); }

		private :

			Graph();
			Graph(const Graph&);

			std::map<const SPKObject*,Node*> ptr2Nodes;
			std::list<Node*> nodes;

			mutable std::list<Node*>::iterator currentPosIt;
			mutable bool posInitialized;

			Node* createNode(const Descriptor& descriptor);
		};

	private :

		/**
		* @brief The inner save method to be implemented in derived classes
		* @param os : the output stream to save the system to
		* @param graph : the graph that contains the hierarchy of nodes to save
		* @return true if the saving was successful, false if it failed
		*/
        virtual bool innerSave(std::ostream& os,Graph& graph,const std::string& path=0) const = 0;

		static void constructGraph(Graph& graph,const System* system);
		static void constructNode(Graph& graph,const SPKObject* object,size_t level);
	};
}}

#endif
