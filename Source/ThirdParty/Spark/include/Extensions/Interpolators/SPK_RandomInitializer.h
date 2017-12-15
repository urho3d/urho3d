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

#ifndef H_SPK_RANDOMINITIALIZER
#define H_SPK_RANDOMINITIALIZER

namespace SPK
{
	template<typename T>
	class RandomInitializer : public Interpolator<T>
	{
	SPK_DEFINE_OBJECT_TEMPLATE(RandomInitializer<T>);
	SPK_DEFINE_DESCRIPTION_TEMPLATE

	public :

		static Ref<RandomInitializer<T> > create(const T& minValue = T(),const T& maxValue = T());

		void setValues(const T& minValue,const T& maxValue);
		const T& getMinValue() const;
		const T& getMaxValue() const;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		T minValue;
		T maxValue;

		RandomInitializer<T>(const T& min = T(),const T& max = T());
		RandomInitializer<T>(const RandomInitializer<T>& interpolator);

        virtual void interpolate(T* data,Group& group,DataSet* dataSet) const override {}
        virtual void init(T& data,Particle& particle,DataSet* dataSet) const override;
	};

	typedef RandomInitializer<Color> ColorRandomInitializer;
	typedef RandomInitializer<float> FloatRandomInitializer;

	SPK_IMPLEMENT_OBJECT_TEMPLATE(ColorRandomInitializer)
	SPK_IMPLEMENT_OBJECT_TEMPLATE(FloatRandomInitializer)

	SPK_START_DESCRIPTION_TEMPLATE(RandomInitializer<T>)
	SPK_PARENT_ATTRIBUTES(Interpolator<T>)
	SPK_ATTRIBUTE_ARRAY_GENERIC("values",T)
	SPK_END_DESCRIPTION

	template<typename T>
	RandomInitializer<T>::RandomInitializer(const T& minValue,const T& maxValue) :
		Interpolator<T>(false),
		minValue(minValue),
		maxValue(maxValue)
	{}

	template<typename T>
	RandomInitializer<T>::RandomInitializer(const RandomInitializer<T>& interpolator) :
		Interpolator<T>(interpolator),
		minValue(interpolator.minValue),
		maxValue(interpolator.maxValue)
	{}

	template<typename T>
	inline Ref<RandomInitializer<T> > RandomInitializer<T>::create(const T& min,const T& max)
	{
		return SPK_NEW(RandomInitializer<T>,min,max);
	}

	template<typename T>
	inline void RandomInitializer<T>::setValues(const T& minValue,const T& maxValue)
	{
		this->minValue = minValue;
		this->maxValue = maxValue;
	}

	template<typename T>
	inline const T& RandomInitializer<T>::getMinValue() const
	{
		return minValue;
	}

	template<typename T>
	inline const T& RandomInitializer<T>::getMaxValue() const
	{
		return maxValue;
	}

	template<typename T>
	inline void RandomInitializer<T>::init(T& data,Particle& particle,DataSet* dataSet) const
	{
		data = SPK_RANDOM(minValue,maxValue);
	}

	template<typename T>
	void RandomInitializer<T>::innerImport(const IO::Descriptor& descriptor)
	{
		Interpolator<T>::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("values")))
		{
			std::vector<T> tmpValues = attrib->getValues<T>();
			if (tmpValues.size() == 2)
				setValues(tmpValues[0],tmpValues[1]);
			else
				SPK_LOG_ERROR("RandomInitializer<T>::innerImport(const IO::Descriptor&) - Wrong number of values : " << tmpValues.size());
		}
	}

	template<typename T>
	void RandomInitializer<T>::innerExport(IO::Descriptor& descriptor) const
	{
		Interpolator<T>::innerExport(descriptor);
		T tmpValues[2] = {minValue,maxValue};
		descriptor.getAttribute("values")->setValues(tmpValues,2);
	}
}

#endif
