#include "../UI/RichMarkupParser.h"
#include "../Core/StringUtils.h"

namespace Urho3D {

namespace {

typedef struct {
  const char* name;
  const Color color;
} ColorEntry;

inline Color ParseHTMLColor(const String& str) {
  static const ColorEntry color_table[] = {
    { "red", Color::RED },
    { "green", Color::GREEN },
    { "blue", Color::BLUE },
    { "black", Color::BLACK },
    { "white", Color::WHITE },
    { "transparent", Color::TRANSPARENT },
    { "yellow", Color::YELLOW },
    { "cyan", Color::CYAN },
    { "magenta", Color::MAGENTA },
    { "gray", Color::GRAY },
    { "orange", Color(1.0f, 0.647f, 0.0f) },
    // TODO: Add more colors
    { NULL, Color() },
  };

  unsigned char R = 0, G = 0, B = 0, A = 0;

  String color = str.ToLower();

  for (int i = 0; color_table[i].name; i++) {
    const ColorEntry* entry = &color_table[i];
    if (color.Compare(entry->name) == 0)
      return entry->color;
  }

  if (color.Length() == 7 || color.Length() == 9) {
    if (color.Find("#") == 0) {
			R = (unsigned char)strtoul(str.Substring(1, 2).CString(), 0, 16);
      G = (unsigned char)strtoul(str.Substring(3, 2).CString(), 0, 16);
      B = (unsigned char)strtoul(str.Substring(5, 2).CString(), 0, 16);
      A = str.Length() == 7 ? 255 : (unsigned char)strtoul(str.Substring(7, 2).CString(), 0, 16);
		}
	}	

  return Color((float)R / 255.0f, (float)G / 255.0f, (float)B / 255.0f, (float)A / 255.0f);
}

} // namespace

// Supported tags:
//  <br> - line break
//  <b></b> - bold
//  <i></i> - italic
//  <color=#FF800000></color> - change text color, supports 24/32 bit hex and color names
//  <size=14></size> - change text size in pixels
//  <font=Fonts/Annonymous Pro.ttf></font> - change text font
//  <img src=image.png width=320 height=240 /> - embed an image
//  TODO: <quad material=material.xml width=10 height=10 x=10 y=10 />
void HTMLParser::Parse(const String& text, BlockVector& blocks, const FontState& default_font_state) {
  unsigned pos = 0, last_tag_end = 0;
  unsigned tag_begin = 0, tag_end = 0;
  bool closing_tag = false;
  String tag;

  Vector<TextBlock> stack;
  TextBlock* current_block = 0;

  // copy everything up to the first found tag
  pos = text.Find('<', pos, false);
  if (pos != String::NPOS && pos != 0) {
    TextBlock block;
    block.font = default_font_state;
    block.text = text.Substring(0, pos);
    blocks.Push(block);
    last_tag_end = pos;
  }

  while ((pos = text.Find('<', pos, false)) != String::NPOS) {
    tag_end = text.Find('>', pos + 1, false);
    // skip <>
    if (tag_end == pos + 1) {
      pos += 1;
      continue;
    }

    // stop if there's no closing tag or text ends
    if (pos + 1 >= text.Length() || tag_end == String::NPOS) {
      break;
    }

    tag_begin = pos;
    closing_tag = text[pos + 1] == '/';

    pos += closing_tag ? 2 : 1;

    tag = text.Substring(pos, tag_end - pos);

    TextBlock block;

    if (!closing_tag) {
      block.text = text.Substring(last_tag_end, tag_begin - last_tag_end);

      if (tag == "br") {
        // Append current text as a block
        if (current_block)
          block.font = current_block->font;
        blocks.Push(block);
        // Append line break tag
        block.is_line_brake = true;
        block.text.Clear();
        blocks.Push(block);
      } else if (tag.StartsWith("img")) {
        // Append current text as a block
        if (current_block)
          block.font = current_block->font;
        blocks.Push(block);

        block.is_iconic = true;
        closing_tag = true;
        auto img_tokens = tag.Split(' ');
        for (auto& t : img_tokens) {
          auto tokens = t.Split('=');
          if (tokens.Size() == 2) {
            const String& name = tokens[0];
            const String& value = tokens[1];
            if (name == "width")
              block.image_width = ToFloat(value);
            else if (name == "height")
              block.image_height = ToFloat(value);
            else if (name == "src")
              block.text = value;
          }
        }
        
        // Append image tag
        blocks.Push(block);
      } else if (tag == "b") {
        block.font.bold = true;
      } else if (tag == "i") {
        block.font.italic = true;
      } else if (tag.StartsWith("color")) {
        auto tokens = tag.Split('=');
        if (tokens.Size() >= 2)
          block.font.color = ParseHTMLColor(tokens[1]);
      } else if (tag.StartsWith("size")) {
        auto tokens = tag.Split('=');
        if (tokens.Size() >= 2)
          block.font.size = ToInt(tokens[1]);
      }
    } else if (current_block)
      current_block->text = text.Substring(last_tag_end, tag_begin - last_tag_end);

    // On every tag found, push the current block to the list of blocks
    if (current_block && !block.is_line_brake) {
      if (!closing_tag)
        current_block->text = block.text;
      if (!current_block->text.Empty())
        blocks.Push(*current_block);
    }

    if (closing_tag) {
      // On closing tag, pop one block from the stack
      if (!stack.Empty())
        stack.Pop();
    } else {
      // On opening tag, push the current block in the stack
      if (!block.is_line_brake)
        stack.Push(block);
    }

    pos = tag_end + 1;
    last_tag_end = tag_end + 1;

    if (!stack.Empty())
      current_block = &stack[stack.Size() - 1];
    else
      current_block = 0;
  }

  // copy anything after the last tag
  if (last_tag_end < text.Length() - 1) {
    TextBlock block;
    block.font = default_font_state;
    block.text = text.Substring(last_tag_end, text.Length() - last_tag_end);
    blocks.Push(block);
  }

  // append blocks that are not closed properly
  if (!closing_tag && current_block && !current_block->text.Empty()) {
    blocks.Push(*current_block);
  }
}

} // namespace Urho3D