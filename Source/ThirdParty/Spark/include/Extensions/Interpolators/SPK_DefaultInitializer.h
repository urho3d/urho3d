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

#ifndef H_SPK_DEFAULTINITIALIZER
#define H_SPK_DEFAULTINITIALIZER

namespace SPK
{
	template<typename T>
	class DefaultInitializer : public Interpolator<T>
	{
	SPK_DEFINE_OBJECT_TEMPLATE(DefaultInitializer<T>)
	SPK_DEFINE_DESCRIPTION_TEMPLATE

	public :

		static  Ref<DefaultInitializer<T> > create(const T& value);

		void setDefaultValue(const T& value);
		const T& getDefaultValue() const;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		T defaultValue;

		DefaultInitializer<T>(const T& value = T());
		DefaultInitializer<T>(const DefaultInitializer<T>& interpolator);

        virtual  void interpolate(T* data,Group& group,DataSet* dataSet) const override {}
        virtual  void init(T& data,Particle& particle,DataSet* dataSet) const override;
	};

	typedef DefaultInitializer<Color> ColorDefaultInitializer;
	typedef DefaultInitializer<float> FloatDefaultInitializer;

	SPK_IMPLEMENT_OBJECT_TEMPLATE(ColorDefaultInitializer)
	SPK_IMPLEMENT_OBJECT_TEMPLATE(FloatDefaultInitializer)

	SPK_START_DESCRIPTION_TEMPLATE(DefaultInitializer<T>)
	SPK_PARENT_ATTRIBUTES(Interpolator<T>)
	SPK_ATTRIBUTE_GENERIC("value",T)
	SPK_END_DESCRIPTION

	template<typename T>
	DefaultInitializer<T>::DefaultInitializer(const T& value) :
		Interpolator<T>(false),
		defaultValue(value)
	{}

	template<typename T>
	DefaultInitializer<T>::DefaultInitializer(const DefaultInitializer<T>& interpolator) :
		Interpolator<T>(interpolator),
		defaultValue(interpolator.defaultValue)
	{}

	template<typename T>
	inline Ref<DefaultInitializer<T> > DefaultInitializer<T>::create(const T& value)
	{
		return SPK_NEW(DefaultInitializer<T>,value);
	}

	template<typename T>
	inline void DefaultInitializer<T>::setDefaultValue(const T& value)
	{
		defaultValue = value;
	}

	template<typename T>
	inline const T& DefaultInitializer<T>::getDefaultValue() const
	{
		return defaultValue;
	}

	template<typename T>
	inline void DefaultInitializer<T>::init(T& data,Particle& particle,DataSet* dataSet) const
	{
		data = defaultValue;
	}

	template<typename T>
	void DefaultInitializer<T>::innerImport(const IO::Descriptor& descriptor)
	{
		Interpolator<T>::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("value")))
			setDefaultValue(attrib->getValue<T>());
	}

	template<typename T>
	void DefaultInitializer<T>::innerExport(IO::Descriptor& descriptor) const
	{
		Interpolator<T>::innerExport(descriptor);
		descriptor.getAttribute("value")->setValue(getDefaultValue());
	}
}

#endif
