// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_TAB_CONTAINER_H
#define TB_TAB_CONTAINER_H

#include "tb_widgets_common.h"

namespace tb {

/** TBTabLayout is a TBLayout used in TBTabContainer to apply
	some default properties on any TBButton added to it. */
class TBTabLayout : public TBLayout
{
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBTabLayout, TBLayout);

	virtual void OnChildAdded(TBWidget *child);
	virtual PreferredSize OnCalculatePreferredContentSize(const SizeConstraints &constraints);
};

/** TBTabContainer - A container with tabs for multiple pages. */

class TBTabContainer : public TBWidget
{
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBTabContainer, TBWidget);

	TBTabContainer();
	~TBTabContainer();

	/** Set along which axis the content should layouted.
		Use SetAlignment instead for more choice! Also, calling
		SetAxis directly does not update the current alignment. */
	virtual void SetAxis(AXIS axis);
	virtual AXIS GetAxis() const { return m_root_layout.GetAxis(); }

	/** Set alignment of the tabs. */
	void SetAlignment(TB_ALIGN align);
	TB_ALIGN GetAlignment() const { return m_align; }

	/** Set which page should be selected and visible. */
	virtual void SetValue(int value);
	virtual int GetValue() { return m_current_page; }

	/** Set which page should be selected and visible. */
	void SetCurrentPage(int index) { SetValue(index); }
	int GetCurrentPage() { return GetValue(); }
	int GetNumPages();

	/** Return the widget that is the current page, or nullptr if none is active. */
	TBWidget *GetCurrentPageWidget() const;

	virtual void OnInflate(const INFLATE_INFO &info);
	virtual bool OnEvent(const TBWidgetEvent &ev);
	virtual void OnProcess();

	virtual TBWidget *GetContentRoot() { return &m_content_root; }
	TBLayout *GetTabLayout() { return &m_tab_layout; }
protected:
	TBLayout m_root_layout;
	TBTabLayout m_tab_layout;
	TBWidget m_content_root;
	bool m_need_page_update;
	int m_current_page;
	TB_ALIGN m_align;
};

};

#endif // TB_TAB_CONTAINER_H
