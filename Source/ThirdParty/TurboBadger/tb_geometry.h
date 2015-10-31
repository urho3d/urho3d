// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_GEOMETRY_H
#define TB_GEOMETRY_H

#include "tb_core.h"

namespace tb {

/** Simple point class. */

class TBPoint
{
public:
	int x, y;
	TBPoint() : x(0), y(0) {}
	TBPoint(int x, int y) : x(x), y(y) {}
};

/** Simple rectangle class. */

class TBRect
{
public:
	int x, y, w, h;
	TBRect() : x(0), y(0), w(0), h(0) {}
	TBRect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	inline bool IsEmpty() const						{ return w <= 0 || h <= 0; }
	inline bool IsInsideOut() const					{ return w < 0 || h < 0; }
	inline bool Equals(const TBRect &rect) const	{ return rect.x == x && rect.y == y && rect.w == w && rect.h == h; }
	bool Intersects(const TBRect &rect) const;
	bool Contains(const TBPoint &p) const			{ return p.x >= x && p.y >= y && p.x < x + w && p.y < y + h; }

	inline void Reset()								{ x = y = w = h = 0; }
	inline void Set(int x, int y, int w, int h)		{ this->x = x; this->y = y; this->w = w; this->h = h; }

	inline TBRect Shrink(int left, int top, int right, int bottom) const	{ return TBRect(x + left, y + top, w - left - right, h - top - bottom); }
	inline TBRect Expand(int left, int top, int right, int bottom) const	{ return Shrink(-left, -top, -right, -bottom); }
	inline TBRect Shrink(int tx, int ty) const		{ return TBRect(x + tx, y + ty, w - tx * 2, h - ty * 2); }
	inline TBRect Expand(int tx, int ty) const		{ return Shrink(-tx, -ty); }
	inline TBRect Offset(int dx, int dy) const		{ return TBRect(x + dx, y + dy, w, h); }

	/** Return a rect moved inside bounding_rect. If the rect doesn't fit inside
		bounding_rect, it will be placed so the x and/or y matches bounding_rect. */
	TBRect MoveIn(const TBRect &bounding_rect) const;

	/** Return a rect centered in bounding_rect. */
	TBRect CenterIn(const TBRect &bounding_rect) const;

	TBRect Union(const TBRect &rect) const;
	TBRect Clip(const TBRect &clip_rect) const;
};

/** TBRegion does calculations on regions represented by a list of rectangles. */

class TBRegion
{
public:
	TBRegion();
	~TBRegion();

	/** Remove the rect at the given index. */
	void RemoveRect(int index);

	/** Remove the rect at the given index.
		This method will change the order of rectangles after index. */
	void RemoveRectFast(int index);

	/** Remove all rectangles so the region becomes empty.
		If free_memory is false, the internal buffers will be reused
		if more rectangles are added again under its life time. */
	void RemoveAll(bool free_memory = true);

	/** Set the region to the given rect. */
	bool Set(const TBRect &rect);

	/** Add the rect without doing any overlap check.
		If coalesce is true, it will coalesce the rectangle
		with existing rectangles if possible (until there's
		nothing more to coalesce it with). */
	bool AddRect(const TBRect &rect, bool coalesce);

	/** Include the rect in the region.
		This will add only the parts that's not already in the region so the result doesn't
		contain overlap parts. This assumes there's no overlap in the region already! */
	bool IncludeRect(const TBRect &include_rect);

	/** Exclude the rect from the region. */
	bool ExcludeRect(const TBRect &exclude_rect);

	/** Add the rectangles that's left of rect after excluding exclude_rect. */
	bool AddExcludingRects(const TBRect &rect, const TBRect &exclude_rect, bool coalesce);

	bool IsEmpty() const							{ return m_num_rects == 0; }
	int GetNumRects() const							{ return m_num_rects; }
	const TBRect &GetRect(int index) const;
private:
	TBRect *m_rects;
	int m_num_rects;
	int m_capacity;
	bool GrowIfNeeded();
};

}; // namespace tb

#endif // TB_GEOMETRY_H
