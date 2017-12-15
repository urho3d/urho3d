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

#ifndef H_SPK_IOBUFFER
#define H_SPK_IOBUFFER

namespace SPK
{
namespace IO
{
	class IOBuffer
	{
	public :

		IOBuffer(size_t capacity);
		IOBuffer(size_t,std::istream& is);
		~IOBuffer();

		const char* getData() const	{ return buf; }

		////////////////////
		// Size operators //
		////////////////////

		size_t getSize() const				{ return size; }
		size_t getCapacity() const			{ return capacity; }
		size_t getPosition() const			{ return position; }

		void skip(size_t nb) const			{ position += nb; }
		void setPosition(size_t pos) const	{ position = pos; }
		void clear()						{ position = size = 0; }

		bool isAtEnd() const				{ return position >= size; }

		//////////////////////////////
		// Primitive get operations //
		//////////////////////////////

		const char* get(size_t length) const;

		int32 get32() const
		{
			if (USE_LITTLE_ENDIANS)
				return *reinterpret_cast<const int32*>(get(4));
			else
				return swap32(*reinterpret_cast<const int32*>(get(4)));
		}

		template<class T> T get() const;

		//////////////////////////////
		// Primitive put operations //
		//////////////////////////////

		void put(char c);
		void put(const char* c,size_t length);

		void put32(int32 i)
		{
			if (USE_LITTLE_ENDIANS)
				put(reinterpret_cast<char*>(&i),4);
			else
				put(reinterpret_cast<char*>(swap32(i)),4);
		}

		////////////////////////////
		// Generic put operations //
		////////////////////////////

		void put(float f)			{ put32(*reinterpret_cast<int32*>(&f)); }
		void put(uint32 i)			{ put32(*reinterpret_cast<int32*>(&i)); }
		void put(int32 i)			{ put32(i); }
		void put(std::string s)		{ put(s.data(),s.size()); put('\0'); }
        void put(const Vector3D& v)	{ put(v.x); put(v.y); put(v.z); }
        void put(const Color& c)    { put32(*reinterpret_cast<const int32*>(&c)); }
		void put(bool b)			{ put(static_cast<char>(b ? 0x01 : 0x00)); }

		template<class T>
		void putArray(const std::vector<T>& t)
		{
			put(static_cast<uint32>(t.size()));
			for (size_t i = 0; i < t.size(); ++i)
				put(t[i]);
		}

		void putBuffer(const IOBuffer& buffer)
		{
			put(buffer.getData(),buffer.getSize());
		}

	private :

		IOBuffer(const IOBuffer& buffer);

		static const bool USE_LITTLE_ENDIANS;

		char* buf;
		size_t capacity;
		size_t size;
		mutable size_t position;

		static int32 swap32(int32 i)
		{
			return ((i & 0xFF000000 >> 24) & 0xFF) |
					(i & 0x00FF0000 >> 8) |
					(i & 0x0000FF00 << 8) |
					(i & 0x000000FF << 24) ;
		}

		void updateSize(size_t newPosition);

		static bool isLittleEndians();
	};

    ////////////////////////////
	// Generic get operations //
	////////////////////////////

    template<> inline char IOBuffer::get() const	{ return *get(1); }
    template<> inline float IOBuffer::get() const 	{ int32 i = get32(); return *reinterpret_cast<float*>(&i); }
	template<> inline uint32 IOBuffer::get() const 	{ int32 i = get32(); return *reinterpret_cast<uint32*>(&i); }
	template<> inline int32 IOBuffer::get() const	{ return get32(); }
	template<> inline Color IOBuffer::get() const	{ int32 i = get32(); return *reinterpret_cast<Color*>(&i); }
	template<> inline bool IOBuffer::get() const	{ return get<char>() != 0; }

	template<> SPK_PREFIX std::string IOBuffer::get<std::string>() const;
	template<> SPK_PREFIX Vector3D IOBuffer::get<Vector3D>() const;
}}

#endif
