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

#include <iostream>
#include <fstream>
#include <ctime>

#include <SPARK_Core.h>

namespace SPK
{
namespace IO
{
    Ref<System> Loader::load(std::istream& is,const std::string& path) const
	{
		clock_t startTime = std::clock();

		Graph graph;
        if (innerLoad(is,graph,path))
		{
			const Ref<System>& system = graph.finalize();
			unsigned int loadTime = static_cast<unsigned int>(((std::clock() - startTime) * 1000) / CLOCKS_PER_SEC);
			SPK_LOG_INFO("The system has been successfully loaded in " << loadTime << "ms");
			return system;
		}
		else
		{
			SPK_LOG_INFO("An error occurred while loading the System");
			return SPK_NULL_REF;
		}
	}

	Ref<System> Loader::load(const std::string& path) const
	{
		std::ifstream is(path.c_str(),std::ios::in | std::ios::binary);
		if (is)
		{
            Ref<System> system = load(is,path);
			is.close();
			return system;
		}
		else
		{
			SPK_LOG_ERROR("Loader::load(const std::string&) - Impossible to read from the file " << path);
			return SPK_NULL_REF;
		}
	}

    Ref<System> Loader::loadFromBuffer(const char * data, unsigned int datasize)
    {
        clock_t startTime = std::clock();

        Graph graph;
        if (innerLoadFromBuffer(graph,data,datasize))
        {
            const Ref<System>& system = graph.finalize();
            unsigned int loadTime = static_cast<unsigned int>(((std::clock() - startTime) * 1000) / CLOCKS_PER_SEC);
            SPK_LOG_INFO("The system has been successfully loaded in " << loadTime << "ms");
            return system;
        }
        else
        {
            SPK_LOG_INFO("An error occurred while loading the System");
            return SPK_NULL_REF;
        }
    }

	Loader::Node::Node(const Ref<SPKObject>& object) :
		object(object),
		descriptor(object->createDescriptor())
	{}

	Loader::Graph::Graph() : nodesValidated(false) {}

	Loader::Graph::~Graph()
	{
		for (std::list<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
			SPK_DELETE(*it);
	}

	bool Loader::Graph::addNode(size_t key,const std::string& name)
	{
		SPK_ASSERT(!nodesValidated,"Loader::Graph::addNode(size_t,string) - Graph has been processed. Nodes cannot be added any longer");

		Ref<SPKObject> object = IOManager::get().createObject(name);

		if (!object)
		{
			SPK_LOG_ERROR("Loader::Graph::addNode(size_t,string) - The type \"" << name << "\" is not registered");
			return false;
		}

		if (getNode(key,false) != NULL)
		{
			SPK_LOG_ERROR("Loader::Graph::addNode(size_t,string) - duplicate key for nodes : " << key);
			return false;
		}

		Node* node = SPK_NEW(Node,object);
		nodes.push_back(node);
		key2Ptr.insert(std::make_pair(key,node));
		return true;
	}

	bool Loader::Graph::validateNodes()
	{
		size_t nbSystems = 0;
		for (std::list<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
            Ref<SPKObject> objectRef = staticCast<SPKObject>((*it)->object);
            if (objectRef && objectRef->getClassName() == "System")
			{
                Ref<System> systemRef = staticCast<System>((*it)->object);
				system = systemRef;
				++nbSystems;
			}
		}

		if (nbSystems != 1) // One and only one system is allowed
		{
			SPK_LOG_ERROR("Loader::Graph::validateNodes() - One and only one system is allowed in the graph");
			return false;
		}

		return nodesValidated = true;
	}

	const Ref<System>& Loader::Graph::finalize()
	{
		SPK_ASSERT(nodesValidated,"Loader::Graph::finalize() - Graph has not been validated before finalization");

		// Imports all descriptors to set up the objects
		for (std::list<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
			(*it)->object->importAttributes((*it)->descriptor);

		return system;
	}

	Loader::Node* Loader::Graph::getNode(size_t key,bool withCheck) const
	{
		if (withCheck)
			SPK_ASSERT(nodesValidated,"Loader::Graph::getNode(size_t,boolean) - Graph has not been validated, nodes cannot be gotten");

		std::map<size_t,Node*>::const_iterator it = key2Ptr.find(key);
		if (it != key2Ptr.end())
			return it->second;
		else
			return NULL;
	}
}}
