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

#ifndef H_SPK_POINTRENDERBEHAVIOR
#define H_SPK_POINTRENDERBEHAVIOR

namespace SPK
{
	/**
	* @enum PointType
	* @brief Constants defining the type of points to render
	*/
	enum PointType
	{
		POINT_TYPE_SQUARE,	/**< Points are renderered as squares */
		POINT_TYPE_CIRCLE,	/**< Points are renderered as circles */
		POINT_TYPE_SPRITE,	/**< Points are renderered as point sprites (textured points) */
	};

	/**
	* @brief Base Interface for rendering particles with points
	*/
	class PointRenderBehavior
	{
	public :

		////////////////
		// Destructor //
		////////////////

		/** @brief Destructor of PointRenderBehavior */
		virtual  ~PointRenderBehavior() {}

		//////////
		// Type //
		//////////

		/**
		* @brief Sets the type of points to use in this PointRenderBehavior
		*
		* If the type is not supported by the platform, false is returned and the type per default is set.
		*
		* @param type : the type of points to use in this PointRenderBehavior
		* @return true if the type can be set, false otherwise
		*/
		virtual  bool setType(PointType type);

		/**
		* @brief Gets the type of points in this PointRenderBehavior
		* @return the type of points in this PointRenderBehavior
		*/
		PointType getType() const;

		////////////////
		// point size //
		////////////////

		/**
		* @brief Sets the size of the points in this PointRenderBehavior
		* @param size : the size of the points in this PointRenderBehavior
		*/
		virtual  void setScreenSize(float screenSize);

		/**
		* @brief Gets the size of points in this PointRenderBehavior
		* @return the size of points in this PointRenderBehavior
		*/
		float getScreenSize() const;

		virtual  void setWorldScale(float worldScale);
		float getWorldScale() const;

		/**
		* @brief Sets the way size of points is computed
		* @param worldSizeEnabled : true to enable universe size, false to use screen size
		* @return true the type of size can be set, false otherwise
		*/
		virtual  bool enableWorldSize(bool worldSizeEnabled);

		/**
		* @brief Tells whether world size is enabled or not in this GLPointRenderer
		* @return true if world size is enabled, false if not
		*/
		bool isWorldSizeEnabled() const;

	protected :

		PointType type;
		bool worldSize;

		union 
		{
			float screenSize;
			float worldScale;
		};

		/////////////////
		// Constructor //
		/////////////////

		/**
		* @brief Constructor of PointRenderBehavior
		* @param type : the initial type of this PointRenderBehavior (must be supported by default by the platform)
		* @param size : the width of this PointRenderBehavior
		*/
		PointRenderBehavior(PointType type = POINT_TYPE_SQUARE,float screenSize = 1.0f);
	};

	inline PointRenderBehavior::PointRenderBehavior(PointType type,float screenSize) :
		type(type),
        worldSize(false),
        screenSize(screenSize)
	{}

	inline bool PointRenderBehavior::setType(PointType type)
	{
		this->type = type;
		return true;
	}

	inline PointType PointRenderBehavior::getType() const
	{
		return type;
	}

	inline void PointRenderBehavior::setScreenSize(float screenSize)
	{
		this->screenSize = screenSize;
	}

	inline float PointRenderBehavior::getScreenSize() const
	{
		return screenSize;
	}

	inline void PointRenderBehavior::setWorldScale(float worldScale)
	{
		this->worldScale = worldScale;
	}

	inline float PointRenderBehavior::getWorldScale() const
	{
		return worldScale;
	}

	inline bool PointRenderBehavior::enableWorldSize(bool worldSizeEnabled)
	{
		worldSize = worldSizeEnabled;
		return true;
	}

	inline bool PointRenderBehavior::isWorldSizeEnabled() const
	{
		return worldSize;
	}
}

#endif
