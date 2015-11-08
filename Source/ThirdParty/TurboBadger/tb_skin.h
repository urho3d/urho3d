// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_SKIN_H
#define TB_SKIN_H

#include "tb_core.h"
#include "tb_renderer.h"
#include "tb_bitmap_fragment.h"
#include "tb_hashtable.h"
#include "tb_linklist.h"
#include "tb_dimension.h"
#include "tb_value.h"

namespace tb {

class TBNode;
class TBSkinConditionContext;

/** Used for some values in TBSkinElement if they has not been specified in the skin. */
#define SKIN_VALUE_NOT_SPECIFIED TB_INVALID_DIMENSION

/** Skin state types (may be combined).
	NOTE: This should exactly match WIDGET_STATE in tb_widgets.h! */
enum SKIN_STATE {
	SKIN_STATE_NONE			= 0,
	SKIN_STATE_DISABLED		= 1,
	SKIN_STATE_FOCUSED		= 2,
	SKIN_STATE_PRESSED		= 4,
	SKIN_STATE_SELECTED		= 8,
	SKIN_STATE_HOVERED		= 16,

	SKIN_STATE_ALL			=	SKIN_STATE_DISABLED |
								SKIN_STATE_FOCUSED |
								SKIN_STATE_PRESSED |
								SKIN_STATE_SELECTED |
								SKIN_STATE_HOVERED
};
MAKE_ENUM_FLAG_COMBO(SKIN_STATE);

/** Type of painting that should be done for a TBSkinElement. */
enum SKIN_ELEMENT_TYPE {
	SKIN_ELEMENT_TYPE_STRETCH_BOX,
	SKIN_ELEMENT_TYPE_STRETCH_BORDER,
	SKIN_ELEMENT_TYPE_STRETCH_IMAGE,
	SKIN_ELEMENT_TYPE_TILE,
	SKIN_ELEMENT_TYPE_IMAGE
};

/** TBSkinCondition checks if a condition is true for a given TBSkinConditionContext.
	This is used to apply different state elements depending on what is currently
	painting the skin. */

class TBSkinCondition : public TBLinkOf<TBSkinCondition>
{
public:
	/** Defines which target(s) relative to the context that should be tested for the condition. */
	enum TARGET {
		TARGET_THIS,			///< The object painting the skin.
		TARGET_PARENT,			///< The parent of the object painting the skin.
		TARGET_ANCESTORS,		///< All ancestors of the object painting the skin.
		TARGET_PREV_SIBLING,	///< The previous sibling of the object painting the skin.
		TARGET_NEXT_SIBLING		///< The next sibling of the object painting the skin.
	};
	/** Defines which property in the context that should be checked. */
	enum PROPERTY {
		PROPERTY_SKIN,				///< The background skin id.
		PROPERTY_WINDOW_ACTIVE,		///< The window is active (no value required).
		PROPERTY_AXIS,				///< The axis of the content (x or y)
		PROPERTY_ALIGN,				///< The alignment.
		PROPERTY_ID,				///< The id.
		PROPERTY_STATE,				///< The state is set.
		PROPERTY_VALUE,				///< The current value (integer).
		PROPERTY_HOVER,				///< Focus is on the target or any child (no value required).
		PROPERTY_CAPTURE,			///< Capture is on the target or any child (no value required).
		PROPERTY_FOCUS,				///< Focus is on the target or any child (no value required).
		PROPERTY_CUSTOM				///< It's a property unknown to skin, that the TBSkinConditionContext might know about.
	};

	/** Defines if the condition tested should be equal or not for the condition to be true. */
	enum TEST {
		TEST_EQUAL,		///< Value should be equal for condition to be true.
		TEST_NOT_EQUAL	///< Value should not be equal for condition to be true.
	};

	/** Stores the information needed for checking a condition. */
	struct CONDITION_INFO {
		PROPERTY prop;			///< Which property.
		TBID custom_prop;		///< Which property (only if prop is PROPERTY_CUSTOM).
		TBID value;				///< The value to compare.
	};

	TBSkinCondition(TARGET target, PROPERTY prop, const TBID &custom_prop, const TBID &value, TEST test);

