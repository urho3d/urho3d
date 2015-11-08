// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_skin_util.h"

namespace tb {

static int GetFadeoutSize(int scrolled_distance, int fadeout_length)
{
	// Make it appear gradually
	//float factor = scrolled_distance / 10.f;
	//factor = CLAMP(factor, 0.5f, 1);
	//return (int)(fadeout_length * factor);
	return scrolled_distance > 0 ? fadeout_length : 0;
}

void DrawEdgeFadeout(const TBRect &dst_rect, TBID skin_x, TBID skin_y,
					 int left, int top, int right, int bottom)
{
	if (TBSkinElement *skin = g_tb_skin->GetSkinElement(skin_x))
	{
		if (skin->bitmap)
		{
			int bw = skin->bitmap->Width();
			int bh = skin->bitmap->Height();
			int dw;
			if ((dw = GetFadeoutSize(left, bw)) > 0)
				g_renderer->DrawBitmap(TBRect(dst_rect.x, dst_rect.y, dw, dst_rect.h), TBRect(0, 0, bw, bh), skin->bitmap);
			if ((dw = GetFadeoutSize(right, bw)) > 0)
				g_renderer->DrawBitmap(TBRect(dst_rect.x + dst_rect.w - dw, dst_rect.y, dw, dst_rect.h), TBRect(bw, 0, -bw, bh), skin->bitmap);
		}
	}
	if (TBSkinElement *skin = g_tb_skin->GetSkinElement(skin_y))
	{
		if (skin->bitmap)
		{
			int bw = skin->bitmap->Width();
			int bh = skin->bitmap->Height();
			int dh;
			if ((dh = GetFadeoutSize(top, bh)) > 0)
				g_renderer->DrawBitmap(TBRect(dst_rect.x, dst_rect.y, dst_rect.w, dh), TBRect(0, 0, bw, bh), skin->bitmap);
			if ((dh = GetFadeoutSize(bottom, bh)) > 0)
				g_renderer->DrawBitmap(TBRect(dst_rect.x, dst_rect.y + dst_rect.h - dh, dst_rect.w, dh), TBRect(0, bh, bw, -bh), skin->bitmap);
		}
	}
}

}; // namespace tb
