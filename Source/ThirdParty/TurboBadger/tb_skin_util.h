// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_SKIN_UTIL_H
#define TB_SKIN_UTIL_H

#include "tb_skin.h"

namespace tb {

/** Draw fade out skin elements at the edges of dst_rect if needed.
	It indicates to the user that there is hidden content.
	left, top, right, bottom specifies the (positive) distance scrolled
	from the limit. */
void DrawEdgeFadeout(const TBRect &dst_rect, TBID skin_x, TBID skin_y,
					 int left, int top, int right, int bottom);

}; // namespace tb

#endif // TB_SKIN_UTIL_H
