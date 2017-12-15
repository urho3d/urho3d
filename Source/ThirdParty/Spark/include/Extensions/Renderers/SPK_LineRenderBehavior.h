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

#ifndef H_SPK_LINERENDERBEHAVIOR
#define H_SPK_LINERENDERBEHAVIOR

namespace SPK
{
	/**
	* @brief Base Interface for rendering particles with lines
	*/
	class LineRenderBehavior
	{
	public :

		////////////////
		// Destructor //
		////////////////

		/** @brief Destructor of LineRenderBehavior */
		virtual  ~LineRenderBehavior() {}

		/////////////
		// Setters //
		/////////////

		/**
		* @brief Sets the length multiplier of this LineRenderBehavior
		*
		* The length multiplier is the value which will be multiplied by the Particle velocity to get the line length in the universe.<br>
		* A positive length means the line will be drawn in advance to the Particle, as opposed to a negative length.
		*
		* @param length : the length multiplier of this GLLineRenderer
		*/
		void setLength(float length);

		/**
		* @brief Sets the width of this LineRenderBehavior
		* @param width : the width of this LineRenderBehavior
		*/
		virtual  void setWidth(float width);

		/////////////
		// Getters //
		/////////////

		/**
		* @brief Gets the length multiplier of this LineRenderBehavior
		* @return the length multiplier of this LineRenderBehavior
		*/
		float getLength() const;

		/**
		* @brief Gets the width of this LineRenderBehavior
		* @return the width of this LineRenderBehavior
		*/
		float getWidth() const;

	protected :

		float length;
		float width;

		/////////////////
		// Constructor //
		/////////////////

		/**
		* @brief Constructor of LineRenderBehavior
		* @param length : the length multiplier of this LineRenderBehavior
		* @param width : the width of this GLLineRenderer
		*/
		LineRenderBehavior(float length = 1.0f,float width = 1.0f);
	};


	inline LineRenderBehavior::LineRenderBehavior(float length,float width) :
		length(length),
		width(width)
	{}

	inline void LineRenderBehavior::setLength(float length)
	{
		this->length = length;
	}

	inline void LineRenderBehavior::setWidth(float width)
	{
		this->width = width;
	}

	inline float LineRenderBehavior::getLength() const
	{
		return length;
	}

	inline float LineRenderBehavior::getWidth() const
	{
		return width;
	}
}

#endif
