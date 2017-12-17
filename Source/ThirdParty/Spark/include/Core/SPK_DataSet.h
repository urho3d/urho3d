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

#ifndef H_SPK_DATASET
#define H_SPK_DATASET

/**
* @brief A convenience macro to get a Data of a given type from a Dataset
* @param type : type of the data (used to cast the data)
* @param dataSetPtr : pointer to the dataset holding the data
* @param index : the index onf the data in the dataset
* @return a reference to the data at the given index of the dataset casted in the right type
*/
#define SPK_GET_DATA(type,dataSetPtr,index) static_cast<type&>(*(dataSetPtr)->getData(index))

namespace SPK
{
	/**
	* @brief An abstract class representing additional data for particles.
	*
	* This class is meant to be derived in order to represent additional data attached to group of particles
	* that can be used by DataHandler objects (typically modifiers or interpolators).<br>
	* <br>
	* A data has also a flag that can be used to check the integrity of the data.
	*/
	class Data
	{
	friend class Group;
	friend class DataSet;

	public :

		/**
		* @brief Sets the flag of the data
		* @param flag : the flag of the data
		*/
		void setFlag(long flag);

		/**
		* @brief Gets the flag of the data
		* @return the flag of the data
		*/
		long getFlag() const;

	protected :

		Data();
		virtual  ~Data() {}

	private :

		long flag;

		/**
		* @brief Swaps the additional data of 2 particles
		* This pure virtual method must be implemented in children.
		* @param index0 : index of the first particle
		* @param index1 : index of the second particle
		*/
		virtual void swap(size_t index0,size_t index1) = 0;
	};

	/**
	* @brief A class that is used to attach a set of Data to a DataHandler.
	*
	* datasets are handled by groups and passed to internal datahandlers (typically modifiers and interpolators) when needed.<br> 
	* datasets life cycles (creation and destruction) are handled by groups.
	*/
	class SPK_PREFIX DataSet
	{
	friend class Group;
	friend class DataHandler;

	public :

		DataSet();
		~DataSet();

		/**
		* @brief Inializes the data with the given number of slots of Data
		* Any previously held data is destroyed.<br>
		* This reserves the slots of data but does not fill them with any data.
		* @param nbData : the number of data this dataset can hold
		*/
		void init(size_t nbData);

		/**
		* @brief Sets the data for a given data slot
		* @param index : the slot index where to store the data
		* @param data : the data to store
		*/
		void setData(size_t index,Data* data);

		/**
		* @brief Gets the data at a given slot
		* @param index : the index of the slot from where to retrieve the data
		* @return the data in the given slot
		*/
		Data* getData(size_t index);

		/**
		* @brief Gets the data at a given slot
		* This is the constant version of the method
		* @param index : the index of the slot from where to retrieve the data
		* @return the data in the given slot
		*/
		const Data* getData(size_t index) const;

		/**
		* @brief Tells whether this dataset is initialized
		* Typically the dataset used by a DataHandler is considered as initialized after a call to DataHandler::createData(DataSet&,const Group&) const
		* @return true if the data set is initialized, false if not
		*/
		bool isInitialized() const;

		/**
		* @brief Destroys the data of a particular slot
		* @param index : the index of the slot in which to destroy the data
		*/
		void destroyData(size_t index);

		/** @brief Destroys all the data held */
		void destroyAllData();

	private :

		Data** dataArray;
		size_t nbData;
		bool initialized;

		void setInitialized();
		void swap(size_t index0,size_t index1);
	};

	inline Data::Data() :
		flag(0)
	{}

	inline void Data::setFlag(long flag)
	{
		this->flag = flag;
	}

	inline long Data::getFlag() const
	{
		return flag;
	}

	inline DataSet::DataSet() :
        dataArray(NULL),
		nbData(0),
        initialized(false)
	{}

	inline DataSet::~DataSet()
	{
		destroyAllData();
		SPK_DELETE_ARRAY(dataArray);
	}

	inline void DataSet::setInitialized()
	{
		initialized = true;
	}

	inline Data* DataSet::getData(size_t index)
	{
		return dataArray[index];
	}

	inline const Data* DataSet::getData(size_t index) const
	{
		return dataArray[index];
	}

	inline bool DataSet::isInitialized() const
	{
		return initialized;
	}

	inline void DataSet::destroyData(size_t index)
	{
		setData(index,NULL);
	}

	inline void DataSet::swap(size_t index0,size_t index1)
	{
		for (size_t i = 0; i < nbData; ++i)
			dataArray[i]->swap(index0,index1);
	}
};

#endif
