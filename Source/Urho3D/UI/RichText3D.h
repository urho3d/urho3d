#ifndef __RICH_TEXT_3D_H__
#define __RICH_TEXT_3D_H__
#pragma once

#include "../UI/RichWidget.h"

namespace Urho3D {

enum TickerType {
	TickerType_None,
	TickerType_Horizontal,
	TickerType_Vertical,
};

enum TickerDirection {
  TickerDirection_Negative,
  TickerDirection_Positive,
};

enum TextAlign {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

enum TextWrapping {
	WRAP_NONE,
	WRAP_WORD
};

// TODO: need more lightweight structures
struct FontState {
	String face;
	unsigned char size;
	Color color;
	bool	bold;
	bool	italic;
	bool	underlined;
	bool	striked;
	bool	superscript;
	bool	subscript;

	FontState():
	size(0),
		bold(false),
		italic(false),
		underlined(false),
		striked(false),
		superscript(false),
		subscript(false)
	{
	};
};

struct TextBlock {
	// either the text or the image source
	String text; 
	FontState font;

	float image_width;
  float image_height;
	bool is_iconic;
	bool is_visible;
	bool is_line_brake;

  void Reset() {
    image_width = 0;
    image_height = 0;
    is_iconic = false;
    is_visible = true;
    is_line_brake = false;
  }

	TextBlock()
		: image_width(0)
		, image_height(0)
		, is_iconic(false)
		, is_visible(true)
		, is_line_brake(false) {

	}
};

typedef Vector<TextBlock> BlockVector; 

struct TextLine {
	TextLine()
		: Width(0)
		, Height(0)
		, offsetX(0)
		, offsetY(0)
		, align(ALIGN_LEFT) {

	}

	int Width;
	int Height;

	int offsetX;
	int offsetY;

	TextAlign	align;

	BlockVector blocks;
};

typedef Vector<TextLine> LineVector;

	
// RichTextView3D
class RichTextView3D: public RichWidget {
  URHO3D_OBJECT(RichTextView3D, RichWidget)
public:
  /// Register object factory. Drawable must be registered first.
  static void RegisterObject(Context* context);

  RichTextView3D(Context* context);
  virtual ~RichTextView3D();

  // Set display text inside the view
	void SetText(const String& text/*, const String& context_name = ""*/);
  // Get currently displayed text
  const String& GetText() const;
  // Enable script parser
	void SetParserEnabled(bool parse_script);
  // Parser enabled ?
	bool GetParserEnabled() const { return parse_script_; }
  // Set the default font for blocks without formatting
	void SetDefaultFont(const String& face, unsigned char size, bool bold, bool italic, bool underlined);
  // Set text color
  void SetTextColor(const Color& color);
  // Get text color
	Color GetTextColor() const { return default_font_state_.color; }
  // Set text alignment
  void SetAlignment(TextAlign align);
  // Get text alignment
  TextAlign GetAlignment() const { return alignment_; }
  // Set additional line spacing
  void SetLineSpacing(int line_spacing);
  // Get additional line spacing
  int GetLineSpacing() const { return line_spacing_; }
  // Set word wrapping
  void SetWrapping(bool wrapping);
  // Get wrapping
  bool GetWrapping() const { return wrapping_ == WRAP_WORD; }
  // Set ticker type
  void SetTickerType(TickerType type);
  // Get ticker type
  TickerType GetTickerType() const;
  // Set ticker scroll direction
  void SetTickerDirection(TickerDirection direction);
  // Get ticker scroll direction
  TickerDirection GetTickerDirection() const;
  // Set ticker scroll speed
  void SetTickerSpeed(float pixelspersecond);
  // Get ticker scroll speed
  float GetTickerSpeed() const;
  // Set single line
  void SetSingleLine(bool single_line);
  // Get single line
  bool GetSingleLine() const { return single_line_; }
  // Reset the ticker to the beginning
  void ResetTicker();
  // Set ticker position (0-1 range)
	void SetTickerPosition(float tickerPosition);
  // Get ticker position (0-1 range)
	float GetTickerPosition() const;
  // Get refresh count - number of times the view is recompiled
	unsigned GetRefreshCount() const { return refresh_count_; }
  // Get font ResourceRef
  ResourceRef GetFontAttr() const;
  // Set font ResourceRef
  void SetFontAttr(const ResourceRef& value);
  // Get font size
  int GetFontSizeAttr() const;
  // Set font size
  void SetFontSizeAttr(int size);
protected:
	// the caption text
	String text_;
  // additional line spacing
  int line_spacing_;
  // last recompile time
	long long last_update_time_;
  // last script recompile
	long long last_script_update_;
	// ticker type
	TickerType ticker_type_;
  // ticker direction
  TickerDirection ticker_direction_;
  // ticker speed
	float ticker_speed_;
	// default font state for unformatted text
	FontState default_font_state_;
	// the lines of text, could be removed in the future
	LineVector lines_;
	// the scroll origin of the text (in ticker mode)
	Vector3 scroll_origin_;
	// is the text single line
	bool single_line_;
	// ticker position (0-1)
	float ticker_position_;
	// wrapping
	TextWrapping wrapping_;
  // alignment
	TextAlign alignment_;
  // enable script parsing
	bool parse_script_;
  // script parser context
	String context_name_;
	// how many times this text has recompiled itself
	unsigned refresh_count_;
	// Compile the text to render items
  void CompileTextLayout();
  // Arrange text blocks into the textview layout as lines
  void ArrangeTextBlocks(BlockVector& markup_blocks);
  // Draw text lines to the widget
  void DrawTextLines();
  // Called when widget needs to update itself
  virtual void OnUpdate();
};

} // namespace engine

#endif
