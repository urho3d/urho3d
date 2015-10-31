// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_bitmap_fragment.h"
#include "tb_system.h"
#include "tb_tempbuffer.h"

#ifdef TB_IMAGE_LOADER_STB

namespace tb {

// Configure stb image and remove some features we don't use to reduce binary size.
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
//#define STBI_SIMD
#define STBI_NO_STDIO
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_HDR

// Disable unused function warnings for stb_image.h. Since STB_IMAGE_STATIC is
// defined, it will contain a couple of unused static functions.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

// Include stb image - Tiny portable and reasonable fast image loader from http://nothings.org/
// Should not be used for content not distributed with your app (May not be secure and doesn't
// support all formats fully)
#include "thirdparty/stb_image.h"

#pragma GCC diagnostic pop

class STBI_Loader : public TBImageLoader
{
public:
	int width, height;
	unsigned char *data;

	STBI_Loader() : width(0), height(0), data(nullptr) {}
	~STBI_Loader() { stbi_image_free(data); }

	virtual int Width() { return width; }
	virtual int Height() { return height; }
	virtual uint32 *Data() { return (uint32*)data; }
};

TBImageLoader *TBImageLoader::CreateFromFile(const char *filename)
{
	if (TBFile *file = TBFile::Open(filename, TBFile::MODE_READ))
	{
		long size = file->Size();
		TBTempBuffer buf;
		if (buf.Reserve(size))
		{
			size = file->Read(buf.GetData(), 1, size);

			int w, h, comp;
			if (unsigned char *img_data = stbi_load_from_memory(
				(unsigned char*) buf.GetData(), size, &w, &h, &comp, 4))
			{
				if (STBI_Loader *img = new STBI_Loader())
				{
					img->width = w;
					img->height = h;
					img->data = img_data;
					delete file;
					return img;
				}
				else
					stbi_image_free(img_data);
			}
		}
		delete file;
	}
	return nullptr;
}

}; // namespace tb

#endif // TB_IMAGE_LOADER_STB
