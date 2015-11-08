// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_dimension.h"
#include "tb_types.h"
#include "tb_system.h"
#include "tb_tempbuffer.h"
#include "tb_value.h"
#include <stdlib.h>
#include <ctype.h>

namespace tb {

// == TBDimensionConverter ==================================================================================

void TBDimensionConverter::SetDPI(int src_dpi, int dst_dpi)
{
	m_src_dpi = src_dpi;
	m_dst_dpi = dst_dpi;
	m_dst_dpi_str.Clear();
	if (NeedConversion())
		m_dst_dpi_str.SetFormatted("@%d", m_dst_dpi);
}

void TBDimensionConverter::GetDstDPIFilename(const char *filename, TBTempBuffer *tempbuf) const
{
	int dot_pos = 0;
	for (dot_pos = strlen(filename) - 1; dot_pos > 0; dot_pos--)
		if (filename[dot_pos] == '.')
			break;
	tempbuf->ResetAppendPos();
	tempbuf->Append(filename, dot_pos);
	tempbuf->AppendString(GetDstDPIStr());
	tempbuf->AppendString(filename + dot_pos);
}

int TBDimensionConverter::DpToPx(int dp) const
{
	if (dp <= TB_INVALID_DIMENSION || dp == 0 || !NeedConversion())
		return dp;
	if (dp > 0)
	{
		dp = dp * m_dst_dpi / m_src_dpi;
		return MAX(dp, 1);
	}
	else
	{
		dp = dp * m_dst_dpi / m_src_dpi;
		return MIN(dp, -1);
	}
}

int TBDimensionConverter::MmToPx(int mm) const
{
	if (mm <= TB_INVALID_DIMENSION || mm == 0)
		return mm;

	return (int) (mm * TBSystem::GetDPI() / 25.4f + 0.5f);
}

int TBDimensionConverter::GetPxFromString(const char *str, int def_value) const
{
	if (!str || !is_start_of_number(str))
		return def_value;
	int len = strlen(str);
	int val = atoi(str);
	// "dp" and unspecified unit is dp.
	if ((len > 0 && isdigit(str[len - 1])) ||
		(len > 2 && strcmp(str + len - 2, "dp") == 0))
		return DpToPx(val);
	else if (len > 2 && strcmp(str + len - 2, "mm") == 0)
		return MmToPx(val);
	else
		return val;
}

int TBDimensionConverter::GetPxFromValue(TBValue *value, int def_value) const
{
	if (!value)
		return def_value;
	if (value->GetType() == TBValue::TYPE_INT)
		return DpToPx(value->GetInt());
	else if (value->GetType() == TBValue::TYPE_FLOAT)
		// FIX: We might want float versions of all dimension functions.
		return DpToPx((int)value->GetFloat());
	return GetPxFromString(value->GetString(), def_value);
}

}; // namespace tb
