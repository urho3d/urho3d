// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_SCROLL_CONTAINER_H
#define TB_SCROLL_CONTAINER_H

#include "tb_widgets_common.h"

namespace tb {

enum SCROLL_MODE {
	SCROLL_MODE_X_Y,			///< X and Y always			scroll-mode: xy
	SCROLL_MODE_Y,				///< Y always (X never)		scroll-mode: y
	SCROLL_MODE_Y_AUTO,			///< Y auto (X never)		scroll-mode: y-auto
	SCROLL_MODE_X_AUTO_Y_AUTO,	///< X auto, Y auto			scroll-mode: auto
	SCROLL_MODE_OFF				///< X any Y never			scroll-mode: off
};

/** TBScrollContainerRoot - Internal for TBScrollContainer */

class TBScrollContainerRoot : public TBWidget
{
private: // May only be used by TBScrollContainer.
	friend class TBScrollContainer;
	TBScrollContainerRoot() {}
public:
	virtual void OnPaintChildren(const PaintProps &paint_props);
	virtual void GetChildTranslation(int &x, int &y) const;
};

/** TBScrollBarVisibility - Helper for TBScrollContainer or any other scrollable
	container that needs to solve scrollbar visibility according to SCROLL_MODE. */
class TBScrollBarVisibility
{
public:
	TBScrollBarVisibility () : x_on(false), y_on(false), visible_w(0), visible_h(0) {}

	static TBScrollBarVisibility Solve(SCROLL_MODE mode, int content_w, int content_h,
														int available_w, int available_h,
														int scrollbar_x_h, int scrollbar_y_w);
	static bool IsAlwaysOnX(SCROLL_MODE mode) { return mode == SCROLL_MODE_X_Y; }
	static bool IsAlwaysOnY(SCROLL_MODE mode) { return mode == SCROLL_MODE_X_Y || mode == SCROLL_MODE_Y; }
public:
	bool x_on, y_on;
	int visible_w, visible_h;
};

/** TBScrollContainer - A container with scrollbars that can scroll its children. */

class TBScrollContainer : public TBWidget
{
friend class TBScrollContainerRoot;
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBScrollContainer, TBWidget);

	TBScrollContainer();
	~TBScrollContainer();

	/** Set to true if the preferred size of this container should adapt to the preferred
		size of the content. This is disabled by default. */
	void SetAdaptToContentSize(bool adapt);
	bool GetAdaptToContentSize() { return m_adapt_to_content_size; }

	/** Set to true if the content should adapt to the available size of this container
		when it's larger than the preferred size. */
	void SetAdaptContentSize(bool adapt);
	bool GetAdaptContentSize() { return m_adapt_content_size; }

	void SetScrollMode(SCROLL_MODE mode);
	SCROLL_MODE GetScrollMode() { return m_mode; }

	virtual void ScrollTo(int x, int y);
	virtual TBWidget::ScrollInfo GetScrollInfo();
	virtual TBWidget *GetScrollRoot() { return &m_root; }

	virtual void InvalidateLayout(INVALIDATE_LAYOUT il);

	virtual TBRect GetPaddingRect();
	virtual PreferredSize OnCalculatePreferredContentSize(const SizeConstraints &constraints);

	virtual void OnInflate(const INFLATE_INFO &info);
	virtual bool OnEvent(const TBWidgetEvent &ev);
	virtual void OnProcess();
	virtual void OnResized(int old_w, int old_h);

	virtual TBWidget *GetContentRoot() { return &m_root; }
protected:
	TBScrollBar m_scrollbar_x;
	TBScrollBar m_scrollbar_y;
	TBScrollContainerRoot m_root;
	bool m_adapt_to_content_size;
	bool m_adapt_content_size;
	bool m_layout_is_invalid;
	SCROLL_MODE m_mode;
	void ValidateLayout(const SizeConstraints &constraints);
};

};

#endif // TB_SCROLL_CONTAINER_H
