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

#ifndef H_SPK_ARRAYDATA
#define H_SPK_ARRAYDATA

#include <algorithm> // for std:swap

namespace SPK
{
	/**
	* @brief A class that holds an array of generic type per particle.
	*
	* Each particle can hold n variable of the given type. the whole data is stored in a unique array of size : <br>
	* <i>max number of particles * number of variables per particles</i>
	*/
	template<typename T>
	class ArrayData : public Data
	{
	public :
		
		/**
		* @brief Constructor of arraydata
		* @param nbParticles : the maximum number of particles
		* @param sizePerParticle : the number of variable of type T per particle
		*/
		ArrayData<T>(size_t nbParticles,size_t sizePerParticle);

		/**
		* @brief Gets the inner array of data
		* @return the inner array of data
		*/
		T* getData();

		/**
		* @brief Gets the inner array of data
		* This is the constant version of the method
		* @return the inner array of data
		*/
		const T* getData() const;
		
		/**
		* @brief Gets the array of data for a given particle
		* @return the array of data for a given particle
		*/
		T* getParticleData(size_t index);

		/**
		* @brief Gets the array of data for a given particle
		* This is the constant version of the method
		* @return the array of data for a given particle
		*/
		const T* getParticleData(size_t index) const;

		/**
		* @brief Gets the element in the inner array at the given index
		* @param index : the index from which to get the element
		* @return the element stored at the index
		*/ 
		T& operator[](size_t index);

		/**
		* @brief Gets the element in the inner array at the given index
		* This is the constant version of the method
		* @param index : the index from which to get the element
		* @return the element stored at the index
		*/ 
		const T& operator[](size_t index) const;

		/**
		* @brief Gets the total number of elements in the inner array
		* This method returns <i>max number of particles * number of variables per particles</i>
		* @return the total number of elements in the inner array
		*/
		size_t getTotalSize() const;

		/**
		* @brief Gets the number of elements per particle
		* @return the number of elements per particle
		*/
		size_t getSizePerParticle() const;

	private :

		T* data;
		size_t totalSize;
		size_t sizePerParticle;

		~ArrayData<T>();

        virtual void swap(size_t index0,size_t index1) override;
	};

	typedef ArrayData<float>	FloatArrayData;		/**< @brief ArrayData holding floats */
	typedef ArrayData<Color>	ColorArrayData;		/**< @brief ArrayData holding colors */
	typedef ArrayData<Vector3D> Vector3DArrayData;	/**< @brief ArrayData holding vectors */

	template<typename T>
	inline ArrayData<T>::ArrayData(size_t nbParticles,size_t sizePerParticle) :
		Data(),
		totalSize(nbParticles * sizePerParticle),
		sizePerParticle(sizePerParticle)
	{
		data = SPK_NEW_ARRAY(T,totalSize);
	}

	template<typename T>
	inline ArrayData<T>::~ArrayData()
	{
		SPK_DELETE_ARRAY(data);
	}

	template<typename T>
	inline T* ArrayData<T>::getData()
	{
		return data;
	}

	template<typename T>
	inline const T* ArrayData<T>::getData() const
	{
		return data;
	}

	template<typename T>
	inline T* ArrayData<T>::getParticleData(size_t index)
	{
		return data + index * sizePerParticle;
	}

	template<typename T>
	inline const T* ArrayData<T>::getParticleData(size_t index) const
	{
		return data + index * sizePerParticle;
	}

	template<typename T>
	inline T& ArrayData<T>::operator[](size_t index)
	{
		return data[index];
	}
	
	template<typename T>
	inline const T& ArrayData<T>::operator[](size_t index) const
	{
		return data[index];
	}

	template<typename T>
	inline size_t ArrayData<T>::getTotalSize() const
	{
		return totalSize;
	}

	template<typename T>
	inline size_t ArrayData<T>::getSizePerParticle() const
	{
		return sizePerParticle;
	}

	template<typename T>
    inline void ArrayData<T>::swap(size_t index0,size_t index1)
	{
		index0 *= sizePerParticle;
		index1 *= sizePerParticle;
		for (size_t i = 0; i < sizePerParticle; ++i)
			std::swap(data[index0 + i],data[index1 + i]);
	}
}

#endif
