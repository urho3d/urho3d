// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_FONT_DESC_H
#define TB_FONT_DESC_H

#include "tb_types.h"
#include "tb_id.h"

namespace tb {

/** TBFontDescription describes a font.
	By default when nothing is set, the font is unspecified and means it should be inherited
	from a parent widget that specifies a font, or use the default font if no parent does. */

class TBFontDescription
{
public:
	/** Set the font ID of the font to use.
		This ID maps to the font names in TBFontInfo, which is managed from
		TBFontManager::AddFontInfo, TBFontManager::GetFontInfo.

		Example:
		If a font was added to the font manager with the name "Vera", you can
		do font_description.SetID(TBIDC("Vera")).
		*/
	void SetID(const TBID &id)											{ m_id = id; }

	/** Get the TBID for the font name (See SetID). */
	TBID GetID() const { return m_id; }

	/** Get the TBID for the TBFontFace that matches this font description.
		This is a ID combining both the font file, and variation (such as size and style),
		and should be used to identify a certain font face.

		If this is 0, the font description is unspecified. For a widget, that means that the font
		should be inherited from the parent widget. */
	TBID GetFontFaceID() const { return m_id + m_packed_init; }

	void SetSize(uint32 size)											{ m_packed.size = MIN(size, 0x8000u); }
	uint32 GetSize() const												{ return m_packed.size; }

	//not connected to anything yet
	//void SetBold(bool bold)											{ m_packed.bold = bold; }
	//bool GetBold() const												{ return m_packed.bold; }

	//not connected to anything yet
	//void SetItalic(bool italic)										{ m_packed.italic = italic; }
	//bool GetItalic() const											{ return m_packed.italic; }

	TBFontDescription() : m_packed_init(0) {}
	TBFontDescription(const TBFontDescription &src)						{ m_packed_init = src.m_packed_init; m_id = src.m_id; }
	const TBFontDescription& operator = (const TBFontDescription &src)	{ m_packed_init = src.m_packed_init; m_id = src.m_id; return *this; }
	bool operator == (const TBFontDescription &fd) const { return m_packed_init == fd.m_packed_init && m_id == fd.m_id; }
	bool operator != (const TBFontDescription &fd) const { return !(*this == fd); }
private:
	TBID m_id;
	union {
		struct {
			uint32 size : 15;
			uint32 italic : 1;
			uint32 bold : 1;
		} m_packed;
		uint32 m_packed_init;
	};
};

}; // namespace tb

#endif // TB_FONT_DESC_H
