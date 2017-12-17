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

#ifndef H_SPK_ROTATOR
#define H_SPK_ROTATOR

namespace SPK
{
	/**
	* @class Rotator
	* @brief A Modifier allowing to rotate particle with their rotation speed
	*
	* Instead of controlling directly the particle angle, this modifier allows to control the particle rotation speed.<br>
	* The rotator derives the particle angle from the particle rotation speed.<br>
	* <br>
	* For this modifier to work, the PARAM_ANGLE must be enabled (and can be random in addition but not mutable or interpolated)
	* and the PARAM_ROTATION_SPEED must be at least enabled in the model of the group of particles that are modified.
	*/
	class SPK_PREFIX Rotator : public Modifier
	{
	SPK_IMPLEMENT_OBJECT(Rotator)

	public :

		/**
		* @brief Creates and registers a new Rotator
		* @return A new registered Rotator
		*/
		static  Ref<Rotator> create();

	private :

		/** @brief Constructor of Rotator */
		Rotator();
		Rotator(const Rotator& rotator);

        virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Rotator::Rotator() :
		Modifier(MODIFIER_PRIORITY_POSITION,false,false,false)
	{}

	inline Rotator::Rotator(const Rotator& rotator) :
		Modifier(rotator)
	{}

	inline Ref<Rotator> Rotator::create()
	{
		return SPK_NEW(Rotator);
	}
}

#endif
