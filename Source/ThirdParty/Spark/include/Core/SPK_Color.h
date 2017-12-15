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

#ifndef H_SPK_COLOR
#define H_SPK_COLOR

#include <iostream> // for operator <<

namespace SPK
{
	/** @brief A class defining a 32 bits color (4 components stored in rgba) */
	class Color
	{
	public :

		////////////////
		// Parameters //
		////////////////
		
		// Stored in RGBA format
		unsigned char r;	/**< Red component (from 0x00 to 0xFF) */
		unsigned char g;	/**< Green component (from 0x00 to 0xFF) */
		unsigned char b;	/**< Blue component (from 0x00 to 0xFF) */
		unsigned char a;	/**< Alpha component (from 0x00 to 0xFF) */

		//////////////////
		// Constructors //
		//////////////////

		/** 
		* @brief Constructor of Color
		* @param rgba : a value representing the color in rgba format
		*/
		Color(uint32 rgba = 0xFFFFFFFF);

		/**
		* @brief Constructor of Color
		* @param r : red component (from 0x00 to 0xFF)
		* @param g : green component (from 0x00 to 0xFF)
		* @param b : blue component (from 0x00 to 0xFF)
		* @param a : alpha component (from 0x00 to 0xFF)
		*/
		Color(int r,int g,int b,int a);

		///////////////
		// Operators //
		///////////////

		/**
		* @brief Adds a color
		* @param c : the color to add
		*/
		Color& operator+=(const Color& c);

		/**
		* @brief Subtracts a color
		* @param c : the color to subtract
		*/
		Color& operator-=(const Color& c);

		/**
		* @brief Cast operator from color to int
		* @return the resulting integer in rgba format
		*/
		operator uint32();

		/////////////
		// Setters //
		/////////////

		/**
		* @brief Sets the red component
		* @param r : the red component
		*/
		void setR(int r);

		/**
		* @brief Sets the green component
		* @param g : the green component
		*/
		void setG(int g);

		/**
		* @brief Sets the blue component
		* @param b : the blue component
		*/
		void setB(int b);

		/**
		* @brief Sets the alpha component
		* @param a : the alpha component
		*/
		void setA(int a);

		/**
		* @brief Sets the color from rgba
		* @param rgba : value of the rgba
		*/
		void setRGBA(uint32 rgba);

		/**
		* @brief Sets the color from argb
		* @param argb : value of the argb
		*/
		void setARGB(uint32 argb);

		/**
		* @brief Sets the color from bgra
		* @param bgra : value of the bgra
		*/
		void setBGRA(uint32 bgra);

		/**
		* @brief Sets the color
		* @param r : red component (from 0x00 to 0xFF)
		* @param g : green component (from 0x00 to 0xFF)
		* @param b : blue component (from 0x00 to 0xFF)
		* @param a : alpha component (from 0x00 to 0xFF)
		*/
		void set(int r,int g,int b,int a);
		
		/////////////
		// Getters //
		/////////////

		/**
		* @brief Gets the red component
		* @return the red component
		*/
		int getR() const;

		/**
		* @brief Gets the green component
		* @return the green component
		*/
		int getG() const;

		/**
		* @brief Gets the blue component
		* @return the blue component
		*/
		int getB() const;

		/**
		* @brief Gets the alpha component
		* @return the alpha component
		*/
		int getA() const;

		/**
		* @brief Gets the color in rgba format
		* @return a value representing the color in rgba format
		*/
		uint32 getRGBA() const;

		/**
		* @brief Gets the color in argb format
		* @return a value representing the color in argb format
		*/
		uint32 getARGB() const;

		/**
		* @brief Gets the color in bgra format
		* @return a value representing the color in bgra format
		*/
		uint32 getBGRA() const;

        /**
        * @brief Gets the color in abgr format
        * @return a value representing the color in abgr format
        */
        uint32 getABGR() const;

		///////////////
		// Interface //
		///////////////

		/**
		* @brief Linearly interpolates the color from 2 colors and a ratio
		* Interpolates between c0 and c1 : <i>c = c0 * (1 - ratio) + c1 * ratio</i>
		* @param c0 : the first color used for interpolation
		* @param c1 : the second color used for interpolation
		* @param ratio : the ratio used to interpolate between the 2 colors
		*/
		void interpolate(const Color& c0,const Color& c1,float ratio);
	};

	////////////////////////
	// External operators //
	////////////////////////

	/**
	* @brief Adds 2 colors
	* returns <i>c0 + c1</i>
	* @param c0 : the first color
	* @param c1 : the second color
	* @return the resulting color
	*/
	Color operator+(const Color& c0,const Color& c1);

	/**
	* @brief Subtracts 2 colors
	* returns <i>c0 - c1</i>
	* @param c0 : the first color
	* @param c1 : the second color
	* @return the resulting color
	*/
	Color operator-(const Color& c0,const Color& c1);

	/**
	* @brief Checks if 2 colors are equal
	* All components of the colors must be equal for 2 colors to be equal
	* @param c0 : the first color
	* @param c1 : the second color
	* return true if the 2 colors are equal, false if not
	*/
	bool operator==(const Color& c0,const Color& c1);

	/**
	* @brief Checks if 2 colors are not equal
	* @param c0 : the first color
	* @param c1 : the second color
	* return true if the 2 colors are not equal, false if they are
	*/
	bool operator!=(const Color& c0,const Color& c1);

	/**
	* @brief Writes a color on an output stream
	* The color is written that way : <i>0xRGBA</i>
	* @param s : the output stream where to write
	* @param c : the color to write to the output stream
	* @return the output stream
	*/
	std::ostream& operator<<(std::ostream& s,const Color& c);

