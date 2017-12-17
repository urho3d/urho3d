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

#ifndef H_SPK_INTERPOLATOR
#define H_SPK_INTERPOLATOR

namespace SPK
{
	class Group;
	class Particle;

	/** @brief An abstract generic class that allows to interpolate data */
	template<typename T>
	class Interpolator :	public SPKObject,
							public DataHandler
	{
	friend class Group;

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(SPKObject)
	SPK_END_DESCRIPTION

	public :

		virtual  ~Interpolator() {}

	protected :

		/**
		* @brief Constructor of interpolator
		* @param NEEDS_DATASET : true if the interpolator needs additional data, false otherwise
		*/
		Interpolator(bool NEEDS_DATASET);

		/**
		* @brief A helper method that linearly interpolates a value
		* The result is computed this way : <i>result = start * (1.0f - ratio) + end * ratio</i>
		* @param result : A reference to the result of the interpolation
		* @param start : the start value used for the interpolation
		* @param end : the end value used for the interpolation
		* @param ratio : the ratio of the interpolation (between 0.0f and 1.0f)
		*/
		void interpolateParam(T& result,const T& start,const T& end,float ratio) const;
		
	private :

		/**
		* @brief Interpolates the given data of the particles of a group
		* 
		* This is a pure virtual method that must be overriden in inherited interpolators.<br>
		* The array of data passed must be interpolated. The number of data to interpolate is the number of active particles of the group.<br>
		* If NEEDS_DATASET was set to true, a dataset is passed to the method, else NULL is passed.
		*
		* @param data : the array of data to interpolate
		* @param group : the group from which to interpolate the data
		* @param dataSet : the associated dataset of the pair interpolator/group. Will be NULL if NEEDS_DATASET is false
		*/
		virtual void interpolate(T* data,Group& group,DataSet* dataSet) const = 0;

		/**
		* @brief Initializes the given data for the given particle
		* This is a pure virtual method that must be overriden in inherited interpolators.<br>
		* @param data : the data to initialize
		* @param particle : the particle holding the data that must be initialized
		* @param dataset : the associated dataset of the pair interpolator/group. Will be NULL if NEEDS_DATASET is false 
		*/
		virtual void init(T& data,Particle& particle,DataSet* dataSet) const = 0;
	};

	typedef Interpolator<Color> ColorInterpolator; /**< @brief Abstract interpolator of colors */
	typedef Interpolator<float> FloatInterpolator; /**< @brief Abstract interpolator of floats */

	template<typename T>
	inline Interpolator<T>::Interpolator(bool NEEDS_DATASET) :
		SPKObject(),
		DataHandler(NEEDS_DATASET)
	{}

	template<typename T>
	inline void Interpolator<T>::interpolateParam(T& result,const T& start,const T& end,float ratio) const
	{
		result = start * (1.0f - ratio) + end * ratio;
	}

	// Specialization for Color
	template<>
	inline void Interpolator<Color>::interpolateParam(Color& result,const Color& start,const Color& end,float ratio) const
	{
		result.interpolate(start,end,ratio);
	}
}

#endif
