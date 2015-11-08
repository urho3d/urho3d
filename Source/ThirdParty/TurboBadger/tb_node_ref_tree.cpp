// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_node_ref_tree.h"
#include "tb_language.h"
#include "tb_system.h"

namespace tb {

// == TBNodeRefTree ==============================================================

//static
TBLinkListOf<TBNodeRefTree> TBNodeRefTree::s_ref_trees;

TBNodeRefTree::TBNodeRefTree(const char *name) : m_name(name), m_name_id(name)
{
	s_ref_trees.AddLast(this);
}

TBNodeRefTree::~TBNodeRefTree()
{
	s_ref_trees.Remove(this);
}

TBValue &TBNodeRefTree::GetValue(const char *request)
{
	if (TBNode *node = m_node.GetNodeFollowRef(request))
		return node->GetValue();
	TBDebugPrint("TBNodeRefTree::GetValue - Request not found: %s\n", request);
	static TBValue nullval;
	return nullval;
}

//static
TBValue &TBNodeRefTree::GetValueFromTree(const char *request)
{
	assert(*request == '@');
	TBNode tmp;
	tmp.GetValue().SetString(request, TBValue::SET_AS_STATIC);
	TBNode *node = TBNodeRefTree::FollowNodeRef(&tmp);
	if (node != &tmp)
		return node->GetValue();
	static TBValue nullval;
	return nullval;
}

void TBNodeRefTree::SetValue(const char *request, const TBValue &value)
{
	if (TBNode *node = m_node.GetNode(request, TBNode::GET_MISS_POLICY_CREATE))
	{
		// FIX: Only invoke the listener if it really changed.
		node->GetValue().Copy(value);
		InvokeChangeListenersInternal(request);
	}
}

void TBNodeRefTree::InvokeChangeListenersInternal(const char *request)
{
	TBLinkListOf<TBNodeRefTreeListener>::Iterator iter = m_listeners.IterateForward();
	while (TBNodeRefTreeListener *listener = iter.GetAndStep())
		listener->OnDataChanged(this, request);
}

//static
TBNodeRefTree *TBNodeRefTree::GetRefTree(const char *name, int name_len)
{
	for (TBNodeRefTree *rt = s_ref_trees.GetFirst(); rt; rt = rt->GetNext())
		if (strncmp(rt->GetName(), name, name_len) == 0)
			return rt;
	return nullptr;
}

//static
TBNode *TBNodeRefTree::FollowNodeRef(TBNode *node)
{
	// Detect circular loops by letting this call get a unique id.
	// Update the id on each visited node and if it's already set,
	// there's a loop. This cost the storage of id in each TBNode,
	// and assumes the look up doesn't cause other lookups
	// recursively.
	// FIX: Switch to hare and teleporting tortouise?
	static uint32 s_cycle_id = 0;
	uint32 cycle_id = ++s_cycle_id;
	TBNode *start_node = node;

	while (node->GetValue().IsString())
	{
		// If not a reference at all, we're done.
		const char *node_str = node->GetValue().GetString();
		if (*node_str != '@')
			break;

		// If there's no tree name and request, we're done. It's probably a language string.
		const char *name_start = node_str + 1;
		const char *name_end = TBNode::GetNextNodeSeparator(name_start);
		if (*name_end == 0)
			break;

		TBNode *next_node = nullptr;

		// We have a "@>noderequest" string. Go ahead and do a local look up.
		if (*name_start == '>')
		{
			TBNode *local_root = node;
			while (local_root->GetParent())
				local_root = local_root->GetParent();
			next_node  = local_root->GetNode(name_start + 1, TBNode::GET_MISS_POLICY_NULL);
		}
		// We have a "@treename>noderequest" string. Go ahead and look it up from the right node tree.
		else if (TBNodeRefTree *rt = TBNodeRefTree::GetRefTree(name_start, name_end - name_start))
		{
			next_node = rt->m_node.GetNode(name_end + 1, TBNode::GET_MISS_POLICY_NULL);
		}
		else
		{
			TBDebugPrint("TBNodeRefTree::ResolveNode - No tree found for request \"%s\" from node \"%s\"\n",
						 node_str, node->GetValue().GetString());
			break;
		}

		if (!next_node)
		{
			TBDebugPrint("TBNodeRefTree::ResolveNode - Node not found on request \"%s\"\n", node_str);
			break;
		}
		node = next_node;

		// Detect circular reference loop.
		if (node->m_cycle_id != cycle_id)
			node->m_cycle_id = cycle_id;
		else
		{
			TBDebugPrint("TBNodeRefTree::ResolveNode - Reference loop detected on request \"%s\" from node \"%s\"\n",
				node_str, node->GetValue().GetString());
			return start_node;
		}
	}
	return node;
}

//static
void TBNodeRefTree::ResolveConditions(TBNode *parent_node)
{
	bool condition_ret = false;
	TBNode *node = parent_node->GetFirstChild();
	while (node)
	{
		bool delete_node = false;
		bool move_children = false;
		if (strcmp(node->GetName(), "@if") == 0)
		{
			condition_ret = node->GetValueFollowRef().GetInt() ? true : false;
			if (condition_ret)
				move_children = true;
			delete_node = true;
		}
		else if (strcmp(node->GetName(), "@else") == 0)
		{
			condition_ret = !condition_ret;
			if (condition_ret)
				move_children = true;
			delete_node = true;
		}

		// Make sure we'll skip any nodes added from a conditional branch.
		TBNode *node_next = node->GetNext();

		if (move_children)
		{
			// Resolve the branch first, since we'll skip it.
			ResolveConditions(node);
			while (TBNode *content = node->GetLastChild())
			{
				node->Remove(content);
				parent_node->AddAfter(content, node);
			}
		}

		if (delete_node)
			parent_node->Delete(node);
		else
			ResolveConditions(node);
		node = node_next;
	}
}

}; // namespace tb
