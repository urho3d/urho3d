// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_RENDERER_BATCHER_H
#define TB_RENDERER_BATCHER_H

#include "tb_renderer.h"

#ifdef TB_RENDERER_BATCHER

namespace tb {

#define VERTEX_BATCH_SIZE 6 * 2048

/** TBRendererBatcher is a helper class that implements batching of draw operations for a TBRenderer.
	If you do not want to do your own batching you can subclass this class instead of TBRenderer.
	If overriding any function in this class, make sure to call the base class too. */
class TBRendererBatcher : public TBRenderer
{
public:
	/** Vertex stored in a Batch */
	struct Vertex
	{
		float x, y;
		float u, v;
		union {
			struct { unsigned char r, g, b, a; };
			uint32 col;
		};
	};
	/** A batch which should be rendered. */
	class Batch
	{
	public:
		Batch() : vertex_count(0), bitmap(nullptr), fragment(nullptr), batch_id(0), is_flushing(false) {}
		void Flush(TBRendererBatcher *batch_renderer);
		Vertex *Reserve(TBRendererBatcher *batch_renderer, int count);

		Vertex vertex[VERTEX_BATCH_SIZE];
		int vertex_count;

		TBBitmap *bitmap;
		TBBitmapFragment *fragment;

		uint32 batch_id;
		bool is_flushing;

        TBRect clipRect;
	};

	TBRendererBatcher();
	virtual ~TBRendererBatcher();

	virtual void BeginPaint(int render_target_w, int render_target_h);
	virtual void EndPaint();

	virtual void Translate(int dx, int dy);

	virtual void SetOpacity(float opacity);
	virtual float GetOpacity();

	virtual TBRect SetClipRect(const TBRect &rect, bool add_to_current);
	virtual TBRect GetClipRect();

	virtual void DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmapFragment *bitmap_fragment);
	virtual void DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmap *bitmap);
	virtual void DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmapFragment *bitmap_fragment);
	virtual void DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmap *bitmap);
	virtual void DrawBitmapTile(const TBRect &dst_rect, TBBitmap *bitmap);
	virtual void DrawRect(const TBRect &dst_rect, const TBColor &color);
	virtual void DrawRectFill(const TBRect &dst_rect, const TBColor &color);
	virtual void FlushBitmap(TBBitmap *bitmap);
	virtual void FlushBitmapFragment(TBBitmapFragment *bitmap_fragment);

	virtual void BeginBatchHint(TBRenderer::BATCH_HINT hint) {}
	virtual void EndBatchHint() {}

	// == Methods that need implementation in subclasses ================================
	virtual TBBitmap *CreateBitmap(int width, int height, uint32 *data) = 0;
	virtual void RenderBatch(Batch *batch) = 0;
	virtual void SetClipRect(const TBRect &rect) = 0;
protected:
	uint8 m_opacity;
	TBRect m_screen_rect;
	TBRect m_clip_rect;
	int m_translation_x;
	int m_translation_y;

	float m_u, m_v, m_uu, m_vv; ///< Some temp variables
	Batch batch; ///< The one and only batch. this should be improved.

	void AddQuadInternal(const TBRect &dst_rect, const TBRect &src_rect, uint32 color, TBBitmap *bitmap, TBBitmapFragment *fragment);
	void FlushAllInternal();
};

}; // namespace tb

#endif // TB_RENDERER_BATCHER

#endif // TB_RENDERER_BATCHER_H
