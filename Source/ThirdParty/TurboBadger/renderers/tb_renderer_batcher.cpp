// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "renderers/tb_renderer_batcher.h"
#include "tb_bitmap_fragment.h"
#include "tb_system.h"

#ifdef TB_RENDERER_BATCHER

namespace tb {

// == TBRendererBatcher::Batch ==========================================================

#ifdef TB_RUNTIME_DEBUG_INFO
uint32 dbg_begin_paint_batch_id = 0;
uint32 dbg_frame_triangle_count = 0;
#endif // TB_RUNTIME_DEBUG_INFO

#define VER_COL(r, g, b, a) (((a)<<24) + ((b)<<16) + ((g)<<8) + r)
#define VER_COL_OPACITY(a) (0x00ffffff + (((uint32)a) << 24))

void TBRendererBatcher::Batch::Flush(TBRendererBatcher *batch_renderer)
{
	if (!vertex_count || is_flushing)
		return;

	// Prevent re-entrancy. Calling fragment->GetBitmap may end up calling TBBitmap::SetData
	// which will end up flushing any existing batch with that bitmap.
	is_flushing = true;

	if (fragment)
	{
		// Now it's time to ensure the bitmap data is up to date. A call to GetBitmap
		// with TB_VALIDATE_ALWAYS should guarantee that its data is validated.
		TBBitmap *frag_bitmap = fragment->GetBitmap(TB_VALIDATE_ALWAYS);
		((void)frag_bitmap); // silence warning about unused variable
		assert(frag_bitmap == bitmap);
	}

	batch_renderer->RenderBatch(this);

#ifdef TB_RUNTIME_DEBUG_INFO
	if (TB_DEBUG_SETTING(RENDER_BATCHES))
	{
		// This assumes we're drawing triangles. Need to modify this
		// if we start using strips, fans or whatever.
		dbg_frame_triangle_count += vertex_count / 3;

		// Draw the triangles again using a random color based on the batch
		// id. This indicates which triangles belong to the same batch.
		uint32 id = batch_id - dbg_begin_paint_batch_id;
		uint32 hash = id * (2166136261U ^ id);
		uint32 color = 0xAA000000 + (hash & 0x00FFFFFF);
		for (int i = 0; i < vertex_count; i++)
			vertex[i].col = color;
		bitmap = nullptr;
		batch_renderer->RenderBatch(this);
	}
#endif // TB_RUNTIME_DEBUG_INFO

	vertex_count = 0;

	batch_id++; // Will overflow eventually, but that doesn't really matter.

	is_flushing = false;
}

TBRendererBatcher::Vertex *TBRendererBatcher::Batch::Reserve(TBRendererBatcher *batch_renderer, int count)
{
	assert(count < VERTEX_BATCH_SIZE);
	if (vertex_count + count > VERTEX_BATCH_SIZE)
		Flush(batch_renderer);
	Vertex *ret = &vertex[vertex_count];
	vertex_count += count;
	return ret;
}

// == TBRendererBatcher ===================================================================

TBRendererBatcher::TBRendererBatcher()
	: m_opacity(255), m_translation_x(0), m_translation_y(0)
	, m_u(0), m_v(0), m_uu(0), m_vv(0)
{
}

TBRendererBatcher::~TBRendererBatcher()
{
}

void TBRendererBatcher::BeginPaint(int render_target_w, int render_target_h)
{
#ifdef TB_RUNTIME_DEBUG_INFO
	dbg_begin_paint_batch_id = batch.batch_id;
	dbg_frame_triangle_count = 0;
#endif // TB_RUNTIME_DEBUG_INFO

	m_screen_rect.Set(0, 0, render_target_w, render_target_h);
	m_clip_rect = m_screen_rect;
}

void TBRendererBatcher::EndPaint()
{
	FlushAllInternal();

#ifdef TB_RUNTIME_DEBUG_INFO
	if (TB_DEBUG_SETTING(RENDER_BATCHES))
		TBDebugPrint("Frame rendered using %d batches and a total of %d triangles.\n",
						batch.batch_id - dbg_begin_paint_batch_id,
						dbg_frame_triangle_count);
#endif // TB_RUNTIME_DEBUG_INFO
}

void TBRendererBatcher::Translate(int dx, int dy)
{
	m_translation_x += dx;
	m_translation_y += dy;
}

void TBRendererBatcher::SetOpacity(float opacity)
{
	int8 opacity8 = (uint8) (opacity * 255);
	if (opacity8 == m_opacity)
		return;
	m_opacity = opacity8;
}

float TBRendererBatcher::GetOpacity()
{
	return m_opacity / 255.f;
}

TBRect TBRendererBatcher::SetClipRect(const TBRect &rect, bool add_to_current)
{
	TBRect old_clip_rect = m_clip_rect;
	m_clip_rect = rect;
	m_clip_rect.x += m_translation_x;
	m_clip_rect.y += m_translation_y;

	if (add_to_current)
		m_clip_rect = m_clip_rect.Clip(old_clip_rect);

	FlushAllInternal();
	SetClipRect(m_clip_rect);

	old_clip_rect.x -= m_translation_x;
	old_clip_rect.y -= m_translation_y;
	return old_clip_rect;
}

TBRect TBRendererBatcher::GetClipRect()
{
	TBRect curr_clip_rect = m_clip_rect;
	curr_clip_rect.x -= m_translation_x;
	curr_clip_rect.y -= m_translation_y;
	return curr_clip_rect;
}

void TBRendererBatcher::DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmapFragment *bitmap_fragment)
{
	if (TBBitmap *bitmap = bitmap_fragment->GetBitmap(TB_VALIDATE_FIRST_TIME))
		AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y),
						src_rect.Offset(bitmap_fragment->m_rect.x, bitmap_fragment->m_rect.y),
						VER_COL_OPACITY(m_opacity), bitmap, bitmap_fragment);
}

