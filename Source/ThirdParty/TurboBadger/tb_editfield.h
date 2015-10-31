// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_EDITFIELD_H
#define TB_EDITFIELD_H

#include "tb_widgets_common.h"
#include "tb_msg.h"
#include "tb_style_edit.h"

namespace tb {

/** EDIT_TYPE - These types does not restrict input (may change in the future).
	They are just hints for virtual keyboard, so it can show special keys. */
enum EDIT_TYPE {
	EDIT_TYPE_TEXT,
	EDIT_TYPE_SEARCH,
	EDIT_TYPE_PASSWORD,
	EDIT_TYPE_EMAIL,
	EDIT_TYPE_PHONE,
	EDIT_TYPE_URL,
	EDIT_TYPE_NUMBER
};

/** The default content factory for embedded content in TBEditField with styling enabled.

	Creates all that TBTextFragmentContentFactory creates by default,
	and any type of widget from a inline resource string.

	Syntax: <widget xxx> Where xxx is parsed by TBWidgetsReader.

	Example - Create a button with id "hello":

		<widget TBButton: text: "Hello world!" id: "hello">

	Example - Create a image from skin element "Icon48":

		<widget TBSkinImage: skin: "Icon48">
*/

class TBEditFieldContentFactory : public TBTextFragmentContentFactory
{
public:
	class TBEditField *editfield;
	virtual int GetContent(const char *text);
	virtual TBTextFragmentContent *CreateFragmentContent(const char *text, int text_len);
};

/** TBEditFieldScrollRoot - Internal for TBEditField.
	Acts as a scrollable container for any widget created as embedded content. */

class TBEditFieldScrollRoot : public TBWidget
{
private: // May only be used by TBEditField.
	friend class TBEditField;
	TBEditFieldScrollRoot() {}
public:
	virtual void OnPaintChildren(const PaintProps &paint_props);
	virtual void GetChildTranslation(int &x, int &y) const;
	virtual WIDGET_HIT_STATUS GetHitStatus(int x, int y);
};

/** TBEditField is a one line or multi line textfield that is editable or
	read-only. It can also be a passwordfield by calling
	SetEditType(EDIT_TYPE_PASSWORD).

	It may perform styling of text and contain custom embedded content,
	if enabled by SetStyling(true). Disabled by default.
*/

class TBEditField : public TBWidget, private TBStyleEditListener, public TBMessageHandler
{
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBEditField, TBWidget);

	TBEditField();
	~TBEditField();

	/** Get the visible rect (the GetPaddingRect() minus any scrollbars) */
	TBRect GetVisibleRect();

	/** Set if multiple lines should be allowed or not.
		Will also set wrapping (to true if multiline, and false if not). */
	void SetMultiline(bool multiline);
	bool GetMultiline() const { return m_style_edit.packed.multiline_on; }

	/** Set if styling should be enabled or not. Default is disabled. */
	void SetStyling(bool styling);
	bool GetStyling() const { return m_style_edit.packed.styling_on; }

	/** Set if read only mode should be enabled. Default is disabled.
		In read only mode, editing is disabled and caret is hidden.
		The user is still able to focus, select and copy text. */
	void SetReadOnly(bool readonly);
	bool GetReadOnly() const { return m_style_edit.packed.read_only; }

	/** Set to true if the text should wrap if multi line is enabled (See SetMultiline). */
	void SetWrapping(bool wrapping);
	bool GetWrapping() const { return m_style_edit.packed.wrapping; }

	/** Set to true if the preferred size of this editfield should adapt to the
		size of the content (disabled by default).
		If wrapping is enabled, the result is partly dependant on the virtual
		width (See SetVirtualWidth). */
	void SetAdaptToContentSize(bool adapt);
	bool GetAdaptToContentSize() const { return m_adapt_to_content_size; }

	/** The virtual width is only used if the size is adapting to content size
		(See SetAdaptToContentSize) and wrapping is enabled.
		The virtual width will be used to layout the text and see which resulting
		width and height it takes up. The width that is actually used depends on
		the content. It is also up to the the layouter to decide if the size
		should be respected or not. The default is 250. */
	void SetVirtualWidth(int virtual_width);
	int GetVirtualWidth() const { return m_virtual_width; }

