// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_font_renderer.h"
#include "tb_renderer.h"
#include "tb_tempbuffer.h"
#include "tb_system.h"
#include "tb_node_tree.h"
#include "tb_hashtable.h"

#ifdef TB_FONT_RENDERER_TBBF

using namespace tb;

struct GLYPH {
	int x, w;
};

/** TBBFRenderer renders a bitmap font.

	A font is loaded from a text file and at least one image that contains
	glyphs for a given size. The number of glyphs that the font contains is
	defined by the glyph string defined in the text file.

	Text file format (in tb.txt format parsed by parser/tb_parser.h):

		- info>glyph_str			Should specify which characters the image
								file contains.
		- info>rgb				Set to 1 for color fonts that should never
								care about the text color when drawing.
								Set to 0 to let drawing blend using the text
								color. Default 0.
		- size xx				Specify font size xx. Should contain the
								following nodes:
			- bitmap				The image file name (in the same folder).
			- ascent				The ascent. Default 0.
			- descent			The descent. Default 0.
			- x_ofs				The x offset for all glyph. This can be
								used in combination with advance_delta to
								compensate for f.ex glow that extend
								around the glyph.  Default 0.
			- advance_delta		The advance delta for all glyphs. This can
								be used to compensate for f.ex shadow that
								should not add to each glyphs horizontal
								advance. Default 0.
			- space_advance		The advance for the space character.

	Image file format

		Should contain the characters specified in the glyph_str.

		All characters should be placed on one long line. Each glyph will be
		found, measured and cropped automatically. In order for this to work,
		each glyph must touch pixels somewhere from the left to the right edge.
		So if you f.ex have a quotation mark, you will have to make sure there
		is pixels with alpha > 0 between the two dots, otherwise the dots will
		be identified as different glyphs.
*/
class TBBFRenderer : public TBFontRenderer
{
public:
	TBBFRenderer();
	~TBBFRenderer();

	bool Load(const char *filename, int size);
	bool FindGlyphs();
	GLYPH *FindNext(UCS4 cp, int x);

	virtual TBFontFace *Create(TBFontManager *font_manager, const char *filename,
								const TBFontDescription &font_desc);

	virtual TBFontMetrics GetMetrics();
	virtual bool RenderGlyph(TBFontGlyphData *dst_bitmap, UCS4 cp);
	virtual void GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp);
private:
	TBNode m_node;
	TBFontMetrics m_metrics;
	TBImageLoader *m_img;
	int m_size;
	int m_x_ofs;
	int m_advance_delta;
	int m_space_advance;
	int m_rgb;
	TBHashTableAutoDeleteOf<GLYPH> m_glyph_table;
};

TBBFRenderer::TBBFRenderer()
	: m_img(nullptr)
	, m_size(0)
	, m_x_ofs(0)
	, m_advance_delta(0)
	, m_space_advance(0)
	, m_rgb(0)
{
}

TBBFRenderer::~TBBFRenderer()
{
	delete m_img;
}

TBFontMetrics TBBFRenderer::GetMetrics()
{
	return m_metrics;
}

bool TBBFRenderer::RenderGlyph(TBFontGlyphData *data, UCS4 cp)
{
	if (cp == ' ')
		return false;
	GLYPH *glyph;
	if ((glyph = m_glyph_table.Get(cp)) ||
		(glyph = m_glyph_table.Get('?')))
	{
		data->w = glyph->w;
		data->h = m_img->Height();
		data->stride = m_img->Width();
		data->data32 = m_img->Data() + glyph->x;
		data->rgb = m_rgb ? true : false;
		return true;
	}
	return false;
}

void TBBFRenderer::GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp)
{
	metrics->x = m_x_ofs;
	metrics->y = -m_metrics.ascent;
	if (cp == ' ')
		metrics->advance = m_space_advance;
	else if (GLYPH *glyph = m_glyph_table.Get(cp))
		metrics->advance = glyph->w + m_advance_delta;
	else if (GLYPH *glyph = m_glyph_table.Get('?'))
		metrics->advance = glyph->w + m_advance_delta;
}

