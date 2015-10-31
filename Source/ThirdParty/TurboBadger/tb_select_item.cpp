// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_select.h"
#include "tb_menu_window.h"
#include "tb_widgets_listener.h"
#include "tb_language.h"
#include <assert.h>
#include <stdlib.h>

namespace tb {

/** TBSimpleLayoutItemWidget is a item containing a layout with the following:
	-TBSkinImage showing the item image.
	-TBTextField showing the item string.
	-TBSkinImage showing the arrow for items with a submenu.
	It also handles submenu events. */

class TBSimpleLayoutItemWidget : public TBLayout, private TBWidgetListener
{
public:
	TBSimpleLayoutItemWidget(TBID image, TBSelectItemSource *source, const char *str);
	~TBSimpleLayoutItemWidget();
	virtual bool OnEvent(const TBWidgetEvent &ev);
private:
	TBSelectItemSource *m_source;
	TBTextField m_textfield;
	TBSkinImage m_image;
	TBSkinImage m_image_arrow;
	TBMenuWindow *m_menu; ///< Points to the submenu window if opened
	virtual void OnWidgetDelete(TBWidget *widget);
	void OpenSubMenu();
	void CloseSubMenu();
};

// == TBSimpleLayoutItemWidget ==============================================================================

TBSimpleLayoutItemWidget::TBSimpleLayoutItemWidget(TBID image, TBSelectItemSource *source, const char *str)
	: m_source(source)
	, m_menu(nullptr)
{
	SetSkinBg(TBIDC("TBSelectItem"));
	SetLayoutDistribution(LAYOUT_DISTRIBUTION_AVAILABLE);
	SetPaintOverflowFadeout(false);

	if (image)
	{
		m_image.SetSkinBg(image);
		m_image.SetIgnoreInput(true);
		AddChild(&m_image);
	}

	m_textfield.SetText(str);
	m_textfield.SetTextAlign(TB_TEXT_ALIGN_LEFT);
	m_textfield.SetIgnoreInput(true);
	AddChild(&m_textfield);

	if (source)
	{
		m_image_arrow.SetSkinBg(TBIDC("arrow.right"));
		m_image_arrow.SetIgnoreInput(true);
		AddChild(&m_image_arrow);
	}
}

TBSimpleLayoutItemWidget::~TBSimpleLayoutItemWidget()
{
	if (m_image_arrow.GetParent())
		RemoveChild(&m_image_arrow);
	RemoveChild(&m_textfield);
	if (m_image.GetParent())
		RemoveChild(&m_image);
	CloseSubMenu();
}

bool TBSimpleLayoutItemWidget::OnEvent(const TBWidgetEvent &ev)
{
	if (m_source && ev.type == EVENT_TYPE_CLICK && ev.target == this)
	{
		OpenSubMenu();
		return true;
	}
	return false;
}

void TBSimpleLayoutItemWidget::OnWidgetDelete(TBWidget *widget)
{
	assert(widget == m_menu);
	CloseSubMenu();
}

void TBSimpleLayoutItemWidget::OpenSubMenu()
{
	if (m_menu)
		return;

	// Open a new menu window for the submenu with this widget as target
	m_menu = new TBMenuWindow(this, TBIDC("submenu"));
	if (m_menu)
	{
		SetState(WIDGET_STATE_SELECTED, true);
		m_menu->AddListener(this);
		m_menu->Show(m_source, TBPopupAlignment(TB_ALIGN_RIGHT), -1);
	}
}

void TBSimpleLayoutItemWidget::CloseSubMenu()
{
	if (!m_menu)
		return;

	SetState(WIDGET_STATE_SELECTED, false);
	m_menu->RemoveListener(this);
	if (!m_menu->GetIsDying())
		m_menu->Close();
	m_menu = nullptr;
}

// == TBSelectItemViewer ==============================================================================

void TBSelectItemViewer::SetSource(TBSelectItemSource *source)
{
	if (m_source == source)
		return;

	if (m_source)
		m_source->m_viewers.Remove(this);
	m_source = source;
	if (m_source)
		m_source->m_viewers.AddLast(this);

	OnSourceChanged();
}

// == TBSelectItemSource ====================================================================================

TBSelectItemSource::~TBSelectItemSource()
{
	// If this assert trig, you are deleting a model that's still set on some
	// TBSelect widget. That might be dangerous.
	assert(!m_viewers.HasLinks());
}

bool TBSelectItemSource::Filter(int index, const char *filter)
{
	const char *str = GetItemString(index);
	if (str && stristr(str, filter))
		return true;
	return false;
}

TBWidget *TBSelectItemSource::CreateItemWidget(int index, TBSelectItemViewer *viewer)
{
	const char *string = GetItemString(index);
	TBSelectItemSource *sub_source = GetItemSubSource(index);
	TBID image = GetItemImage(index);
	if (sub_source || image)
	{
		if (TBSimpleLayoutItemWidget *itemwidget = new TBSimpleLayoutItemWidget(image, sub_source, string))
			return itemwidget;
	}
	else if (string && *string == '-')
	{
		if (TBSeparator *separator = new TBSeparator)
		{
			separator->SetGravity(WIDGET_GRAVITY_ALL);
			separator->SetSkinBg(TBIDC("TBSelectItem.separator"));
			return separator;
		}
	}
	else if (TBTextField *textfield = new TBTextField)
	{
		textfield->SetSkinBg("TBSelectItem");
		textfield->SetText(string);
		textfield->SetTextAlign(TB_TEXT_ALIGN_LEFT);
		return textfield;
	}
	return nullptr;
}

void TBSelectItemSource::InvokeItemChanged(int index, TBSelectItemViewer *exclude_viewer)
{
	TBLinkListOf<TBSelectItemViewer>::Iterator iter = m_viewers.IterateForward();
	while (TBSelectItemViewer *viewer = iter.GetAndStep())
		if (viewer != exclude_viewer)
			viewer->OnItemChanged(index);
}

void TBSelectItemSource::InvokeItemAdded(int index)
{
	TBLinkListOf<TBSelectItemViewer>::Iterator iter = m_viewers.IterateForward();
	while (TBSelectItemViewer *viewer = iter.GetAndStep())
		viewer->OnItemAdded(index);
}

void TBSelectItemSource::InvokeItemRemoved(int index)
{
	TBLinkListOf<TBSelectItemViewer>::Iterator iter = m_viewers.IterateForward();
	while (TBSelectItemViewer *viewer = iter.GetAndStep())
		viewer->OnItemRemoved(index);
}

void TBSelectItemSource::InvokeAllItemsRemoved()
{
	TBLinkListOf<TBSelectItemViewer>::Iterator iter = m_viewers.IterateForward();
	while (TBSelectItemViewer *viewer = iter.GetAndStep())
		viewer->OnAllItemsRemoved();
}

}; // namespace tb
