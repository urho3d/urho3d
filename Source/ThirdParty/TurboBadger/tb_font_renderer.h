// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_FONT_RENDERER_H
#define TB_FONT_RENDERER_H

#include "tb_core.h"
#include "tb_bitmap_fragment.h"
#include "tb_renderer.h"
#include "tb_tempbuffer.h"
#include "tb_linklist.h"
#include "tb_font_desc.h"
#include "utf8/utf8.h"

namespace tb {

class TBBitmap;
class TBFontFace;

/** TBFontGlyphData is rendering info used during glyph rendering by TBFontRenderer.
	It does not own the data pointers. */
class TBFontGlyphData
{
public:
	TBFontGlyphData() : data8(nullptr), data32(nullptr), w(0), h(0), stride(0), rgb(false) {}
	~TBFontGlyphData() {}

	uint8 *data8;
	uint32 *data32;
	int w, h, stride;
	bool rgb;
};

/** TBGlyphMetrics contains metrics for a font glyph. */
class TBGlyphMetrics
{
public:
	TBGlyphMetrics() : advance(0), x(0), y(0) {}
	int16 advance, x, y;
};

/** TBFontMetrics contains metrics for a font face. */
class TBFontMetrics
{
public:
	TBFontMetrics() : ascent(0), descent(0), height(0) {}
	int16 ascent;	///< Ascent. See TBFontFace::GetAscent()
	int16 descent;	///< Descent. See TBFontFace::GetDescent()
	int16 height;	///< Height. See TBFontFace::GetHeight()
};

/** TBFontRenderer renders glyphs from a font file. */
class TBFontRenderer : public TBLinkOf<TBFontRenderer>
{
public:
	virtual ~TBFontRenderer() {}

	/** Open the given font file with this renderer and return a new TBFontFace with it.
		return nullptr if the file can't be opened by this renderer. */
	virtual TBFontFace *Create(TBFontManager *font_manager, const char *filename,
								const TBFontDescription &font_desc) = 0;

	virtual bool RenderGlyph(TBFontGlyphData *data, UCS4 cp) = 0;
	virtual void GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp) = 0;
	virtual TBFontMetrics GetMetrics() = 0;
	//virtual int GetKernAdvance(UCS4 cp1, UCS4 cp2) = 0;
};

/** TBFontGlyph holds glyph metrics and bitmap fragment.
	There's one of these for all rendered (both successful
	and missing) glyphs in TBFontFace. */
class TBFontGlyph : public TBLinkOf<TBFontGlyph>
{
public:
	TBFontGlyph(const TBID &hash_id, UCS4 cp);
	TBID hash_id;
	UCS4 cp;
	TBGlyphMetrics metrics;		///< The glyph metrics.
	TBBitmapFragment *frag;		///< The bitmap fragment, or nullptr if missing.
	bool has_rgb;				///< if true, drawing should ignore text color.
};

/** TBFontGlyphCache caches glyphs for font faces.
	Rendered glyphs use bitmap fragments from its fragment manager. */
class TBFontGlyphCache : private TBRendererListener
{
public:
	TBFontGlyphCache();
	~TBFontGlyphCache();

	/** Get the glyph or nullptr if it is not in the cache. */
	TBFontGlyph *GetGlyph(const TBID &hash_id, UCS4 cp);

	/** Create the glyph and put it in the cache. Returns the glyph, or nullptr on fail. */
	TBFontGlyph *CreateAndCacheGlyph(const TBID &hash_id, UCS4 cp);

	/** Create a bitmap fragment for the given glyph and render data. This may drop other
		rendered glyphs from the fragment map. Returns the fragment, or nullptr on fail. */
	TBBitmapFragment *CreateFragment(TBFontGlyph *glyph, int w, int h, int stride, uint32 *data);

#ifdef TB_RUNTIME_DEBUG_INFO
	/** Render the glyph bitmaps on screen, to analyze fragment positioning. */
	void Debug();
#endif

	// Implementing TBRendererListener
	virtual void OnContextLost();
	virtual void OnContextRestored();
private:
	void DropGlyphFragment(TBFontGlyph *glyph);
	TBBitmapFragmentManager m_frag_manager;
	TBHashTableAutoDeleteOf<TBFontGlyph> m_glyphs;
	TBLinkListOf<TBFontGlyph> m_all_rendered_glyphs;
};

/** TBFontEffect applies an effect on each glyph that is rendered in a TBFontFace. */
class TBFontEffect
{
public:
	TBFontEffect();
	~TBFontEffect();

	/** Set blur radius. 0 means no blur. */
	void SetBlurRadius(int blur_radius);

	/** Returns true if the result is in RGB and should not be painted using the color parameter
		given to DrawString. In other words: It's a color glyph. */
	bool RendersInRGB() const { return false; }

	TBFontGlyphData *Render(TBGlyphMetrics *metrics, const TBFontGlyphData *src);
private:
	// Blur data
	int m_blur_radius;
	float *m_tempBuffer;
	float *m_kernel;
	TBTempBuffer m_blur_temp;
};

/** TBFontFace represents a loaded font that can measure and render strings. */
class TBFontFace
{
public:
	TBFontFace(TBFontGlyphCache *glyph_cache, TBFontRenderer *renderer, const TBFontDescription &font_desc);
	~TBFontFace();

	/** Render all glyphs needed to display the string. */
	bool RenderGlyphs(const char *glyph_str, int glyph_str_len = TB_ALL_TO_TERMINATION);

