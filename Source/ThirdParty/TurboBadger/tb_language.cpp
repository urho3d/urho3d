// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_language.h"
#include "tb_system.h"
#include "tb_node_tree.h"

namespace tb {

TBLanguage::~TBLanguage()
{
	Clear();
}

bool TBLanguage::Load(const char *filename)
{
	// Read the file into a node tree (even though it's only a flat list)
	TBNode node;
	if (!node.ReadFile(filename))
		return false;

	// Go through all nodes and add to the strings hash table
	TBNode *n = node.GetFirstChild();
	while (n)
	{
		const char *str = n->GetValue().GetString();
		TBStr *new_str = new TBStr(str);
		if (!new_str || !strings.Add(TBID(n->GetName()), new_str))
		{
			delete new_str;
			return false;
		}
		n = n->GetNext();
	}
	return true;
}

void TBLanguage::Clear()
{
	strings.DeleteAll();
}

const char *TBLanguage::GetString(const TBID &id)
{
	if (TBStr *str = strings.Get(id))
		return *str;
#ifdef TB_RUNTIME_DEBUG_INFO
	static TBStr tmp;
	tmp.SetFormatted("<TRANSLATE:%s>", id.debug_string.CStr());
	return tmp;
#else
	return "<TRANSLATE!>";
#endif
}

}; // namespace tb
