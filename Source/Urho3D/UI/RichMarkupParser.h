#ifndef __RICH_HTML_PARSER_H__
#define __RICH_HTML_PARSER_H__
#pragma once

#include "../UI/RichText3D.h"

namespace Urho3D {

class HTMLParser {
public:
	static void Parse(const String& text, BlockVector& blocks, const FontState& default_font_state);
};

} // namespace Urho3D

#endif