	/** Return true if the condition is true for the given context. */
	bool GetCondition(TBSkinConditionContext &context) const;
private:
	TARGET m_target;
	CONDITION_INFO m_info;
	TEST m_test;
};

/** TBSkinConditionContext checks if a condition is true. It is passed to skin painting functions
	so different state elements can be applied depending on the current situation of the context.
	F.ex a widget may change appearance if it's under a parent with a certain skin. */

class TBSkinConditionContext
{
public:
	/** Return true if the given target and property equals the given value. */
	virtual bool GetCondition(TBSkinCondition::TARGET target, const TBSkinCondition::CONDITION_INFO &info) = 0;
};

/** TBSkinElementState has a skin element id that should be used if its state and condition
	matches that which is being painted.
*/

class TBSkinElementState : public TBLinkOf<TBSkinElementState>
{
public:
	/** Defines how to match states. */
	enum MATCH_RULE {
		/** States with "all" (SKIN_STATE_ALL) will also be considered a match. */
		MATCH_RULE_DEFAULT,
		/** States with "all" will not be considered a match. */
		MATCH_RULE_ONLY_SPECIFIC_STATE
	};

	bool IsMatch(SKIN_STATE state, TBSkinConditionContext &context,
				MATCH_RULE rule = MATCH_RULE_DEFAULT) const;

	bool IsExactMatch(SKIN_STATE state, TBSkinConditionContext &context,
				MATCH_RULE rule = MATCH_RULE_DEFAULT) const;

	TBID element_id;
	SKIN_STATE state;
	TBLinkListAutoDeleteOf<TBSkinCondition> conditions;
};

/** List of state elements in a TBSkinElement. */

class TBSkinElementStateList
{
public:
	~TBSkinElementStateList();

	TBSkinElementState *GetStateElement(SKIN_STATE state, TBSkinConditionContext &context,
						TBSkinElementState::MATCH_RULE rule = TBSkinElementState::MATCH_RULE_DEFAULT) const;

	TBSkinElementState *GetStateElementExactMatch(SKIN_STATE state, TBSkinConditionContext &context,
						TBSkinElementState::MATCH_RULE rule = TBSkinElementState::MATCH_RULE_DEFAULT) const;

	bool HasStateElements() const { return m_state_elements.HasLinks(); }
	const TBSkinElementState *GetFirstElement() const { return m_state_elements.GetFirst(); }

	void Load(TBNode *n);
private:
	TBLinkListOf<TBSkinElementState> m_state_elements;
};

/** Skin element.
	Contains a bitmap fragment (or nullptr) and info specifying how it should be painted.
	Also contains padding and other look-specific widget properties. */
class TBSkinElement
{
public:
	TBSkinElement();
	~TBSkinElement();

	// Skin properties
	TBID id;			///< ID of the skin element
	TBStr name;			///< Name of the skin element, f.ex "TBSelectDropdown.arrow"
	TBStr bitmap_file;	///< File name of the bitmap (might be empty)
	TBBitmapFragment *bitmap;///< Bitmap fragment containing the graphics, or nullptr.
	uint8 cut;			///< How the bitmap should be sliced using StretchBox.
	int16 expand;		///< How much the skin should expand outside the widgets rect.
	SKIN_ELEMENT_TYPE type;///< Skin element type
	bool is_painting;	///< If the skin is being painted (avoiding eternal recursing)
	bool is_getting;	///< If the skin is being got (avoiding eternal recursion)
	int16 padding_left;		///< Left padding for any content in the element
	int16 padding_top;		///< Top padding for any content in the element
	int16 padding_right;	///< Right padding for any content in the element
	int16 padding_bottom;	///< Bottom padding for any content in the element
	int16 width;			///< Intrinsic width or SKIN_VALUE_NOT_SPECIFIED
	int16 height;			///< Intrinsic height or SKIN_VALUE_NOT_SPECIFIED
	int16 pref_width;		///< Preferred width or SKIN_VALUE_NOT_SPECIFIED
	int16 pref_height;		///< Preferred height or SKIN_VALUE_NOT_SPECIFIED
	int16 min_width;		///< Minimum width or SKIN_VALUE_NOT_SPECIFIED
	int16 min_height;		///< Minimum height or SKIN_VALUE_NOT_SPECIFIED
	int16 max_width;		///< Maximum width or SKIN_VALUE_NOT_SPECIFIED
	int16 max_height;		///< Maximum height or SKIN_VALUE_NOT_SPECIFIED
	int16 spacing;			///< Spacing used on layout or SKIN_VALUE_NOT_SPECIFIED.
	int16 content_ofs_x;	///< X offset of the content in the widget.
	int16 content_ofs_y;	///< Y offset of the content in the widget.
	int16 img_ofs_x;		///< X offset for type image. Relative to image position (img_position_x).
	int16 img_ofs_y;		///< Y offset for type image. Relative to image position (img_position_y).
	int8 img_position_x;	///< Horizontal position for type image. 0-100 (left to
							///< right in available space). Default 50.
	int8 img_position_y;	///< Vertical position for type image. 0-100 (top to bottom
							///< in available space). Default 50.
	int8 flip_x;			///< The skin is flipped horizontally
	int8 flip_y;			///< The skin is flipped vertically
	float opacity;			///< Opacity that should be used for the whole widget (0.f - 1.f).
	TBColor text_color;		///< Color of the text in the widget.
	TBColor bg_color;		///< Color of the background in the widget.
	int16 bitmap_dpi;		///< The DPI of the bitmap that was loaded.
	TBValue tag;			///< This value is free to use for anything. It's not used internally.

