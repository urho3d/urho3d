// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_tempbuffer.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

namespace tb {

static char *p_realloc(char *buf, size_t size) { return (char *) realloc(buf, size); }
static void p_free(char *buf) { free(buf); }

TBTempBuffer::TBTempBuffer()
	: m_data(0)
	, m_data_size(0)
	, m_append_pos(0)
{
}

TBTempBuffer::~TBTempBuffer()
{
	p_free(m_data);
}

void TBTempBuffer::SetAppendPos(int append_pos)
{
	assert(append_pos >= 0 && append_pos <= m_data_size);
	m_append_pos = append_pos;
}

bool TBTempBuffer::Reserve(int size)
{
	if (size > m_data_size)
	{
		char *new_data = p_realloc(m_data, size);
		if (!new_data)
			return false;
		m_data = new_data;
		m_data_size = size;
	}
	return true;
}

int TBTempBuffer::GetAppendReserveSize(int needed_size) const
{
	// Reserve some extra memory to reduce the reserve calls.
	needed_size *= 2;
	return needed_size < 32 ? 32 : needed_size;
}

bool TBTempBuffer::Append(const char *data, int size)
{
	if (m_append_pos + size > m_data_size && !Reserve(GetAppendReserveSize(m_append_pos + size)))
		return false;
	memcpy(m_data + m_append_pos, data, size);
	m_append_pos += size;
	return true;
}

bool TBTempBuffer::AppendSpace(int size)
{
	if (m_append_pos + size > m_data_size && !Reserve(GetAppendReserveSize(m_append_pos + size)))
		return false;
	m_append_pos += size;
	return true;
}

bool TBTempBuffer::AppendString(const char *str)
{
	// Add 1 to include the null termination in the data.
	if (Append(str, strlen(str) + 1))
	{
		// Now remove the null termination from the append position
		// again, so another call will append to the same string (instead of
		// after the null termination of the first string)
		m_append_pos--;
		return true;
	}
	return false;
}

bool TBTempBuffer::AppendPath(const char *full_path_and_filename)
{
	const char *str_start = full_path_and_filename;
	while (const char *next = strpbrk(full_path_and_filename, "\\/"))
		full_path_and_filename = next + 1;

	if (str_start == full_path_and_filename) // Filename contained no path
	{
		str_start = "./";
		full_path_and_filename = str_start + 2;
	}

	int len = full_path_and_filename - str_start;
	if (Reserve(len + 1))
	{
		// Add the string, and nulltermination.
		Append(str_start, len);
		Append("", 1);
		// Remove null termination from append pos again (see details in AppendString).
		m_append_pos--;
		return true;
	}
	return false;
}

}; // namespace tb
