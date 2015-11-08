// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_font_renderer.h"
#include "tb_renderer.h"
#include "tb_system.h"

#ifdef TB_FONT_RENDERER_STB

using namespace tb;

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "thirdparty/stb_truetype.h"

/** STBFontRenderer renders fonts using stb_truetype.h (http://nothings.org/) */

class STBFontRenderer : public TBFontRenderer
{
public:
	STBFontRenderer();
	~STBFontRenderer();

	bool Load(const char *filename, int size);

	virtual TBFontFace *Create(TBFontManager *font_manager, const char *filename,
								const TBFontDescription &font_desc);

	virtual TBFontMetrics GetMetrics();
	virtual bool RenderGlyph(TBFontGlyphData *dst_bitmap, UCS4 cp);
	virtual void GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp);
private:
	stbtt_fontinfo font;
	unsigned char *ttf_buffer;
	unsigned char *render_data;
	int font_size;
	float scale;
};

STBFontRenderer::STBFontRenderer()
	: ttf_buffer(nullptr)
	, render_data(nullptr)
{
}

STBFontRenderer::~STBFontRenderer()
{
	delete [] ttf_buffer;
	delete [] render_data;
}

TBFontMetrics STBFontRenderer::GetMetrics()
{
	TBFontMetrics metrics;
	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
	metrics.ascent = (int) (ascent * scale + 0.5f);
	metrics.descent = (int) ((-descent) * scale + 0.5f);
	metrics.height = (int) ((ascent - descent + lineGap) * scale + 0.5f);
	return metrics;
}

bool STBFontRenderer::RenderGlyph(TBFontGlyphData *data, UCS4 cp)
{
	delete [] render_data;
	render_data = stbtt_GetCodepointBitmap(&font, 0, scale, cp, &data->w, &data->h, 0, 0);
	data->data8 = render_data;
	data->stride = data->w;
	data->rgb = false;
	return data->data8 ? true : false;
}

void STBFontRenderer::GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp)
{
	int advanceWidth, leftSideBearing;
	stbtt_GetCodepointHMetrics(&font, cp, &advanceWidth, &leftSideBearing);
	metrics->advance = (int) (advanceWidth * scale + 0.5f);
	int ix0, iy0, ix1, iy1;
	stbtt_GetCodepointBitmapBox(&font, cp, 0, scale, &ix0, &iy0, &ix1, &iy1);
	metrics->x = ix0;
	metrics->y = iy0;
}

bool STBFontRenderer::Load(const char *filename, int size)
{
	TBFile *f = TBFile::Open(filename, TBFile::MODE_READ);
	if (!f)
		return false;

	size_t ttf_buf_size = f->Size();
	ttf_buffer = new unsigned char[ttf_buf_size];
	if (ttf_buffer)
		ttf_buf_size = f->Read(ttf_buffer, 1, ttf_buf_size);
	delete f;

	if (!ttf_buffer)
		return false;

	stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));

	font_size = (int) (size * 1.3f); // FIX: Constant taken out of thin air because fonts get too small.
	scale = stbtt_ScaleForPixelHeight(&font, (float)font_size);
	return true;
}

TBFontFace *STBFontRenderer::Create(TBFontManager *font_manager, const char *filename, const TBFontDescription &font_desc)
{
	if (STBFontRenderer *fr = new STBFontRenderer())
	{
		if (fr->Load(filename, (int) font_desc.GetSize()))
			if (TBFontFace *font = new TBFontFace(font_manager->GetGlyphCache(), fr, font_desc))
				return font;
		delete fr;
	}
	return nullptr;
}

void register_stb_font_renderer()
{
	if (STBFontRenderer *fr = new STBFontRenderer)
		g_font_manager->AddRenderer(fr);
}

#endif // TB_FONT_RENDERER_STB