	/**
	* @brief Reads a color from an intput stream
	* See the operator<< for the expected format
	* @param s : the input stream where to read from
	* @param c : the color to be read
	* @return the output stream
	*/
	std::istream& operator>>(std::istream& s,Color& c);

	/////////////////
	// Definitions //
	/////////////////

	inline Color::Color(uint32 rgba) :
		r((unsigned char)(rgba >> 24)),
		g((unsigned char)(rgba >> 16)),
		b((unsigned char)(rgba >> 8)),
		a((unsigned char)(rgba))
	{}

	inline Color::Color(int r,int g,int b,int a) :
		r(r),
		g(g),
		b(b),
		a(a)
	{}

	inline Color& Color::operator+=(const Color& c)
	{
		int a = getA() + c.getA();
		if (a > 255) a = 255;
		int r = getR() + c.getR();
		if (r > 255) r = 255;
		int g = getG() + c.getG();
		if (g > 255) g = 255;
		int b = getB() + c.getB();
		if (b > 255) b = 255;
		set(a,r,g,b);
		return *this;
	}

	inline Color& Color::operator-=(const Color& c)
	{
		int a = getA() - c.getA();
		if (a < 0) a = 0;
		int r = getR() - c.getR();
		if (r < 0) r = 0;
		int g = getG() - c.getG();
		if (g < 0) g = 0;
		int b = getB() - c.getB();
		if (b < 0) b = 0;
		set(a,r,g,b);
		return *this;
	}

	inline Color::operator uint32()
	{
		return getRGBA();
	}

	inline void Color::setR(int r) { this->r = r; }
	inline void Color::setG(int g) { this->g = g; }
	inline void Color::setB(int b) { this->b = b; }
	inline void Color::setA(int a) { this->a = a; }

	inline void Color::setRGBA(uint32 rgba)
	{
		r = (unsigned char)(rgba >> 24);
		g = (unsigned char)(rgba >> 16);
		b = (unsigned char)(rgba >> 8);
		a = (unsigned char)(rgba);
	}

	inline void Color::setARGB(uint32 argb)
	{
		a = (unsigned char)(argb >> 24);
		r = (unsigned char)(argb >> 16);
		g = (unsigned char)(argb >> 8);
		b = (unsigned char)(argb);
	}

	inline void Color::setBGRA(uint32 bgra)
	{
		b = (unsigned char)(bgra >> 24);
		g = (unsigned char)(bgra >> 16);
		r = (unsigned char)(bgra >> 8);
		a = (unsigned char)(bgra);
	}

	inline void Color::set(int r,int g,int b,int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	inline int Color::getR() const { return r; }
	inline int Color::getG() const { return g; }
	inline int Color::getB() const { return b; }
	inline int Color::getA() const { return a; }

	inline uint32 Color::getRGBA() const
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	}

	inline uint32 Color::getARGB() const
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	inline uint32 Color::getBGRA() const
	{
		return (b << 24) | (g << 16) | (r << 8) | a;
	}

    inline uint32 Color::getABGR() const
    {
        return (a << 24) | (b << 16) | (g << 8) | r;
    }

	inline void Color::interpolate(const Color& c0,const Color& c1,float ratio)
	{
		int iRatio = static_cast<int>(ratio * 256.0f); // We use fixed point to speed up the interpolation
		int invRatio = 256 - iRatio;
		r = (unsigned char)((c0.r * invRatio + c1.r * iRatio) >> 8);
		g = (unsigned char)((c0.g * invRatio + c1.g * iRatio) >> 8);
		b = (unsigned char)((c0.b * invRatio + c1.b * iRatio) >> 8);
		a = (unsigned char)((c0.a * invRatio + c1.a * iRatio) >> 8);
	}

	inline Color operator+(const Color& c0,const Color& c1)
	{
		Color c(c0);
		return c += c1;
	}

	inline Color operator-(const Color& c0,const Color& c1)
	{
		Color c(c0);
		return c -= c1;
	}

	inline bool operator==(const Color& c0,const Color& c1)
	{
		return c0.getRGBA() == c1.getRGBA();
	}

	inline bool operator!=(const Color& c0,const Color& c1)
	{
		return c0.getRGBA() != c1.getRGBA();
	}

	inline std::ostream& operator<<(std::ostream& s,const Color& c)
	{
		std::ios_base::fmtflags oldFormat = s.flags();
		s.setf(std::ios_base::hex |std::ios_base::showbase);
		s.unsetf(std::ios_base::dec | std::ios_base::oct);
		s << c.getRGBA();
		s.flags(oldFormat);
		return s;
	}

	inline std::istream& operator>>(std::istream& s,Color& c)
	{
		std::ios_base::fmtflags oldFormat = s.flags();
		s.setf(std::ios_base::hex | std::ios_base::showbase);
		s.unsetf(std::ios_base::dec | std::ios_base::oct);
		uint32 rgba = 0;
		s >> rgba;
		c.setRGBA(rgba);
		s.flags(oldFormat);
		return s;
	}

	// Specialization of the random generation of colors
	template<>
	inline Color SPKContext::generateRandom(const Color& c0,const Color& c1)
	{
		return Color(
			generateRandom(c0.getR(),c1.getR()),
			generateRandom(c0.getG(),c1.getG()),
			generateRandom(c0.getB(),c1.getB()),
			generateRandom(c0.getA(),c1.getA()));
	}
}

#endif