	/** Get the vertical distance (positive) from the horizontal baseline to the highest character coordinate
		in a font face. */
	int GetAscent() const { return m_metrics.ascent; }

	/** Get the vertical distance (positive) from the horizontal baseline to the lowest character coordinate
		in the font face. */
	int GetDescent() const { return m_metrics.descent; }

	/** Get height of the font in pixels. */
	int GetHeight() const { return m_metrics.height; }

	/** Get the font description that was used to create this font. */
	TBFontDescription GetFontDescription() const { return m_font_desc; }

	/** Get the effect object, so the effect can be changed.
		Note: No glyphs are re-rendered. Only new glyphs are affected. */
	TBFontEffect *GetEffect() { return &m_effect; }

	/** Draw string at position x, y (marks the upper left corner of the text). */
	void DrawString(int x, int y, const TBColor &color, const char *str, int len = TB_ALL_TO_TERMINATION);

	/** Measure the width of the given string. Should measure len characters or to the null
		termination (whatever comes first). */
	int GetStringWidth(const char *str, int len = TB_ALL_TO_TERMINATION);

#ifdef TB_RUNTIME_DEBUG_INFO
	/** Render the glyph bitmaps on screen, to analyze fragment positioning. */
	void Debug();
#endif

	/** Set a background font which will always be rendered behind this one
	    when calling DrawString. Very usefull to add a shadow effect to a font. */
	void SetBackgroundFont(TBFontFace *font, const TBColor &col, int xofs, int yofs);
private:
	TBID GetHashId(UCS4 cp) const;
	TBFontGlyph *GetGlyph(UCS4 cp, bool render_if_needed);
	TBFontGlyph *CreateAndCacheGlyph(UCS4 cp);
	void RenderGlyph(TBFontGlyph *glyph);
	TBFontGlyphCache *m_glyph_cache;
	TBFontRenderer *m_font_renderer;
	TBFontDescription m_font_desc;
	TBFontMetrics m_metrics;
	TBFontEffect m_effect;
	TBTempBuffer m_temp_buffer;

	TBFontFace *m_bgFont;
	int m_bgX;
	int m_bgY;
	TBColor m_bgColor;
};

/** TBFontInfo provides information about a font file associated with a font id. */
class TBFontInfo
{
public:
	/** Get the font filename. */
	const char *GetFilename() const { return m_filename; }

	/** Get the font name. */
	const char *GetName() const { return m_name; }

	/** Get the font ID that can be used to create this font from a
		TBFontDescription (See TBFontDescription::SetID) */
	TBID GetID() const { return m_id; }

private:
	friend class TBFontManager;
	TBFontInfo(const char *filename, const char *name) : m_filename(filename), m_name(name), m_id(name) {}
	TBStr m_filename;
	TBStr m_name;
	TBID m_id;
};

/** TBFontManager creates and owns font faces (TBFontFace) which are looked up from
	TBFontDescription using GetFontFace.

	The fonts it can return must first have their file added and indexed (AddFontInfo),
	and then created CreateFontFace. Otherwise when asking for a font and it doesn't
	exist, it will use the default font.

	Font ID 0 is always populated with a dummy font that draws squares. This font is
	generally not used for other things than unit testing or as fallback when there is
	no font backend implemented yet. Since there is always at least the test font, no
	nullptr checks are needed.
*/
class TBFontManager
{
public:
	TBFontManager();
	~TBFontManager();

	/** Add a renderer so fonts supported by the renderer can be created. Ownership of the
		renderer is taken, until calling RemoveRenderer. */
	void AddRenderer(TBFontRenderer *renderer) { m_font_renderers.AddLast(renderer); }
	void RemoveRenderer(TBFontRenderer *renderer) { m_font_renderers.Remove(renderer); }

	/** Add TBFontInfo for the given font filename, so it can be loaded and identified
		using the font id in a TBFontDescription. */
	TBFontInfo *AddFontInfo(const char *filename, const char *name);

	/** Get TBFontInfo for the given font id, or nullptr if there is no match. */
	TBFontInfo *GetFontInfo(const TBID &id) const;

	/** Return true if there is a font loaded that match the given font description. */
	bool HasFontFace(const TBFontDescription &font_desc) const;

	/** Get a loaded font matching the description, or the default font if there is no exact match.
		If there is not even any default font loaded, it will return the test dummy font (rendering
		only squares). */
	TBFontFace *GetFontFace(const TBFontDescription &font_desc);

	/** Create and add a font with the given description. Returns the created font face, or
		nullptr on fail. The font is owned by this TBFontManager, and can be recieved from
		GetFontFace using the same TBFontDescription. */
	TBFontFace *CreateFontFace(const TBFontDescription &font_desc);

	/** Set the default font description. This is the font description that will be used by default
		for widgets. By default, the default description is using the test dummy font. */
	void SetDefaultFontDescription(const TBFontDescription &font_desc) { m_default_font_desc = font_desc; }
	TBFontDescription GetDefaultFontDescription() const { return m_default_font_desc; }

	/** Return the glyph cache used for fonts created by this font manager. */
	TBFontGlyphCache *GetGlyphCache() { return &m_glyph_cache; }
private:
	TBHashTableAutoDeleteOf<TBFontInfo> m_font_info;
	TBHashTableAutoDeleteOf<TBFontFace> m_fonts;
	TBLinkListAutoDeleteOf<TBFontRenderer> m_font_renderers;
	TBFontGlyphCache m_glyph_cache;
	TBFontDescription m_default_font_desc;
	TBFontDescription m_test_font_desc;
};

}; // namespace tb

#endif // TB_FONT_RENDERER_H
