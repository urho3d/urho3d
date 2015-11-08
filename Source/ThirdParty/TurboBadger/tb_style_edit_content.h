// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_STYLE_EDIT_CONTENT_H
#define TB_STYLE_EDIT_CONTENT_H

#include "tb_core.h"

namespace tb {

class TBTextFragment;

/** Content for a non-text TBTextFragment. */

class TBTextFragmentContent
{
public:
	virtual ~TBTextFragmentContent() {}

	/** Update the position of the content, relative to the first line of text (no scrolling applied). */
	virtual void UpdatePos(int x, int y) {}

	virtual void Paint(TBTextFragment *fragment, int32 translate_x, int32 translate_y, TBTextProps *props) {}
	virtual void Click(TBTextFragment *fragment, int button, uint32 modifierkeys) {}
	virtual int32 GetWidth(TBFontFace *font, TBTextFragment *fragment) { return 0; }
	virtual int32 GetHeight(TBFontFace *font, TBTextFragment *fragment) { return 0; }
	virtual int32 GetBaseline(TBFontFace *font, TBTextFragment *fragment) { return GetHeight(font, fragment); }
	virtual bool GetAllowBreakBefore() { return true; }
	virtual bool GetAllowBreakAfter() { return true; }

	/** Get type of fragment content. All standard fragments return 0. */
	virtual uint32 GetType()		{ return 0; }
};

/** A horizontal line for TBStyleEdit. */

class TBTextFragmentContentHR : public TBTextFragmentContent
{
public:
	TBTextFragmentContentHR(int32 width_in_percent, int32 height);

	virtual void Paint(TBTextFragment *fragment, int32 translate_x, int32 translate_y, TBTextProps *props);
	virtual int32 GetWidth(TBFontFace *font, TBTextFragment *fragment);
	virtual int32 GetHeight(TBFontFace *font, TBTextFragment *fragment);
private:
	int32 width_in_percent, height;
};

/** Fragment content that enables underline in a TBStyleEdit */

class TBTextFragmentContentUnderline : public TBTextFragmentContent
{
public:
	TBTextFragmentContentUnderline() {}
	virtual void Paint(TBTextFragment *fragment, int32 translate_x, int32 translate_y, TBTextProps *props);
	virtual bool GetAllowBreakBefore() { return true; }
	virtual bool GetAllowBreakAfter() { return false; }
};

/** Fragment content that changes color in a TBStyleEdit */

class TBTextFragmentContentTextColor : public TBTextFragmentContent
{
public:
	TBColor color;
	TBTextFragmentContentTextColor(const TBColor &color) : color(color) {}
	virtual void Paint(TBTextFragment *fragment, int32 translate_x, int32 translate_y, TBTextProps *props);
	virtual bool GetAllowBreakBefore() { return true; }
	virtual bool GetAllowBreakAfter() { return false; }
};

/** Fragment content that ends a change of style in a TBStyleEdit */

class TBTextFragmentContentStylePop : public TBTextFragmentContent
{
public:
	virtual void Paint(TBTextFragment *fragment, int32 translate_x, int32 translate_y, TBTextProps *props);
	virtual bool GetAllowBreakBefore() { return false; }
	virtual bool GetAllowBreakAfter() { return true; }
};

}; // namespace tb

#endif // TB_STYLE_EDIT_CONTENT_H
