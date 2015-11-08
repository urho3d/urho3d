// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_skin.h"
#include "tb_system.h"
#include "tb_tempbuffer.h"
#include "tb_node_tree.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

namespace tb {

// == Util functions ==========================================================

/*TB_TEXT_ALIGN StringToTextAlign(const char *align_str)
{
	TB_TEXT_ALIGN align = TB_TEXT_ALIGN_CENTER;
	if (strstr(state_str, "left"))		align = TB_TEXT_ALIGN_LEFT;
	if (strstr(state_str, "center"))	align = TB_TEXT_ALIGN_CENTER;
	if (strstr(state_str, "right"))		align = TB_TEXT_ALIGN_RIGHT;
	return state;
}*/

SKIN_STATE StringToState(const char *state_str)
{
	SKIN_STATE state = SKIN_STATE_NONE;
	if (strstr(state_str, "all"))		state |= SKIN_STATE_ALL;
	if (strstr(state_str, "disabled"))	state |= SKIN_STATE_DISABLED;
	if (strstr(state_str, "focused"))	state |= SKIN_STATE_FOCUSED;
	if (strstr(state_str, "pressed"))	state |= SKIN_STATE_PRESSED;
	if (strstr(state_str, "selected"))	state |= SKIN_STATE_SELECTED;
	if (strstr(state_str, "hovered"))	state |= SKIN_STATE_HOVERED;
	return state;
}

SKIN_ELEMENT_TYPE StringToType(const char *type_str)
{
	if (strcmp(type_str, "StretchBox") == 0)
		return SKIN_ELEMENT_TYPE_STRETCH_BOX;
	else if (strcmp(type_str, "Image") == 0)
		return SKIN_ELEMENT_TYPE_IMAGE;
	else if (strcmp(type_str, "Stretch Image") == 0)
		return SKIN_ELEMENT_TYPE_STRETCH_IMAGE;
	else if (strcmp(type_str, "Tile") == 0)
		return SKIN_ELEMENT_TYPE_TILE;
	else if (strcmp(type_str, "StretchBorder") == 0)
		return SKIN_ELEMENT_TYPE_STRETCH_BORDER;
	TBDebugOut("Skin error: Unknown skin type!\n");
	return SKIN_ELEMENT_TYPE_STRETCH_BOX;
}

TBSkinCondition::TARGET StringToTarget(const char *target_str)
{
	if (strcmp(target_str, "this") == 0)
		return TBSkinCondition::TARGET_THIS;
	else if (strcmp(target_str, "parent") == 0)
		return TBSkinCondition::TARGET_PARENT;
	else if (strcmp(target_str, "ancestors") == 0)
		return TBSkinCondition::TARGET_ANCESTORS;
	else if (strcmp(target_str, "prev sibling") == 0)
		return TBSkinCondition::TARGET_PREV_SIBLING;
	else if (strcmp(target_str, "next sibling") == 0)
		return TBSkinCondition::TARGET_NEXT_SIBLING;
	TBDebugOut("Skin error: Unknown target in condition!\n");
	return TBSkinCondition::TARGET_THIS;
}

TBSkinCondition::PROPERTY StringToProperty(const char *prop_str)
{
	if (strcmp(prop_str, "skin") == 0)
		return TBSkinCondition::PROPERTY_SKIN;
	else if (strcmp(prop_str, "window active") == 0)
		return TBSkinCondition::PROPERTY_WINDOW_ACTIVE;
	else if (strcmp(prop_str, "axis") == 0)
		return TBSkinCondition::PROPERTY_AXIS;
	else if (strcmp(prop_str, "align") == 0)
		return TBSkinCondition::PROPERTY_ALIGN;
	else if (strcmp(prop_str, "id") == 0)
		return TBSkinCondition::PROPERTY_ID;
	else if (strcmp(prop_str, "state") == 0)
		return TBSkinCondition::PROPERTY_STATE;
	else if (strcmp(prop_str, "value") == 0)
		return TBSkinCondition::PROPERTY_VALUE;
	else if (strcmp(prop_str, "hover") == 0)
		return TBSkinCondition::PROPERTY_HOVER;
	else if (strcmp(prop_str, "capture") == 0)
		return TBSkinCondition::PROPERTY_CAPTURE;
	else if (strcmp(prop_str, "focus") == 0)
		return TBSkinCondition::PROPERTY_FOCUS;
	return TBSkinCondition::PROPERTY_CUSTOM;
}

// == TBSkinCondition =======================================================

TBSkinCondition::TBSkinCondition(TARGET target, PROPERTY prop, const TBID &custom_prop, const TBID &value, TEST test)
	: m_target(target)
	, m_test(test)
{
	m_info.prop = prop;
	m_info.custom_prop = custom_prop;
	m_info.value = value;
}

bool TBSkinCondition::GetCondition(TBSkinConditionContext &context) const
{
	bool equal = context.GetCondition(m_target, m_info);
	return equal == (m_test == TEST_EQUAL);
}

// == TBSkin ================================================================

TBSkin::TBSkin()
	: m_listener(nullptr)
	, m_default_disabled_opacity(0.3f)
	, m_default_placeholder_opacity(0.2f)
	, m_default_spacing(0)
{
	g_renderer->AddListener(this);

	// Avoid filtering artifacts at edges when we draw fragments stretched.
	m_frag_manager.SetAddBorder(true);
}

bool TBSkin::Load(const char *skin_file, const char *override_skin_file)
{
	if (!LoadInternal(skin_file))
		return false;
	if (override_skin_file && !LoadInternal(override_skin_file))
		return false;
	return ReloadBitmaps();
}

bool TBSkin::LoadInternal(const char *skin_file)
{
	TBNode node;
	if (!node.ReadFile(skin_file))
		return false;

	TBTempBuffer skin_path;
	if (!skin_path.AppendPath(skin_file))
		return false;

	if (node.GetNode("description"))
	{
		// Check which DPI mode the dimension converter should use.
		// The base-dpi is the dpi in which the padding, spacing (and so on)
		// is specified in. If the skin supports a different DPI that is
		// closer to the screen DPI, all such dimensions will be scaled.
		int base_dpi = node.GetValueInt("description>base-dpi", 96);
		int supported_dpi = base_dpi;
		if (TBNode *supported_dpi_node = node.GetNode("description>supported-dpi"))
		{
			assert(supported_dpi_node->GetValue().IsArray() || supported_dpi_node->GetValue().GetInt() == base_dpi);
			if (TBValueArray *arr = supported_dpi_node->GetValue().GetArray())
			{
				int screen_dpi = TBSystem::GetDPI();
				int best_supported_dpi = 0;
				for (int i = 0; i < arr->GetLength(); i++)
				{
					int candidate_dpi = arr->GetValue(i)->GetInt();
					if (!best_supported_dpi || ABS(candidate_dpi - screen_dpi) < ABS(best_supported_dpi - screen_dpi))
						best_supported_dpi = candidate_dpi;
				}
				supported_dpi = best_supported_dpi;
			}
		}
		m_dim_conv.SetDPI(base_dpi, supported_dpi);
	}

	// Read skin constants
	if (const char *color = node.GetValueString("defaults>text-color", nullptr))
		m_default_text_color.SetFromString(color, strlen(color));
	m_default_disabled_opacity = node.GetValueFloat("defaults>disabled>opacity",
		m_default_disabled_opacity);
	m_default_placeholder_opacity = node.GetValueFloat("defaults>placeholder>opacity",
		m_default_placeholder_opacity);
	m_default_spacing = GetPxFromNode(node.GetNode("defaults>spacing"), m_default_spacing);

	// Iterate through all elements nodes and add skin elements or patch already
	// existing elements.
	TBNode *elements = node.GetNode("elements");
	if (elements)
	{
		TBNode *n = elements->GetFirstChild();
		while (n)
		{
			// If we have a "clone" node, clone all children from that node
			// into this node.
			while (TBNode *clone = n->GetNode("clone"))
			{
				n->Remove(clone);

				TBNode *clone_source = elements->GetNode(clone->GetValue().GetString());
				if (clone_source)
					n->CloneChildren(clone_source);

				delete clone;
			}

			// If the skin element already exist, we will call Load on it again.
			// This will patch the element with any new data from the node.
			TBID element_id(n->GetName());
			TBSkinElement *e = GetSkinElement(element_id);
			if (!e)
			{
				e = new TBSkinElement;
				if (!e)
					return false;
				m_elements.Add(element_id, e);
			}

			e->Load(n, this, skin_path.GetData());
			if (m_listener)
				m_listener->OnSkinElementLoaded(this, e, n);

			n = n->GetNext();
		}
	}
	return true;
}

void TBSkin::UnloadBitmaps()
{
	// Unset all bitmap pointers.
	TBHashTableIteratorOf<TBSkinElement> it(&m_elements);
	while (TBSkinElement *element = it.GetNextContent())
		element->bitmap = nullptr;

	// Clear all fragments and bitmaps.
	m_frag_manager.Clear();
}

bool TBSkin::ReloadBitmaps()
{
	UnloadBitmaps();
	bool success = ReloadBitmapsInternal();
	// Create all bitmaps for the bitmap fragment maps
	if (success)
		success = m_frag_manager.ValidateBitmaps();

#ifdef TB_RUNTIME_DEBUG_INFO
	TBStr info;
	info.SetFormatted("Skin loaded using %d bitmaps.\n", m_frag_manager.GetNumMaps());
	TBDebugOut(info);
#endif
	return success;
}

bool TBSkin::ReloadBitmapsInternal()
{
	// Load all bitmap files into new bitmap fragments.
	TBTempBuffer filename_dst_DPI;
	bool success = true;
	TBHashTableIteratorOf<TBSkinElement> it(&m_elements);
	while (TBSkinElement *element = it.GetNextContent())
	{
		if (!element->bitmap_file.IsEmpty())
		{
			assert(!element->bitmap);

			// FIX: dedicated_map is not needed for all backends (only deprecated fixed function GL)
			bool dedicated_map = element->type == SKIN_ELEMENT_TYPE_TILE;

			// Try to load bitmap fragment in the destination DPI (F.ex "foo.png" becomes "foo@192.png")
			int bitmap_dpi = m_dim_conv.GetSrcDPI();
			if (m_dim_conv.NeedConversion())
			{
				m_dim_conv.GetDstDPIFilename(element->bitmap_file, &filename_dst_DPI);
				element->bitmap = m_frag_manager.GetFragmentFromFile(filename_dst_DPI.GetData(), dedicated_map);
				if (element->bitmap)
					bitmap_dpi = m_dim_conv.GetDstDPI();
			}
			element->SetBitmapDPI(m_dim_conv, bitmap_dpi);

			// If we still have no bitmap fragment, load from default file.
			if (!element->bitmap)
				element->bitmap = m_frag_manager.GetFragmentFromFile(element->bitmap_file, dedicated_map);

			if (!element->bitmap)
				success = false;
		}
	}
	return success;
}

TBSkin::~TBSkin()
{
	g_renderer->RemoveListener(this);
}

TBSkinElement *TBSkin::GetSkinElement(const TBID &skin_id) const
{
	if (!skin_id)
		return nullptr;
	return m_elements.Get(skin_id);
}

TBSkinElement *TBSkin::GetSkinElementStrongOverride(const TBID &skin_id, SKIN_STATE state, TBSkinConditionContext &context) const
{
	if (TBSkinElement *skin_element = GetSkinElement(skin_id))
	{
		// Avoid eternal recursion when overrides refer to elements referring back.
		if (skin_element->is_getting)
			return nullptr;
		skin_element->is_getting = true;

		// Check if there's any strong overrides for this element with the given state.
		TBSkinElementState *override_state = skin_element->m_strong_override_elements.GetStateElement(state, context);
		if (override_state)
		{
			if (TBSkinElement *override_element = GetSkinElementStrongOverride(override_state->element_id, state, context))
			{
				skin_element->is_getting = false;
				return override_element;
			}
		}

		skin_element->is_getting = false;
		return skin_element;
	}
	return nullptr;
}

TBSkinElement *TBSkin::PaintSkin(const TBRect &dst_rect, const TBID &skin_id, SKIN_STATE state, TBSkinConditionContext &context)
{
	return PaintSkin(dst_rect, GetSkinElement(skin_id), state, context);
}

TBSkinElement *TBSkin::PaintSkin(const TBRect &dst_rect, TBSkinElement *element, SKIN_STATE state, TBSkinConditionContext &context)
{
	if (!element || element->is_painting)
		return nullptr;

	// Avoid potential endless recursion in evil skins
	element->is_painting = true;

	// Return the override if we have one.
	TBSkinElement *return_element = element;

	TB_IF_DEBUG(bool paint_error_highlight = false);

	// If there's any override for this state, paint it.
	TBSkinElementState *override_state = element->m_override_elements.GetStateElement(state, context);
	if (override_state)
	{
		if (TBSkinElement *used_override = PaintSkin(dst_rect, override_state->element_id, state, context))
			return_element = used_override;
		else
		{
			TB_IF_DEBUG(paint_error_highlight = true);
			TBDebugOut("Skin error: The skin references a missing element, or has a reference loop!\n");
			// Fall back to the standard skin.
			override_state = nullptr;
		}
	}

	// If there was no override, paint the standard skin element.
	if (!override_state)
		PaintElement(dst_rect, element);

	// Paint all child elements that matches the state (or should be painted for all states)
	if (element->m_child_elements.HasStateElements())
	{
		const TBSkinElementState *state_element = element->m_child_elements.GetFirstElement();
		while (state_element)
		{
			if (state_element->IsMatch(state, context))
				PaintSkin(dst_rect, state_element->element_id, state_element->state & state, context);
			state_element = state_element->GetNext();
		}
	}

	// Paint ugly rectangles on invalid skin elements in debug builds.
	TB_IF_DEBUG(if (paint_error_highlight) g_renderer->DrawRect(dst_rect.Expand(1, 1), TBColor(255, 205, 0)));
	TB_IF_DEBUG(if (paint_error_highlight) g_renderer->DrawRect(dst_rect.Shrink(1, 1), TBColor(255, 0, 0)));

	element->is_painting = false;
	return return_element;
}

void TBSkin::PaintSkinOverlay(const TBRect &dst_rect, TBSkinElement *element, SKIN_STATE state, TBSkinConditionContext &context)
{
	if (!element || element->is_painting)
		return;

	// Avoid potential endless recursion in evil skins
	element->is_painting = true;

	// Paint all overlay elements that matches the state (or should be painted for all states)
	const TBSkinElementState *state_element = element->m_overlay_elements.GetFirstElement();
	while (state_element)
	{
		if (state_element->IsMatch(state, context))
			PaintSkin(dst_rect, state_element->element_id, state_element->state & state, context);
		state_element = state_element->GetNext();
	}

	element->is_painting = false;
}

void TBSkin::PaintElement(const TBRect &dst_rect, TBSkinElement *element)
{
	PaintElementBGColor(dst_rect, element);
	if (!element->bitmap)
		return;
	if (element->type == SKIN_ELEMENT_TYPE_IMAGE)
		PaintElementImage(dst_rect, element);
	else if (element->type == SKIN_ELEMENT_TYPE_TILE)
		PaintElementTile(dst_rect, element);
	else if (element->type == SKIN_ELEMENT_TYPE_STRETCH_IMAGE || element->cut == 0)
		PaintElementStretchImage(dst_rect, element);
	else if (element->type == SKIN_ELEMENT_TYPE_STRETCH_BORDER)
		PaintElementStretchBox(dst_rect, element, false);
	else
		PaintElementStretchBox(dst_rect, element, true);
}

TBRect TBSkin::GetFlippedRect(const TBRect &src_rect, TBSkinElement *element) const
{
	// Turning the source rect "inside out" will flip the result when rendered.
	TBRect tmp_rect = src_rect;
	if (element->flip_x)
	{
		tmp_rect.x += tmp_rect.w;
		tmp_rect.w = -tmp_rect.w;
	}
	if (element->flip_y)
	{
		tmp_rect.y += tmp_rect.h;
		tmp_rect.h = -tmp_rect.h;
	}
	return tmp_rect;
}

void TBSkin::PaintElementBGColor(const TBRect &dst_rect, TBSkinElement *element)
{
	if (element->bg_color == 0)
		return;
	g_renderer->DrawRectFill(dst_rect, element->bg_color);
}

void TBSkin::PaintElementImage(const TBRect &dst_rect, TBSkinElement *element)
{
	TBRect src_rect(0, 0, element->bitmap->Width(), element->bitmap->Height());
	TBRect rect = dst_rect.Expand(element->expand, element->expand);
	rect.Set(rect.x + element->img_ofs_x + (rect.w - src_rect.w) * element->img_position_x / 100,
			rect.y + element->img_ofs_y + (rect.h - src_rect.h) * element->img_position_y / 100,
			src_rect.w, src_rect.h);
	g_renderer->DrawBitmap(rect, GetFlippedRect(src_rect, element), element->bitmap);
}

void TBSkin::PaintElementTile(const TBRect &dst_rect, TBSkinElement *element)
{
	TBRect rect = dst_rect.Expand(element->expand, element->expand);
	g_renderer->DrawBitmapTile(rect, element->bitmap->GetBitmap());
}

void TBSkin::PaintElementStretchImage(const TBRect &dst_rect, TBSkinElement *element)
{
	if (dst_rect.IsEmpty())
		return;
	TBRect rect = dst_rect.Expand(element->expand, element->expand);
	TBRect src_rect = GetFlippedRect(TBRect(0, 0, element->bitmap->Width(), element->bitmap->Height()), element);
	g_renderer->DrawBitmap(rect, src_rect, element->bitmap);
}

void TBSkin::PaintElementStretchBox(const TBRect &dst_rect, TBSkinElement *element, bool fill_center)
{
	if (dst_rect.IsEmpty())
		return;

	TBRect rect = dst_rect.Expand(element->expand, element->expand);

	// Stretch the dst_cut (if rect is smaller than the skin size)
	// FIX: the expand should also be stretched!
	int cut = element->cut;
	int dst_cut_w = MIN(cut, rect.w / 2);
	int dst_cut_h = MIN(cut, rect.h / 2);
	int bw = element->bitmap->Width();
	int bh = element->bitmap->Height();

	bool has_left_right_edges = rect.h > dst_cut_h * 2;
	bool has_top_bottom_edges = rect.w > dst_cut_w * 2;

	rect = GetFlippedRect(rect, element);
	if (element->flip_x)
		dst_cut_w = -dst_cut_w;
	if (element->flip_y)
		dst_cut_h = -dst_cut_h;

	// Corners
	g_renderer->DrawBitmap(TBRect(rect.x, rect.y, dst_cut_w, dst_cut_h), TBRect(0, 0, cut, cut), element->bitmap);
	g_renderer->DrawBitmap(TBRect(rect.x + rect.w - dst_cut_w, rect.y, dst_cut_w, dst_cut_h), TBRect(bw - cut, 0, cut, cut), element->bitmap);
	g_renderer->DrawBitmap(TBRect(rect.x, rect.y + rect.h - dst_cut_h, dst_cut_w, dst_cut_h), TBRect(0, bh - cut, cut, cut), element->bitmap);
	g_renderer->DrawBitmap(TBRect(rect.x + rect.w - dst_cut_w, rect.y + rect.h - dst_cut_h, dst_cut_w, dst_cut_h), TBRect(bw - cut, bh - cut, cut, cut), element->bitmap);

	// Left & right edge
	if (has_left_right_edges)
	{
		g_renderer->DrawBitmap(TBRect(rect.x, rect.y + dst_cut_h, dst_cut_w, rect.h - dst_cut_h * 2), TBRect(0, cut, cut, bh - cut * 2), element->bitmap);
		g_renderer->DrawBitmap(TBRect(rect.x + rect.w - dst_cut_w, rect.y + dst_cut_h, dst_cut_w, rect.h - dst_cut_h * 2), TBRect(bw - cut, cut, cut, bh - cut * 2), element->bitmap);
	}

	// Top & bottom edge
	if (has_top_bottom_edges)
	{
		g_renderer->DrawBitmap(TBRect(rect.x + dst_cut_w, rect.y, rect.w - dst_cut_w * 2, dst_cut_h), TBRect(cut, 0, bw - cut * 2, cut), element->bitmap);
		g_renderer->DrawBitmap(TBRect(rect.x + dst_cut_w, rect.y + rect.h - dst_cut_h, rect.w - dst_cut_w * 2, dst_cut_h), TBRect(cut, bh - cut, bw - cut * 2, cut), element->bitmap);
	}

	// Center
	if (fill_center && has_top_bottom_edges && has_left_right_edges)
		g_renderer->DrawBitmap(TBRect(rect.x + dst_cut_w, rect.y + dst_cut_h, rect.w - dst_cut_w * 2, rect.h - dst_cut_h * 2), TBRect(cut, cut, bw - cut * 2, bh - cut * 2), element->bitmap);
}

#ifdef TB_RUNTIME_DEBUG_INFO
void TBSkin::Debug()
{
	m_frag_manager.Debug();
}
#endif // TB_RUNTIME_DEBUG_INFO

void TBSkin::OnContextLost()
{
	// We could simply do: m_frag_manager.DeleteBitmaps() and then all bitmaps
	// would be recreated automatically when needed. But because it's easy,
	// we unload everything so we save some memory (by not keeping any image
	// data around).
	UnloadBitmaps();
}

void TBSkin::OnContextRestored()
{
	// Reload bitmaps (since we unloaded everything in OnContextLost())
	ReloadBitmaps();
}

int TBSkin::GetPxFromNode(TBNode *node, int def_value) const
{
	return node ? m_dim_conv.GetPxFromValue(&node->GetValue(), def_value) : def_value;
}

// == TBSkinElement =========================================================

TBSkinElement::TBSkinElement()
	: bitmap(nullptr), cut(0), expand(0), type(SKIN_ELEMENT_TYPE_STRETCH_BOX)
	, is_painting(false), is_getting(false)
	, padding_left(0), padding_top(0), padding_right(0), padding_bottom(0)
	, width(SKIN_VALUE_NOT_SPECIFIED), height(SKIN_VALUE_NOT_SPECIFIED)
	, pref_width(SKIN_VALUE_NOT_SPECIFIED), pref_height(SKIN_VALUE_NOT_SPECIFIED)
	, min_width(SKIN_VALUE_NOT_SPECIFIED), min_height(SKIN_VALUE_NOT_SPECIFIED)
	, max_width(SKIN_VALUE_NOT_SPECIFIED), max_height(SKIN_VALUE_NOT_SPECIFIED)
	, spacing(SKIN_VALUE_NOT_SPECIFIED)
	, content_ofs_x(0), content_ofs_y(0)
	, img_ofs_x(0), img_ofs_y(0)
	, img_position_x(50), img_position_y(50)
	, flip_x(0), flip_y(0), opacity(1.f)
	, text_color(0, 0, 0, 0)
	, bg_color(0, 0, 0, 0)
	, bitmap_dpi(0)
{
}

TBSkinElement::~TBSkinElement()
{
}

int TBSkinElement::GetIntrinsicMinWidth() const
{
	// Sizes below the skin cut size would start to shrink the skin below pretty,
	// so assume that's the default minimum size if it's not specified (minus expansion)
	return cut * 2 - expand * 2;
}

int TBSkinElement::GetIntrinsicMinHeight() const
{
	// Sizes below the skin cut size would start to shrink the skin below pretty,
	// so assume that's the default minimum size if it's not specified (minus expansion)
	return cut * 2 - expand * 2;
}

int TBSkinElement::GetIntrinsicWidth() const
{
	if (width != SKIN_VALUE_NOT_SPECIFIED)
		return width;
	if (bitmap)
		return bitmap->Width() - expand * 2;
	// FIX: We may want to check child elements etc.
	return SKIN_VALUE_NOT_SPECIFIED;
}

int TBSkinElement::GetIntrinsicHeight() const
{
	if (height != SKIN_VALUE_NOT_SPECIFIED)
		return height;
	if (bitmap)
		return bitmap->Height() - expand * 2;
	// FIX: We may want to check child elements etc.
	return SKIN_VALUE_NOT_SPECIFIED;
}

void TBSkinElement::SetBitmapDPI(const TBDimensionConverter &dim_conv, int bitmap_dpi)
{
	if (this->bitmap_dpi)
	{
		// We have already applied the modifications so abort. This may
		// happen when we reload bitmaps without reloading the skin.
		return;
	}
	if (dim_conv.NeedConversion())
	{
		if (bitmap_dpi == dim_conv.GetDstDPI())
		{
			// The bitmap was loaded in a different DPI than the base DPI so
			// we must scale the bitmap properties.
			expand = expand * dim_conv.GetDstDPI() / dim_conv.GetSrcDPI();
			cut = cut * dim_conv.GetDstDPI() / dim_conv.GetSrcDPI();
		}
		else
		{
			// The bitmap was loaded in the base DPI and we need to scale it.
			// Apply the DPI conversion to the skin element scale factor.
			// FIX: For this to work well, we would need to apply scale to both
			//      image and all the other types of drawing too.
			// scale_x = scale_x * dim_conv.GetDstDPI() / dim_conv.GetSrcDPI();
			// scale_y = scale_y * dim_conv.GetDstDPI() / dim_conv.GetSrcDPI();
		}
	}
	this->bitmap_dpi = bitmap_dpi;
}

bool TBSkinElement::HasState(SKIN_STATE state, TBSkinConditionContext &context)
{
	return	m_override_elements.GetStateElement(state, context, TBSkinElementState::MATCH_RULE_ONLY_SPECIFIC_STATE) ||
			m_child_elements.GetStateElement(state, context, TBSkinElementState::MATCH_RULE_ONLY_SPECIFIC_STATE) ||
			m_overlay_elements.GetStateElement(state, context, TBSkinElementState::MATCH_RULE_ONLY_SPECIFIC_STATE);
}

void TBSkinElement::Load(TBNode *n, TBSkin *skin, const char *skin_path)
{
	if (const char *bitmap = n->GetValueString("bitmap", nullptr))
	{
		bitmap_file.Clear();
		bitmap_file.Append(skin_path);
		bitmap_file.Append(bitmap);
	}

	// Note: Always read cut and expand as pixels. These values might later be
	//       recalculated depending on the DPI the bitmaps are available in.
	cut = n->GetValueInt("cut", cut);
	expand = n->GetValueInt("expand", expand);

	name.Set(n->GetName());
	id.Set(n->GetName());

	const TBDimensionConverter *dim_conv = skin->GetDimensionConverter();

	if (TBNode *padding_node = n->GetNode("padding"))
	{
		TBValue &val = padding_node->GetValue();
		if (val.GetArrayLength() == 4)
		{
			padding_top = dim_conv->GetPxFromValue(val.GetArray()->GetValue(0), 0);
			padding_right = dim_conv->GetPxFromValue(val.GetArray()->GetValue(1), 0);
			padding_bottom = dim_conv->GetPxFromValue(val.GetArray()->GetValue(2), 0);
			padding_left = dim_conv->GetPxFromValue(val.GetArray()->GetValue(3), 0);
		}
		else if (val.GetArrayLength() == 2)
		{
			padding_top = padding_bottom = dim_conv->GetPxFromValue(val.GetArray()->GetValue(0), 0);
			padding_left = padding_right = dim_conv->GetPxFromValue(val.GetArray()->GetValue(1), 0);
		}
		else
		{
			padding_top = padding_right = padding_bottom = padding_left = dim_conv->GetPxFromValue(&val, 0);
		}
	}
	width = skin->GetPxFromNode(n->GetNode("width"), width);
	height = skin->GetPxFromNode(n->GetNode("height"), height);
	pref_width = skin->GetPxFromNode(n->GetNode("pref-width"), pref_width);
	pref_height = skin->GetPxFromNode(n->GetNode("pref-height"), pref_height);
	min_width = skin->GetPxFromNode(n->GetNode("min-width"), min_width);
	min_height = skin->GetPxFromNode(n->GetNode("min-height"), min_height);
	max_width = skin->GetPxFromNode(n->GetNode("max-width"), max_width);
	max_height = skin->GetPxFromNode(n->GetNode("max-height"), max_height);
	spacing = skin->GetPxFromNode(n->GetNode("spacing"), spacing);
	content_ofs_x = skin->GetPxFromNode(n->GetNode("content-ofs-x"), content_ofs_x);
	content_ofs_y = skin->GetPxFromNode(n->GetNode("content-ofs-y"), content_ofs_y);
	img_position_x = n->GetValueInt("img-position-x", img_position_x);
	img_position_y = n->GetValueInt("img-position-y", img_position_y);
	img_ofs_x = skin->GetPxFromNode(n->GetNode("img-ofs-x"), img_ofs_x);
	img_ofs_y = skin->GetPxFromNode(n->GetNode("img-ofs-y"), img_ofs_y);
	flip_x = n->GetValueInt("flip-x", flip_x);
	flip_y = n->GetValueInt("flip-y", flip_y);
	opacity = n->GetValueFloat("opacity", opacity);

	if (const char *color = n->GetValueString("text-color", nullptr))
		text_color.SetFromString(color, strlen(color));

	if (const char *color = n->GetValueString("background-color", nullptr))
		bg_color.SetFromString(color, strlen(color));

	if (const char *type_str = n->GetValueString("type", nullptr))
		type = StringToType(type_str);

	// Create all state elements
	m_override_elements.Load(n->GetNode("overrides"));
	m_strong_override_elements.Load(n->GetNode("strong-overrides"));
	m_child_elements.Load(n->GetNode("children"));
	m_overlay_elements.Load(n->GetNode("overlays"));
}

// == TBSkinElementState ====================================================

bool TBSkinElementState::IsMatch(SKIN_STATE state, TBSkinConditionContext &context, MATCH_RULE rule) const
{
	if (rule == MATCH_RULE_ONLY_SPECIFIC_STATE && this->state == SKIN_STATE_ALL)
		return false;
	if ((state & this->state) || this->state == SKIN_STATE_ALL)
	{
		for (TBSkinCondition *condition = conditions.GetFirst(); condition; condition = condition->GetNext())
			if (!condition->GetCondition(context))
				return false;
		return true;
	}
	return false;
}

bool TBSkinElementState::IsExactMatch(SKIN_STATE state, TBSkinConditionContext &context, MATCH_RULE rule) const
{
	if (rule == MATCH_RULE_ONLY_SPECIFIC_STATE && this->state == SKIN_STATE_ALL)
		return false;
	if (state == this->state || this->state == SKIN_STATE_ALL)
	{
		for (TBSkinCondition *condition = conditions.GetFirst(); condition; condition = condition->GetNext())
			if (!condition->GetCondition(context))
				return false;
		return true;
	}
	return false;
}

// == TBSkinElementStateList ==================================================

TBSkinElementStateList::~TBSkinElementStateList()
{
	while (TBSkinElementState *state = m_state_elements.GetFirst())
	{
		m_state_elements.Remove(state);
		delete state;
	}
}

TBSkinElementState *TBSkinElementStateList::GetStateElement(SKIN_STATE state, TBSkinConditionContext &context, TBSkinElementState::MATCH_RULE rule) const
{
	// First try to get a state element with a exact match to the current state
	if (TBSkinElementState *element_state = GetStateElementExactMatch(state, context, rule))
		return element_state;
	// No exact state match. Get a state with a partly match if there is one.
	TBSkinElementState *state_element = m_state_elements.GetFirst();
	while (state_element)
	{
		if (state_element->IsMatch(state, context, rule))
			return state_element;
		state_element = state_element->GetNext();
	}
	return nullptr;
}

TBSkinElementState *TBSkinElementStateList::GetStateElementExactMatch(SKIN_STATE state, TBSkinConditionContext &context, TBSkinElementState::MATCH_RULE rule) const
{
	TBSkinElementState *state_element = m_state_elements.GetFirst();
	while (state_element)
	{
		if (state_element->IsExactMatch(state, context, rule))
			return state_element;
		state_element = state_element->GetNext();
	}
	return nullptr;
}

void TBSkinElementStateList::Load(TBNode *n)
{
	if (!n)
		return;

	// For each node, create a new state element.
	TBNode *element_node = n->GetFirstChild();
	while (element_node)
	{
		TBSkinElementState *state = new TBSkinElementState;
		if (!state)
			return;

		// By default, a state element applies to all combinations of states
		state->state = SKIN_STATE_ALL;
		state->element_id.Set(element_node->GetValue().GetString());

		// Loop through all nodes, read state and create all found conditions.
		for (TBNode *condition_node = element_node->GetFirstChild(); condition_node; condition_node = condition_node->GetNext())
		{
			if (strcmp(condition_node->GetName(), "state") == 0)
				state->state = StringToState(condition_node->GetValue().GetString());
			else if (strcmp(condition_node->GetName(), "condition") == 0)
			{
				TBSkinCondition::TARGET target = StringToTarget(condition_node->GetValueString("target", ""));

				const char *prop_str = condition_node->GetValueString("property", "");
				TBSkinCondition::PROPERTY prop = StringToProperty(prop_str);
				TBID custom_prop;
				if (prop == TBSkinCondition::PROPERTY_CUSTOM)
					custom_prop.Set(prop_str);

				TBID value;
				if (TBNode *value_n = condition_node->GetNode("value"))
				{
					// Set the it to number or string. If it's a state, we must first convert the
					// state string to the SKIN_STATE state combo.
					if (prop == TBSkinCondition::PROPERTY_STATE)
						value.Set(StringToState(value_n->GetValue().GetString()));
					else if (value_n->GetValue().IsString())
						value.Set(value_n->GetValue().GetString());
					else
						value.Set(value_n->GetValue().GetInt());
				}

				TBSkinCondition::TEST test = TBSkinCondition::TEST_EQUAL;
				if (const char *test_str = condition_node->GetValueString("test", nullptr))
				{
					if (strcmp(test_str, "!=") == 0)
						test = TBSkinCondition::TEST_NOT_EQUAL;
				}

				if (TBSkinCondition *condition = new TBSkinCondition(target, prop, custom_prop, value, test))
					state->conditions.AddLast(condition);
			}
		}

		// State is reado to add
		m_state_elements.AddLast(state);
		element_node = element_node->GetNext();
	}
}

}; // namespace tb
