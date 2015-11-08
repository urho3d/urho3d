// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_widgets_reader.h"
#include "tb_widgets_common.h"
#include "tb_scroll_container.h"
#include "tb_tab_container.h"
#include "tb_select.h"
#include "tb_inline_select.h"
#include "tb_editfield.h"
#include "tb_node_tree.h"
#include "tb_font_renderer.h"
#include "tb_toggle_container.h"
#include "image/tb_image_widget.h"

namespace tb {

TB_WIDGET_FACTORY(TBWidget, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
void TBWidget::OnInflate(const INFLATE_INFO &info)
{
	TBWidgetsReader::SetIDFromNode(GetID(), info.node->GetNode("id"));

	TBWidgetsReader::SetIDFromNode(GetGroupID(), info.node->GetNode("group-id"));

	if (info.sync_type == TBValue::TYPE_FLOAT)
		SetValueDouble(info.node->GetValueFloat("value", 0));
	else
		SetValue(info.node->GetValueInt("value", 0));

	if (TBNode *data_node = info.node->GetNode("data"))
		data.Copy(data_node->GetValue());

	SetIsGroupRoot(info.node->GetValueInt("is-group-root", GetIsGroupRoot()) ? true : false);

	SetIsFocusable(info.node->GetValueInt("is-focusable", GetIsFocusable()) ? true : false);

	SetWantLongClick(info.node->GetValueInt("want-long-click", GetWantLongClick()) ? true : false);

	SetIgnoreInput(info.node->GetValueInt("ignore-input", GetIgnoreInput()) ? true : false);

	SetOpacity(info.node->GetValueFloat("opacity", GetOpacity()));

	if (const char *text = info.node->GetValueString("text", nullptr))
		SetText(text);

	if (const char *connection = info.node->GetValueStringRaw("connection", nullptr))
	{
		// If we already have a widget value with this name, just connect to it and the widget will
		// adjust its value to it. Otherwise create a new widget value, and give it the value we
		// got from the resource.
		if (TBWidgetValue *value = g_value_group.GetValue(connection))
			Connect(value);
		else if (TBWidgetValue *value = g_value_group.CreateValueIfNeeded(connection, info.sync_type))
		{
			value->SetFromWidget(this);
			Connect(value);
		}
	}
	if (const char *axis = info.node->GetValueString("axis", nullptr))
		SetAxis(*axis == 'x' ? AXIS_X : AXIS_Y);
	if (const char *gravity = info.node->GetValueString("gravity", nullptr))
	{
		WIDGET_GRAVITY g = WIDGET_GRAVITY_NONE;
		if (strstr(gravity, "left"))		g |= WIDGET_GRAVITY_LEFT;
		if (strstr(gravity, "top"))			g |= WIDGET_GRAVITY_TOP;
		if (strstr(gravity, "right"))		g |= WIDGET_GRAVITY_RIGHT;
		if (strstr(gravity, "bottom"))		g |= WIDGET_GRAVITY_BOTTOM;
		if (strstr(gravity, "all"))			g |= WIDGET_GRAVITY_ALL;
		if (!(g & WIDGET_GRAVITY_LEFT_RIGHT))
			g |= WIDGET_GRAVITY_LEFT;
		if (!(g & WIDGET_GRAVITY_TOP_BOTTOM))
			g |= WIDGET_GRAVITY_TOP;
		SetGravity(g);
	}
	if (const char *visibility = info.node->GetValueString("visibility", nullptr))
	{
		if (!strcmp(visibility, "visible"))			SetVisibilility(WIDGET_VISIBILITY_VISIBLE);
		else if (!strcmp(visibility, "invisible"))	SetVisibilility(WIDGET_VISIBILITY_INVISIBLE);
		else if (!strcmp(visibility, "gone"))		SetVisibilility(WIDGET_VISIBILITY_GONE);
	}
	if (const char *state = info.node->GetValueString("state", nullptr))
	{
		if (strstr(state, "disabled"))
			SetState(WIDGET_STATE_DISABLED, true);
	}
	if (const char *skin = info.node->GetValueString("skin", nullptr))
	{
		SetSkinBg(skin);
	}
	if (TBNode *lp = info.node->GetNode("lp"))
	{
		LayoutParams layout_params;
		if (GetLayoutParams())
			layout_params = *GetLayoutParams();
		const TBDimensionConverter *dc = g_tb_skin->GetDimensionConverter();
		if (const char *str = lp->GetValueString("width", nullptr))
			layout_params.SetWidth(dc->GetPxFromString(str, LayoutParams::UNSPECIFIED));
		if (const char *str = lp->GetValueString("height", nullptr))
			layout_params.SetHeight(dc->GetPxFromString(str, LayoutParams::UNSPECIFIED));
		if (const char *str = lp->GetValueString("min-width", nullptr))
			layout_params.min_w = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		if (const char *str = lp->GetValueString("max-width", nullptr))
			layout_params.max_w = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		if (const char *str = lp->GetValueString("pref-width", nullptr))
			layout_params.pref_w = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		if (const char *str = lp->GetValueString("min-height", nullptr))
			layout_params.min_h = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		if (const char *str = lp->GetValueString("max-height", nullptr))
			layout_params.max_h = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		if (const char *str = lp->GetValueString("pref-height", nullptr))
			layout_params.pref_h = dc->GetPxFromString(str, LayoutParams::UNSPECIFIED);
		SetLayoutParams(layout_params);
	}

	// Add the new widget to the hiearchy if not already added.
	if (!GetParent())
		info.target->AddChild(this, info.target->GetZInflate());

	// Read the font now when the widget is in the hiearchy so inheritance works.
	if (TBNode *font = info.node->GetNode("font"))
	{
		TBFontDescription fd = GetCalculatedFontDescription();
		if (const char *size = font->GetValueString("size", nullptr))
		{
			int new_size = g_tb_skin->GetDimensionConverter()->GetPxFromString(size, fd.GetSize());
			fd.SetSize(new_size);
		}
		if (const char *name = font->GetValueString("name", nullptr))
			fd.SetID(name);
		SetFontDescription(fd);
	}

	info.target->OnInflateChild(this);

	if (TBNode *rect_node = info.node->GetNode("rect"))
	{
		const TBDimensionConverter *dc = g_tb_skin->GetDimensionConverter();
		TBValue &val = rect_node->GetValue();
		if (val.GetArrayLength() == 4)
		{
			SetRect(TBRect(dc->GetPxFromValue(val.GetArray()->GetValue(0), 0),
				dc->GetPxFromValue(val.GetArray()->GetValue(1), 0),
				dc->GetPxFromValue(val.GetArray()->GetValue(2), 0),
				dc->GetPxFromValue(val.GetArray()->GetValue(3), 0)));
		}
	}
}

TB_WIDGET_FACTORY(TBButton, TBValue::TYPE_NULL, WIDGET_Z_BOTTOM) {}
void TBButton::OnInflate(const INFLATE_INFO &info)
{
	SetToggleMode(info.node->GetValueInt("toggle-mode", GetToggleMode()) ? true : false);
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBInlineSelect, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
void TBInlineSelect::OnInflate(const INFLATE_INFO &info)
{
	int min = info.node->GetValueInt("min", GetMinValue());
	int max = info.node->GetValueInt("max", GetMaxValue());
	SetLimits(min, max);
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBClickLabel, TBValue::TYPE_STRING, WIDGET_Z_BOTTOM) {}

TB_WIDGET_FACTORY(TBEditField, TBValue::TYPE_STRING, WIDGET_Z_TOP) {}
void TBEditField::OnInflate(const INFLATE_INFO &info)
{
	SetMultiline(info.node->GetValueInt("multiline", 0) ? true : false);
	SetStyling(info.node->GetValueInt("styling", 0) ? true : false);
	SetReadOnly(info.node->GetValueInt("readonly", 0) ? true : false);
	SetWrapping(info.node->GetValueInt("wrap", GetWrapping()) ? true : false);
	SetAdaptToContentSize(info.node->GetValueInt("adapt-to-content", GetAdaptToContentSize()) ? true : false);
	if (const char *virtual_width = info.node->GetValueString("virtual-width", nullptr))
		SetVirtualWidth(g_tb_skin->GetDimensionConverter()->GetPxFromString(virtual_width, GetVirtualWidth()));
	if (const char *text = info.node->GetValueString("placeholder", nullptr))
		SetPlaceholderText(text);
	if (const char *type = info.node->GetValueString("type", nullptr))
	{
		if (stristr(type, "text"))			SetEditType(EDIT_TYPE_TEXT);
		else if (stristr(type, "search"))	SetEditType(EDIT_TYPE_SEARCH);
		else if (stristr(type, "password"))	SetEditType(EDIT_TYPE_PASSWORD);
		else if (stristr(type, "email"))	SetEditType(EDIT_TYPE_EMAIL);
		else if (stristr(type, "phone"))	SetEditType(EDIT_TYPE_PHONE);
		else if (stristr(type, "url"))		SetEditType(EDIT_TYPE_URL);
		else if (stristr(type, "number"))	SetEditType(EDIT_TYPE_NUMBER);
	}
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBLayout, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
void TBLayout::OnInflate(const INFLATE_INFO &info)
{
	if (const char *spacing = info.node->GetValueString("spacing", nullptr))
		SetSpacing(g_tb_skin->GetDimensionConverter()->GetPxFromString(spacing, SPACING_FROM_SKIN));
	SetGravity(WIDGET_GRAVITY_ALL);
	if (const char *size = info.node->GetValueString("size", nullptr))
	{
		LAYOUT_SIZE ls = LAYOUT_SIZE_PREFERRED;
		if (strstr(size, "available"))
			ls = LAYOUT_SIZE_AVAILABLE;
		else if (strstr(size, "gravity"))
			ls = LAYOUT_SIZE_GRAVITY;
		SetLayoutSize(ls);
	}
	if (const char *pos = info.node->GetValueString("position", nullptr))
	{
		LAYOUT_POSITION lp = LAYOUT_POSITION_CENTER;
		if (strstr(pos, "left") || strstr(pos, "top"))
			lp = LAYOUT_POSITION_LEFT_TOP;
		else if (strstr(pos, "right") || strstr(pos, "bottom"))
			lp = LAYOUT_POSITION_RIGHT_BOTTOM;
		else if (strstr(pos, "gravity"))
			lp = LAYOUT_POSITION_GRAVITY;
		SetLayoutPosition(lp);
	}
	if (const char *pos = info.node->GetValueString("overflow", nullptr))
	{
		LAYOUT_OVERFLOW lo = LAYOUT_OVERFLOW_CLIP;
		if (strstr(pos, "scroll"))
			lo = LAYOUT_OVERFLOW_SCROLL;
		SetLayoutOverflow(lo);
	}
	if (const char *dist = info.node->GetValueString("distribution", nullptr))
	{
		LAYOUT_DISTRIBUTION ld = LAYOUT_DISTRIBUTION_PREFERRED;
		if (strstr(dist, "available"))
			ld = LAYOUT_DISTRIBUTION_AVAILABLE;
		else if (strstr(dist, "gravity"))
			ld = LAYOUT_DISTRIBUTION_GRAVITY;
		SetLayoutDistribution(ld);
	}
	if (const char *dist = info.node->GetValueString("distribution-position", nullptr))
	{
		LAYOUT_DISTRIBUTION_POSITION ld = LAYOUT_DISTRIBUTION_POSITION_CENTER;
		if (strstr(dist, "left") || strstr(dist, "top"))
			ld = LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP;
		else if (strstr(dist, "right") || strstr(dist, "bottom"))
			ld = LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM;
		SetLayoutDistributionPosition(ld);
	}
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBScrollContainer, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
void TBScrollContainer::OnInflate(const INFLATE_INFO &info)
{
	SetGravity(WIDGET_GRAVITY_ALL);
	SetAdaptContentSize(info.node->GetValueInt("adapt-content", GetAdaptContentSize()) ? true : false);
	SetAdaptToContentSize(info.node->GetValueInt("adapt-to-content", GetAdaptToContentSize()) ? true : false);
	if (const char *mode = info.node->GetValueString("scroll-mode", nullptr))
	{
		if (!strcmp(mode, "xy"))			SetScrollMode(SCROLL_MODE_X_Y);
		if (!strcmp(mode, "y"))				SetScrollMode(SCROLL_MODE_Y);
		if (!strcmp(mode, "y-auto"))			SetScrollMode(SCROLL_MODE_Y_AUTO);
		if (!strcmp(mode, "auto"))			SetScrollMode(SCROLL_MODE_X_AUTO_Y_AUTO);
		if (!strcmp(mode, "off"))			SetScrollMode(SCROLL_MODE_OFF);
	}
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBTabContainer, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
void TBTabContainer::OnInflate(const INFLATE_INFO &info)
{
	TBWidget::OnInflate(info);

	if (const char *align = info.node->GetValueString("align", nullptr))
	{
		if (!strcmp(align, "left"))			SetAlignment(TB_ALIGN_LEFT);
		else if (!strcmp(align, "top"))		SetAlignment(TB_ALIGN_TOP);
		else if (!strcmp(align, "right"))	SetAlignment(TB_ALIGN_RIGHT);
		else if (!strcmp(align, "bottom"))	SetAlignment(TB_ALIGN_BOTTOM);
	}
	// Allow additional attributes to be specified for the "tabs", "content" and "root" layouts by
	// calling OnInflate.
	if (TBNode *tabs = info.node->GetNode("tabs"))
	{
		// Inflate the tabs widgets into the tab layout.
		TBLayout *tab_layout = GetTabLayout();
		info.reader->LoadNodeTree(tab_layout, tabs);

		INFLATE_INFO inflate_info(info.reader, tab_layout->GetContentRoot(), tabs, TBValue::TYPE_NULL);
		tab_layout->OnInflate(inflate_info);
	}
	if (TBNode *tabs = info.node->GetNode("content"))
	{
		INFLATE_INFO inflate_info(info.reader, GetContentRoot(), tabs, TBValue::TYPE_NULL);
		GetContentRoot()->OnInflate(inflate_info);
	}
	if (TBNode *tabs = info.node->GetNode("root"))
	{
		INFLATE_INFO inflate_info(info.reader, &m_root_layout, tabs, TBValue::TYPE_NULL);
		m_root_layout.OnInflate(inflate_info);
	}
}

TB_WIDGET_FACTORY(TBScrollBar, TBValue::TYPE_FLOAT, WIDGET_Z_TOP) {}
void TBScrollBar::OnInflate(const INFLATE_INFO &info)
{
	const char *axis = info.node->GetValueString("axis", "x");
	SetAxis(*axis == 'x' ? AXIS_X : AXIS_Y);
	SetGravity(*axis == 'x' ? WIDGET_GRAVITY_LEFT_RIGHT : WIDGET_GRAVITY_TOP_BOTTOM);
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBSlider, TBValue::TYPE_FLOAT, WIDGET_Z_TOP) {}
void TBSlider::OnInflate(const INFLATE_INFO &info)
{
	const char *axis = info.node->GetValueString("axis", "x");
	SetAxis(*axis == 'x' ? AXIS_X : AXIS_Y);
	SetGravity(*axis == 'x' ? WIDGET_GRAVITY_LEFT_RIGHT : WIDGET_GRAVITY_TOP_BOTTOM);
	double min = (double)info.node->GetValueFloat("min", (float)GetMinValue());
	double max = (double)info.node->GetValueFloat("max", (float)GetMaxValue());
	SetLimits(min, max);
	TBWidget::OnInflate(info);
}

void ReadItems(TBNode *node, TBGenericStringItemSource *target_source)
{
	// If there is a items node, loop through all its children and add
	// items to the target item source.
	if (TBNode *items = node->GetNode("items"))
	{
		for (TBNode *n = items->GetFirstChild(); n; n = n->GetNext())
		{
			if (strcmp(n->GetName(), "item") != 0)
				continue;
			const char *item_str = n->GetValueString("text", "");
			TBID item_id;
			if (TBNode *n_id = n->GetNode("id"))
				TBWidgetsReader::SetIDFromNode(item_id, n_id);

			TBGenericStringItem *item = new TBGenericStringItem(item_str, item_id);
			if (!item || !target_source->AddItem(item))
			{
				// Out of memory
				delete item;
				break;
			}
		}
	}
}

TB_WIDGET_FACTORY(TBSelectList, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
void TBSelectList::OnInflate(const INFLATE_INFO &info)
{
	// Read items (if there is any) into the default source
	ReadItems(info.node, GetDefaultSource());
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBSelectDropdown, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
void TBSelectDropdown::OnInflate(const INFLATE_INFO &info)
{
	// Read items (if there is any) into the default source
	ReadItems(info.node, GetDefaultSource());
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBCheckBox, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBRadioButton, TBValue::TYPE_INT, WIDGET_Z_TOP) {}

TB_WIDGET_FACTORY(TBTextField, TBValue::TYPE_STRING, WIDGET_Z_TOP) {}
void TBTextField::OnInflate(const INFLATE_INFO &info)
{
	if (const char *text_align = info.node->GetValueString("text-align", nullptr))
	{
		if (!strcmp(text_align, "left"))		SetTextAlign(TB_TEXT_ALIGN_LEFT);
		else if (!strcmp(text_align, "center"))	SetTextAlign(TB_TEXT_ALIGN_CENTER);
		else if (!strcmp(text_align, "right"))	SetTextAlign(TB_TEXT_ALIGN_RIGHT);
	}
	TBWidget::OnInflate(info);
}

TB_WIDGET_FACTORY(TBSkinImage, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBSeparator, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBProgressSpinner, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBContainer, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBSectionHeader, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
TB_WIDGET_FACTORY(TBSection, TBValue::TYPE_INT, WIDGET_Z_TOP) {}

TB_WIDGET_FACTORY(TBToggleContainer, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
void TBToggleContainer::OnInflate(const INFLATE_INFO &info)
{
	if (const char *toggle = info.node->GetValueString("toggle", nullptr))
	{
		if (stristr(toggle, "enabled"))			SetToggle(TBToggleContainer::TOGGLE_ENABLED);
		else if (stristr(toggle, "opacity"))	SetToggle(TBToggleContainer::TOGGLE_OPACITY);
		else if (stristr(toggle, "expanded"))	SetToggle(TBToggleContainer::TOGGLE_EXPANDED);
	}
	SetInvert(info.node->GetValueInt("invert", GetInvert()) ? true : false);
	TBWidget::OnInflate(info);
}

#ifdef TB_IMAGE

TB_WIDGET_FACTORY(TBImageWidget, TBValue::TYPE_NULL, WIDGET_Z_TOP) {}
void TBImageWidget::OnInflate(const INFLATE_INFO &info)
{
	if (const char *filename = info.node->GetValueString("filename", nullptr))
		SetImage(filename);
	TBWidget::OnInflate(info);
}

#endif // TB_IMAGE

// == TBWidgetFactory ===================================

// We can't use a linked list object since we don't know if its constructor
// would run before of after any widget factory constructor that add itself
// to it. Using a manual one way link list is very simple.
TBWidgetFactory *g_registered_factories = nullptr;

TBWidgetFactory::TBWidgetFactory(const char *name, TBValue::TYPE sync_type)
	: name(name)
	, sync_type(sync_type)
	, next_registered_wf(nullptr)
{
}

void TBWidgetFactory::Register()
{
	next_registered_wf = g_registered_factories;
	g_registered_factories = this;
}

// == TBWidgetsReader ===================================

TBWidgetsReader *TBWidgetsReader::Create()
{
	TBWidgetsReader *w_reader = new TBWidgetsReader;
	if (!w_reader || !w_reader->Init())
	{
		delete w_reader;
		return nullptr;
	}
	return w_reader;
}

bool TBWidgetsReader::Init()
{
	for (TBWidgetFactory *wf = g_registered_factories; wf; wf = wf->next_registered_wf)
		if (!AddFactory(wf))
			return false;
	return true;
}

TBWidgetsReader::~TBWidgetsReader()
{
}

bool TBWidgetsReader::LoadFile(TBWidget *target, const char *filename)
{
	TBNode node;
	if (!node.ReadFile(filename))
		return false;
	LoadNodeTree(target, &node);
	return true;
}

bool TBWidgetsReader::LoadData(TBWidget *target, const char *data)
{
	TBNode node;
	node.ReadData(data);
	LoadNodeTree(target, &node);
	return true;
}

bool TBWidgetsReader::LoadData(TBWidget *target, const char *data, int data_len)
{
	TBNode node;
	node.ReadData(data, data_len);
	LoadNodeTree(target, &node);
	return true;
}

void TBWidgetsReader::LoadNodeTree(TBWidget *target, TBNode *node)
{
	// Iterate through all nodes and create widgets
	for (TBNode *child = node->GetFirstChild(); child; child = child->GetNext())
		CreateWidget(target, child);
}

void TBWidgetsReader::SetIDFromNode(TBID &id, TBNode *node)
{
	if (!node)
		return;
	if (node->GetValue().IsString())
		id.Set(node->GetValue().GetString());
	else
		id.Set(node->GetValue().GetInt());
}

bool TBWidgetsReader::CreateWidget(TBWidget *target, TBNode *node)
{
	// Find a widget creator from the node name
	TBWidgetFactory *wc = nullptr;
	for (wc = factories.GetFirst(); wc; wc = wc->GetNext())
		if (strcmp(node->GetName(), wc->name) == 0)
			break;
	if (!wc)
		return false;

	// Create the widget
	INFLATE_INFO info(this, target->GetContentRoot(), node, wc->sync_type);
	TBWidget *new_widget = wc->Create(&info);
	if (!new_widget)
		return false;

	// Read properties and add i to the hierarchy.
	new_widget->OnInflate(info);

	// If this assert is trigged, you probably forgot to call TBWidget::OnInflate from an overridden version.
	assert(new_widget->GetParent());

	// Iterate through all nodes and create widgets
	for (TBNode *n = node->GetFirstChild(); n; n = n->GetNext())
		CreateWidget(new_widget, n);

	if (node->GetValueInt("autofocus", 0))
		new_widget->SetFocus(WIDGET_FOCUS_REASON_UNKNOWN);

	return true;
}

}; // namespace tb
