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

#ifndef H_SPK_DATAHANDLER
#define H_SPK_DATAHANDLER

namespace SPK
{
	class Group;

	/**
	* @brief An interface that allows an object to handle and use some additional data attached to particles
	* 
	* When a class dealing with particles needs to maintain an additional set of data in extention to the already provided parameters,
	* it should inherited from DataHandler.<br>
	* <br>
	* Datasets are maintained by groups and passed to datahandlers for update and use. Each datahandler has its own dataset within a given group<br>
	* While groups are responsible of the creation and destruction of datasets, datahandler are responsible for the creation and update of the data within
	* the datasets.
	* <br>
	* This allows to theorically extends particles to infinity as the structure of a particle is derived from the datahandlers updating/needing it.<br>
	* <br>
	* Note that if a datahandler is created with its NEEDS_DATASET set to false, it will then behave as if it was not a datahandler.
	*/
	class DataHandler
	{
	friend class Group;

	public :

		virtual  ~DataHandler() {}

		/**
		* @brief Tells if the datahandler needs some additional data or not
		* @return true if the datahandler needs additional data or not
		*/
		bool needsDataSet() const;

	protected :

		/**
		* @brief Constructor of datahandler
		* Note that if a datahandler is created with its NEEDS_DATASET set to false, it will then behave as if it was not a datahandler.
		* @param NEEDS_DATASET : true if the datahandler needs additional data, false if not
		*/
		DataHandler(bool NEEDS_DATASET); // abstract class

		/**
		* @brief Creates the data within the passed dataset
		*
		* This method is called by the engine before the datahandler needs some additional data.<br>
		* After this method has been called, the dataset for the given couple datahandler/group is set as initialized.<br>
		* <br>
		* Note that by default, the method is implemented empty as it will only be used by datahandler that needs dataset.
		*
		* @param dataSet : the dataset reserved by the passed group for this datahandler
		* @param group : the group that is passing its dataset
		*/
		virtual  void createData(DataSet& dataSet,const Group& group) const {}

		/**
		* @brief Checks the integrity of data within the passed dataset
		*
		* This method is called by the engine each time before the datahandler will need to use the dataset.<br> 
		* This method is responsible for checking the integrity of the data within the dataset.<br>
		* If data is invalid when entering this method, they must be valid at exit.<br>
		* <br>
		* Note that by default, the method is implemented empty as it will only be used by datahandler that needs dataset.
		*
		* @param dataSet : the dataset reserved by the passed group for this datahandler
		* @param group : the group that is passing its dataset
		*/
		virtual  void checkData(DataSet& dataSet,const Group& group) const {}

		void prepareData(const Group& group,DataSet* dataSet) const;

	private :

		const bool NEEDS_DATASET;
	};

	inline DataHandler::DataHandler(bool NEEDS_DATASET) :
		NEEDS_DATASET(NEEDS_DATASET)
	{}

	inline bool DataHandler::needsDataSet() const
	{
		return NEEDS_DATASET;
	}

	inline void DataHandler::prepareData(const Group& group,DataSet* dataSet) const
	{
		if (dataSet != NULL)
		{
			if (!dataSet->isInitialized())
				createData(*dataSet,group);
			else
				checkData(*dataSet,group);

			dataSet->setInitialized();
		}
	}
};

#endif