void TBRendererBatcher::DrawBitmap(const TBRect &dst_rect, const TBRect &src_rect, TBBitmap *bitmap)
{
	AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y), src_rect, VER_COL_OPACITY(m_opacity), bitmap, nullptr);
}

void TBRendererBatcher::DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmapFragment *bitmap_fragment)
{
	if (TBBitmap *bitmap = bitmap_fragment->GetBitmap(TB_VALIDATE_FIRST_TIME))
	{
		uint32 a = (color.a * m_opacity) / 255;
		AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y),
						src_rect.Offset(bitmap_fragment->m_rect.x, bitmap_fragment->m_rect.y),
						VER_COL(color.r, color.g, color.b, a), bitmap, bitmap_fragment);
	}
}

void TBRendererBatcher::DrawBitmapColored(const TBRect &dst_rect, const TBRect &src_rect, const TBColor &color, TBBitmap *bitmap)
{
	uint32 a = (color.a * m_opacity) / 255;
	AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y),
					src_rect, VER_COL(color.r, color.g, color.b, a), bitmap, nullptr);
}

void TBRendererBatcher::DrawBitmapTile(const TBRect &dst_rect, TBBitmap *bitmap)
{
	AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y),
					TBRect(0, 0, dst_rect.w, dst_rect.h),
					VER_COL_OPACITY(m_opacity), bitmap, nullptr);
}

void TBRendererBatcher::DrawRect(const TBRect &dst_rect, const TBColor &color)
{
	if (dst_rect.IsEmpty())
		return;
	// Top
	DrawRectFill(TBRect(dst_rect.x, dst_rect.y, dst_rect.w, 1), color);
	// Bottom
	DrawRectFill(TBRect(dst_rect.x, dst_rect.y + dst_rect.h - 1, dst_rect.w, 1), color);
	// Left
	DrawRectFill(TBRect(dst_rect.x, dst_rect.y + 1, 1, dst_rect.h - 2), color);
	// Right
	DrawRectFill(TBRect(dst_rect.x + dst_rect.w - 1, dst_rect.y + 1, 1, dst_rect.h - 2), color);
}

