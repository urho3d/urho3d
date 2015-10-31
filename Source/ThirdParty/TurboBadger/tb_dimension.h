// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_DIMENSION_H
#define TB_DIMENSION_H

#include "tb_types.h"
#include "tb_debug.h"
#include "tb_str.h"

namespace tb {

/** Dimensions <= this value will be untouched by conversion in TBDimensionConverter.
	To preserve special constants, those must be <= this value. */
#define TB_INVALID_DIMENSION -5555

class TBTempBuffer;
class TBValue;

/** TBDimensionConverter converts device independant points
	to pixels, based on two DPI values.
	Dimensions in Turbo Badger are normally in pixels (if not specified differently)
	and conversion normally take place when loading skin. */
class TBDimensionConverter
{
	int m_src_dpi; ///< The source DPI (Normally the base_dpi from skin).
	int m_dst_dpi; ///< The destination DPI (Normally the supported skin DPI nearest to TBSystem::GetDPI).
	TBStr m_dst_dpi_str; ///< The file suffix that should be used to load bitmaps in destinatin DPI.
public:
	TBDimensionConverter() : m_src_dpi(100), m_dst_dpi(100) {}

	/** Set the source and destination DPI that will affect the conversion. */
	void SetDPI(int src_dpi, int dst_dpi);

	/** Get the source DPI. */
	int GetSrcDPI() const { return m_src_dpi; }

	/** Get the destination DPI. */
	int GetDstDPI() const { return m_dst_dpi; }

	/** Get the file name suffix that should be used to load bitmaps in the destination DPI.
		Examples: "@96", "@196" */
	const char *GetDstDPIStr() const { return m_dst_dpi_str; }

	/** Get the file name with destination DPI suffix (F.ex "foo.png" becomes "foo@192.png").
		The temp buffer will contain the resulting file name. */
	void GetDstDPIFilename(const char *filename, TBTempBuffer *tempbuf) const;

	/** Return true if the source and destinatin DPI are different. */
	bool NeedConversion() const { return m_src_dpi != m_dst_dpi; }

	/** Convert device independant point to pixel. */
	int DpToPx(int dp) const;

	/** Convert millimeter to pixel. */
	int MmToPx(int mm) const;

	/** Get a pixel value from string in any of the following formats:
		str may be nullptr. def_value is returned on fail.

		Device independent point:		"1", "1dp"
		Pixel value:					"1px"
		*/
	int GetPxFromString(const char *str, int def_value) const;

	/** Get a pixel value from TBValue.
		value may be nullptr. def_value is returned on fail.

		Number formats are treated as dp.
		String format is treated like for GetPxFromString.
		*/
	int GetPxFromValue(TBValue *value, int def_value) const;
};

}; // namespace tb

#endif // TB_DIMENSION_H
