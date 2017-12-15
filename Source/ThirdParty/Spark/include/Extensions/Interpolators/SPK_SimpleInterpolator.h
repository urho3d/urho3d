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

#ifndef H_SPK_SIMPLEINTERPOLATOR
#define H_SPK_SIMPLEINTERPOLATOR

namespace SPK
{
	template<typename T>
	class SimpleInterpolator : public Interpolator<T>
	{
	SPK_DEFINE_OBJECT_TEMPLATE(SimpleInterpolator)
	SPK_DEFINE_DESCRIPTION_TEMPLATE

	public :

		static  Ref<SimpleInterpolator<T> > create(const T& birthValue,const T& deathValue);

		void setValues(const T& birth,const T& death);
		const T& getBirthValue() const;
		const T& getDeathValue() const;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		T birthValue;
		T deathValue;

		SimpleInterpolator<T>(const T& birthValue = T(),const T& deathValue = T());
		SimpleInterpolator<T>(const SimpleInterpolator<T>& interpolator);

        virtual void interpolate(T* data,Group& group,DataSet* dataSet) const override;
        virtual  void init(T& data,Particle& particle,DataSet* dataSet) const override;
	};

	typedef SimpleInterpolator<Color> ColorSimpleInterpolator;
	typedef SimpleInterpolator<float> FloatSimpleInterpolator;

	SPK_IMPLEMENT_OBJECT_TEMPLATE(ColorSimpleInterpolator)
	SPK_IMPLEMENT_OBJECT_TEMPLATE(FloatSimpleInterpolator)

	SPK_START_DESCRIPTION_TEMPLATE(SimpleInterpolator<T>)
	SPK_PARENT_ATTRIBUTES(Interpolator<T>)
	SPK_ATTRIBUTE_ARRAY_GENERIC("values",T)
	SPK_END_DESCRIPTION

	template<typename T>
	SimpleInterpolator<T>::SimpleInterpolator(const T& birthValue,const T& deathValue) :
		Interpolator<T>(false),
		birthValue(birthValue),
		deathValue(deathValue)
	{}

	template<typename T>
	SimpleInterpolator<T>::SimpleInterpolator(const SimpleInterpolator<T>& interpolator) :
		Interpolator<T>(interpolator),
		birthValue(interpolator.birthValue),
		deathValue(interpolator.deathValue)
	{}

	template<typename T>
	inline Ref<SimpleInterpolator<T> > SimpleInterpolator<T>::create(const T& birthValue,const T& deathValue)
	{
		return SPK_NEW(SimpleInterpolator<T>,birthValue,deathValue);
	}

	template<typename T>
	inline void SimpleInterpolator<T>::setValues(const T& birth,const T& death)
	{
		this->birthValue = birth;
		this->deathValue = death;
	}

	template<typename T>
	inline const T& SimpleInterpolator<T>::getBirthValue() const
	{
		return birthValue;
	}

	template<typename T>
	inline const T& SimpleInterpolator<T>::getDeathValue() const
	{
		return deathValue;
	}

	template<typename T>
	inline void SimpleInterpolator<T>::init(T& data,Particle& particle,DataSet* dataSet) const
	{
		data = birthValue;
	}

	template<typename T>
	void SimpleInterpolator<T>::interpolate(T* data,Group& group,DataSet* dataSet) const
	{
		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
            this->interpolateParam(data[particleIt->getIndex()],deathValue,birthValue,particleIt->getEnergy());
	}

	template<typename T>
	void SimpleInterpolator<T>::innerImport(const IO::Descriptor& descriptor)
	{
		Interpolator<T>::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("values")))
		{
			std::vector<T> tmpValues = attrib->getValues<T>();
			if (tmpValues.size() == 2)
				setValues(tmpValues[0],tmpValues[1]);
			else
				SPK_LOG_ERROR("SimpleInterpolator<T>::innerImport(const IO::Descriptor&) - Wrong number of values : " << tmpValues.size());
		}
	}

	template<typename T>
	void SimpleInterpolator<T>::innerExport(IO::Descriptor& descriptor) const
	{
		Interpolator<T>::innerExport(descriptor);
		T tmpValues[2] = {birthValue,deathValue};
		descriptor.getAttribute("values")->setValues(tmpValues,2);
	}
}

#endif
