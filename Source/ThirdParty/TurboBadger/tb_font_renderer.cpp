// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_font_renderer.h"
#include "tb_renderer.h"
#include "tb_system.h"
#include <math.h>

namespace tb {

// ================================================================================================

static void blurGlyph(unsigned char* src, int srcw, int srch, int srcStride, unsigned char* dst, int dstw, int dsth, int dstStride, float* temp, float* kernel, int kernelRadius)
{
	for (int y = 0; y < srch; y++)
	{
		for (int x = 0; x < dstw; x++)
		{
			float val = 0;
			for (int k_ofs = -kernelRadius; k_ofs <= kernelRadius; k_ofs++)
			{
				if (x - kernelRadius + k_ofs >= 0 && x - kernelRadius + k_ofs < srcw)
					val += src[y * srcStride + x - kernelRadius + k_ofs] * kernel[k_ofs + kernelRadius];
			}
			temp[y * dstw + x] = val;
		}
	}
	for (int y = 0; y < dsth; y++)
	{
		for (int x = 0; x < dstw; x++)
		{
			float val = 0;
			for (int k_ofs = -kernelRadius; k_ofs <= kernelRadius; k_ofs++)
			{
				if (y - kernelRadius + k_ofs >= 0 && y - kernelRadius + k_ofs < srch)
					val += temp[(y - kernelRadius + k_ofs) * dstw + x] * kernel[k_ofs + kernelRadius];
			}
			dst[y * dstStride + x] = (unsigned char)(val + 0.5f);
		}
	}
}

// ================================================================================================

TBFontEffect::TBFontEffect()
	: m_blur_radius(0)
	, m_tempBuffer(nullptr)
	, m_kernel(nullptr)
{
}

TBFontEffect::~TBFontEffect()
{
	delete [] m_tempBuffer;
	delete [] m_kernel;
}

void TBFontEffect::SetBlurRadius(int blur_radius)
{
	assert(blur_radius >= 0);
	if (m_blur_radius == blur_radius)
		return;
	m_blur_radius = blur_radius;
	if (m_blur_radius > 0)
	{
		delete [] m_kernel;
		m_kernel = new float[m_blur_radius * 2 + 1];
		if (!m_kernel)
		{
			m_blur_radius = 0;
			return;
		}
		float stdDevSq2 = (float)m_blur_radius / 2.f;
		stdDevSq2 = 2.f * stdDevSq2 * stdDevSq2;
		float scale = 1.f / sqrt(3.1415f * stdDevSq2);
		float sum = 0;
		for (int k = 0; k < 2 * m_blur_radius + 1; k++)
		{
			float x = (float)(k - m_blur_radius);
			float kval = scale * exp(-(x * x / stdDevSq2));
			m_kernel[k] = kval;
			sum += kval;
		}
		for (int k = 0; k < 2 * m_blur_radius + 1; k++)
			m_kernel[k] /= sum;
	}
}

TBFontGlyphData *TBFontEffect::Render(TBGlyphMetrics *metrics, const TBFontGlyphData *src)
{
	TBFontGlyphData *effect_glyph_data = nullptr;
	if (m_blur_radius > 0 && src->data8)
	{
		// Create a new TBFontGlyphData for the blurred glyph
		effect_glyph_data = new TBFontGlyphData;
		if (!effect_glyph_data)
			return nullptr;
		effect_glyph_data->w = src->w + m_blur_radius * 2;
		effect_glyph_data->h = src->h + m_blur_radius * 2;
		effect_glyph_data->stride = effect_glyph_data->w;
		effect_glyph_data->data8 = new unsigned char[effect_glyph_data->w * effect_glyph_data->h];

		// Reserve memory needed for blurring.
		if (!effect_glyph_data->data8 ||
			!m_blur_temp.Reserve(effect_glyph_data->w * effect_glyph_data->h * sizeof(float)))
		{
			delete effect_glyph_data;
			return nullptr;
		}

		// Blur!
		blurGlyph(src->data8, src->w, src->h, src->stride,
					effect_glyph_data->data8, effect_glyph_data->w, effect_glyph_data->h, effect_glyph_data->w,
					(float *)m_blur_temp.GetData(), m_kernel, m_blur_radius);

		// Adjust glyph position to compensate for larger size.
		metrics->x -= m_blur_radius;
		metrics->y -= m_blur_radius;
	}
	return effect_glyph_data;
}

// == TBFontGlyph =================================================================================

TBFontGlyph::TBFontGlyph(const TBID &hash_id, UCS4 cp)
	: hash_id(hash_id)
	, cp(cp)
	, frag(nullptr)
	, has_rgb(false)
{
}

// == TBFontGlyphCache ============================================================================

TBFontGlyphCache::TBFontGlyphCache()
{
	// Only use one map for the font face. The glyph cache will start forgetting
	// glyphs that haven't been used for a while if the map gets full.
	m_frag_manager.SetNumMapsLimit(1);
	m_frag_manager.SetDefaultMapSize(TB_GLYPH_CACHE_WIDTH, TB_GLYPH_CACHE_HEIGHT);

	g_renderer->AddListener(this);
}

TBFontGlyphCache::~TBFontGlyphCache()
{
	g_renderer->RemoveListener(this);
}

TBFontGlyph *TBFontGlyphCache::GetGlyph(const TBID &hash_id, UCS4 cp)
{
	if (TBFontGlyph *glyph = m_glyphs.Get(hash_id))
	{
		// Move the glyph to the end of m_all_rendered_glyphs so we maintain LRU (oldest first)
		if (m_all_rendered_glyphs.ContainsLink(glyph))
		{
			m_all_rendered_glyphs.Remove(glyph);
			m_all_rendered_glyphs.AddLast(glyph);
		}
		return glyph;
	}
	return nullptr;
}

TBFontGlyph *TBFontGlyphCache::CreateAndCacheGlyph(const TBID &hash_id, UCS4 cp)
{
	assert(!GetGlyph(hash_id, cp));
	TBFontGlyph *glyph = new TBFontGlyph(hash_id, cp);
	if (glyph && m_glyphs.Add(glyph->hash_id, glyph))
		return glyph;
	delete glyph;
	return nullptr;
}

TBBitmapFragment *TBFontGlyphCache::CreateFragment(TBFontGlyph *glyph, int w, int h, int stride, uint32 *data)
{
	assert(GetGlyph(glyph->hash_id, glyph->cp));
	// Don't bother if the requested glyph is too large.
	if (w > TB_GLYPH_CACHE_WIDTH || h > TB_GLYPH_CACHE_HEIGHT)
		return nullptr;

	bool try_drop_largest = true;
	bool dropped_large_enough_glyph = false;
	do
	{
		// Attempt creating a fragment for the rendered glyph data
		if (TBBitmapFragment *frag = m_frag_manager.CreateNewFragment(glyph->hash_id, false, w, h, stride, data))
		{
			glyph->frag = frag;
			m_all_rendered_glyphs.AddLast(glyph);
			return frag;
		}
		// Drop the oldest glyph that's large enough to free up the space we need.
		if (try_drop_largest)
		{
			const int check_limit = 20;
			int check_count = 0;
			for (TBFontGlyph *oldest = m_all_rendered_glyphs.GetFirst(); oldest && check_count < check_limit; oldest = oldest->GetNext())
			{
				if (oldest->frag->Width() >= w && oldest->frag->GetAllocatedHeight() >= h)
				{
					DropGlyphFragment(oldest);
					dropped_large_enough_glyph = true;
					break;
				}
				check_count++;
			}
			try_drop_largest = false;
		}
		// We had no large enough glyph so just drop the oldest one. We will likely
		// spin around the loop, fail and drop again a few times before we succeed.
		if (!dropped_large_enough_glyph)
		{
			if (TBFontGlyph *oldest = m_all_rendered_glyphs.GetFirst())
				DropGlyphFragment(oldest);
			else
				break;
		}
	} while (true);
	return nullptr;
}

void TBFontGlyphCache::DropGlyphFragment(TBFontGlyph *glyph)
{
	assert(glyph->frag);
	m_frag_manager.FreeFragment(glyph->frag);
	glyph->frag = nullptr;
	m_all_rendered_glyphs.Remove(glyph);
}

#ifdef TB_RUNTIME_DEBUG_INFO
void TBFontGlyphCache::Debug()
{
	m_frag_manager.Debug();
}
#endif // TB_RUNTIME_DEBUG_INFO

void TBFontGlyphCache::OnContextLost()
{
	m_frag_manager.DeleteBitmaps();
}

void TBFontGlyphCache::OnContextRestored()
{
	// No need to do anything. The bitmaps will be created when drawing.
}

// ================================================================================================

TBFontFace::TBFontFace(TBFontGlyphCache *glyph_cache, TBFontRenderer *renderer, const TBFontDescription &font_desc)
	: m_glyph_cache(glyph_cache), m_font_renderer(renderer), m_font_desc(font_desc), m_bgFont(nullptr), m_bgX(0), m_bgY(0)
{
	if (m_font_renderer)
		m_metrics = m_font_renderer->GetMetrics();
	else
	{
		// Invent some metrics for the test font
		int size = m_font_desc.GetSize();
		m_metrics.ascent = size - size / 4;
		m_metrics.descent = size / 4;
		m_metrics.height = size;
	}
}

TBFontFace::~TBFontFace()
{
	// It would be nice to drop all glyphs we have live for this font face.
	// Now they only die when they get old and kicked out of the cache.
	// We currently don't drop any font faces either though (except on shutdown)
	delete m_font_renderer;
}

void TBFontFace::SetBackgroundFont(TBFontFace *font, const TBColor &col, int xofs, int yofs)
{
	m_bgFont = font;
	m_bgX = xofs;
	m_bgY = yofs;
	m_bgColor = col;
}

bool TBFontFace::RenderGlyphs(const char *glyph_str, int glyph_str_len)
{
	if (!m_font_renderer)
		return true; // This is the test font

	if (glyph_str_len == TB_ALL_TO_TERMINATION)
		glyph_str_len = strlen(glyph_str);

	bool has_all_glyphs = true;
	int i = 0;
	while (glyph_str[i] && i < glyph_str_len)
	{
		UCS4 cp = utf8::decode_next(glyph_str, &i, glyph_str_len);
		if (!GetGlyph(cp, true))
			has_all_glyphs = false;
	}
	return has_all_glyphs;
}

TBFontGlyph *TBFontFace::CreateAndCacheGlyph(UCS4 cp)
{
	if (!m_font_renderer)
		return nullptr; // This is the test font

	// Create the new glyph
	TBFontGlyph *glyph = m_glyph_cache->CreateAndCacheGlyph(GetHashId(cp), cp);
	if (glyph)
		m_font_renderer->GetGlyphMetrics(&glyph->metrics, cp);
	return glyph;
}

void TBFontFace::RenderGlyph(TBFontGlyph *glyph)
{
	assert(!glyph->frag);
	TBFontGlyphData glyph_data;
	if (m_font_renderer->RenderGlyph(&glyph_data, glyph->cp))
	{
		TBFontGlyphData *effect_glyph_data = m_effect.Render(&glyph->metrics, &glyph_data);
		TBFontGlyphData *result_glyph_data = effect_glyph_data ? effect_glyph_data : &glyph_data;

		// The glyph data may be in uint8 format, which we have to convert since we always
		// create fragments (and TBBitmap) in 32bit format.
		uint32 *glyph_dsta_src = result_glyph_data->data32;
		if (!glyph_dsta_src && result_glyph_data->data8)
		{
			if (m_temp_buffer.Reserve(result_glyph_data->w * result_glyph_data->h * sizeof(uint32)))
			{
				glyph_dsta_src = (uint32 *) m_temp_buffer.GetData();
				for (int y = 0; y < result_glyph_data->h; y++)
					for (int x = 0; x < result_glyph_data->w; x++)
					{
#ifdef TB_PREMULTIPLIED_ALPHA
						uint8 opacity = result_glyph_data->data8[x + y * result_glyph_data->stride];
						glyph_dsta_src[x + y * result_glyph_data->w] = TBColor(opacity, opacity, opacity, opacity);
#else
						glyph_dsta_src[x + y * result_glyph_data->w] = TBColor(255, 255, 255, result_glyph_data->data8[x + y * result_glyph_data->stride]);
#endif
					}
			}
		}

		// Finally, the glyph data is ready and we can create a bitmap fragment.
		if (glyph_dsta_src)
		{
			glyph->has_rgb = result_glyph_data->rgb;
			m_glyph_cache->CreateFragment(glyph, result_glyph_data->w, result_glyph_data->h,
										result_glyph_data->stride, glyph_dsta_src);
		}

		delete effect_glyph_data;
	}
#ifdef TB_RUNTIME_DEBUG_INFO
	//char glyph_str[9];
	//int len = utf8::encode(cp, glyph_str);
	//glyph_str[len] = 0;
	//TBStr info;
	//info.SetFormatted("Created glyph %d (\"%s\"). Cache contains %d glyphs (%d%% full) using %d bitmaps.\n", cp, glyph_str, m_all_glyphs.CountLinks(), m_frag_manager.GetUseRatio(), m_frag_manager.GetNumMaps());
	//TBDebugOut(info);
#endif
}

TBID TBFontFace::GetHashId(UCS4 cp) const
{
	return cp * 31 + m_font_desc.GetFontFaceID();
}

TBFontGlyph *TBFontFace::GetGlyph(UCS4 cp, bool render_if_needed)
{
	TBFontGlyph *glyph = m_glyph_cache->GetGlyph(GetHashId(cp), cp);
	if (!glyph)
		glyph = CreateAndCacheGlyph(cp);
	if (glyph && !glyph->frag && render_if_needed)
		RenderGlyph(glyph);
	return glyph;
}

void TBFontFace::DrawString(int x, int y, const TBColor &color, const char *str, int len)
{
	if (m_bgFont)
		m_bgFont->DrawString(x+m_bgX, y+m_bgY, m_bgColor, str, len);

	if (m_font_renderer)
		g_renderer->BeginBatchHint(TBRenderer::BATCH_HINT_DRAW_BITMAP_FRAGMENT);

	int i = 0;
	while (str[i] && i < len)
	{
		UCS4 cp = utf8::decode_next(str, &i, len);
		if (cp == 0xFFFF)
			continue;
		if (TBFontGlyph *glyph = GetGlyph(cp, true))
		{
			if (glyph->frag)
			{
				TBRect dst_rect(x + glyph->metrics.x, y + glyph->metrics.y + GetAscent(), glyph->frag->Width(), glyph->frag->Height());
				TBRect src_rect(0, 0, glyph->frag->Width(), glyph->frag->Height());
				if (glyph->has_rgb)
					g_renderer->DrawBitmap(dst_rect, src_rect, glyph->frag);
				else
					g_renderer->DrawBitmapColored(dst_rect, src_rect, color, glyph->frag);
			}
			x += glyph->metrics.advance;
		}
		else if (!m_font_renderer) // This is the test font. Use same glyph width as height and draw square.
		{
			g_renderer->DrawRect(TBRect(x, y, m_metrics.height / 3, m_metrics.height), color);
			x += m_metrics.height / 3 + 1;
		}
	}

	if (m_font_renderer)
		g_renderer->EndBatchHint();
}

int TBFontFace::GetStringWidth(const char *str, int len)
{
	int width = 0;
	int i = 0;
	while (str[i] && i < len)
	{
		UCS4 cp = utf8::decode_next(str, &i, len);
		if (cp == 0xFFFF)
			continue;
		if (!m_font_renderer) // This is the test font. Use same glyph width as height.
			width += m_metrics.height / 3 + 1;
		else if (TBFontGlyph *glyph = GetGlyph(cp, false))
			width += glyph->metrics.advance;
	}
	return width;
}

#ifdef TB_RUNTIME_DEBUG_INFO
void TBFontFace::Debug()
{
	m_glyph_cache->Debug();
}
#endif // TB_RUNTIME_DEBUG_INFO

// == TBFontManager ===============================================================================

TBFontManager::TBFontManager()
{
	// Add the test dummy font with empty name (Equals to ID 0)
	AddFontInfo("-test-font-dummy-", "");
	m_test_font_desc.SetSize(16);
	CreateFontFace(m_test_font_desc);

	// Use the test dummy font as default by default
	m_default_font_desc = m_test_font_desc;
}

TBFontManager::~TBFontManager()
{
}

TBFontInfo *TBFontManager::AddFontInfo(const char *filename, const char *name)
{
	if (TBFontInfo *fi = new TBFontInfo(filename, name))
	{
		if (m_font_info.Add(fi->GetID(), fi))
			return fi;
		delete fi;
	}
	return nullptr;
}

TBFontInfo *TBFontManager::GetFontInfo(const TBID &id) const
{
	return m_font_info.Get(id);
}

bool TBFontManager::HasFontFace(const TBFontDescription &font_desc) const
{
	return m_fonts.Get(font_desc.GetFontFaceID()) ? true : false;
}

TBFontFace *TBFontManager::GetFontFace(const TBFontDescription &font_desc)
{
	if (TBFontFace *font = m_fonts.Get(font_desc.GetFontFaceID()))
		return font;
	if (TBFontFace *font = m_fonts.Get(GetDefaultFontDescription().GetFontFaceID()))
		return font;
	return m_fonts.Get(m_test_font_desc.GetFontFaceID());
}

TBFontFace *TBFontManager::CreateFontFace(const TBFontDescription &font_desc)
{
	assert(!HasFontFace(font_desc)); // There is already a font added with this description!

	TBFontInfo *fi = GetFontInfo(font_desc.GetID());
	if (!fi)
		return nullptr;

	if (fi->GetID() == 0) // Is this the test dummy font
	{
		if (TBFontFace *font = new TBFontFace(&m_glyph_cache, nullptr, font_desc))
		{
			if (m_fonts.Add(font_desc.GetFontFaceID(), font))
				return font;
			delete font;
		}
		return nullptr;
	}

	// Iterate through font renderers until we find one capable of creating a font for this file.
	for (TBFontRenderer *fr = m_font_renderers.GetFirst(); fr; fr = fr->GetNext())
	{
		if (TBFontFace *font = fr->Create(this, fi->GetFilename(), font_desc))
		{
			if (m_fonts.Add(font_desc.GetFontFaceID(), font))
				return font;
			delete font;
		}
	}
	return nullptr;
}

}; // namespace tb
