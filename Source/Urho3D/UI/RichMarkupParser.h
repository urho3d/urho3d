#pragma once

#include "../UI/RichText3D.h"

namespace Urho3D
{

/// An utility class that parses RichText markup.
class HTMLParser
{
public:
    /// Parse the text and outputs the text as TextBlock array.
    static void Parse(const String& text, Vector<TextBlock>& blocks, const FontState& default_font_state);
};

} // namespace Urho3D

