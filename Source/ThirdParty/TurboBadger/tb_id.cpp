// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_id.h"
#include "tb_hashtable.h"

namespace tb {

// == TBID ==============================================================================

#ifdef TB_RUNTIME_DEBUG_INFO

// Hash table for checking if we get any collisions (same hash value for TBID's created
// from different strings)
static TBHashTableAutoDeleteOf<TBID> all_id_hash;
static bool is_adding = false;

void TBID::Set(uint32 newid)
{
	id = newid;
	debug_string.Clear();
	if (!is_adding && tb_core_is_initialized())
	{
		if (!all_id_hash.Get(id))
		{
			is_adding = true;
			all_id_hash.Add(id, new TBID(*this));
			is_adding = false;
		}
	}
}

void TBID::Set(const TBID &newid)
{
	id = newid;
	TB_IF_DEBUG(debug_string.Set(newid.debug_string));
	if (!is_adding && tb_core_is_initialized())
	{
		if (TBID *other_id = all_id_hash.Get(id))
		{
			// If this happens, 2 different strings result in the same hash.
			// It might be a good idea to change one of them, but it might not matter.
			assert(other_id->debug_string.Equals(debug_string));
		}
		else
		{
			is_adding = true;
			all_id_hash.Add(id, new TBID(*this));
			is_adding = false;
		}
	}
}

void TBID::Set(const char *string)
{
	id = TBGetHash(string);
	TB_IF_DEBUG(debug_string.Set(string));
	if (!is_adding && tb_core_is_initialized())
	{
		if (TBID *other_id = all_id_hash.Get(id))
		{
			assert(other_id->debug_string.Equals(debug_string));
		}
		else
		{
			is_adding = true;
			all_id_hash.Add(id, new TBID(*this));
			is_adding = false;
		}
	}
}

#endif // TB_RUNTIME_DEBUG_INFO

}; // namespace tb