	/** Get the minimum width, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetMinWidth() const { return min_width; }

	/** Get the minimum height, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetMinHeight() const { return min_height; }

	/** Get the intrinsic minimum width. It will be calculated based on the skin properties. */
	int GetIntrinsicMinWidth() const;

	/** Get the intrinsic minimum height. It will be calculated based on the skin properties. */
	int GetIntrinsicMinHeight() const;

	/** Get the maximum width, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetMaxWidth() const { return max_width; }

	/** Get the maximum height, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetMaxHeight() const { return max_height; }

	/** Get the preferred width, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetPrefWidth() const { return pref_width; }

	/** Get the preferred height, or SKIN_VALUE_NOT_SPECIFIED if not specified. */
	int GetPrefHeight() const { return pref_height; }

	/** Get the intrinsic width. If not specified using the "width" attribute, it will be
		calculated based on the skin properties. If it can't be calculated it will return
		SKIN_VALUE_NOT_SPECIFIED. */
	int GetIntrinsicWidth() const;

	/** Get the intrinsic height. If not specified using the "height" attribute, it will be
		calculated based on the skin properties. If it can't be calculated it will return
		SKIN_VALUE_NOT_SPECIFIED. */
	int GetIntrinsicHeight() const;

	/** Set the DPI that the bitmap was loaded in. This may modify properties
		to compensate for the bitmap resolution. */
	void SetBitmapDPI(const TBDimensionConverter &dim_conv, int bitmap_dpi);

	/** List of override elements (See TBSkin::PaintSkin) */
	TBSkinElementStateList m_override_elements;

	/** List of strong-override elements (See TBSkin::PaintSkin) */
	TBSkinElementStateList m_strong_override_elements;

	/** List of child elements (See TBSkin::PaintSkin) */
	TBSkinElementStateList m_child_elements;

	/** List of overlay elements (See TBSkin::PaintSkin) */
	TBSkinElementStateList m_overlay_elements;

	/** Check if there's a exact or partial match for the given state in either
		override, child or overlay element list.
		State elements with state "all" will be ignored. */
	bool HasState(SKIN_STATE state, TBSkinConditionContext &context);

	/** Return true if this element has overlay elements. */
	bool HasOverlayElements() const { return m_overlay_elements.HasStateElements(); }

	void Load(TBNode *n, TBSkin *skin, const char *skin_path);
};

class TBSkinListener
{
public:
	/** Called when a skin element has been loaded from the given TBNode.
		NOTE: This may be called multiple times on elements that occur multiple times
		in the skin or is overridden in an override skin.
		This method can be used to f.ex feed custom properties into element->tag. */
	virtual void OnSkinElementLoaded(TBSkin *skin, TBSkinElement *element, TBNode *node) = 0;
};

/** TBSkin contains a list of TBSkinElement. */
class TBSkin : private TBRendererListener
{
public:
	TBSkin();
	virtual ~TBSkin();

	/** Set the listener for this skin. */
	void SetListener(TBSkinListener *listener) { m_listener = listener; }
	TBSkinListener *GetListener() const { return m_listener;  }

	/** Load the skin file and the bitmaps it refers to.

		If override_skin_file is specified, it will also be loaded into this skin after
		loading skin_file. Elements using the same name will override any previosly
		read data for the same element. Known limitation: Clone can currently only
		clone elements in the same file!

		Returns true on success, and all bitmaps referred to also loaded successfully. */
	bool Load(const char *skin_file, const char *override_skin_file = nullptr);

	/** Unload all bitmaps used in this skin. */
	void UnloadBitmaps();

	/** Reload all bitmaps used in this skin. Calls UnloadBitmaps first to ensure no bitmaps
		are loaded before loading new ones. */
	bool ReloadBitmaps();

	/** Get the dimension converter used for the current skin. This dimension converter
		converts to px by the same factor as the skin (based on the skin DPI settings). */
	const TBDimensionConverter *GetDimensionConverter() const { return &m_dim_conv; }