bool TBBFRenderer::Load(const char *filename, int size)
{
	m_size = size;
	if (!m_node.ReadFile(filename))
		return false;

	// Check for size nodes and get the one closest to the size we want.
	TBNode *size_node = nullptr;
	for (TBNode *n = m_node.GetFirstChild(); n; n = n->GetNext())
	{
		if (strcmp(n->GetName(), "size") == 0)
		{
			if (!size_node || ABS(m_size - n->GetValue().GetInt()) < ABS(m_size - size_node->GetValue().GetInt()))
				size_node = n;
		}
	}
	if (!size_node)
		return false;

	// Metrics
	m_metrics.ascent = size_node->GetValueInt("ascent", 0);
	m_metrics.descent = size_node->GetValueInt("descent", 0);
	m_metrics.height = m_metrics.ascent + m_metrics.descent;

	// Other data
	m_advance_delta = size_node->GetValueInt("advance_delta", 0);
	m_space_advance = size_node->GetValueInt("space_advance", 0);
	m_x_ofs = size_node->GetValueInt("x_ofs", 0);

	// Info
	m_rgb = m_node.GetValueInt("info>rgb", 0);

	// Get the path for the bitmap file.
	TBTempBuffer bitmap_filename;
	if (!bitmap_filename.AppendPath(filename))
		return false;

	// Append the bitmap filename for the given size.
	bitmap_filename.AppendString(size_node->GetValueString("bitmap", ""));

	m_img = TBImageLoader::CreateFromFile(bitmap_filename.GetData());

	return FindGlyphs();
}

inline unsigned char GetAlpha(uint32 color)
{
	return (color & 0xff000000) >> 24;
}

bool TBBFRenderer::FindGlyphs()
{
	if (!m_img)
		return false;

	const char *glyph_str = m_node.GetValueString("info>glyph_str", nullptr);
	if (!glyph_str)
		return false;

	int glyph_str_len = strlen(glyph_str);
	int i = 0;
	int x = 0;
	while (UCS4 uc = utf8::decode_next(glyph_str, &i, glyph_str_len))
	{
		if (GLYPH *glyph = FindNext(uc, x))
		{
			m_glyph_table.Add(uc, glyph); // OOM!
			x = glyph->x + glyph->w + 1;
		}
		else
			break;
	}
	return true;
}

GLYPH *TBBFRenderer::FindNext(UCS4 cp, int x)
{
	int width = m_img->Width();
	int height = m_img->Height();
	uint32 *data32 = m_img->Data();

	if (x >= width)
		return nullptr;

	GLYPH *glyph = new GLYPH;
	if (!glyph)
		return nullptr;

	glyph->x = -1;
	glyph->w = -1;

	// Find the left edge of the glyph
	for (int i = x; i < width && glyph->x == -1; i++)
	{
		for (int j = 0; j < height; j++)
			if (GetAlpha(data32[i + j * width]))
			{
				glyph->x = x = i;
				break;
			}
	}

	// Find the right edge of the glyph
	for (int i = x; i < width; i++)
	{
		int j;
		for (j = 0; j < height; j++)
		{
			if (GetAlpha(data32[i + j * width]))
				break;
		}
		if (j == height) // The whole col was clear, so we found the edge
		{
			glyph->w = i - glyph->x;
			break;
		}
	}

	if (glyph->x == -1 || glyph->w == -1)
	{
		delete glyph;
		return nullptr;
	}
	return glyph;
}

TBFontFace *TBBFRenderer::Create(TBFontManager *font_manager, const char *filename, const TBFontDescription &font_desc)
{
	if (!strstr(filename, ".tb.txt"))
		return nullptr;
	if (TBBFRenderer *fr = new TBBFRenderer())
	{
		if (fr->Load(filename, (int) font_desc.GetSize()))
			if (TBFontFace *font = new TBFontFace(font_manager->GetGlyphCache(), fr, font_desc))
				return font;
		delete fr;
	}
	return nullptr;
}

void register_tbbf_font_renderer()
{
	if (TBBFRenderer *fr = new TBBFRenderer)
		g_font_manager->AddRenderer(fr);
}

#endif // TB_FONT_RENDERER_TBBF