void TBRendererBatcher::DrawRectFill(const TBRect &dst_rect, const TBColor &color)
{
	if (dst_rect.IsEmpty())
		return;
	uint32 a = (color.a * m_opacity) / 255;
	AddQuadInternal(dst_rect.Offset(m_translation_x, m_translation_y),
					TBRect(), VER_COL(color.r, color.g, color.b, a), nullptr, nullptr);
}

void TBRendererBatcher::AddQuadInternal(const TBRect &dst_rect, const TBRect &src_rect, uint32 color, TBBitmap *bitmap, TBBitmapFragment *fragment)
{
    if (batch.bitmap != bitmap)
    {
        batch.Flush(this);
        batch.bitmap = bitmap;
    }
    batch.fragment = fragment;

    // save clip rect
    batch.clipRect = m_clip_rect;

    if (bitmap)
    {
        #ifdef URHO3D_OPENGL
        float uvOffset = 0.0f;
        #else
        float uvOffset = 0.5f;
        #endif
        int bitmap_w = bitmap->Width();
        int bitmap_h = bitmap->Height();
        m_u  = (float)(src_rect.x + uvOffset)/ bitmap_w;
        m_v  = (float)(src_rect.y + uvOffset)/ bitmap_h;
        m_uu = (float)(src_rect.x + uvOffset + src_rect.w) / bitmap_w;
        m_vv = (float)(src_rect.y + uvOffset + src_rect.h) / bitmap_h;
    }

    // change triangle winding order to clock-wise
    Vertex *ver = batch.Reserve(this, 6);
    ver[0].x = (float) dst_rect.x;
    ver[0].y = (float) (dst_rect.y + dst_rect.h);
    ver[0].u = m_u;
    ver[0].v = m_vv;
    ver[0].col = color;
    ver[2].x = (float) (dst_rect.x + dst_rect.w);
    ver[2].y = (float) (dst_rect.y + dst_rect.h);
    ver[2].u = m_uu;
    ver[2].v = m_vv;
    ver[2].col = color;
    ver[1].x = (float) dst_rect.x;
    ver[1].y = (float) dst_rect.y;
    ver[1].u = m_u;
    ver[1].v = m_v;
    ver[1].col = color;

    ver[3].x = (float) dst_rect.x;
    ver[3].y = (float) dst_rect.y;
    ver[3].u = m_u;
    ver[3].v = m_v;
    ver[3].col = color;
    ver[5].x = (float) (dst_rect.x + dst_rect.w);
    ver[5].y = (float) (dst_rect.y + dst_rect.h);
    ver[5].u = m_uu;
    ver[5].v = m_vv;
    ver[5].col = color;
    ver[4].x = (float) (dst_rect.x + dst_rect.w);
    ver[4].y = (float) dst_rect.y;
    ver[4].u = m_uu;
    ver[4].v = m_v;
    ver[4].col = color;

    // Update fragments batch id (See FlushBitmapFragment)
    if (fragment)
        fragment->m_batch_id = batch.batch_id;
}

void TBRendererBatcher::FlushAllInternal()
{
	batch.Flush(this);
}

void TBRendererBatcher::FlushBitmap(TBBitmap *bitmap)
{
	// Flush the batch if it's using this bitmap (that is about to change or be deleted)
	if (batch.vertex_count && bitmap == batch.bitmap)
		batch.Flush(this);
}

void TBRendererBatcher::FlushBitmapFragment(TBBitmapFragment *bitmap_fragment)
{
	// Flush the batch if it is using this fragment (that is about to change or be deleted)
	// We know if it is in use in the current batch if its batch_id matches the current
	// batch_id in our (one and only) batch.
	// If we switch to a more advance batching system with multiple batches, we need to
	// solve this a bit differently.
	if (batch.vertex_count && bitmap_fragment->m_batch_id == batch.batch_id)
		batch.Flush(this);
}

}; // namespace tb

#endif // TB_RENDERER_BATCHER
