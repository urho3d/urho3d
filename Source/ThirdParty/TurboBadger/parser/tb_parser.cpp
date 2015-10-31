// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "parser/tb_parser.h"
#include "tb_tempbuffer.h"
#include "utf8/utf8.h"
#include <assert.h>
#include <ctype.h>

namespace tb {

// == Util functions ====================================================================

static bool is_hex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

static uint32 parse_hex(char *&src, int max_count)
{
	uint32 hex = 0;
	for (int i = 0; i < max_count; i++)
	{
		char c = *src;
		if (!is_hex(c))
			break;
		hex <<= 4;
		hex |= isdigit(c) ? c - '0' : tolower(c) - 'a' + 10;
		src++;
	}
	return hex;
}

void UnescapeString(char *str)
{
	// fast forward to any escape sequence
	while (*str && *str != '\\')
		str++;

	char *dst = str, *src = str;
	while (*src)
	{
		if (*src == '\\')
		{
			bool code_found = true;
			switch (src[1])
			{
			case 'a': *dst = '\a'; break;
			case 'b': *dst = '\b'; break;
			case 'f': *dst = '\f'; break;
			case 'n': *dst = '\n'; break;
			case 'r': *dst = '\r'; break;
			case 't': *dst = '\t'; break;
			case 'v': *dst = '\v'; break;
			case '0': *dst = '\0'; break;
			case '\"': *dst = '\"'; break;
			case '\'': *dst = '\''; break;
			case '\\': *dst = '\\'; break;
			case 'x': // \xXX
			case 'u': // \uXXXX
			{
				// This should be safe. A utf-8 character can be at most 4 bytes,
				// and we have 4 bytes to use for \xXX and 6 for \uXXXX.
				src += 2;
				if (UCS4 hex = parse_hex(src, src[1] == 'x' ? 2 : 4))
					dst += utf8::encode(hex, dst);
				continue;
			}
			default:
				code_found = false;
			}
			if (code_found)
			{
				src += 2;
				dst++;
				continue;
			}
		}
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
}

bool is_white_space(const char *str)
{
	switch (*str)
	{
	case ' ':
	case '\t':
		return true;
	default:
		return false;
	}
}

/** Return true if the given string starts with a color.
	Ex: #ffdd00, #fd0 */
bool is_start_of_color(const char *str)
{
	if (*str++ != '#')
		return false;
	int digit_count = 0;
	while (is_hex(*str))
	{
		str++;
		digit_count++;
	}
	return digit_count == 8 || digit_count == 6 || digit_count == 4 || digit_count == 3;
}

/** Return true if the given string may be a node reference, such
	as language strings or TBNodeRefTree references. */
bool is_start_of_reference(const char *str)
{
	if (*str++ != '@')
		return false;
	while (*str && *str != ' ')
	{
		// If the token ends with colon, it's not a value but a key.
		if (*str == ':')
			return false;
		str++;
	}
	return true;
}

/** Check if the line is a comment or empty space. If it is, consume the leading
	whitespace from line. */
bool is_space_or_comment(char *&line)
{
	char *tmp = line;
	while (is_white_space(tmp))
		tmp++;
	if (*tmp == '#' || *tmp == 0)
	{
		line = tmp;
		return true;
	}
	return false;
}

bool is_pending_multiline(const char *str)
{
	while (is_white_space(str))
		str++;
	return str[0] == '\\' && str[1] == 0;
}

bool IsEndQuote(const char *buf_start, const char *buf, const char quote_type)
{
	if (*buf != quote_type)
		return false;
	int num_backslashes = 0;
	while (buf_start < buf && *(buf-- - 1) == '\\')
		num_backslashes++;
	return !(num_backslashes & 1);
}

// == Parser ============================================================================

TBParser::STATUS TBParser::Read(TBParserStream *stream, TBParserTarget *target)
{
	TBTempBuffer line, work;
	if (!line.Reserve(1024) || !work.Reserve(1024))
		return STATUS_OUT_OF_MEMORY;

	current_indent = 0;
	current_line_nr = 1;
	pending_multiline = false;
	multi_line_sub_level = 0;

	while (int read_len = stream->GetMoreData((char *)work.GetData(), work.GetCapacity()))
	{
		char *buf = work.GetData();

		// Skip BOM (BYTE ORDER MARK) character, often in the beginning of UTF-8 documents.
		if (current_line_nr == 1 && read_len > 3 &&
			(uint8)buf[0] == 239 &&
			(uint8)buf[1] == 187 &&
			(uint8)buf[2] == 191)
		{
			read_len -= 3;
			buf += 3;
		}

		int line_pos = 0;
		while (true)
		{
			// Find line end
			int line_start = line_pos;
			while (line_pos < read_len && buf[line_pos] != '\n')
				line_pos++;

			if (line_pos < read_len)
			{
				// We have a line
				// Skip preceding \r (if we have one)
				int line_len = line_pos - line_start;
				if (!line.Append(buf + line_start, line_len))
					return STATUS_OUT_OF_MEMORY;

				// Strip away trailing '\r' if the line has it
				char *linebuf = line.GetData();
				int linebuf_len = line.GetAppendPos();
				if (linebuf_len > 0 && linebuf[linebuf_len - 1] == '\r')
					linebuf[linebuf_len - 1] = 0;

				// Terminate the line string
				if (!line.Append("", 1))
					return STATUS_OUT_OF_MEMORY;

				// Handle line
				OnLine(line.GetData(), target);
				current_line_nr++;

				line.ResetAppendPos();
				line_pos++; // Skip this \n
				// Find next line
				continue;
			}
			// No more lines here so push the rest and break for more data
			if (!line.Append(buf + line_start, read_len - line_start))
				return STATUS_OUT_OF_MEMORY;
			break;
		}
	}
	if (line.GetAppendPos())
	{
		if (!line.Append("", 1))
			return STATUS_OUT_OF_MEMORY;
		OnLine(line.GetData(), target);
		current_line_nr++;
	}
	return STATUS_OK;
}

void TBParser::OnLine(char *line, TBParserTarget *target)
{
	if (is_space_or_comment(line))
	{
		if (*line == '#')
			target->OnComment(current_line_nr, line + 1);
		return;
	}
	if (pending_multiline)
	{
		OnMultiline(line, target);
		return;
	}

	// Check indent
	int indent = 0;
	while (line[indent] == '\t' && line[indent] != 0)
		indent++;
	line += indent;

	if (indent - current_indent > 1)
	{
		target->OnError(current_line_nr, "Indentation error. (Line skipped)");
		return;
	}

	if (indent > current_indent)
	{
		// FIX: Report indentation error if more than 1 higher!
		assert(indent - current_indent == 1);
		target->Enter();
		current_indent++;
	}
	else if (indent < current_indent)
	{
		while (indent < current_indent)
		{
			target->Leave();
			current_indent--;
		}
	}

	if (*line == 0)
		return;
	else
	{
		char *token = line;
		// Read line while consuming it and copy over to token buf
		while (!is_white_space(line) && *line != 0)
			line++;
		int token_len = line - token;
		// Consume any white space after the token
		while (is_white_space(line))
			line++;

		bool is_compact_line = token_len && token[token_len - 1] == ':';

		TBValue value;
		if (is_compact_line)
		{
			token_len--;
			token[token_len] = 0;

			// Check if the first argument is not a child but the value for this token
			if (*line == '[' || *line == '\"' || *line == '\'' ||
				is_start_of_number(line) ||
				is_start_of_color(line) ||
				is_start_of_reference(line))
			{
				ConsumeValue(value, line);

				if (pending_multiline)
				{
					// The value wrapped to the next line, so we should remember the token and continue.
					multi_line_token.Set(token);
					return;
				}
			}
		}
		else if (token[token_len])
		{
			token[token_len] = 0;
			UnescapeString(line);
			value.SetFromStringAuto(line, TBValue::SET_AS_STATIC);
		}
		target->OnToken(current_line_nr, token, value);

		if (is_compact_line)
			OnCompactLine(line, target);
	}
}

void TBParser::OnCompactLine(char *line, TBParserTarget *target)
{
	target->Enter();
	while (*line)
	{
		// consume any whitespace
		while (is_white_space(line))
			line++;

		// Find token
		char *token = line;
		while (*line != ':' && *line != 0)
			line++;
		if (!*line)
			break; // Syntax error, expected token
		*line++ = 0;

		// consume any whitespace
		while (is_white_space(line))
			line++;

		TBValue v;
		ConsumeValue(v, line);

		if (pending_multiline)
		{
			// The value wrapped to the next line, so we should remember the token and continue.
			multi_line_token.Set(token);
			// Since we need to call target->Leave when the multiline is ready, set multi_line_sub_level.
			multi_line_sub_level = 1;
			return;
		}

		// Ready
		target->OnToken(current_line_nr, token, v);
	}

	target->Leave();
}

void TBParser::OnMultiline(char *line, TBParserTarget *target)
{
	// consume any whitespace
	while (is_white_space(line))
		line++;

	TBValue value;
	ConsumeValue(value, line);

	if (!pending_multiline)
	{
		// Ready with all lines
		value.SetString(multi_line_value.GetData(), TBValue::SET_AS_STATIC);
		target->OnToken(current_line_nr, multi_line_token, value);

		if (multi_line_sub_level)
			target->Leave();

		// Reset
		multi_line_value.SetAppendPos(0);
		multi_line_sub_level = 0;
	}
}

void TBParser::ConsumeValue(TBValue &dst_value, char *&line)
{
	// Find value (As quoted string, or as auto)
	char *value = line;
	if (*line == '\"' || *line == '\'')
	{
		const char quote_type = *line;
		// Consume starting quote
		line++;
		value++;
		// Find ending quote or end
		while (!IsEndQuote(value, line, quote_type) && *line != 0)
			line++;
		// Terminate away the quote
		if (*line == quote_type)
			*line++ = 0;

		// consume any whitespace
		while (is_white_space(line))
			line++;
		// consume any comma
		if (*line == ',')
			line++;

		UnescapeString(value);
		dst_value.SetString(value, TBValue::SET_AS_STATIC);
	}
	else
	{
		// Find next comma or end
		while (*line != ',' && *line != 0)
			line++;
		// Terminate away the comma
		if (*line == ',')
			*line++ = 0;

		UnescapeString(value);
		dst_value.SetFromStringAuto(value, TBValue::SET_AS_STATIC);
	}

	// Check if we still have pending value data on the following line and set pending_multiline.
	bool continuing_multiline = pending_multiline;
	pending_multiline = is_pending_multiline(line);

	// Append the multi line value to the buffer.
	if (continuing_multiline || pending_multiline)
		multi_line_value.AppendString(dst_value.GetString());
}

}; // namespace tb
