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

#ifndef H_SPK_IOMANAGER
#define H_SPK_IOMANAGER

#include <iostream>
#include <fstream>
#include <map>
#include <string>

namespace SPK
{
namespace IO
{
	class SPK_PREFIX IOManager
	{
	public :

		static IOManager& get();

		void unregisterAll();

		void registerIOConverters();
		void registerCoreObjects();

		template<typename T> void registerObject();
		template<typename T> void unregisterObject();
		template<typename T> bool isObjectRegistered() const;

		void registerLoader(const std::string& ext,Loader* loader);
		void unregisterLoader(const std::string& ext);
		Loader* getLoader(const std::string& ext) const;

		void registerSaver(const std::string& ext,Saver* saver);
		void unregisterSaver(const std::string& ext);
		Saver* getSaver(const std::string& ext) const;

        Ref<System> load(const std::string& path) const;
		Ref<System> load(const std::string& ext,std::istream& is) const;
        Ref<System> loadFromBuffer(const std::string& ext, char * data, unsigned int size) const;

		bool save(const std::string& path,const Ref<System>& system) const;
		bool save(const std::string& ext,std::ostream& os,const Ref<System>& system) const;

	private :

		typedef Ref<SPKObject> (*createSerializableFn)();

		std::map<std::string,createSerializableFn> registeredObjects;
		std::map<std::string,Loader*> registeredLoaders;
		std::map<std::string,Saver*> registeredSavers;

		IOManager();
		IOManager(const IOManager&) {}
		IOManager& operator=(const IOManager&);

		static std::string formatExtension(const std::string& ext);
		static std::string getExtension(const std::string& path);

		template<typename T> static void registerGeneric(const std::string& ext,T* t,std::map<std::string,T*>& table);
		template<typename T> static void unregisterGeneric(const std::string& ext,std::map<std::string,T*>& table);
		template<typename T> static T* getGeneric(const std::string& ext,const std::map<std::string,T*>& table);

		/////////////////////////////////////
		// Helper methods to build objects //
		/////////////////////////////////////

		friend class Loader::Graph;
		Ref<SPKObject> createObject(const std::string& id) const;
		void linkGroup(Group& group,System& system) const;
	};

	template<typename T> void IOManager::registerObject()
	{
		const std::string name = T::asName();
		if (registeredObjects.find(name) != registeredObjects.end())
			SPK_LOG_WARNING("IOManager::registerSerializable<T> - " << name << " is already registered");

		registeredObjects.insert(std::make_pair(name,&(T::createSerializable)));
	}

	template<typename T> void IOManager::unregisterObject()
	{
		const std::string name = T::getSerializableName();
		std::map<std::string,createSerializableFn>::iterator it = registeredObjects.find(name);
		if (it == registeredObjects.end())
		{
			SPK_LOG_WARNING("IOConverter::unregisterSerializable<T> - " << name << " is not registered and therefore cannot be unregistered");
		}
		else
			registeredObjects.erase(it);
	}

	template<typename T> inline bool IOManager::isObjectRegistered() const
	{
		return registeredObjects.find(T::getSerializableName()) != registeredObjects.end();
	}

	inline void IOManager::registerLoader(const std::string& ext,Loader* loader) { registerGeneric<Loader>(ext,loader,registeredLoaders); }
	inline void IOManager::unregisterLoader(const std::string& ext) { unregisterGeneric<Loader>(ext,registeredLoaders); }
	inline Loader* IOManager::getLoader(const std::string& ext) const { return getGeneric<Loader>(ext,registeredLoaders); }

	inline void IOManager::registerSaver(const std::string& ext,Saver* saver) { registerGeneric<Saver>(ext,saver,registeredSavers); }
	inline void IOManager::unregisterSaver(const std::string& ext) { unregisterGeneric<Saver>(ext,registeredSavers); }
	inline Saver* IOManager::getSaver(const std::string& ext) const { return getGeneric<Saver>(ext,registeredSavers); }

	template<typename T>
	void IOManager::registerGeneric(const std::string& ext,T* t,std::map<std::string,T*>& table)
	{
		const std::string name = formatExtension(ext);
		typename std::map<std::string,T*>::iterator it = table.find(name);
		if (it != table.end())
		{
			SPK_LOG_WARNING("IOManager::registerGeneric<T> - " << name << " is already registered. Previous one is overriden");
			SPK_DELETE(it->second);
			table.erase(it);
		}

		table.insert(std::make_pair(name,t));
	}

	template<typename T>
	void IOManager::unregisterGeneric(const std::string& ext,std::map<std::string,T*>& table)
	{
		const std::string name = formatExtension(ext);
		typename std::map<std::string,T*>::iterator it = table.find(name);
		if (it == table.end())
		{
			SPK_LOG_WARNING("IOManager::unregisterGeneric<T> - " << name << " is not registered and therefore cannot be unregistered")
		}
		else
		{
			SPK_DELETE(it->second);
			table.erase(it);
		}
	}

	template<typename T>
	T* IOManager::getGeneric(const std::string& ext,const std::map<std::string,T*>& table)
	{
		const std::string name = formatExtension(ext);
		typename std::map<std::string,T*>::const_iterator it = table.find(name);
		return it != table.end() ? it->second : NULL;
	}
}}
#endif