	/** Get the skin element with the given id.
		Returns nullptr if there's no match. */
	TBSkinElement *GetSkinElement(const TBID &skin_id) const;

	/** Get the skin element with the given id and state.
		This is like calling GetSkinElement and also following any strong overrides that
		match the current state (if any). See details about strong overrides in PaintSkin.
		Returns nullptr if there's no match. */
	TBSkinElement *GetSkinElementStrongOverride(const TBID &skin_id, SKIN_STATE state, TBSkinConditionContext &context) const;

	/** Get the default text color for all skin elements */
	TBColor GetDefaultTextColor() const { return m_default_text_color; }

	/** Get the default disabled opacity for all skin elements */
	float GetDefaultDisabledOpacity() const { return m_default_disabled_opacity; }

	/** Get the default placeholder opacity for all skin elements */
	float GetDefaultPlaceholderOpacity() const { return m_default_placeholder_opacity; }

	/** Get the default layout spacing in pixels. */
	int GetDefaultSpacing() const { return m_default_spacing; }

	/** Paint the skin at dst_rect.

		Strong override elements:
		-Strong override elements are like override elements, but they don't only apply
		 when painting. They also override padding and other things that might affect
		 the layout of the widget having the skin set.

		Override elements:
		-If there is a override element with the exact matching state, it will paint
		 the override *instead* if the base skin. If no exact match was found, it will
		 check for a partial match and paint that *instead* of the base skin.

		Child elements:
		-It will paint *all* child elements that match the current state ("all" can be specified
		 as state so it will always be painted). The elements are painted in the order they are
		 specified in the skin.

		Special elements:
		-There's some special generic skin elements used by TBWidget (see TBWidget::SetSkinBg)

		Overlay elements:
		-Overlay elements are painted separately, from PaintSkinOverlay (when all sibling
		 widgets has been painted). As with child elements, all overlay elements that match
		 the current state will be painted in the order they are specified in the skin.

		Return the skin element used (after following override elements),
		or nullptr if no skin element was found matching the skin_id. */
	TBSkinElement *PaintSkin(const TBRect &dst_rect, const TBID &skin_id, SKIN_STATE state, TBSkinConditionContext &context);

	/** Paint the skin at dst_rect. Just like the PaintSkin above, but takes a specific
		skin element instead of looking it up from the id. */
	TBSkinElement *PaintSkin(const TBRect &dst_rect, TBSkinElement *element, SKIN_STATE state, TBSkinConditionContext &context);

	/** Paint the overlay elements for the given skin element and state. */
	void PaintSkinOverlay(const TBRect &dst_rect, TBSkinElement *element, SKIN_STATE state, TBSkinConditionContext &context);

#ifdef TB_RUNTIME_DEBUG_INFO
	/** Render the skin bitmaps on screen, to analyze fragment positioning. */
	void Debug();
#endif

	/** Get the fragment manager. */
	TBBitmapFragmentManager *GetFragmentManager() { return &m_frag_manager; }

	// Implementing TBRendererListener
	virtual void OnContextLost();
	virtual void OnContextRestored();
private:
	friend class TBSkinElement;
	TBSkinListener *m_listener;
	TBHashTableAutoDeleteOf<TBSkinElement> m_elements;	///< All skin elements for this skin.
	TBBitmapFragmentManager m_frag_manager;				///< Fragment manager
	TBDimensionConverter m_dim_conv;					///< Dimension converter
	TBColor m_default_text_color;						///< Default text color for all skin elements
	float m_default_disabled_opacity;					///< Disabled opacity
	float m_default_placeholder_opacity;				///< Placeholder opacity
	int16 m_default_spacing;							///< Default layout spacing
	bool LoadInternal(const char *skin_file);
	bool ReloadBitmapsInternal();
	void PaintElement(const TBRect &dst_rect, TBSkinElement *element);
	void PaintElementBGColor(const TBRect &dst_rect, TBSkinElement *element);
	void PaintElementImage(const TBRect &dst_rect, TBSkinElement *element);
	void PaintElementTile(const TBRect &dst_rect, TBSkinElement *element);
	void PaintElementStretchImage(const TBRect &dst_rect, TBSkinElement *element);
	void PaintElementStretchBox(const TBRect &dst_rect, TBSkinElement *element, bool fill_center);
	TBRect GetFlippedRect(const TBRect &src_rect, TBSkinElement *element) const;
	int GetPxFromNode(TBNode *node, int def_value) const;
};

}; // namespace tb

#endif // TB_SKIN_H
