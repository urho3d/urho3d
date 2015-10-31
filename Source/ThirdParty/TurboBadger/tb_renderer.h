// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_RENDERER_H
#define TB_RENDERER_H

#include "tb_core.h"
#include "tb_geometry.h"
#include "tb_color.h"
#include "tb_linklist.h"

namespace tb {

class TBBitmapFragment;

/** TBRendererListener is a listener for TBRenderer. */
class TBRendererListener : public TBLinkOf<TBRendererListener>
{
public:
	virtual ~TBRendererListener() {}

	/** Called when the context has been lost and all TBBitmaps need to be deleted.
		NOTE: Only do cleanup here. It's not safe to do work on any bitmap since the
		context is already lost. */
	virtual void OnContextLost() = 0;

	/** Called when the context has been restored again, and new TBBitmaps can be created
		again. */
	virtual void OnContextRestored() = 0;
};

/** TBBitmap is a minimal interface for bitmap to be painted by TBRenderer. */

class TBBitmap
{
public:
	/** Note: Implementations for batched renderers should call TBRenderer::FlushBitmap
		to make sure any active batch is being flushed before the bitmap is deleted. */
	virtual ~TBBitmap() {}

	virtual int Width() = 0;
	virtual int Height() = 0;

	/** Update the bitmap with the given data (in BGRA32 format).
		Note: Implementations for batched renderers should call TBRenderer::FlushBitmap
		to make sure any active batch is being flushed before the bitmap is changed. */
	virtual void SetData(uint32 *data) = 0;
};

/** TBRenderer is a minimal interface for painting strings and bitmaps. */

class TBRenderer
{
public:
	virtual ~TBRenderer() {}

	/** Should be called before invoking paint on any widget.
		render_target_w and render_target_h should be the size of the render target
		that the renderer renders to. I.e window size, screen size or frame buffer object. */
	virtual void BeginPaint(int render_target_w, int render_target_h) = 0;
	virtual void EndPaint() = 0;

	/** Translate all drawing with the given offset */
	virtual void Translate(int dx, int dy) = 0;

	/** Set the current opacity that should apply to all drawing (0.f-1.f). */
	virtual void SetOpacity(float opacity) = 0;
	virtual float GetOpacity() = 0;

	/** Set a clip rect to the renderer. add_to_current should be true when
		pushing a new cliprect that should clip inside the last clip rect,
		and false when restoring.
		It will return the clip rect that was in use before this call. */
	virtual TBRect SetClipRect(const TBRect &rect, bool add_to_current) = 0;

	/** Get the current clip rect. Note: This may be different from the rect
		sent to SetClipRect, due to intersecting with the previous cliprect! */
	virtual TBRect GetClipRect() = 0;

	/** Draw the src_rect part of the fragment stretched to dst_rect.
		dst_rect or src_rect can have negative width and height to achieve horizontal and vertical flip. */
	virtual void DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmapFragment *bitmap_fragment) = 0;

	/** Draw the src_rect part of the bitmap stretched to dst_rect.
		dst_rect or src_rect can have negative width and height to achieve horizontal and vertical flip. */
	virtual void DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmap *bitmap) = 0;

	/** Draw the src_rect part of the fragment stretched to dst_rect.
		The bitmap will be used as a mask for the color.
		dst_rect or src_rect can have negative width and height to achieve horizontal and vertical flip. */
	virtual void DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmapFragment *bitmap_fragment) = 0;

	/** Draw the src_rect part of the bitmap stretched to dst_rect.
		The bitmap will be used as a mask for the color.
		dst_rect or src_rect can have negative width and height to achieve horizontal and vertical flip. */
	virtual void DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmap *bitmap) = 0;

	/** Draw the bitmap tiled into dst_rect. */
	virtual void DrawBitmapTile(const TBRect &dst_rect, TBBitmap *bitmap) = 0;

	/** Draw a 1px thick rectangle outline. */
	virtual void DrawRect(const TBRect &dst_rect, const TBColor &color) = 0;

	/** Draw a filled rectangle. */
	virtual void DrawRectFill(const TBRect &dst_rect, const TBColor &color) = 0;

	/** Make sure the given bitmap fragment is flushed from any batching, because it may
		be changed or deleted after this call. */
	virtual void FlushBitmapFragment(TBBitmapFragment *bitmap_fragment) = 0;

	/** Create a new TBBitmap from the given data (in BGRA32 format).
		Width and height must be a power of two.
		Return nullptr if fail. */
	virtual TBBitmap *CreateBitmap(int width, int height, uint32 *data) = 0;

	/** Add a listener to this renderer. Does not take ownership. */
	void AddListener(TBRendererListener *listener) { m_listeners.AddLast(listener); }

	/** Remove a listener from this renderer. */
	void RemoveListener(TBRendererListener *listener) { m_listeners.Remove(listener); }

	/** Invoke OnContextLost on all listeners.
		Call when bitmaps should be forgotten. */
	void InvokeContextLost();

	/** Invoke OnContextRestored on all listeners.
		Call when bitmaps can safely be restored. */
	void InvokeContextRestored();

	/** Defines the hint given to BeginBatchHint. */
	enum BATCH_HINT {
		/** All calls are either DrawBitmap or DrawBitmapColored with the same bitmap
			fragment. */
		BATCH_HINT_DRAW_BITMAP_FRAGMENT
	};

	/** A hint to batching renderers that the following set of draw calls are of the
		same type so batching might be optimized.
		The hint defines what operations are allowed between BeginBatchHint
		until EndBatchHint is called. All other draw operations are invalid.
		It's not valid to nest calls to BeginBatchHint. */
	virtual void BeginBatchHint(BATCH_HINT hint) {}

	/** End the hint scope started with BeginBatchHint. */
	virtual void EndBatchHint() {}
private:
	TBLinkListOf<TBRendererListener> m_listeners;
};

}; // namespace tb

#endif // TB_RENDERER_H