	/** Get the TBStyleEdit object that contains more functions and settings. */
	TBStyleEdit *GetStyleEdit() { return &m_style_edit; }

	/** Set the edit type that is a hint for virtual keyboards about what the
		content should be. */
	void SetEditType(EDIT_TYPE type);
	EDIT_TYPE GetEditType() { return m_edit_type; }

	/** Support custom skin condition properties. Currently supported properties are:
		"edit-type", matching those of EDIT_TYPE.
		"multiline", matching 1 if multiline mode is enabled.
		"readonly", matching 1 if readonly mode is enabled. */
	virtual bool GetCustomSkinCondition(const TBSkinCondition::CONDITION_INFO &info);

	/** Set which alignment the text should have if the space
		given when painting is larger than the text.
		This changes the default for new blocks, as wel as the currently selected blocks or the block
		of the current caret position if nothing is selected. */
	void SetTextAlign(TB_TEXT_ALIGN align) { m_style_edit.SetAlign(align); }
	TB_TEXT_ALIGN GetTextAlign() { return m_style_edit.align; }

	virtual bool SetText(const char *text) { return m_style_edit.SetText(text, TB_CARET_POS_BEGINNING); }
	virtual bool GetText(TBStr &text) { return m_style_edit.GetText(text); }
	using TBWidget::GetText; ///< Make all versions in base class available.

	using TBWidget::Invalidate; ///< Make Invalidate in base class available.

	/** Set the text and also specify if the caret should be positioned at the beginning
		or end of the text. */
	bool SetText(const char *text, TB_CARET_POS pos)
											{ return m_style_edit.SetText(text, pos); }
	/** Set the text of the given length and also specify if the caret should be positioned
		at the beginning or end of the text. */
	bool SetText(const char *text, int text_len, TB_CARET_POS pos = TB_CARET_POS_BEGINNING)
											{ return m_style_edit.SetText(text, text_len, pos); }

	/** Set the placeholder text. It will be visible only when the textfield is empty. */
	virtual bool SetPlaceholderText(const char *text) { return m_placeholder.SetText(text); }
	virtual bool GetPlaceholderText(TBStr &text) { return m_placeholder.GetText(text); }

	virtual void ScrollTo(int x, int y);
	virtual TBWidget::ScrollInfo GetScrollInfo();
	virtual TBWidget *GetScrollRoot() { return &m_root; }

	virtual bool OnEvent(const TBWidgetEvent &ev);
	virtual void OnPaint(const PaintProps &paint_props);
	virtual void OnPaintChildren(const PaintProps &paint_props);
	virtual void OnInflate(const INFLATE_INFO &info);
	virtual void OnAdded();
	virtual void OnFontChanged();
	virtual void OnFocusChanged(bool focused);
	virtual void OnResized(int old_w, int old_h);
	virtual TBWidget *GetContentRoot() { return &m_root; }

	virtual PreferredSize OnCalculatePreferredContentSize(const SizeConstraints &constraints);

	virtual void OnMessageReceived(TBMessage *msg);
private:
	TBScrollBar m_scrollbar_x;
	TBScrollBar m_scrollbar_y;
	TBWidgetString m_placeholder;
	EDIT_TYPE m_edit_type;
	TBEditFieldScrollRoot m_root;
	TBEditFieldContentFactory m_content_factory;
	TBStyleEdit m_style_edit;
	bool m_adapt_to_content_size;
	int m_virtual_width;
	void UpdateScrollbarVisibility(bool multiline);

	// == TBStyleEditListener =======================
	virtual void OnChange();
	virtual bool OnEnter();
	virtual void Invalidate(const TBRect &rect);
	virtual void DrawString(int32 x, int32 y, TBFontFace *font, const TBColor &color, const char *str, int32 len);
	virtual void DrawRect(const TBRect &rect, const TBColor &color);
	virtual void DrawRectFill(const TBRect &rect, const TBColor &color);
	virtual void DrawTextSelectionBg(const TBRect &rect);
	virtual void DrawContentSelectionFg(const TBRect &rect);
	virtual void DrawCaret(const TBRect &rect);
	virtual void Scroll(int32 dx, int32 dy);
	virtual void UpdateScrollbars();
	virtual void CaretBlinkStart();
	virtual void CaretBlinkStop();
};

}; // namespace tb

#endif // TB_EDITFIELD_H
