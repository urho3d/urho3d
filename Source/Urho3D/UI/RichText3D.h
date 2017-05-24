#pragma once

#include "../UI/RichWidget.h"

namespace Urho3D {

/// Ticker type
enum TickerType
{
    TickerType_None,
    TickerType_Horizontal,
    TickerType_Vertical,
};

/// Ticker direction
enum TickerDirection
{
    TickerDirection_Negative,
    TickerDirection_Positive,
};

/// Text align
enum TextAlign
{
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
};

/// Text wrapping
enum TextWrapping
{
    WRAP_NONE,
    WRAP_WORD
};

/// Font description of a text block
struct FontState
{
    String face;
    unsigned size;
    Color color;
    bool bold;
    bool italic;
    bool underlined;
    bool striked;
    bool superscript;
    bool subscript;

    FontState()
     : size(0),
       bold(false),
       italic(false),
       underlined(false),
       striked(false),
       superscript(false),
       subscript(false) {};
};

/// A block of text or an image
struct TextBlock
{
    /// Text or image/material source
    String text; 
    /// Font description of this block (if this is a text block)
    FontState font;

    float image_width;
    float image_height;
    bool is_iconic;
    bool is_visible;
    bool is_line_brake;

    void Reset() {
      image_width = 0.0f;
      image_height = 0.0f;
      is_iconic = false;
      is_visible = true;
      is_line_brake = false;
    }

    TextBlock()
     : image_width(0.0f)
     , image_height(0.0f)
     , is_iconic(false)
     , is_visible(true)
     , is_line_brake(false) {}
};

/// A line inside the text layout
struct TextLine
{
    TextLine()
     : width(0)
     , height(0)
      , offset_x(0)
      , offset_y(0)
      , align(ALIGN_LEFT) {}

    int width;
    int height;

    int offset_x;
    int offset_y;

    TextAlign	align;
    Vector<TextBlock> blocks;
};

/// RichText3D
class RichText3D: public RichWidget
{
  URHO3D_OBJECT(RichText3D, RichWidget)
public:
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Contructor.
    RichText3D(Context* context);
    /// Destructor.
    virtual ~RichText3D();

    /// Set display text inside the view.
    void SetText(const String& text);
    /// Get currently displayed text (as markup).
    const String& GetText() const;
    /// Set the default font for blocks without formatting.
    void SetDefaultFont(const String& face, unsigned size, bool bold, bool italic, bool underlined);
    /// Set text color.
    void SetTextColor(const Color& color);
    /// Get text color.
    Color GetTextColor() const { return default_font_state_.color; }
    /// Set text alignment.
    void SetAlignment(TextAlign align);
    /// Get text alignment.
    TextAlign GetAlignment() const { return alignment_; }
    /// Set additional line spacing (can be negative).
    void SetLineSpacing(int line_spacing);
    /// Get additional line spacing.
    int GetLineSpacing() const { return line_spacing_; }
    /// Set word wrapping.
    void SetWrapping(bool wrapping);
    /// Get wrapping.
    bool GetWrapping() const { return wrapping_ == WRAP_WORD; }
    /// Set ticker type.
    void SetTickerType(TickerType type);
    /// Get ticker type.
    TickerType GetTickerType() const;
    /// Set ticker scroll direction.
    void SetTickerDirection(TickerDirection direction);
    /// Get ticker scroll direction.
    TickerDirection GetTickerDirection() const;
    /// Set ticker scroll speed.
    void SetTickerSpeed(float pixelspersecond);
    /// Get ticker scroll speed.
    float GetTickerSpeed() const;
    /// Set single line.
    void SetSingleLine(bool single_line);
    /// Get single line.
    bool GetSingleLine() const { return single_line_; }
    /// Reset the ticker to the beginning.
    void ResetTicker();
    /// Set ticker position (0-1 range).
    void SetTickerPosition(float tickerPosition);
    /// Get ticker position (0-1 range).
    float GetTickerPosition() const;
    /// Get refresh count - number of times the view is recompiled.
    unsigned GetRefreshCount() const { return refresh_count_; }
    /// Get font ResourceRef.
    ResourceRef GetFontAttr() const;
    /// Set font ResourceRef.
    void SetFontAttr(const ResourceRef& value);
    /// Get font size.
    int GetFontSizeAttr() const;
    /// Set font size.
    void SetFontSizeAttr(int size);
protected:
    /// The caption text.
    String text_;
    /// Additional line spacing (can be negative).
    int line_spacing_;
    /// Last recompile time.
    long long	last_update_time_;
    /// Last script recompile.
    long long	last_script_update_;
    /// Ticker type.
    TickerType ticker_type_;
    /// Ticker direction.
    TickerDirection ticker_direction_;
    /// Ticker speed.
    float ticker_speed_;
    /// Default font state for unformatted text.
    FontState default_font_state_;
    /// The lines of text.
    Vector<TextLine> lines_; // TODO: could be removed in the future.
    /// The scroll origin of the text (in ticker mode).
    Vector3 scroll_origin_;
    /// Is the text single line.
    bool single_line_;
    /// Ticker position (0-1).
    float ticker_position_;
    /// Wrapping
    TextWrapping wrapping_;
    /// Alignment
    TextAlign alignment_;
    /// How many times this text has recompiled itself
    unsigned refresh_count_;

    /// Compile the text to render items.
    void CompileTextLayout();
    /// Arrange text blocks into the textview layout as lines.
    void ArrangeTextBlocks(Vector<TextBlock>& markup_blocks);
    /// Draw text lines to the widget.
    void DrawTextLines();

    void UpdateTickerAnimation(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
};

} // namespace Urho3D
