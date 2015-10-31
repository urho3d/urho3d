// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_ID_H
#define TB_ID_H

#include "tb_types.h"
#include "tb_hash.h"
#include "tb_str.h"

namespace tb {

/** TBID is a wrapper for a uint32 to be used as ID.
	The uint32 can be set directly to any uint32, or it can be
	set from a string which will be hashed into the uint32. */
class TBID
{
public:
	TBID(uint32 id = 0)				{ Set(id); }
	TBID(const char *string)		{ Set(string); }
	TBID(const TBID &id)			{ Set(id); }

#ifdef TB_RUNTIME_DEBUG_INFO
	void Set(uint32 newid);
	void Set(const TBID &newid);
	void Set(const char *string);
#else
	void Set(uint32 newid)			{ id = newid; }
	void Set(const TBID &newid)		{ id = newid; }
	void Set(const char *string)	{ id = TBGetHash(string); }
#endif

	operator uint32 () const		{ return id; }
	const TBID& operator = (const TBID &id) { Set(id); return *this; }
private:
	uint32 id;
public:
	/** This string is here to aid debugging (Only in debug builds!)
		It should not to be used in your code! */
#ifdef TB_RUNTIME_DEBUG_INFO
	friend class TBLanguage;
	TBStr debug_string;
#endif
};

}; // namespace tb

#endif // TB_ID_H
